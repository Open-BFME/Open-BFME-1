// cl: /DNDEBUG /MD /EHsc

typedef int AudioHandle;

class AudioManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent(AudioHandle handle);
};

extern AudioManager *TheAudio;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	const void *m_moduleData;
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class FiringTracker : public UpdateModule
{
protected:
	virtual ~FiringTracker();

private:
	unsigned char m_unreconstructed_20[0x38];
	AudioHandle m_audioHandle;
};

FiringTracker::~FiringTracker()
{
	TheAudio->removeAudioEvent(m_audioHandle);
	m_audioHandle = 1;
}
