// ?doSpecialPowerAtObject@GrabPassengerSpecialPower@@UAEXPAVObject@@I@Z
// partial score=0.43 date=2026-09-22
// Retail 0x0025F6C0: GrabPassengerSpecialPower::doSpecialPowerAtObject.
// The vtable slot and the 0x27 special-power type are independently witnessed.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class Object;
class Coord3D;
class Waypoint;

enum SpecialPowerType
{
	RVA0025F6C0_SPECIAL_POWER_TYPE_27 = 0x27
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	Overridable *friend_getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xcc];
	UnsignedInt m_kindOf; // +0xd4
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc];
	Int m_specialPowerType; // +0x14
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual SpecialPowerTemplate *getSpecialPowerTemplate();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void doSpecialPowerAtObject(Object *, UnsignedInt);

	unsigned char m_pad04[4];
	Int m_pausedCount;
};

class BFMEContainSlotShim
{
public:
#define RVA0025F6C0_SLOT(N) virtual void slot##N();
	RVA0025F6C0_SLOT(00)
	RVA0025F6C0_SLOT(01)
	RVA0025F6C0_SLOT(02)
	RVA0025F6C0_SLOT(03)
	RVA0025F6C0_SLOT(04)
	RVA0025F6C0_SLOT(05)
	RVA0025F6C0_SLOT(06)
	RVA0025F6C0_SLOT(07)
	RVA0025F6C0_SLOT(08)
	RVA0025F6C0_SLOT(09)
	RVA0025F6C0_SLOT(10)
	RVA0025F6C0_SLOT(11)
	RVA0025F6C0_SLOT(12)
	RVA0025F6C0_SLOT(13)
	RVA0025F6C0_SLOT(14)
	RVA0025F6C0_SLOT(15)
	RVA0025F6C0_SLOT(16)
	RVA0025F6C0_SLOT(17)
	RVA0025F6C0_SLOT(18)
	RVA0025F6C0_SLOT(19)
	RVA0025F6C0_SLOT(20)
	RVA0025F6C0_SLOT(21)
	RVA0025F6C0_SLOT(22)
	RVA0025F6C0_SLOT(23)
	RVA0025F6C0_SLOT(24)
	virtual Object *slot25();
#undef RVA0025F6C0_SLOT
};

class BFMEContainResultShim
{
public:
#define RVA0025F6C0_RESULT_SLOT(N) virtual void slot##N();
	RVA0025F6C0_RESULT_SLOT(00)
	RVA0025F6C0_RESULT_SLOT(01)
	RVA0025F6C0_RESULT_SLOT(02)
	RVA0025F6C0_RESULT_SLOT(03)
	RVA0025F6C0_RESULT_SLOT(04)
	RVA0025F6C0_RESULT_SLOT(05)
	RVA0025F6C0_RESULT_SLOT(06)
	RVA0025F6C0_RESULT_SLOT(07)
	RVA0025F6C0_RESULT_SLOT(08)
	RVA0025F6C0_RESULT_SLOT(09)
	RVA0025F6C0_RESULT_SLOT(10)
	RVA0025F6C0_RESULT_SLOT(11)
	RVA0025F6C0_RESULT_SLOT(12)
	RVA0025F6C0_RESULT_SLOT(13)
	RVA0025F6C0_RESULT_SLOT(14)
	RVA0025F6C0_RESULT_SLOT(15)
	RVA0025F6C0_RESULT_SLOT(16)
	RVA0025F6C0_RESULT_SLOT(17)
	virtual Object *slot18(Int, Int, Int);
#undef RVA0025F6C0_RESULT_SLOT
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x19c];
	Int m_disabledMask;
	unsigned char m_pad1a8[0x54];
	BFMEContainSlotShim *m_contain;

	ThingTemplate *getTemplate() const { return m_template; }
	BFMEContainSlotShim *getContain() const { return m_contain; }
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(
		SpecialPowerType type) const;
	void setStatusBit(Int bit, Bool value);
};

enum CommandSourceType
{
	RVA0025F6C0_COMMAND_SOURCE = 0
};

class ActionManager
{
public:
	Bool canDoSpecialPowerAtObject(const Object *owner, const Object *target,
		CommandSourceType commandSource, const SpecialPowerTemplate *specialPower,
		UnsignedInt commandOptions, Bool checkSourceRequirements);
};

extern ActionManager *TheActionManager;

class SpecialPowerModule
{
public:
	Bool initiateIntentToDoSpecialPower(const Object *targetObj,
		const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions);
	void finishSpecialPower(UnsignedInt arg);
};

class GrabPassengerSpecialPower : public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtObject(Object *target, UnsignedInt commandOptions);
};

void GrabPassengerSpecialPower::doSpecialPowerAtObject(
	Object *target, UnsignedInt commandOptions)
{
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_pausedCount > 0)
			return;
		Object *owner = *reinterpret_cast<Object **>(
			reinterpret_cast<char *>(this) - 8);
		if (owner->m_disabledMask != 0)
			return;
	}

	Object *ownerObject;
	ThingTemplate *targetTemplate = target->getTemplate();
	if (targetTemplate != 0 && targetTemplate->m_nextOverride != 0)
		targetTemplate = const_cast<ThingTemplate *>(reinterpret_cast<const ThingTemplate *>(
			targetTemplate->m_nextOverride->getFinalOverride()));
	if ((targetTemplate->m_kindOf & 0x1000) != 0)
	{
		BFMEContainSlotShim *contain = target->getContain();
		Object *candidate = contain->slot25();
		if (candidate != 0)
		{
			candidate = reinterpret_cast<BFMEContainResultShim *>(candidate)->slot18(
				1, 0, 0);
			if (candidate != 0)
			{
				SpecialPowerModuleInterface *interfacePtr =
					reinterpret_cast<SpecialPowerModuleInterface *>(this);
				SpecialPowerTemplate *specialPower =
					interfacePtr->getSpecialPowerTemplate();
				Overridable *overridden = specialPower->m_nextOverride;
				if (overridden != 0)
				{
					if (overridden->m_nextOverride != 0)
						specialPower = reinterpret_cast<SpecialPowerTemplate *>(
							overridden->friend_getFinalOverride());
					else
						specialPower = reinterpret_cast<SpecialPowerTemplate *>(
							overridden);
				}
				if (specialPower->m_specialPowerType == 0x27)
				{
					ownerObject = *reinterpret_cast<Object **>(
						reinterpret_cast<char *>(this) - 8);
					SpecialPowerModuleInterface *module =
						ownerObject->findSpecialPowerModuleInterface(
							RVA0025F6C0_SPECIAL_POWER_TYPE_27);
					if (module == 0)
						return;
					SpecialPowerTemplate *moduleTemplate =
						module->getSpecialPowerTemplate();
					if (!TheActionManager->canDoSpecialPowerAtObject(
							ownerObject, target,
							static_cast<CommandSourceType>(
								(commandOptions >> 18) & 1),
							moduleTemplate, commandOptions, true))
						return;
				}
				candidate->setStatusBit(0x3e, true);
			}
		}
		goto doPower;
	}

	SpecialPowerModuleInterface *interfacePtr =
		reinterpret_cast<SpecialPowerModuleInterface *>(this);
	SpecialPowerTemplate *specialPower = interfacePtr->getSpecialPowerTemplate();
	Overridable *overridden = specialPower->m_nextOverride;
	if (overridden != 0)
	{
		if (overridden->m_nextOverride != 0)
			specialPower = reinterpret_cast<SpecialPowerTemplate *>(
				overridden->friend_getFinalOverride());
		else
			specialPower = reinterpret_cast<SpecialPowerTemplate *>(overridden);
	}
	if (specialPower->m_specialPowerType != 0x27)
		return;
	ownerObject = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 8);
	SpecialPowerModuleInterface *module = ownerObject->findSpecialPowerModuleInterface(
		RVA0025F6C0_SPECIAL_POWER_TYPE_27);
	if (module == 0)
		return;
	SpecialPowerTemplate *moduleTemplate = module->getSpecialPowerTemplate();
	if (!TheActionManager->canDoSpecialPowerAtObject(
			ownerObject, target,
			static_cast<CommandSourceType>((commandOptions >> 18) & 1),
			moduleTemplate, commandOptions, true))
		return;

doPower:
	SpecialPowerModule *base = reinterpret_cast<SpecialPowerModule *>(
		reinterpret_cast<char *>(this) - 0x10);
	base->initiateIntentToDoSpecialPower(target, 0,
		(reinterpret_cast<const Waypoint *>(commandOptions)), 0);
	unsigned char *data = *reinterpret_cast<unsigned char **>(
		reinterpret_cast<char *>(this) - 0xc);
	if (data[0xc] == 0)
		base->finishSpecialPower((UnsignedInt)target + 0x38);
}
