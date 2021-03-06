//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_NOTIFY
#define OSG_NOTIFY 1

#include <osg/Export.h>

#include <iostream>
#include <fstream>
#include <memory>

namespace osg {

/** Range of notify levels from DEBUG_FP through to FATAL, ALWAYS
  * is reserved for forcing the absorption of all messages.  The
  * keywords are also used verbatim when specified by the environmental
  * variable OSGNOTIFYLEVEL.  See documentation on osg::notify() for
  * further details.
  */
enum NotifySeverity {
    ALWAYS=0,
    FATAL=1,
    WARN=2,
    NOTICE=3,
    INFO=4,
    DEBUG_INFO=5,
    DEBUG_FP=6
};

/** global notify level. */
//SG_EXPORT extern NotifySeverity g_NotifyLevel;

/** global notify nul stream. added for Mac OSX */
//SG_EXPORT extern std::auto_ptr<std::ofstream> g_NotifyNulStream;

/** global notify nul stream. added for Mac OSX */
//SG_EXPORT extern bool g_NotifyInit;

/** set the notify level, overriding the default or value set by
  * the environmental variable OSGNOTIFYLEVEL.
  */
SG_EXPORT extern void setNotifyLevel(NotifySeverity severity);

/** get the notify level. */
SG_EXPORT extern NotifySeverity getNotifyLevel();

/** initialize notify level. */
SG_EXPORT extern bool initNotifyLevel();

/** notify messaging function for providing fatal through to verbose
  * debugging messages.  Level of messages sent to the console can
  * be controlled by setting the NotifyLevel either within your 
  * application or via the an environmental variable. For instance
  * setenv OSGNOTIFYLEVEL DEBUG (for tsh), export OSGNOTIFYLEVEL=DEBUG
  * (for bourne shell) or set OSGNOTIFYLEVEL=DEBUG (for Windows) all
  * set tell the osg to redirect all debugging and more important messages
  * to the console (useful for debugging :-)  setting ALWAYS will force
  * all messages to be absorbed, which might be appropriate for final
  * applications.  Default NotifyLevel is NOTICE.  Check the enum 
  * NotifySeverity for full range of possibilities.  To use the notify
  * with your code simply use the notify function as a normal file
  * stream (like cout) i.e osg::notify(osg::DEBUG) << "Hello Bugs!"<<endl;
  */
  
//
// PJA MAC OSX 30-09-01 
// previous implementation was causing Mac OSX to misbehave. This version
// places less stress on compiler and runs on Mac

SG_EXPORT extern std::ostream& notify(const NotifySeverity severity);
// {
//     static bool initilized = false;
//     if (!initilized) initilized = initNotifyLevel();
// 
//     if (severity<=g_NotifyLevel)
//     {
//         if (severity<=osg::WARN) return std::cerr;
//         else return std::cout;
//     }
//     cout << "doing a notify to null stream "<<osg::g_NotifyLevel<<" "<<osg::g_NotifyNulStream.get()<<" "<<osg::g_NotifyInit<<endl;
//     //if (osg::g_NotifyNulStream.get()==0L) abort();
//     return std::cout;    
//     //return *osg::g_NotifyNulStream;
// }

inline std::ostream& notify(void) { return notify(osg::INFO); }

}

#endif
