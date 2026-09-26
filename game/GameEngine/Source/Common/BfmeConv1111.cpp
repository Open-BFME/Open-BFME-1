// Open-BFME5 conversions.

class BfmeK1111
{
public:
	void bfmeEnd1111(void);
};

class BfmeE1111
{
public:
	virtual void bfmeSlot1111E_0(int a);
};

struct BfmeNode1111
{
	char m_bfmePad[8];
	BfmeNode1111 *m_bfme08;
	char m_bfmePad1[8];
	BfmeK1111 *m_bfme14;
};

BfmeNode1111 *__cdecl bfmeNext1111(BfmeNode1111 *p);
void __cdecl bfmeFree1111(void *p);

struct BfmeVt1111
{
	char m_bfmePad[0x28];
	void (__stdcall *m_bfme28)(BfmeE1111 *e);
};

class BfmeW1111
{
public:
	void bfmeGo1111A(void);
	void bfmeUnlink1111(BfmeE1111 *e);
	BfmeVt1111 *m_bfmeVt;
	char m_bfmePad0[4];
	BfmeE1111 *m_bfme08;
	char m_bfmePad1[0x10];
	BfmeNode1111 *m_bfme1c;
};

void BfmeW1111::bfmeGo1111A(void)
{
	BfmeNode1111 *h = m_bfme1c;
	BfmeNode1111 *p = h->m_bfme08;
	BfmeE1111 *e;

	while (p != h) {
		BfmeK1111 *k = p->m_bfme14;

		if (k) {
			k->bfmeEnd1111();
			bfmeFree1111(k);
		}
		p = bfmeNext1111(p);
		h = m_bfme1c;
	}
	e = m_bfme08;
	while (e) {
		bfmeUnlink1111(e);
		m_bfmeVt->m_bfme28(e);
		if (e)
			e->bfmeSlot1111E_0(1);
		e = m_bfme08;
	}
}
