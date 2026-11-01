// ?run@Rva00235150@@QAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z
// partial score=0.9331 date=2026-11-01
// cl: /DNDEBUG /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Include
// stlport
//
// Retail RVA 0x00235150: 299 bytes, ret 0x10, no EH.  Body of slot 101 of
// the +0xE4 interface subobject shared by the AODHordeContain (0x010AE230),
// 0x010AED58 and 0x010B07E0 interface tables (ILT 0x000317AF), so it is a
// base-class override reached with this = module+0xE4.  The method name is
// unproven; the address-derived name stays.
// For every member of the module's +0x38 Object list it asks interface
// slot 7 for the member's formation position (the same call
// BfmeAODHordeContainOwner::updateFormationMembers makes), takes the owning
// Object's position (averaged with the destination unless the layer is
// LAYER_GROUND), lets the pathfinder adjust the member position
// (ILT 0x000392CA -> 0x003E5010, Object*, Coord3D*, owner, bool, ret 16) and
// builds the member's path through AIUpdateInterface::buildPath_00271010.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "Lib/Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class AIUpdateInterface
{
public:
	void buildPath_00271010(const Coord3D *from, const Coord3D *to, Int cost,
		PathfindLayerEnum layer, const Coord3D *via, const Coord3D *goal);
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	char m_unreconstructed000[0x38];
	Coord3D m_position;
	char m_unreconstructed044[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class Pathfinder;
class AI
{
public:
	char m_unreconstructed00[0x0c];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class Rva00235150Call {};
typedef void (Rva00235150Call::*Adjust)(Object *member,
	Coord3D *position, Object *owner, Bool flag);
extern void j_000392ca();

class Rva00235150Module
{
public:
	void *m_vptr;
	void *m_moduleData;
	Object *m_object;
	char m_unreconstructed00c[0x38 - 0x0c];
	_STL::list<Object *> m_members;
};

template<int N> class Rva00235150Slots : public Rva00235150Slots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template<> class Rva00235150Slots<0> {};

class Rva00235150 : public Rva00235150Slots<7>
{
public:
	virtual Coord3D memberPosition(Object *member, Real *angle) = 0;

	void run(const Coord3D *from, const Coord3D *to, Int cost,
		PathfindLayerEnum layer);

	Rva00235150Module *module() { return (Rva00235150Module *)((char *)this - 0xe4); }
};

// ?run@Rva00235150@@QAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z
void Rva00235150::run(const Coord3D *from, const Coord3D *to, Int cost,
	PathfindLayerEnum layer)
{
	Object *volatile owner = module()->m_object;
	for (_STL::list<Object *>::iterator it = module()->m_members.begin();
		it != module()->m_members.end(); ++it)
	{
		Object *member = *it;
		if (member == 0)
			continue;

		AIUpdateInterface *ai = member->getAI();
		Real angle = 0.0f;
		Coord3D goal;
		goal = memberPosition(member, &angle);
		Coord3D via = *owner->getPosition();
		if (layer != LAYER_GROUND)
		{
			via.x += to->x;
			via.y += to->y;
			via.z += to->z;
			via.x *= 0.5f;
			via.y *= 0.5f;
			via.z *= 0.5f;
		}

		union { void (*raw)(); Adjust call; } adjust = { j_000392ca };
		(((Rva00235150Call *)TheAI->m_pathfinder)->*adjust.call)(member, &goal,
			owner, false);
		ai->buildPath_00271010(from, to, cost, layer, &via, &goal);
	}
}
