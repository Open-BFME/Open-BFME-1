// The carved body returns the address-derived object's dword at offset 0x28.

struct Rva0015F720
{
	int m_pad0[10];
	int m_value;

	int getAt28() const;
};

int Rva0015F720::getAt28() const
{
	return m_value;
}
