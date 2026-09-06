// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00613FF0: reverse lookup in the staging-server hash table.
//
// The table is keyed by an integer handle and stores the server pointer.  The
// callback asks for the handle belonging to a server, so this deliberately
// walks the hash table's iterator range instead of hashing the pointer.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

struct _SBServer;
typedef _SBServer *SBServer;

typedef _STL::hash_map<int, SBServer, _STL::hash<int>, _STL::equal_to<int> >
	StagingServerMap;

class PeerThreadClass
{
public:
	int findServer(SBServer server);

private:
	char m_pad[0x210];
	StagingServerMap m_stagingServers;
};

int PeerThreadClass::findServer(SBServer server)
{
	StagingServerMap::iterator it = m_stagingServers.begin();
	StagingServerMap::iterator end = m_stagingServers.end();
	while (it != end)
	{
		if (server == it->second)
			return it->first;
		++it;
	}

	return -1;
}
