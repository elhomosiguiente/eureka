//
//
// Copyright (c) 2012  Andreas Bauer <baueran@gmail.com>
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

#include <iostream>
#include <string>
#include "item.hh"

using namespace std;

Item::Item()
{
	std::cout << "Item()" << std::endl;
	icon = 0;
	_weight = 0;
}

Item::Item(const Item& i)
{
	std::cout << "Item(const Item&): i: " << i.icon << std::endl;
	_name = i._name;
	_plural_name = i._plural_name;
	_weight = i._weight;
	icon = i.icon;
	_gold = i._gold;
}

Item& Item::operator=(const Item& i)
{
	std::cout << "Item::operator=" << std::endl;
	_name = i._name;
	_plural_name = i._plural_name;
	_weight = i._weight;
	icon = i.icon;
	_gold = i._gold;
	return *this;
}

int Item::gold()
{
	return _gold;
}

void Item::gold(int g)
{
	_gold = g;
}

std::string Item::name() const
{
	return _name;
}

Item& Item::name(const string n)
{
	_name = n;
	return *this;
}

const string& Item::plural_name()
{
	return _plural_name;
}

Item& Item::plural_name(const string n)
{
	_plural_name = n;
	return *this;
}

unsigned Item::weight()
{
	return _weight;
}

void Item::weight(unsigned new_weight)
{
	_weight = new_weight;
}

std::string Item::luaName()
{
	return "";
}
