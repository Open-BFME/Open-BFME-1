// ?executeCrateBehavior@SalvageCrateCollide@@MAE_NPAVObject@@@Z
// partial score=0.977 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/asciistring_downloadmanager

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short wchar_t;

#include "Common/UnicodeString.h"

class Player;

class ExperienceTracker
{
public:
	Bool gainExpForLevel(Int levels, Bool playSound, Bool doAll);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ExperienceTracker *getExperienceTracker() const
	{
		return *reinterpret_cast<ExperienceTracker *const *>(
			reinterpret_cast<const char *>(this) + 0x210);
	}
};

struct BfmePlayerView
{
	char m_prefix[0x2c];
	Int m_playerType;
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;
extern char g_bfmeFileAO[];
extern float GetGameLogicRandomValueReal(float low, float high, char *file, Int line);

class BfmeS1254;

class BfmeA1254
{
public:
	void bfmeDraw1254(BfmeS1254 *object, Int text);
};

struct SalvageCrateCollideModuleDataSlice
{
	char m_prefix[0x5c];
	float m_levelChance;
	char m_padding60[0x70 - 0x60];
	Bool m_allowComputerPickup;
};

class ObjectModuleView
{
public:
	virtual ~ObjectModuleView() = 0;

protected:
	const void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterfaceView
{
public:
	virtual void getBehaviorInterface() = 0;
};

class CollideModuleInterfaceView
{
public:
	virtual void onCollide() = 0;
};

class CollideModuleView : public ObjectModuleView,
	public BehaviorModuleInterfaceView,
	public CollideModuleInterfaceView
{
};

class CrateCollideView : public CollideModuleView
{
protected:
	virtual Bool executeCrateBehavior(Object *other) = 0;

	Bool m_everExecuted;
};

class SalvageCrateCollide : public CrateCollideView
{
protected:
	virtual Bool executeCrateBehavior(Object *other);

	const SalvageCrateCollideModuleDataSlice *getSalvageCrateCollideModuleData() const
	{
		return reinterpret_cast<const SalvageCrateCollideModuleDataSlice *>(m_moduleData);
	}

private:
	void doMoney(Object *other);
};

Bool SalvageCrateCollide::executeCrateBehavior(Object *other)
{
	{
		const SalvageCrateCollideModuleDataSlice *filterData =
			getSalvageCrateCollideModuleData();
		if (!filterData->m_allowComputerPickup && other != 0)
		{
			Player *player = other->getControllingPlayer();
			if (player != 0 &&
				reinterpret_cast<const BfmePlayerView *>(player)->m_playerType == 1)
				return false;
		}
	}

	const SalvageCrateCollideModuleDataSlice *modData =
		getSalvageCrateCollideModuleData();
	const float randomNumber =
		GetGameLogicRandomValueReal(0.0f, 1.0f, g_bfmeFileAO, 0x44);
	if (randomNumber < modData->m_levelChance)
	{
		if (other != 0 && other->getExperienceTracker() != 0)
		{
			other->getExperienceTracker()->gainExpForLevel(1, true, false);

			UnicodeString rankString;
			rankString.format(TheGameText->fetch("GUI:GainRank"), 1);
			reinterpret_cast<BfmeA1254 *>(this)->bfmeDraw1254(
				reinterpret_cast<BfmeS1254 *>(other), reinterpret_cast<Int>(&rankString));
		}
	}
	else
	{
		doMoney(other);
	}

	return true;
}
