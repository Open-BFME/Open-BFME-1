// ?rva001FE7C0@GettingBuiltBehavior@@UAE_NXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FE7C0, 178 bytes.  Slot 7 of GettingBuiltBehavior's secondary
// vftable 0x010A45E0 (ILT 0x00022C19).  Same secondary this as
// GettingBuiltBehaviorCostForDamage: ModuleData at this-0x1C, Object at
// this-0x18.  Slot 5 of this vtable is the byte getter at 0x001FE4A0.
//
// Unless slot 5 reports true, the structure counts as ready when its module
// field +0x20 is negative, nothing damaged it within the GlobalData window
// (+0xB50 seconds) and body slot 5 is below the shared constant at VA
// 0x01075334; otherwise when its body is rubble.  A ready structure still
// fails while its castle member behavior has a live pending object
// (CastleBehavior::isPendingObjectUnavailable).  The method name is unproven.
//
// Spellings the bytes decide: the ready tests and the castle test are one
// boolean expression each, so MSVC returns them as 0/1 in EAX while the
// slot-5 early-out returns `false` in AL and sits last; the rubble test is a
// Bool assignment (sete/test).

#include "../../../../Include/Common/ScalarTypes.h"



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

extern Real g_bfmeDefaultBU;
// Retail readonly VA 0x01075350 is 0.0f.

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

class CastleBehavior
{
public:
	Bool isPendingObjectUnavailable() const;		///< 0x00372090

	unsigned char m_unreconstructed_00[0x14];
	void *m_field14;
	unsigned char m_unreconstructed_18[0x24 - 0x18];
	unsigned char m_field24;
};

Module *__cdecl rva0036BB10FindCastleMemberBehavior(const Object *object);


// ?rva001FE7C0@GettingBuiltBehavior@@UAE_NXZ
Bool GettingBuiltBehavior::rva001FE7C0()
{
	if (!rva001FE4A0())
	{
		const GettingBuiltBehaviorModuleData *data = getModuleData();
		Object *object = getObject();
		BodyModuleInterface *body = object->getBodyModule();
		Bool ready;
		if (data->m_field20 < 0.0f)
		{
			ObjectID source = 0;
			ready = !object->bfmeGetRecentDamageSource(&source, TheWritableGlobalData->m_recentDamageSeconds)
				&& body->slot14() < g_bfmeDefaultBU;
		}
		else
			ready = body->getDamageState() == BODY_RUBBLE;
		CastleBehavior *item;
		return ready && ((item = (CastleBehavior *)rva0036BB10FindCastleMemberBehavior(getObject())) == 0 || item->m_field14 == 0 || item->m_field24 || !item->isPendingObjectUnavailable());
	}
	return false;
}
