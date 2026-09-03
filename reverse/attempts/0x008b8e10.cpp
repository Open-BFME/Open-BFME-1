// ?bfmeSet1242@BfmeN1242@@QAEXHPAVBfmeE1242@@@Z
// partial score=0.92 date=2026-09-02
// cl: /O2 /DNDEBUG /MD

class BfmeE1242;

class BfmeN1242
{
public:
	void bfmeReserve1242(int n);
	void bfmePut1242(int i, BfmeE1242 *e);
	void bfmeSet1242(int i, BfmeE1242 *e);

	char m_bfmePad00[0x28];
	int m_bfme28;
};

void BfmeN1242::bfmeSet1242(int i, BfmeE1242 *e)
{
	int n;
	BfmeN1242 *self;
	self = this;
	if (i >= 0)
	{
		n = i + 1;
		self->bfmeReserve1242(n);
		self->bfmePut1242(i, e);
		int c = self->m_bfme28;
		if (n > c)
			c = n;
		self->m_bfme28 = c;
	}
}
