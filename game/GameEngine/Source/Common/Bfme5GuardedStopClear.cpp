struct BfmeStopState
{
	char m_bfmeFields[0x4C];
	int m_bfmeStatus;
};

class BfmeStopF
{
public:
	char m_bfmeFields[4];
	BfmeStopState *m_bfmeState;
};

void j_00015e2e();

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
		// One-argument fastcall places this in ECX, like a no-argument thiscall.
		typedef void (__fastcall *BfmeStopCall)(BfmeStopF *);
		reinterpret_cast<BfmeStopCall>(&j_00015e2e)(stopper);
		m_bfmeStopper = 0;
	}
}
