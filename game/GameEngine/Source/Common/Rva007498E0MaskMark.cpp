// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG
//
// Near-twin of BfmeMaskAX::bfmeMarkAX (twin 0x00749830, BfmeMaskAX.cpp):
// identical bounds-checked bit-set/clear shape, but the byte-mask begin/end
// pair sits at +0x50/+0x54 here instead of +0x44/+0x48 -- 0xc more padding
// ahead of it.  Address-derived identity.

struct Rva007498E0MaskBytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class Rva007498E0Mask
{
public:
	void markBit(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x18];
	Rva007498E0MaskBytes m_bits;
};

// @?markBit@Rva007498E0Mask@@QAEXHHE@Z 0x007498E0
void Rva007498E0Mask::markBit(int x, int y, unsigned char value)
{
	Rva007498E0Mask *self = this;

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
