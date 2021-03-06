// This source file is part of eureka
//
// Copyright (c) 2007-2018 Andreas Bauer <a@pspace.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

#include <string>
#include <iostream>
#include <memory>
#include <algorithm> // sort

#include "gamecontrol.hh"  // TODO: This could be removed, only use it for random number generator.
#include "playercharacter.hh"
#include "profession.hh"
#include "race.hh"
#include "spell.hh"
#include "ztatswincontentprovider.hh"
#include "util.hh"
#include "world.hh"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>

PlayerCharacter::PlayerCharacter(): _is_npc(false), _ep(0), _level(1)
{
	_condition = GOOD;
	_prof = FIGHTER; // Bogus value, which will be overwritten
}

PlayerCharacter::PlayerCharacter(const char* name, int hpm, int spm, 
				 int str, int luck, int dxt, int wis, 
				 int charr, int iq, int end, bool sex, int level,
				 RACE race, PROFESSION profession) : PlayerCharacter()
{
	_race = race;
	_prof = profession;
	_name = name;
	_hp_max = hpm;
	_hp = hpm;
	_sp = spm;
	_sp_max = spm;
	_str = str;
	_luck = luck;
	_dxt = dxt;
	_wis = wis;
	_char = charr;
	_iq = iq;
	_end = end;
	_sex = sex;
	_level = level;

	_is_npc = false; // Default

	_condition = GOOD;
	_ep = 0;
	// TODO: active_spells?
}

PlayerCharacter::PlayerCharacter(const PlayerCharacter& p) : GameCharacter(p)
{
	_prof = p._prof;
	_level = p._level;
	_ep = p._ep;
	_is_npc = p._is_npc;
}

bool PlayerCharacter::is_spell_caster()
{
	return _prof == MAGE || _prof == CLERIC || _prof == DRUID || _prof == NECROMANCER || _prof == ARCHMAGE || _prof == GEOMANCER;
}

int PlayerCharacter::ep()
{
	return _ep;
}

void PlayerCharacter::inc_ep(int ne)
{
	_ep += ne;
}

PROFESSION PlayerCharacter::profession()
{
	return _prof;
}

void PlayerCharacter::set_profession(PROFESSION np)
{
  _prof = np;
}


void PlayerCharacter::set_level_passively(const int l)
{
	_level = l;
}

// This not simply sets the level, but, if l greater than the current level, increases the player characteristics.

void PlayerCharacter::set_level_actively(const int l)
{
	if (l <= _level) {
		std::cerr << "WARNING: playercharacter.cc: Tried to set a lower (or the same) experience level for " << name() << " than he/she currently has. Level NOT set!\n";
		return;
	}

	GameControl& gc = GameControl::Instance();

	// Now update the character properties, once for each level raised.
	int levels = potential_level() - level();
	for (int i = 0; i < levels; i++) {
		_hp_max = _hp_max + gc.random(3,6);

		if (is_spell_caster()) {
			_sp_max = _sp_max + gc.random(3,6);
			_sp = _sp_max;
		}

		_str  = min(18, _str + gc.random(0,1));
		_dxt  = min(18, _dxt + gc.random(0,1));
		_end  = min(18, _end + gc.random(0,1));
		_wis  = min(18, _wis + gc.random(0,1));
		_iq   = min(18, _iq + gc.random(0,1));
		_luck = min(18, _luck + gc.random(0,1));
	}

	_level = l;
}

int PlayerCharacter::level()
{
	return _level;
}

std::shared_ptr<ZtatsWinContentSelectionProvider<Spell>> PlayerCharacter::create_spells_content_selection_provider()
{
	std::shared_ptr<ZtatsWinContentSelectionProvider<Spell>> content_selection_provider(new ZtatsWinContentSelectionProvider<Spell>());
	std::vector<std::pair<StringAlignmentTuple, Spell>> content_page;

	if (is_spell_caster()) {

		std::map<std::string, int> spell_list;
		std::map<std::string, std::string> spell_file_paths;

		for (auto spell : *(World::Instance().get_spells())) {
			if (profession() == spell.profession && level() >= spell.level) {
				std::string spell_name  = (char)(toupper(spell.name[0])) + spell.name.substr(1);
				std::string spell_descr = spell_name + " (Lvl " + std::to_string(spell.level) + ", SP: " + std::to_string(spell.sp) + ")";
				content_page.push_back(std::pair<StringAlignmentTuple, Spell>(StringAlignmentTuple(spell_descr, Alignment::LEFTALIGN), spell));
			}
		}

	    auto sortRuleLambda = [] (const std::pair<StringAlignmentTuple, Spell>& s1, const std::pair<StringAlignmentTuple, Spell>& s2) -> bool {
	       return s1.second.name.compare(s2.second.name) < 0;
	    };
		std::sort(content_page.begin(), content_page.end(), sortRuleLambda);
		content_selection_provider->add_content_page(content_page);

		if (content_page.size() > 0)
			content_selection_provider->add_content_page(content_page);
		else
			std::cout << "INFO: playercharacter.cc: Created an empty ZtatsWinContentSelectionProvider object.\n";
	}

	return content_selection_provider;
}

// Returns the level a character can be in potentially; that is, if the player then goes through the
// up-levelling ritual (whatever that will turn out to be in this game - TODO)
//
// Initially it probably makes sense to have actual level == potential level.

int PlayerCharacter::potential_level()
{
	int lev = 1;

	switch (_race) {
	case HUMAN:
		if (_ep >= 50)
			lev = 2;
		if (_ep >= 100)
			lev = 3;
		if (_ep >= 200)
			lev = 4;
		if (_ep >= 400)
			lev = 5;
		if (_ep >= 800)
			lev = 6;
		if (_ep >= 1600)
			lev = 7;
		if (_ep >= 3200)
			lev = 8;
		if (_ep >= 5000)
			lev = 9;
		if (_ep >= 10000)
			lev = 10;
		break;
	case ELF: // slower progress than human
		if (_ep >= 100)
			lev = 2;
		if (_ep >= 200)
			lev = 3;
		if (_ep >= 400)
			lev = 4;
		if (_ep >= 800)
			lev = 5;
		if (_ep >= 1600)
			lev = 6;
		if (_ep >= 3200)
			lev = 7;
		if (_ep >= 6000)
			lev = 8;
		if (_ep >= 10000)
			lev = 9;
		if (_ep >= 15000)
			lev = 10;
		break;
	case HOBBIT: // slightly quicker progress than human
		if (_ep >= 50)
			lev = 2;
		if (_ep >= 100)
			lev = 3;
		if (_ep >= 200)
			lev = 4;
		if (_ep >= 400)
			lev = 5;
		if (_ep >= 800)
			lev = 6;
		if (_ep >= 1200)
			lev = 7;
		if (_ep >= 2000)
			lev = 8;
		if (_ep >= 5000)
			lev = 9;
		if (_ep >= 8000)
			lev = 10;
		break;
	case HALF_ELF: // quick to progress at first but slow to finish
		if (_ep >= 50)
			lev = 2;
		if (_ep >= 100)
			lev = 3;
		if (_ep >= 200)
			lev = 4;
		if (_ep >= 400)
			lev = 5;
		if (_ep >= 800)
			lev = 6;
		if (_ep >= 1600)
			lev = 7;
		if (_ep >= 4000)
			lev = 8;
		if (_ep >= 8000)
			lev = 9;
		if (_ep >= 15000)
			lev = 10;
		break;
	case DWARF: // slow to progress at first but quick to finish, bit like hobbit really
		if (_ep >= 10)
			lev = 2;
		if (_ep >= 200)
			lev = 3;
		if (_ep >= 400)
			lev = 4;
		if (_ep >= 800)
			lev = 5;
		if (_ep >= 1200)
			lev = 6;
		if (_ep >= 2000)
			lev = 7;
		if (_ep >= 4000)
			lev = 8;
		if (_ep >= 8000)
			lev = 9;
		if (_ep >= 10000)
			lev = 10;
		break;
	default:
		std::cerr << "WARNING: playercharacter.cc: animals do not have a potential level, no?!\n";
		break;
	}

	return lev;
}

bool PlayerCharacter::is_npc()
{
	return _is_npc;
}

void PlayerCharacter::set_npc()
{
	_is_npc = true;
}
