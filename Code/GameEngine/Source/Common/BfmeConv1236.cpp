// Open-BFME5 conversions.

class BfmeB1236
{
public:
	void bfmeApply1236(void *a);
	void bfmeEmit1236(void *a, int b, void *c);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x10 - 0x08];
	int m_bfme10;
	char m_bfmePad14[0x28 - 0x14];
	int m_bfme28;
	char m_bfmePad2c[0x4c - 0x2c];
	void *m_bfme4c;
};

class BfmeA1236
{
public:
	void bfmeBegin1236();
	void bfmePush1236(void *a);
	void bfmeMark1236();
	void bfmeSet1236(void *a);
	void bfmePop1236();
	void bfmeEnd1236();
};

void bfmeGo1236(BfmeA1236 *a, BfmeB1236 *b, void *c)
{
	a->bfmeBegin1236();
	a->bfmePush1236(&b->m_bfme28);
	a->bfmeMark1236();
	if ((b->m_bfme04 & 0x3f) == 0xf && !((unsigned char)(~(b->m_bfme04 >> 15)) & 1))
		b->bfmeApply1236(b->m_bfme4c);
	a->bfmeSet1236(&b->m_bfme10);
	b->bfmeEmit1236(a, 0, c);
	a->bfmePop1236();
	a->bfmeEnd1236();
}
