#ifndef _EVENTRECEIVER_H_
#define _EVENTRECEIVER_H_

#include <irrlicht.h>

struct SMouse{
  SMouse() : x(0), y(0) {}
  int x,y;
};

class EventReceiver : public irr::IEventReceiver{
public:
  EventReceiver(){
    for(irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; i++){
      KeyIsDown[i] = false;
    }
  }

  virtual bool OnEvent(const irr::SEvent& event){
    if(event.EventType == irr::EET_KEY_INPUT_EVENT){
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    } else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
      switch(event.MouseInput.Event){

      case irr::EMIE_MOUSE_MOVED:
        MouseInfo.x = event.MouseInput.X;
        MouseInfo.y = event.MouseInput.Y;
        break;

      default:
        break;
      }
    }
    return false;
  }

  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
  }

  const SMouse& mouse(){
    return MouseInfo;
  }

private:
  bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  SMouse MouseInfo;
};

#endif /* _EVENTRECEIVER_H_ */
