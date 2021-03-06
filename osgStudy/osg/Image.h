//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

// -*-c++-*-

#ifndef OSG_IMAGE
#define OSG_IMAGE 1

#include <osg/Object.h>
#include <osg/GL.h>

#include <string>
#include <vector>

namespace osg {

/** Image class for encapsulating the storage texture image data.*/
class SG_EXPORT Image : public Object
{

    public :

        Image();
        
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Image(const Image& image,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        virtual Object* cloneType() const { return osgNew Image(); }
        virtual Object* clone(const CopyOp& copyop) const { return osgNew Image(*this,copyop); }
        virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const Image*>(obj)!=0; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Image"; }


        void setFileName(const std::string& fileName);
        inline const std::string& getFileName() const { return _fileName; }
        
        
        /* allocated a pixel block of specified size and type.*/
        void createImage(int s,int t,int r,
                         GLenum format,GLenum type,
                         int packing=1);
        
        
        /** set the image data and format.
          * note, when the packing value is negative (the default is -1) this method assumes
          * a _packing width of 1 if the width is not a multiple of 4,
          * otherwise automatically sets to _packing to 4. If a positive
          * value of packing is supplied than _packing is simply set to that value.
          */
        void setImage(int s,int t,int r,
                      GLint internalTextureformat,
                      GLenum format,GLenum type,
                      unsigned char *data,
                      int packing=1);
            
        /** readPixels from screen at specified position and size, using glReadPixels.
          * Create memory for storage if required, reuse existing pixel coords if possible.
          * if pixelFormat or dataType*/
        void readPixels(int x,int y,int width,int height,
                        GLenum format,GLenum type);
            

        /** Scale image to specified size. */
        void scaleImage(const int s,const int t,const int r);



        /** Width of image.*/
        inline const int s() const { return _s; }

        /** Height of image.*/
        inline const int t() const { return _t; }
        
        /** Depth of image.*/
        inline const int r() const { return _r; }
        
        void setInternalTextureFormat(GLint internalFormat);
        inline const GLint getInternalTextureFormat() const { return _internalTextureFormat; }
        
        void setPixelFormat(const GLenum format);
        inline const GLenum getPixelFormat() const { return _pixelFormat; }
        
        inline const GLenum getDataType() const { return _dataType; }        
        
        inline const unsigned int getPacking() const { return _packing; }
        
        /** return the numbers of bits required for each pixel.*/        
        inline const unsigned int getPixelSizeInBits() const { return computePixelSizeInBits(_pixelFormat,_dataType); }

        /** return the numbers of bytes each row of pixels occupies once it has been packed.*/        
        inline const unsigned int getRowSizeInBytes() const { return computeRowWidthInBytes(_s,_pixelFormat,_dataType,_packing); }

        /** return the numbers of bytes each image (_s*_t) of pixels occupies..*/
        inline const unsigned int getImageSizeInBytes() const { return getRowSizeInBytes()*_t; }
        
        /** return the numbers of bytes the whole row/image/volume of pixels occupies.*/        
        inline const unsigned int getTotalSizeInBytes() const { return getImageSizeInBytes()*_r; }

        /** raw image data.*/
        inline unsigned char *data() { return _data; }
        
        /** raw const image data.*/
        inline const unsigned char *data() const { return _data; }


        unsigned char* data(int column, int row=0,int image=0)
        {
            if (!_data) return NULL;
            return _data+(column*getPixelSizeInBits())/8+row*getRowSizeInBytes()+image*getImageSizeInBytes();
        }
        
        /** Flip the image horizontally.*/
        void flipHorizontal(int image=0);
        
        /** Flip the image vertically.*/
        void flipVertical(int image=0);


        /** Ensure image dimensions are a power of two.
          * Mip Mapped texture require the image dimensions to be
          * power of two and are within the maxiumum texture size for
          * the host machine.*/
        void ensureValidSizeForTexturing();
      
        /** Dirty the image, which increments the modified flag, to force osg::Texture to reload the image.*/
        inline void dirty() { ++_modifiedTag; }      
      
        /** Set the modified tag value, only used by osg::Texture when using texture subloading. */
        inline void setModifiedTag(const unsigned int value) { _modifiedTag=value; }

        /** Get modified tag value, only used by osg::Texture when using texture subloading. */
        inline const unsigned int getModifiedTag() const { return _modifiedTag; }


        static const bool isPackedType(GLenum type);
        static const unsigned int computeNumComponents(GLenum format);
        static const unsigned int computePixelSizeInBits(GLenum format,GLenum type);
        static const unsigned int computeRowWidthInBytes(int width,GLenum format,GLenum type,int packing);
        
        // precomputed mipmaps stuff;
        typedef std::vector< unsigned int > MipmapDataType;

        inline bool isMipmap() const {return !_mipmapData.empty();};

        unsigned int getNumMipmaps() const
        {
            return _mipmapData.size()+1;
        };

        // send offsets into data 
        // It is assumed that first mipmap offset (index 0) is 0
        inline void setMipmapData(const MipmapDataType& mipmapDataVector)
        {
            _mipmapData = mipmapDataVector;
        };
        
        inline unsigned char* getMipmapData(unsigned int mipmapNumber) const
        {
            if(mipmapNumber == 0)
                return _data;
            else if(mipmapNumber < getNumMipmaps())
               return _data + _mipmapData[mipmapNumber-1];
            return 0L;
        };

    protected :

        virtual ~Image();

        Image& operator = (const Image&) { return *this; }

        std::string _fileName;
        int _s, _t, _r;
        GLint _internalTextureFormat;
        GLenum _pixelFormat;
        GLenum _dataType;
        unsigned int _packing;
        unsigned char *_data;

        unsigned int _modifiedTag;

        MipmapDataType _mipmapData;
};

class Geode;

/** Convenience function to be used by images loaders to generate a valid geode
 * to return for readNode().  
 * Use the images s and t values scale the dimensions of the image.
 */
SG_EXPORT extern Geode* createGeodeForImage(Image* image);
/** Convenience function to be used by images loaders to generate a valid geode
 * to return for readNode().  
 * Use the specified s and t values scale the dimensions of the image.
 */
SG_EXPORT extern Geode* createGeodeForImage(Image* image,const float s,const float t);

}

#endif                                            // __SG_IMAGE_H
