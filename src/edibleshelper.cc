/*
 * shieldhelper.cc
 *
 *  Created on: Jun 22, 2014
 *      Author: baueran
 */

#include "edibleshelper.hh"
#include "edible.hh"
#include "luawrapper.hh"
#include "luaapi.hh"        // to define _lua_state

#include <string>

#include <boost/algorithm/string.hpp>

EdiblesHelper::EdiblesHelper()
{
/*	globArrayName = "Shields";*/
}

EdiblesHelper::~EdiblesHelper()
{
	// TODO Auto-generated destructor stub
}

// See ShieldHelper.

Edible* EdiblesHelper::createFromLua(std::string array_name)
{
	std::string globArrayName = "Edibles";
	LuaWrapper lua(_lua_state);
	Edible *w = new Edible();

	w->name(lua.get_item_prop<std::string>(globArrayName, array_name, "name"));
	w->plural_name(lua.get_item_prop<std::string>(globArrayName, array_name, "plural_name"));

	w->food_up = (int)(lua.get_item_prop<double>(globArrayName, array_name, "food_up"));
	w->healing_power = stringToEmphasis.at(boost::to_upper_copy<std::string>(lua.get_item_prop<std::string>(globArrayName, array_name, "healing_power")));
	w->poison_healing_power = stringToEmphasis.at(boost::to_upper_copy<std::string>(lua.get_item_prop<std::string>(globArrayName, array_name, "poison_healing_power")));
	w->poisonous = stringToEmphasis.at(boost::to_upper_copy<std::string>(lua.get_item_prop<std::string>(globArrayName, array_name, "poisonous")));
	w->is_magic_herb = boost::to_upper_copy<std::string>(lua.get_item_prop<std::string>(globArrayName, array_name, "magic_herb")) == "TRUE" ? true : false;
	w->intoxicating = stringToEmphasis.at(boost::to_upper_copy<std::string>(lua.get_item_prop<std::string>(globArrayName, array_name, "intoxicating_effect")));

	w->weight((int)(lua.get_item_prop<double>(globArrayName, array_name, "weight")));
	w->icon = (int)(lua.get_item_prop<double>(globArrayName, array_name, "icon"));
	w->gold((int)(lua.get_item_prop<double>(globArrayName, array_name, "gold")));

	return w;
}

// Returns true if the Lua array has an entry named item_name, false otherwise.

bool EdiblesHelper::exists(std::string item_name)
{
	LuaWrapper lua(_lua_state);
	return lua.hasEntry("Edibles", item_name);
}