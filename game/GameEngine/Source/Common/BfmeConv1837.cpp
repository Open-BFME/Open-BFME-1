void __stdcall bfmeNotifyXA(int kind);
void __cdecl bfmeReleaseXA(void *item);

class BfmeStateXA
{
public:
	void bfmeStepXA(void *unused);

	void bfmeApplyXA(void *item, int kind);
	void bfmeFlushXA();
	void bfmeDoneXA();

	unsigned char m_bfmeHeadXA[0x40];
	void *m_bfmeFirstXA;
	void *m_bfmeSecondXA;
	unsigned char m_bfmeMidXA[0x5c];
	int m_bfmeModeXA;
};

void BfmeStateXA::bfmeStepXA(void *unused)
{
	switch (m_bfmeModeXA)
	{
	case 1:
		bfmeApplyXA(m_bfmeFirstXA, 1);
		break;
	case 2:
		bfmeApplyXA(m_bfmeSecondXA, 2);
		break;
	case 3:
		bfmeNotifyXA(1);
		break;
	}

	bfmeFlushXA();
	bfmeReleaseXA(m_bfmeSecondXA);
	bfmeDoneXA();
}
