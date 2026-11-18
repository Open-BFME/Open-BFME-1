// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <list>

// FlammableUpdate::onDamage, retail 0x002940D0 (346 bytes); ilt_oracle CONFIRMS
// the name.  The receiver is the DamageModuleInterface subobject at +0x20.
// BFME adds an underwater guard ahead of Zero Hour's flame-limit bookkeeping,
// and after a successful ignition either splash-damages every contained object
// with half of the aflame damage amount (at least 1) or notifies the contain
// module.  Unwitnessed members keep their offsets.

#include "../../../../Include/Common/ScalarTypes.h"



typedef int ObjectID;
#define NULL 0

#include "../../../../Include/Common/Enums/DamageType.h"
#include "../../../../Include/Common/Enums/DeathType.h"

class DamageInfo
{
public:
	DamageInfo();
	virtual void crc();

	struct
	{
		void *_vptr;
		ObjectID m_sourceID;
		unsigned char m_pad0c[4];
		DamageType m_damageType;
		unsigned char m_pad14[4];
		DeathType m_deathType;
		Real m_amount;
		unsigned char m_pad20[0x2c];
	} in;
	struct
	{
		void *_vptr;
		Real m_actualDamageDealt;
		Real m_actualDamageClipped;
		Bool m_noEffect;
	} out;
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
typedef _STL::list<Object *> ContainedItemsList;

class ContainModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b();
	virtual void s1c();
	virtual void slot1d(Int how);
	virtual void s1e(); virtual void s1f();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s2a(); virtual void s2b();
	virtual void s2c(); virtual void s2d(); virtual void s2e(); virtual void s2f();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
	virtual void s38(); virtual void s39(); virtual void s3a(); virtual void s3b();
	virtual void s3c(); virtual void s3d(); virtual void s3e(); virtual void s3f();
	virtual void s40();
	virtual const ContainedItemsList *getContainedItemsList();
};


class Object
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c();
	virtual void attemptDamage(DamageInfo *damageInfo);

	ObjectID getID() const { return m_id; }
	UnsignedInt getStatusWord() const { return m_status; }
	ContainModuleInterface *getContain() const { return m_contain; }

	unsigned char m_pad04[0x34];
	Real m_x;
	Real m_y;
	unsigned char m_pad40[0x34];
	ObjectID m_id;
	unsigned char m_pad78[0x18];
	UnsignedInt m_status;
	unsigned char m_pad94[0x168];
	ContainModuleInterface *m_contain;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ);
};
extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

class FlammableUpdateModuleData
{
public:
	unsigned char m_pad00[0x14];
	Int m_aflameDamageAmount;
	unsigned char m_pad18[4];
	Real m_flameDamageLimitData;
	UnsignedInt m_flameDamageExpirationDelay;
	unsigned char m_pad24[0x10];
	Bool m_flag34;
};

class UpdateModuleFront
{
public:
	virtual ~UpdateModuleFront();
	const FlammableUpdateModuleData *getFlammableUpdateModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const FlammableUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x14];
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
};

class FlammableUpdate : public UpdateModuleFront, public DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	void tryToIgnite();

private:
	unsigned char m_pad24[0x14];
	Real m_flameDamageLimit;
	UnsignedInt m_lastFlameDamageDealt;
	unsigned char m_pad40[8];
	ObjectID m_field48;
};

// ?onDamage@FlammableUpdate@@UAEXPAVDamageInfo@@@Z
void FlammableUpdate::onDamage(DamageInfo *damageInfo)
{
	if (damageInfo->out.m_actualDamageClipped > 0.0f)
		m_field48 = damageInfo->in.m_sourceID;

	Object *me = getObject();
	Bool underwater = TheTerrainLogic->isUnderwater(me->m_x, me->m_y, NULL, NULL);
	if (damageInfo->in.m_damageType == DAMAGE_FLAME && !underwater)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if ((Int)(now - getFlammableUpdateModuleData()->m_flameDamageExpirationDelay) > (Int)m_lastFlameDamageDealt)
			m_flameDamageLimit = getFlammableUpdateModuleData()->m_flameDamageLimitData;
		m_lastFlameDamageDealt = now;

		if ((me->getStatusWord() & 0xc00) == 0)
		{
			m_flameDamageLimit -= damageInfo->out.m_actualDamageDealt;
			if (m_flameDamageLimit <= 0.0f)
			{
				tryToIgnite();
				const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
				if (data->m_flag34 && me->getContain())
				{
					DamageInfo damage;
					Int half = data->m_aflameDamageAmount / 2;
					damage.in.m_amount = (Real)_STL::max(half, 1);
					damage.in.m_sourceID = me->getID();
					damage.in.m_damageType = DAMAGE_FLAME;
					damage.in.m_deathType = DEATH_BURNED;
					const ContainedItemsList *items = me->getContain()->getContainedItemsList();
					if (items)
					{
						for (ContainedItemsList::const_iterator it = items->begin(); it != items->end(); )
						{
							Object *rider = *it;
							++it;
							if (rider)
								rider->attemptDamage(&damage);
						}
					}
				}
				else if (me->getContain())
				{
					me->getContain()->slot1d(2);
				}
			}
		}
	}
}
