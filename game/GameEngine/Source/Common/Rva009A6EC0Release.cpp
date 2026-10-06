// Open-BFME5 conversion of the codec buffer release helper.

// Each call targets 0x009A5980, the matched 5-byte tail jump that forwards to
// the free-and-dispatch helper at 0x009A58E0.
void Rva009A5980(void *what);

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
			Rva009A5980(self->m_at188);
		self->m_at188 = 0;
		self->m_at180 = 0;

		if (self->m_at18C != 0)
			Rva009A5980(self->m_at18C);
		self->m_at18C = 0;
		self->m_at184 = 0;

		Rva009A5980(*what);
		*what = 0;
	}
}
