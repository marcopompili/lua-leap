#include "leap-parser.hpp"

static void processVector(lua_State *L, Leap::Vector v)
{
  lua_createtable(L, 0, 6);

  lua_pushnumber(L, v.x);
  lua_setfield(L, -2, "x");

  lua_pushnumber(L, v.y);
  lua_setfield(L, -2, "y");

  lua_pushnumber(L, v.z);
  lua_setfield(L, -2, "z");

  lua_pushnumber(L, v.pitch());
  lua_setfield(L, -2, "pitch");

  lua_pushnumber(L, v.yaw());
  lua_setfield(L, -2, "yaw");

  lua_pushnumber(L, v.roll());
  lua_setfield(L, -2, "roll");

  lua_settable(L, -3);
}

static void normalizedVector(lua_State *L, Leap::Vector v, Leap::InteractionBox ibox)
{
  Leap::Vector normalized = ibox.normalizePoint(v, false);

  lua_createtable(L, 0, 3);

  lua_pushnumber(L, normalized.x);
  lua_setfield(L, -2, "x");

  lua_pushnumber(L, normalized.y);
  lua_setfield(L, -2, "y");

  lua_pushnumber(L, normalized.z);
  lua_setfield(L, -2, "z");

  lua_settable(L, -3);
}

// static void processFinger(lua_State *L, Leap::Finger finger)
// {
  
// }

// static void processFingers(lua_State *L, Leap::FingerList fingers)
// {
  
// }

// static void processGestures(lua_State *L, Leap::Hand hand)
// {

// }

static void processHand(lua_State *L, Leap::Hand hand, Leap::InteractionBox ibox)
{
  // hand subtable
  lua_createtable(L, 0, 11);

  lua_pushnumber(L, hand.confidence());
  lua_setfield(L, -2, "confidence");

  lua_pushnumber(L, hand.grabStrength());
  lua_setfield(L, -2, "grabStrength");

  lua_pushinteger(L, hand.id());
  lua_setfield(L, -2, "id");

  lua_pushboolean(L, hand.isValid());
  lua_setfield(L, -2, "isValid");

  lua_pushboolean(L, hand.isLeft());
  lua_setfield(L, -2, "isLeft");
  
  lua_pushboolean(L, hand.isRight());
  lua_setfield(L, -2, "isRight");

  lua_pushstring(L, hand.toString().c_str());
  lua_setfield(L, -2, "tostring");

  // Direction vector
  lua_pushliteral(L, "direction");
  processVector(L, hand.direction());

  // Normal vector
  lua_pushliteral(L, "palmNormal");
  processVector(L, hand.palmNormal());

  // Position vector
  lua_pushliteral(L, "palmPosition");
  processVector(L, hand.palmPosition());

  // Normalized position vector
  lua_pushliteral(L, "normalizedPalmPosition");
  normalizedVector(L, hand.palmPosition(), ibox);

  // Velocity vector
  lua_pushliteral(L, "palmVelocity");
  processVector(L, hand.palmVelocity());

  lua_pushnumber(L, hand.palmWidth());
  lua_setfield(L, -2, "palmWidth");

  lua_pushnumber(L, hand.pinchStrength());
  lua_setfield(L, -2, "pinchStrength");

  lua_pushliteral(L, "sphereCenter");
  processVector(L, hand.sphereCenter());

  lua_pushnumber(L, hand.sphereRadius());
  lua_setfield(L, -2, "sphereRadius");

  lua_pushnumber(L, hand.timeVisible());
  lua_setfield(L, -2, "timeVisible");

  lua_pushliteral(L, "wirstPosition");
  processVector(L, hand.wristPosition());

  // hand set subtable
  lua_settable(L, -3);
}

void processHands(lua_State *L, Leap::HandList hands, Leap::InteractionBox ibox)
{
  // table with frontmost, leftmost, rightmost
  lua_pushliteral(L, "hands");
  lua_createtable(L, 0, 3);

  lua_pushliteral(L, "frontmost");
  processHand(L, hands.frontmost(), ibox);
 
  lua_pushliteral(L, "leftmost");
  processHand(L, hands.leftmost(), ibox);
 
  lua_pushliteral(L, "rightmost");
  processHand(L, hands.rightmost(), ibox);

  // add hands to "hands" table
  lua_settable(L, -3); 
}
