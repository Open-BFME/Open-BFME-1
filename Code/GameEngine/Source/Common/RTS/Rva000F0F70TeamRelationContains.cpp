// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// Retail 0x000F0F70 is the Team-side relation-map membership helper.  The
// caller name is absent from the stripped object, so the owner spelling stays
// address-derived.  Team's BFME layout puts m_teamRelations at +0xEC; its
// single polymorphic base puts the STLport map at +0x04.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

typedef unsigned int TeamID;
typedef int Relationship;
typedef _STL::pair<const TeamID, Relationship> Rva000F0F70RelationPair;
typedef _STL::hash_map<TeamID, Relationship, _STL::hash<TeamID>,
	_STL::equal_to<TeamID>, _STL::allocator<Rva000F0F70RelationPair> > Rva000F0F70RelationMap;

struct Rva000F0F70TeamRelationMap
{
	void *m_vtable;
	Rva000F0F70RelationMap m_map;
};

class Rva000F0F70TeamRelationLookup
{
public:
	bool contains(TeamID key) const;

private:
	char m_unmodelled[0xec];
	Rva000F0F70TeamRelationMap *m_teamRelations;
};

// ?contains@Rva000F0F70TeamRelationLookup@@QBE_NI@Z
bool Rva000F0F70TeamRelationLookup::contains(TeamID key) const
{
	return m_teamRelations->m_map.find(key) != m_teamRelations->m_map.end();
}
