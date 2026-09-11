// cl: /DNDEBUG /DRELEASE_DEBUG_LOGGING /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

typedef int Int;
typedef float Real;
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

	private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xC8 - sizeof(Overridable)];
	UnsignedInt m_kindOf;
};

template <int NUM_BITS>
class BitFlags
{
	UnsignedInt m_bits[6];
};

typedef BitFlags<116> KindOfMaskType;

struct BattlePlanBonuses
{
	Real m_armorScalar;
	Int m_bombardment;
	Int m_searchAndDestroy;
	Int m_holdTheLine;
	Real m_sightRangeScalar;
	KindOfMaskType m_validKindOf;
	KindOfMaskType m_invalidKindOf;
};

class Thing
{
public:
	bool isAnyKindOf(const KindOfMaskType &mask) const;

};

class BodyModuleInterface;

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((unsigned char *)this + 0x200);
	}

	Real getVisionRange() const;
	void setVisionRange(Real range);
	Real getShroudClearingRange() const;
	void setShroudClearingRange(Real range);
	void setWeaponBonusCondition(Int condition)
	{
		*(UnsignedInt *)((unsigned char *)this + 0x2a0) |= 1u << condition;
	}
	void clearWeaponBonusCondition(Int condition)
	{
		*(UnsignedInt *)((unsigned char *)this + 0x2a0) &= ~(1u << condition);
	}
};

#define BODY_SLOT(n) virtual void bodySlot##n() = 0;
class __declspec(novtable) BodyModuleInterface
{
public:
	BODY_SLOT(00) BODY_SLOT(01) BODY_SLOT(02) BODY_SLOT(03)
	BODY_SLOT(04) BODY_SLOT(05) BODY_SLOT(06) BODY_SLOT(07)
	BODY_SLOT(08) BODY_SLOT(09) BODY_SLOT(10) BODY_SLOT(11)
	BODY_SLOT(12) BODY_SLOT(13) BODY_SLOT(14) BODY_SLOT(15)
	BODY_SLOT(16) BODY_SLOT(17) BODY_SLOT(18) BODY_SLOT(19)
	BODY_SLOT(20) BODY_SLOT(21) BODY_SLOT(22) BODY_SLOT(23)
	BODY_SLOT(24) BODY_SLOT(25)
	virtual void applyDamageScalar(Real scalar) = 0;
};
#undef BODY_SLOT

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;

// ?localApplyBattlePlanBonusesToObject@@YAHPAVObject@@PAX@Z
static int localApplyBattlePlanBonusesToObject(Object *obj, void *userData)
{
	const BattlePlanBonuses *bonus = (const BattlePlanBonuses *)userData;
	Object *objectToValidate = obj;
	Object *objectToModify = obj;

	ThingTemplate *thing = *(ThingTemplate **)((unsigned char *)obj + 0x04);
	Overridable *nextOverride = thing ? *(Overridable **)((unsigned char *)thing + 0x04) : 0;
	if (thing && nextOverride)
		thing = (ThingTemplate *)nextOverride->getFinalOverride();

	Bool isProjectile = (thing->m_kindOf & 0x02000000) != 0;
	if (isProjectile)
		objectToValidate = TheBfmeGameLogic->findObjectByID(
			*(ObjectID *)((unsigned char *)obj + 0x78));

	if (objectToValidate)
	{
		const KindOfMaskType *validKindOf = &bonus->m_validKindOf;
		if (objectToValidate->isAnyKindOf(*validKindOf))
		{
			if (!objectToValidate->isAnyKindOf(bonus->m_invalidKindOf))
			{
				if (!isProjectile)
				{
					if (bonus->m_armorScalar != 1.0f)
					{
						BodyModuleInterface *body = objectToModify->getBodyModule();
						UnicodeString unusedDisplayName;
						body->applyDamageScalar(bonus->m_armorScalar);
					}

					if (bonus->m_sightRangeScalar != 1.0f)
					{
						objectToModify->setVisionRange(
							obj->getVisionRange() * bonus->m_sightRangeScalar);
						objectToModify->setShroudClearingRange(
							obj->getShroudClearingRange() * bonus->m_sightRangeScalar);
					}
				}

				if (bonus->m_bombardment > 0)
					objectToModify->setWeaponBonusCondition(12);
				else
					objectToModify->clearWeaponBonusCondition(12);

				if (bonus->m_holdTheLine > 0)
					objectToModify->setWeaponBonusCondition(13);
				else
					objectToModify->clearWeaponBonusCondition(13);

				if (bonus->m_searchAndDestroy > 0)
					objectToModify->setWeaponBonusCondition(14);
				else
					objectToModify->clearWeaponBonusCondition(14);
			}
		}
	}

	return 1;
}

static int (*volatile keepLocalApplyBattlePlanBonusesToObject)(Object *, void *) =
	&localApplyBattlePlanBonusesToObject;
