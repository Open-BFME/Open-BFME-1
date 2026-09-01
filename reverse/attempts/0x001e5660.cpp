// ?getRemainingAmmo@Weapon@@QBEI_N@Z
// partial score=0.94 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc
typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef bool Bool;

class BfmeAmmoDescriptor
{
public:
	Bool isValid() const;
};

class BfmeAmmoProvider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual UnsignedInt getRemainingAmmo(const BfmeAmmoDescriptor *descriptor);
};

class Object
{
public:
	char m_padding[0x1fc];
	BfmeAmmoProvider *m_ammoProvider;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *g_bfmeAmmoGameLogic;

class WeaponTemplate
{
public:
	char m_padding[0x4e8];
	BfmeAmmoDescriptor m_ammoDescriptor;
};

enum WeaponStatus
{
	RELOADING_CLIP = 3
};

class Weapon
{
public:
	virtual void unused();
	UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;

private:
	WeaponStatus bfmeComputeStatus(Bool *changed) const;

	const WeaponTemplate *m_template;
	ObjectID m_ownerID;
	UnsignedInt m_weaponSlot;
	mutable WeaponStatus m_status;
	UnsignedInt m_ammoInClip;
};

UnsignedInt Weapon::getRemainingAmmo(Bool countReloadingAsEmpty) const
{
	const WeaponTemplate *weaponTemplate = m_template;
	if(weaponTemplate->m_ammoDescriptor.isValid())
	{
		Object *owner = g_bfmeAmmoGameLogic->findObjectByID(m_ownerID);
		BfmeAmmoProvider *provider = owner ? owner->m_ammoProvider : 0;
		if(provider)
		{
			UnsignedInt remaining = provider->getRemainingAmmo(&m_template->m_ammoDescriptor);
			return remaining;
		}
	}

	if(countReloadingAsEmpty && bfmeComputeStatus(0) == RELOADING_CLIP)
		return 0;

	return m_ammoInClip;
}
