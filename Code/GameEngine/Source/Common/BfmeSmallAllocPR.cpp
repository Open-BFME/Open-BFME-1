// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Og- /DZH_EMIT_POOL_GLUE /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define private public
#include "PreRTS.h"
#undef private

namespace _STL
{

class NodeAllocMutex
{
public:
	void _M_acquire_lock(void);
	void _M_release_lock(void);
};

}

#undef _STLP_STATIC_MUTEX
#define _STLP_STATIC_MUTEX NodeAllocMutex
#undef _STLP_MUTEX_INITIALIZER
#define _STLP_MUTEX_INITIALIZER
#define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION 1
#include <stl/_alloc.c>
#undef _STLP_EXPOSE_GLOBALS_IMPLEMENTATION

class BfmeNodeAllocLock : public _STL::_Node_Alloc_Lock<false, 0>
{
	int m_dummy;

public:
	~BfmeNodeAllocLock()
	{
		int unused;
		(void)unused;
    }
};

// The matched STLport refill body is also known under this BFME alias at the
// retail address.  Calling the alias keeps the private-member decoration from
// being changed by the TU-local access exposure above.
extern void *bfmeSmallRefillPR(unsigned int bytes);

void *bfmeSmallAllocPR(unsigned int bytes)
{
	void *result;
	_STL::_Node_alloc_obj * volatile *my_free_list =
		_STL::__node_alloc<false, 0>::_S_free_list + ((bytes - 1) >> 3);
	BfmeNodeAllocLock lock_instance;
	if ((result = *my_free_list) != 0) {
		*my_free_list = ((_STL::_Node_alloc_obj *)result)->_M_free_list_link;
	} else {
		result = bfmeSmallRefillPR(bytes);
	}
	return result;
}
