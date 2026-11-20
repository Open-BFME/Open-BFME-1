// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include/Lib /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/GameLogic
// GrabPassengerSpecialPower secondary interface; evidence: targets/game/reverse/identity_evidence/0025f6c0-passenger-target.md
// ?doSpecialPowerAtObject@GrabPassengerSpecialPower@@UAEXPBVObject@@I@Z

#include "../../../../Include/Common/ScalarTypes.h"



class Object;
#include "Coord3D.h"

enum SpecialPowerType
{
	RVA0025F6C0_SPECIAL_POWER_TYPE_27 = 0x27
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
	Bool m_isOverride;
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
};
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad0c[0xbc];
	UnsignedInt m_kindOf[6]; // +0xc8
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_pad0c[8];
	Int m_specialPowerType; // +0x14
	Int getSpecialPowerType() const { return getFO()->m_specialPowerType; }
	const SpecialPowerTemplate *getFO() const { return static_cast<const SpecialPowerTemplate *>(friend_getFinalOverride()); }
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
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void doSpecialPowerAtObject(const Object *, UnsignedInt);

	unsigned char m_pad04[4];
	Int m_pausedCount;
};

class BFMEContainResultShim;

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
	virtual void *slot25();
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
	virtual Object *slot18(Bool, const Coord3D *, float);
#undef RVA0025F6C0_RESULT_SLOT
};

#define BFME_HAVE_COORD3D 1
#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const { if (!m_template) return 0; return static_cast<const ThingTemplate *>(m_template->getFinalOverride()); }
#define OBJECT_TU_MEMBERS BFMEContainSlotShim *getContain() const { return reinterpret_cast<BFMEContainSlotShim *>(m_contain); } SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const; void setStatusBit(Int bit, Bool value);
#include "object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS
#include "command_source_type.h"

class ActionManager
{
public:
	Bool canDoSpecialPowerAtObject(const Object *owner, const Object *target,
		CommandSourceType commandSource, const SpecialPowerTemplate *specialPower,
		UnsignedInt commandOptions, Bool checkSourceRequirements);
};


// Retail 0x012ED700: use the existing data owner; retain the local pointee view.
extern class ActionManager *TheActionManager;

class SpecialPowerModule
{
	friend class GrabPassengerSpecialPower;
protected:
	void initiateIntentToDoSpecialPower(const Object *targetObj,
		const Coord3D *targetPos, UnsignedInt commandOptions, UnsignedInt arg4);
public:
	void finishSpecialPower(UnsignedInt arg);
};

class GrabPassengerSpecialPower : public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtObject(const Object *target, UnsignedInt commandOptions);
};

void GrabPassengerSpecialPower::doSpecialPowerAtObject(const Object *target, UnsignedInt commandOptions)
{
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_pausedCount > 0)
			return;
		Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
		if (owner->m_disabledMask != 0)
			return;
	}
	const Object *candidate;
	const ThingTemplate *targetTemplate = target->getTemplate();
	if ((targetTemplate->m_kindOf[3] & 0x1000) != 0)
	{
		BFMEContainSlotShim *contain = target->getContain();
		void *container = contain->slot25();
		if (container != 0)
		{
			candidate = reinterpret_cast<BFMEContainResultShim *>(container)->slot18(true, 0, 0.0f);
			if (candidate == 0)
				return;
			if (getSpecialPowerTemplate()->getSpecialPowerType() == 0x27)
			{
				SpecialPowerModuleInterface *module = (*reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8))->findSpecialPowerModuleInterface(RVA0025F6C0_SPECIAL_POWER_TYPE_27);
				if (module == 0)
					return;
				Object *ownerObject = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
				if (!reinterpret_cast<ActionManager *>( TheActionManager )->canDoSpecialPowerAtObject(ownerObject, target, static_cast<CommandSourceType>((commandOptions >> 18) & 1), module->getSpecialPowerTemplate(), commandOptions, true))
					return;
			}
			const_cast<Object *>(candidate)->setStatusBit(0x3e, true);
		}
		else
			candidate = target;
	}
	else
	{
		if (getSpecialPowerTemplate()->getSpecialPowerType() == 0x27)
		{
			SpecialPowerModuleInterface *module = (*reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8))->findSpecialPowerModuleInterface(RVA0025F6C0_SPECIAL_POWER_TYPE_27);
			if (module == 0)
				return;
			Object *ownerObject = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
			if (!reinterpret_cast<ActionManager *>( TheActionManager )->canDoSpecialPowerAtObject(ownerObject, target, static_cast<CommandSourceType>((commandOptions >> 18) & 1), module->getSpecialPowerTemplate(), commandOptions, true))
				return;
		}
		candidate = target;
	}
	SpecialPowerModule *base = reinterpret_cast<SpecialPowerModule *>(reinterpret_cast<char *>(this) - 0x10);
	base->initiateIntentToDoSpecialPower(candidate, 0, commandOptions, 0);
	unsigned char *data = *reinterpret_cast<unsigned char **>(reinterpret_cast<char *>(this) - 0xc);
	if (data[0xc] == 0)
		base->finishSpecialPower((UnsignedInt)candidate + 0x38);
}
