-- -----------------------------------------------
-- Troll definition file for eureka
-- Copyright (c) Andreas Bauer <baueran@gmail.com>
-- -----------------------------------------------

require "string"
require "math"

do
   local hp          = 0
   local hp_max      = 0
   local weapon      = nil
   local strength    = 16
   local luck        = 12
   local dxt         = 12
   local distance    = 0
   local gold        = 0
   local ep          = 10

   local name        = "Wolf"
   local plural_name = "Wolves"
   local distance    = 0
   
   local combat      = ""
   local nth_foe     = 0

   local player_name = "" -- Name of party member who is attacked

   function create_instance()
      hp_max   = simpl_rand(5, 15) + 5
      hp       = hp_max
      weapon   = nil
      strength = simpl_rand(5, 14) + 4
      luck     = simpl_rand(5, 12)
      gold     = 0
   end

   function set_combat_ptr(ptr, number)
      combat  = ptr
      nth_foe = number
      simpl_set_combat_ptr(combat)
   end

   function get_name() 
      return name
   end

   function get_plural_name()      
      return plural_name
   end

   function get_ep()
      return ep
   end

   function set_gold(new_gold)
      gold = new_gold
   end

   function get_gold()
      return gold
   end

   function get_distance()
      return distance
   end

   function set_distance(new_dist)
      distance = new_dist
   end

   function img_path()
      return simpl_datapath() .. "/bestiary/wolves.png"
   end
   
   function get_hp()
      return hp
   end

   function set_hp(new_hp)
      hp = new_hp
   end

   function get_hp_max()
      return hp_max
   end

   function set_hp_max(new_hp_max)
      hp_max = new_hp_max
   end

   function get_strength()
      return strength
   end

   function get_luck()
      return luck
   end

   function set_luck(new_luck)
      luck = new_luck
   end

   function get_dxt()
      return dxt
   end

   function set_dxt(newdxt)
      dxt = newdxt
   end

   function get_weapon()
      return ""
   end

   function set_weapon(name)
      weapon = Weapons[name]
   end

   -- Return true if, when given a chance to, the foe rather advances
   -- than fights.  If false is returned, it indicates that the foe
   -- can actually fight from the distance, say, with a long range
   -- weapon or with a magic spell, etc.

   function advance()
      return true
   end

   function flee()
      simpl_flee(nth_foe)
   end

   function attack()
      if (get_hp() < get_hp_max() / 100 * 20) then
	 flee()
	 return false
      end

      player_name = simpl_rand_player(1) -- Get exactly 1 random player to be attacked

      r = simpl_rand(1, 20) - simpl_bonus(get_luck()) - simpl_bonus(get_dxt())
      attack_successful = r < simpl_get_ac(player_name)
      
      if (attack_successful == false) then
      	 simpl_printcon(string.format("A %s tries to reach %s with its massive claws but misses.", 
				       get_name(), player_name), true)
      end
		     
      return attack_successful
   end

   function fight()
      if (distance > 10) then
      	 simpl_printcon(string.format("A %s reaches for %s but cannot reach.",
      				      get_name(), player_name), true)
      	 return
      end

      damage = simpl_rand(2, 5)
      simpl_printcon(string.format("A %s rams its teeth into %s's flesh and hits for %d points of damage.",
				   get_name(), player_name, damage, player_name), true)
    				                
      simpl_player_change_hp(player_name, -damage)
      simpl_notify_party_hit()
   end
      
end