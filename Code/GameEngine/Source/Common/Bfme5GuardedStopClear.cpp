struct BfmeStopState
{
	char m_bfmeFields[0x4C];
	int m_bfmeStatus;
};

class BfmeStopF
{
public:
	void bfmeStop(void);

	char m_bfmeFields[4];
	BfmeStopState *m_bfmeState;
};

class Gen_0028EFD0
{
public:
	void bfmeClear(void);

private:
	char m_bfmeFields[0x8C];
	BfmeStopF *m_bfmeStopper;
};

// ?bfmeClear@Gen_0028EFD0@@QAEXXZ
void Gen_0028EFD0::bfmeClear(void)
{
	BfmeStopF *stopper = m_bfmeStopper;

	if (stopper != 0 && stopper->m_bfmeState->m_bfmeStatus != -1)
	{
		stopper->bfmeStop();
		m_bfmeStopper = 0;
	}
}
