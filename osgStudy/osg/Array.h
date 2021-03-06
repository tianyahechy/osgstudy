//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_ARRAY
#define OSG_ARRAY 1

#include <osg/Object.h>
#include <osg/GL.h>
#include <osg/Vec2.h>
#include <osg/Vec3.h>
#include <osg/Vec4.h>
#include <osg/UByte4.h>

#include <vector>

namespace osg {

class ArrayVisitor;

class SG_EXPORT Array : public Object
{

    public:
    
        enum Type
        {
            ArrayType = 0,
            ByteArrayType     = 1,
            ShortArrayType    = 2,
            IntArrayType      = 3,
            UByteArrayType    = 4,
            UShortArrayType   = 5,
            UIntArrayType     = 6,
            UByte4ArrayType   = 7,
            FloatArrayType    = 8,
            Vec2ArrayType     = 9,
            Vec3ArrayType     = 10,
            Vec4ArrayType     = 11
        };

        Array(Type arrayType=ArrayType,GLint dataSize=0,GLenum dataType=0):
            _arrayType(arrayType),
            _dataSize(dataSize),
            _dataType(dataType) {}
    
        Array(const Array& array,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            Object(array,copyop),
            _arrayType(array._arrayType),
            _dataSize(array._dataSize),
            _dataType(array._dataType) {}

        virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const Array*>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const;
        
        virtual void accept(ArrayVisitor&) {}


        Type                    getType() const { return _arrayType; }
        GLint                   getDataSize() const { return _dataSize; }
        GLenum                  getDataType() const { return _dataType; }
        virtual const GLvoid*   getDataPointer() const = 0;
        virtual unsigned int    getNumElements() const = 0;

    protected:
    
        virtual ~Array() {}

        Type        _arrayType;
        GLint       _dataSize;
        GLenum      _dataType;
};



template<typename T, Array::Type ARRAYTYPE, int DataSize, int DataType>
class TemplateArray : public Array, public std::vector<T>
{
    public:
    
        TemplateArray() : Array(ARRAYTYPE,DataSize,DataType) {}

        TemplateArray(const TemplateArray& ta,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            Array(ta,copyop),
            std::vector<T>(ta) {}
        
        TemplateArray(unsigned int no) : 
            Array(ARRAYTYPE,DataSize,DataType),
            std::vector<T>(no) {}

        TemplateArray(unsigned int no,T* ptr) : 
            Array(ARRAYTYPE,DataSize,DataType),
            std::vector<T>(ptr,ptr+no) {}

        template <class InputIterator>
        TemplateArray(InputIterator first,InputIterator last) : 
            Array(ARRAYTYPE,DataSize,DataType),
            std::vector<T>(first,last) {}        

        virtual Object* cloneType() const { return osgNew TemplateArray(); }
        virtual Object* clone(const CopyOp& copyop) const { return osgNew TemplateArray(*this,copyop); }        
        virtual void accept(ArrayVisitor& av) { av.apply(*this); }

        virtual const GLvoid*   getDataPointer() const { if (!empty()) return &front(); else return 0; }
        virtual unsigned int    getNumElements() const { return size(); }

    protected:
    
        virtual ~TemplateArray() {}
};

typedef TemplateArray<GLbyte,Array::ByteArrayType,1,GL_BYTE>                    ByteArray;
typedef TemplateArray<GLshort,Array::ShortArrayType,1,GL_SHORT>                 ShortArray;
typedef TemplateArray<GLint,Array::IntArrayType,1,GL_INT>                       IntArray;
typedef TemplateArray<GLubyte,Array::UByteArrayType,1,GL_UNSIGNED_BYTE>         UByteArray;
typedef TemplateArray<GLushort,Array::UShortArrayType,1,GL_UNSIGNED_SHORT>      UShortArray;
typedef TemplateArray<GLuint,Array::UIntArrayType,1,GL_UNSIGNED_INT>            UIntArray;
typedef TemplateArray<UByte4,Array::UByte4ArrayType,4,GL_UNSIGNED_BYTE>         UByte4Array;
typedef TemplateArray<float,Array::FloatArrayType,1,GL_FLOAT>                   FloatArray;
typedef TemplateArray<Vec2,Array::Vec2ArrayType,2,GL_FLOAT>                     Vec2Array;
typedef TemplateArray<Vec3,Array::Vec3ArrayType,3,GL_FLOAT>                     Vec3Array;
typedef TemplateArray<Vec4,Array::Vec4ArrayType,4,GL_FLOAT>                     Vec4Array;

class ArrayVisitor
{
    public:
        ArrayVisitor() {}
        
        virtual void apply(Array&) {}
        virtual void apply(ByteArray&) {}
        virtual void apply(ShortArray&) {}
        virtual void apply(IntArray&) {}
        virtual void apply(UByteArray&) {}
        virtual void apply(UShortArray&) {}
        virtual void apply(UIntArray&) {}
        virtual void apply(UByte4Array&) {}
        virtual void apply(FloatArray&) {}
        virtual void apply(Vec2Array&) {}
        virtual void apply(Vec3Array&) {}
        virtual void apply(Vec4Array&) {}
    
};

}

#endif
