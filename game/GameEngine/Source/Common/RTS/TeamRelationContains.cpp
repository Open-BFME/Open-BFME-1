// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// The two relation-map membership helpers, at adjacent offsets on one object:
//
//   0x000F0F70  the team-side lookup, map pointer at +0xEC
//   0x000F0FD0  the player-side lookup, map pointer at +0xF0
//
// Both are 71-byte bodies that ask the same question of the same kind of map,
// and Team's BFME layout puts the two map pointers four bytes apart -- which
// is the fact two separate files could each half-state and neither could show.
// A single polymorphic base puts the STLport map at +0x04 inside each map
// object, so one wrapper shape serves both.
//
// The map instantiation was written out twice under two names, and they are
// not two types: the key typedefs -- TeamID in one file, PlayerIndex in the
// other -- are both unsigned int, so the two hash_map spellings are one
// instantiation and already resolved to one body at link time. Declared once,
// that stops being invisible.
//
// The two lookup class names stay exactly as they are. They are spelled into
// their rows' decorations -- ?contains@Rva000F0F70TeamRelationLookup@@QBE_NI@Z
// and ?contains@Rva000F0FD0PlayerRelationLookup@@QBE_NI@Z -- so renaming them
// to something shared would delete both rows. The owner spelling stays
// address-derived because the caller names are absent from the stripped object.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

typedef unsigned int TeamID;
typedef unsigned int PlayerIndex;
typedef int Relationship;

// TeamID and PlayerIndex are the same type, so this is the one instantiation
// both bodies call.
typedef _STL::pair<const TeamID, Relationship> BfmeRelationPair;
typedef _STL::hash_map<TeamID, Relationship, _STL::hash<TeamID>,
	_STL::equal_to<TeamID>, _STL::allocator<BfmeRelationPair> > BfmeRelationMap;

struct BfmeRelationMapObject
{
	void *m_vtable;
	BfmeRelationMap m_map;						// +0x04
};

class Rva000F0F70TeamRelationLookup
{
public:
	bool contains(TeamID key) const;

private:
	char m_unmodelled[0xec];
	BfmeRelationMapObject *m_teamRelations;				// +0xEC
};

class Rva000F0FD0PlayerRelationLookup
{
public:
	bool contains(PlayerIndex key) const;

private:
	char m_unmodelled[0xf0];
	BfmeRelationMapObject *m_playerRelations;			// +0xF0
};

// ?contains@Rva000F0F70TeamRelationLookup@@QBE_NI@Z
bool Rva000F0F70TeamRelationLookup::contains(TeamID key) const
{
	return m_teamRelations->m_map.find(key) != m_teamRelations->m_map.end();
}

// ?contains@Rva000F0FD0PlayerRelationLookup@@QBE_NI@Z
bool Rva000F0FD0PlayerRelationLookup::contains(PlayerIndex key) const
{
	return m_playerRelations->m_map.find(key) != m_playerRelations->m_map.end();
}
