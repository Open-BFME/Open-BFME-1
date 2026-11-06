// ?method@Rva0016F4F0@@QAEXPAVObject@@0PAVAIUpdateInterface@@@Z
// cl: /DNDEBUG /MD /Igame/Libraries/Include
//
// Retail RVA 0x0016F4F0, 243 bytes, ret 0x0C at +0xF0 then INT3. The matched
// AIChargeTargetState::update (0x00185060) calls it through ILT 0x000126F7
// with this, the source and victim Objects and the source's
// AIUpdateInterface; nothing names the method, so it keeps the address name.
// Aims 50 units past the victim along the source->victim direction, fires
// slot 14 of the +0x1C object, removes the source's pathfinder goal
// (Pathfinder::removeGoal, ILT 0x00015D02), clears +0x4C, records the point
// at +0x24 and requests a final path (AIUpdateInterface::requestPath, ILT
// 0x0003BCFF).
//
// Shape: the memberwise Coord3D copy / three-field sub / accumulated
// z-y-x length idiom of Rva0016F150 (BFME 2 donor rva00344D60). Retail reads
// 50.0f from 0x010977EC, a TU-local constant object referenced only here
// (__real@42480000 is 0x0107FAA8), so it is a file-static const.
#include <math.h>
#include "Lib/Coord3D.h"

struct MemberwiseCoord3D : public Coord3D
{
	MemberwiseCoord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	void add(const Coord3D *p) { x += p->x; y += p->y; z += p->z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
	float GetLength() const { float a = z * z; a += y * y; a += x * x; return (float)sqrt(a); }
	float Normalize() { float len = GetLength(); float inv = 1.0f / len; x *= inv; y *= inv; z *= inv; return len; }
};

typedef bool Bool;

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	char m_unreconstructed000[0x38];
	Coord3D m_position;
};

class Pathfinder
{
public:
	void removeGoal(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

	char m_unreconstructed00[0x0c];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

// Retail .rdata 0x010977EC (50.0f), referenced only by this body.
static const float s_Rva010977EC = 50.0f;

extern void j_0003bcff();

class AIUpdateInterface
{
public:
	void requestPath(Coord3D *destination, Bool isFinalGoal)
	{
		typedef void (AIUpdateInterface::*Fn)(Coord3D *, Bool);
		union { void (*raw)(); Fn fn; } u;
		u.raw = j_0003bcff;
		(this->*u.fn)(destination, isFinalGoal);
	}
};

class Rva0016F4F0Callback
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(int);
};

class Rva0016F4F0
{
public:
	void method(Object *origin, Object *target, AIUpdateInterface *ai);

	char m_unreconstructed00[0x1C];
	Rva0016F4F0Callback *m_callback1C;
	char m_unreconstructed20[4];
	Coord3D m_position24;
	char m_unreconstructed30[0x1C];
	unsigned char m_flag4C;
};

void Rva0016F4F0::method(Object *origin, Object *target, AIUpdateInterface *ai)
{
	if (target == 0)
		return;
	MemberwiseCoord3D destination(*target->getPosition());
	destination.sub(origin->getPosition());
	destination.Normalize();
	destination.scale(s_Rva010977EC);
	destination.add(target->getPosition());
	m_callback1C->slot38(0);
	TheAI->pathfinder()->removeGoal(origin);
	m_flag4C = 0;
	m_position24 = destination;
	ai->requestPath(&destination, true);
}
