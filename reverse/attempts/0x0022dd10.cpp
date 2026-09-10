// ?onContaining@TransportContain@@UAEXPAVObject@@_N@Z
// partial score=0.43 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME TransportContain::onContaining, retail 0x0022DD10 (865 bytes).
//
// Identity is established by the matched RiderChangeContain::onContaining
// caller at 0x0022B3E0 and the existing TransportContain callee pin.  The
// retail body is the ContainModuleInterface secondary view: module data is at
// this-0x1c and the owning Object is at this-0x18.  This TU keeps that BFME
// view local; the vendored Zero Hour TransportContain layout is not used.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
class Player;

enum KindOfType
{
	KINDOF_BFME_66 = 0x66,
	KINDOF_BFME_6C = 0x6c
};

class Drawable
{
public:
	void apply(Bool pending);
	void bfmeDelayA(Int frames);
	void bfmeDelayB(Int frames);
};

// The drawable methods below are existing ILT targets.  The names are the
// address-backed names already recorded in symbols.csv, not new identity
// claims for the surrounding TransportContain body.
#pragma comment(linker, "/alternatename:?apply@Drawable@@QAEX_N@Z=?j_0002d439@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeDelayA@Drawable@@QAEXH@Z=?j_0003f288@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeDelayB@Drawable@@QAEXH@Z=?j_00046a1f@@YAXXZ")

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;

	template <int NUMBITS>
	class KindOfMask
	{
	public:
		UnsignedInt m_bits[(NUMBITS + 31) / 32];
	};

	typedef KindOfMask<192> KindOfMaskType;
	Bool isKindOfMulti(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear) const;
};

class Object
{
public:
	// Object::getDrawable is vtable slot 10 (+0x28) in the BFME Object view.
	virtual void objectSlot00() = 0;
	virtual void objectSlot01() = 0;
	virtual void objectSlot02() = 0;
	virtual void objectSlot03() = 0;
	virtual void objectSlot04() = 0;
	virtual void objectSlot05() = 0;
	virtual void objectSlot06() = 0;
	virtual void objectSlot07() = 0;
	virtual void objectSlot08() = 0;
	virtual void objectSlot09() = 0;
	virtual Drawable *getDrawable() const;

	void bfmeSetConditionState(Int state);
	void notifyModelConditionChanged();
	Int getTransportSlotCount() const;
	void *unidentified_001BFE20();
	void setMode(Int mode, Int value);
	void clearCondition(Int mode);
	int getRelationship(const Object *other) const;
};

// Object::unidentified_001BFE20 is the existing address-derived accessor at
// ILT 0x0000D3B9.  Its retail return is an opaque provider used only through
// the virtual slot at +0xf0 below, so keep the return opaque in this TU.
typedef void *(*BfmeOpaqueAccessor)(void);

class BfmeListProvider
{
public:
	virtual void providerSlot00() = 0;
	virtual void providerSlot01() = 0;
	virtual void providerSlot02() = 0;
	virtual void providerSlot03() = 0;
	virtual void providerSlot04() = 0;
	virtual void providerSlot05() = 0;
	virtual void providerSlot06() = 0;
	virtual void providerSlot07() = 0;
	virtual void providerSlot08() = 0;
	virtual void providerSlot09() = 0;
	virtual void providerSlot10() = 0;
	virtual void providerSlot11() = 0;
	virtual void providerSlot12() = 0;
	virtual void providerSlot13() = 0;
	virtual void providerSlot14() = 0;
	virtual void providerSlot15() = 0;
	virtual void providerSlot16() = 0;
	virtual void providerSlot17() = 0;
	virtual void providerSlot18() = 0;
	virtual void providerSlot19() = 0;
	virtual void providerSlot20() = 0;
	virtual void providerSlot21() = 0;
	virtual void providerSlot22() = 0;
	virtual void providerSlot23() = 0;
	virtual void providerSlot24() = 0;
	virtual void providerSlot25() = 0;
	virtual void providerSlot26() = 0;
	virtual void providerSlot27() = 0;
	virtual void providerSlot28() = 0;
	virtual void providerSlot29() = 0;
	virtual void providerSlot30() = 0;
	virtual void providerSlot31() = 0;
	virtual void providerSlot32() = 0;
	virtual void providerSlot33() = 0;
	virtual void providerSlot34() = 0;
	virtual void providerSlot35() = 0;
	virtual void providerSlot36() = 0;
	virtual void providerSlot37() = 0;
	virtual void providerSlot38() = 0;
	virtual void providerSlot39() = 0;
	virtual void providerSlot40() = 0;
	virtual void providerSlot41() = 0;
	virtual void providerSlot42() = 0;
	virtual void providerSlot43() = 0;
	virtual void providerSlot44() = 0;
	virtual void providerSlot45() = 0;
	virtual void providerSlot46() = 0;
	virtual void providerSlot47() = 0;
	virtual void providerSlot48() = 0;
	virtual void providerSlot49() = 0;
	virtual void providerSlot50() = 0;
	virtual void providerSlot51() = 0;
	virtual void providerSlot52() = 0;
	virtual void providerSlot53() = 0;
	virtual void providerSlot54() = 0;
	virtual void providerSlot55() = 0;
	virtual void providerSlot56() = 0;
	virtual void providerSlot57() = 0;
	virtual void providerSlot58() = 0;
	virtual void providerSlot59() = 0;
	virtual void fill(_STL::list<Object *> *objects) = 0; // vtable +0xf0
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
};

class TransportContainModuleData
{
public:
	Thing::KindOfMaskType *kindOfMask180() const
	{
		return reinterpret_cast<Thing::KindOfMaskType *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x180);
	}

	Thing::KindOfMaskType *kindOfMask198() const
	{
		return reinterpret_cast<Thing::KindOfMaskType *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x198);
	}

	void *createList() const
	{
		return *reinterpret_cast<void *const *>(
			reinterpret_cast<const char *>(this) + 0x200);
	}

	Bool keepStatus() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0x204);
	}

	Rva2225E0Filter *filter() const
	{
		return reinterpret_cast<Rva2225E0Filter *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x20c);
	}

	Bool applyPassengerDelay() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0x210);
	}

	float passengerDelay() const
	{
		return *reinterpret_cast<const float *>(
			reinterpret_cast<const char *>(this) + 0x214);
	}

	Bool scalePassengerDelay() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0x21c);
	}
};

class ObjectCreationListStore
{
public:
	void bfmeCreate(void *list, Object *owner, void *position);
};

extern ObjectCreationListStore *TheObjectCreationListStore;

class OpenContain
{
public:
	virtual void onContaining(Object *rider, Bool wasSelected);
};

class TransportContain
{
public:
	// The BFME ContainModuleInterface view has these established slots.  The
	// body calls +0x58, +0xa0, +0xd8 and +0x100 directly through this view.
	virtual void containSlot00() = 0;
	virtual void containSlot01() = 0;
	virtual void containSlot02() = 0;
	virtual void containSlot03() = 0;
	virtual void containSlot04() = 0;
	virtual void containSlot05() = 0;
	virtual void containSlot06() = 0;
	virtual void containSlot07() = 0;
	virtual void containSlot08() = 0;
	virtual void containSlot09() = 0;
	virtual void containSlot10() = 0;
	virtual void containSlot11() = 0;
	virtual void containSlot12() = 0;
	virtual void containSlot13() = 0;
	virtual void containSlot14() = 0;
	virtual void containSlot15() = 0;
	virtual void containSlot16() = 0;
	virtual void containSlot17() = 0;
	virtual void containSlot18() = 0;
	virtual void containSlot19() = 0;
	virtual void containSlot20() = 0;
	virtual void containSlot21() = 0;
	virtual void containSlot22(Object *rider, Bool value) = 0; // +0x58
	virtual void containSlot23() = 0;
	virtual void containSlot24() = 0;
	virtual void containSlot25() = 0;
	virtual void containSlot26() = 0;
	virtual void containSlot27() = 0;
	virtual void containSlot28() = 0;
	virtual void containSlot29() = 0;
	virtual void containSlot30() = 0;
	virtual void containSlot31() = 0;
	virtual void containSlot32() = 0;
	virtual void containSlot33() = 0;
	virtual void containSlot34() = 0;
	virtual void containSlot35() = 0;
	virtual void containSlot36() = 0;
	virtual void containSlot37() = 0;
	virtual void containSlot38() = 0;
	virtual void containSlot39() = 0;
	virtual Bool containSlot40() const = 0; // +0xa0
	virtual void containSlot41() = 0;
	virtual void containSlot42() = 0;
	virtual void containSlot43() = 0;
	virtual void containSlot44() = 0;
	virtual void containSlot45() = 0;
	virtual void containSlot46() = 0;
	virtual void containSlot47() = 0;
	virtual void containSlot48() = 0;
	virtual void containSlot49() = 0;
	virtual void containSlot50() = 0;
	virtual void containSlot51() = 0;
	virtual void containSlot52() = 0;
	virtual void containSlot53() = 0;
	virtual void containSlot54(Object *rider) = 0; // +0xd8
	virtual void containSlot55() = 0;
	virtual void containSlot56() = 0;
	virtual void containSlot57() = 0;
	virtual void containSlot58() = 0;
	virtual void containSlot59() = 0;
	virtual void containSlot60() = 0;
	virtual void containSlot61() = 0;
	virtual void containSlot62() = 0;
	virtual void containSlot63() = 0;
	virtual Int getContainCount(Int argument) const = 0; // +0x100
	virtual void onContaining(Object *rider, Bool wasSelected);

private:
	TransportContainModuleData *getModuleData() const
	{
		return *reinterpret_cast<TransportContainModuleData *const *>(
			reinterpret_cast<const char *>(this) - 0x1c);
	}

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x18);
	}

	Bool payloadCreated() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0xc0);
	}

	UnsignedInt &extraSlotsInUse() const
	{
		return *reinterpret_cast<UnsignedInt *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0xb8);
	}
};

// ?onContaining@TransportContain@@UAEXPAVObject@@_N@Z
void TransportContain::onContaining(Object *rider, Bool wasSelected)
{
	reinterpret_cast<OpenContain *>(this)->OpenContain::onContaining(
		rider, wasSelected);
	Object *owner = getObject();
	TransportContainModuleData *data = getModuleData();
	rider->bfmeSetConditionState(3);

	if (payloadCreated())
	{
		UnsignedInt &riderConditions = *reinterpret_cast<UnsignedInt *>(
			reinterpret_cast<char *>(rider) + 0x118);
		if ((riderConditions & 0x01000000) != 0)
		{
			riderConditions &= ~0x01000000u;
			rider->notifyModelConditionChanged();
		}
	}

	extraSlotsInUse() += rider->getTransportSlotCount() - 1;
	if (getContainCount(0) == 1)
	{
		Object *conditionOwner = getObject();
		UnsignedInt &ownerConditions = *reinterpret_cast<UnsignedInt *>(
			reinterpret_cast<char *>(conditionOwner) + 0x118);
		if ((ownerConditions & 0x00400000) == 0)
		{
			ownerConditions |= 0x00400000;
			conditionOwner->notifyModelConditionChanged();
		}
	}

	Drawable *riderDrawable = rider->getDrawable();
	if (riderDrawable != 0)
	{
		if (!containSlot40())
		{
			UnsignedInt &conditions = *reinterpret_cast<UnsignedInt *>(
				reinterpret_cast<char *>(rider) + 0x118);
			if ((conditions & 0x00800000) == 0)
			{
				conditions |= 0x00800000;
				rider->notifyModelConditionChanged();
			}
			else if ((conditions & 0x02000000) == 0)
			{
				conditions |= 0x02000000;
				rider->notifyModelConditionChanged();
			}
		}
		else
		{
			if (reinterpret_cast<Thing *>(rider)->isKindOf(KINDOF_BFME_66))
			{
				UnsignedInt &conditions = *reinterpret_cast<UnsignedInt *>(
					reinterpret_cast<char *>(rider) + 0x118);
				if ((conditions & 0x00800000) == 0)
				{
					conditions |= 0x00800000;
					rider->notifyModelConditionChanged();
				}
				else if ((conditions & 0x02000000) == 0)
				{
					conditions |= 0x02000000;
					rider->notifyModelConditionChanged();
				}
			}
			else
			{
				UnsignedInt &conditions = *reinterpret_cast<UnsignedInt *>(
					reinterpret_cast<char *>(rider) + 0x118);
				if ((conditions & 0x02000000) == 0)
				{
					conditions |= 0x02000000;
					rider->notifyModelConditionChanged();
				}
			}
		}

		riderDrawable->apply(false);
	}

	Thing::KindOfMaskType *firstMask = data->kindOfMask180();
	for (Int i = 0; i != 6; ++i)
	{
		if (firstMask->m_bits[i] != 0)
		{
			if (reinterpret_cast<Thing *>(rider)->isKindOfMulti(
				*data->kindOfMask198(), *reinterpret_cast<Thing::KindOfMaskType *>(
					0x012ED8B8)))
			{
				getObject()->clearCondition(4);
				goto masks_done;
			}
			break;
		}
	}

	Thing::KindOfMaskType *secondMask = data->kindOfMask198();
	for (Int i = 0; i != 6; ++i)
	{
		if (secondMask->m_bits[i] != 0)
		{
			if (reinterpret_cast<Thing *>(rider)->isKindOfMulti(
				*secondMask, *reinterpret_cast<Thing::KindOfMaskType *>(
					0x012ED8B8)))
				getObject()->clearCondition(5);
			break;
		}
	}

	masks_done:
	containSlot54(rider);
	containSlot22(rider, false);

	if (data->createList() != 0)
	{
		if (owner->getRelationship(rider) != 2)
		{
			if (!data->keepStatus())
				rider->setMode(0x3b, 1);

			TheObjectCreationListStore->bfmeCreate(
				data->createList(), owner, reinterpret_cast<char *>(owner) + 0x38);
			if (!data->keepStatus())
				rider->clearCondition(0x3b);
		}
	}

	if (!data->applyPassengerDelay() || riderDrawable == 0)
		return;

	float delay = data->passengerDelay();
	if (delay <= 0.0f)
		return;
	if (!data->filter()->accepts(rider, 0))
		return;
	if (!reinterpret_cast<Thing *>(rider)->isKindOf(KINDOF_BFME_6C))
		return;

	BfmeListProvider *provider = reinterpret_cast<BfmeListProvider *>(
		rider->unidentified_001BFE20());
	_STL::list<Object *> objects;
	provider->fill(&objects);
	for (_STL::list<Object *>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		Object *object = *it;
		if (object == 0)
			continue;
		Drawable *drawable = object->getDrawable();
		if (drawable == 0)
			continue;

		Int frames = (Int)delay;
		if (data->scalePassengerDelay())
			drawable->bfmeDelayA(frames);
		else
			drawable->bfmeDelayB(frames);
	}
}
