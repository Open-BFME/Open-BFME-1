// cl: /DNDEBUG /MD /EHsc

typedef float Real;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual UnsignedInt getFrame();
};

extern GameClient *TheGameClient;
extern Real GetGameClientRandomValueReal(Real, Real, char *, int);

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad000[0x1C8];
	Real m_chance;
	UnsignedInt m_selectedValue;
	unsigned char m_selectedFlag;
	unsigned char m_rerollOnEveryFrame;
};

class RandomSoundSelectorClientBehavior
{
private:
	void reroll();
	char m_pad00[4];
	RandomSoundSelectorClientBehaviorModuleDataView *m_moduleData;
	char m_pad08[8];
	Real m_randomSelection;
	UnsignedInt m_lastFrame;
};

// ?reroll@RandomSoundSelectorClientBehavior@@AAEXXZ
void RandomSoundSelectorClientBehavior::reroll()
{
	if (m_moduleData->m_rerollOnEveryFrame && TheGameClient &&
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
