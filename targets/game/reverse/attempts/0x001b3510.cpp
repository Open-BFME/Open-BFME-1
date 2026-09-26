// ?rva001B3510@Rva001CD990FiringTracker@@QAEXPBVWeapon@@HPBXE@Z
// partial score=0.41 date=2026-09-26
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned char Bool;
typedef unsigned int AudioHandle;

enum ObjectID
{
	INVALID_ID = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

struct Coord3D
{
	float x;
	float y;
	float z;

	bool IsExactlyEqualTo(const Coord3D &other) const;
};

#include "ascii_string.h"

class Counted
{
public:
	virtual ~Counted();
	long m_refCount;
};

class CountedPtr
{
public:
	Counted *m_ptr;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &right);
	virtual ~AudioEventRTS();
	void setObjectID(ObjectID objectID);

private:
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;
	UnsignedInt m_playingHandle;
	UnsignedInt m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	UnsignedInt m_pitchShift;
	UnsignedInt m_volume;
	UnsignedInt m_timeOfDay;
	UnsignedInt m_objectID;
	Int m_ownerType;
	Coord3D m_position;
	unsigned char m_flags[10];
	unsigned char m_pad4A[2];
	UnsignedInt m_float4C;
	UnsignedInt m_volumeShift;
	UnsignedInt m_delay;
	UnsignedInt m_int58;
	UnsignedInt m_playerIndex;
	UnsignedInt m_portionToPlayNext;
	UnsignedInt m_loopCount;
	UnsignedInt m_int68;
	AsciiString m_tail;
};

class Object
{
public:
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const unsigned char *>(this) + 0x74);
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}

	Bool testWeaponBonusCondition(Int condition) const
	{
		return static_cast<Bool>((
			*reinterpret_cast<const UnsignedInt *>(
				reinterpret_cast<const unsigned char *>(this) + 0x2a0) >> condition) & 1);
	}
};

enum WeaponBonusCondition
{
	WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN = 2,
	WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST = 3
};

class Weapon
{
private:
	const unsigned char *getTemplate() const
	{
		return *reinterpret_cast<const unsigned char * const *>(
			reinterpret_cast<const unsigned char *>(this) + 4);
	}

public:
	UnsignedInt getAutoReloadWhenIdleFrames() const
	{
		return *reinterpret_cast<const UnsignedInt *>(getTemplate() + 0x4cc);
	}

	UnsignedInt getContinuousFireCoastFrames() const
	{
		return *reinterpret_cast<const UnsignedInt *>(getTemplate() + 0x4c8);
	}

	UnsignedInt getContinuousFireOneShotsNeeded() const
	{
		return *reinterpret_cast<const UnsignedInt *>(getTemplate() + 0x4c0);
	}

	UnsignedInt getContinuousFireTwoShotsNeeded() const
	{
		return *reinterpret_cast<const UnsignedInt *>(getTemplate() + 0x4c4);
	}

	UnsignedInt getPossibleNextShotFrame() const
	{
		return *reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const unsigned char *>(this) + 0x18);
	}

	UnsignedInt getFireSoundLoopTime() const
	{
		return *reinterpret_cast<const UnsignedInt *>(getTemplate() + 0x124);
	}

	const AudioEventRTS &getFireSound() const
	{
		return *reinterpret_cast<const AudioEventRTS *>(getTemplate() + 0xb4);
	}
};

class GameLogic
{
public:
	Object *findObjectByID(Int objectID);

	UnsignedInt getFrame() const
	{
		return *reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const unsigned char *>(this) + 0x3c);
	}
};

extern GameLogic *TheGameLogic;

class AudioManager
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
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event);
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual Bool isCurrentlyPlaying(AudioHandle handle);
};

extern AudioManager *TheAudio;

class UpdateModule
{
protected:
	Object *getObject() const
	{
		return *reinterpret_cast<Object * const *>(
			reinterpret_cast<const unsigned char *>(this) + 8);
	}

	void setWakeFrame(Object *object, UpdateSleepTime frame);

private:
	unsigned char m_unmodelled[0x20];
};

class RvaC4390First
{
private:
	unsigned char m_unmodelled[0x74];

public:
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const unsigned char *>(this) + 0x74);
	}
};

class RvaC4390Second
{
public:
	RvaC4390First *resolve(Int allowLookup);
};

class FiringTracker : public UpdateModule
{
protected:
	void coolDown(bool forceReset);
	void speedUp();

	Int m_consecutiveShots;
	Int m_victimID;
	Coord3D m_victimPosition;
	Bool m_victimIsPosition;
	unsigned char m_alignment35[3];
	Int m_auxiliaryObjectID;
	UnsignedInt m_frameToStartCooldown;
	UnsignedInt m_frameToForceReload;
	UnsignedInt m_lastShotFrame;
	Coord3D m_lastShotPosition;
	UnsignedInt m_frameToStopLoopingSound;
	AudioHandle m_audioHandle;
};

class Rva001CD990FiringTracker : public FiringTracker
{
	public:
	void rva001B3510(const Weapon *weaponFired, Int victimID,
		const void *victimPosition, Bool forceReset);
};

void Rva001CD990FiringTracker::rva001B3510(
	const Weapon *weaponFired, Int victimID,
	const void *victimPosition, Bool forceReset)
{
	Object *victim = TheGameLogic->findObjectByID(victimID);

	if (victim != 0 &&
		(reinterpret_cast<const unsigned char *>(victim)[0x94] & 0x20) != 0)
	{
		m_auxiliaryObjectID =
			reinterpret_cast<RvaC4390Second *>(victim)->resolve(0) != 0
				? reinterpret_cast<RvaC4390Second *>(victim)->resolve(0)->getID()
				: 0;
	}

	UnsignedInt now = TheGameLogic->getFrame();
	m_lastShotFrame = now;
	m_lastShotPosition = *getObject()->getPosition();

	if (forceReset != 0)
	{
		m_consecutiveShots = 1;
		coolDown(true);
	}
	else
	{
		if (victimID != 0 || victimPosition == 0)
		{
			if (m_victimIsPosition)
			{
				m_consecutiveShots = 1;
			}
			else if (victimID == m_victimID)
			{
				++m_consecutiveShots;
			}
			else if (now < m_frameToStartCooldown)
			{
				++m_consecutiveShots;
			}
			else
			{
				m_consecutiveShots = 1;
			}
			m_victimID = victimID;
			m_victimIsPosition = false;
		}
		else
		{
			const Coord3D *position =
				reinterpret_cast<const Coord3D *>(victimPosition);
			if (!m_victimIsPosition)
			{
				m_consecutiveShots = 1;
				m_victimPosition = *position;
				m_victimID = INVALID_ID;
			}
			else if (m_victimPosition.IsExactlyEqualTo(*position))
			{
				++m_consecutiveShots;
			}
			else if (now < m_frameToStartCooldown)
			{
				++m_consecutiveShots;
				m_victimPosition = *position;
			}
			else
			{
				m_consecutiveShots = 1;
				m_victimPosition = *position;
			}
			m_victimIsPosition = true;
		}

		UnsignedInt autoReloadDelay =
			weaponFired->getAutoReloadWhenIdleFrames();
		if (autoReloadDelay > 0)
			m_frameToForceReload = now + autoReloadDelay;

		UnsignedInt coast = weaponFired->getContinuousFireCoastFrames();
		if (coast != 0)
			m_frameToStartCooldown =
				weaponFired->getPossibleNextShotFrame() + coast;
		else
			m_frameToStartCooldown = 0;

		Int shotsNeededOne =
			weaponFired->getContinuousFireOneShotsNeeded();
		Int shotsNeededTwo =
			weaponFired->getContinuousFireTwoShotsNeeded();

		if (getObject()->testWeaponBonusCondition(
			WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN))
		{
			if (m_consecutiveShots < shotsNeededOne)
				coolDown(false);
			else if (m_consecutiveShots > shotsNeededTwo)
				speedUp();
		}
		else if (getObject()->testWeaponBonusCondition(
			WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST))
		{
			if (m_consecutiveShots < shotsNeededTwo)
				coolDown(false);
		}
		else if (m_consecutiveShots > shotsNeededOne)
		{
			speedUp();
		}

		UnsignedInt fireSoundLoopTime = weaponFired->getFireSoundLoopTime();
		if (fireSoundLoopTime != 0)
		{
			if (m_frameToStopLoopingSound == 0
				|| !TheAudio->isCurrentlyPlaying(m_audioHandle))
			{
				AudioEventRTS audio = weaponFired->getFireSound();
				audio.setObjectID(getObject()->getID());
				m_audioHandle = TheAudio->addAudioEvent(&audio);
			}
			m_frameToStopLoopingSound = now + fireSoundLoopTime;
		}
		else
		{
			AudioEventRTS fireAndForgetSound = weaponFired->getFireSound();
			fireAndForgetSound.setObjectID(getObject()->getID());
			TheAudio->addAudioEvent(&fireAndForgetSound);
			m_frameToStopLoopingSound = 0;
		}
	}

	UpdateSleepTime sleepTime =
		(m_frameToStopLoopingSound == 0
			&& m_frameToStartCooldown == 0
			&& m_frameToForceReload == 0)
			? UPDATE_SLEEP_FOREVER
			: UPDATE_SLEEP_NONE;
	setWakeFrame(getObject(), sleepTime);
}
