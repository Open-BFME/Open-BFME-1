// ?bfmeStepBN@BfmeOwnBN@@QAEXXZ (identity unknown)
// partial score=0.85 date=2026-09-06
// 28/34 at exact size and exact structure: a one-byte local whose address is
// passed (the `lea edx,[esp+0xb]` into the push-ecx frame slot), the member
// passed twice, and the result stored back over it.
// Residue: retail emits `push 0` (the last argument) BEFORE `mov esi,ecx` and
// the two member loads, and holds them in ecx/eax where MSVC uses edx/eax and
// pushes the zero after the loads. Scratch-register and push-scheduling class.
void * __cdecl bfmeRunBN(void *first, void *second, void *third, char *status, int flag);

class BfmeOwnBN
{
public:
	void bfmeStepBN(void);

	unsigned char m_bfmeHeadBN[8];
	void *m_bfmeSrcBN;
	void *m_bfmeCurBN;
};

void BfmeOwnBN::bfmeStepBN(void)
{
	char status;

	m_bfmeCurBN = bfmeRunBN(m_bfmeCurBN, m_bfmeCurBN, m_bfmeSrcBN, &status, 0);
}
