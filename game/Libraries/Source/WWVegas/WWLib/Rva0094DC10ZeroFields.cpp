// Retail 0x0094DC10 ends at 0x0094DC1F; an INT3 separates the next body.
struct Rva0094DC10Fields
{
	unsigned short m_first;
	unsigned short m_second;
	void *m_pointer;

	Rva0094DC10Fields();
	Rva0094DC10Fields *keepAt94DC20(unsigned int ignored);
};

Rva0094DC10Fields::Rva0094DC10Fields()
{
	m_first = 0;
	m_second = 0;
	m_pointer = 0;
}

Rva0094DC10Fields *Rva0094DC10Fields::keepAt94DC20(unsigned int)
{
	return this;
}
