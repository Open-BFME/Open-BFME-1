// Open-BFME5 conversion of the codec image-buffer release helper.

// Retail calls the separately padded 5-byte free thunk at 0x009A5980
// (BfmeReleaseSetBZB.cpp, a tail jump to 0x009A58E0), not bfmeGo930C
// (0x009A58E0) itself.
void Rva009A5980(void *what);

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
		Rva009A5980(self->m_at248);
	if (self->m_at250 != 0)
		Rva009A5980(self->m_at250);
	if (self->m_at258 != 0)
		Rva009A5980(self->m_at258);
	if (self->m_at260 != 0)
		Rva009A5980(self->m_at260);

	self->m_at248 = 0;
	self->m_at250 = 0;
	self->m_at258 = 0;
	self->m_at244 = 0;
	self->m_at24C = 0;
	self->m_at254 = 0;
	self->m_at260 = 0;
}
