// cl: /DNDEBUG /MD /EHsc


typedef float Real;
typedef bool Bool;
typedef int Int;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	unsigned char m_unmodelled_000[0x10];
	Int m_damageType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual const DamageInfo *getLastDamageInfo() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *reinterpret_cast<BodyModuleInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x200);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	Bool isEmpty() const;
	void doFXObj(const Object *, const Object *) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
struct AngleFXInfo
{
	Real angle;
	FXList *fxList;
};

class AngleFXInfoVector
{
public:
	typedef const AngleFXInfo *const_iterator;

	const_iterator begin() const
	{
		return m_begin;
	}

	const_iterator end() const
	{
		return m_end;
	}

private:
	const AngleFXInfo *m_begin;
	const AngleFXInfo *m_end;
	const AngleFXInfo *m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
class StructureToppleUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x48];
	unsigned int m_damageFXTypes;
	unsigned char m_unmodelled_04c[0x5c];
	AngleFXInfoVector m_angleFX;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
class StructureToppleUpdate
{
protected:
	virtual ~StructureToppleUpdate();
	void doAngleFX(Real curAngle, Real newAngle);
	StructureToppleUpdateModuleData *m_moduleData;
	Object *m_object;

	const StructureToppleUpdateModuleData *getModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject()
	{
		return m_object;
	}

	const Object *getObject() const
	{
		return m_object;
	}
};

static __forceinline Bool getDamageTypeFlag(unsigned int flags, Int damageType)
{
	return (flags & (1u << (damageType - 1))) != 0;
}

// ?doAngleFX@StructureToppleUpdate@@IAEXMM@Z
void StructureToppleUpdate::doAngleFX(Real curAngle, Real newAngle)
{
	const StructureToppleUpdateModuleData *data = getModuleData();
	const DamageInfo *lastDamageInfo =
		getObject()->getBodyModule()->getLastDamageInfo();
	Object *building;

	for (AngleFXInfoVector::const_iterator it = data->m_angleFX.begin();
		it != data->m_angleFX.end();
		++it)
	{
		if (it->angle > curAngle && it->angle <= newAngle)
		{
			if (lastDamageInfo == 0 ||
				getDamageTypeFlag(data->m_damageFXTypes,
					lastDamageInfo->m_damageType))
			{
				building = getObject();
				FXList *fxList = it->fxList;
				if (fxList != 0 && !fxList->isEmpty())
					fxList->doFXObj(building, 0);
			}
		}
	}
}
