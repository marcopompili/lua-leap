#include "leap-controller.hpp"

static int leap_ctrl__tostring(lua_State *L)
{
  Leap::Controller *ctrl = *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));
  char out[128];

  sprintf(out, "<Leap::Controller>\nConnected: %d\nService Connected: %d\n",
          ctrl->isConnected(),
          ctrl->isServiceConnected());

  lua_pushstring(L, out);

  return 1;
}

static int leap_ctrl__gc(lua_State *L)
{
  delete *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));

  return 0;
}

static int leap_ctrl_enable_gesture(lua_State *L)
{
  if (lua_gettop(L) < 3) {
    luaL_error(L, "This method needs two arguments");
  }

  Leap::Controller *ctrl = *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));

  int t = luaL_checkinteger(L, 2);

  if (4 < t && t > 6) {
    luaL_error(L, "Invalid Gesture type");
  }

  bool e = lua_toboolean(L, 3);

  ctrl->enableGesture(Leap::Gesture::Type(t), e);

  return 0;
}

  static int leap_ctrl_is_connected(lua_State *L)
  {
    Leap::Controller *ctrl = *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));

    lua_pushboolean(L, ctrl->isConnected());
  
    return 1;
  }

static int leap_ctrl_is_gesture_enabled(lua_State *L)
{
  if (lua_gettop(L) < 2) {
    luaL_error(L, "This method needs 1 argument");
  }

  Leap::Controller *ctrl = *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));

  Leap::Gesture::Type t = Leap::Gesture::Type(lua_tointeger(L, 2));

  lua_pushboolean(L, ctrl->isGestureEnabled(t));

  return 1;
}

  static int leap_ctrl_is_service_connected(lua_State *L)
  {
    Leap::Controller *ctrl = *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));

    lua_pushboolean(L, ctrl->isServiceConnected());

    return 1;
  }

static int leap_ctrl_frame(lua_State *L)
{
  Leap::Controller *ctrl = *static_cast<Leap::Controller**>(luaL_checkudata(L, 1, LEAP_MT_CONTROLLER));

  int history = 0;

  if (lua_gettop(L) > 2)
    history = lua_tointeger(L, 2);

  Leap::Frame f = ctrl->frame(history);
  Leap::HandList hands = f.hands();

  lua_createtable(L, 0, 0);
  
  // Frame id
  lua_pushinteger(L, f.id());
  lua_setfield(L, -2, "ID");

  // Timestamp
  lua_pushinteger(L, f.timestamp());
  lua_setfield(L, -2, "TS");

  // FPS
  lua_pushinteger(L, f.currentFramesPerSecond());
  lua_setfield(L, -2, "FPS");

  // count
  lua_pushinteger(L, hands.count());
  lua_setfield(L, -2, "handCount");
  
  if (!hands.isEmpty()) {
    processHands(L, hands, f.interactionBox());
  }

  return 1;
}

int leap_ctrl__new(lua_State *L)
{
  *static_cast<Leap::Controller**>(lua_newuserdata(L, sizeof(Leap::Controller))) = new Leap::Controller();
  
  // if no MT is defined then add the methods
  if (luaL_newmetatable(L, LEAP_MT_CONTROLLER))
    { 
      static const luaL_Reg methods[] =
        {
         {"__tostring", leap_ctrl__tostring},
         {"__gc", leap_ctrl__gc},
         {"isConnected", leap_ctrl_is_connected},
         {"isGestureEnabled", leap_ctrl_is_gesture_enabled},
         {"isServiceConnected", leap_ctrl_is_service_connected},
         {"enableGesture", leap_ctrl_enable_gesture},
         {"frame", leap_ctrl_frame},
         {NULL, NULL}
        };

      luaL_setfuncs(L, methods, 0);
      lua_pushvalue(L, -1);
      lua_setfield(L, -2, "__index");
    }
  lua_setmetatable(L, -2);

  return 1;
}
