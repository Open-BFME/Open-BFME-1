// cl: /DNDEBUG /MD /EHsc-
// TransportContain containment validation through its secondary interface.
// The canonical Object layout supplies the status and model-condition fields.

#include "../../../../Include/Common/ScalarTypes.h"


class Object;
struct Rva2225E0Filter;

struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_previous;
	Object *m_object;
};

struct ContainedItemsList
{
	ContainedItemNode *m_sentinel;
};

#define CONTAIN_SLOT(n) virtual void containSlot##n() = 0;

class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02)
	virtual Bool isSpecialZeroSlotContainer() const = 0;
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
	CONTAIN_SLOT(44) CONTAIN_SLOT(45) CONTAIN_SLOT(46) CONTAIN_SLOT(47)
	CONTAIN_SLOT(48) CONTAIN_SLOT(49) CONTAIN_SLOT(50) CONTAIN_SLOT(51)
	CONTAIN_SLOT(52) CONTAIN_SLOT(53) CONTAIN_SLOT(54) CONTAIN_SLOT(55)
	CONTAIN_SLOT(56) CONTAIN_SLOT(57) CONTAIN_SLOT(58) CONTAIN_SLOT(59)
	CONTAIN_SLOT(60) CONTAIN_SLOT(61) CONTAIN_SLOT(62) CONTAIN_SLOT(63)
	CONTAIN_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const = 0;
};

#undef CONTAIN_SLOT

// ?hasModelConditionBit@Object@@QBE_NI@Z absent-from-retail
#define OBJECT_TU_MEMBERS \
    Bool hasModelConditionBit(unsigned bit) const \
    { \
        return (m_modelConditionFlags[bit >> 5] & (1U << (bit & 31))) != 0; \
    }
#include "../object.h"
#undef OBJECT_TU_MEMBERS

class TransportContainModuleData
{
public:
	unsigned char m_unmodelled_000[0x1f9];
	Bool m_unknown1f9;
	unsigned char m_unmodelled_1fa[0x208 - 0x1fa];
	Int m_unknown208;
};

struct Rva0022DBA0Input
{
	TransportContainModuleData *data;
	const Object *rider;
};

#define TRANSPORT_SLOT(n) virtual void transportSlot##n() = 0;

class TransportContain
{
public:
	TRANSPORT_SLOT(00) TRANSPORT_SLOT(01) TRANSPORT_SLOT(02)
	TRANSPORT_SLOT(03) TRANSPORT_SLOT(04) TRANSPORT_SLOT(05)
	TRANSPORT_SLOT(06) TRANSPORT_SLOT(07) TRANSPORT_SLOT(08)
	TRANSPORT_SLOT(09) TRANSPORT_SLOT(10) TRANSPORT_SLOT(11)
	TRANSPORT_SLOT(12) TRANSPORT_SLOT(13) TRANSPORT_SLOT(14)
	TRANSPORT_SLOT(15) TRANSPORT_SLOT(16) TRANSPORT_SLOT(17)
	TRANSPORT_SLOT(18) TRANSPORT_SLOT(19) TRANSPORT_SLOT(20)
	TRANSPORT_SLOT(21) TRANSPORT_SLOT(22)
	virtual Int getContainMax() const = 0;
	TRANSPORT_SLOT(24) TRANSPORT_SLOT(25) TRANSPORT_SLOT(26)
	TRANSPORT_SLOT(27) TRANSPORT_SLOT(28) TRANSPORT_SLOT(29)
	TRANSPORT_SLOT(30) TRANSPORT_SLOT(31) TRANSPORT_SLOT(32)
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
	TRANSPORT_SLOT(34) TRANSPORT_SLOT(35)
	TRANSPORT_SLOT(36) TRANSPORT_SLOT(37) TRANSPORT_SLOT(38)
	TRANSPORT_SLOT(39) TRANSPORT_SLOT(40) TRANSPORT_SLOT(41)
	TRANSPORT_SLOT(42) TRANSPORT_SLOT(43) TRANSPORT_SLOT(44)
	TRANSPORT_SLOT(45)
	virtual Int getExtraSlotsInUse() = 0;
	TRANSPORT_SLOT(47) TRANSPORT_SLOT(48) TRANSPORT_SLOT(49)
	TRANSPORT_SLOT(50) TRANSPORT_SLOT(51) TRANSPORT_SLOT(52)
	TRANSPORT_SLOT(53) TRANSPORT_SLOT(54) TRANSPORT_SLOT(55)
	TRANSPORT_SLOT(56) TRANSPORT_SLOT(57) TRANSPORT_SLOT(58)
	TRANSPORT_SLOT(59) TRANSPORT_SLOT(60) TRANSPORT_SLOT(61)
	TRANSPORT_SLOT(62) TRANSPORT_SLOT(63)
	virtual unsigned getContainCount002225E0(Rva2225E0Filter *countRiders) const = 0;


	TransportContainModuleData *getModuleData() const
	{
		return *(TransportContainModuleData *const *)((const char *)this - 0x1c);
	}

	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x18);
	}

private:
	unsigned char m_unmodelled_004[0xb4];
	Int m_extraSlotsInUse;
};

#undef TRANSPORT_SLOT

extern void j_000237b8();
extern void j_00026107();
extern void j_0003251f();

struct BfmeOpenContainValidationCall
{
	Bool call(const Object *object, Bool checkCapacity) const;
};

struct BfmeTransportSlotCountCall
{
	Int call() const;
};

struct BfmeKindOfCall
{
	Bool call(Int kind) const;
};

static Bool callOpenContainValidation(const TransportContain *self,
	const Object *object, Bool checkCapacity)
{
	typedef Bool (BfmeOpenContainValidationCall::*Function)(const Object *, Bool) const;
	union { void (*raw)(); Function member; } function;
	function.raw = j_000237b8;
	return (reinterpret_cast<const BfmeOpenContainValidationCall *>(self)->*
		function.member)(object, checkCapacity);
}

static Int getTransportSlotCount(const Object *object)
{
	typedef Int (BfmeTransportSlotCountCall::*Function)() const;
	union { void (*raw)(); Function member; } function;
	function.raw = j_00026107;
	return (reinterpret_cast<const BfmeTransportSlotCountCall *>(object)->*
		function.member)();
}

static Bool isKindOf(const Object *object, Int kind)
{
	typedef Bool (BfmeKindOfCall::*Function)(Int) const;
	union { void (*raw)(); Function member; } function;
	function.raw = j_0003251f;
	return (reinterpret_cast<const BfmeKindOfCall *>(object)->*
		function.member)(kind);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
	can this container contain this kind of object?
	and, if checkCapacity is TRUE, does this container have enough space left to hold the given unit?
*/
// ?isValidContainerFor@TransportContain@@UBE_NPBVObject@@_N@Z
Bool TransportContain::isValidContainerFor(const Object *rider,
	Bool checkCapacity) const
{
	Rva0022DBA0Input input = { getModuleData(), rider };
	TransportContainModuleData *data = input.data;
	rider = input.rider;
	// sanity
	if (rider == 0)
		goto nullRider;
	if ((rider->m_status[1] & 0x20000000) != 0)
		return false;

	Int playerMaskBit = data->m_unknown208;
	if (playerMaskBit != -1 &&
		!getObject()->hasModelConditionBit(playerMaskBit))
		return false;

	// The point of this new code is to determine when something is a "fake" container, to
	// look at the object inside of it to use that as the valid check. There is a case, when a
	// paratrooper (an infantry contained in a parachute). In this case, when we pass this object
	// to contain in a transport plane, we want to check the infantry, not the parachute.
	ContainModuleInterface *contain = rider->m_contain;
	if (contain != 0 && contain->isSpecialZeroSlotContainer())
	{
		// Report the first thing inside it!
		const ContainedItemsList *items = rider->m_contain->getContainedItemsList();
		if (items != 0)
		{
			ContainedItemNode *node = items->m_sentinel->m_next;
			if (node != items->m_sentinel && node->m_object != 0)
				// Replace the object we are checking with the *first* object contained within it.
				rider = node->m_object;
		}
	}

	// extend functionality
	if (!callOpenContainValidation(this, rider, checkCapacity))
		return false;

//	// only allied objects can be transported.
//	// order matters: we want to know if I consider it to be an ally, not vice versa
//	if (getObject()->getRelationship(rider) != ALLIES)
//		return false;

	if (isKindOf(rider, 0x83) && getModuleData()->m_unknown1f9)
		return getContainCount002225E0(0) < getContainMax();

	Int transportSlotCount = getTransportSlotCount(rider);
	// if 0, this object isn't transportable.
	if (transportSlotCount == 0)
		return false;

	if (checkCapacity)
		return getContainCount002225E0(0) + m_extraSlotsInUse +
			transportSlotCount <= getContainMax();
	return true;
nullRider:
	return false;
}

