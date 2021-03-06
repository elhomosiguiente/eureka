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

#ifndef __GENERALMAP_HH
#define __GENERALMAP_HH

#include "boost/unordered_map.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/path.hpp"

#include <string>
#include <vector>
#include <utility>
#include <memory>
// See comments in world.hh for the weird 'undef None'
#undef None
#include <libxml++/libxml++.h>

#include "mapobj.hh"
#include "action.hh"
#include "gameevent.hh"

class NoInitialCoordsException
{
protected:
  std::string err;

public:
  NoInitialCoordsException(std::string s) { err = s; }
  std::string print() const { return err; }
};

class Map
{
public:
  Map();
  Map(const Map&);
  virtual ~Map();

  void unload_map_data();
  std::string get_name();
  std::string get_longname();
  void set_name(const char*);
  void set_longname(const char*);
  // Loads the map from disk and overwrites any changes that may have
  // been made to the map stored in memory.  That is, the disk data
  // will shamelessly overwrite the currently used memory of the map.
  bool xml_load_map_data(boost::filesystem::path);
  bool xml_load_map_data();
  bool xml_write_map_data(boost::filesystem::path);
  bool xml_write_map_data();
  std::pair<int,int> get_initial_coords();
  // Returns true if this map has been written on disk before, i.e.,
  // this can be indirectly used to check whether the map is new or
  // not.
  bool exists_on_disk();
  unsigned height() const;
  unsigned width() const;
  bool modified() const;
  // If called like set_notmodified(), it means that the map was saved
  // and has, since then, not been modified.  If called
  // set_notmodified(false), then it means the map was modified and
  // needs saving.
  void set_notmodified(bool = true);
  // Get and set_tile use absolute map coordinates, i.e., could be
  // absolute hex values
  virtual int get_tile(unsigned, unsigned) = 0;
  virtual int set_tile(unsigned, unsigned, unsigned) = 0;
  virtual bool is_outdoors() const = 0;
  /**
   * This is not really an out-of-bounds-check, as the visible map can still be within
   * the bounds of the defined map.  But this shows whether coordinates would still be
   * on the visible map, if the game placed something on them, given as x and y.
   */
  virtual bool is_within_visible_bounds(int, int) = 0;
  // Shrink or expand map, depending on the values
  virtual void expand_map(int, int, int, int) = 0;
  void expand_map_data(int, int, int, int);
  /// Can only be called if there is EXACTLY one item in location under scrutiny!
  void pop_obj(unsigned, unsigned);
  int rm_obj_by_id(std::string);
  void rm_obj(MapObj*);
  void pop_obj_animate(unsigned, unsigned);
  void pop_obj_animate(std::pair<unsigned, unsigned>);
  void push_obj(MapObj);
  std::vector<MapObj*> get_objs(unsigned x, unsigned y);
  std::vector<MapObj*> get_objs(std::pair<unsigned, unsigned> coords);
  std::vector<std::shared_ptr<Action>> get_actions(unsigned, unsigned);
  void add_action(std::shared_ptr<Action>);
  void add_event_to_action(unsigned, unsigned, std::shared_ptr<GameEvent>);
  void del_action(unsigned, unsigned);
  boost::unordered_multimap<std::pair<unsigned, unsigned>, MapObj>* objs();
  unsigned how_many_mapobj_at(unsigned, unsigned);

  bool guarded_city;
  bool is_dungeon;
  bool initial;

protected:
  // Variables
  std::string _name;
  std::string _longname;
  // xmlpp::Document* _main_map_xml_file;
  // xmlpp::Node* _main_map_xml_root;
  bool _modified;
  int initial_x, initial_y;

  // XML-helper functions
  void parse_node(const xmlpp::Node*);
  void parse_objects_node(const xmlpp::Node*);
  MapObj return_object_node(const xmlpp::Element*);
  void parse_data_node(const xmlpp::Node*);
  std::vector<std::shared_ptr<Action>> parse_actions_node(const xmlpp::Node*);
  void write_action_node(xmlpp::Element*, Action*);
  bool write_obj_xml_node(MapObj, xmlpp::Element*);

  // Map data and stuff...
  std::vector<std::vector<unsigned>>                               _data;
  boost::unordered_multimap<std::pair<unsigned, unsigned>, MapObj> _map_objects;
  std::vector<std::shared_ptr<Action>>                             _actions;
};

#endif
