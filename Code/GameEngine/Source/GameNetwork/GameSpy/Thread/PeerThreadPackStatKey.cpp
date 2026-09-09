// ?packStatKey@PeerThreadClass@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@PBD0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?packStatKey@PeerThreadClass@@: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp
//
// Retail 0x00647CD0 (205 B): PeerThreadClass::packStatKey, the ZH
// PeerThread.cpp:366 body line for line (called by lookupStatForPlayer at
// 0x00647DD0, PeerThreadLookupStatForPlayer.cpp). Standalone TU so STLport
// builds with its default node allocator (direct calls), matching that
// neighbour's approach instead of the project's PreRTS.h configuration.

#include <string>

class PeerThreadClass
{
public:
	std::string packStatKey(const char *nick, const char *key);
};

std::string PeerThreadClass::packStatKey(const char *nick, const char *key)
{
	std::string s = nick;
	s.append(key);
	return s;
}
