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

// ILT 0x000290D2 -> 0x00465B80, matched ?apply@Rva00465B80@@QAEXXZ (sets the
// byte at +0x1AC to 1), called on the window manager at 0x012F19E8.
class Rva00465B80
{
public:
	void apply();
};

class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

class AptSaveLoad;
class BfmeAptScreenSaveLoad;
extern BfmeAptScreenSaveLoad *TheAptSaveLoad;

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
	if (m_state == 0 && *reinterpret_cast<volatile int *>(&reinterpret_cast<AptSaveLoad * &>(TheAptSaveLoad)) != 0) {
		reinterpret_cast<Rva00465B80 *>(g_rva012F19E8WindowManager)->apply();
	}
}
