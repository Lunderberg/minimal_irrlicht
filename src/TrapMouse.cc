#include "TrapMouse.hh"

#include <irrlicht.h>

void TrapMouse(irr::IrrlichtDevice* device){
  auto lower_right = device->getVideoDriver()->getViewPort().LowerRightCorner;
  int maxX = lower_right.X;
  int maxY = lower_right.Y;

  // Catching mouse events on linux fails when the mouse is outside the window.
  // This can cause the mouse to escape when moving quickly.
  auto cursor_pos = device->getCursorControl()->getRelativePosition();
  int x = cursor_pos.X * maxX;
  int y = cursor_pos.Y * maxY;

  bool changed = false;
  if(x < 1){
    x = 1;
    changed = true;
  }
  if(x >= maxX){
    x = maxX-2;
    changed = true;
  }
  if(y < 1){
    y = 1;
    changed = true;
  }
  if(y >= maxY){
    y = maxY-2;
    changed = true;
  }

  if(changed){
    device->getCursorControl()->setPosition(x,y);
  }
}
