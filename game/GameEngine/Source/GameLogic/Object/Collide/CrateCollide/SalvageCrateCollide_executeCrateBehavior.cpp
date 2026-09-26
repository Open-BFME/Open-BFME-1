// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// SalvageCrateCollide::executeCrateBehavior (retail 0x002184D0, 263 B).
// Identity: SalvageCrateCollide vtable 0x010AA8CC slot 10 -> ILT 0x0003C074 ->
// 0x002184D0. The random roll is 0x002181C0, a separate out-of-line member of
// this TU (same SalvageCrateCollide.cpp file string and line 0x44, same
// module-data +0x5c chance) that returns 2 or 3 and is auto-inlined here.
// Retail FuncInfo 0x00DFB804 keeps six unwind states: 0->-1 1->0 2->1 and
// 3->-1 4->3 with no cleanup, then 5->-1 destroying the rank text. The roll can
// never produce outcomes 0 and 1, so the optimizer dropped those branches and
// only their tracked lifetimes survive. What those branches did is
// unrecoverable; they are modelled below only by their lifetime counts.

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
	Int rva002181C0();
	void doMoney(Object *other);
};

// Retail keeps this out of line at 0x002181C0 (landed there under the
// placeholder ?bfmeRollAO@BfmeOwnAO@@QAEHXZ); only outcomes 2 and 3 exist.
// Defined here so the compiler inlines it into executeCrateBehavior as retail
// does; this TU's out-of-line copy is not a claim.
// ?rva002181C0@SalvageCrateCollide@@AAEHXZ present-unmatched
Int SalvageCrateCollide::rva002181C0()
{
	const SalvageCrateCollideModuleDataSlice *modData =
		getSalvageCrateCollideModuleData();
	if (GetGameLogicRandomValueReal(0.0f, 1.0f, g_bfmeFileAO, 0x44) < modData->m_levelChance)
		return 2;
	return 3;
}

Bool SalvageCrateCollide::executeCrateBehavior(Object *other)
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

	Int outcome = rva002181C0();
	if (outcome == 0)
	{
		// Unreachable: retail unwind states 0-2, three nested lifetimes.
		UnicodeString eliminated0;
		UnicodeString eliminated1;
		UnicodeString eliminated2;
		reinterpret_cast<BfmeA1254 *>(this)->bfmeDraw1254(
			reinterpret_cast<BfmeS1254 *>(other), reinterpret_cast<Int>(&eliminated2));
	}
	else if (outcome == 1)
	{
		// Unreachable: retail unwind states 3-4, two nested lifetimes.
		UnicodeString eliminated0;
		UnicodeString eliminated1;
		reinterpret_cast<BfmeA1254 *>(this)->bfmeDraw1254(
			reinterpret_cast<BfmeS1254 *>(other), reinterpret_cast<Int>(&eliminated1));
	}
	else if (outcome == 2)
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
