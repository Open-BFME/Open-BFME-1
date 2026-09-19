// cl: /DNDEBUG /MD /EHsc

typedef float Real;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual void moduleAnchor();

protected:
	const ModuleData *m_moduleData;
	void *m_drawable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule : public Module
{
public:
	ClientUpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ClientUpdateModule();
	virtual void clientUpdate() = 0;
};

class SoundSelectorInterface
{
public:
	virtual void selectSound() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1c();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void pad2c();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3c();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4c();
	virtual void pad50();
	virtual void pad54();
	virtual void pad58();
	virtual void pad5c();
	virtual void pad60();
	virtual void pad64();
	virtual UnsignedInt getFrame();
};

extern GameClient *TheGameClient;
extern Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad000[0x1C8];
	Real m_chance;
	UnsignedInt m_selectedValue;
	unsigned char m_selectedFlag;
	unsigned char m_rerollOnEveryFrame;
};

class RandomSoundSelectorClientBehavior : public ClientUpdateModule, public SoundSelectorInterface
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	virtual void clientUpdate();
	virtual void selectSound();

private:
	void reroll();
	Real m_randomSelection;
	UnsignedInt m_lastFrame;
};

RandomSoundSelectorClientBehavior::RandomSoundSelectorClientBehavior(
	Thing *thing, const ModuleData *moduleData) :
	ClientUpdateModule(thing, moduleData),
	m_randomSelection(GetGameClientRandomValueReal(
		0.0f,
		1.0f,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable\\Behavior\\RandomSoundSelectorClientBehavior.cpp",
		96))
{
	if (TheGameClient)
		m_lastFrame = TheGameClient->getFrame();
	else
		m_lastFrame = 0;
}

// ?reroll@RandomSoundSelectorClientBehavior@@AAEXXZ
void RandomSoundSelectorClientBehavior::reroll()
{
	RandomSoundSelectorClientBehaviorModuleDataView *moduleData =
		(RandomSoundSelectorClientBehaviorModuleDataView *)m_moduleData;
	if (moduleData->m_rerollOnEveryFrame && TheGameClient &&
		TheGameClient->getFrame() != m_lastFrame)
	{
		m_randomSelection = GetGameClientRandomValueReal(
			0.0f,
			1.0f,
			"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\Drawable\\Behavior\\RandomSoundSelectorClientBehavior.cpp",
			114);
		m_lastFrame = TheGameClient->getFrame();
	}
}
