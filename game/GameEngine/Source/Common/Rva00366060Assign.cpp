// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00365070Blk
{
public:
	Rva00365070Blk &operator=(const Rva00365070Blk &other);

private:
	int m_pad[3];
};

class Rva00366060
{
	int m_00;
	int m_04;
	char m_08;
	Rva0036CA00Str m_0C;
	Rva0036CA00Str m_10;
	Rva0036CA00Str m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	Rva00365070Blk m_30;
	int m_3C;
	int m_40;
	int m_44;
	Rva0036CA00Str m_48;
	char m_4C;
	int m_50;
	Rva0036CA00Str m_54;

public:
	Rva00366060 &operator=(const Rva00366060 &other);
};

Rva00366060 &Rva00366060::operator=(const Rva00366060 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_3C = other.m_3C;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_50 = other.m_50;
	m_54 = other.m_54;
	return *this;
}

extern "C" Rva00366060 *__cdecl Rva003662C0CopyRange(
	const Rva00366060 *first,
	const Rva00366060 *last,
	Rva00366060 *result)
{
	int count = last - first;
	while( count > 0 )
	{
		*result = *first;
		++first;
		++result;
		--count;
	}
	return result;
}

// @_Rva003662C0CopyRange 0x003662C0
