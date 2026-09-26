// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
typedef int DeathType;

class Object;
class Drawable;

class GameLogic
{
public:
	char m_pad000[0x3c];
	UnsignedInt m_frame;

	UnsignedInt getFrame() const
	{
		return m_frame;
	}
};

extern GameLogic *TheGameLogic;

class PoisonedBehaviorModuleData
{
public:
	char m_pad000[8];
	UnsignedInt m_poisonDamageIntervalData;
	UnsignedInt m_poisonDurationData;
};

class DamageInfo
{
	public:
	char m_pad000[0x18];
	DeathType m_deathType;
	char m_pad01c[0x34];
	float m_actualDamageDealt;
};

class Drawable
{
public:
	char m_pad000[0x114];
	unsigned int m_status;

	void setTintStatus()
	{
		m_status |= 4;
	}
};

class Object
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
	virtual Drawable *getDrawable();
};

#pragma comment(linker, "/alternatename:?frameToSleepTime@UpdateModule@@IAE?AW4UpdateSleepTime@@IIII@Z=?j_000202a7@@YAXXZ")
#pragma comment(linker, "/alternatename:?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z=?j_000157da@@YAXXZ")

__forceinline UnsignedInt *minimum(UnsignedInt *a, UnsignedInt *b)
{
	return *a < *b ? a : b;
}

class UpdateModule
{
protected:
	void *m_vftable;
	PoisonedBehaviorModuleData *m_moduleData;
	Object *m_object;
	char m_pad00c[0x18];

	PoisonedBehaviorModuleData *getPoisonedBehaviorModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject() const
	{
		return m_object;
	}

	void setWakeFrame(Object *object, UpdateSleepTime sleep);
	UpdateSleepTime frameToSleepTime(UnsignedInt frame1, UnsignedInt frame2,
		UnsignedInt frame3, UnsignedInt frame4);
};

class PoisonedBehavior : public UpdateModule
{
	protected:
	void startPoisonedEffects(const DamageInfo *damageInfo);

	UpdateSleepTime calcSleepTime()
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (m_poisonOverallStopFrame == 0 || m_poisonOverallStopFrame == now)
			return UPDATE_SLEEP_FOREVER;
		return frameToSleepTime(m_poisonDamageFrame, m_poisonOverallStopFrame,
			UPDATE_SLEEP_FOREVER, UPDATE_SLEEP_FOREVER);
	}

private:
	UnsignedInt m_poisonDamageFrame;
	UnsignedInt m_poisonOverallStopFrame;
	float m_poisonDamageAmount;
	DeathType m_deathType;
};

// ?startPoisonedEffects@PoisonedBehavior@@IAEXPBVDamageInfo@@@Z
void PoisonedBehavior::startPoisonedEffects(const DamageInfo *damageInfo)
{
	const PoisonedBehaviorModuleData *data = getPoisonedBehaviorModuleData();
	UnsignedInt now = TheGameLogic->getFrame();

	m_poisonDamageAmount = damageInfo->m_actualDamageDealt;
	m_poisonOverallStopFrame = now + data->m_poisonDurationData;
	if (m_poisonDamageFrame != 0)
	{
		UnsignedInt nextDamageFrame = now + data->m_poisonDamageIntervalData;
		m_poisonDamageFrame = *minimum(&m_poisonDamageFrame, &nextDamageFrame);
	}
	else
		m_poisonDamageFrame = now + data->m_poisonDamageIntervalData;

	m_deathType = damageInfo->m_deathType;
	Drawable *drawable = getObject()->getDrawable();
	if (drawable)
		drawable->setTintStatus();

	setWakeFrame(getObject(), calcSleepTime());
}
