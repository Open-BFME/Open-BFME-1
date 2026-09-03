// Open-BFME5 conversion of the codec image-buffer release helper.

void bfmeTwoBZB(void *what);

struct Rva009A8880Buffer
{
	unsigned char m_pad0[0x244];
	void *m_at244;
	void *m_at248;
	void *m_at24C;
	void *m_at250;
	void *m_at254;
	void *m_at258;
	void *m_at25C;
	void *m_at260;
};

void Rva009A8880Release(void *what)
{
	Rva009A8880Buffer *self = (Rva009A8880Buffer *)what;

	if (self->m_at248 != 0)
		bfmeTwoBZB(self->m_at248);
	if (self->m_at250 != 0)
		bfmeTwoBZB(self->m_at250);
	if (self->m_at258 != 0)
		bfmeTwoBZB(self->m_at258);
	if (self->m_at260 != 0)
		bfmeTwoBZB(self->m_at260);

	self->m_at248 = 0;
	self->m_at250 = 0;
	self->m_at258 = 0;
	self->m_at244 = 0;
	self->m_at24C = 0;
	self->m_at254 = 0;
	self->m_at260 = 0;
}
