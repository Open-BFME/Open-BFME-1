// cl: /DNDEBUG /MD /O2
// Swap two 8-byte pointer pairs at +4, then the two 32-byte blocks at +0xC
// and +0x2C. The pair address is `other ? &other->m_04 : 0`.

class Rva00356830Blk
{
public:
	void swap(Rva00356830Blk &other);

private:
	int m_data[8];
};

class Rva003569D0Blk
{
public:
	void swap(Rva003569D0Blk &other);

private:
	int m_data[8];
};

class Rva00357800Owner
{
public:
	void swap(Rva00357800Owner *other);

private:
	int m_00;
	int m_04;
	int m_08;
	Rva00356830Blk m_0C;
	Rva003569D0Blk m_2C;
};

static void swapInt(int &left, int &right)
{
	int value = left;
	left = right;
	right = value;
}

// ?swap@Rva00357800Owner@@QAEXPAV1@@Z
void Rva00357800Owner::swap(Rva00357800Owner *other)
{
	int *right = other ? &other->m_04 : 0;
	swapInt(m_04, *right);
	swapInt(m_08, right[1]);

	m_0C.swap(other->m_0C);
	m_2C.swap(other->m_2C);
}
