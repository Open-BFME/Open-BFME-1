// cl: /O2 /DNDEBUG /MD
// Retail 0x00470840 returns the dword at receiver offset 0x4.

struct Rva00470840
{
	char m_padding[4];
	int m_field4;

	int get() const;
};

int Rva00470840::get() const
{
	return m_field4;
}

struct Rva002A5A90
{
	char m_padding[4];
	int m_field4;

	int get() const;
};

int Rva002A5A90::get() const
{
	return m_field4;
}
