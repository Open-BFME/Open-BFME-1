// ?update@BoneFXUpdate@@UAE?AW4UpdateSleepTime@@XZ
// clean reconstruction of retail 0x00289580, 467 bytes
// cl: /DNDEBUG /MD /EHsc

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

class AsciiString
{
	void *m_data;
};

class GameClientRandomVariable
{
	public:
	float getValue() const;

	private:
	Int m_type;
	float m_low;
	float m_high;
};

class GameLogicRandomVariable
{
	public:
	float getValue() const;

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

#define TheGameLogic (*(GameLogic **)0x012f0898)

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
	void doFXListAtBone(const FXList *, const Coord3D *);
	void doOCLAtBone(const ObjectCreationList *, const Coord3D *);
	void doParticleSystemAtBone(const ParticleSystemTemplate *, const Coord3D *);
	void computeNextLogicFXTime(const BaseBoneListInfo *info, Int &nextFrame)
	{
		if (info->onlyOnce) {
			nextFrame = -1;
			return;
		}
		nextFrame = TheGameLogic->getFrame() + (Int)info->gameLogicDelay.getValue();
	}
	void computeNextClientFXTime(const BaseBoneListInfo *info, Int &nextFrame)
	{
		if (info->onlyOnce) {
			nextFrame = -1;
			return;
		}
		nextFrame = TheGameLogic->getFrame() + (Int)info->gameClientDelay.getValue();
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

#pragma comment(linker, "/alternatename:?initTimes@BoneFXUpdate@@IAEXXZ=?j_0002f775@@YAXXZ")
#pragma comment(linker, "/alternatename:?doFXListAtBone@BoneFXUpdate@@IAEXPBVFXList@@PBUCoord3D@@@Z=?j_0002ef6e@@YAXXZ")
#pragma comment(linker, "/alternatename:?doOCLAtBone@BoneFXUpdate@@IAEXPBVObjectCreationList@@PBUCoord3D@@@Z=?j_0001b1f3@@YAXXZ")
#pragma comment(linker, "/alternatename:?doParticleSystemAtBone@BoneFXUpdate@@IAEXPBVParticleSystemTemplate@@PBUCoord3D@@@Z=?j_00019420@@YAXXZ")
#pragma comment(linker, "/alternatename:?getValue@GameLogicRandomVariable@@QBEMXZ=?j_000188cc@@YAXXZ")
#pragma comment(linker, "/alternatename:?getValue@GameClientRandomVariable@@QBEMXZ=?j_0000d7b5@@YAXXZ")

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
			doFXListAtBone(d->fxList[m_curBodyState][i].fx, &m_FXBonePositions[m_curBodyState][i]);
			computeNextLogicFXTime(&d->fxList[m_curBodyState][i], m_nextFXFrame[m_curBodyState][i]);
		}
		if ((m_nextOCLFrame[m_curBodyState][i] != -1) && (m_nextOCLFrame[m_curBodyState][i] <= now)) {
			doOCLAtBone(d->ocl[m_curBodyState][i].ocl, &m_OCLBonePositions[m_curBodyState][i]);
			computeNextLogicFXTime(&d->ocl[m_curBodyState][i], m_nextOCLFrame[m_curBodyState][i]);
		}
		if ((m_nextParticleSystemFrame[m_curBodyState][i] != -1) && (m_nextParticleSystemFrame[m_curBodyState][i] <= now)) {
			doParticleSystemAtBone(d->particleSystem[m_curBodyState][i].particleSysTemplate, &m_PSBonePositions[m_curBodyState][i]);
			computeNextClientFXTime(&d->particleSystem[m_curBodyState][i], m_nextParticleSystemFrame[m_curBodyState][i]);
		}
	}
	return UPDATE_SLEEP_NONE;
}
