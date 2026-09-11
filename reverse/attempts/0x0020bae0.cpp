// ?computeAggregateStates@SpawnBehavior@@QAEXXZ
// partial score=0.9 date=2026-09-10
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME's aggregate-state body uses the primary SpawnBehavior subobject.  The
// public Zero Hour header is a different layout, so keep this witness local.

#include <list>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

struct Rva0020BAE0Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(Real xValue, Real yValue, Real zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}

	void add(const Rva0020BAE0Coord3D &value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
	}

	void scale(Real factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;
	}

	void sub(const Rva0020BAE0Coord3D &value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
	}
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

class GameMessage
{
public:
	void appendBooleanArgument(Bool value);
	void appendObjectIDArgument(unsigned int value);
};

class Rva0020BAE0MessageStream
{
public:
	virtual void messageStreamSlot0();
	virtual void messageStreamSlot1();
	virtual void messageStreamSlot2();
	virtual void messageStreamSlot3();
	virtual void messageStreamSlot4();
	virtual void messageStreamSlot5();
	virtual void messageStreamSlot6();
	virtual void messageStreamSlot7();
	virtual void messageStreamSlot8();
	virtual void messageStreamSlot9();
	virtual void messageStreamSlot10();
	virtual void messageStreamSlot11();
	virtual void messageStreamSlot12();
	virtual GameMessage *appendMessage(Int messageType);
};

#define TheMessageStream (*(Rva0020BAE0MessageStream **)0x012ED5EC)

class Rva0020BAE0Drawable
{
public:
	Bool isSelected() const
	{
		return *reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const unsigned char *>(this) + 0x3AC) != 0;
	}
};

class Rva0020BAE0BodyModule
{
public:
	virtual void bodySlot0();
	virtual void bodySlot1();
	virtual void bodySlot2();
	virtual void bodySlot3();
	virtual Real getHealth();
	virtual void bodySlot5();
	virtual Real getMaxHealth();
	virtual void bodySlot7();
	virtual void bodySlot8();
	virtual void bodySlot9();
	virtual void bodySlot10();
	virtual void bodySlot11();
	virtual void bodySlot12();
	virtual void bodySlot13();
	virtual void bodySlot14();
	virtual void bodySlot15();
	virtual void bodySlot16();
	virtual void bodySlot17();
	virtual void bodySlot18();
	virtual void bodySlot19();
	virtual void bodySlot20();
	virtual void setInitialHealth(Real health);
};

class Rva0020BAE0SlavedUpdate
{
public:
	virtual void slavedSlot0();
	virtual void slavedSlot1();
	virtual void slavedSlot2();
	virtual void slavedSlot3();
	virtual Bool isSelfTasking();
};

class Rva0020BAE0BehaviorInterface
{
public:
	virtual void behaviorSlot0();
	virtual void behaviorSlot1();
	virtual void behaviorSlot2();
	virtual void behaviorSlot3();
	virtual void behaviorSlot4();
	virtual void behaviorSlot5();
	virtual void behaviorSlot6();
	virtual void behaviorSlot7();
	virtual void behaviorSlot8();
	virtual void behaviorSlot9();
	virtual void behaviorSlot10();
	virtual void behaviorSlot11();
	virtual void behaviorSlot12();
	virtual void behaviorSlot13();
	virtual void behaviorSlot14();
	virtual void behaviorSlot15();
	virtual void behaviorSlot16();
	virtual void behaviorSlot17();
	virtual void behaviorSlot18();
	virtual void behaviorSlot19();
	virtual void behaviorSlot20();
	virtual void behaviorSlot21();
	virtual void behaviorSlot22();
	virtual void behaviorSlot23();
	virtual void behaviorSlot24();
	virtual Rva0020BAE0SlavedUpdate *getSlavedUpdateInterface();
};

class Rva0020BAE0BehaviorModule;

class Object
{
public:
	virtual void objectSlot0();
	virtual void objectSlot1();
	virtual void objectSlot2();
	virtual void objectSlot3();
	virtual void objectSlot4();
	virtual void objectSlot5();
	virtual void objectSlot6();
	virtual void objectSlot7();
	virtual void objectSlot8();
	virtual void objectSlot9();
	virtual Rva0020BAE0Drawable *getDrawable();
	void maskObject(Bool mask);

	Rva0020BAE0BehaviorModule **getBehaviorModules()
	{
		return *reinterpret_cast<Rva0020BAE0BehaviorModule ***>(
			reinterpret_cast<unsigned char *>(this) + 0x1F0);
	}

	Rva0020BAE0BodyModule *getBodyModule() const
	{
		return *reinterpret_cast<Rva0020BAE0BodyModule *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x200);
	}

	const Rva0020BAE0Coord3D &getPosition() const
	{
		return *reinterpret_cast<const Rva0020BAE0Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}

	unsigned int getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const unsigned char *>(this) + 0x74);
	}

	void setHealthBoxOffset(const Rva0020BAE0Coord3D &offset)
	{
		*reinterpret_cast<Rva0020BAE0Coord3D *>(
			reinterpret_cast<unsigned char *>(this) + 0x24C) = offset;
	}
};

class Rva0020BAE0InGameUI
{
public:
	virtual void uiSlot0();
	virtual void uiSlot1();
	virtual void uiSlot2();
	virtual void uiSlot3();
	virtual void uiSlot4();
	virtual void uiSlot5();
	virtual void uiSlot6();
	virtual void uiSlot7();
	virtual void uiSlot8();
	virtual void uiSlot9();
	virtual void uiSlot10();
	virtual void uiSlot11();
	virtual void uiSlot12();
	virtual void uiSlot13();
	virtual void uiSlot14();
	virtual void uiSlot15();
	virtual void uiSlot16();
	virtual void uiSlot17();
	virtual void uiSlot18();
	virtual void uiSlot19();
	virtual void uiSlot20();
	virtual void uiSlot21();
	virtual void uiSlot22();
	virtual void uiSlot23();
	virtual void uiSlot24();
	virtual void uiSlot25();
	virtual void uiSlot26();
	virtual void uiSlot27();
	virtual void uiSlot28();
	virtual void uiSlot29();
	virtual void uiSlot30();
	virtual void uiSlot31();
	virtual void uiSlot32();
	virtual void uiSlot33();
	virtual void uiSlot34();
	virtual void uiSlot35();
	virtual void uiSlot36();
	virtual void uiSlot37();
	virtual void uiSlot38();
	virtual void uiSlot39();
	virtual void uiSlot40();
	virtual void uiSlot41();
	virtual void uiSlot42();
	virtual void uiSlot43();
	virtual void uiSlot44();
	virtual void uiSlot45();
	virtual void uiSlot46();
	virtual void uiSlot47();
	virtual void uiSlot48();
	virtual void uiSlot49();
	virtual void uiSlot50();
	virtual void uiSlot51();
	virtual void uiSlot52();
	virtual void uiSlot53();
	virtual void uiSlot54();
	virtual void uiSlot55();
	virtual void selectDrawable(Rva0020BAE0Drawable *drawable);
	virtual void uiSlot57();
	virtual void uiSlot58();
	virtual void uiSlot59();
	virtual void uiSlot60();
	virtual void uiSlot61();
	virtual void uiSlot62();
	virtual void uiSlot63();
	virtual void uiSlot64();
	virtual void uiSlot65();
	virtual void uiSlot66();
	virtual void uiSlot67();
	virtual void uiSlot68();
	virtual void uiSlot69();
	virtual void uiSlot70();
	virtual void uiSlot71();
	virtual void uiSlot72();
	virtual void uiSlot73();
	virtual void uiSlot74();
	virtual void uiSlot75();
	virtual void uiSlot76();
	virtual void uiSlot77();
	virtual void uiSlot78();
	virtual void uiSlot79();
	virtual void uiSlot80();
	virtual void uiSlot81();
	virtual void uiSlot82();
	virtual void uiSlot83();
	virtual void uiSlot84();
	virtual void uiSlot85();
	virtual void uiSlot86();
	virtual void uiSlot87();
	virtual void uiSlot88();
	virtual void uiSlot89();
	virtual void uiSlot90();
	virtual void uiSlot91();
	virtual void uiSlot92();
	virtual void setDisplayedMaxWarning(Bool displayed);
};

#define TheInGameUI (*(Rva0020BAE0InGameUI **)0x012F148C)

class Rva0020BAE0SpawnBehaviorModuleData
{
private:
	unsigned char m_pad00[0x08];

public:
	Int m_spawnNumberData;
};

class Rva0020BAE0ObjectModule
{
public:
	virtual void objectModuleSlot0();

protected:
	const Rva0020BAE0SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
};

class Rva0020BAE0BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceSlot0();
};

class Rva0020BAE0UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceSlot0();
};

class Rva0020BAE0BehaviorModule
	: public Rva0020BAE0ObjectModule,
	  public Rva0020BAE0BehaviorModuleInterface
{
public:
	virtual ~Rva0020BAE0BehaviorModule() {}

	Rva0020BAE0SlavedUpdate *getSlavedUpdateInterface()
	{
		return reinterpret_cast<Rva0020BAE0BehaviorInterface *>(
			reinterpret_cast<unsigned char *>(this) + 0x0C)->getSlavedUpdateInterface();
	}
};

class Rva0020BAE0UpdateModule
	: public Rva0020BAE0BehaviorModule,
	  public Rva0020BAE0UpdateModuleInterface
{
public:
	virtual ~Rva0020BAE0UpdateModule() {}

	Object *getObject()
	{
		return m_object;
	}
	const Rva0020BAE0SpawnBehaviorModuleData *getSpawnBehaviorModuleData()
	{
		return m_moduleData;
	}

private:
	unsigned int m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	unsigned int m_updateState;
};

class Rva0020BAE0SecondaryBase1
{
public:
	virtual void secondarySlot0();
	virtual void secondarySlot1();
	virtual void secondarySlot2();
	virtual void secondarySlot3();
	virtual void secondarySlot4();
	virtual void secondarySlot5();
	virtual void secondarySlot6();
	virtual void secondarySlot7();
	virtual void secondarySlot8();
	virtual void secondarySlot9();
	virtual void secondarySlot10();
	virtual void secondarySlot11();
	virtual void secondarySlot12();
	virtual void secondarySlot13();
	virtual void secondarySlot14();
};

class Rva0020BAE0SecondaryBase2
{
public:
	virtual void secondarySlot0();
	virtual void secondarySlot1();
};

class Rva0020BAE0SecondaryBase3
{
public:
	virtual void secondarySlot0();
	virtual void secondarySlot1();
	virtual void secondarySlot2();
};

class Rva0020BAE0SecondaryBase4
{
public:
	virtual void secondarySlot0();
};

class SpawnBehavior
	: public Rva0020BAE0UpdateModule,
	  public Rva0020BAE0SecondaryBase1,
	  public Rva0020BAE0SecondaryBase2,
	  public Rva0020BAE0SecondaryBase3,
	  public Rva0020BAE0SecondaryBase4
{
public:
	virtual void onDelete();
	virtual void getUpdateInterface();
	virtual void getDieInterface();
	virtual void getDamageInterface();
	virtual void getSpawnBehaviorInterface();
	virtual void update();
	virtual void onDie();
	virtual void onDamage();
	virtual void onHealing();
	virtual void onBodyDamageStateChange();
	virtual void maySpawnSelfTaskAI();
	virtual void onSpawnDeath();
	virtual void getClosestSlave();
	virtual void orderSlavesToAttackTarget();
	virtual void orderSlavesToAttackPosition();
	virtual void getCanAnySlavesAttackSpecificTarget();
	virtual void getCanAnySlavesUseWeaponAgainstTarget();
	virtual void canAnySlavesAttack();
	virtual void orderSlavesToGoIdle();
	virtual void orderSlavesDisabledUntil();
	virtual void orderSlavesToClearDisabled();
	virtual void giveSlavesStealthUpgrade();
	virtual void areAllSlavesStealthed();
	virtual void revealSlaves();
	virtual void doSlavesHaveFreedom();
	void computeAggregateStates();

private:
	unsigned char m_pad30[0x18];
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_active;
	unsigned char m_aggregateHealth;
	unsigned char m_initialBurstTimesInited;
	unsigned char m_pad4F;
	UnsignedInt m_spawnCount;
	UnsignedInt m_selfTaskingSpawnCount;
};

// ?computeAggregateStates@SpawnBehavior@@QAEXXZ
void SpawnBehavior::computeAggregateStates()
{
	if (!m_aggregateHealth)
		return;

	const Rva0020BAE0SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();
	Object *obj = getObject();

	Int spawnCount = 0;
	Int spawnCountMax = md->m_spawnNumberData;
	Rva0020BAE0Coord3D avgSpawnPos;
	avgSpawnPos.set(0.0f, 0.0f, 0.0f);
	Real acrHealth = 0.0f;
	Real avgHealthMax = 0.0f;

	Bool SomebodyIsSelected = false;
	Bool SomebodyIsNotSelected = false;
	Rva0020BAE0Drawable *spawnDraw = 0;
	Object *currentSpawn = 0;

	m_selfTaskingSpawnCount = 0;

	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin();
		iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID(*iter);

		if (currentSpawn)
		{
			for (Rva0020BAE0BehaviorModule **update = currentSpawn->getBehaviorModules();
				*update; ++update)
			{
				Rva0020BAE0SlavedUpdate *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != 0)
				{
					m_selfTaskingSpawnCount += sdu->isSelfTasking();
					break;
				}
			}

			avgSpawnPos.add(currentSpawn->getPosition());

			Rva0020BAE0BodyModule *body = currentSpawn->getBodyModule();
			acrHealth += body->getHealth();
			avgHealthMax += body->getMaxHealth();

			spawnDraw = currentSpawn->getDrawable();
			if (spawnDraw->isSelected())
				SomebodyIsSelected = true;
			else
				SomebodyIsNotSelected = true;

			++spawnCount;
		}
	}

	if (SomebodyIsSelected && (!obj->getDrawable()->isSelected() || SomebodyIsNotSelected))
	{
		GameMessage *teamMsg = TheMessageStream->appendMessage(0x3E9);
		teamMsg->appendBooleanArgument(false);

		if (SomebodyIsNotSelected)
		{
			for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin();
				iter != m_spawnIDs.end(); iter++)
			{
				currentSpawn = TheGameLogic->findObjectByID(*iter);
				if (currentSpawn)
				{
					spawnDraw = currentSpawn->getDrawable();
					if (!spawnDraw->isSelected())
					{
						TheInGameUI->selectDrawable(spawnDraw);
						TheInGameUI->setDisplayedMaxWarning(false);
						teamMsg->appendBooleanArgument(false);
						teamMsg->appendObjectIDArgument(currentSpawn->getID());
					}
				}
			}
		}

		if (!obj->getDrawable()->isSelected())
		{
			TheInGameUI->selectDrawable(obj->getDrawable());
			TheInGameUI->setDisplayedMaxWarning(false);
			teamMsg->appendBooleanArgument(false);
			teamMsg->appendObjectIDArgument(obj->getID());
		}
	}

	avgSpawnPos.scale(1.0f / spawnCount);
	avgSpawnPos.sub(obj->getPosition());
	obj->setHealthBoxOffset(avgSpawnPos);

	if (spawnCount)
	{
		avgHealthMax /= spawnCount;
		Real perfectTotalHealth = avgHealthMax * spawnCountMax;
		Real actualHealth = acrHealth / perfectTotalHealth;
		obj->getBodyModule()->setInitialHealth(
			*(const Real *)0x0107FAC4 * actualHealth);
	}
	else
	{
		obj->getBodyModule()->setInitialHealth(0.0f);
	}

	obj->maskObject(true);
}
