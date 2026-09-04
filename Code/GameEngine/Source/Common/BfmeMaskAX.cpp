// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG

struct BfmeMaskBytesAX
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class BfmeMaskAX
{
public:
	void bfmeMarkAX(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x0c];
	BfmeMaskBytesAX m_bits;
};

// ?bfmeMarkAX@BfmeMaskAX@@QAEXHHE@Z
void BfmeMaskAX::bfmeMarkAX(int x, int y, unsigned char value)
{
	BfmeMaskAX *self = this;

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
