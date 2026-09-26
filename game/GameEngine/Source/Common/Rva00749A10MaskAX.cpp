// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG

// Near-twin of BfmeMaskAX::bfmeMarkAX (twin 0x00749830, BfmeMaskAX.cpp):
// identical two-dimensional bounds-checked bit setter, only the padding
// before the begin/end byte-range pointers differs (0x3C bytes here instead
// of 0x0C), moving m_bits from +0x44/+0x48 to +0x74/+0x78. Concrete class
// identity is not present in the available BFME source or symbols, so the
// address-derived class name is intentional.

struct Rva00749A10Bytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class Rva00749A10MaskAX
{
public:
	void bfmeMarkAX(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x3C];
	Rva00749A10Bytes m_bits;
};

// address-derived: ?bfmeMarkAX@Rva00749A10MaskAX@@QAEXHHE@Z
void Rva00749A10MaskAX::bfmeMarkAX(int x, int y, unsigned char value)
{
	Rva00749A10MaskAX *self = this;

	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= self->m_height)
		return;
	if (x >= self->m_width)
		return;

	int index = self->m_pitch * y + (x >> 3);
	if ((unsigned int)index >= self->m_bits.size())
		return;

	unsigned char *slot = self->m_bits.m_begin + index;
	if (value)
		*slot |= (unsigned char)(1 << (x & 7));
	else
		*slot &= (unsigned char)~(1 << (x & 7));
}
