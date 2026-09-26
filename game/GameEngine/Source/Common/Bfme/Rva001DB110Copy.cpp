// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001DB110 (6 bytes).

class Rva001DB110
{
public:
	void copy();

private:
	unsigned m_value;
	unsigned m_source;
};

void Rva001DB110::copy()
{
	m_value = m_source;
}
