// cl: /O2 /Ob0

class Rva000FA3F0Str
{
public:
	Rva000FA3F0Str &operator=(const Rva000FA3F0Str &other);

private:
	void *m_item;
};

class Rva000FA3F0Blk
{
public:
	Rva000FA3F0Blk &operator=(const Rva000FA3F0Blk &other);

private:
	int m_pad[3];
};

class Rva000FA3F0
{
	int m_00;
	int m_04;
	char m_08;
	Rva000FA3F0Str m_0C;
	Rva000FA3F0Str m_10;
	Rva000FA3F0Str m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	Rva000FA3F0Blk m_30;
	int m_3C;
	int m_40;
	int m_44;
	Rva000FA3F0Str m_48;
	char m_4C;
	int m_50;
	Rva000FA3F0Str m_54;
	int m_58;
	int m_5C;

public:
	Rva000FA3F0 &operator=(const Rva000FA3F0 &other);
};

Rva000FA3F0 &Rva000FA3F0::operator=(const Rva000FA3F0 &other)
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
	m_58 = other.m_58;
	m_5C = other.m_5C;
	return *this;
}

extern "C" Rva000FA3F0 *__cdecl Rva000FA0E0CopyRange(
	const Rva000FA3F0 *first,
	const Rva000FA3F0 *last,
	Rva000FA3F0 *result)
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

// @_Rva000FA0E0CopyRange 0x000FA0E0
