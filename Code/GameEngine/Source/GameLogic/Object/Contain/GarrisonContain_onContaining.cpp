// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail RVA 0x0021EFC0, 179 bytes.
//
// The caller/thunk pair is the GarrisonContain containment hook: the retail
// vtable installed by the matched GarrisonContain constructor at +0x20 has
// this body at slot +0x44.  The GeneralsMD GarrisonContain implementation is
// the source family; the BFME body additionally applies the two observed
// model/status masks and tests the existing struct-return containment status.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

template<int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

enum DisabledType
{
	DISABLED_HELD = 3
};

struct Rva221A50Triple
{
	unsigned int first;
	unsigned int second;
	unsigned int third;
};

class Gen_00411DD0
{
public:
	void bfmeSet(Bool value);
};

class Thing
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}

	void setPosition(const Coord3D *position);
};

class Object
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

	void setDisabled(DisabledType type);
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);
};

class OpenContain
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
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void onContaining(Object *object, Bool wasSelected);
};

class GarrisonContain : public OpenContain
{
public:
	virtual void recalcApparentControllingPlayer();
	virtual void onContaining(Object *object, Bool wasSelected);

	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual Rva221A50Triple getStatus(Object *object) const;
};

// ?onContaining@GarrisonContain@@UAEXPAVObject@@_N@Z
void GarrisonContain::onContaining(Object *object, Bool wasSelected)
{
	OpenContain::onContaining(object, wasSelected);

	Object *structure = *(Object **)((unsigned char *)this - 0x18);
	object->setDisabled(DISABLED_HELD);
	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 57), true);
	structure->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 1), true);
	*(unsigned int *)((unsigned char *)object + 0x2a0) |= 1;
	reinterpret_cast<Thing *>(object)->setPosition(
		reinterpret_cast<const Thing *>(structure)->getPosition());

	if ((getStatus(0).second & 0x10000000) != 0)
		object->getDrawable()->bfmeSet(true);

	recalcApparentControllingPlayer();
}
