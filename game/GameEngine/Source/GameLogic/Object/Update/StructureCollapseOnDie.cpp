// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Object;
class DamageInfo;

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

class StructureCollapseModuleDataView
{
public:
	unsigned char m_unreconstructed00[8];
	DieMuxData m_dieMuxData;
};

class AIUpdateInterface
{
public:
	void markAsDead();
};

class StructureCollapseObjectView
{
public:
	unsigned char m_unreconstructed00[0x204];
	AIUpdateInterface *m_aiUpdate;
};

class GameLogic
{
public:
	void deselectObject(Object *object, PlayerMaskType players, Bool affectSelected);
};

extern GameLogic *TheGameLogic;

class StructureCollapseUpdate
{
public:
	virtual void onDie(const DamageInfo *damageInfo);

private:
	Object *getRetailObject() const
	{
		return *(Object **)((const char *)this - 0x18);
	}

	const StructureCollapseModuleDataView *getRetailModuleData() const
	{
		return *(const StructureCollapseModuleDataView **)((const char *)this - 0x1c);
	}

protected:
	void beginStructureCollapse(const DamageInfo *damageInfo);
};

// ?onDie@StructureCollapseUpdate@@UAEXPBVDamageInfo@@@Z
void StructureCollapseUpdate::onDie(const DamageInfo *damageInfo)
{
	const StructureCollapseModuleDataView *moduleData = getRetailModuleData();
	if (!moduleData->m_dieMuxData.isDieApplicable(getRetailObject(), damageInfo))
		return;

	AIUpdateInterface *ai =
		((StructureCollapseObjectView *)getRetailObject())->m_aiUpdate;
	if (ai != 0)
		ai->markAsDead();

	TheGameLogic->deselectObject(getRetailObject(), 0xffff, true);
	((StructureCollapseUpdate *)((char *)this - 0x20))->beginStructureCollapse(damageInfo);
}
