// ?bfmeValidateSets@Gen00529BE0@@QAE_NXZ
// partial score=0.78 date=2026-09-02
// cl: /EHs-c-

class Gen00529BE0Gate
{
public:
	bool active(void);
private:
	unsigned char m_data[0x40];
};

int bfmeSeed(int left, int right, ...);
int bfmeMix(int value, unsigned int key);
short bfmePick(int left, int right);

class Gen00529BE0
{
public:
	bool bfmeValidateSets(void);
private:
	unsigned char m_unmodelled[0x28];
	Gen00529BE0Gate m_gate;
	void *m_first[8];
	void *m_second[8];
	void *m_third[8];
	void *m_fourth[8];
	unsigned char m_unmodelledE8[0x20];
	void *m_required;
};

// Walk four independently selected pointer sets until the keyed state reaches
// its sentinel. Any missing selected entry rejects the state.
// ?bfmeValidateSets@Gen00529BE0@@QAE_NXZ
bool Gen00529BE0::bfmeValidateSets(void)
{
	if (m_gate.active() && m_required == 0)
		return false;

	int state = bfmeSeed(0, 0);
	while (bfmeMix(state, 0xB9DC8031) != 0x66DE9C79)
	{
		if (m_first[bfmePick(state, state)] == 0)
			return false;
		if (m_second[bfmePick(state, state)] == 0)
			return false;
		if (m_third[bfmePick(state, state)] == 0)
			return false;
		if (m_fourth[bfmePick(state, state)] == 0)
			return false;
		state = bfmeMix(state, 0xE4CD9C42);
	}
	return true;
}
