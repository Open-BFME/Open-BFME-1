// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// HijackerUpdate ctor 0x00295B20 installs vtable 0x010BF714 at +0x10; slot 0 reaches this body via ILT 0x0003C673.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include "Common/BitFlags.h"
#include "Common/GameType.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_4 = 4
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

	ObjectID getID(void) const
	{
		return m_id;
	}

	public:
	unsigned char m_padToID[0x6c];
	ObjectID m_id;
	unsigned char m_padToContain[0x184];
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

typedef BitFlags<86> ObjectStatusMaskType;

class Rva00295D70HijackerUpdateModuleData
{
public:
	unsigned char m_pad00[0x0c];
	AsciiString m_parachuteName;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thingTemplate, Team *team,
		const ObjectStatusMaskType &statusBits, UnsignedInt extra);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

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

class HijackerUpdate : public Rva00295D70UpdateModule
{
public:
	virtual UpdateSleepTime update(void);
	void setTargetObject(const Object *object)
	{
		if (object)
			m_targetID = object->getID();
		else
			m_targetID = INVALID_ID;
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
UpdateSleepTime HijackerUpdate::update(void)
{
	if (!m_update)
		return UPDATE_SLEEP_NONE;

	if (m_isInVehicle)
	{
		Object *obj = getObject();

		// Keep the hidden hijacker on the hijacked vehicle while it lives.
		Object *target = m_targetID != INVALID_ID ? TheBfmeGameLogic->findObjectByID(m_targetID) : 0;
		if (target)
		{
			Coord3D *position = reinterpret_cast<Coord3D *>(
				reinterpret_cast<UnsignedByte *>(target) + 0x38);
			obj->setPosition(position);
			m_wasTargetAirborne = static_cast<UnsignedByte>(
				reinterpret_cast<BfmeOwnerRW *>(target)->bfmeCheckRW());
			m_ejectPos = *position;
		}
		else
		{
			// The vehicle is gone: restore and unhide the hijacker.
			obj->rva001CA2E0();

			if (obj->getDrawable())
				obj->getDrawable()->bfmeSet(false);

			obj->clearStatus(OBJECT_STATUS_4);
			obj->maskObject(false);
			obj->clearStatus(OBJECT_STATUS_3);

			Rva00295D70AI *ai = *reinterpret_cast<Rva00295D70AI **>(
				reinterpret_cast<UnsignedByte *>(obj) + 0x204);
			if (ai)
				ai->aiIdle(CMD_FROM_AI);

			if (m_wasTargetAirborne)
			{
				const ThingTemplate *putInContainerTmpl = TheThingFactory->findTemplate(
					getModuleData()->m_parachuteName);
				if (putInContainerTmpl)
				{
					Object *container = TheThingFactory->newObject(
						putInContainerTmpl, obj->getTeam(), ObjectStatusMaskType(), 0);
					container->setPosition(&m_ejectPos);
					if (container->getContain()->isValidContainerFor(obj, true))
					{
						container->getContain()->addToContain(obj);
					}
				}
			}

			setTargetObject(0);
			setIsInVehicle(0);
			setUpdate(0);
			m_wasTargetAirborne = false;
		}
	}
	else
	{
		m_wasTargetAirborne = false;
	}

	return UPDATE_SLEEP_NONE;
}
