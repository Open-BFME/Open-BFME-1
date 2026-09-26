// ?onDie@FXListDie@@UAEXPBVDamageInfo@@@Z
// partial score=0.75 date=2026-09-07
// cl: /DNDEBUG /MD /EHs-c-

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
	void doFXObj(const Object *primary, const Object *secondary) const;
	void doFXPos(const Coord3D *position, const Matrix3D *transform,
		Real radius, const Coord3D *secondary) const;
	static void doFXObj(const FXList *fx, const Object *primary,
		const Object *secondary);
	static void doFXPos(const FXList *fx, const Coord3D *position);
};

class BfmeThingCOF
{
public:
	bool bfmeAskCOF();
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
	unsigned int m_defaultDeathFX;
	unsigned char m_orientToObject;
};

static const FXList *getDefaultDeathFX(FXListDieModuleData *data)
{
	return (const FXList *)data->m_defaultDeathFX;
}

#define TheGameLogic (*(GameLogic **)0x012F0898)

extern void j_00011f77();
extern void j_00022bba();
extern void j_0001bb21();
extern void j_0001f253();

void FXList::doFXObj(const FXList *fx, const Object *primary,
	const Object *secondary)
{
	if (fx != 0)
	{
		BfmeThingCOF *cof = (BfmeThingCOF *)fx;
		typedef bool (BfmeThingCOF::*AskCall)();
		union { void *asVoid; AskCall asMember; } askCast;
		askCast.asVoid = (void *)j_00011f77;
		if (!(cof->*askCast.asMember)())
		{
			typedef void (FXList::*FXObjCall)(const Object *, const Object *) const;
			union { void *asVoid; FXObjCall asMember; } fxObjCast;
			fxObjCast.asVoid = (void *)j_00022bba;
			(fx->*fxObjCast.asMember)(primary, secondary);
		}
	}
}

void FXList::doFXPos(const FXList *fx, const Coord3D *position)
{
	if (fx != 0)
	{
		BfmeThingCOF *cof = (BfmeThingCOF *)fx;
		typedef bool (BfmeThingCOF::*AskCall)();
		union { void *asVoid; AskCall asMember; } askCast;
		askCast.asVoid = (void *)j_00011f77;
		if (!(cof->*askCast.asMember)())
		{
			typedef void (FXList::*FXPosCall)(const Coord3D *,
				const Matrix3D *, Real, const Coord3D *) const;
			union { void *asVoid; FXPosCall asMember; } fxPosCast;
			fxPosCast.asVoid = (void *)j_0001bb21;
			(fx->*fxPosCast.asMember)(position, 0, 0, 0);
		}
	}
}

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

	const FXList *getDefaultDeathFX() const
	{
		return (const FXList *)getFXListDieModuleData()->m_defaultDeathFX;
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

	if (self->getDefaultDeathFX() == 0)
		return;
	FXListDieModuleData *moduleData = self->getFXListDieModuleData();
	if (moduleData->m_orientToObject)
	{
		typedef Object *(GameLogic::*FindCall)(ObjectID);
		union { void *asVoid; FindCall asMember; } findCast;
		findCast.asVoid = (void *)j_0001f253;
		Object *damageDealer = (TheGameLogic->*findCast.asMember)(
			info->m_sourceID);
		FXList *fxList = (FXList *)self->getDefaultDeathFX();
		if (fxList == 0)
			return;
		Object *owner = self->getObject();
		BfmeThingCOF *cof = (BfmeThingCOF *)fxList;
		typedef bool (BfmeThingCOF::*AskCall)();
		union { void *asVoid; AskCall asMember; } askCast;
		askCast.asVoid = (void *)j_00011f77;
		if ((cof->*askCast.asMember)())
			return;
		typedef void (FXList::*FXObjCall)(const Object *, const Object *) const;
		union { void *asVoid; FXObjCall asMember; } fxObjCast;
		fxObjCast.asVoid = (void *)j_00022bba;
		(fxList->*fxObjCast.asMember)(owner, damageDealer);
		return;
	}

	FXList *fxList = (FXList *)self->getDefaultDeathFX();
	if (fxList == 0)
		return;
	Object *owner = self->getObject();
	BfmeThingCOF *cof = (BfmeThingCOF *)fxList;
	typedef bool (BfmeThingCOF::*AskCall)();
	union { void *asVoid; AskCall asMember; } askCast;
	askCast.asVoid = (void *)j_00011f77;
	if ((cof->*askCast.asMember)())
		return;
	typedef void (FXList::*FXPosCall)(const Coord3D *, const Matrix3D *,
		Real, const Coord3D *) const;
	union { void *asVoid; FXPosCall asMember; } fxPosCast;
	fxPosCast.asVoid = (void *)j_0001bb21;
	(fxList->*fxPosCast.asMember)(&owner->m_position, 0, 0, 0);
}
