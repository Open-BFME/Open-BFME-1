// cl: /DNDEBUG /MD /EHsc

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

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
class ObjectModule : public Gen_dtor_00113f20
{
private:
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
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_indexInUpdate;

public:
	virtual ~UpdateModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModuleInterface
{
public:
	virtual void onDamage() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void removeAudioEvent(unsigned int audioEvent);
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdate
	: public UpdateModule, public DamageModuleInterface
{
public:
	virtual ~FlammableUpdate();

private:
	int m_status;
	unsigned int m_aflameEndFrame;
	unsigned int m_burnedEndFrame;
	unsigned int m_damageEndFrame;
	unsigned int m_audioHandle;
};

// ??1FlammableUpdate@@UAE@XZ
FlammableUpdate::~FlammableUpdate()
{
	if (m_audioHandle)
	{
		TheAudio->removeAudioEvent(m_audioHandle);
		m_audioHandle = 0;
	}
}
