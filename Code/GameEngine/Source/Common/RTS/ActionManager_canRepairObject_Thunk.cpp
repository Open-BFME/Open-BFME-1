// cl: /DNDEBUG /MD /EHsc
// Retail identity comes from the ActionManager callers and the helper ILTs.
// The local views preserve the BFME object offsets and virtual call slots.

typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;

enum ObjectID
{
	INVALID_ID = 0
};

enum Relationship
{
	ENEMIES = 2
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_FOGGED = 3
};

class Player
{
public:
	Int getPlayerIndex(void) const;
};

class StructureCompletionInterface
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual Bool slot20(void);
};

class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;
};

class BFMEActionThing
{
public:
	Bool isKindOf(Int kind) const;
};

class Rva000C4A70
{
public:
	Bool field(void) const;
};

class BodyModuleInterface
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual float getHealth(void);
	virtual void slot14(void);
	virtual float getMaxHealth(void);
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
	Player *getControllingPlayer(void) const;
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	StructureCompletionInterface *getStructureCompletionInterface(void);
	ObjectID getSoleHealingBenefactor(void) const;

	char m_pad00[0x74];
	Int m_id;
	char m_pad78[0x88];
	UnsignedByte m_privateStatus100;
	char m_pad101[0xff];
	BodyModuleInterface *m_body200;
	char m_pad204[0x10];
	void *m_containedBy214;
	char m_pad218[0x12c];
	UnsignedByte m_privateStatus;
};

static Bool isObjectShroudedForAction(const Object *source, const Object *target,
	CommandSourceType commandSource)
{
	if (target)
	{
		Int targetID = *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(target) + 0x74);
		if (targetID >= 0x05f5e0fc && targetID <= 0x05f5e0ff)
			return false;
	}

	if (source && target && source->getControllingPlayer())
	{
		if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(source->getControllingPlayer()) + 0x2c) == 0 &&
			commandSource != CMD_FROM_SCRIPT &&
			target->getShroudedStatus(source->getControllingPlayer()->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
			return true;
	}

	return false;
}

class ActionManager
{
public:
	Bool canRepairObject(const Object *, const Object *, CommandSourceType);
};

// The relationship, kind, status, completion, health, shroud, and beneficiary
// calls match the retail ILTs used by the Dozer and Worker repair callers.
Bool ActionManager::canRepairObject(const Object *obj, const Object *objectToRepair,
	CommandSourceType commandSource)
{
	if (obj == 0 || objectToRepair == 0)
		return false;

	if (obj->getRelationship(objectToRepair) != ENEMIES)
		return false;

	if ((objectToRepair->m_privateStatus & 1) != 0 &&
		!((const Rva000C4A70 *)objectToRepair)->field())
		return false;

	if (((const BFMEActionThing *)objectToRepair)->isKindOf(0x16))
		return false;
	if (((const BFMEActionThing *)objectToRepair)->isKindOf(0x18))
		return false;
	if (((const BFMEActionObject *)obj)->testStatus(2))
		return false;
	if (((const BFMEActionObject *)objectToRepair)->testStatus(2))
		return false;
	if (((const BFMEActionThing *)objectToRepair)->isKindOf(0x26) == 1)
		return false;
	if (!((const BFMEActionThing *)obj)->isKindOf(0x0e))
		return false;
	if (!((const BFMEActionThing *)objectToRepair)->isKindOf(7))
		return false;

	BodyModuleInterface *body = objectToRepair->m_body200;
	if (body->getHealth() == body->getMaxHealth())
		return false;

	if (((const BFMEActionThing *)objectToRepair)->isKindOf(0x95))
		return false;

	StructureCompletionInterface *completion =
		const_cast<Object *>(objectToRepair)->getStructureCompletionInterface();
	if (completion && completion->slot20())
		return false;

	if (isObjectShroudedForAction(obj, objectToRepair, commandSource))
		return false;
	if (obj->m_containedBy214 != 0)
		return false;

	ObjectID beneficiary = objectToRepair->getSoleHealingBenefactor();
	if (beneficiary != 0 && beneficiary != obj->m_id)
		return false;
	return true;
}
