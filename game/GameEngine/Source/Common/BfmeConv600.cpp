// The relationship query this body makes is Object::getRelationship, the 5-byte
// thunk at 0x0004A719.  Object's real layout lives in one header, which hands a
// TU the non-virtual members it needs through OBJECT_TU_MEMBERS; spelling the
// member there (instead of a TU-local stand-in) is what puts retail's mangled
// name on the call.  The opaque field reads below stay on the local layouts.
enum Relationship
{
	Relationship_BfmeConv600
};

#define OBJECT_TU_MEMBERS Relationship getRelationship(const Object *) const;

#include "../GameLogic/Object/object.h"

class BfmeOtherCGG
{
public:
	int bfmeKindCGG(void *value);
};

class BfmeThingCGG
{
public:
	void *bfmeGoCGG(BfmeOtherCGG *other, bool flag);
	unsigned char m_bfmeHead[4];
	void *m_bfmeVal;
	unsigned char m_bfmeGap[8];
	void *m_bfmePtr;
};

void *BfmeThingCGG::bfmeGoCGG(BfmeOtherCGG *other, bool flag)
{
	if (reinterpret_cast<Object *>(other)->getRelationship(reinterpret_cast<const Object *>(m_bfmeVal)) == 2 && !flag)
		return 0;
	return m_bfmePtr;
}
