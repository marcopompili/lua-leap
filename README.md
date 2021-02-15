lua-leap
========

Lua bindings for the [Leap Motion Controller](https://developer.leapmotion.com/documentation/) (version 2.3.1 on GNU/Linux) for lua 5.2 and later.

# Installation

## Build with luarocks

To build the library using the rockspec file do this:

```
luarocks
```

## Build locally

This package comes with autotools, to build it locally simply do this:

```
./configure && make
```

## Use Luarocks (not yet ready)

This package it's not published on luarocks yet for now you have to build it locally.


# Examples

## Basic example

```
local leap = require('leap')

local c = leap.Controller()
print(c)

local lastFrameID = -1

local on = true

print("Press Enter to quit...")

while on
do
   local f = c:frame()
   if lastFrameID ~= f.ID then
      lastFrameID = f.ID
      print("ID " .. f.ID, f.FPS .. " FPS")

      if f.hands then
         print("leftmost.palmPosition.x", f.hands.leftmost.palmPosition.x)
      end
   end
end
```

First include the library and then create a `leap.Controller`, then poll the controller for receiving frames
by calling `c:frame()` to be sure that a new frame is polled control for the frame ID, like in the example above.

## Example with Awesome-wm

```
local gears = require("gears")
local leap = require("leap")

local controller = leap.Controller()
local lastFrameID = -1

local leapPoller = gears.timer
{
    timeout = 0.0085, -- 115 FPS
    autostart = true, -- default is false
    callback = function ()
        local frame = controller.frame()

        if lastFrameID ~= frame.ID then
            lastFrameID = frame.ID

            print("ID " .. frame.ID, frame.FPS .. " FPS")
        end
    end
}
```

An example on how to use lua-leap with Awesome-wm, in this case `gears` allows to poll the controller 115 times each seconds which is the highest FPS the controller can get. In the example above we're just logging
the `ID` of the frame and the `FPS` on the device for testing.

# Notes

The actual implementation generates a lua table with the data extracted from the frame, the data structure is similare of the Websocket version without having the overhead of using websockets.

## Table structure

This is the message structure for a `Frame` in lua:

```
{
    ID,
    TS,
    FPS,
    handCount,
    hands = {
        frontmost = {
            confidence,
            id,
            isValid,
            isLeft,
            isRight,
            tosting,
            direction = {
                x,
                y,
                z,
                pitch,
                yaw,
                roll
            },
            palmNormal = { ... },
            palmPosition = { ... },
            palmVelocity = { ... },
            sphereRadius
        },
        leftmost = { ... },
        rightmost = { ... }
    }
}
```

# Versions
- Working on 0.1.0
