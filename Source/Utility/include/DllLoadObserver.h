#ifndef DllLoadObserver_h__
#define DllLoadObserver_h__

#include "typedefs.h"
#include "UtilityExport.h"

class DllLoader;
class UTILITY_EXPORT DllLoadObserver 
{
public:
    DllLoadObserver();
    virtual ~DllLoadObserver();

    // @Brief ∂ØÃ¨ø‚º”‘ÿ [1/24/2014 kyske]
    virtual bool onDllLoad(DllLoader* pDllLoader) = 0;

    // @Brief ∂ØÃ¨ø‚–∂‘ÿ [1/24/2014 kyske]
    virtual bool onDllUnload(DllLoader* pDllLoader) = 0;
};
#endif // DllLoadObserver_h__