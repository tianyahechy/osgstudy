//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_FRAMESTAMP
#define OSG_FRAMESTAMP 1

#include <osg/Referenced.h>

#if defined(__sgi) || (defined(WIN32) && !defined(__MWERKS__))
#include <time.h>
#else
#include <ctime>
using std::tm;
#endif

namespace osg
{

/** Class which encapsulates the frame number, reference time and calander
  * time of specific frame, used to synchonize operations on the scene graph
  * and other machines when using a graphics cluster.  Note the calander
  * time can be an artificial simulation time or capture the real time
  * of day etc.*/ 
class SG_EXPORT FrameStamp : public Referenced
{
    public:

        FrameStamp();
        FrameStamp(const FrameStamp& fs);
        ~FrameStamp();
        
        FrameStamp& operator = (const FrameStamp& fs);
        
        void setFrameNumber(int fnum) { _frameNumber = fnum; }
        int getFrameNumber() const { return _frameNumber; }
        
        void setReferenceTime(double refTime) { _referenceTime = refTime; }
        double getReferenceTime() const { return _referenceTime; }
        
        void setCalendarTime(const tm& calendarTime);
        void getCalendarTime(tm& calendarTime) const;
        
    protected:
    
        // note no dynamic memory is used so that data can be passed
        // via a simple memory copy or within a data packet across
        // the network.
    
        int     _frameNumber;
        double  _referenceTime;
        
        
        // member varaibles of time.h's tm structure, copied here to
        // ensure that all data is no dynamic. The tm structure itself
        // is not completely consistent betweem implementations, which
        // could be a problem when sending the FrameStamp across a network
        // with differnt versions of tm (i.e mixing Unix and Windows.)
        int tm_sec;            /* Seconds.        [0-60] (1 leap second) */
        int tm_min;            /* Minutes.        [0-59] */
        int tm_hour;           /* Hours.          [0-23] */
        int tm_mday;           /* Day.            [1-31] */
        int tm_mon;            /* Month.          [0-11] */
        int tm_year;           /* Year            - 1900.  */
        int tm_wday;           /* Day of week.    [0-6] */
        int tm_yday;           /* Days in year.   [0-365]    */
        int tm_isdst;           /* DST.           [-1/0/1]*/
        
        
};

}


#endif
