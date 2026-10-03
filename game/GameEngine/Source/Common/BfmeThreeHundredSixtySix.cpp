struct BfmeSlotWA
{
	void *m_bfmeWhat;
	unsigned char m_bfmeRest[0x2c];
};

// Retail reaches the lazy-initialisation call through the five-byte thunk at
// ILT 0x0002DE02, which the ledger defines as ?j_0002de02@@YAXXZ in
// game/gen_small/thunks_021.cpp and nothing else defines, so the member's
// reference is spelled as that thunk. ecx still holds `this` at the call site,
// so a plain argument-less call reproduces the retail bytes.
void j_0002de02();

class BfmeThingWA
{
public:
	void *bfmeGetWA();
	unsigned char m_bfmeHead[0x1c];
	BfmeSlotWA m_bfmeSlots[120];
	unsigned char m_bfmeGapOne[0x28];
	int m_bfmeIndex;
	unsigned char m_bfmeGapTwo[0x26];
	bool m_bfmeMany;
	unsigned char m_bfmeGapThree[0x19];
	int m_bfmeState;
};

void *BfmeThingWA::bfmeGetWA()
{
	if (m_bfmeState == -1)
		j_0002de02();
	if (!m_bfmeMany)
		return m_bfmeSlots[0].m_bfmeWhat;
	return m_bfmeSlots[m_bfmeIndex].m_bfmeWhat;
}
