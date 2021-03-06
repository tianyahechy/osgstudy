//C++
// ---------------------------------------------------------------------------------------------------------------------------------
// Copyright 2000, Paul Nettle. All rights reserved.
//
// You are free to use this source code in any commercial or non-commercial product.
//
// mmgr.h - Memory manager & tracking software
//
// The most recent version of this software can be found at: ftp://ftp.GraphicsPapers.com/pub/ProgrammingTools/MemoryManagers/
//
// [NOTE: Best when viewed with 8-character tabs]
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef    _H_MMGR
#define    _H_MMGR


#include <osg/Export.h>

#include <stdlib.h>
#include <new>


// ---------------------------------------------------------------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------------------------------------------------------------

typedef    struct tag_au
{
    size_t        actualSize;
    size_t        reportedSize;
    void        *actualAddress;
    void        *reportedAddress;
    char        sourceFile[40];
    char        sourceFunc[40];
    unsigned int    sourceLine;
    unsigned int    allocationType;
    bool        breakOnDealloc;
    bool        breakOnRealloc;
    unsigned int    allocationNumber;
    struct tag_au    *next;
    struct tag_au    *prev;
} sAllocUnit;

typedef    struct
{
    unsigned int    totalReportedMemory;
    unsigned int    totalActualMemory;
    unsigned int    peakReportedMemory;
    unsigned int    peakActualMemory;
    unsigned int    accumulatedReportedMemory;
    unsigned int    accumulatedActualMemory;
    unsigned int    accumulatedAllocUnitCount;
    unsigned int    totalAllocUnitCount;
    unsigned int    peakAllocUnitCount;
} sMStats;

// ---------------------------------------------------------------------------------------------------------------------------------
// External constants
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern const    unsigned int    m_alloc_unknown;
SG_EXPORT extern const    unsigned int    m_alloc_new;
SG_EXPORT extern const    unsigned int    m_alloc_new_array;
SG_EXPORT extern const    unsigned int    m_alloc_malloc;
SG_EXPORT extern const    unsigned int    m_alloc_calloc;
SG_EXPORT extern const    unsigned int    m_alloc_realloc;
SG_EXPORT extern const    unsigned int    m_alloc_delete;
SG_EXPORT extern const    unsigned int    m_alloc_delete_array;
SG_EXPORT extern const    unsigned int    m_alloc_free;

// ---------------------------------------------------------------------------------------------------------------------------------
// Used by the macros
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern void        m_setOwner(const char *file, const unsigned int line);

// ---------------------------------------------------------------------------------------------------------------------------------
// Allocation breakpoints
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern bool        &m_breakOnRealloc(void *reportedAddress);
SG_EXPORT extern bool        &m_breakOnDealloc(void *reportedAddress);
SG_EXPORT extern void         m_breakOnAllocation(unsigned int count);

// ---------------------------------------------------------------------------------------------------------------------------------
// The meat of the memory tracking software
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern void  *m_allocator(const char *sourceFile, const unsigned int sourceLine,
                                     const unsigned int allocationType, const size_t reportedSize);
SG_EXPORT extern void  *m_reallocator(const char *sourceFile, const unsigned int sourceLine,
                                      const unsigned int reallocationType, const size_t reportedSize, void *reportedAddress);
SG_EXPORT extern void  m_deallocator(const char *sourceFile, const unsigned int sourceLine,
                                     const unsigned int deallocationType, const void *reportedAddress);

// ---------------------------------------------------------------------------------------------------------------------------------
// Utilitarian functions
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern bool m_validateAddress(const void *reportedAddress);
SG_EXPORT extern bool m_validateAllocUnit(const sAllocUnit *allocUnit);
SG_EXPORT extern bool m_validateAllAllocUnits();

// ---------------------------------------------------------------------------------------------------------------------------------
// Unused RAM calculations
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern unsigned int    m_calcUnused(const sAllocUnit *allocUnit);
SG_EXPORT extern unsigned int    m_calcAllUnused();

// ---------------------------------------------------------------------------------------------------------------------------------
// Logging and reporting
// ---------------------------------------------------------------------------------------------------------------------------------

SG_EXPORT extern void        m_dumpAllocUnit(const sAllocUnit *allocUnit, const char *prefix = "");
SG_EXPORT extern void        m_dumpMemoryReport(const char *filename = "memreport.log", const bool overwrite = true);
SG_EXPORT extern sMStats     m_getMemoryStatistics();

// ---------------------------------------------------------------------------------------------------------------------------------
// Variations of global operators new & delete
// ---------------------------------------------------------------------------------------------------------------------------------

#ifdef OSG_USE_MEMORY_MANAGER

    // ---------------------------------------------------------------------------------------------------------------------------------
    // Macros -- "Kids, please don't try this at home. We're trained professionals here." :)
    // ---------------------------------------------------------------------------------------------------------------------------------


    #define    osgNew              (m_setOwner  (__FILE__,__LINE__),false) ? NULL : new
    #define    osgDelete           (m_setOwner  (__FILE__,__LINE__),false) ? m_setOwner("",0) : delete
    #define    osgMalloc(sz)        m_allocator  (__FILE__,__LINE__,m_alloc_malloc,sz)
    #define    osgCalloc(sz)        m_allocator  (__FILE__,__LINE__,m_alloc_calloc,sz)
    #define    osgRealloc(ptr,sz)   m_reallocator(__FILE__,__LINE__,m_alloc_realloc,sz,ptr)
    #define    osgFree(ptr)         m_deallocator(__FILE__,__LINE__,m_alloc_free,ptr)

#else // OSG_USE_MEMORY_MANAGER

    #define    osgNew               new
    #define    osgDelete            delete
    #define    osgMalloc(sz)        malloc(sz)
    #define    osgCalloc(sz)        calloc(sz)
    #define    osgRealloc(ptr,sz)   realloc(ptr,sz)
    #define    osgFree(ptr)         free(ptr)

#endif // OSG_USE_MEMORY_MANAGER

// ---------------------------------------------------------------------------------------------------------------------------------
// mmgr.h - End of file
// ---------------------------------------------------------------------------------------------------------------------------------

#endif // _H_MMGR
