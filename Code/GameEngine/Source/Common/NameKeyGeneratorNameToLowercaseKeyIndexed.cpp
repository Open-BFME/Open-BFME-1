// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/namekeygenerator /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// The current-layout copy of NameKeyGenerator::nameToLowercaseKey.  Unlike
// the stale-header copy at 0x009EDD70, this body uses the vptr'd 16-byte Bucket
// and maintains BFME's reverse key-to-Bucket index.

#include "PreRTS.h"

UnsignedInt calcHashForLowercaseString(const char *name);

NameKeyType NameKeyGenerator::nameToLowercaseKey(const char *nameString)
{
	Bucket *b;
	UnsignedInt hash = calcHashForLowercaseString(nameString) % SOCKET_COUNT;

	for (b = m_sockets[hash]; b; b = b->m_nextInSocket) {
		if (_strcmpi(nameString, b->m_nameString.str()) == 0) {
			return b->m_key;
		}
	}

	b = newInstance(Bucket);
	b->m_key = (NameKeyType)m_nextID++;
	b->m_nameString = nameString;
	b->m_nextInSocket = m_sockets[hash];
	m_sockets[hash] = b;
	keyToBucketMap().insert(KeyToBucketMap::value_type(b->m_key, b));

	return b->m_key;
}
