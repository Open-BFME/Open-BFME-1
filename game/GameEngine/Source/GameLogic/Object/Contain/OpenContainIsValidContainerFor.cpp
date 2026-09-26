// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: OpenContain::isValidContainerFor, retail 0x00226A80, 492 bytes.
//
// Identity: OpenContain's ContainModuleInterface vtable 0x010AC038 (the table
// OpenContainOnRemoving.cpp proves) holds this body at slot 33 (+0x84) through
// the ILT at 0x000237B8, the same slot SiegeEngineContainIsValidContainerFor.cpp
// declares isValidContainerFor at. TransportContain::isValidContainerFor
// (0x0022DBA0) and HordeTransportContain::isValidContainerFor (0x0024BD70) both
// make the qualified base call with the rider and checkCapacity, as the Zero
// Hour TransportContain does. The relationship switch is the Zero Hour body:
// ENEMIES/NEUTRAL/ALLIES read the AllowEnemiesInside, AllowNeutralInside and
// AllowAlliesInside INI fields at 0x14E/0x14F/0x14D (targets/game/reverse/field_names.csv).
// BFME adds the status/kind gates, the PassengerFilter at +0x114 and the
// own-player override at +0x14C.
//
// Retail enters with the ContainModuleInterface subobject (+0x20) in ECX.

typedef bool Bool;
typedef int Int;

enum KindOfType
{
	KIND_NONE
};

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

class Player;
class ThingTemplate;
class AsciiString;

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer(void) const;
};

template <typename T> class BfmeStringBase
{
	friend class BFMERetailAsciiString;

private:
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
	{
		((BfmeStringBase<char> *)this)->m_data =
			((BfmeStringBase<char> *)&other)->m_data;
	}
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void *m_data;

private:
	void releaseBuffer();
};

class BodyModuleInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual BFMERetailAsciiString bfmeGetBUE(void) = 0;
};

class Object : public Thing
{
public:
	Bool testStatus(Int status) const;
	Relationship getRelationship(const Object *other) const;

	unsigned char m_beforeStatus[0x90];
	unsigned int m_status[2];
	unsigned char m_beforeBody[0x200 - 0x98];
	BodyModuleInterface *m_body;
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);

	unsigned int m_handle;
};

// The template test the PassengerFilter makes; retail calls the ILT at
// 0x0001B437 with ECX = the filter.
class Rva0039F0A0
{
public:
	Bool accepts(const void *thing, Player *objectPlayer, Player *ownerPlayer);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

class OpenContainModuleData
{
public:
	unsigned char m_beforeFilter[0x114];
	Rva2225E0Filter m_filter;
	unsigned char m_beforeFlags[0x34];
	unsigned char m_allowOwnPlayerInsideOverride;	// INI AllowOwnPlayerInsideOverride (field_names.csv)
	unsigned char m_allowAlliesInside;
	unsigned char m_allowEnemiesInside;
	unsigned char m_allowNeutralInside;
};

// OpenContain's primary base: the vtable and module fields that sit 0x20 bytes
// below the ContainModuleInterface subobject.
class OpenContainPrimaryBase
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	// Slot 19 (+0x4C): OpenContain's own body 0x00219710 is xor al,al / ret 4;
	// nothing names it.
	virtual Bool primarySlot19(const Object *object) const = 0;

	OpenContainModuleData *getModuleData(void) const
	{
		return *(OpenContainModuleData *const *)((const char *)this + 4);
	}

	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this + 8);
	}

private:
	unsigned char m_unmodelled04[0x20 - 4];
};

class ContainModuleInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual Bool isValidContainerFor(const Object *object,
		Bool checkCapacity) const = 0;
};

class OpenContain : public OpenContainPrimaryBase, public ContainModuleInterface
{
public:
	virtual Bool isValidContainerFor(const Object *object,
		Bool checkCapacity) const;

private:
	unsigned char m_unmodelled24[0xb6 - 0x24];
	unsigned char m_enabled;
};

// ?isValidContainerFor@OpenContain@@UBE_NPBVObject@@_N@Z
Bool OpenContain::isValidContainerFor(const Object *object,
	Bool checkCapacity) const
{
	Object *owner = getObject();
	OpenContainModuleData *data = getModuleData();
	unsigned int status0 = object->m_status[0];
	if ((status0 & 1) != 0 ||
		(object->m_status[1] & 0x20000000) != 0 ||
		m_enabled == 0)
		return false;

	if (object->isKindOf((KindOfType)0x6d) &&
		!owner->isKindOf((KindOfType)0x75) &&
		!owner->isKindOf((KindOfType)0x86))
		return false;

	if (object->isKindOf((KindOfType)0x83) ||
		object->isKindOf((KindOfType)0x87))
	{
		BFMERetailAsciiString name = object->m_body->bfmeGetBUE();
		if (name.m_data != 0 &&
			*(unsigned short *)((char *)name.m_data + 4) != 0)
		{
			BfmeThingFactory *factory = TheThingFactory;
			const ThingTemplate *thingTemplate =
				factory->findTemplate(*(const AsciiString *)&name);
			if (thingTemplate != 0 &&
				((Rva0039F0A0 *)&data->m_filter)->accepts(thingTemplate,
					((const BfmeObjectCall *)object)->getControllingPlayer(),
					((const BfmeObjectCall *)owner)->getControllingPlayer()))
				goto relationship;
		}
		return false;
	}

	if (!data->m_filter.accepts((Object *)object,
			((const BfmeObjectCall *)owner)->getControllingPlayer()))
		return false;

relationship:
	unsigned char allowed;
	switch (object->getRelationship(owner))
	{
	case ENEMIES:
		allowed = data->m_allowEnemiesInside;
		goto checkAllowed;
	case NEUTRAL:
		allowed = data->m_allowNeutralInside;
		goto checkAllowed;
	case ALLIES:
		if (((const BfmeObjectCall *)object)->getControllingPlayer() ==
			((const BfmeObjectCall *)owner)->getControllingPlayer())
		{
			if (data->m_allowOwnPlayerInsideOverride != 0)
				goto success;
		}
		if (data->m_allowAlliesInside != 0)
			goto success;
		if (!object->testStatus(0x25))
			goto failed;
		allowed = primarySlot19(object);
		goto checkAllowed;
	default:
		goto failed;
	}

checkAllowed:
	if (allowed == 0)
		goto failed;
success:
	return true;
failed:
	return false;
}
