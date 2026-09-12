// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// MonsterDockUpdate::onApproachReached, retail RVA 0x002CDDF0 (216 bytes).
// The MonsterDockUpdate constructor and destructor install DockUpdateInterface
// vtable 0x010CA9F0: slot 8 routes through 0x00029181 to this body. The base
// vtable 0x010CA800 has onApproachReached in that slot, and this override calls
// it through 0x0001A6E0 -> 0x002CBCC0. onEnterReached is the next slot.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef unsigned short PlayerMask;
typedef bool Bool;
typedef int Int;

class BfmeFlags
{
public:
	Bool test(Int bit) const
	{
		return (m_bits & (1U << bit)) != 0;
	}

	void set(Int bit)
	{
		m_bits |= 1U << bit;
	}

private:
	UnsignedInt m_bits;
};

template <int Bits>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bit)
	{
		m_bits.set(bit);
	}

	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(bit) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (bit))

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);

	unsigned char m_pad[0x130];
	BfmeFlags m_flags;
};

class GameLogic
{
public:
	void deselectObject(Object *object, PlayerMask playerMask, Bool affectClient);
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

extern GameLogic *TheGameLogic;

class DockUpdate
{
public:
	virtual void onApproachReached(Object *docker);
};

class MonsterDockUpdate : public DockUpdate
{
public:
	virtual void onApproachReached(Object *docker);
};

void MonsterDockUpdate::onApproachReached(Object *docker)
{
	DockUpdate::onApproachReached(docker);
	GameLogic *logic = TheGameLogic;
	Object *me = *(Object **)((char *)this - 0x18);
	logic->deselectObject(docker, 0xffff, true);
	me->setStatus(MAKE_OBJECT_STATUS_MASK(3));
	me->setStatus(MAKE_OBJECT_STATUS_MASK(59));
	docker->setStatus(MAKE_OBJECT_STATUS_MASK(3));
	docker->setStatus(MAKE_OBJECT_STATUS_MASK(59));

	Object *owner = *(Object **)((char *)this - 0x18);
	if (!owner->m_flags.test(16))
	{
		owner->m_flags.set(16);
		((BfmeOwnerVNI *)owner)->bfmeApply1VNI();
	}
}
