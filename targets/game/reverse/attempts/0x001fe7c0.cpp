// ?d_001fe7c0@@YAXXZ
// partial score=0.85 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FE7C0, 178 bytes.  Slot 7 of GettingBuiltBehavior's secondary
// vftable 0x010A45E0 (ILT 0x00022C19).  Same secondary this as
// GettingBuiltBehaviorCostForDamage: ModuleData at this-0x1C, Object at
// this-0x18.  Slot 5 of this vtable is rva001FE4A0.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class Object;
class Module;

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual Real slot14() const = 0;
	virtual Real getInitialHealth() const = 0;
	virtual void slot1c() = 0;
	virtual BodyDamageType getDamageState() const = 0;
};

class Object
{
public:
	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const;

	__forceinline BodyModuleInterface *getBodyModule() const
	{
		return m_body;
	}

private:
	unsigned char m_unreconstructed_00[0x200];
	BodyModuleInterface *m_body;
};

class GettingBuiltBehaviorModuleData
{
public:
	unsigned char m_unreconstructed_00[0x20];
	Real m_field20;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xb50];
	UnsignedInt m_recentDamageSeconds;
};

extern GlobalData *TheWritableGlobalData;

#define BfmeZeroRange (*(const Real *)0x01075350)
#define g_bfmeDefaultBU (*(const Real *)0x01075334)

class GettingBuiltBehaviorPrimary
{
public:
	virtual void primarySlot00();

protected:
	__forceinline const GettingBuiltBehaviorModuleData *getModuleData() const
	{
		return m_moduleData;
	}

	__forceinline Object *getObject() const
	{
		return m_object;
	}

private:
	const GettingBuiltBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unreconstructed_0C[0x20 - 0x0C];
};

class GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Bool rva001FE4A0() = 0;
	virtual void slot06() = 0;
	virtual Bool rva001FE7C0() = 0;
};

class GettingBuiltBehavior :
	public GettingBuiltBehaviorPrimary,
	public GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual Bool rva001FE7C0();
};

class BfmeItemE63
{
public:
	unsigned char m_pad00[0x14];
	void *m_field14;
	unsigned char m_pad18[0x24 - 0x18];
	unsigned char m_field24;
	Bool checkValid();
};

Module *__cdecl rva0036BB10FindCastleMemberBehavior(const Object *object);

#pragma comment(linker, "/alternatename:?bfmeGetRecentDamageSource@Object@@QBE_NPAII@Z=?j_000402d2@@YAXXZ")
#pragma comment(linker, "/alternatename:?checkValid@BfmeItemE63@@QAE_NXZ=?j_0004b015@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0036BB10FindCastleMemberBehavior@@YAPAVModule@@PBVObject@@@Z=?j_0000e6e7@@YAXXZ")

// ?rva001FE7C0@GettingBuiltBehavior@@UAE_NXZ
Bool GettingBuiltBehavior::rva001FE7C0()
{
	if (rva001FE4A0())
		return false;

	const GettingBuiltBehaviorModuleData *data = getModuleData();
	Object *object = getObject();
	BodyModuleInterface *body = object->getBodyModule();

	if (data->m_field20 < BfmeZeroRange)
	{
		ObjectID source = 0;
		if (object->bfmeGetRecentDamageSource(&source, TheWritableGlobalData->m_recentDamageSeconds))
			return false;
		if (!(body->slot14() < g_bfmeDefaultBU))
			return false;
	}
	else if (body->getDamageState() != BODY_RUBBLE)
	{
		return false;
	}

	object = getObject();
	BfmeItemE63 *item = (BfmeItemE63 *)rva0036BB10FindCastleMemberBehavior(object);
	if (item != 0 && item->m_field14 != 0 && !item->m_field24 && item->checkValid())
		return false;
	return true;
}
