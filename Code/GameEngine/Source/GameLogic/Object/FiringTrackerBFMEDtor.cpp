// cl: /DNDEBUG /MD /EHsc
// readable body of ??1FiringTracker@@MAE@XZ: Code/GameEngine/Source/GameLogic/Object/FiringTracker.cpp

typedef int AudioHandle;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	const void *m_moduleData;
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/FiringTracker.h
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
