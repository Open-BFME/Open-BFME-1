// cl: /DNDEBUG /MD /EHsc

extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_UNREADY = 5
};

class Object;
class ModuleData;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual Real getInitialHealth() const = 0;
	virtual Real getHealth() const = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void clearRecentObjectState() = 0;
};

class Object
{
public:
	char m_pad04[0x34];
	Coord3D m_position;
	char m_pad44[0x1bc];
	BodyModuleInterface *m_bodyModule;
	char m_pad204[0x1c];
	Real m_field220;
	char m_pad224[0x120];
	unsigned char m_privateStatus;

	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void applyHealth(Real value, Object *source, int reason) = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void clearRecentObjectState() = 0;
};

class ModuleData
{
public:
	char m_pad00[0x20];
	union
	{
		Real m_field20;
		UnsignedInt m_field20Bits;
	};
	char m_pad24[4];
	void *m_ocl;
	Bool m_field2c;
};

class GettingBuiltBehaviorDeepBase
{
public:
	virtual ~GettingBuiltBehaviorDeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class GettingBuiltBehaviorInterface1
{
public:
	virtual void slot00() = 0;
};

class GettingBuiltBehaviorUpdateInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual void getDisabledTypesToProcess() = 0;
};

class GettingBuiltBehaviorUpdateModule :
	public GettingBuiltBehaviorDeepBase,
	public GettingBuiltBehaviorInterface1,
	public GettingBuiltBehaviorUpdateInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_indexInUpdate;
};

class GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Bool rva001FE4A0() = 0;
};

class GettingBuiltBehavior :
	public GettingBuiltBehaviorUpdateModule,
	public GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual UpdateSleepTime update();

	Bool m_field24;
	UnsignedInt m_field28;
	UnsignedInt m_field2c;
	Bool m_field30;
	Bool m_field31;
	Bool m_field32;
	Bool m_field33;
	Bool m_field34;
	Bool m_field35;
	Bool m_field36;
	UnsignedInt m_field38;
};

class BfmeItemE63
{
public:
	char m_pad00[0x14];
	void *m_field14;
	char m_pad18[0x0c];
	Bool m_field24;
};

class Module
{
public:
	char m_pad00[0x14];
	void *m_field14;
	char m_pad18[0x0c];
	Bool m_field24;
};

class WeaponStore
{
};

// Retail routes these calls through incremental-link thunks at these addresses.
extern void j_000402d2();
extern void j_0004b015();
extern void j_00035e5e();
extern void j_0000e6e7();
extern void j_00036449();
extern void j_000329cf();
extern void j_00035ee0();
extern void j_0002ea14();

// Carrier classes for the ILT-routed thiscalls: no bases, so the member
// pointer needs no this-adjustment and the call folds to a direct call.
class RecentSourceCarrier { };
class ItemValidCarrier { };
class WeaponCreateCarrier { };
class GettingBuiltCarrier { };

extern WeaponStore *TheWeaponStore;
extern const Real g_rva01075350;
extern Real g_012ADC90;
extern "C" Real __identifier("?g_012ADC90@@3MA") = 75.0f;
#define BfmeObjectCreationRange g_012ADC90

// ?update@GettingBuiltBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime GettingBuiltBehavior::update()
{
	Object *object = m_object;
	ModuleData *data = (ModuleData *)m_moduleData;
	typedef Bool (RecentSourceCarrier::*RecentSourceFn)(UnsignedInt *, UnsignedInt) const;
	union { void (*fn)(); RecentSourceFn call; } recentSource = { j_000402d2 };
	typedef Bool (ItemValidCarrier::*ValidFn)();
	union { void (*fn)(); ValidFn call; } itemValid = { j_0004b015 };
	typedef void (WeaponCreateCarrier::*CreateFn)(void *, Object *, void *);
	union { void (*fn)(); CreateFn call; } weaponCreate = { j_00035e5e };
	typedef Module *(__cdecl *CastleMemberFn)(const Object *);
	typedef Bool (GettingBuiltCarrier::*BoolFn)();
	union { void (*fn)(); BoolFn call; } f001ff060 = { j_00036449 };
	typedef void (GettingBuiltCarrier::*VoidFn)();
	union { void (*fn)(); VoidFn call; } f001fec30 = { j_000329cf };
	union { void (*fn)(); VoidFn call; } f001ff5c0 = { j_00035ee0 };
	union { void (*fn)(); VoidFn call; } f001fe970 = { j_0002ea14 };
	Bool objectDead = (object->m_privateStatus & 1) != 0;
	if (m_field31 != objectDead && data->m_field2c)
	{
		m_field31 = objectDead;
		m_field28 = data->m_field20Bits;
		if (objectDead)
			m_field30 = 1;
	}

	UnsignedInt source = 0;
	Bool hasRecentSource;
	if (m_field35 || !((RecentSourceCarrier *)object->*recentSource.call)(&source, 4))
		hasRecentSource = false;
	else
		hasRecentSource = true;

	GettingBuiltBehavior *primary = (GettingBuiltBehavior *)((char *)this);
	Bool handled = ((GettingBuiltCarrier *)primary->*f001ff060.call)();
	GettingBuiltBehaviorSecondaryInterface *secondary;
	BfmeItemE63 *item;
	BodyModuleInterface *body;
	if (!objectDead)
	{
		if (data->m_field20 >= g_rva01075350)
		{
			if (hasRecentSource && !m_field36)
				goto cleanup;
		}

		secondary = (GettingBuiltBehaviorSecondaryInterface *)((char *)this + 0x20);
		if (secondary->rva001FE4A0())
		{
		item = (BfmeItemE63 *)((CastleMemberFn)(void *)j_0000e6e7)(
			*(Object **)((char *)this + 0x08));
		if (item != 0 && item->m_field14 != 0 && !item->m_field24 && ((ItemValidCarrier *)item->*itemValid.call)())
			goto handled_or_cleanup;
		}
		else
			goto handled_or_cleanup;

		if (!m_field36 && handled)
			return UPDATE_SLEEP_NONE;

		if (!m_field34 && object->m_field220 >= BfmeObjectCreationRange)
		{
			m_field34 = true;
			if (data->m_ocl != 0)
				((WeaponCreateCarrier *)TheWeaponStore->*weaponCreate.call)(data->m_ocl, object, &object->m_position);
		}

		body = object->m_bodyModule;
		if (body != 0)
		{
			Real health = body->getHealth() / (Real)m_field2c;
			object->applyHealth(health, object, 2);
			object->m_field220 = body->getInitialHealth() * 100.0f;
			if (!m_field35)
				body->clearRecentObjectState();
		}

		((GettingBuiltCarrier *)primary->*f001ff5c0.call)();
		return UPDATE_SLEEP_NONE;
	}

	cleanup:
	((GettingBuiltCarrier *)primary->*f001fec30.call)();
	handled_cleanup:
	((GettingBuiltCarrier *)primary->*f001ff5c0.call)();
	((GettingBuiltCarrier *)primary->*f001fe970.call)();
	return UPDATE_SLEEP_UNREADY;

	handled_or_cleanup:
	if (handled)
	{
		_WriteBarrier();
		return UPDATE_SLEEP_NONE;
	}
	goto handled_cleanup;
}
