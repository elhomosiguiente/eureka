// ----------------------------------------------------------------
// leibniz
//
// Copyright (c) 2009  Andreas Bauer <baueran@gmail.com>
//
// This is not free software.  See COPYING for further information.
// ----------------------------------------------------------------

#include <string>
#include <sstream>
#include <gtkmm.h>
#include <vector>
#include <iostream>
#include "selectmapwin.hh"
#include "../world.hh"
#include "../map.hh"

SelectMapWin::SelectMapWin(void)
  :  bok(Gtk::Stock::OK),
     bcancel(Gtk::Stock::CANCEL)
{
  set_title("Select maps");
  show_all_children();
  set_modal(true);
  set_default_size(400, 200);

  align.set_padding(10, 10, 10, 10);
  add(align);

  _swin.add(_tview);
  _swin.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  vbox.add(_swin);
  vbox.add(sep);
  align.add(vbox);

  _tview.get_selection()->signal_changed().
    connect(sigc::mem_fun(*this, &SelectMapWin::row_changed_event), false);
  
  bcancel.
    signal_clicked().
    connect(sigc::mem_fun(*this, &SelectMapWin::on_button_cancel));
  bok.
    signal_clicked().
    connect(sigc::mem_fun(*this, &SelectMapWin::on_button_ok));

  // Create the Tree model
  _tmodel = Gtk::ListStore::create(_cols);
  _tview.set_model(_tmodel);

  // Prepare tree view data
  std::vector<Map*>* vmaps = World::Instance().get_maps();
  for (std::vector<Map*>::iterator curr_map = vmaps->begin(); 
       curr_map != vmaps->end(); curr_map++)
    {
      if ((*curr_map)->exists_on_disk())
	{
	  Gtk::TreeModel::Row row = *(_tmodel->append());
	  row[_cols.m_col_name] = (*curr_map)->get_name();
	  row[_cols.m_col_outdoors] = (*curr_map)->is_outdoors();
	}
    }

  // Shove tree view data into actual tree view and do some cosmetics
  _tview.append_column("Map name", _cols.m_col_name);
  int num_columns = _tview.append_column("Outdoors", _cols.m_col_outdoors);
  for (int i = 0; i < num_columns; i++)
    {
      _tview.get_column(i)->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
      _tview.get_column(i)->set_resizable(true);
    }
  _tview.get_column(0)->set_fixed_width(250);

  // Until the user selected a map disable ok/select button.
  bok.set_sensitive(false);

  hbox_b.set_homogeneous();
  hbox_b.set_spacing(10);
  hbox_b.pack_end(bok);
  hbox_b.pack_end(bcancel);
  hbox_b_space.set_spacing(50);
  hbox_b.pack_end(hbox_b_space);
  vbox.pack_start(hbox_b, Gtk::PACK_SHRINK);
  vbox.set_spacing(10);

  bok.set_can_default();
  bok.grab_default();

  show_all_children();
}

SelectMapWin::~SelectMapWin(void)
{
}

void SelectMapWin::on_button_cancel(void)
{
  hide();
}

void SelectMapWin::on_button_ok(void)
{
  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = 
    _tview.get_selection();

  if (refSelection)
    {
      Gtk::TreeModel::iterator iter = refSelection->get_selected();

      if (iter)
	{
	  std::stringstream tmp;
	  tmp << (*iter)[_cols.m_col_name];
	  _selected_map = tmp.str();
	  //	  std::cout << "Map: " << (*iter)[_cols.m_col_name] << std::endl;
	}
    }
  hide();
}

std::string SelectMapWin::get_selected_map(void) const
{
  return _selected_map;
}

void SelectMapWin::row_changed_event(void)
{
  if (_tview.get_selection()->count_selected_rows() > 0)
    bok.set_sensitive(true);
  else
    bok.set_sensitive(false);
}
