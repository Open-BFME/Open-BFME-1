// cl: /DNDEBUG /MD /EHsc

// LifetimeUpdate::update, retail 0x00298010.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum DamageType
{
	DAMAGE_SNIPER = 8
};

enum DeathType
{
	DEATH_LIFETIME = 0
};

class DamageInfo
{
public:
	unsigned char m_pad00[8];
	int m_sourceID;
};

class LifetimeUpdateModuleData
{
public:
	virtual ~LifetimeUpdateModuleData();

private:
	unsigned char m_pad04[0x0c];

public:
	unsigned char m_waitForWakeup;
	unsigned char m_scoreKill;
	unsigned char m_pad12[2];
	int m_deadLifetime;

	bool isEnabled() const
	{
		return m_scoreKill != 0;
	}

	int getDeathType() const
	{
		return m_deadLifetime;
	}
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual DamageInfo *getLastDamageInfo() = 0;
};

class Object
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((char *)this + 0x200);
	}

	void kill(DamageType damageType, DeathType deathType);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class BFMEReportDamageSource
{
public:
	void report(Object *owner, int setting);
};

class LifetimeUpdate
{
public:
	virtual UpdateSleepTime update();

protected:
	Object *getObject() const
	{
		return *(Object **)((const unsigned char *)this - 8);
	}

	LifetimeUpdateModuleData *getLifetimeUpdateModuleData() const
	{
		return *(LifetimeUpdateModuleData **)((const unsigned char *)this - 0xc);
	}
};

extern GameLogic *TheGameLogic;

UpdateSleepTime LifetimeUpdate::update()
{
	register Object *self = getObject();
	LifetimeUpdateModuleData *data = getLifetimeUpdateModuleData();
	if ((*((volatile UnsignedInt *)((char *)self + 0x120)) & 0x10000) != 0)
		return UPDATE_SLEEP_NONE;

	if (data->isEnabled())
	{
		Object *killer = TheGameLogic->findObjectByID(
			self->getBodyModule()->getLastDamageInfo() != 0
				? self->getBodyModule()->getLastDamageInfo()->m_sourceID
				: 0);
		if (killer != 0)
			((BFMEReportDamageSource *)killer)->report(self, 1);
	}

	self->kill(DAMAGE_SNIPER, (DeathType)data->getDeathType());
	return UPDATE_SLEEP_FOREVER;
}
