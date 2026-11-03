// ?method@Rva00287410Owner@@UAEXPAVObject@@W4CommandSourceType@@@Z
// partial score=0.0 date=2026-11-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail 0x00287410 (346 B, ret 8): slot 0 of the vtable 0x010BC684 that
// ??0SmartBombTargetHomingUpdate (0x00286F80) installs at +0x20, so the body is
// entered with ECX at that interface and reaches the module's object through
// [ecx-0x18]. The method name is unproven; the class keeps the address. The
// ledger had pinned two destructor names on this extent, which the retail
// body (two stack arguments, no teardown) refutes.

#include <list>

typedef bool Bool;

#include "../../command_source_type.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
	const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS \
	void setStatusBit(Int bit, Bool set); \
	void unidentified_000F20F0(Int index, Int value);

class AIUpdateInterface;

#include "../object.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiForceAttackObject(Object *victim, Int maxShots,
		CommandSourceType commandSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;
};

// 0x001CB020 is defined as BfmeObjAS::bfmeParentAS (RvaC4390Second_resolve.cpp).
class BfmeObjAS
{
public:
	BfmeObjAS *bfmeParentAS(Int index);
};

struct RvaC4390Interface
{
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void setObjectID(Int id) = 0;		// +0x14
	virtual void slot18() = 0;
	virtual Int isBusy() = 0;					// +0x1C
};

class RvaC4390First
{
public:
	RvaC4390Interface *getInterface();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CommandXlat.h
class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	Int m_specialPowerType;
	Coord3D m_position;
	UnsignedInt m_commandButton;
};

typedef _STL::list<Drawable *> DrawableList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
		MSG_RVA00287410_VOICE = 0x7E9
	};
};

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class Rva00287410Module
{
public:
	virtual void slot00();

	void *m_unmodelled04;
	Object *m_object;							// +0x08
	char m_unmodelled0C[0x14];
};

class Rva00287410Interface
{
public:
	virtual void method(Object *target, CommandSourceType commandSource) = 0;
};

class Rva00287410Owner : public Rva00287410Module, public Rva00287410Interface
{
public:
	virtual void method(Object *target, CommandSourceType commandSource);

	Int m_targetID;								// +0x24
};

void Rva00287410Owner::method(Object *target, CommandSourceType commandSource)
{
	Object *object = m_object;
	if (!target || !object)
		return;

	Object *parent = (Object *)((BfmeObjAS *)target)->bfmeParentAS(0);
	if (!parent)
		return;

	RvaC4390Interface *iface = ((RvaC4390First *)parent)->getInterface();
	if (!iface || iface->isBusy())
		return;

	// The block (not an early return) keeps the list's scope over target's
	// last use, so MSVC leaves the list in the frame (sharing the spilled this
	// slot) instead of target's dead argument home, as retail does.
	AIUpdateInterface *ai = object->m_ai;
	if (ai)
	{
		Int parentID = parent->m_id;
		m_targetID = parentID;
		Int id = object->m_id;
		iface->setObjectID(id);
		ai->m_commands.aiForceAttackObject(target, 0x7fffffff, commandSource);
		object->unidentified_000F20F0(0x40, 1);
		parent->setStatusBit(0x49, true);
		parent->unidentified_000F20F0(0x49, 1);

		PickAndPlayInfo info;
		info.m_position = *parent->getPosition();
		info.m_drawTarget = parent->getDrawable();

		DrawableList list;
		list.push_back(object->getDrawable());
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_RVA00287410_VOICE, &info);
	}
}
