// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// Retail 0x000F0FD0 is the player-side relation-map membership helper.  The
// stripped object has no recoverable original helper name, so the owner stays
// address-derived.  Team's BFME layout puts m_playerRelations at +0xF0; its
// single polymorphic base puts the STLport map at +0x04.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

typedef unsigned int PlayerIndex;
typedef int Relationship;
typedef _STL::pair<const PlayerIndex, Relationship> Rva000F0FD0RelationPair;
typedef _STL::hash_map<PlayerIndex, Relationship, _STL::hash<PlayerIndex>,
	_STL::equal_to<PlayerIndex>, _STL::allocator<Rva000F0FD0RelationPair> > Rva000F0FD0RelationMap;

struct Rva000F0FD0PlayerRelationMap
{
	void *m_vtable;
	Rva000F0FD0RelationMap m_map;
};

class Rva000F0FD0PlayerRelationLookup
{
public:
	bool contains(PlayerIndex key) const;

private:
	char m_unmodelled[0xf0];
	Rva000F0FD0PlayerRelationMap *m_playerRelations;
};

// ?contains@Rva000F0FD0PlayerRelationLookup@@QBE_NI@Z
bool Rva000F0FD0PlayerRelationLookup::contains(PlayerIndex key) const
{
	return m_playerRelations->m_map.find(key) != m_playerRelations->m_map.end();
}
