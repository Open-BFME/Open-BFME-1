// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: GiveUpgradeUpdateModuleData ctor
// Base call, vtbl, zeros +0x254..+0x268, float +0x26c=0.025, byte +0x270=0.

class GiveUpgradeUpdateModuleDataBase
{
public:
	GiveUpgradeUpdateModuleDataBase();
	virtual void giveUpgradeModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x250];
};

extern "C" char GiveUpgradeUpdateModuleData_vtbl;

class __declspec(novtable) GiveUpgradeUpdateModuleData
	: public GiveUpgradeUpdateModuleDataBase
{
public:
	GiveUpgradeUpdateModuleData();

private:
	unsigned int m_254;
	unsigned int m_258;
	unsigned int m_25c;
	// Named factory 0x0011AB80 passes ILT 0x00010CEE -> 0x0025D970.
	// Its own FieldParse table at RVA 0x00CB51F0 witnesses these five
	// names: GiveUpgradeEffect/+260, SpawnOutFX/+264, GiveUpgradeSound/+268,
	// FadeOutSpeed/+26c and DeliverUpgrade/+270. Preserve this constructor
	// view as raw four-byte storage: +26c is float data in parseReal
	// (0x00852B20) and the named update body (0x0025E4B0).
	unsigned int m_giveUpgradeEffect;
	unsigned int m_spawnOutFX;
	unsigned int m_giveUpgradeSound;
	unsigned int m_fadeOutSpeed;
	unsigned char m_deliverUpgrade;
};

// ??0GiveUpgradeUpdateModuleData@@QAE@XZ
GiveUpgradeUpdateModuleData::GiveUpgradeUpdateModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&GiveUpgradeUpdateModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_254) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_258) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_25c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_giveUpgradeEffect) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_spawnOutFX) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_giveUpgradeSound) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_deliverUpgrade) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_fadeOutSpeed) = 0x3CCCCCCDu; // ~0.025f
}
