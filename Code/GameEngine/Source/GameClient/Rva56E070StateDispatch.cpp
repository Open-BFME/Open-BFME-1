// cl: /DNDEBUG /MD /EHsc

class BfmeThingME
{
public:
	int bfmeTestME();
};

class Rva005121A0Service
{
public:
	void dispatch( void *first, void *second, bool selected, int state );
};

extern Rva005121A0Service *TheRva005121A0Service;

class Rva56E070StateOwner : public BfmeThingME
{
public:
	char m_pad0[0x258];
	int m_state;
	int m_direction;
	char m_pad260[4];
	void *m_arg264;
	void *m_arg268;
	void *m_context26c;
	int m_mode270;
	int m_value274;
	bool m_flag278;
	char m_pad279[3];
	int m_auxiliaryState;

	void prepareFinish();
	void finishCurrent();
	void finishTail();
	void finishState14();
	void finishState15();
	void finishState16();
	void beginState(int unused);
	void dispatchLateState(int unused);
};

void Rva56E070StateOwner::finishCurrent()
{
	if (m_auxiliaryState == 4) {
		prepareFinish();
		finishTail();
		return;
	}
	TheRva005121A0Service->dispatch(
		m_arg264, m_arg268, m_mode270 == 3, m_auxiliaryState );
	finishTail();
}

void Rva56E070StateOwner::beginState(int unused)
{
	if (m_state != 0)
		return;
	m_direction = bfmeTestME();
	if (m_flag278) {
		m_state = 10;
		return;
	}
	if (m_auxiliaryState == 4) {
		finishState14();
		return;
	}
	m_state = 3;
}

void Rva56E070StateOwner::dispatchLateState(int unused)
{
	if (m_state == 14) {
		if (m_auxiliaryState == 4) {
			finishState14();
			return;
		}
		m_state = 3;
		return;
	}
	if (m_state == 15) {
		finishState15();
		return;
	}
	if (m_state == 16) {
		finishState16();
		return;
	}
	if (m_state == 17) {
		m_state = m_direction != 0 ? 3 : 1;
	}
}
