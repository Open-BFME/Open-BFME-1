// ?d_00234e60@@YAXXZ
// partial score=0.6 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep
// stlport
// Open-BFME: address-derived HordeContain formation refresh body, retail 0x00234E60.

#define _STLP_USE_NEWALLOC 1
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NAMESPACES 1
#include <list>
#include <math.h>
#include "coord.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;
class LocomotorSet;

template <int N>
class Rva00234E60VirtualSlots : public Rva00234E60VirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva00234E60VirtualSlots<0>
{
};

class Rva00234E60AIUpdate
	: public Rva00234E60VirtualSlots<97>
{
public:
	virtual Bool slot97() = 0;
	Bool bfmeBlocksFormationRefresh();

	LocomotorSet *getLocomotorSet() const
	{
		return *(LocomotorSet **)((const char *)this + 0x1a8);
	}
};

class Rva00234E60Thing
{
public:
	void setPosition(const Coord3D *position);
};

class Object : public Rva00234E60Thing
{
public:
	char m_head[0x38];
	Coord3D m_position;
	char m_tail[0x1c0];
	Rva00234E60AIUpdate *m_ai;

	int getLayer() const;
};

class Pathfinder
{
public:
	void removeGoal(Object *object);
	Bool adjustDestination(Object *object, const LocomotorSet &locomotors,
		Coord3D *destination, const Coord3D *groupDestination);
	void updateGoal(Object *object, const Coord3D *destination, int layer,
		const char *file, int line);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

	char m_head[0x0c];
	Pathfinder *m_pathfinder;
};

class BfmeGameLogic
{
public:
	char m_head[0x3c];
	UnsignedInt m_frame;
};

#define TheAI (*(AI **)0x012EF214)
#define TheBfmeGameLogic (*(BfmeGameLogic **)0x012F0898)

class __declspec(novtable) Rva00234E60HordeContainView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void updateMemberGoal(Coord3D *goal, Object *member,
		int *state) = 0;
};

class Rva00234E60OpenContain
{
public:
	virtual void slot00() = 0;

	char m_pad04[4];
	Object *m_owner;
	char m_pad0c[0x2c];
	_STL::list<Object *> m_members;
	char m_pad3c[0xa8];
};

class Rva00234E60HordeContain
	: public Rva00234E60OpenContain,
	  public Rva00234E60HordeContainView
{
public:
	void rva00234E60();

private:
	unsigned char m_flagE8;
	unsigned char m_flagE9;
	unsigned char m_padEA[0x102];
	UnsignedInt m_refreshFrame;
	unsigned char m_refreshPending;
};

#pragma comment(linker, "/alternatename:?setPosition@Rva00234E60Thing@@QAEXPBUCoord3D@@@Z=?setPosition@Thing@@QAEXPBUCoord3D@@@Z")
#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@PBU4@@Z=?j_00027ffc@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeBlocksFormationRefresh@Rva00234E60AIUpdate@@QAE_NXZ=?j_00044774@@YAXXZ")

void Rva00234E60HordeContain::rva00234E60()
{
	register Object *owner = m_owner;
	register Rva00234E60HordeContain *self = this;
	register Rva00234E60AIUpdate *ai = owner->m_ai;
	if (ai->slot97())
	{
		self->m_refreshFrame = TheBfmeGameLogic->m_frame;
		return;
	}

	if (!self->m_refreshPending)
		return;

	if (self->m_refreshFrame + 0xf >= TheBfmeGameLogic->m_frame)
		return;

	Bool enabled = true;
	self->m_refreshPending = 0;
	self->m_flagE9 = enabled;
	if (ai->bfmeBlocksFormationRefresh())
		return;
	self->m_flagE8 = enabled;

	Coord3D destination = owner->m_position;
	for (_STL::list<Object *>::iterator it = self->m_members.begin();
		it != self->m_members.end(); ++it)
	{
		Object *member = *it;
		AI *gameAI = TheAI;
		Pathfinder *pathfinder = gameAI->m_pathfinder;
		pathfinder->removeGoal(member);
	}

	TheAI->pathfinder()->adjustDestination(owner, *ai->getLocomotorSet(),
		&destination, 0);

	Coord3D delta;
	delta.x = owner->m_position.x - destination.x;
	delta.y = owner->m_position.y - destination.y;
	delta.z = owner->m_position.z - destination.z;
	float distance = delta.length();
	if (distance > *(const float *)0x01075C74 &&
		distance < *(const float *)0x0109A028)
		owner->setPosition(&destination);

	#line 2249 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
	TheAI->pathfinder()->updateGoal(owner, &owner->m_position,
		owner->getLayer(), __FILE__, 2249);

	_STL::list<Object *>::iterator it = self->m_members.begin();
	while (it != self->m_members.end())
	{
		Object *member = *it;
		int state = 0;
		Coord3D memberGoal;
		((Rva00234E60HordeContainView *)this)->updateMemberGoal(
			&memberGoal, member, &state);
		TheAI->pathfinder()->updateGoal(member, &memberGoal,
			member->getLayer(), __FILE__, 2257);
		++it;
	}
}
