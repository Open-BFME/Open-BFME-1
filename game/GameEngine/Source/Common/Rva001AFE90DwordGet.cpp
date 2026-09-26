class Rva001AFE90
{
	unsigned char m_padding[0x4];
	unsigned int m_value;

public:
	unsigned int get() const;
};

// ?get@Rva001AFE90@@QBEIXZ
unsigned int Rva001AFE90::get() const
{
	return m_value;
}
