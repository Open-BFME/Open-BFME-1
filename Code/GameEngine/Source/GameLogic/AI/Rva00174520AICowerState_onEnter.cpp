// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Retail 0x00174520: AICowerState::onEnter.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_FAILURE = -2
};

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Rva00174520FlagWord
{
public:
	Bool test(int index) const
	{
		return m_bits.test(index);
	}

	void set(int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<32> m_bits;
};

class Object
{
public:
	Bool isSelectable() const;
	void setSelectable(Bool selectable);
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void notifyModelConditionChanged();

	unsigned char m_unreconstructed_000[0x130];
	Rva00174520FlagWord m_flags_130;
};

struct Rva00174520StateMachine
{
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_014[0x2c];
	unsigned char m_field_040;
};

class Rva000A19E0StateBase
{
public:
	virtual StateReturnType onEnter();
};

class Rva001744C0State : public Rva000A19E0StateBase
{
	unsigned char m_unreconstructed_004[0x18];
	Rva00174520StateMachine *m_machine;
	unsigned char m_unreconstructed_020[4];
	unsigned char m_selectable;

public:
	virtual StateReturnType onEnter();
};

extern void j_00026e04();
typedef StateReturnType (__fastcall *Rva00174520BaseOnEnter)(Rva001744C0State *state);

StateReturnType Rva001744C0State::onEnter()
{
	Object *owner = m_machine->m_owner;
	m_selectable = owner->isSelectable();
	owner->setSelectable(false);

	owner->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 68), true);

	if (!owner->m_flags_130.test(25))
	{
		owner->m_flags_130.set(25);
		owner->notifyModelConditionChanged();
	}

	m_machine->m_field_040 = 1;
	return ((Rva00174520BaseOnEnter)j_00026e04)(this);
}
