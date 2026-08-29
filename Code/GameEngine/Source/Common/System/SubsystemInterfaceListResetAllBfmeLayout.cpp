// readable body of ?resetAll@SubsystemInterfaceList@@QAEXXZ: Code/GameEngine/Source/Common/System/SubsystemInterface.cpp
// BFME layout reconstruction of SubsystemInterface.cpp's resetAll body.
// The BFME list stores eight-byte subsystem/slot pairs, and its reset virtual
// is at vtable offset 0x10 rather than the shared ZH offset 0x0c.

class BfmeSubsystemInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void reset() = 0;
};

struct BfmeSubsystemEntry
{
	BfmeSubsystemInterface *m_subsystem;
	void *m_slot;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterfaceList
{
public:
	void resetAll();

	BfmeSubsystemEntry *m_begin;
	BfmeSubsystemEntry *m_end;
	BfmeSubsystemEntry *m_capacity;
};

void SubsystemInterfaceList::resetAll()
{
	for (BfmeSubsystemEntry *it = m_end; it != m_begin; --it)
	{
		(it - 1)->m_subsystem->reset();
	}
}
