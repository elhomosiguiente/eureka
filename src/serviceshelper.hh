/*
 * shieldhelper.hh
 *
 *  Created on: Jun 22, 2014
 *      Author: baueran
 */

#ifndef SERVICESHELPER_HH_
#define SERVICESHELPER_HH_

#include <string>

#include <lua.h>
#include <lualib.h>

#include "playercharacter.hh"
#include "service.hh"

class ServicesHelper
{
public:
  ServicesHelper();
  virtual ~ServicesHelper();
  static Service* createFromLua(std::string, lua_State*);
  static bool existsInLua(std::string, lua_State*);
  static void apply(Service*, int);
};

#endif
