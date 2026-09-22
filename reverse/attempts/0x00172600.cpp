// ?d_00172600@@YAXXZ
// partial score=0.9974 date=2026-09-22
// cl: /Ob1 /ICode/Libraries/Source/WWVegas/WWMath /FAsc /Fabuild/hub_00172600/current.cod
// Complete hub reconstruction, retail RVA 0x00172600 (1524 bytes).
// Symbol: ?onEnter@AIInternalMoveToStateOnEnterShim@@QAE?AW4StateReturnType@@XZ
// See ANALYSIS.md for independently witnessed identities, layouts and ABIs.
// No assembly and no new callee pin. Existing j_ routes are ABI adapters.
// Retail frame is aligned8, alloc32, saved EBX/frame-EBP/ESI/EDI; no EH.
// Probe output is authoritative about how closely this source emits that shape.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
// stlport
#include <bitset>
#include <math.h>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "coord3d.h"

// Real member implementations from Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp.
// Kept in this TU so VC7.1 can inline the actual coordinate operations.
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }
inline Coord3D &Coord3D::Sub2D(const Coord3DBase &that) { x-=that.x; y-=that.y; return *this; }
inline Coord3D &Coord3D::Sub2D(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    return *this;
}
inline float Coord3D::GetLengthEstimate2D() const
{
    float ax = fabs(x);
    float ay = fabs(y);
    if (ax > ay) return ax + 0.25f * ay;
    return ay + 0.25f * ax;
}

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

template<int N>
class Rva00172600Flags {
public:
    bool testWord(unsigned int bit) const {
        if (bits._M_getword(bit) & bits._S_maskbit(bit)) return true;
        return false;
    }
    void set(unsigned int bit) { bits._Unchecked_set(bit); }
private:
    _STL::bitset<N> bits;
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
	Rva00172600Flags<320> m_condition;
	unsigned char m_pad138[0x204 - 0x138];
	Rva00172600AIUpdate *m_ai;
	void notifyModelConditionChanged();
    __forceinline void setCondition(unsigned int flag) {
        if (!m_condition.testWord(flag)) {
            m_condition.set(flag);
            notifyModelConditionChanged();
        }
    }
    Rva00172600AIUpdate *getAI() const { return m_ai; }
	Coord3D *getPosition() { return &m_position; }
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
	virtual bool slot17() = 0;
};

class AIInternalMoveToStateOnEnterShim : public Rva00172600StateWithComputePath
{
public:
	unsigned char m_pad04[0x18];
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

	Object *getMachineOwner() const { return m_machine->m_owner; }
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
	Bool rva00027ffc(Object *, void *, Coord3D *, const Coord3D *);
	void rva000294e2(Object *, Coord3D *, Int, const char *, Int);
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
#pragma comment(linker, "/alternatename:?rva00010109@Rva00172600Calls@@QAE_NXZ=?j_00010109@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001246d@Rva00172600Calls@@QAEXXZ=?j_0001246d@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00012486@Rva00172600Calls@@QAEXXZ=?j_00012486@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001a36b@Rva00172600Calls@@QAEHXZ=?j_0001a36b@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001c26f@Rva00172600Calls@@QAE_NPAVCoord3D@@H@Z=?j_0001c26f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001c675@Rva00172600Calls@@QAEHPAVObject@@PAVCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0001c7e2@Rva00172600Calls@@QAEXH@Z=?j_0001c7e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002191d@Rva00172600Calls@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00027ffc@Rva00172600Calls@@QAE_NPAVObject@@PAXPAVCoord3D@@PBV3@@Z=?j_00027ffc@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000294e2@Rva00172600Calls@@QAEXPAVObject@@PAVCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002b3f0@Rva00172600Calls@@QAEXXZ=?j_0002b3f0@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003251f@Rva00172600Calls@@QAE_NH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000333ac@Rva00172600Calls@@QAEMXZ=?j_000333ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00034c16@Rva00172600Calls@@QAEXPAVObject@@PAVCoord3D@@@Z=?j_00034c16@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0003a391@Rva00172600Calls@@QAEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00046ad3@Rva00172600Calls@@QAE_NPAVObject@@@Z=?j_00046ad3@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00048ca7@Rva00172600Calls@@QAEXM@Z=?j_00048ca7@@YAXXZ")

StateReturnType AIInternalMoveToStateOnEnterShim::onEnter()
{
	if (TheAudioClientUpdate != 0 && m_ambientPlayingHandle >= 5)
	{
		TheAudioClientUpdate->slot19(m_ambientPlayingHandle);
		m_ambientPlayingHandle = 1;
	}

	Object *owner = getMachineOwner();
	Rva00172600AIUpdate *ai = owner->getAI();
	m_waitingForPath = ai->m_waitingForPath;

	if (g_012F0239 && g_012ED4FC)
	{
		Rva00172600Template *templateForLog = owner->m_template;
		UnsignedInt objectId = owner->m_id;
		if (templateForLog != 0 && templateForLog->m_override != 0)
		{
			templateForLog = (Rva00172600Template *)
			((Rva00172600Calls *)templateForLog->m_override)->rva000022bb();
		}
		const char *objectName = templateForLog->m_name ?
            (const char *)templateForLog->m_name + 8 : (const char *)0x0107388b;
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098e70, objectName, objectId,
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

	Real queryFloat =
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

		((Rva00172600Calls *)pathfinder)->rva000294e2(owner,
			&m_goalPosition,
			((Rva00172600Calls *)TheTerrainLogic)->rva0001c675(owner, &m_goalPosition),
			(const char *)0x0109769c, 0x909);
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098b38, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}
		((Rva00172600Calls *)pathfinder)->rva0001c7e2(0);
	}
	else if (g_012F0239 && g_012ED4FC)
	{
		((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
			(const char *)0x01098ad8);
	}

	Coord3D *position = owner->getPosition();
	Coord3D delta(*position);
	delta.Sub2D(m_goalPosition);
	Real lengthEstimate = delta.GetLengthEstimate2D();

	Bool startSound;
	if (lengthEstimate > g_01098AD4)
	{
		startSound = 1;
		if (g_012F0239 && g_012ED4FC)
		{
			((Rva00172600DebugLogCall)j_0003a17a)(g_012ED4FC,
				(const char *)0x01098a58, m_goalPosition.x,
				m_goalPosition.y, m_goalPosition.z);
		}

		if (currentLocomotor != 0 &&
			((Rva00172600Calls *)currentLocomotor)->rva00046ad3(owner) &&
			(m_waitingForPath ||
			 queryFloat > *(Real *)((unsigned char *)currentLocomotor + 0x38)))
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
				position, layer);
			UnsignedInt condition = onCellTypeTwo ? 0x66 : 0x3c;
			owner->setCondition(condition);
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
			owner->setCondition(0x3c);
		}
		else
		{
			if (g_012F0239 && g_012ED4FC)
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

if (!slot17())
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

#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

// ABI-compatible local spellings resolve to independently witnessed global pins.
#pragma comment(linker, "/alternatename:?g_012F0239@@3EA=?Glo012F0239@@3_NA")
#pragma comment(linker, "/alternatename:?g_012ED4FC@@3PAXA=?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A")
#pragma comment(linker, "/alternatename:?g_01098AD4@@3MA=g_bfmeOffsetDF")
#pragma comment(linker, "/alternatename:?TheAudioClientUpdate@@3PAVRva005A00B0AudioClient@@A=?TheAudioClientUpdate@@3PAURva005A00B0AudioClient@@A")
