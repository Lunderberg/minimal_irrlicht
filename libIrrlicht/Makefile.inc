# $(LIBRARY): ALL_CPPFLAGS += -DIRRLICHT_EXPORTS=1
# $(LIBRARY): ALL_CPPFLAGS += -DPNG_THREAD_UNSAFE_OK -DPNG_NO_MMX_CODE -DPNG_NO_MNG_FEATURES
ALL_CPPFLAGS += -DIRRLICHT_EXPORTS=1
ALL_CPPFLAGS += -DPNG_THREAD_UNSAFE_OK -DPNG_NO_MMX_CODE -DPNG_NO_MNG_FEATURES

LIBRARY_INC_DIRS = include source/Irrlicht/zlib source/Irrlicht/jpeglib source/Irrlicht/libpng
LIBRARY_SRC_DIRS = source/Irrlicht source/Irrlicht/lzma source/Irrlicht/zlib source/Irrlicht/jpeglib source/Irrlicht/libpng source/Irrlicht/aesGladman source/Irrlicht/bzip2

ifeq ($(LINK_AGAINST_STATIC),1)
  ifeq ($(SYSTEM),linux)
    ALL_LDLIBS += -lGL -lXxf86vm -lXext -lX11 -lXcursor
  endif

  ifeq ($(SYSTEM),windows)
    ALL_LDLIBS = -lgdi32 -lopengl32 -ld3dx9_43 -lwinmm
  endif
else
  ifeq ($(SYSTEM),Linux)
    $(LIBRARY): SHARED_LDLIBS = -lGL -lXxf86vm -lXext -lX11 -lXcursor
  endif

  ifeq ($(SYSTEM),windows)
    $(LIBRARY): SHARED_LDLIBS = -lgdi32 -lopengl32 -ld3dx9_43 -lwinmm
  endif
endif
