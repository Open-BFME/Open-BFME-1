// ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.88 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_4 = 4
};

struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};

class AsciiString
{
};

class ThingTemplate
{
};

class Team
{
};

class Thing
{
public:
	virtual void slot00() = 0;
	void setPosition(const Coord3D *position);
};

class Gen_00411DD0
{
public:
	void bfmeSet(bool hidden);
};

class Rva00295D70ContainModuleInterface;

class Rva00295D70ObjectContainView
{
public:
	unsigned char m_pad00[0x1fc];
	Rva00295D70ContainModuleInterface *m_contain;
};

class Rva00295D70Snapshot
{
public:
	virtual void snapshotSlot() = 0;
};

class Object : public Thing, public Rva00295D70Snapshot
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
	virtual Gen_00411DD0 *getDrawable() = 0;

	void rva001CA2E0(void);
	void clearStatus(ObjectStatusTypes status);
	void maskObject(bool masked);
	Team *getTeam(void) const
	{
		return m_team;
	}
	Rva00295D70ContainModuleInterface *getContain(void) const
	{
		return m_contain;
	}
	void addContainedObject(Object *object);

	public:
	unsigned char m_padToContain[0x1f4];
	Rva00295D70ContainModuleInterface *m_contain;
	unsigned char m_padToTeam[0x3c];
	Team *m_team;
};

class BfmeOwnerRW
{
public:
	int bfmeCheckRW(void);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

struct ObjectStatusMaskType;

class Rva00295D70HijackerUpdateModuleData
{
public:
	unsigned char m_pad00[0x0c];
	AsciiString m_parachuteName;
};

class Rva00295D70HijackerUpdateFull
{
public:
	unsigned char m_pad00[0x24];
	Coord3D m_ejectPos;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thingTemplate, Team *team,
		const volatile ObjectStatusMaskType &statusBits, UnsignedInt extra);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheThingFactory (*(ThingFactory **)0x012EF1D8)
extern void j_0004494a(void);

struct ObjectStatusMaskType
{
	UnsignedInt m_bits[3];
};

typedef Object *(ThingFactory::*ThingFactoryNewObjectCall)(
	const ThingTemplate *, Team *, const volatile ObjectStatusMaskType &, void *);

static __forceinline Object *rva00295D70NewObject(
	ThingFactory *factory, const ThingTemplate *thingTemplate, Team *team,
	const volatile ObjectStatusMaskType &statusBits = ObjectStatusMaskType(),
	void *extra = 0)
{
	union
	{
		void (*raw)(void);
		ThingFactoryNewObjectCall member;
	} call;
	call.raw = j_0004494a;
	return (factory->*call.member)(thingTemplate, team, statusBits, extra);
}

class Rva00295D70AIHead
{
private:
	unsigned char m_pad00[0x20];
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class Rva00295D70AI : public Rva00295D70AIHead, public AICommandInterface
{
};

class Rva00295D70ContainModuleInterface
{
public:
	virtual void asOpenContain() = 0;
	virtual void containReactToTransformChange() = 0;
	virtual bool isGarrisonable() const = 0;
	virtual bool isBustable() const = 0;
	virtual bool isSpecialZeroSlotContainer() const = 0;
	virtual bool isHealContain() const = 0;
	virtual bool isTunnelContain() const = 0;
	virtual bool isRiderChangeContain() const = 0;
	virtual bool isImmuneToClearBuildingAttacks() const = 0;
	virtual bool isSpecialOverlordStyleContainer() const = 0;
	virtual bool isAnyRiderAttacking() const = 0;
	virtual void clientVisibleContainedFlashAsSelected() = 0;
	virtual void onObjectWantsToEnterOrExit(Object *, int) = 0;
	virtual bool hasObjectsWantingToEnterOrExit() const = 0;
	virtual const void *getApparentControllingPlayer(const void *) const = 0;
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void onContaining(Object *, bool) = 0;
	virtual void onRemoving(Object *) = 0;
	virtual void onCapture(void *, void *) = 0;
	virtual void onSelling() = 0;
	virtual int getContainMax() const = 0;
	virtual void *getContainExitInterface() = 0;
	virtual void orderAllPassengersToExit(int, bool) = 0;
	virtual void orderAllPassengersToIdle(int) = 0;
	virtual void orderAllPassengersToHackInternet(int) = 0;
	virtual void markAllPassengersDetected() = 0;
	virtual void bfmeContainSlot26() = 0;
	virtual void bfmeContainSlot27() = 0;
	virtual void bfmeContainSlot28() = 0;
	virtual void bfmeContainSlot29() = 0;
	virtual void bfmeContainSlot30() = 0;
	virtual void bfmeContainSlot31() = 0;
	virtual void bfmeContainSlot32() = 0;
	virtual bool isValidContainerFor(const Object *object, bool force) const = 0;
	virtual void addToContain(Object *object) = 0;
	virtual void addToContainList(Object *object) = 0;
	virtual void removeFromContain(Object *object, bool exposeStealthUnits) = 0;
	virtual void removeAllContained(bool exposeStealthUnits) = 0;
	virtual void killAllContained(void) = 0;
	virtual void harmAndForceExitAllContained(void *info) = 0;
	virtual bool isEnclosingContainerFor(const Object *object) const = 0;
	virtual bool isPassengerAllowedToFire(ObjectID id) const = 0;
	virtual void setPassengerAllowedToFire(bool permission) = 0;
	virtual void setOverrideDestination(const Coord3D *) = 0;
	virtual bool isDisplayedOnControlBar() const = 0;
	virtual int getExtraSlotsInUse(void) = 0;
	virtual bool isKickOutOnCapture(void) = 0;
	virtual void iterateContained(void *, void *, bool) = 0;
	virtual UnsignedInt getContainCount() const = 0;
	virtual const void *getContainedItemsList() const = 0;
	virtual const Object *friend_getRider() const = 0;
	virtual float getContainedItemsMass() const = 0;
	virtual UnsignedInt getStealthUnitsContained() const = 0;
	virtual bool calcBestGarrisonPosition(Coord3D *, const Coord3D *) = 0;
	virtual bool attemptBestFirePointPosition(Object *, void *, Object *) = 0;
	virtual bool attemptBestFirePointPosition(Object *, void *, const Coord3D *) = 0;
};

union Rva00295D70ContainValue
{
	Object *object;
	Rva00295D70ContainModuleInterface *contain;
};


__forceinline void Object::addContainedObject(Object *object)
{
	m_contain->addToContain(object);
}

static __forceinline void rva00295D70SetPosition(
	Object *object, const Coord3D *position)
{
	object->setPosition(position);
}

static __forceinline void rva00295D70AddContain(
	Rva00295D70ContainModuleInterface *contain, Object *object)
{
	contain->addToContain(object);
}

class Rva00295D70HijackerUpdateModuleData;

class Rva00295D70Module
{
public:
	virtual ~Rva00295D70Module();

protected:
	const Rva00295D70HijackerUpdateModuleData *m_moduleData;
};

class Rva00295D70ObjectModule : public Rva00295D70Module
{
public:
	virtual void onCapture(Object *oldTeam, Object *newTeam);

protected:
	Object *m_object;
};

class Rva00295D70BehaviorModuleInterface
{
public:
	virtual void getBody();
	virtual void getCollide();
	virtual void getContain();
	virtual void getCreate();
	virtual void getDamage();
	virtual void getDestroy();
	virtual void getDie();
	virtual void getSpecialPower();
	virtual void getUpdate();
};

class Rva00295D70BehaviorModule : public Rva00295D70ObjectModule,
	public Rva00295D70BehaviorModuleInterface
{
};

class Rva00295D70UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class Rva00295D70UpdateModule : public Rva00295D70BehaviorModule,
	public Rva00295D70UpdateModuleInterface
{
protected:
	UnsignedInt m_nextCallFrame;
	Int m_indexInLogic;
	Int m_pad;

	Object *getObject() const
	{
		return m_object;
	}

	const Rva00295D70HijackerUpdateModuleData *getModuleData() const
	{
		return m_moduleData;
	}
};

class Rva00295D70HijackerUpdate : public Rva00295D70UpdateModule
{
public:
	virtual UpdateSleepTime update(void);
	void setTargetObject(const Object *object)
	{
		m_targetID = object == 0 ? 0 : 1;
	}
	void setIsInVehicle(UnsignedByte inVehicle)
	{
		m_isInVehicle = inVehicle;
	}
	void setUpdate(UnsignedByte update)
	{
		m_update = update;
	}

private:
	ObjectID m_targetID;
	Coord3D m_ejectPos;
	UnsignedByte m_update;
	UnsignedByte m_isInVehicle;
	UnsignedByte m_wasTargetAirborne;
};

// ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime Rva00295D70HijackerUpdate::update(void)
{
	if (m_update == 0)
		return UPDATE_SLEEP_NONE;

	if (m_isInVehicle != 0)
	{
		ObjectID targetID = m_targetID;
		Object *object = getObject();

		if (targetID != 0)
		{
			Object *target = TheBfmeGameLogic->findObjectByID(targetID);
			if (target != 0)
			{
				Coord3D *position = reinterpret_cast<Coord3D *>(
					reinterpret_cast<UnsignedByte *>(target) + 0x38);
				object->setPosition(position);
				m_wasTargetAirborne = static_cast<UnsignedByte>(
					reinterpret_cast<BfmeOwnerRW *>(target)->bfmeCheckRW());
				m_ejectPos = *position;
				return UPDATE_SLEEP_NONE;
			}
		}

		object->rva001CA2E0();

		if (object->getDrawable() != 0)
			reinterpret_cast<Gen_00411DD0 *>(object->getDrawable())->bfmeSet(false);

		object->clearStatus(OBJECT_STATUS_4);
		object->maskObject(false);
		object->clearStatus(OBJECT_STATUS_3);

		Rva00295D70AI *ai = *reinterpret_cast<Rva00295D70AI **>(
			reinterpret_cast<UnsignedByte *>(object) + 0x204);
		if (ai != 0)
			ai->aiIdle(CMD_FROM_AI);

		if (m_wasTargetAirborne != 0)
		{
			const Rva00295D70HijackerUpdateModuleData *moduleData =
				getModuleData();
			ThingTemplate *thingTemplate = TheThingFactory->findTemplate(
				moduleData->m_parachuteName);
			if (thingTemplate != 0)
			{
				Object *objectContainer = TheThingFactory->newObject(
					thingTemplate,
					object->getTeam(),
					ObjectStatusMaskType(), 0);
				objectContainer->setPosition(&m_ejectPos);

				if (objectContainer->getContain()->isValidContainerFor(object, true))
				{
					objectContainer->getContain()->addToContain(object);
				}
				else
				{
				}
			}
		}

		setTargetObject(0);
		setIsInVehicle(0);
		setUpdate(0);
	}

	m_wasTargetAirborne = 0;
	return UPDATE_SLEEP_NONE;
}
