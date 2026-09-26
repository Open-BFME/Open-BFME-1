// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery for the identical 0x000F9350 and 0x000F9370 bodies.

class Rva000F9350
{
public:
	unsigned address(unsigned index) const;

private:
	unsigned m_first;
};

class Rva000F9370
{
public:
	unsigned address(unsigned index) const;

private:
	unsigned m_first;
};

unsigned Rva000F9350::address(unsigned index) const
{
	return m_first + index * 96u;
}

unsigned Rva000F9370::address(unsigned index) const
{
	return m_first + index * 96u;
}
