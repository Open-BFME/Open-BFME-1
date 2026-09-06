// ?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z
// partial score=0.95 date=2026-09-06
// ?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>


typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpgradeStatusType
{
	UPGRADE_STATUS_COMPLETE = 2
};

class AsciiString
{
public:
	AsciiString(const AsciiString &);
	~AsciiString();
};

class UpgradeTemplate
{
public:
	void *m_vtable;
	Int m_type;
};

struct BfmeZ1095B
{
public:
	void *m_vtable;
	Int m_type;
};

class BfmeQ1095A
{
public:
	BfmeZ1095B *bfmeGet1095(Int);
};

class BfmeR1094;

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
};

class Upgrade;

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *, UpgradeStatusType);
};

class Object
{
public:
	Player *getControllingPlayer() const;

	char m_pad00[0x1a4];
	UnsignedInt m_field1a4;
};

class SpecialPowerModule
{
public:
	void finishSpecialPower(UnsignedInt);
};

class PlayerUpgradeSpecialPowerModuleData
{
public:
	char m_pad00[0x210];
	_STL::vector<AsciiString> m_upgradeNames;
};

class PlayerUpgradeSpecialPower
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
	virtual void startPowerRecharge();

	virtual void doSpecialPower(UnsignedInt);
};

struct PlayerUpgradeSpecialPowerPrimary
{
	char m_pad00[4];
	PlayerUpgradeSpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

static PlayerUpgradeSpecialPowerPrimary *primary(PlayerUpgradeSpecialPower *self)
{
	return (PlayerUpgradeSpecialPowerPrimary *)((char *)self - 0x10);
}

#define TheUpgradeCenter (*(BfmeQ1095A **)0x012EF188)

// ?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z
void PlayerUpgradeSpecialPower::doSpecialPower(UnsignedInt)
{
	Player *player;
	BfmeZ1095B *upgrade;
	if (primary(this)->m_object->m_field1a4 != 0)
		return;

	startPowerRecharge();
	_STL::vector<AsciiString> upgradeNames = primary(this)->m_moduleData->m_upgradeNames;
	for (Int i = 0; i < (Int)(upgradeNames.end() - upgradeNames.begin()); ++i)
	{
		upgrade =
			TheUpgradeCenter->bfmeGet1095((Int)(unsigned int)(upgradeNames.begin() + i));
		if (upgrade != 0 && upgrade->m_type == 0)
		{
			player = (Player *)((BfmeK1094 *)primary(this)->m_object)->bfmeCur1094();
			player->addUpgrade((const UpgradeTemplate *)upgrade, UPGRADE_STATUS_COMPLETE);
		}
	}

	((SpecialPowerModule *)primary(this))->finishSpecialPower(0);
}
