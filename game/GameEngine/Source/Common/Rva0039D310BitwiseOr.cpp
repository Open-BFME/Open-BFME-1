// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0039D310Bits
{
public:
	void orWith(const Rva0039D310Bits *other);

private:
	unsigned int m_bits0;
	unsigned int m_bits1;
	unsigned int m_bits2;
	unsigned int m_bits3;
	unsigned int m_bits4;
	unsigned int m_bits5;
};

void Rva0039D310Bits::orWith(const Rva0039D310Bits *other)
{
	m_bits0 |= other->m_bits0;
	m_bits1 |= other->m_bits1;
	m_bits2 |= other->m_bits2;
	m_bits3 |= other->m_bits3;
	m_bits4 |= other->m_bits4;
	m_bits5 |= other->m_bits5;
}
