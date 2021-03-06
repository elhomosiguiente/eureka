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

#ifndef PLAYERCHARACTER_HH
#define PLAYERCHARACTER_HH

#include "race.hh"
#include "profession.hh"
#include "gamecharacter.hh"
#include "spell.hh"
#include "ztatswincontentprovider.hh"

#include <string>
#include <memory>

#include <boost/unordered_map.hpp>

enum PlayerState {
  NORMAL_STATE, 
  DRUNK_STATE, 
  ASLEEP_STATE, 
  POSSESSED_STATE, 
  PARALYSED_STATE
};

// TODO: Add invincibility/invisible, but one can be
// invincible/invisible and possessed, for example.

class PlayerCharacter : public GameCharacter
{
private:
  PROFESSION  _prof;
  bool 	      _is_npc;
  int         _ep;
  int         _level;
  boost::unordered_map<std::string, int> _active_spells;

public:
  PlayerCharacter();
  PlayerCharacter(const char*, int hpm = 0, int spm = 0, int str = 0, 
		  int luck = 0, int dxt = 0, int wis = 0, int charr = 0,
		  int iq = 0, int end = 0, bool sex = true, int level = 1,
		  RACE = HUMAN, PROFESSION = FIGHTER);
  PlayerCharacter(const PlayerCharacter&);
  PROFESSION profession();
  void set_profession(PROFESSION);
  int ep();
  void inc_ep(int);
  int level();
  void set_level_actively(const int);
  void set_level_passively(const int);
  int potential_level();
  bool is_spell_caster();
  std::shared_ptr<ZtatsWinContentSelectionProvider<Spell>> create_spells_content_selection_provider();
  bool is_npc();
  void set_npc();
};

#endif
