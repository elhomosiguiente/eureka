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

#ifndef MISCITEM_HH
#define MISCITEM_HH

#include <string>

#include "item.hh"
#include "mapobj.hh"

class MiscItem : public Item
{
private:
	MapObj _mapObj;
	bool _has_mapobj;

public:
	MiscItem();
	virtual ~MiscItem();
	MiscItem(const MiscItem&);

	MapObj get_obj();
	void set_obj(MapObj);
	std::string get_lua_name();
	bool has_mapobj();
};

#endif
