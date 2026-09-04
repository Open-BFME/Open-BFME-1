// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct BfmeBitPlaneBytes0074
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char operator[](int index) const { return m_begin[index]; }
};

class Gen_0074B410
{
public:
	bool bfmeBitA(int x, int y) const;

	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	unsigned char m_opaque10[0x18];
	BfmeBitPlaneBytes0074 m_bits;
	unsigned char m_opaque30[0x04];
	int m_stride;
};

bool Gen_0074B410::bfmeBitA(int x, int y) const
{
	register const Gen_0074B410 *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

class Gen_0074BA50
{
public:
	bool bfmeBitA(int x, int y) const;

private:
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	unsigned char m_opaque10[0x24];
	int m_stride;
	BfmeBitPlaneBytes0074 m_bits;
};

bool Gen_0074BA50::bfmeBitA(int x, int y) const
{
	register const Gen_0074BA50 *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

class Gen_0074BAC0
{
public:
	bool bfmeBitA(int x, int y) const;

private:
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	unsigned char m_opaque10[0x24];
	int m_stride;
	unsigned char m_opaque38[0x30];
	BfmeBitPlaneBytes0074 m_bits;
};

bool Gen_0074BAC0::bfmeBitA(int x, int y) const
{
	register const Gen_0074BAC0 *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

class Gen_0074BB30
{
public:
	bool bfmeBitA(int x, int y) const;

private:
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	unsigned char m_opaque10[0x24];
	int m_stride;
	unsigned char m_opaque38[0x48];
	BfmeBitPlaneBytes0074 m_bits;
};

bool Gen_0074BB30::bfmeBitA(int x, int y) const
{
	register const Gen_0074BB30 *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

class Gen_00749830
{
public:
	void setBit(int x, int y, unsigned char value);

private:
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	unsigned char m_opaque10[0x24];
	int m_stride;
	unsigned char m_opaque38[0x0c];
	unsigned char *m_begin;
	unsigned char *m_end;
};

void Gen_00749830::setBit(int x, int y, unsigned char value)
{
	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= m_height)
		return;
	if (x >= m_width)
		return;

	const int index = m_stride * y + (x >> 3);
	if ((unsigned)index >= (unsigned)(m_end - m_begin))
		return;

	unsigned char mask = 1;
	mask <<= x & 7;
	if (value)
		m_begin[index] |= mask;
	else
		m_begin[index] &= (unsigned char)~mask;
}
