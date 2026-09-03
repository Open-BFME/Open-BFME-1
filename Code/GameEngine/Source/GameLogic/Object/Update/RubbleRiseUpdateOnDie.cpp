// cl: /DNDEBUG /MD /EHsc

class Thing;
class DamageInfo;
class Object;

class ModuleData;

class RubbleRiseBase
{
public:
	RubbleRiseBase(Thing *, const ModuleData *);
	virtual ~RubbleRiseBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class RubbleRiseInterface1
{
public:
	virtual void reserved();
};

class RubbleRiseInterface2
{
public:
	virtual void reserved();
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public RubbleRiseBase,
	public RubbleRiseInterface1, public RubbleRiseInterface2
{
protected:
	void setWakeFrame(Object *object, UpdateSleepTime sleepTime);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class DieMuxData
{
public:
	bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

class RubbleRiseUpdateModuleData
{
private:
	unsigned char m_base[8];

public:
	DieMuxData m_dieMuxData;
};

class RubbleRiseUpdate : public UpdateModule, public DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo);

private:
	unsigned int m_phaseFrame;
	unsigned int m_nextRiseFrame;
	unsigned int m_riseState;
	float m_riseVelocity;
	float m_currentHeight;
	float m_rubbleHeight;
};

// ?onDie@RubbleRiseUpdate@@UAEXPBVDamageInfo@@@Z
void RubbleRiseUpdate::onDie(const DamageInfo *damageInfo)
{
	const RubbleRiseUpdateModuleData *data =
		(const RubbleRiseUpdateModuleData *)m_moduleData;
	if (data->m_dieMuxData.isDieApplicable(getObject(), damageInfo))
	{
		RubbleRiseUpdate *module =
			(RubbleRiseUpdate *)(unsigned char *)this;
		module->m_phaseFrame = 0;
		module->m_riseState = 0;
		module->m_riseVelocity = 0.0f;
		module->m_nextRiseFrame = 0;
		module->m_currentHeight = 0.0f;
		module->m_rubbleHeight = 0.0f;
		module->setWakeFrame(module->getObject(), UPDATE_SLEEP_NONE);
	}
}
