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

#ifndef EDIBLE_HH
#define EDIBLE_HH

#include "item.hh"
#include "eureka.hh"
#include <string>

class Edible : public Item
{
public:
  Edible();
  virtual ~Edible();
  Edible(const Edible&);

  int      food_up;
  Emphasis healing_power;
  Emphasis poison_healing_power;
  Emphasis poisonous;
  bool     is_magic_herb;
  Emphasis intoxicating;

  std::string get_lua_name();
};

#endif
