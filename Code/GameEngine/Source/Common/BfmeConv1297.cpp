// Open-BFME5 conversions.

class BfmeSlotSQA
{
public:
	void bfmeOneSQA(int v);
	void bfmeTwoSQA(int v);
};

class BfmeThingSQA
{
public:
	void bfmeGoSQA(int a, int b);
	char m_bfmePad[0x178];
	BfmeSlotSQA m_bfmeSlot;
};

void BfmeThingSQA::bfmeGoSQA(int a, int b)
{
	m_bfmeSlot.bfmeOneSQA(a);
	m_bfmeSlot.bfmeTwoSQA(b);
}
