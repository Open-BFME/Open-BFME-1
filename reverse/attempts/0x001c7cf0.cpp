// ?rva001C7CF0@Object@@QAEXMMMABVAsciiString@@@Z
// partial score=0.75 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// BFME Object launch-force helper. Retail 0x001C7CF0, 295 bytes.
// The body proves its own contents: it reads the physics module at Object+0x208
// (m_physics), bails on the byte at PhysicsBehavior+0x5c, resolves the template
// override chain through the matched Overridable::getFinalOverride (0x00087A80
// via ILT 0x000022BB), bails on ThingTemplate+0x4b0, then builds a Coord3D from
// a degrees-to-radians scale (g_01075954 == PI/180) and hands it to the pinned
// PhysicsBehavior::applyMotiveForce (0x0029AC40 via ILT 0x0002A284). It then
// sets bit 0x01000000 of the ModelConditionFlags word at Object+0x11c, pushes
// the flags at Object+0x110 into Drawable::replaceModelConditionState
// (0x0041CCD0 via ILT 0x0001343F), notifies the AIUpdateInterface at
// Object+0x204 and calls its vtable slot +0x224, and finally maps the incoming
// AsciiString against the literal table at 0x012AD04C
// { "NONE", "CATAPULT_ROCK", "TREBUCHET_ROCK" } and stores the winning index at
// Drawable+0x2ec.
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

class ModelConditionFlags
{
public:
	unsigned int m_bits[4];
};

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
	void **m_vtable;                         // 0x000
	unsigned char m_pad004[0x224 - 0x004];

	void friend_notifyStateMachineChanged();

	void vtableSlot224()
	{
		typedef void (__fastcall *Slot)(AIUpdateInterface *);
		((Slot)m_vtable[0x224 / 4])(this);
	}
};

class Object
{
public:
	void rva001C7CF0(Real angleDegrees, Real magnitude,
		Real verticalScale, const AsciiString &rockName);

private:
	unsigned char m_pad000[0x004];
	ThingTemplate *m_template;               // 0x004
	unsigned char m_pad008[0x080 - 0x008];
	Drawable *m_drawable;                    // 0x080
	unsigned char m_pad084[0x110 - 0x084];
	ModelConditionFlags m_conditionFlags;    // 0x110
	unsigned char m_pad120[0x204 - 0x120];
	AIUpdateInterface *m_ai;                 // 0x204
	PhysicsBehavior *m_physics;              // 0x208
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

	if ((m_conditionFlags.m_bits[3] & 0x01000000) == 0)
	{
		m_conditionFlags.m_bits[3] |= 0x01000000;
		Drawable *drawable = m_drawable;
		if (drawable)
			drawable->replaceModelConditionState(m_conditionFlags, 0, 0);
		AIUpdateInterface *ai = m_ai;
		if (ai)
			ai->friend_notifyStateMachineChanged();
	}

	AIUpdateInterface *ai = m_ai;
	if (ai)
		ai->vtableSlot224();

	Int index = 0;
	for (Int i = 0; i < 3; ++i)
	{
		if (rockName.compare(theRockNames[i]) == 0)
		{
			index = i;
			break;
		}
	}

	Drawable *drawable = m_drawable;
	if (drawable)
		drawable->m_int2EC = index;
}
