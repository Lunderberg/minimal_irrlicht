#ifndef _PROCEDURALTEXTURE_H_
#define _PROCEDURALTEXTURE_H_

namespace irr{
  namespace video{
    class ITexture;
    class IVideoDriver;
  }
}

irr::video::ITexture* create_solid_texture(irr::video::IVideoDriver* driver,
                                           unsigned char r, unsigned char g,
                                           unsigned char b, unsigned char t=0);

#endif /* _PROCEDURALTEXTURE_H_ */
