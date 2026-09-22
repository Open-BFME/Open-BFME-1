// ?d_0027a5e0@@YAXXZ
// partial score=0.99 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AIUpdateInterface method at retail 0x0027A5E0 (348 bytes). Identity
// is proven by a DIR32 string literal the body passes to updateGoal() as a
// debug __FILE__ argument: "F:\bfme\Code\gameengine\Source\GameLogic\Object\
// Update\AIUpdate." (verified against the retail .rdata bytes at 0x010B97D8),
// matching AIUpdateInterface's own home file. The real method name is not
// proven (no caller or vtable slot names it), so it keeps the address token.
//
// Body: if this->m_attackInfoName (+0x1F4) is set and non-empty, looks up
// this->m_attackInfo (+0x70) via ScriptEngine::getAttackInfo. Calls a base
// helper (bfmeBase987), then, if a pending id (+0x1D0) is not -1, resets it
// and dispatches vtable slot 0x1FC with the saved id. Reads the owned Object
// at +0x8 and asks bfmeBlocksFormationRefresh(): when false, queries a scale
// value from the object, notifies TheAI's pathfinder-slot object, calls
// updateGoal/removePos/updatePos on it, and assigns a held reference; when
// true, computes a scaled/offset Coord3D from the object's +0x9C/+0xA0 ints
// and a shared constant, then calls updateGoal with a different reason code
// and skips the held-reference assignment.

typedef int Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
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

class AsciiString
{
};

class AttackPriorityInfo;

class ScriptEngine
{
public:
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

class BfmeA987
{
public:
	void bfmeBase987();
};

class BfmeHordeMember
{
public:
	bool bfmeBlocksFormationRefresh();
};

class BfmeHolderNS
{
public:
	int bfmeQueryNS();
};

class BfmeItemGK;

class BfmeAgentGK
{
public:
	void bfmeNoteGK(BfmeItemGK *item);
};

class BfmeIdlePathfinder
{
public:
	void updateGoal(Object *obj, const Coord3D *pos, int reason, const char *file, int line);
};

class Pathfinder
{
public:
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

class BfmeOwnerBR
{
};

extern BfmeOwnerBR *g_bfmeOwnerBR;
extern void j_000143d0();

extern const float g_bfmeK1266C;

class AIUpdateInterface
{
public:
	void rva0027a5e0();

private:
	char m_pad00[0x8 - 4];
	Object *m_object;                  // +0x8
	char m_pad0c[0x70 - 0xc];
	const AttackPriorityInfo *m_attackInfo; // +0x70
	char m_pad74[0x1d0 - 0x74];
	int m_pendingId;                   // +0x1d0
	char m_pad1d4[0x1f4 - 0x1d4];
	RawPtrField m_attackInfoName;      // +0x1f4

#define AIUI_UNUSED_SLOT(n) virtual void unused##n() = 0;
	AIUI_UNUSED_SLOT(000) AIUI_UNUSED_SLOT(001) AIUI_UNUSED_SLOT(002) AIUI_UNUSED_SLOT(003)
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
	virtual void dispatchPendingId(int id) = 0;
#undef AIUI_UNUSED_SLOT
};

void AIUpdateInterface::rva0027a5e0()
{
	if (m_attackInfoName.value &&
		*reinterpret_cast<short *>(static_cast<char *>(m_attackInfoName.value) + 4) != 0)
	{
		m_attackInfo = TheScriptEngine->getAttackInfo(
			*reinterpret_cast<const AsciiString *>(&m_attackInfoName));
	}

	reinterpret_cast<BfmeA987 *>(this)->bfmeBase987();

	if (m_pendingId != -1)
	{
		int pending = m_pendingId;
		m_pendingId = -1;
		dispatchPendingId(pending);
	}

	Object *object = m_object;

	if (!reinterpret_cast<BfmeHordeMember *>(this)->bfmeBlocksFormationRefresh())
	{
		int scale = reinterpret_cast<BfmeHolderNS *>(object)->bfmeQueryNS();

		reinterpret_cast<BfmeAgentGK *>(TheAI->m_pathfinderRaw)->bfmeNoteGK(
			reinterpret_cast<BfmeItemGK *>(object));
		{
			Coord3D *posPtr = &object->m_pos38;
			reinterpret_cast<BfmeIdlePathfinder *>(TheAI->m_pathfinderRaw)->updateGoal(
				object, posPtr, scale,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x20eb);
			reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->removePos(object);
			reinterpret_cast<Pathfinder *>(TheAI->m_pathfinderRaw)->updatePos(object, posPtr);
		}

		{
			typedef void (Object::*RefAssignRaw)(int);
			typedef void (__cdecl *RefAssignFn)();
			union { RefAssignFn function; RefAssignRaw member; } refRoute;
			refRoute.function = j_0000cb3f;
			(object->*refRoute.member)(scale);
		}

		typedef void (BfmeOwnerBR::*OwnerAssignRaw)(Object *);
		typedef void (__cdecl *OwnerAssignFn)();
		union { OwnerAssignFn function; OwnerAssignRaw member; } ownerRoute;
		ownerRoute.function = j_000143d0;
		(g_bfmeOwnerBR->*ownerRoute.member)(object);

		return;
	}

	int field9c = object->m_field9c;
	int field0a0 = object->m_field0a0;
	if (field9c >= 0 && field0a0 >= 0)
	{
		Coord3D pos;
		pos.x = static_cast<float>((field9c * 5) << 1) + g_bfmeK1266C;
		pos.y = static_cast<float>((field0a0 * 5) << 1) + g_bfmeK1266C;

		reinterpret_cast<BfmeAgentGK *>(TheAI->m_pathfinderRaw)->bfmeNoteGK(
			reinterpret_cast<BfmeItemGK *>(object));

		void *pathfinderForGoal = TheAI->m_pathfinderRaw;

		reinterpret_cast<BfmeIdlePathfinder *>(pathfinderForGoal)->updateGoal(
			object, &pos, reinterpret_cast<BfmeHolderNS *>(object)->bfmeQueryNS(),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x20f6);
	}

	typedef void (BfmeOwnerBR::*OwnerAssignRaw2)(Object *);
	typedef void (__cdecl *OwnerAssignFn2)();
	union { OwnerAssignFn2 function; OwnerAssignRaw2 member; } ownerRoute2;
	ownerRoute2.function = j_000143d0;
	(g_bfmeOwnerBR->*ownerRoute2.member)(object);
}
