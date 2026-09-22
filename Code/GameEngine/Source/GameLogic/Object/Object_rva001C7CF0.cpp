// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// BFME Object launch-force helper. Retail 0x001C7CF0, 295 bytes.
// The body proves its own contents: it reads the physics module at Object+0x208
// (m_physics), bails on the byte at PhysicsBehavior+0x5c, resolves the template
// override chain through the matched Overridable::getFinalOverride (0x00087A80
// via ILT 0x000022BB), bails on ThingTemplate+0x4b0, then builds a Coord3D from
// a degrees-to-radians scale (the literal pool entry 0x3C8EFA35 == PI/180 at
// 0x01075954) and hands it to the pinned PhysicsBehavior::applyMotiveForce
// (0x0029AC40 via ILT 0x0002A284). It then sets model-condition bit 120 of the
// 320-bit flag field at Object+0x110 (word 3 is Object+0x11c, bit 24), pushes
// the field into Drawable::replaceModelConditionState (0x0041CCD0 via ILT
// 0x0001343F), notifies the AIUpdateInterface at Object+0x204 and calls its
// vtable slot +0x224, and finally maps the incoming AsciiString against the
// literal table at 0x012AD04C { "NONE", "CATAPULT_ROCK", "TREBUCHET_ROCK" }
// and stores the winning index at Drawable+0x2ec. That same three-name rock
// list is the one the landed INI parser ActiveBodyParseDamageCreationList.cpp
// scans at VA 0x012AE2C4, which corroborates the index meaning.
//
// The search loop calls StringBase<char>::compare through the receiver
// directly rather than through AsciiString::compare. That matters for bytes:
// ascii_string.h's AsciiString::compare is a delegating inline, and the extra
// inline level makes VC7.1 hand the pushed table entry EAX. Dropping it gives
// retail's "mov ecx,[edi*4+0x12ad04c]; push ecx" at +0xf0, the last residue.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

#include "ascii_string.h"

extern "C" double __cdecl sin(double value);
extern "C" double __cdecl cos(double value);
#pragma intrinsic(sin, cos)

typedef float Real;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class ThingTemplate
{
public:
	void *m_vtable;                          // 0x000
	Overridable *m_nextOverride;             // 0x004
	unsigned char m_pad008[0x4b0 - 0x008];
	unsigned char m_byte4B0;                 // 0x4b0
};

class PhysicsBehavior
{
public:
	void applyMotiveForce(const Coord3D *force);
	// Unnamed retail body 0x0029A6A0 reached through ILT 0x0000D81E; no pin
	// carries a semantic name for it, so it keeps its address.
	void rva0029A6A0(Bool flag);

	unsigned char m_pad000[0x5c];
	unsigned char m_byte5C;                  // 0x05c
};

// Native accessor layers: retail materialises the condition mask in a register
// (mov eax,mask; test eax,ecx; or ecx,eax), which only survives when the bit
// index travels through the bitset accessors instead of a raw word expression.
// See docs/shape_levers.md "Model-condition bit masks".
class ModelConditionFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }
	void reset(Int bit) { m_bits.reset(bit); }

private:
	_STL::bitset<320> m_bits;
};

typedef char Rva001C7CF0ModelConditionFlagsSizeCheck[
	(sizeof(ModelConditionFlags) == 40) ? 1 : -1];

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		unsigned int a, unsigned int b);

	unsigned char m_pad000[0x2ec];
	Int m_int2EC;                            // 0x2ec
};

struct AIUpdateInterface
{
	// Retail's own decoration for 0x0026ED10 is public virtual, so the
	// declaration has to be virtual for the call to reference that symbol;
	// the call itself is qualified, which is the direct call retail makes.
	virtual void friend_notifyStateMachineChanged();

	void vtableSlot224()
	{
		typedef void (__fastcall *Slot)(AIUpdateInterface *);
		(*(Slot **)this)[0x224 / 4](this);
	}
};

class Object
{
public:
	void rva001C7CF0(Real angleDegrees, Real magnitude,
		Real verticalScale, const AsciiString &rockName);

	unsigned char m_pad000[0x004];
	ThingTemplate *m_template;               // 0x004
	unsigned char m_pad008[0x080 - 0x008];
	Drawable *m_drawable;                    // 0x080
	unsigned char m_pad084[0x110 - 0x084];
	ModelConditionFlags m_modelConditionFlags; // 0x110 .. 0x138
	unsigned char m_pad138[0x204 - 0x138];
	AIUpdateInterface *m_ai;                 // 0x204
	PhysicsBehavior *m_physics;              // 0x208
};

static __forceinline void setModelCondition(Object *object, Int bit)
{
	if (!object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.set(bit);

		Drawable *drawable = object->m_drawable;
		if (drawable)
			drawable->replaceModelConditionState(object->m_modelConditionFlags, 0, 0);

		AIUpdateInterface *ai = object->m_ai;
		if (ai)
			ai->AIUpdateInterface::friend_notifyStateMachineChanged();
	}
}

// Word 3 of the 320-bit field is Object+0x11c and retail sets its bit 24.
enum Rva001C7CF0ModelCondition
{
	BFME_MODELCONDITION_BIT120 = 120
};

static const char *const theRockNames[3] =
{
	"NONE",
	"CATAPULT_ROCK",
	"TREBUCHET_ROCK"
};

void Object::rva001C7CF0(Real angleDegrees,
	Real magnitude, Real verticalScale, const AsciiString &rockName)
{
	PhysicsBehavior *physics = m_physics;
	if (!physics)
		return;
	if (physics->m_byte5C)
		return;

	const ThingTemplate *tmpl = m_template;
	if (tmpl && tmpl->m_nextOverride)
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if (tmpl->m_byte4B0)
		return;

	angleDegrees *= 0.017453292f;
	Coord3D force;
	force.x = (Real)cos(angleDegrees);
	force.y = (Real)sin(angleDegrees);
	force.x *= magnitude;
	force.y *= magnitude;
	force.z = magnitude * verticalScale;
	physics->applyMotiveForce(&force);
	physics->rva0029A6A0(true);

	setModelCondition(this, BFME_MODELCONDITION_BIT120);

	AIUpdateInterface *ai = m_ai;
	if (ai)
		ai->vtableSlot224();

	Int index = 0;
	for (Int i = 0; i < 3; ++i)
	{
		if (((const StringBase<char> *)&rockName)->compare(theRockNames[i]) == 0)
		{
			index = i;
			break;
		}
	}

	Drawable *drawable = m_drawable;
	if (drawable)
		drawable->m_int2EC = index;
}
