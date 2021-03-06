//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_BOUNDSCHECKING
#define OSG_BOUNDSCHECKING 1

#include <osg/Notify.h>

namespace osg {


/** if value is greater than or equal to minValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class T>
inline void clampGEQUAL(T& value,const T minValue,const char* valueName)
{
    if (value<minValue)
    {
        notify(WARN) << "Warning: "<<valueName<<" of "<<value<<" is below permitted minimum, clampping to "<<minValue<<"."<< std::endl;
        value = minValue;
    }
}

/** if value is less than or equal to maxValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class T>
inline void clampLEQUAL(T& value,const T maxValue,const char* valueName)
{
    if (value>maxValue)
    {
        notify(WARN) << "Warning: "<<valueName<<" of "<<value<<" is above permitted maximum, clampping to "<<maxValue<<"."<< std::endl;
        value = maxValue;
    }
}

/** if value is between or equal to minValue and maxValue do nothing - legal value,
  * otherwise clamp value to specified to range and return warning 
  * with valueName specifying which variable was clamped. Equivilant to
  * calling clampGEQUAL(value,minValue,valueName); clampLEQUAL(value,maxValue,valueName); */
template <class T>
inline void clampBetweenRange(T& value,const T minValue,const T maxValue,const char* valueName)
{
    if (value<minValue)
    {
        notify(WARN) << "Warning: "<<valueName<<" of "<<value<<" is below permitted minimum, clampping to "<<minValue<<"."<< std::endl;
        value = minValue;
    }
    else
    if (value>maxValue)
    {
        notify(WARN) << "Warning: "<<valueName<<" of "<<value<<" is above permitted maximum, clampping to "<<maxValue<<"."<< std::endl;
        value = maxValue;
    }
    
}

/** if array element value[i] is greater than or equal to minValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArrayElementGEQUAL(A& value,const unsigned int i,const T minValue,const char* valueName)
{
    if (value[i]<minValue)
    {
        notify(WARN) << "Warning: "<<valueName<<"["<<i<<"] of "<<value[i]<<" is below permitted minimum, clampping to "<<minValue<<"."<< std::endl;
        value[i] = minValue;
    }
}

/** if array element value[i] is less than or equal to maxValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArrayElementLEQUAL(A& value,const unsigned int i,const T maxValue,const char* valueName)
{
    if (value[i]>maxValue)
    {
        notify(WARN) << "Warning: "<<valueName<<"["<<i<<"] of "<<value[i]<<" is above permitted maximum, clampping to "<<maxValue<<"."<< std::endl;
        value = maxValue;
    }
}

/** if array element value[i] is between or equal to minValue and maxValue do nothing - legal value,
  * otherwise clamp value to specified to range and return warning 
  * with valueName specifying which variable was clamped. Equivilant to
  * calling clampGEQUAL(value,minValue,valueName); clampLEQUAL(value,maxValue,valueName); */
template <class A, class T>
inline void clampArrayElementBetweenRange(A& value,const unsigned int i,const T minValue,const T maxValue,const char* valueName)
{
    if (value[i]<minValue)
    {
        notify(WARN) << "Warning: "<<valueName<<"["<<i<<"] of "<<value[i]<<" is below permitted minimum, clampping to "<<minValue<<"."<< std::endl;
        value[i] = minValue;
    }
    else
    if (value[i]>maxValue)
    {
        notify(WARN) << "Warning: "<<valueName<<"["<<i<<"] of "<<value[i]<<" is above permitted maximum, clampping to "<<maxValue<<"."<< std::endl;
        value[i] = maxValue;
    }
    
}

/** if array elements are greater than or equal to minValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArrayElementsGEQUAL(A& value,const unsigned int first,const unsigned int last,const T minValue,const char* valueName)
{
    for(unsigned int i=first;i<=last;++i)
        clampArrayElementGEQUAL(value,i,minValue,valueName);
}

/** if array elements are less than or equal to maxValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArrayElementsLEQUAL(A& value,const unsigned int first,const unsigned int last,const T maxValue,const char* valueName)
{
    for(unsigned int i=first;i<=last;++i)
        clampArrayElementLEQUAL(value,i,maxValue,valueName);
}

/** if array elements are between or equal to minValue and maxValue do nothing - legal value,
  * otherwise clamp value to specified to range and return warning 
  * with valueName specifying which variable was clamped. Equivalent to
  * calling clampGEQUAL(value,minValue,valueName); clampLEQUAL(value,maxValue,valueName); */
template <class A, class T>
inline void clampArrayElementsBetweenRange(A& value,const unsigned int first,const unsigned int last,const T minValue,const T maxValue,const char* valueName)
{
    for(unsigned int i=first;i<=last;++i)
        clampArrayElementBetweenRange(value,i,minValue,maxValue,valueName);    
}


/** if array4 elements are greater than or equal to minValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArray3GEQUAL(A& value,const T minValue,const char* valueName)
{
    clampArrayElementsGEQUAL(value,0u,2u,minValue,valueName);
}

/** if array4 elements are is less than or equal to maxValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArray3LEQUAL(A& value,const T maxValue,const char* valueName)
{
    clampArrayElementsLEQUAL(value,0u,2u,maxValue,valueName);
}

/** if array4 elements are between or equal to minValue and maxValue do nothing - legal value,
  * otherwise clamp value to specified to range and return warning 
  * with valueName specifying which variable was clamped. Equivilant to
  * calling clampGEQUAL(value,minValue,valueName); clampLEQUAL(value,maxValue,valueName); */
template <class A, class T>
inline void clampArray3BetweenRange(A& value,const T minValue,const T maxValue,const char* valueName)
{
    clampArrayElementsBetweenRange(value,0u,2u,minValue,maxValue,valueName);
}



/** if array4 elements are greater than or equal to minValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArray4GEQUAL(A& value,const T minValue,const char* valueName)
{
    clampArrayElementsGEQUAL(value,0u,3u,minValue,valueName);
}

/** if array4 elements are is less than or equal to maxValue do nothing - legal value,
  * otherwise clamp value to specified maximum value and return warning 
  * with valueName specifying which variable was clamped.*/
template <class A, class T>
inline void clampArray4LEQUAL(A& value,const unsigned int first,const unsigned int last,const T maxValue,const char* valueName)
{
    clampArrayElementsLEQUAL(value,0u,3u,maxValue,valueName);
}

/** if array4 elements are between or equal to minValue and maxValue do nothing - legal value,
  * otherwise clamp value to specified to range and return warning 
  * with valueName specifying which variable was clamped. Equivilant to
  * calling clampGEQUAL(value,minValue,valueName); clampLEQUAL(value,maxValue,valueName); */
template <class A, class T>
inline void clampArray4BetweenRange(A& value,const T minValue,const T maxValue,const char* valueName)
{
    clampArrayElementsBetweenRange(value,0u,3u,minValue,maxValue,valueName);
}

}

#endif
