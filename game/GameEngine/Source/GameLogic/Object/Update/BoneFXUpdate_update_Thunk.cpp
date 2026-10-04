// ?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ
// clean reconstruction of retail 0x00289580, 467 bytes
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Retail calls these bodies through 5-byte ILT thunks, so each call site is a
// plain thiscall `call rel32` naming ?j_XXXXXXXX@@YAXXZ. The pmf unions below
// are spelled on deliberately non-polymorphic route classes: cl 7.1 only folds
// a constant pointer-to-member into a direct thiscall for a non-virtual class.
// On BoneFXUpdate itself (polymorphic) it emits mov eax, imm32 / call eax and
// re-allocates registers across the whole update() body.
// initTimes needs no route: its 5-byte ILT thunk at 0x0002F775 is itself a real
// body named ?initTimes@BoneFXUpdate@@IAEXXZ and is pinned at that address, so a
// direct member call already reaches retail. The old linker alias directive
// named a ?j_XXXXXXXX@@YAXXZ symbol that does not exist in the reconstruction.
extern void j_0002ef6e();
extern void j_0001b1f3();
extern void j_00019420();
extern void j_000188cc();
extern void j_0000d7b5();

class BoneFXUpdateRoute
{
};

class RandomVariableRoute
{
};

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class FXList;
class ObjectCreationList;
class ParticleSystemTemplate;

#include "ascii_string.h"

class GameClientRandomVariable
{
	private:
		Int m_type;
		float m_low;
		float m_high;
};

class GameLogicRandomVariable
{
	private:
		Int m_type;
		float m_low;
		float m_high;
};

struct BaseBoneListInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	Bool onlyOnce;
	unsigned char padding[3];
};

struct BoneFXListInfo : BaseBoneListInfo
{
	const FXList *fx;
};

struct BoneOCLInfo : BaseBoneListInfo
{
	const ObjectCreationList *ocl;
};

struct BoneParticleSystemInfo : BaseBoneListInfo
{
	const ParticleSystemTemplate *particleSysTemplate;
};

class BoneFXUpdateModuleData
{
public:
	unsigned char header[0x0c];
	BoneFXListInfo fxList[4][8];
	Int damageOCLTypes;
	BoneOCLInfo ocl[4][8];
	Int damageParticleTypes;
	BoneParticleSystemInfo particleSystem[4][8];
};

class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return m_frame;
	}

private:
	unsigned char padding[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class BehaviorModulePrimary
{
public:
	virtual void slot();
	const BoneFXUpdateModuleData *m_moduleData;
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void slot();
};

class BehaviorModule : public BehaviorModulePrimary, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	Int m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_updateState;
};

class VectorInt
{
public:
	Int *m_begin;
	Int *m_end;
	Int *m_capacity;
};

class BoneFXUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

protected:
	void initTimes();
	void computeNextLogicFXTime(const BaseBoneListInfo *info, Int &nextFrame)
	{
		if (info->onlyOnce) {
			nextFrame = -1;
			return;
		}
		typedef float (RandomVariableRoute::*Fn)() const;
		union { void (*fn)(); Fn call; } u = { j_000188cc };
		nextFrame = TheGameLogic->getFrame() + (Int)(((RandomVariableRoute *)&info->gameLogicDelay)->*u.call)();
	}
	void computeNextClientFXTime(const BaseBoneListInfo *info, Int &nextFrame)
	{
		if (info->onlyOnce) {
			nextFrame = -1;
			return;
		}
		typedef float (RandomVariableRoute::*Fn)() const;
		union { void (*fn)(); Fn call; } u = { j_0000d7b5 };
		nextFrame = TheGameLogic->getFrame() + (Int)(((RandomVariableRoute *)&info->gameClientDelay)->*u.call)();
	}

private:
	VectorInt m_particleSystemIDs;
	Int m_nextFXFrame[4][8];
	Int m_nextOCLFrame[4][8];
	Int m_nextParticleSystemFrame[4][8];
	Coord3D m_FXBonePositions[4][8];
	Coord3D m_OCLBonePositions[4][8];
	Coord3D m_PSBonePositions[4][8];
	Int m_curBodyState;
	Bool m_bonesResolved[4];
	Bool m_active;
};

UpdateSleepTime BoneFXUpdate::update()
{
	const BoneFXUpdateModuleData *d = m_moduleData;
	Int now = TheGameLogic->getFrame();

	if (m_active == false) {
		initTimes();
		m_active = true;
	}

	for (Int i = 0; i < 8; ++i) {
		if ((m_nextFXFrame[m_curBodyState][i] != -1) && (m_nextFXFrame[m_curBodyState][i] <= now)) {
			typedef void (BoneFXUpdateRoute::*Fn)(const FXList *, const Coord3D *);
			union { void (*fn)(); Fn call; } u = { j_0002ef6e };
			(((BoneFXUpdateRoute *)this)->*u.call)(d->fxList[m_curBodyState][i].fx, &m_FXBonePositions[m_curBodyState][i]);
			computeNextLogicFXTime(&d->fxList[m_curBodyState][i], m_nextFXFrame[m_curBodyState][i]);
		}
		if ((m_nextOCLFrame[m_curBodyState][i] != -1) && (m_nextOCLFrame[m_curBodyState][i] <= now)) {
			typedef void (BoneFXUpdateRoute::*Fn)(const ObjectCreationList *, const Coord3D *);
			union { void (*fn)(); Fn call; } u = { j_0001b1f3 };
			(((BoneFXUpdateRoute *)this)->*u.call)(d->ocl[m_curBodyState][i].ocl, &m_OCLBonePositions[m_curBodyState][i]);
			computeNextLogicFXTime(&d->ocl[m_curBodyState][i], m_nextOCLFrame[m_curBodyState][i]);
		}
		if ((m_nextParticleSystemFrame[m_curBodyState][i] != -1) && (m_nextParticleSystemFrame[m_curBodyState][i] <= now)) {
			typedef void (BoneFXUpdateRoute::*Fn)(const ParticleSystemTemplate *, const Coord3D *);
			union { void (*fn)(); Fn call; } u = { j_00019420 };
			(((BoneFXUpdateRoute *)this)->*u.call)(d->particleSystem[m_curBodyState][i].particleSysTemplate, &m_PSBonePositions[m_curBodyState][i]);
			computeNextClientFXTime(&d->particleSystem[m_curBodyState][i], m_nextParticleSystemFrame[m_curBodyState][i]);
		}
	}
	return UPDATE_SLEEP_NONE;
}
