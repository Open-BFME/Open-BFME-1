// Address-derived state transitions. The owner is not recovered; the fields
// below are fixed by the retail receiver accesses at these two boundaries.
class Rva56A8StateOwner
{
public:
	void applyZeroState(int);
	void applyFourState(int);
	void applyDefaultState(int);
	void applyGlobalCall(int);

private:
	char m_pad0[0x258];
	volatile int m_state;
	char m_pad25c[0x20];
	int m_auxiliaryState;
};

class BfmeGlobal_012f19e8
{
public:
	void bfmeCall_000290d2();
};

void Rva56A8StateOwner::applyZeroState(int)
{
	if (m_state == 0) {
		m_auxiliaryState = 1;
		m_state = 2;
	}
}

void Rva56A8StateOwner::applyFourState(int)
{
	if (m_state == 0) {
		m_auxiliaryState = 4;
		m_state = 2;
	}
}

void Rva56A8StateOwner::applyDefaultState(int)
{
	if (m_state == 0) {
		int state = 2;
		m_auxiliaryState = state;
		m_state = state;
	}
}

void Rva56A8StateOwner::applyGlobalCall(int)
{
	if (m_state == 0 && *reinterpret_cast<volatile int *>(0x012f4b44) != 0) {
		reinterpret_cast<BfmeGlobal_012f19e8 **>(0x012f19e8)[0]->bfmeCall_000290d2();
	}
}
