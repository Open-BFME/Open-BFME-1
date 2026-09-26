// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: SpecialAbilityUpdate::killSpecialObjects, retail 0x002A67A0.

typedef int ObjectID;

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

enum SpecialPowerType
{
	SPECIAL_MISSILE_DEFENDER_LASER_GUIDED_MISSILES = 0x15
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType() const
	{
		const SpecialPowerTemplate *self;
		Overridable *overrideTemplate = m_nextOverride;

		if ( overrideTemplate )
		{
			if ( overrideTemplate->m_nextOverride )
				overrideTemplate = overrideTemplate->m_nextOverride->friend_getFinalOverride();

			self = (const SpecialPowerTemplate *)overrideTemplate;
		}
		else
		{
			self = this;
		}

		return self->m_specialPowerType;
	}

private:
	unsigned char m_unmodelled_08[0x14 - 8];
	SpecialPowerType m_specialPowerType;
};

class Weapon;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};

class Object
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const
	{
		return reinterpret_cast<const WeaponSet *>(
			reinterpret_cast<const unsigned char *>(this) + 0x264)->getWeaponInWeaponSlot(slot);
	}

	void setWeaponLock(int weaponSlot, int lockType);
};

struct ObjectLookupNode
{
	ObjectLookupNode *next;
	ObjectID id;
	Object *object;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if ( id == 0 )
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if ( it == m_objHash.end() )
			return 0;

		return (*it).second;
	}

	void destroyObject(Object *object);

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1D8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class SpecialAbilityUpdate
{
	protected:
	void killSpecialObjects();

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_00C[0xCC - 0x0C];
	_STL::list<ObjectID> m_specialObjectIDList;
	unsigned int m_specialObjectEntries;
};

// ?killSpecialObjects@SpecialAbilityUpdate@@IAEXXZ
void SpecialAbilityUpdate::killSpecialObjects()
{
	const SpecialAbilityUpdateModuleData *data = m_moduleData;
	const SpecialPowerTemplate *spTemplate = data->m_specialPowerTemplate;
	Object *specialObject;

	_STL::list<ObjectID>::iterator i;
	for ( i = m_specialObjectIDList.begin(); i != m_specialObjectIDList.end(); ++i )
	{
		specialObject = TheGameLogic->findObjectByID(*i);
		if ( specialObject )
		{
			TheGameLogic->destroyObject(specialObject);
		}
	}

	m_specialObjectIDList.clear();
	m_specialObjectEntries = 0;

	switch ( spTemplate->getSpecialPowerType() )
	{
		case SPECIAL_MISSILE_DEFENDER_LASER_GUIDED_MISSILES:
		{
			Object *object = m_object;
			Weapon *weapon = object->getWeaponInWeaponSlot(PRIMARY_WEAPON);
			if ( weapon )
			{
				object->setWeaponLock(PRIMARY_WEAPON, 1);
			}
			break;
		}
	}
}
