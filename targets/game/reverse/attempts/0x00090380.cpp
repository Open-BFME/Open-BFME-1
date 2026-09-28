// ??0NameKeyGenerator@@QAE@XZ
// partial score=0.99 date=2026-09-28
// BANKED 2026-09-28 (orchestrator wind-down): this body is BYTE-EXACT (120 B) only together with the
// shim change below, which declares NameKeyGenerator's key->Bucket hash_map as a REAL member so the
// ctor init list can construct it (hash_map(100) -> the four member stores + _M_initialize_buckets).
// That shim change broke the full gate: game/GameEngine/Source/Common/NameKeyGenerator.cpp:87 still does
// reinterpret_cast<KeyToBucketMap*>(m_keyToBucketStorage)->clear() (C2440), and a real member would also
// make ~NameKeyGenerator destroy the map, which the raw-storage idiom exists to avoid (retail never frees it).
// Next step: keep the storage idiom for every other TU and give THIS TU its own shim/class view (TU-scoped),
// or placement-new the map in the ctor and compare bytes. Required shim change, as a diff:
//
// diff --git a/inputs/reference/shims/namekeygenerator/Common/NameKeyGenerator.h b/inputs/reference/shims/namekeygenerator/Common/NameKeyGenerator.h
// index 95831c77ff..599822ab84 100644
// --- a/inputs/reference/shims/namekeygenerator/Common/NameKeyGenerator.h
// +++ b/inputs/reference/shims/namekeygenerator/Common/NameKeyGenerator.h
// @@ -191,8 +191,8 @@ private:
//  	// freed anywhere); this storage does too, by construction. Same technique as
//  	// WWDebug/wwmemlog.cpp's `char _MemLogCriticalSectionHandle[sizeof(CRITICAL_SECTION)]`.
//  	typedef std::hash_map<NameKeyType, Bucket*, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > KeyToBucketMap;
// -	UnsignedInt		m_keyToBucketStorage[(sizeof(KeyToBucketMap) + sizeof(UnsignedInt) - 1) / sizeof(UnsignedInt)];
// -	KeyToBucketMap& keyToBucketMap() { return *reinterpret_cast<KeyToBucketMap*>(m_keyToBucketStorage); }
// +	KeyToBucketMap		m_keyToBucketStorage;
// +	KeyToBucketMap& keyToBucketMap() { return m_keyToBucketStorage; }
//  
//  };  // end class NameKeyGenerator
//  
//
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
