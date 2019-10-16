// lua-leap"

#include "lleap.hpp"
#include "leap-controller.hpp"

#define LUALEAP_VERSION		"lua-leap 0.1.0"
#define LUALEAP_COPYRIGHT	"Copyright (C) 2017, 2019 - Lua-leap by Marco Pompili (pompilimrc@gmail.com)."
#define LUALEAP_DESCRIPTION	"Lua bindings for Leap Motion Controller."

// Lib

static int leap_wait_loop(lua_State *L)
{
  printf("Press Enter to quit...");
  
  while(1)
  {
    char c = getchar();

    if (c == '\n')
      break;
  }
  
  return 0;
}

static const struct luaL_Reg leap_f[] =
{
 {"Controller", leap_ctrl__new},
 {"waitLoop", leap_wait_loop},
 {NULL, NULL}
};

extern "C"
{  
  // Initialization
  LUALIB_API int luaopen_leap(lua_State *L)
  {
    // Lib table
    lua_createtable(L, 0, 6);

    // register module information
    lua_pushliteral(L, LUALEAP_VERSION);
    lua_setfield(L, -2, "_VERSION");

    lua_pushliteral(L, LUALEAP_COPYRIGHT);
    lua_setfield(L, -2, "_COPYRIGHT");

    lua_pushliteral(L, LUALEAP_DESCRIPTION);
    lua_setfield(L, -2, "_DESCRIPTION");

    // Finger table
    lua_pushliteral(L, "Finger");
    lua_createtable(L, 0, 3);

    // Joint types
    lua_pushinteger(L, Leap::Finger::JOINT_MCP);
    lua_setfield(L, -2, "JOINT_MCP");

    lua_pushinteger(L, Leap::Finger::JOINT_PIP);
    lua_setfield(L, -2, "JOINT_PIP");

    lua_pushinteger(L, Leap::Finger::JOINT_DIP);
    lua_setfield(L, -2, "JOINT_DIP");

    lua_pushinteger(L, Leap::Finger::JOINT_TIP);
    lua_setfield(L, -2, "JOINT_TIP");

    // Finger types
    lua_pushinteger(L, Leap::Finger::TYPE_THUMB);
    lua_setfield(L, -2, "TYPE_THUMB");

    lua_pushinteger(L, Leap::Finger::TYPE_INDEX);
    lua_setfield(L, -2, "TYPE_INDEX");

    lua_pushinteger(L, Leap::Finger::TYPE_MIDDLE);
    lua_setfield(L, -2, "TYPE_MIDDLE");

    lua_pushinteger(L, Leap::Finger::TYPE_RING);
    lua_setfield(L, -2, "TYPE_RING");

    lua_pushinteger(L, Leap::Finger::TYPE_PINKY);
    lua_setfield(L, -2, "TYPE_PINKY");

    lua_settable(L, -3);

    // Gesture table
    lua_pushliteral(L, "Gestures");
    lua_createtable(L, 0, 2);

    // States
    lua_pushinteger(L, Leap::Gesture::STATE_INVALID);
    lua_setfield(L, -2, "STATE_INVALID");

    lua_pushinteger(L, Leap::Gesture::STATE_START);
    lua_setfield(L, -2, "STATE_START");

    lua_pushinteger(L, Leap::Gesture::STATE_UPDATE);
    lua_setfield(L, -2, "STATE_UPDATE");

    lua_pushinteger(L, Leap::Gesture::STATE_STOP);
    lua_setfield(L, -2, "STATE_STOP");

    // Types
    lua_pushinteger(L, Leap::Gesture::TYPE_INVALID);
    lua_setfield(L, -2, "TYPE_INVALID");

    lua_pushinteger(L, Leap::Gesture::TYPE_SWIPE);
    lua_setfield(L, -2, "TYPE_SWIPE");

    lua_pushinteger(L, Leap::Gesture::TYPE_CIRCLE);
    lua_setfield(L, -2, "TYPE_CIRCLE");

    lua_pushinteger(L, Leap::Gesture::TYPE_SCREEN_TAP);
    lua_setfield(L, -2, "TYPE_SCREEN_TAP");

    lua_pushinteger(L, Leap::Gesture::TYPE_KEY_TAP);
    lua_setfield(L, -2, "TYPE_KEY_TAP");

    lua_settable(L, -3);

    // Lib functions
    luaL_setfuncs(L, leap_f , 0);

    return 1;
  }
}
