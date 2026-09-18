// ?onEnter@AIInternalMoveToStateOnEnterShim@@QAE?AW4StateReturnType@@XZ
// partial score=0.25 date=2026-09-17
// partial reconstruction for retail RVA 0x00172600, size 1524 bytes.
//
// Boundary: dis_retail.py reaches the contiguous epilogue at +0x5F3
// (ret at +0x5F3, no jump-table/data bytes inside the 0x5F4-byte extent).
// Identity: the 0x00021E27 ILT is named by the 26 derived-state callers as
// AIInternalMoveToState::onEnter; the CritterDesync format strings in this
// body name the same method.  The emitted symbol remains the row's shim name
// so this bank does not overclaim a second source owner.
//
// Proved layout/evidence used here: State::m_machine +0x1C; the AI owner at
// StateMachine+0x10; AIUpdate::m_curLocomotor +0x1CC, its locomotor-set view
// +0x1A8 and virtual slot 117 +0x1D4; Object template +0x04, position +0x38,
// id +0x74, immobile flags +0x94, model-condition words +0x110 and AI +0x204;
// state goal +0x24, ambient handle +0x40, waiting +0x4D and retry +0x4E.
// The 21 direct retail callees are retained by their printed address thunks;
// no unprinted semantic callee name is introduced.  Debug/audio/pathfinding
// control flow and all literal strings are transcribed from the retail body.
// The distance/condition interpretation is the remaining reconstruction
// assumption: the x87 max-plus-min expression selects the blah1/blah2 arms,
// while the called helper ABIs and field offsets are independently witnessed.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Rva00172600AIUpdate;
class Rva00172600Pathfinder;

class Rva00172600StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class Rva00172600Override
{
public:
	void *m_vptr;
	unsigned char m_pad04[0x1c];
	void *m_name;
};

class Rva00172600Template
{
public:
	void *m_vptr;
	Rva00172600Override *m_override;
	unsigned char m_pad08[0x18];
	void *m_name;
};

class Object
{
public:
	void *m_vptr;
	Rva00172600Template *m_template;
	unsigned char m_pad08[0x30];
	Coord3D m_position;
	unsigned char m_pad44[0x30];
	UnsignedInt m_id;
	unsigned char m_pad78[0x1c];
	UnsignedInt m_status;
	unsigned char m_pad98[0x78];
	UnsignedInt m_condition110;
	UnsignedInt m_condition114;
	unsigned char m_pad118[0xec];
	Rva00172600AIUpdate *m_ai;
};

template<int N>
class Rva00172600VirtualSlots : public Rva00172600VirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template<>
class Rva00172600VirtualSlots<0>
{
};

class Rva00172600AIUpdate : public Rva00172600VirtualSlots<117>
{
public:
	virtual void slot117() = 0;

	unsigned char m_pad004[0x1a8 - 0x04];
	unsigned char m_locomotorSet[0x24];
	void *m_curLocomotor;
	unsigned char m_pad1d0[0x31e - 0x1d0];
	Bool m_waitingForPath;
};

class Rva005A00B0AudioClient : public Rva00172600VirtualSlots<19>
{
public:
	virtual void slot19(UnsignedInt) = 0;
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Rva00172600Pathfinder *m_pathfinder;
};

struct Rva003FD060TerrainLogic
{
};

class Rva00172600StateWithComputePath
 	: public Rva00172600VirtualSlots<17>
{
public:
	virtual Bool slot17() = 0;
};

class AIInternalMoveToStateOnEnterShim
{
public:
	unsigned char m_pad00[0x1c];
	Rva00172600StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x10];
	UnsignedInt m_ambientPlayingHandle;
	UnsignedInt m_pathTimestamp;
	UnsignedInt m_blockedRepathTimestamp;
	Bool m_adjustDestinations;
	Bool m_waitingForPath;
	Bool m_tryOneMoreRepath;

	StateReturnType onEnter();
};

extern AI *TheAI;
extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern Real g_01098AD4;
extern Real g_01083B6C;

extern void j_000022bb(void);
extern void j_0000979b(void);
extern void j_0000ebab(void);
extern void j_00010109(void);
extern void j_0001246d(void);
extern void j_00012486(void);
extern void j_0001a36b(void);
extern void j_0001c26f(void);
extern void j_0001c675(void);
extern void j_0001c7e2(void);
extern void j_0002191d(void);
extern void j_00027ffc(void);
extern void j_000294e2(void);
extern void j_0002b3f0(void);
extern void j_0003251f(void);
extern void j_000333ac(void);
extern void j_00034c16(void);
extern void j_0003a17a(void);
extern void j_0003a391(void);
extern void j_00046ad3(void);
extern void j_00048ca7(void);

typedef void (__cdecl *Rva00172600DebugLogCall)(void *, const char *, ...);

// These are address-derived member-pointer adapters.  Their only purpose is
// to give MSVC 7.1 the retail thiscall ABI; every adapter is redirected to the
// exact printed j_ callee below, and the adapter spellings make no identity
// claim about those bodies.
class Rva00172600Calls
{
public:
	Rva00172600Override *rva000022bb();
	void rva0000979b();
	void rva0000ebab(Int);
	Bool rva00010109();
	void rva0001246d();
	void rva00012486();
	Int rva0001a36b();
	Bool rva0001c26f(Coord3D *, Int);
	Int rva0001c675(Object *, Coord3D *);
	void rva0001c7e2(Int);
	void rva0002191d();
	Bool rva00027ffc(Object *, void *, Coord3D *, Int);
	void rva000294e2(Object *, Coord3D *, Int);
	void rva0002b3f0();
	Bool rva0003251f(Int);
	Real rva000333ac();
	void rva00034c16(Object *, Coord3D *);
	Int rva0003a391();
	Bool rva00046ad3(Object *);
	void rva00048ca7(Real);
};

#pragma comment(linker, "/alternatename:?rva000022bb@Rva00172600Calls@@QAEPAVRva00172600Override@@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000979b@Rva00172600Calls@@QAEXXZ=?j_0000979b@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0000ebab@Rva00172600Calls@@QAEXH@Z=?j_0000ebab@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00010109@Rva00172600Calls@@QAEEXZ=?j_00010109@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001246d@Rva00172600Calls@@QAEXXZ=?j_0001246d@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00012486@Rva00172600Calls@@QAEXXZ=?j_00012486@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001a36b@Rva00172600Calls@@QAEHXZ=?j_0001a36b@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001c26f@Rva00172600Calls@@QAEEPAUCoord3D@@H@Z=?j_0001c26f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001c675@Rva00172600Calls@@QAEHPAVObject@@PAUCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001c7e2@Rva00172600Calls@@QAEXH@Z=?j_0001c7e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002191d@Rva00172600Calls@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00027ffc@Rva00172600Calls@@QAEEPAVObject@@PAXPAUCoord3D@@H@Z=?j_00027ffc@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000294e2@Rva00172600Calls@@QAEXPAVObject@@PAUCoord3D@@H@Z=?j_000294e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002b3f0@Rva00172600Calls@@QAEXXZ=?j_0002b3f0@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003251f@Rva00172600Calls@@QAEEH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000333ac@Rva00172600Calls@@QAEMXZ=?j_000333ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00034c16@Rva00172600Calls@@QAEXPAVObject@@PAUCoord3D@@@Z=?j_00034c16@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003a391@Rva00172600Calls@@QAEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00046ad3@Rva00172600Calls@@QAEEPAVObject@@@Z=?j_00046ad3@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00048ca7@Rva00172600Calls@@QAEXM@Z=?j_00048ca7@@YAXXZ")

StateReturnType AIInternalMoveToStateOnEnterShim::onEnter()
{
	if (TheAudioClientUpdate != 0 && m_ambientPlayingHandle >= 5)
	{
		TheAudioClientUpdate->slot19(m_ambientPlayingHandle);
		m_ambientPlayingHandle = 1;
	}

	Rva00172600StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;
	Rva00172600AIUpdate *ai = owner->m_ai;
	m_waitingForPath = ai->m_waitingForPath;

	if (g_012F0239 && g_012ED4FC)
	{
		Rva00172600Template *templateForLog = owner->m_template;
		if (templateForLog != 0 && templateForLog->m_override != 0)
		{
			templateForLog = (Rva00172600Template *)
			((Rva00172600Calls *)templateForLog->m_override)->rva000022bb();
		}
		const char *objectName = (const char *)0x0107388b;
		if (templateForLog != 0 && templateForLog->m_name != 0)
			objectName = (const char *)templateForLog->m_name + 8;
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098e70, objectName, owner->m_id,
			m_goalPosition.x, m_goalPosition.y, m_goalPosition.z);
	}

	if ((owner->m_status & 0x10000) != 0)
	{
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098e08);
		}
		return STATE_FAILURE;
	}

	Real locomotorDistance =
		((Rva00172600Calls *)ai)->rva000333ac();
	void *currentLocomotor = ai->m_curLocomotor;
	if (currentLocomotor != 0)
		((Rva00172600Calls *)currentLocomotor)->rva0000979b();
	m_tryOneMoreRepath = 1;
	((Rva00172600Calls *)ai)->rva0001246d();

	if (g_012F0239 && g_012ED4FC)
	{
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098d90, m_goalPosition.x,
			m_goalPosition.y, m_goalPosition.z);
	}

	Bool adjustsDestination = ((Rva00172600Calls *)this)->rva00010109();
	if (adjustsDestination)
	{
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098d38);
		}

		Rva00172600Pathfinder *pathfinder = TheAI->m_pathfinder;
		Int ignoredObstacleID =
			((Rva00172600Calls *)ai)->rva0001a36b();
		((Rva00172600Calls *)pathfinder)->rva0001c7e2(ignoredObstacleID);
		Bool adjusted = ((Rva00172600Calls *)pathfinder)->rva00027ffc(
			owner, (void *)ai->m_locomotorSet, &m_goalPosition, 0);
		if (!adjusted)
		{
			if (g_012F0239 && g_012ED4FC)
			{
				((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
					(const char *)0x01098cb0, m_goalPosition.x,
					m_goalPosition.y, m_goalPosition.z);
			}
			((Rva00172600Calls *)pathfinder)->rva00034c16(owner,
				&m_goalPosition);
			if (g_012F0239 && g_012ED4FC)
			{
				((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
					(const char *)0x01098c30, m_goalPosition.x,
					m_goalPosition.y, m_goalPosition.z);
			}
		}
		else if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098bb0, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}

		Int layer = ((Rva00172600Calls *)TheTerrainLogic)->rva0001c675(
			owner, &m_goalPosition);
		((Rva00172600Calls *)pathfinder)->rva000294e2(owner,
			&m_goalPosition, layer);
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098b38, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}
	}
	else if (g_012F0239 && g_012ED4FC)
	{
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098ad8);
	}

	Real deltaX = owner->m_position.x - m_goalPosition.x;
	Real deltaY = owner->m_position.y - m_goalPosition.y;
	if (deltaX < 0.0f)
		deltaX = -deltaX;
	if (deltaY < 0.0f)
		deltaY = -deltaY;
	Real lengthEstimate;
	if (deltaX < deltaY)
		lengthEstimate = deltaY + deltaX * g_01083B6C;
	else
		lengthEstimate = deltaX + deltaY * g_01083B6C;

	Bool startSound;
	if (lengthEstimate >= g_01098AD4)
	{
		startSound = 1;
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098a58, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}

		Bool distanceArm = false;
		if (currentLocomotor != 0 &&
			((Rva00172600Calls *)currentLocomotor)->rva00046ad3(owner))
		{
			if (m_waitingForPath ||
				locomotorDistance >= *(Real *)((unsigned char *)currentLocomotor + 0x38))
				distanceArm = true;
		}

		if (distanceArm)
		{
			if (g_012F0239 && g_012ED4FC)
			{
				((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
					(const char *)0x010989f8, m_goalPosition.x,
					m_goalPosition.y, m_goalPosition.z);
			}
			Rva00172600Pathfinder *pathfinder = TheAI->m_pathfinder;
			Int layer = ((Rva00172600Calls *)owner)->rva0003a391();
			Bool onCellTypeTwo = ((Rva00172600Calls *)pathfinder)->rva0001c26f(
				&owner->m_position, layer);
			Int condition = onCellTypeTwo ? 0x66 : 0x3c;
			UnsignedInt *conditionWord = (UnsignedInt *)
				((unsigned char *)owner + 0x110 + (condition >> 5) * 4);
			UnsignedInt conditionBit = 1u << (condition & 0x1f);
			if ((*conditionWord & conditionBit) == 0)
			{
				*conditionWord |= conditionBit;
				((Rva00172600Calls *)owner)->rva0002191d();
			}
		}
		else if (((Rva00172600Calls *)owner)->rva0003251f(0xe) &&
			((Rva00172600Calls *)owner)->rva0003251f(0x10))
		{
			if (g_012F0239 && g_012ED4FC)
			{
				((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
					(const char *)0x01098998, m_goalPosition.x,
					m_goalPosition.y, m_goalPosition.z);
			}
			UnsignedInt *conditionWord = (UnsignedInt *)
				((unsigned char *)owner + 0x114);
			if ((*conditionWord & 0x10000000) == 0)
			{
				*conditionWord |= 0x10000000;
				((Rva00172600Calls *)owner)->rva0002191d();
			}
		}
		else if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098938, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}
	}
	else
	{
		startSound = 0;
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x010988c0, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}
	}

	if (g_012F0239 && g_012ED4FC)
	{
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098850, m_goalPosition.x,
			m_goalPosition.y, m_goalPosition.z);
	}

	if (!((Rva00172600StateWithComputePath *)this)->slot17())
	{
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x010987e0, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}
		((Rva00172600Calls *)ai)->rva00012486();
		return STATE_FAILURE;
	}

	if (g_012F0239 && g_012ED4FC)
	{
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098768, m_goalPosition.x,
			m_goalPosition.y, m_goalPosition.z);
	}
	ai->slot117();
	((Rva00172600Calls *)ai)->rva0000ebab(0);
	((Rva00172600Calls *)ai)->rva00048ca7(999999.0f);
	if (startSound)
		((Rva00172600Calls *)this)->rva0002b3f0();
	return STATE_CONTINUE;
}
