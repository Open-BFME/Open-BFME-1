// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG
//
// 96B twin of ?bfmeMarkAX@BfmeMaskAX@@QAEXHHE@Z (BfmeMaskAX.cpp): identical
// bounds-check-then-set/clear-bit shape, but the byte-buffer begin/end
// fields sit 0x18 bytes further into the object (+0x5c/+0x60 instead of
// +0x44/+0x48), so the padding block ahead of them is 0x24 bytes instead of
// 0x0c. Address-derived name pending a caller/vtable that names the real
// class.

struct Rva00749990BytesAX
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class Rva00749990MaskAX
{
public:
	void bfmeMarkAX(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x24];
	Rva00749990BytesAX m_bits;
};

// ?bfmeMarkAX@Rva00749990MaskAX@@QAEXHHE@Z
void Rva00749990MaskAX::bfmeMarkAX(int x, int y, unsigned char value)
{
	Rva00749990MaskAX *self = this;

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
