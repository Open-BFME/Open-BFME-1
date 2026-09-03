// cl: /DNDEBUG /MD /O2
// Memberwise swap of a 32-byte block: six dwords exchanged in place and two
// 4-byte proxy members swapped through already-pinned cdecl helpers.

struct Rva00356830Proxy8
{
	int m_value;
};

struct Rva00356830Proxy14
{
	int m_value;
};

struct Rva003569D0Proxy14
{
	int m_value;
};

void __cdecl swap(Rva00356830Proxy8 &left, Rva00356830Proxy8 &right);
void __cdecl swap(Rva00356830Proxy14 &left, Rva00356830Proxy14 &right);
void __cdecl swap(Rva003569D0Proxy14 &left, Rva003569D0Proxy14 &right);

class Rva00356830Blk
{
public:
	void swap(Rva00356830Blk &other);

private:
	int m_00;
	int m_04;
	Rva00356830Proxy8 m_08;
	int m_0c;
	int m_10;
	Rva00356830Proxy14 m_14;
	int m_18;
	int m_1c;
};

class Rva003569D0Blk
{
public:
	void swap(Rva003569D0Blk &other);

private:
	int m_00;
	int m_04;
	Rva00356830Proxy8 m_08;
	int m_0c;
	int m_10;
	Rva003569D0Proxy14 m_14;
	int m_18;
	int m_1c;
};

static void swapInt(int &left, int &right)
{
	int value = left;
	left = right;
	right = value;
}

// ?swap@Rva00356830Blk@@QAEXAAV1@@Z
void Rva00356830Blk::swap(Rva00356830Blk &other)
{
	swapInt(m_00, other.m_00);
	swapInt(m_04, other.m_04);
	::swap(m_08, other.m_08);
	swapInt(m_0c, other.m_0c);
	swapInt(m_10, other.m_10);
	::swap(m_14, other.m_14);
	swapInt(m_18, other.m_18);
	swapInt(m_1c, other.m_1c);
}

// ?swap@Rva003569D0Blk@@QAEXAAV1@@Z
void Rva003569D0Blk::swap(Rva003569D0Blk &other)
{
	swapInt(m_00, other.m_00);
	swapInt(m_04, other.m_04);
	::swap(m_08, other.m_08);
	swapInt(m_0c, other.m_0c);
	swapInt(m_10, other.m_10);
	::swap(m_14, other.m_14);
	swapInt(m_18, other.m_18);
	swapInt(m_1c, other.m_1c);
}
