// cl: /O2 /DNDEBUG /MD
// Retail 0x00065290 returns the dword at receiver offset 0x3C.

struct Rva00065290
{
	char m_padding[0x3c];
	int m_field3C;

	int method() const;
};

int Rva00065290::method() const
{
	return m_field3C;
}
