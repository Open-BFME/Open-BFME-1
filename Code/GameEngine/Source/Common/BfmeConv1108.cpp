// Open-BFME5 conversions.

class BfmeK1108
{
public:
	virtual void bfmeSlot1108K_0(void);
	virtual void bfmeSlot1108K_1(void);
	virtual void bfmeSlot1108K_2(void);
	virtual void bfmeSlot1108K_3(void);
	virtual void bfmeSlot1108K_4(void);
	virtual char bfmeSlot1108K_5(void);
};

struct BfmeNode1108
{
	char m_bfmePad[8];
	BfmeNode1108 *m_bfme08;
	char m_bfmePad1[8];
	BfmeK1108 *m_bfme14;
};

BfmeNode1108 *__cdecl bfmeNext1108(BfmeNode1108 *p);

class BfmeW1108
{
public:
	void bfmeGo1108B(void);
	BfmeNode1108 *m_bfme00;
};

void BfmeW1108::bfmeGo1108B(void)
{
	BfmeNode1108 *h = m_bfme00;
	BfmeNode1108 *p = h->m_bfme08;

	while (p != h) {
		BfmeK1108 *q = p->m_bfme14;

		if (q && q->bfmeSlot1108K_5())
			p->m_bfme14->bfmeSlot1108K_4();
		p = bfmeNext1108(p);
		h = m_bfme00;
	}
}
