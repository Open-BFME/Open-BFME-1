// The owner is unknown; retail normalizes a dword argument into byte +0x108.
struct Rva00955C00BoolFlag
{
	char m_reserved[0x108];
	bool m_nonzero108;
	void setNonzero(unsigned int input);
};

void Rva00955C00BoolFlag::setNonzero(unsigned int input)
{
	m_nonzero108 = input != 0;
}
