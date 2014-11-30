#include "ProceduralTexture.hh"

#include <sstream>

#include <irrlicht.h>

irr::video::ITexture* create_solid_texture(irr::video::IVideoDriver* driver,
                                           unsigned char r, unsigned char g,
                                           unsigned char b, unsigned char t){
  unsigned char buf[4] = {b,g,r,t};

  irr::video::IImage* image = driver->createImageFromData(irr::video::ECF_A8R8G8B8,
                                                          {1,1},
                                                          buf);
  std::stringstream ss;
  ss << r << " " << g << " " << b << " " << t;
  std::string name = ss.str();
  irr::video::ITexture* texture = driver->addTexture(name.c_str(), image);
  image->drop();
  if(texture){
    texture->grab();
    return texture;
  } else {
    return NULL;
  }
}
