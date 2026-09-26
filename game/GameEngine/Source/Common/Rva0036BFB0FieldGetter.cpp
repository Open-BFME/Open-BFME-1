// The carved body returns the second dword from its address-derived object.

struct Rva0036BFB0
{
	int m_pad0;
	int m_value;

	int getAt4() const;
};

int Rva0036BFB0::getAt4() const
{
	return m_value;
}
