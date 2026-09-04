// cl: /DNDEBUG /MD
// Candidate for the BFME two-dimensional byte-plane query at retail
// 0x006CB500.

typedef bool Bool;

struct Gen006CB500Bytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char operator[](int index) const { return m_begin[index]; }
};

class Gen006CB500BitPlane
{
public:
	Bool test(int x, int y) const;

public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
	unsigned char m_pad10[0x24];
	int m_stride;
	unsigned char m_pad38[0x3c];
	Gen006CB500Bytes m_bits;
};

Bool Gen006CB500BitPlane::test(int x, int y) const
{
	register const Gen006CB500BitPlane *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
		return 0;

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
		return 0;

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	Bool result = (value & mask) != 0;
	return result;
}
