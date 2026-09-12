// ?d_00226a80@@YAXXZ
// partial score=0.98 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Open-BFME: HordeTransportContain::preflight, retail 0x00226A80.
// The HordeTransportContain vtable and the call from isValidContainerFor at
// 0x0024BD70 identify the owner. The retail body checks object kinds, applies
// the module filter, resolves a body-provided template name, and then checks
// the object relationship before it returns.

#include <list>

typedef bool Bool;
typedef int Int;

enum KindOfType
{
	KIND_NONE
};

enum Relationship
{
	REL_NEUTRAL,
	REL_ENEMIES,
	REL_ALLIES
};

class Player;
class ThingTemplate;

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")

class BfmeOutOfWeaponRangeObject
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer(void) const;
};

class AsciiString
{
public:
	void *m_data;
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

#pragma comment(linker, "/alternatename:?testStatus@Object@@QBE_NH@Z=?j_000016a4@@YAXXZ")

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
	Bool bfmeTest(ThingTemplate *thingTemplate, Player *objectPlayer,
		Player *ownerPlayer);

	unsigned int m_handle;
};

#pragma comment(linker, "/alternatename:?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z=?j_0001da34@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeTest@Rva2225E0Filter@@QAE_NPAVThingTemplate@@PAVPlayer@@1@Z=?j_0001b437@@YAXXZ")

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")

class Rva0020AA00Registry : public BfmeThingFactory
{
};

extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

class HordeTransportContainModuleData
{
public:
	unsigned char m_beforeFilter[0x114];
	Rva2225E0Filter m_filter;
	unsigned char m_beforeFlags[0x34];
	unsigned char m_alliedOwned;
	unsigned char m_alliedOther;
	unsigned char m_neutral;
	unsigned char m_enemy;
};

class HordeTransportContainRelated
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
	virtual Bool accepts(Object *object) = 0;
};

class HordeTransportContainBase
{
public:
	virtual void slot00(void) = 0;
	unsigned char m_pad04[0x92];
	unsigned char m_enabled;
};

template <int Number> class HordeTransportContainIface
{
public:
	virtual void slot(void) = 0;
};

class HordeTransportContain : public HordeTransportContainBase,
	public HordeTransportContainIface<1>, public HordeTransportContainIface<2>,
	public HordeTransportContainIface<3>, public HordeTransportContainIface<4>,
	public HordeTransportContainIface<5>, public HordeTransportContainIface<6>,
	public HordeTransportContainIface<7>, public HordeTransportContainIface<8>,
	public HordeTransportContainIface<9>
{
public:
	Bool preflight(Object *object, Bool checkCapacity) const;

	HordeTransportContainModuleData *getModuleData(void) const
	{
		return *(HordeTransportContainModuleData **)((char *)this - 0x1c);
	}

	Object *getObject(void) const
	{
		return *(Object **)((char *)this - 0x18);
	}
};

// ?preflight@HordeTransportContain@@QBE_NPAVObject@@_N@Z
Bool HordeTransportContain::preflight(Object *object, Bool checkCapacity) const
{
	register HordeTransportContainModuleData * const data =
		*(HordeTransportContainModuleData **)((char *)this - 0x1c);
	register Object *owner = *(Object **)((char *)this - 0x18);
	register HordeTransportContain *record = (HordeTransportContain *)this;
	unsigned int status0 = object->m_status[0];
	if ((status0 & 1) != 0 ||
		(object->m_status[1] & 0x20000000) != 0 ||
		record->m_enabled == 0)
		return false;

	if (((const BfmeOutOfWeaponRangeObject *)object)->isKindOf((KindOfType)0x6d) &&
		!((const BfmeOutOfWeaponRangeObject *)owner)->isKindOf((KindOfType)0x75) &&
		!((const BfmeOutOfWeaponRangeObject *)owner)->isKindOf((KindOfType)0x86))
		return false;

	if (((const BfmeOutOfWeaponRangeObject *)object)->isKindOf((KindOfType)0x83) ||
		((const BfmeOutOfWeaponRangeObject *)object)->isKindOf((KindOfType)0x87))
	{
		BFMERetailAsciiString name = object->m_body->bfmeGetBUE();
		if (name.m_data != 0 &&
			*(unsigned short *)((char *)name.m_data + 4) != 0)
		{
			const ThingTemplate *thingTemplate =
				Rva0020AA00TheRegistry->findTemplate(
					*(const AsciiString *)&name);
			if (thingTemplate != 0 &&
				((Rva2225E0Filter *)&data->m_filter)->bfmeTest(
					(ThingTemplate *)thingTemplate,
					((BfmeObjectCall *)object)->getControllingPlayer(),
					((BfmeObjectCall *)owner)->getControllingPlayer()))
				goto relationship;
		}
		return false;
	}

	if (((Rva2225E0Filter *)&data->m_filter)->accepts(
		object, ((BfmeObjectCall *)owner)->getControllingPlayer()))
		goto relationship;
	return false;

relationship:
	unsigned char allowed;
	switch (object->getRelationship(owner))
	{
	case 0:
		allowed = data->m_neutral;
		goto checkAllowed;
	case 1:
		allowed = data->m_enemy;
		goto checkAllowed;
	case 2:
		if (((BfmeObjectCall *)object)->getControllingPlayer() ==
			((BfmeObjectCall *)owner)->getControllingPlayer())
		{
			if (data->m_alliedOwned != 0)
				goto success;
		}
		if (data->m_alliedOther != 0)
			goto success;
		if (!object->testStatus(0x25))
			goto failed;
		allowed = ((HordeTransportContainRelated *)((char *)record - 0x20))
			->accepts(object);
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
