// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// AIUpdateInterface::loadPostProcess -- retail RVA 0027A5E0, 348 bytes.
// Identity: AIUpdateInterface ctor/dtor install vtable VA 010BA8A8; slot 1
// routes through ILT 00029CD5 to this body (installers 0027F523 / 0027EF81).
// The Zero Hour AIUpdate.cpp loadPostProcess twin at line 5241 has the same
// base call, locomotor reset/dispatch, and stationary/moving goal branches.
// BFME additionally resolves the saved attack-info string and calls 002E4030.
// Full ABI/layout evidence: docs/analysis/0x003e9720.md, especially the
// 0027A5E0 neighbour row. All pointers/offsets below are independently read
// by this retail body; no complete Object/AI layout is claimed.
//
// The name oracle reports m_attitude at AIUpdateInterface+1F4, but retail
// +0007..002A treats that dword as an AsciiString header pointer, checks its
// 16-bit length at +4, and passes the field by reference to getAttackInfo.
// The explicit PostLoadFields0027A5E0 view preserves this conflict without
// assigning an unsupported original field name or changing shared layouts.
// +1D0 is the witnessed m_curLocomotorSet; primary vslot 127 is
// chooseLocomotorSet (AIUpdateInterfaceHelpers.cpp / pristine EA slot order).
//
// Address-only routes retain their established ABI without inventing names:
// 00278830: ECX=AIUpdateInterface, no args, AL predicate, plain ret.
// 001BEC40: ECX=Object, one int, writes Object+314, ret 4.
// 002E4030: ECX=owner singleton at VA 012F060C, Object argument, ret 4.
// Object::getLayer (ILT 0003A391 -> 001BEC20) returns int EAX, plain ret.
// Pathfinder methods use ECX=TheAI+0C pointee: removeGoal/removePos ret 4;
// updatePos ret 8; updateGoal ret 14h. The hub reads only Coord3D.x/y.
// Keep the final owner call OUTSIDE the if/else: VC7.1 then restores EBX
// before that call in the stationary arm, exactly as retail does at +00C4.

#include "ascii_string.h"

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
	int getLayer() const;
	char m_pad00[0x38];
	Coord3D m_pos38;
	char m_pad44[0x9c - 0x44];
	int m_field9c;
	int m_field0a0;
};

struct RawPtrField
{
	void *value;
};

class AttackPriorityInfo;

class ScriptEngine
{
public:
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

extern void j_00015e0b();
extern void j_00044774();

class Pathfinder
{
public:
	void removeGoal(Object *obj);
	void updateGoal(Object *obj, const Coord3D *pos, int layer, const char *file, int line);
	void removePos(Object *obj);
	void updatePos(Object *obj, const Coord3D *pos);
};

extern void j_0000cb3f();

class AI
{
public:
	char m_pad00[0xc];
	void *m_pathfinderRaw;
};

extern AI *TheAI;

class Owner002E4030
{
};

extern Owner002E4030 *g_owner002E4030;
extern void j_000143d0();

struct PostLoadFields0027A5E0
{
	void *m_vtable;
	char m_pad00[0x8 - 4];
	Object *m_object;                  // +0x8
	char m_pad0c[0x70 - 0xc];
	const AttackPriorityInfo *m_attackInfo; // +0x70
	char m_pad74[0x1d0 - 0x74];
	int m_curLocomotorSet;             // +0x1d0
	char m_pad1d4[0x1f4 - 0x1d4];
	RawPtrField m_string1f4;           // +0x1f4
};

class AIUpdateInterface
{
private:
#define AIUI_UNUSED_SLOT(n) virtual void unused##n() = 0;
	AIUI_UNUSED_SLOT(000)
protected:
	virtual void loadPostProcess();
private:
	AIUI_UNUSED_SLOT(002) AIUI_UNUSED_SLOT(003)
	AIUI_UNUSED_SLOT(004) AIUI_UNUSED_SLOT(005) AIUI_UNUSED_SLOT(006) AIUI_UNUSED_SLOT(007)
	AIUI_UNUSED_SLOT(008) AIUI_UNUSED_SLOT(009) AIUI_UNUSED_SLOT(010) AIUI_UNUSED_SLOT(011)
	AIUI_UNUSED_SLOT(012) AIUI_UNUSED_SLOT(013) AIUI_UNUSED_SLOT(014) AIUI_UNUSED_SLOT(015)
	AIUI_UNUSED_SLOT(016) AIUI_UNUSED_SLOT(017) AIUI_UNUSED_SLOT(018) AIUI_UNUSED_SLOT(019)
	AIUI_UNUSED_SLOT(020) AIUI_UNUSED_SLOT(021) AIUI_UNUSED_SLOT(022) AIUI_UNUSED_SLOT(023)
	AIUI_UNUSED_SLOT(024) AIUI_UNUSED_SLOT(025) AIUI_UNUSED_SLOT(026) AIUI_UNUSED_SLOT(027)
	AIUI_UNUSED_SLOT(028) AIUI_UNUSED_SLOT(029) AIUI_UNUSED_SLOT(030) AIUI_UNUSED_SLOT(031)
	AIUI_UNUSED_SLOT(032) AIUI_UNUSED_SLOT(033) AIUI_UNUSED_SLOT(034) AIUI_UNUSED_SLOT(035)
	AIUI_UNUSED_SLOT(036) AIUI_UNUSED_SLOT(037) AIUI_UNUSED_SLOT(038) AIUI_UNUSED_SLOT(039)
	AIUI_UNUSED_SLOT(040) AIUI_UNUSED_SLOT(041) AIUI_UNUSED_SLOT(042) AIUI_UNUSED_SLOT(043)
	AIUI_UNUSED_SLOT(044) AIUI_UNUSED_SLOT(045) AIUI_UNUSED_SLOT(046) AIUI_UNUSED_SLOT(047)
	AIUI_UNUSED_SLOT(048) AIUI_UNUSED_SLOT(049) AIUI_UNUSED_SLOT(050) AIUI_UNUSED_SLOT(051)
	AIUI_UNUSED_SLOT(052) AIUI_UNUSED_SLOT(053) AIUI_UNUSED_SLOT(054) AIUI_UNUSED_SLOT(055)
	AIUI_UNUSED_SLOT(056) AIUI_UNUSED_SLOT(057) AIUI_UNUSED_SLOT(058) AIUI_UNUSED_SLOT(059)
	AIUI_UNUSED_SLOT(060) AIUI_UNUSED_SLOT(061) AIUI_UNUSED_SLOT(062) AIUI_UNUSED_SLOT(063)
	AIUI_UNUSED_SLOT(064) AIUI_UNUSED_SLOT(065) AIUI_UNUSED_SLOT(066) AIUI_UNUSED_SLOT(067)
	AIUI_UNUSED_SLOT(068) AIUI_UNUSED_SLOT(069) AIUI_UNUSED_SLOT(070) AIUI_UNUSED_SLOT(071)
	AIUI_UNUSED_SLOT(072) AIUI_UNUSED_SLOT(073) AIUI_UNUSED_SLOT(074) AIUI_UNUSED_SLOT(075)
	AIUI_UNUSED_SLOT(076) AIUI_UNUSED_SLOT(077) AIUI_UNUSED_SLOT(078) AIUI_UNUSED_SLOT(079)
	AIUI_UNUSED_SLOT(080) AIUI_UNUSED_SLOT(081) AIUI_UNUSED_SLOT(082) AIUI_UNUSED_SLOT(083)
	AIUI_UNUSED_SLOT(084) AIUI_UNUSED_SLOT(085) AIUI_UNUSED_SLOT(086) AIUI_UNUSED_SLOT(087)
	AIUI_UNUSED_SLOT(088) AIUI_UNUSED_SLOT(089) AIUI_UNUSED_SLOT(090) AIUI_UNUSED_SLOT(091)
	AIUI_UNUSED_SLOT(092) AIUI_UNUSED_SLOT(093) AIUI_UNUSED_SLOT(094) AIUI_UNUSED_SLOT(095)
	AIUI_UNUSED_SLOT(096) AIUI_UNUSED_SLOT(097) AIUI_UNUSED_SLOT(098) AIUI_UNUSED_SLOT(099)
	AIUI_UNUSED_SLOT(100) AIUI_UNUSED_SLOT(101) AIUI_UNUSED_SLOT(102) AIUI_UNUSED_SLOT(103)
	AIUI_UNUSED_SLOT(104) AIUI_UNUSED_SLOT(105) AIUI_UNUSED_SLOT(106) AIUI_UNUSED_SLOT(107)
	AIUI_UNUSED_SLOT(108) AIUI_UNUSED_SLOT(109) AIUI_UNUSED_SLOT(110) AIUI_UNUSED_SLOT(111)
	AIUI_UNUSED_SLOT(112) AIUI_UNUSED_SLOT(113) AIUI_UNUSED_SLOT(114) AIUI_UNUSED_SLOT(115)
	AIUI_UNUSED_SLOT(116) AIUI_UNUSED_SLOT(117) AIUI_UNUSED_SLOT(118) AIUI_UNUSED_SLOT(119)
	AIUI_UNUSED_SLOT(120) AIUI_UNUSED_SLOT(121) AIUI_UNUSED_SLOT(122) AIUI_UNUSED_SLOT(123)
	AIUI_UNUSED_SLOT(124) AIUI_UNUSED_SLOT(125) AIUI_UNUSED_SLOT(126)
	virtual void chooseLocomotorSet(int id) = 0;
#undef AIUI_UNUSED_SLOT
};

void AIUpdateInterface::loadPostProcess()
{
	PostLoadFields0027A5E0 *fields = reinterpret_cast<PostLoadFields0027A5E0 *>(this);
	if (fields->m_string1f4.value &&
		*reinterpret_cast<short *>(static_cast<char *>(fields->m_string1f4.value) + 4) != 0)
	{
		fields->m_attackInfo = TheScriptEngine->getAttackInfo(
			*reinterpret_cast<const AsciiString *>(&fields->m_string1f4));
	}

	// UpdateModule::loadPostProcess route: ILT -> 002B2070 -> 0004049E -> 001EF410.
	typedef void (AIUpdateInterface::*BaseCall)();
	union { void (*function)(); BaseCall member; } baseRoute;
	baseRoute.function = j_00015e0b;
	(this->*baseRoute.member)();

	if (fields->m_curLocomotorSet != -1)
	{
		int savedSet = fields->m_curLocomotorSet;
		fields->m_curLocomotorSet = -1;
		chooseLocomotorSet(savedSet);
	}

	Object *object = fields->m_object;

	// The 00278830 predicate returns AL and has no stack arguments.
	typedef bool (AIUpdateInterface::*PredicateCall)();
	union { void (*function)(); PredicateCall member; } predicateRoute;
	predicateRoute.function = j_00044774;
	if (!(this->*predicateRoute.member)())
	{
		int layer = object->getLayer();

		reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->removeGoal(object);
		{
			Coord3D *posPtr = &object->m_pos38;
			reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->updateGoal(
				object, posPtr, layer,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x20eb);
			reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->removePos(object);
			reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->updatePos(object, posPtr);
		}

		{
			typedef void (Object::*LayerStoreCall)(int);
			typedef void (__cdecl *LayerStoreRoute)();
			union { LayerStoreRoute function; LayerStoreCall member; } layerRoute;
			layerRoute.function = j_0000cb3f;
			(object->*layerRoute.member)(layer);
		}
	}
	else
	{
		int field9c = object->m_field9c;
		int field0a0 = object->m_field0a0;
		if (field9c >= 0 && field0a0 >= 0)
		{
			Coord3D pos;
			pos.x = static_cast<float>((field9c * 5) << 1) + 5.0f;
			pos.y = static_cast<float>((field0a0 * 5) << 1) + 5.0f;

			reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->removeGoal(object);

			void *pathfinderForGoal = TheAI->m_pathfinderRaw;

			reinterpret_cast<Pathfinder *>(pathfinderForGoal)->updateGoal(
				object, &pos, object->getLayer(),
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x20f6);
		}
	}

	typedef void (Owner002E4030::*OwnerCall)(Object *);
	union { void (*function)(); OwnerCall member; } ownerRoute;
	ownerRoute.function = j_000143d0;
	(g_owner002E4030->*ownerRoute.member)(object);
}
