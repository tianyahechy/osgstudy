#pragma once

#include "GL.h"
#include "Types.h"
#include "Image.h"
#include "StateAttribute.h"
#include "ref_ptr.h"
#include "Vec4.h"
#include <vector>
#include <map>
#include <set>

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif

#ifndef GL_ARB_texture_compression
#define GL_COMPRESSED_ALPHA_ARB					0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB				0x84EA
#define GL_COMPRESSED_LUMINANCE_ALHPA_ARB		0x84EB
#define GL_COMPRESSED_INTENSITY_ARB				0x84EC
#define GL_COMPRESSED_RGB_ARB					0x84ED
#define GL_COMPRESSED_RGBA_ARB					0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB			0x84EF
#define GL_TEXTURE_IMAGE_SIZE_ARB				0x86A0
#define GL_TEXTURE_COMPRESSED_ARB				0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB	0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB		0x86A3
#endif

#ifndef GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT			0x83F0
#define GL_COMPRESSED_RGB_S3TCA_DXT1_EXT		0x83F1
#define GL_COMPRESSED_RGB_S3TCA_DXT1_EXT		0x83F2
#define GL_COMPRESSED_RGB_S3TCA_DXT1_EXT		0x83F3
#endif // !1

#ifndef GL_MIRRORED_REPEAT_IBM
#define GL_MIRRORED_REPEAT_IBM					0x8370
#endif // !GL_MIRRORED_REPEAT_IBM

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE						0x812F
#endif // !GL_CLAMP_TO_EDGE

#ifndef GL_CLAMP_TO_BORDER_ARB
#define GL_CLAMP_TO_BORDER_ARB					0x812F
#endif // !GL_CLAMP_TO_BORDER_ARB

#ifndef GL_GENERATE_MIPMAP_SGIS
#define GL_GENERATE_MIPMAP_SGIS					0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS			0x8191
#endif // !GL_GENERATE_MIPMAP_SGIS

#ifndef GL_TEXTURE_3D
#define GL_TEXTURE_3D							0x806F
#endif // !GL_TEXTURE_3D

namespace osg
{
	class SG_EXPORT Texture : public StateAttribute
	{
	public:
		enum WrapParameter
		{
			WRAP_S,
			WRAP_T,
			WRAP_R
		};
		enum WrapMode
		{
			CLAMP = GL_CLAMP,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER_ARB,
			REPEAT = GL_REPEAT,
			MIRROR = GL_MIRRORED_REPEAT_IBM
		};
		enum FilterParameter
		{
			MIN_FILTER,
			MAG_FILTER
		};
		enum FilterMode
		{
			LINEAR = GL_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
			LINEAR_MIP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST = GL_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			ANISOTROPIC = GL_TEXTURE_MAX_ANISOTROPY_EXT
		};

		enum InternalFormatMode
		{
			USE_IMAGE_DATA_FORMAT,
			USE_USER_DEFINED_FORMAT,
			USE_ARB_COMPRESSION,
			USE_S3TC_DXT1_COMPRESSION,
			USE_S3TC_DXT3_COMPRESSION,
			USE_S3TC_DXT5_COMPRESSION
		};

		enum SubloadMode
		{
			OFF,
			AUTO,
			IF_DIRTY
		};

	protected:
		typedef std::vector<GLuint> TextureNameList;
		mutable TextureNameList _handleList;

		typedef std::vector<uint> ImageModifiedTag;
		mutable ImageModifiedTag _modifiedTag;

		mutable ref_ptr<Image> _image;
		GLenum _target;
		WrapMode _wrap_s;
		WrapMode _wrap_t;
		WrapMode _wrap_r;

		FilterMode _min_filter;
		FilterMode _mag_filter;
		
		mutable bool _texParametersDirty;
		InternalFormatMode _internalFormatMode;
		int _internalFormatValue;

		Vec4 _borderColor;

		mutable GLsizei _textureWidth, _textureHeight;
		SubloadMode _subloadMode;
		GLint _subLoadOffsX, _subloadOffsY;
		GLsizei _subloadWidth, _subloadHeight;
		typedef std::map<uint, std::set<uint>> DeleteTextureObjectCache;
		static DeleteTextureObjectCache s_deletedTextureObjectCache;

	public:
		Texture();
		Texture(const Texture& text, const CopyOp& copyop = CopyOp::SHALLOW_COPY) :
			StateAttribute(text, copyop)
		{
			_handleList.clear();
			_modifiedTag.clear();
			_image = copyop(text._image.get());
			_target = text._target;
			_wrap_s = text._wrap_s;
			_wrap_t = text._wrap_t;
			_wrap_r = text._wrap_r;
			_min_filter = text._min_filter;
			_mag_filter = text._mag_filter;
			_texParametersDirty = false;
			_internalFormatMode = text._internalFormatMode;
			_internalFormatValue = text._internalFormatValue;
			_borderColor = text._borderColor;
			_textureWidth = text._textureWidth;
			_textureHeight = text._textureHeight;
			_subloadMode = text._subloadMode;
			_subLoadOffsX = text._subLoadOffsX;
			_subLoadOffsY = text._subLoadOffsY;
			_subloadWidth = text._subloadWidth;
			_subloadHeight = text._subloadHeight;

		}

		META_StateAttribute(osg, Texture, TEXTURE);

		virtual bool isTextureAttribute() const { return true; }
		virtual int compare(const StateAttribute& sa) const;  
		virtual void getAssociatedModes(std::vector<GLMode>& modes) const
		{
			modes.push_back(_target);
		}
		void setImage(Image* img);
		Image* getImage() { return _image.get(); }
		const Image* getImage() const { return _image.get(); }
		void copyTexImage2D(State& state, int x, int y, int width, int height);
		void copyTexSubImage2D(State& state, int xOffset, int yOffset, int x, int y, int width, int height);
		void setWrap(const WrapParameter which, const WrapMode wrap);
		const WrapMode getWrap(const WrapParameter which) const;

		void setBorderColor(const Vec4& color) { _borderColor = color; _texParametersDirty = true; }
		const Vec4& borderColor() const { return _borderColor; }

		void setFilter(const FilterParameter which, const FilterMode filter);
		const FilterMode getFilter(const FilterParameter which) const;

		inline void setInternalFormatmode(const InternalFormatMode mode) { _internalFormatMode = mode; };
		inline const InternalFormatMode getInternalFormatmode() const { return _internalFormatMode; }

		inline void setInternalFormatValue(const int internalFormat)
		{
			_internalFormatMode = USE_USER_DEFINED_FORMAT;
			_internalFormatValue = internalFormat;
		}

		inline const int getInternalFormatValue() const { return _internalFormatValue; }

		inline const uint getTextureObject(const uint contextID) const
		{
			if (contextID < _handleList.size())
			{
				return _handleList[contextID];
			}
			return 0;
		}
		inline void setSubloadMode(const SubloadMode mode) { _subloadMode = mode; }
		inline const SubloadMode getSubLoadMode() const { return _subloadMode; }
		inline void setSubloadOffset(const int x, const int y)
		{
			_subloadOffsX = x;
			_subloadOffsY = y;
		}

		inline void getSubloadOffset(int& x, int& y) const
		{
			x = _subloadOffsX;
			y = _subloadOffsY;
		}
		inline void setSubloadSize(const int width, const int height)
		{
			_subloadWidth = width;
			_subloadHeight = height;
		}
		inline void getSubloadSize(int& width, int& height) const
		{
			width = _subloadWidth;
			height = _subloadHeight;
		}
		inline GLuint& getHandle(const uint contextID) const
		{
			if (_handleList.size() <= contextID)
			{
				_handleList.resize(contextID + 1, 0);
			}
			return _handleList[contextID];
		}
		inline uint& getModifiedTage(const uint contextID) const
		{
			if (_modifiedTag.size() <= contextID)
			{
				_modifiedTag.resize(contextID + 1, 0);

			}
			return _modifiedTag[contextID];
		}
		void dirtyTextureObject();
		virtual void apply(State& state) const;
		virtual void compile(State& state) const;
		static void deleteTextureObject(uint contextID, GLuint handle);
		static void flushDeletedTextureObject(uint contextID);

	protected:
		virtual ~Texture();
		void applyTexParameters(GLenum target, State& state) const;
		virtual void applyTexImage(GLenum target, Image* image, State& state) const;

	};
}


