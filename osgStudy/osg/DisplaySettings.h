//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_DisplaySettings
#define OSG_DisplaySettings 1

#include <osg/Referenced.h>

#include <string>
#include <vector>

namespace osg {

/** DisplaySettings class for encapsulating what visuals are required and
  * have been set up, and the status of stereo viewing.*/
class SG_EXPORT DisplaySettings : public osg::Referenced
{

    public:

        /** Maintain a DisplaySettings singleton for objects to querry at runtime.*/
        static DisplaySettings* instance();


        DisplaySettings()
        {
            setDefaults();
            readEnvironmentalVariables();
        }
        
        DisplaySettings(std::vector<std::string>& commandLine)
        {
            setDefaults();
            readEnvironmentalVariables();
            readCommandLine(commandLine);
        }

        DisplaySettings(const DisplaySettings& vs);
        
        virtual ~DisplaySettings();

        

        DisplaySettings& operator = (const DisplaySettings& vs);
 
        
        void merge(const DisplaySettings& vs);

        void setDefaults();
        
        void readEnvironmentalVariables();

        /** read the command line string list, removing any matched control sequences.*/
        void readCommandLine(std::vector<std::string>& commandLine);
        
        

        void setStereo(const bool on) { _stereo = on; }
        const bool getStereo() const { return _stereo; }

        enum StereoMode
        {
            QUAD_BUFFER,
            ANAGLYPHIC,
            HORIZONTAL_SPLIT,
            VERTICAL_SPLIT
        };
        
        void setStereoMode(const StereoMode mode) { _stereoMode = mode; }
        const StereoMode getStereoMode() const { return _stereoMode; }

        void setEyeSeperation(const float eyeSeperation) { _eyeSeperation = eyeSeperation; }
        const float getEyeSeperation() const { return _eyeSeperation; }

        void setScreenDistance(const float distance) { _screenDistance = distance; }
        const float getScreenDistance() const { return _screenDistance; }

        enum SplitStereoHorizontalEyeMapping
        {
            LEFT_EYE_LEFT_VIEWPORT,
            LEFT_EYE_RIGHT_VIEWPORT
        };
        
        void setSplitStereoHorizontalEyeMapping(SplitStereoHorizontalEyeMapping m) { _splitStereoHorizontalEyeMapping = m; }
        SplitStereoHorizontalEyeMapping getSplitStereoHorizontalEyeMapping() const { return _splitStereoHorizontalEyeMapping; }

        void setSplitStereoHorizontalSeperation(const int s) { _splitStereoHorizontalSeperation = s; }
        const int getSplitStereoHorizontalSeperation() const { return _splitStereoHorizontalSeperation; }

        enum SplitStereoVerticalEyeMapping
        {
            LEFT_EYE_TOP_VIEWPORT,
            LEFT_EYE_BOTTOM_VIEWPORT
        };

        void setSplitStereoVerticalEyeMapping(SplitStereoVerticalEyeMapping m) { _splitStereoVerticalEyeMapping = m; }
        SplitStereoVerticalEyeMapping getSplitStereoVerticalEyeMapping() const { return _splitStereoVerticalEyeMapping; }

        void setSplitStereoVerticalSeperation(const int s) { _splitStereoVerticalSeperation = s; }
        const int getSplitStereoVerticalSeperation() const { return _splitStereoVerticalSeperation; }


        void setScreenHeight(const float height) { _screenHeight = height; }
        const float getScreenHeight() const { return _screenHeight; }


        void setDoubleBuffer(const bool flag) { _doubleBuffer = flag; }
        const bool getDoubleBuffer() const { return _doubleBuffer; }


        void setRGB(const bool flag) { _RGB = flag; }
        const bool getRGB() const { return _RGB; }


        void setDepthBuffer(const bool flag) { _depthBuffer = flag; }
        const bool getDepthBuffer() const { return _depthBuffer; }


        void setMinimumNumAlphaBits(const unsigned int bits) { _minimumNumberAlphaBits = bits; }
        const unsigned int getMinimumNumAlphaBits() const { return _minimumNumberAlphaBits; }
        const bool getAlphaBuffer() const { return _minimumNumberAlphaBits!=0; }


        void setMinimumNumStencilBits(const unsigned int bits) { _minimumNumberStencilBits = bits; }
        const unsigned int getMinimumNumStencilBits() const { return _minimumNumberStencilBits; }
        const bool getStencilBuffer() const { return _minimumNumberStencilBits!=0; }


        void setMaxNumberOfGraphicsContexts(const int num) { _maxNumOfGraphicsContexts = num; }
        const int getMaxNumberOfGraphicsContexts() const { return _maxNumOfGraphicsContexts; }


    protected:
    
        void copy(const DisplaySettings& vs);

        bool                            _stereo;
        StereoMode                      _stereoMode;
        float                           _eyeSeperation;
        float                           _screenDistance;
        float                           _screenHeight;

        SplitStereoHorizontalEyeMapping _splitStereoHorizontalEyeMapping;
        int                             _splitStereoHorizontalSeperation;
        SplitStereoVerticalEyeMapping   _splitStereoVerticalEyeMapping;
        int                             _splitStereoVerticalSeperation;
    
        bool                            _doubleBuffer;
        bool                            _RGB;
        bool                            _depthBuffer;
        unsigned int                    _minimumNumberAlphaBits;
        unsigned int                    _minimumNumberStencilBits;

        int                             _maxNumOfGraphicsContexts;

};

}

# endif
