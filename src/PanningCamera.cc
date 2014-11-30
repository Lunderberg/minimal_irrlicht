#include "PanningCamera.hh"

#include <iostream>
#include <stdexcept>

#include "TrapMouse.hh"

PanningCamera::PanningCamera(irr::IrrlichtDevice* p_device)
  : device(p_device), dir_right({1,0,0}), dir_up({0,-1,0}) {
  camera = device->getSceneManager()->addCameraSceneNode();

  if(!camera){
    throw std::runtime_error("Could not make camera");
  }
  // Grab a reference to the device so that the camera will be removed first.
  device->grab();

  InitCameraPerspective();
}

PanningCamera::~PanningCamera(){
  camera->remove();
  device->drop();
}

void PanningCamera::InitCameraOrtho(){
  irr::core::matrix4 matproj;

  matproj.buildProjectionMatrixOrthoRH(15,15,0,200);
  // Because the z has the negative sign, when the x should.
  matproj(2,2) *= -1;
  matproj(0,0) *= -1;

  camera->setProjectionMatrix(matproj,true);
  camera->setPosition({0,0,10});
  camera->setTarget({0,0,0});
}

void PanningCamera::InitCameraPerspective(){
  camera->setPosition({10,10,10});
  camera->setTarget({0,0,0});
  camera->setAspectRatio(4.0/3.0);
  camera->setFOV(1.0);

  irr::core::matrix4 matproj = camera->getProjectionMatrix();
  matproj(0,0) *= -1;
  camera->setProjectionMatrix(matproj);
}

void PanningCamera::Apply(double camera_movement){
  TrapMouse(device);
  auto lower_right = device->getVideoDriver()->getViewPort().LowerRightCorner;
  int maxX = lower_right.X;
  int maxY = lower_right.Y;

  auto cursor_pos = device->getCursorControl()->getRelativePosition();
  int x = cursor_pos.X * maxX;
  int y = cursor_pos.Y * maxY;

  if(x<=1 || x>=maxX-2 || y<=1 || y>=maxY-2){
    irr::core::vector2df disp_screen(x - maxX/2, y - maxY/2);
    disp_screen.normalize();

    irr::core::vector3df disp = disp_screen.X * dir_right + disp_screen.Y * dir_up;
    disp *= camera_movement;

    camera->setPosition(disp + camera->getPosition());
    camera->setTarget(disp + camera->getTarget());
  }
}
