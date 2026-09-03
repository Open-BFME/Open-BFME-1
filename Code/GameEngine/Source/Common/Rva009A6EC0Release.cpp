// Open-BFME5 conversion of the codec buffer release helper.

void bfmeTwoBZB(void *what);

struct Rva009A6EC0Buffer
{
	unsigned char m_pad0[0x180];
	void *m_at180;
	void *m_at184;
	void *m_at188;
	void *m_at18C;
};

void Rva009A6EC0Release(void **what)
{
	Rva009A6EC0Buffer *self = (Rva009A6EC0Buffer *)*what;
	if (self != 0) {
		if (self->m_at188 != 0)
			bfmeTwoBZB(self->m_at188);
		self->m_at188 = 0;
		self->m_at180 = 0;

		if (self->m_at18C != 0)
			bfmeTwoBZB(self->m_at18C);
		self->m_at18C = 0;
		self->m_at184 = 0;

		bfmeTwoBZB(*what);
		*what = 0;
	}
}
