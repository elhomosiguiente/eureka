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

#ifndef OUTDOORSMAP_HH
#define OUTDOORSMAP_HH

#include "map.hh"

class OutdoorsMap : public Map
{
public:
  OutdoorsMap(unsigned, unsigned);
  OutdoorsMap(const char*);
  ~OutdoorsMap();

  bool is_outdoors() const;
  bool is_dungeon() const;
  void set_dungeon(bool);
  int get_tile(unsigned, unsigned);
  int set_tile(unsigned, unsigned, unsigned);
  void expand_map(int, int, int, int);
  bool is_within_visible_bounds(int, int);
};

#endif
