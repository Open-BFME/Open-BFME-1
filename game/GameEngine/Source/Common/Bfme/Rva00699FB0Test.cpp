// cl: /DNDEBUG /MD /EHsc

class Rva00699FB0
{
	public:
	unsigned char m_unmodelled_000[8];
	unsigned *m_object;
	unsigned char m_unmodelled_00C[0x30];
};

bool __stdcall Rva00699FB0Test(const Rva00699FB0 *self)
{
	return ((self->m_object[0x3C / 4] >> 3) & 1u) != 0;
}
