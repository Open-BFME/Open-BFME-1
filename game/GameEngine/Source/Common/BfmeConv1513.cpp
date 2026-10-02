// Open-BFME5 conversions.

// The relationship query this body makes is Object::getRelationship, the 5-byte
// thunk at 0x0004A719.  Object's real layout lives in one header, which hands a
// TU the non-virtual members it needs through OBJECT_TU_MEMBERS; spelling the
// member there (instead of a TU-local stand-in) is what puts retail's mangled
// name on the call.  The opaque byte reads below stay on the local layout.
enum Relationship
{
	Relationship_BfmeConv1513
};

#define OBJECT_TU_MEMBERS Relationship getRelationship(const Object *) const;

#include "../GameLogic/Object/object.h"
#include "../GameLogic/command_source_type.h"

bool __cdecl isObjectShroudedForAction(const Object *source, const Object *target,
	CommandSourceType commandSource);
// Retail's static helper uses EDI/ESI for the two object arguments and one
// stack argument for command source.  This view preserves that call shape.
typedef bool (__cdecl *BfmeShroudedCall)(void *ctx);

class BfmeObjVNI
{
public:
	int bfmeRelationVNI(BfmeObjVNI *o);
	char m_bfmePad000[0x90];
	unsigned char m_bfme90;
	char m_bfmePad091[0x113];
	unsigned char m_bfme1a4;
	char m_bfmePad1a5[0x19f];
	unsigned char m_bfme344;
};

char __stdcall bfmeCanSeeVNI(BfmeObjVNI *a, BfmeObjVNI *b, void *ctx)
{
	if (a != 0 && b != 0 && (b->m_bfme344 & 1) == 0 &&
		reinterpret_cast<BfmeShroudedCall>(&isObjectShroudedForAction)(ctx) == 0
		&& reinterpret_cast<Object *>(a)->getRelationship(reinterpret_cast<const Object *>(b)) == 0 && (b->m_bfme90 & 0x40) == 0)
	{
		unsigned char v = b->m_bfme1a4;

		v >>= 5;
		v = ~v;
		v &= 1;
		return (char)v;
	}
	return 0;
}
