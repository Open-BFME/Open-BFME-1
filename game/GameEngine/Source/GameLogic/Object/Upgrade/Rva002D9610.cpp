// Retail 0x002D9610 is a secondary-interface method whose lexical owner is
// not recoverable from the current caller inventory.  Its ABI and fields are
// nevertheless fixed by the body: slot 7 performs the preamble action, the
// owning Object supplies the controlling Player, and slot 1 receives the
// union of the player's and object's six-word completed-upgrade masks.

typedef unsigned int UnsignedInt;

struct Rva002D9610UpgradeMask
{
	UnsignedInt m_bits[6];
};

class Player
{
public:
	const Rva002D9610UpgradeMask *getCompletedUpgradeMask() const
	{
		return &m_completedUpgrades;
	}

private:
	unsigned char m_unmodelled_000[0x8c];
	Rva002D9610UpgradeMask m_completedUpgrades;
};

extern void j_00020824();

class Object
{
public:
	const Rva002D9610UpgradeMask &getCompletedUpgradeMask() const
	{
		return m_completedUpgrades;
	}

private:
	unsigned char m_unmodelled_000[0x224];
	Rva002D9610UpgradeMask m_completedUpgrades;
};

// Retail's Object::getControllingPlayer body lives behind ILT 0x20824, so the
// call site calls the thunk with the same thiscall shape.
static Player *controllingPlayerOf(Object *object)
{
	typedef Player *(Object::*ControllingPlayer)() const;
	union
	{
		void (*raw)();
		ControllingPlayer call;
	} route = { j_00020824 };
	return (object->*route.call)();
}

class Rva002D9610Owner
{
public:
	virtual void slot00() = 0;
	virtual void slot01(const Rva002D9610UpgradeMask &mask) = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;

	void rva002D9610();
};

void Rva002D9610Owner::rva002D9610()
{
	slot07();

	Rva002D9610UpgradeMask mask =
		*controllingPlayerOf(*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
			->getCompletedUpgradeMask();
	mask.m_bits[0] |= (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
		->getCompletedUpgradeMask().m_bits[0];
	mask.m_bits[1] |= (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
		->getCompletedUpgradeMask().m_bits[1];
	mask.m_bits[2] |= (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
		->getCompletedUpgradeMask().m_bits[2];
	mask.m_bits[3] |= (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
		->getCompletedUpgradeMask().m_bits[3];
	mask.m_bits[4] |= (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
		->getCompletedUpgradeMask().m_bits[4];
	mask.m_bits[5] |= (*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8))
		->getCompletedUpgradeMask().m_bits[5];

	slot01(mask);
}
