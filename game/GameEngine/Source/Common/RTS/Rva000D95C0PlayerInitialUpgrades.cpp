// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// The retail body walks PlayerTemplate::InitialUpgrades and grants each
// resolved template to the Player with complete status.

#include "ascii_string.h"

struct BfmeLegendStringVec
{
	BfmeLegendStringVec(const BfmeLegendStringVec &other);
	~BfmeLegendStringVec();

	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

class AttributeModifierAuraUpdateModuleDataMemberB : public BfmeLegendStringVec
{
public:
	AttributeModifierAuraUpdateModuleDataMemberB(
		const AttributeModifierAuraUpdateModuleDataMemberB &other) :
		BfmeLegendStringVec(other)
	{
	}
	~AttributeModifierAuraUpdateModuleDataMemberB();
};

class UpgradeTemplate;
class Upgrade;

class PlayerTemplate
{
public:
	char m_prefix[0xe8];
	AttributeModifierAuraUpdateModuleDataMemberB m_initialUpgrades;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status);
};

class Rva000D95C0Player
{
public:
	void applyInitialUpgrades();

private:
	char *m_vtable;
	const PlayerTemplate *m_playerTemplate;
};

// Address-derived name. Retail uses this helper from the Player upgrade path.
void Rva000D95C0Player::applyInitialUpgrades()
{
	if (m_playerTemplate != 0)
	{
		AttributeModifierAuraUpdateModuleDataMemberB upgrades(
			m_playerTemplate->m_initialUpgrades);
		int count = upgrades.m_finish - upgrades.m_start;
		int index = 0;
		if (count > 0)
		{
			do
			{
				const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(
					upgrades.m_start[index]);
				if (upgrade != 0)
					((Player *)this)->addUpgrade(upgrade, UPGRADE_STATUS_COMPLETE);
				++index;
			}
			while (index < count);
		}
	}
}
