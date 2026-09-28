// ??0NameKeyGenerator@@QAE@XZ
// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Zero Hour's constructor body verbatim. BFME adds its O(1) key->Bucket reverse
// index (m_keyToBucketStorage, shim-proven at this+0x2bf48) to the member init
// list: the STLport hash_map(100) inlines to the four member stores plus the
// _M_initialize_buckets call at 0x8FF00.
//
// The socket clear is the ZH `for` loop on purpose, not a spelled-out memset:
// MSVC 7.1's loop-idiom recognition lowers it to retail's
// `lea edi,[esi+8]; xor eax,eax; mov ecx,0xafcf; rep stosd` in that order,
// while memset(...,0,...) materialises the fill value one instruction earlier
// (xor eax,eax first) and misses those 5 bytes.

#define __PLACEMENT_VEC_NEW_INLINE
#include <hash_map>
#include "PreRTS.h"

NameKeyGenerator::NameKeyGenerator() : m_keyToBucketStorage(100)
{

	m_nextID = (UnsignedInt)NAMEKEY_INVALID;  // uninitialized system

	for (Int i = 0; i < SOCKET_COUNT; ++i)
		m_sockets[i] = NULL;

}  // end NameKeyGenerator
