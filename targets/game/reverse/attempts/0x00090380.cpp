// ??0NameKeyGenerator@@QAE@XZ
// partial score=0.82 date=2026-09-09
// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <hash_map>
#include "PreRTS.h"

// ??0NameKeyGenerator@@QAE@XZ
NameKeyGenerator::NameKeyGenerator()
{
	new (&keyToBucketMap()) KeyToBucketMap(100);
	m_nextID = NAMEKEY_INVALID;
	memset(m_sockets, 0, sizeof(m_sockets));
}
