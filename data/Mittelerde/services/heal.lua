-- -----------------------------------------------
-- Services definition file for eureka
-- Copyright (c) Andreas Bauer <baueran@gmail.com>
-- -----------------------------------------------

Services["heal"]  = { 
   name                   = "heal", 

   heal                   = 50000,   -- Heal completely! No one has more than 50.000 HP!
   heal_poison            = true,
   resurrect              = false,
   level_up               = false,

   print_after            = "Healing was successful!",

   gold                   = 25
}
