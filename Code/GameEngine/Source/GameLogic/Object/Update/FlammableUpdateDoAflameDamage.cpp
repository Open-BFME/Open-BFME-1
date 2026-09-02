// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00293800: FlammableUpdate::doAflameDamage. ZH body at
// FlammableUpdate.cpp:226 with BFME DamageInfo field offsets (sourceID at
// input+4, damage type at +0xC, death type at +0x14, amount at +0x18) and
// DAMAGE_FLAME=6 / DEATH_BURNED=3.

enum DamageType
{
	DAMAGE_FLAME = 6
};

enum DeathType
{
	DEATH_BURNED = 3
};

class DamageInfo
{
public:
	DamageInfo();

	unsigned char m_pad00[8];
	int m_sourceID;
	unsigned char m_pad0C[4];
	int m_damageType;
	unsigned char m_pad14[4];
	int m_deathType;
	float m_amount;
	unsigned char m_pad20[0x3c];
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void attemptDamage(DamageInfo *info);
};

class FlammableUpdateModuleData
{
private:
	unsigned char m_pad00[0x14];

public:
	int m_aflameDamageAmount;
};

class FlammableUpdate
{
public:
	void doAflameDamage();

private:
	void *m_vtable;
	const FlammableUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x3c];
	int m_sourceID;
};

// ?doAflameDamage@FlammableUpdate@@QAEXXZ
void FlammableUpdate::doAflameDamage()
{
	const FlammableUpdateModuleData *data = m_moduleData;
	Object *obj = m_object;
	DamageInfo info;
	info.m_amount = (float)data->m_aflameDamageAmount;
	info.m_sourceID = m_sourceID;
	info.m_damageType = DAMAGE_FLAME;
	info.m_deathType = DEATH_BURNED;
	obj->attemptDamage(&info);
}
