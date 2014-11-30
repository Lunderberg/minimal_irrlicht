#ifndef _PANNINGCAMERA_H_
#define _PANNINGCAMERA_H_

#include <irrlicht.h>

class PanningCamera{
public:
  PanningCamera(irr::IrrlichtDevice* p_device);
  virtual ~PanningCamera();

  void Apply(double camera_movement);

  // Change the current position and target of the camera.
  irr::core::vector3df getPosition(){return camera->getPosition();}
  void setPosition(irr::core::vector3df pos){ camera->setPosition(pos); }
  irr::core::vector3df getTarget(){return camera->getTarget();}
  void setTarget(irr::core::vector3df target){ camera->setTarget(target); }

  // Change the direction that the camera pans when the mouse is at the edge.
  irr::core::vector3df getDirectionRight(){return dir_right;}
  void setDirectionRight(irr::core::vector3df dir){dir_right = dir; }
  irr::core::vector3df getDirectionUp(){return dir_up;}
  void setDirectionUp(irr::core::vector3df dir){dir_up = dir; }


private:
  void InitCameraOrtho();
  void InitCameraPerspective();

  irr::IrrlichtDevice* device;
  irr::scene::ICameraSceneNode* camera;
  irr::core::vector3df dir_right; //! The direction to pan when the mouse is at the right.
  irr::core::vector3df dir_up; //! The direction to pan when the mouse is at the top.
};

#endif /* _PANNINGCAMERA_H_ */
