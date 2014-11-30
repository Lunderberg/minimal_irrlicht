#include <cstdlib>
#include <iostream>
#include <sstream>

#include <irrlicht.h>
#include "driverChoice.h"

#include "EventReceiver.hh"
#include "ProceduralTexture.hh"
#include "TrapMouse.hh"
#include "PanningCamera.hh"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
  EventReceiver receiver;
  IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640,480), 16,
        		     false, true, false, &receiver);
  if (!device){
    return 1;
  }

  device->setWindowCaption(L"Hello World! - Rewriting test");

  auto driver = device->getVideoDriver();
  auto smgr = device->getSceneManager();
  auto guienv = device->getGUIEnvironment();

  auto text = guienv->addStaticText(L"",
                                    rect<s32>(10,10,260,22), true);

  // Set the ambient light
  //smgr->setAmbientLight({0.1,0.1,0.1});

  PanningCamera camera(device);
  camera.setPosition({0,0,10});
  camera.setTarget({0,0,0});

  // Draw an array of spheres
  scene::IMeshSceneNode* sphere;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      for(int k=0; k<5; k++){
        sphere = smgr->addSphereSceneNode(0.5);
        if(sphere){
          driver->getMeshManipulator()->flipSurfaces(sphere->getMesh());
          sphere->setPosition(core::vector3df(i-2,j-2,k-2));
          sphere->setMaterialTexture(0, create_solid_texture(driver, 63*i+1, 63*j+1, 63*k+1));
          sphere->addShadowVolumeSceneNode();
        }
      }
    }
  }

  // Add a light source
  scene::ILightSceneNode* light = smgr->addLightSceneNode(0, {25,25,50}, {1,1,1}, 100);

  u32 prev_time = device->getTimer()->getTime();
  float movement_speed = 5.0;
  float light_movement_speed = 25.0;
  float camera_movement_speed = 5.0;

  while(device->run()){
    // Find dT
    auto now = device->getTimer()->getTime();
    double dT = (now - prev_time) / 1000.0;
    prev_time = now;

    if(!device->isWindowActive()){
      device->yield();
      continue;
    }

    camera.Apply(camera_movement_speed * dT);

    // Adjust based on the controls
    core::vector3df sphere_pos = sphere->getPosition();
    if(receiver.IsKeyDown(irr::KEY_KEY_W))
      sphere_pos.Y += movement_speed * dT;
    if(receiver.IsKeyDown(irr::KEY_KEY_S))
      sphere_pos.Y -= movement_speed * dT;
    if(receiver.IsKeyDown(irr::KEY_KEY_A))
      sphere_pos.X -= movement_speed * dT;
    if(receiver.IsKeyDown(irr::KEY_KEY_D))
      sphere_pos.X += movement_speed * dT;
    sphere->setPosition(sphere_pos);

    // Move the light
    core::vector3df light_pos = light->getPosition();
    if(receiver.IsKeyDown(irr::KEY_KEY_I))
      light_pos.Z -= light_movement_speed * dT;
    if(receiver.IsKeyDown(irr::KEY_KEY_K))
      light_pos.Z += light_movement_speed * dT;
    if(receiver.IsKeyDown(irr::KEY_KEY_J))
      light_pos.X -= light_movement_speed * dT;
    if(receiver.IsKeyDown(irr::KEY_KEY_L))
      light_pos.X += light_movement_speed * dT;
    light->setPosition(light_pos);


    // Adjust the FPS counter
    std::wstringstream ss;
    ss << "FPS: " << driver->getFPS()
       << " Mouse: (" << receiver.mouse().x << "," << receiver.mouse().y << ")"
       << " Mouse: (" << device->getCursorControl()->getRelativePosition().X << ","
       << device->getCursorControl()->getRelativePosition().Y << ")";
    auto wstring = ss.str();
    text->setText(wstring.c_str());

    // Draw everything
    driver->beginScene(true, true, SColor(255,100,101,140));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
  }

  device->drop();
  return 0;
}
