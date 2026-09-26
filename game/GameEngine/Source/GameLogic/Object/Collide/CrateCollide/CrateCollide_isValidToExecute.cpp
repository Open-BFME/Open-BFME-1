// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

template <int NUMBITS>
class BitFlags
{
private:
	unsigned char m_storage[0x18];
};

typedef BitFlags<116> KindOfMaskType;

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
	Bool isKindOfMulti(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear) const;
	Bool isAboveTerrainOrWater() const;
};

class Player
{
public:
	Bool hasScience(ScienceType science) const;

	Int getPlayerType() const
	{
		return *(const Int *)((const char *)this + 0x2C);
	}
};

struct BfmePrivateStatusBits
{
	bool m_effectivelyDead : 1;
	bool m_undetectedDefector : 1;
	unsigned char m_rest : 6;
};

struct BfmePrivateStatusByte
{
	unsigned char m_value : 8;
};

class Object : public Thing
{
public:
	Bool isNeutralControlled() const;
	Player *getControllingPlayer() const;

	void *getAIUpdateInterface() const
	{
		return m_ai;
	}

	Bool isEffectivelyDead() const
	{
		return m_privateStatusBits.m_effectivelyDead != 0;
	}

	unsigned char getIsUndetectedDefector() const
	{
		unsigned char status = m_privateStatusByte.m_value;
		status >>= 1;
		status = (unsigned char)~status;
		return status & 1;
	}

public:
	unsigned char m_pad0001[0x204 - 1];
	void *m_ai;
	unsigned char m_pad0208[0x344 - 0x208];
	union
	{
		unsigned char m_privateStatus;
		BfmePrivateStatusBits m_privateStatusBits;
		BfmePrivateStatusByte m_privateStatusByte;
	};
};

class ModuleData;
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class InlineCollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class CollideModule : public BehaviorModule,
	public InlineCollideModuleInterface,
	public ModuleInterface
{
};

class BfmeCrateCollideModuleData
{
public:
	unsigned char m_pad00[8];
	KindOfMaskType m_kindof;
	KindOfMaskType m_kindofnot;
	Bool m_isForbidOwnerPlayer;
	Bool m_isBuildingPickup;
	Bool m_isHumanOnlyPickup;
	unsigned char m_pad3B;
	ScienceType m_pickupScience;
};

class CrateCollide : public CollideModule
{
public:
	const BfmeCrateCollideModuleData *getCrateCollideModuleData() const
	{
		return *reinterpret_cast<const BfmeCrateCollideModuleData *const *>(
			reinterpret_cast<const char *>(this) + 0x04);
	}

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) + 0x08);
	}

protected:
	virtual Bool isValidToExecute(const Object *other) const;

private:
	Bool m_everExecuted;
};

#pragma comment(linker, "/alternatename:?isNeutralControlled@Object@@QBE_NXZ=?j_0001483a@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOfMulti@Thing@@QBE_NABV?$BitFlags@$0HE@@@0@Z=?j_0003dccb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isAboveTerrainOrWater@Thing@@QBE_NXZ=?j_00004386@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?hasScience@Player@@QBE_NW4ScienceType@@@Z=?j_0000943f@@YAXXZ")

// ?isValidToExecute@CrateCollide@@MBE_NPBVObject@@@Z
Bool CrateCollide::isValidToExecute(const Object *other) const
{
	if (other == 0)
	{
		_WriteBarrier();
		return false;
	}

	if (m_everExecuted)
		return false;

	if (other->isNeutralControlled())
		return false;

	const BfmeCrateCollideModuleData *md = getCrateCollideModuleData();
	Bool validBuildingAttempt = md->m_isBuildingPickup &&
		other->isKindOf(KINDOF_STRUCTURE);

	if (other->getAIUpdateInterface() == 0 && !validBuildingAttempt)
		return false;

	if (!other->isKindOfMulti(md->m_kindof, md->m_kindofnot))
		return false;

	if (other->isEffectivelyDead())
		return false;

	if (getObject()->isAboveTerrainOrWater() && !validBuildingAttempt)
		return false;

	if (md->m_isForbidOwnerPlayer &&
		getObject()->getControllingPlayer() == other->getControllingPlayer())
		return false;

	if (md->m_isHumanOnlyPickup &&
		other->getControllingPlayer() != 0 &&
		other->getControllingPlayer()->getPlayerType() != 0)
		return false;

	if (md->m_pickupScience != SCIENCE_INVALID &&
		other->getControllingPlayer() != 0 &&
		!other->getControllingPlayer()->hasScience(md->m_pickupScience))
		return false;

	return getObject()->getIsUndetectedDefector();
}
