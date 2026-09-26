// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?onVeterancyLevelChanged@Rva001CEAD0Object@@QAEXHH@Z

typedef bool Bool;
enum VeterancyLevel { LEVEL_REGULAR, LEVEL_VETERAN, LEVEL_ELITE, LEVEL_HEROIC };
enum WorldAnimationOptions { WORLD_ANIM_FADE_ON_EXPIRE = 1 };
enum KindOfType { KINDOF_IGNORED_IN_GUI = 0x2f };

struct Coord3D
{
	float x, y, z;
	void add(const Coord3D *other)
	{
		x += other->x;
		y += other->y;
		z += other->z;
	}
};
class UpgradeTemplate;
class Anim2DTemplate;
class Player;

class Object
{
public:
	void updateUpgradeModules();
	void giveUpgrade(const UpgradeTemplate *upgrade);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findVeterancyUpgrade(VeterancyLevel level) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class BfmeObjE10
{
public:
	void actionA(int kind);
	void actionB(int kind);
};

struct BfmeBody
{
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
	virtual void onVeterancyLevelChanged(int oldLevel, int newLevel);
};

struct BfmePlayerList
{
	char pad[0xc];
	Player *localPlayer;
	Player *getLocalPlayer() { return localPlayer; }
};
extern BfmePlayerList *ThePlayerList;

struct BfmeGameLogic
{
	char pad[0x92];
	Bool drawIconUI;
};
extern BfmeGameLogic *TheGameLogic;

struct BfmeAsciiData
{
	int refs;
	unsigned short length;
};
class AsciiString
{
public:
	BfmeAsciiData *data;
	Bool isEmpty() const { return data == 0 || data->length == 0; }
};

struct BfmeGlobalData
{
	char pad[0x200];
	AsciiString levelGainAnimationName;
	float displayTime;
	float zRise;
};
extern BfmeGlobalData *TheWritableGlobalData;

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};
extern Anim2DCollection *TheAnim2DCollection;

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *animation, const Coord3D *pos, WorldAnimationOptions options, float seconds, float rise);
};
extern InGameUI *TheInGameUI;

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &source);
	~AudioEventRTS();
	void setObjectID(unsigned int id);
private:
	char bytes[0x70];
};

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
	virtual void addAudioEvent(const AudioEventRTS *event);
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
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void *getMiscAudio();
};
extern AudioManager *TheAudio;

class Rva001CEAD0Object
{
public:
	void onVeterancyLevelChanged(int oldLevel, int newLevel);
	const Coord3D *getPosition() const { return &m_cachedPos; }
	unsigned int getID() const { return m_id; }
private:
	char pad00[0x38];
	Coord3D m_cachedPos;
	char pad44[0x74 - 0x44];
	unsigned int m_id;
	char pad78[0x24c - 0x78];
	Coord3D m_coordOffset24C;
};

void Rva001CEAD0Object::onVeterancyLevelChanged(int oldLevel, int newLevel)
{
	Object *object = reinterpret_cast<Object *>(this);
	object->updateUpgradeModules();
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findVeterancyUpgrade((VeterancyLevel)newLevel);
	if (upgrade)
		object->giveUpgrade(upgrade);

	BfmeBody *body = *(BfmeBody **)((char *)this + 0x200);
	if (body)
	{
		body->onVeterancyLevelChanged(oldLevel, newLevel);
	}

	Team *team = *(Team **)((char *)this + 0x23c);
	Player *owner = team ? team->getControllingPlayer() : 0;
	Bool hideAnimationForStealth = 0;
	if (owner != ThePlayerList->getLocalPlayer() &&
		(*(unsigned int *)((char *)this + 0x90) & 0x8000) &&
		!(*(unsigned int *)((char *)this + 0x90) & 0x20000))
		hideAnimationForStealth = 1;
	Bool doAnimation = !hideAnimationForStealth &&
		newLevel > oldLevel && !reinterpret_cast<const Thing *>(this)->isKindOf(KINDOF_IGNORED_IN_GUI);

	BfmeObjE10 *action = reinterpret_cast<BfmeObjE10 *>(this);
	unsigned int *bonus = (unsigned int *)((char *)this + 0x2a0);
	switch (newLevel)
	{
	case 0:
		action->actionB(0);
		action->actionB(1);
		action->actionB(2);
		*bonus &= ~0xe00u;
		doAnimation = 0;
		break;
	case 1:
		action->actionA(0);
		action->actionB(1);
		action->actionB(2);
		*bonus = (*bonus & ~0xc00u) | 0x200u;
		break;
	case 2:
		action->actionB(0);
		action->actionA(1);
		action->actionB(2);
		*bonus = (*bonus & ~0xa00u) | 0x400u;
		break;
	case 3:
		action->actionB(0);
		action->actionB(1);
		action->actionA(2);
		*bonus = (*bonus & ~0x600u) | 0x800u;
		break;
	}

	if (doAnimation && TheGameLogic->drawIconUI)
	{
		if (TheAnim2DCollection && !TheWritableGlobalData->levelGainAnimationName.isEmpty())
		{
			Anim2DTemplate *animation = TheAnim2DCollection->findTemplate(TheWritableGlobalData->levelGainAnimationName);
			Coord3D pos;
			pos.x = getPosition()->x;
			pos.y = getPosition()->y;
			pos.z = getPosition()->z;
			pos.add(&m_coordOffset24C);
			TheInGameUI->addWorldAnimation(animation, &pos, WORLD_ANIM_FADE_ON_EXPIRE, TheWritableGlobalData->displayTime, TheWritableGlobalData->zRise);
		}

		void *misc = TheAudio->getMiscAudio();
		AudioEventRTS sound(*(AudioEventRTS *)((char *)misc + 0xa80));
		sound.setObjectID(getID());
		TheAudio->addAudioEvent(&sound);
	}
}
