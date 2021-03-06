-- -----------------------------------------------
-- Conversation definition file for eureka
-- Copyright (c) Andreas Bauer <a@pspace.org>
-- -----------------------------------------------

do
   -- --------------------------------------------------------
   -- Define character values for either party-join or a fight
   -- --------------------------------------------------------

   c_values = { 
      name = "Lera", race = "HUMAN", ep = 0, hp = 10, hpm = 10, sp = 0, spm = 0, str = 7, luck = 15, dxt = 15, wis = 4, charr = 14, 
      iq = 15, endd = 7, sex = "MALE", profession = "MAGE", weapon = Weapons["axe"], shield = Shields["small shield"] 
   } 

   conv_over = false
   
   -- -----------------------------------------------
   -- Standard functions
   -- -----------------------------------------------

   function get_weapon()
      return c_values["weapon"].name
   end

   function get_shield()
      return c_values["shield"].name
   end

   function get_armour()
      return "" -- we ignore armour
   end

   function load_generic_fight_file(name)
      dofile(name) -- To enable combat, must be inserted AFTER c_values is defined!
   end

   function conversation_over()
      return conv_over
   end

   -- -----------------------------------------------
   -- Standard terms
   -- -----------------------------------------------

   items = {}
   items[0] = Edibles["chamomilla"]
   items[1] = Edibles["arnica"]
   items[2] = Edibles["magic mushroom"]
   items[3] = Edibles["garlic"]
   items[4] = Edibles["gelsemium"]
   items[5] = Edibles["sulphur"]
   items[6] = Edibles["thuja"]
   items[7] = Edibles["morbilinium"]

   function description()
      simpl_printcon("You see pretty woman wearing an unorderly, old dress.")
   end

   function name()
      simpl_printcon("My name is " .. c_values["name"] .. ", I collect herbs and sell them to the people who need them. " ..
		     "Are you interested in buying some? (y/n)")

      answer = simpl_getkey("yn")
      simpl_printcon(string.format("%s ", answer))
      if (answer == "y") then
	 simpl_ztatssave()
	 buy()
	 simpl_ztatsrestore()
      else
	 simpl_printcon("Perhaps another time then. What else do you want to know?")
      end
   end

   function buy()
      -- Pass items for displaying and choice in ztats-window
      selected_item = simpl_ztatsshopinteraction(items)
      
      -- Try to add item to player inventory, if something was selected
      if (string.len(selected_item) > 0) then
         buyResult = simpl_buyitem(selected_item)
         if (buyResult == -1) then
            simpl_printcon("It seems, you already carry too much.")
         elseif (buyResult == -2) then
            simpl_printcon("You don't have enough gold.")
         elseif (buyResult == 0) then
            simpl_printcon("I am sure it will guide you well.")
         else
            simpl_printcon("Hmmm... This transaction failed.")
         end
      else
         simpl_printcon("Changed your mind then, eh?")
      end
      
      simpl_printcon("Dost thou seek to undertake further business? (y/n)")
      job2()
   end
   
   function job()
      simpl_printcon("I supply the folks around here with the essentials. Dost thou need some? (y/n)")
      job2()
   end
   
   function job2()
      answer = simpl_getkey("yn")
      simpl_printcon(string.format("%s ", answer))
      
      if (answer == "y") then
	 simpl_ztatssave()
	 buy()
	 simpl_ztatsrestore()
      else
	 simpl_printcon("Perhaps another time then. What else do you want to know?")
      end
   end
   
   function join()
      simpl_printcon("I cannot join thee, my responsibilities are with my store.")
      return false
   end
  
   function bye()
      simpl_printcon("Good bye, traveller!")
   end
   
   function otherwise(item)
      if (item == "melnior") then
	 simpl_printcon("Melnior is the great wizard of Velnibras. You can find him in the tower in the south east behind a magical force field.")
      elseif (string.find(item,"force") or string.find(item, "magic")) then
	 simpl_printcon("Thou must not attempt to enter without protection, or you will die!")
      else
	 simpl_printcon("I am sorry, I cannot help you with that.")
      end
   end
end
