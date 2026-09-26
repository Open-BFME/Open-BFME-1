// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: hash_map<Int, Relationship>::_M_insert, retail 0x00787140, 111
// bytes. The name was parked on the 5-byte thunk at 0x000013E8.
//
// STLport's own body out of the real header: resize for one more element, hash
// the key -- an Int, so the hash is the identity and the bucket index is a
// plain divide -- then link a new node at the head of its bucket.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

typedef unsigned int UnsignedInt;

typedef _STL::hash_map<Int, Relationship, _STL::hash<Int>, _STL::equal_to<Int> > BfmeRelationshipHash;
typedef _STL::hash_map<UnsignedInt, Relationship, _STL::hash<UnsignedInt>, _STL::equal_to<UnsignedInt> > BfmeRelationshipHashU;

Relationship &BfmeRelationshipHashAnchor(BfmeRelationshipHash &table, Int key)
{
	return table[key];
}

Relationship &BfmeRelationshipHashAnchorU(BfmeRelationshipHashU &table, UnsignedInt key)
{
	return table[key];
}
