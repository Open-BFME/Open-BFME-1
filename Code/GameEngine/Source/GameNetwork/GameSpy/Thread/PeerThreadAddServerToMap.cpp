// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// readable body of ?addServerToMap@PeerThreadClass@@: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp

// FILE: PeerThreadAddServerToMap.cpp //////////////////////////////////////
//
// PeerThreadClass::addServerToMap, retail 0x00647950.
//
// PeerThread.cpp compiles this body to 47 of 50 bytes; the three
// disagreements are m_nextStagingServer and m_stagingServers, which BFME puts
// at +0x208 and +0x20c where that file puts them at +0x1f8 and +0x1fc, plus
// the REL32 to map<Int,SBServer>::operator[].  The offsets are the same pair
// PeerThreadClearPlayerStats.cpp records; that file could not host this body
// because its replica declares operator[] rather than including STLport, and
// a declared-only operator[] loses the enregistered copy of val that retail
// keeps in esi.  So the body moved into its own TU with the real header and
// only the two members it proves.
//
// The REL32 goes to the incremental-link thunk at 0x0001AA50, which jumps to
// the operator[] copy at 0x006473A0 -- a second image copy of the same
// instantiation the ledger already claims at 0x000A56D0.  reverse/symbols.csv
// carries 0x006473A0 as an additional candidate for the same decorated name;
// build.py adds a pinned body?s own thunks, so this call site resolves to the
// thunk while every existing call site keeps 0x000A56D0.
//
/////////////////////////////////////////////////////////////////////////////

#include <map>

typedef int Int;
struct _SBServer;
typedef _SBServer *SBServer;

class PeerThreadClass
{
public:

	Int addServerToMap( SBServer server );

private:

	char m_bfmeHead[0x208];
	Int m_nextStagingServer;								// @0x208
	std::map<Int, SBServer> m_stagingServers;			// @0x20c

};

// ?addServerToMap@PeerThreadClass@@QAEHPAU_SBServer@@@Z
Int PeerThreadClass::addServerToMap( SBServer server )
{
	Int val = m_nextStagingServer++;
	m_stagingServers[val] = server;
	return val;
}
