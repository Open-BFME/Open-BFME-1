// ?d_002a4f90@@YAXXZ
// partial score=0.31 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// BFME repair-state setter reconstructed from the ZH twin and retail offsets.

#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void add(const Coord3D *other)
	{
		x += other->x;
		y += other->y;
		z += other->z;
	}

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

class Matrix3D;
class ParticleSystemTemplate;

class Drawable
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable() const;

	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_unmodelled[0x34];
	Coord3D m_position;
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *position);
	void setLifetimeRange(Real min, Real max);
};

extern ParticleSystem *Make00001B18();

class U1Sub
{
public:
	ParticleSystem *m_system;
	U1Sub *m_previous;
	U1Sub *m_next;
};

class BfmeParticleSystemHandle : public U1Sub
{
public:
	~BfmeParticleSystemHandle() throw();

	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make00001B18();
		return m_system;
	}

};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);
	~AudioEventRTS();
	void setPosition(const Coord3D *position);

private:
	unsigned char m_storage[0x70];
};

struct MiscAudio;

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16)
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *event);
	AUDIO_SLOT(18) AUDIO_SLOT(19) AUDIO_SLOT(20) AUDIO_SLOT(21)
	AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24) AUDIO_SLOT(25)
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33)
	AUDIO_SLOT(34) AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37)
	AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41)
	AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44) AUDIO_SLOT(45)
	AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53)
	AUDIO_SLOT(54) AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57)
	AUDIO_SLOT(58) AUDIO_SLOT(59) AUDIO_SLOT(60) AUDIO_SLOT(61)
	AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64) AUDIO_SLOT(65)
	AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72)
	virtual MiscAudio *getMiscAudio();
#undef AUDIO_SLOT
};

struct MiscAudio
{
	unsigned char m_unmodelled[0xaf0];
	AudioEventRTS m_repairSparks;
};

extern ParticleSystemManager *TheParticleSystemManager;
extern AudioManager *TheAudio;
extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

enum RepairStates
{
	REPAIRSTATE_NONE,
	REPAIRSTATE_UNPACKING,
	REPAIRSTATE_PACKING,
	REPAIRSTATE_READY,
	REPAIRSTATE_EXTENDING,
	REPAIRSTATE_RETRACTING,
	REPAIRSTATE_WELDING
};

enum ModelConditionFlagType
{
	MODELCONDITION_FIRING_B = 46,
	MODELCONDITION_FIRING_C = 52,
	MODELCONDITION_PACKING = 93,
	MODELCONDITION_UNPACKING = 95
};

class SlavedUpdateModuleData
{
private:
	unsigned char m_unmodelled[0x38];

public:
	Int m_minReadyFrames;
	Int m_maxReadyFrames;
	Int m_minWeldFrames;
	Int m_maxWeldFrames;
	AsciiString m_weldingSysName;
	AsciiString m_weldingFXBone;
};

class SlavedUpdate
{
public:
	void setRepairModelConditionStates(ModelConditionFlagType flag);
	void moveToNewRepairSpot();
	void setRepairState(RepairStates repairState);

	SlavedUpdateModuleData *getSlavedUpdateModuleData() const
	{
		return *(SlavedUpdateModuleData **)((unsigned char *)this + 4);
	}
	Object *getObject() const
	{
		return m_object;
	}

private:
	unsigned char m_unmodelled_00[8];
	Object *m_object;
	unsigned char m_unmodelled_0c[0x28];
	Int m_framesToWait;
	RepairStates m_repairState;
	Bool m_repairing;
};

#pragma comment(linker, "/alternatename:?setRepairModelConditionStates@SlavedUpdate@@QAEXW4ModelConditionFlagType@@@Z=?j_0001d084@@YAXXZ")
#pragma comment(linker, "/alternatename:?moveToNewRepairSpot@SlavedUpdate@@QAEXXZ=?j_00020e5f@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEmpty@?$StringBase@D@@QBE_NXZ=?j_0000c752@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@ParticleSystemManager@@QBEPAVParticleSystemTemplate@@ABVAsciiString@@@Z=?j_00015267@@YAXXZ")
#pragma comment(linker, "/alternatename:?createParticleSystem@ParticleSystemManager@@QAE?AVBfmeParticleSystemHandle@@PBVParticleSystemTemplate@@_N@Z=?j_0000ebe7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPristineBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@HH@Z=?j_0002319b@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@ParticleSystem@@QAEXPBUCoord3D@@@Z=?j_00021832@@YAXXZ")
#pragma comment(linker, "/alternatename:?setLifetimeRange@ParticleSystem@@QAEXMM@Z=?j_0002423f@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeParticleSystemHandle@@QAE@XZ=?j_00013994@@YAXXZ")
#pragma comment(linker, "/alternatename:?Make00001B18@@YAPAVParticleSystem@@XZ=?j_00001b18@@YAXXZ")
#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@AudioEventRTS@@QAEXPBUCoord3D@@@Z=?j_00001e88@@YAXXZ")

void SlavedUpdate::setRepairState(RepairStates repairState)
{
	const SlavedUpdateModuleData *data;
	const AsciiString *weldingSysName;
	Object *obj = *(Object **)((unsigned char *)this + 8);
	Drawable *draw = obj->getDrawable();
	data = getSlavedUpdateModuleData();

	if (repairState == m_repairState)
		return;

	switch (repairState)
	{
	case REPAIRSTATE_UNPACKING:
		setRepairModelConditionStates(MODELCONDITION_UNPACKING);
		m_framesToWait = 15;
		break;
	case REPAIRSTATE_PACKING:
		setRepairModelConditionStates(MODELCONDITION_PACKING);
		m_framesToWait = 15;
		break;
	case REPAIRSTATE_READY:
	{
		switch (m_repairState)
		{
		case REPAIRSTATE_NONE:
			setRepairModelConditionStates(MODELCONDITION_UNPACKING);
			m_repairState = REPAIRSTATE_UNPACKING;
			m_framesToWait = 15;
			break;
		case REPAIRSTATE_WELDING:
			m_repairState = REPAIRSTATE_RETRACTING;
			m_framesToWait = 5;
			setRepairModelConditionStates(MODELCONDITION_FIRING_C);
			moveToNewRepairSpot();
			break;
		default:
			m_repairState = REPAIRSTATE_READY;
			m_framesToWait = GetGameLogicRandomValue(
				data->m_minReadyFrames, data->m_maxReadyFrames,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
				0x26a);
			break;
		}
		break;
	}
	case REPAIRSTATE_WELDING:
	{
		if (m_repairState == REPAIRSTATE_READY)
		{
			m_repairState = REPAIRSTATE_EXTENDING;
			m_framesToWait = 5;
			setRepairModelConditionStates(MODELCONDITION_FIRING_B);
			break;
		}
		else
		{
		weldingSysName = &data->m_weldingSysName;
		m_repairState = REPAIRSTATE_WELDING;
		m_framesToWait = GetGameLogicRandomValue(
			data->m_minWeldFrames, data->m_maxWeldFrames,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
			0x27b);

		if (!weldingSysName->isEmpty())
		{
			const ParticleSystemTemplate *tmp =
				TheParticleSystemManager->findTemplate(*weldingSysName);
			if (tmp)
			{
				BfmeParticleSystemHandle weldingSys =
					TheParticleSystemManager->createParticleSystem(tmp, true);
				if (weldingSys)
				{
					Coord3D pos;
					if (draw->getPristineBonePositions(data->m_weldingFXBone.str(), 0,
						&pos, 0, 1, 0))
						pos.add(obj->getPosition());
					else
						pos.set(obj->getPosition());

					weldingSys->setPosition(&pos);
					Real time = (Real)(m_framesToWait * 5);
					weldingSys->setLifetimeRange(time, time);
					AudioEventRTS soundToPlay =
						TheAudio->getMiscAudio()->m_repairSparks;
					soundToPlay.setPosition(&pos);
					TheAudio->addAudioEvent(&soundToPlay);
				}
			}
		}

		if (!m_repairing)
		{
			m_repairing = true;
		}
		break;
		}
	}
	}
}
