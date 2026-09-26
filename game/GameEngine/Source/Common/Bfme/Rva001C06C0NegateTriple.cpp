// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001C06C0 (23 bytes).

class Rva001C06C0
{
public:
	void negate();

private:
	unsigned m_first;
	unsigned m_second;
	unsigned m_third;
};

void Rva001C06C0::negate()
{
	m_first = ~m_first;
	m_second = ~m_second;
	m_third = ~m_third;
}
