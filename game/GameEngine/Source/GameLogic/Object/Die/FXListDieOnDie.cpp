// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x002554C0 callback ABI view: module data is at this-0x0c and the
// owning Object at this-0x08. The BFME module-data fields used here are +0x34
// (default death FX) and +0x38 (orient-to-object).

typedef int ObjectID;
typedef float Real;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class DamageInfo;
class Matrix3D;

class DieMuxData
{
public:
	bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

class FXList
{
public:
	virtual ~FXList();
	bool bfmeIsBlocked() const;
	void doFXObj(const Object *primary, const Object *secondary) const;
	void doFXPos(const Coord3D *position, const Matrix3D *transform,
		Real radius, const Coord3D *secondary) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class DamageInfo
{
	unsigned char m_padding00[8];

public:
	ObjectID m_sourceID;
};

class Object
{
	unsigned char m_padding00[0x38];

public:
	Coord3D m_position;
};

struct FXListDieModuleData
{
	unsigned char m_padding00[8];
	DieMuxData m_dieMuxData;
	unsigned char m_padding0c[0x34 - 0x0c];
	const FXList * volatile m_defaultDeathFX;
	bool m_orientToObject;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

extern void j_00011f77();
extern void j_00022bba();
extern void j_0001bb21();
extern void j_0001f253();


class FXListDie
{
public:
	FXListDieModuleData *getFXListDieModuleData() const
	{
		return *(FXListDieModuleData **)((unsigned char *)this - 0x0c);
	}

	Object *getObject() const
	{
		return *(Object **)((unsigned char *)this - 0x08);
	}

	bool isDieApplicable(const DamageInfo *damageInfo) const
	{
		return getFXListDieModuleData()->m_dieMuxData.isDieApplicable(
			getObject(), damageInfo);
	}

	virtual void onDie(const DamageInfo *damageInfo);
};

// ?onDie@FXListDie@@UAEXPBVDamageInfo@@@Z
void FXListDie::onDie(const DamageInfo *damageInfo)
{
	register FXListDie *self = this;
	register const DamageInfo *info = damageInfo;
	if (!self->isDieApplicable(info))
		return;

	FXListDieModuleData *moduleData = self->getFXListDieModuleData();
	if (moduleData->m_defaultDeathFX == 0)
		return;
	if (moduleData->m_orientToObject)
	{
		typedef Object *(GameLogic::*FindCall)(ObjectID);
		union { void *asVoid; FindCall asMember; } findCast;
		findCast.asVoid = (void *)j_0001f253;
		Object *damageDealer = (TheGameLogic->*findCast.asMember)(
			info->m_sourceID);
		FXList *fxList = (FXList *)moduleData->m_defaultDeathFX;
		Object *owner = self->getObject();
		if (fxList != 0)
		{
			typedef bool (FXList::*BlockedCall)() const;
			union { void *asVoid; BlockedCall asMember; } blockedCast;
			blockedCast.asVoid = (void *)j_00011f77;
			if (!(fxList->*blockedCast.asMember)())
			{
				typedef void (FXList::*FXObjCall)(const Object *, const Object *) const;
				union { void *asVoid; FXObjCall asMember; } fxObjCast;
				fxObjCast.asVoid = (void *)j_00022bba;
				(fxList->*fxObjCast.asMember)(owner, damageDealer);
			}
		}
		return;
	}

	FXList *fxList = (FXList *)moduleData->m_defaultDeathFX;
	Object *owner = self->getObject();
	if (fxList != 0)
	{
		typedef bool (FXList::*BlockedCall)() const;
		union { void *asVoid; BlockedCall asMember; } blockedCast;
		blockedCast.asVoid = (void *)j_00011f77;
		if (!(fxList->*blockedCast.asMember)())
		{
			typedef void (FXList::*FXPosCall)(const Coord3D *,
				const Matrix3D *, Real, const Coord3D *) const;
			union { void *asVoid; FXPosCall asMember; } fxPosCast;
			fxPosCast.asVoid = (void *)j_0001bb21;
			(fxList->*fxPosCast.asMember)(&owner->m_position, 0, 0, 0);
		}
	}
}
