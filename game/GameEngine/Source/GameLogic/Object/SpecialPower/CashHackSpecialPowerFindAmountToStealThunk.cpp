// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashHackSpecialPower.h
enum ScienceType
{
	SCIENCE_UNRECONSTRUCTED
};

class Player
{
public:
	bool hasScience(ScienceType science) const;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

struct CashHackUpgrade
{
	ScienceType m_science;
	int m_amountToSteal;
};

struct CashHackUpgradeVector
{
	CashHackUpgrade *m_begin;
	CashHackUpgrade *m_end;
	CashHackUpgrade *m_capacity;

	const CashHackUpgrade *begin(void) const { return m_begin; }
	const CashHackUpgrade *end(void) const { return m_end; }
};

class CashHackSpecialPowerModuleData
{
	char m_beforeUpgrades[0x210];

public:
	CashHackUpgradeVector m_upgrades;
	int m_defaultAmountToSteal;
};

class CashHackSpecialPower
{
	char m_beforeModuleData[4];
	CashHackSpecialPowerModuleData *m_moduleData;
	Object *m_object;

protected:
	int findAmountToSteal() const;
};

extern void j_00020824();
extern void j_0000943f();

int CashHackSpecialPower::findAmountToSteal() const
{
	const CashHackSpecialPowerModuleData *d = m_moduleData;
	typedef Player *(Object::*GetController)(void) const;
	union { void (*fn)(); GetController call; } getController = { j_00020824 };
	const Player *controller = (m_object->*getController.call)();
	if (controller != 0)
	{
		typedef bool (Player::*HasScience)(ScienceType) const;
		union { void (*fn)(); HasScience call; } hasScience = { j_0000943f };
		for (const CashHackUpgrade *it = d->m_upgrades.begin();
			it != d->m_upgrades.end();
			++it)
		{
			if ((controller->*hasScience.call)(it->m_science))
				return it->m_amountToSteal;
		}
	}
	return d->m_defaultAmountToSteal;
}
