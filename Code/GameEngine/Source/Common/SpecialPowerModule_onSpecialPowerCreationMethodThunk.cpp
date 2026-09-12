// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef int ObjectID;

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

class SpecialPowerTemplate;
class Player;
class Object;

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	AsciiString getName(void) const;

	Bool isSharedNSync(void) const
	{
		return getFinalOverride()->m_sharedNSync;
	}

	Bool hasPublicTimer(void) const
	{
		return getFinalOverride()->m_hasPublicTimer;
	}

private:
	const SpecialPowerTemplate *getFinalOverride(void) const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}

	char m_pad[0x114 - 8];

public:
	Bool m_hasPublicTimer;
	Bool m_sharedNSync;
};

class SpecialPowerModuleData
{
public:
	char m_pad[8];
	SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_initiateSound;
	Bool m_startsPaused;
};

class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Player
{
public:
	void expressSpecialPowerReadyFrame(const SpecialPowerTemplate *, UnsignedInt);
	UnsignedInt getOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *);
	Int getPlayerIndex(void) const
	{
		return *(const Int *)((const char *)this + 0x24);
	}
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
	ObjectID getID(void) const
	{
		return *(const ObjectID *)((const char *)this + 0x74);
	}
};

class BfmeOutOfWeaponRangeObject
{
public:
	Bool isKindOf(KindOfType) const;
};

class InGameUI
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot0a(void);
	virtual void slot0b(void);
	virtual void slot0c(void);
	virtual void slot0d(void);
	virtual void slot0e(void);
	virtual void slot0f(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot1a(void);
	virtual void slot1b(void);
	virtual void slot1c(void);
	virtual void slot1d(void);
	virtual void slot1e(void);
	virtual void slot1f(void);
	virtual void slot20(void);
	virtual void addSuperweapon(Int, const AsciiString &, ObjectID,
		const SpecialPowerTemplate *);
};

extern InGameUI *TheInGameUI;

class SpecialPowerModule
{
public:
	virtual void slot00(void) const;
	virtual void slot01(void) const;
	virtual void slot02(void) const;
	virtual void slot03(void) const;
	virtual void slot04(void) const;
	virtual AsciiString getPowerName(void) const;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate(void) const;
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void pauseCountdown(Bool);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void startPowerRecharge(void);
	virtual void onSpecialPowerCreation(void);

private:
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return *(const SpecialPowerModuleData *const *)((const char *)this - 0xc);
	}

	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this - 8);
	}

	UnsignedInt m_availableOnFrame;
};

void SpecialPowerModule::onSpecialPowerCreation(void)
{
	startPowerRecharge();

	if (getSpecialPowerTemplate()->isSharedNSync())
	{
		Player *player = getObject()->getControllingPlayer();
		if (player)
		{
			player->expressSpecialPowerReadyFrame(
				getSpecialPowerTemplate(), TheGameLogic->getFrame());
			m_availableOnFrame = player->getOrStartSpecialPowerReadyFrame(
				getSpecialPowerTemplate());
		}
	}

	if (getSpecialPowerModuleData()->m_startsPaused)
		pauseCountdown(true);

	if (getSpecialPowerModuleData()->m_specialPowerTemplate->hasPublicTimer() == true)
	{
		if (getObject()->getControllingPlayer()
			&& ((BfmeOutOfWeaponRangeObject *)getObject())->isKindOf(
				(KindOfType)7))
		{
			TheInGameUI->addSuperweapon(
				getObject()->getControllingPlayer()->getPlayerIndex(),
				getPowerName(), getObject()->getID(),
				getSpecialPowerModuleData()->m_specialPowerTemplate);
		}
	}
}
