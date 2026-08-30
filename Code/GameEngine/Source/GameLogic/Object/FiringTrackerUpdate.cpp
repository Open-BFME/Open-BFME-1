// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

enum
{
	FALSE = 0,
	TRUE = 1
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum
{
	AHSV_NoSound = 1,
	LOGICFRAMES_PER_SECOND = 5
};

typedef UnsignedInt AudioHandle;

class Object
{
public:
	void reloadAllAmmo(Bool forceReload);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	UnsignedByte m_pad[0x3C];
	UnsignedInt m_frame;
};

class AudioManager
{
public:
	virtual void audioSlot00();
	virtual void audioSlot04();
	virtual void audioSlot08();
	virtual void audioSlot0C();
	virtual void audioSlot10();
	virtual void audioSlot14();
	virtual void audioSlot18();
	virtual void audioSlot1C();
	virtual void audioSlot20();
	virtual void audioSlot24();
	virtual void audioSlot28();
	virtual void audioSlot2C();
	virtual void audioSlot30();
	virtual void audioSlot34();
	virtual void audioSlot38();
	virtual void audioSlot3C();
	virtual void audioSlot40();
	virtual void audioSlot44();
	virtual void audioSlot48();
	virtual void removeAudioEvent(AudioHandle event);
};

extern GameLogic *TheGameLogic;
extern AudioManager *TheAudio;

class FiringTracker
{
public:
	virtual UpdateSleepTime update();

private:
	void coolDown(Bool forceReset);
};

UpdateSleepTime FiringTracker::update()
{
	char *self = reinterpret_cast<char *>(this);
	GameLogic *gameLogic = TheGameLogic;
	UnsignedInt now = gameLogic->getFrame();
	const float *lastShotPosition = reinterpret_cast<const float *>(self + 0x38);

	{
		Object *object = *reinterpret_cast<Object **>(self - 8);
		const float *objectPosition = reinterpret_cast<const float *>(reinterpret_cast<char *>(object) + 0x38);

		if (objectPosition[0] != lastShotPosition[0]
				|| objectPosition[1] != lastShotPosition[1]
				|| objectPosition[2] != lastShotPosition[2])
		{
			reinterpret_cast<FiringTracker *>(self - 0x10)->coolDown(TRUE);
		}
	}

	UnsignedInt *frameToForceReload = reinterpret_cast<UnsignedInt *>(self + 0x30);
	UnsignedInt *frameToStopLoopingSound = reinterpret_cast<UnsignedInt *>(self + 0x44);
	UnsignedInt *frameToStartCooldown = reinterpret_cast<UnsignedInt *>(self + 0x2C);
	AudioHandle *audioHandle = reinterpret_cast<AudioHandle *>(self + 0x48);

	if (*frameToForceReload != 0 && now >= *frameToForceReload)
	{
		Object *object = *reinterpret_cast<Object **>(self - 8);
		object->reloadAllAmmo(TRUE);
		*frameToForceReload = 0;
	}

	if (*frameToStopLoopingSound != 0 && now >= *frameToStopLoopingSound)
	{
		TheAudio->removeAudioEvent(*audioHandle);
		*audioHandle = AHSV_NoSound;
		*frameToStopLoopingSound = 0;
	}

	if (*frameToStartCooldown != 0 && now > *frameToStartCooldown)
	{
		*frameToStartCooldown = now + LOGICFRAMES_PER_SECOND;
		reinterpret_cast<FiringTracker *>(self - 0x10)->coolDown(FALSE);
		return (UpdateSleepTime)LOGICFRAMES_PER_SECOND;
	}

	if (*frameToStopLoopingSound == 0
			&& *reinterpret_cast<volatile UnsignedInt *>(self + 0x2C) == 0
			&& *reinterpret_cast<volatile UnsignedInt *>(self + 0x30) == 0)
		return UPDATE_SLEEP_FOREVER;
	return UPDATE_SLEEP_NONE;
}
