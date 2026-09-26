// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x006C8620 (21 bytes).
// Retail clears the three consecutive dwords at this+0x2FC4.

class Rva006C8620
{
public:
	void reset();

private:
	unsigned char m_unmodelled_000[0x2FC4];
	unsigned m_first;
	unsigned m_second;
	unsigned m_third;
};

void Rva006C8620::reset()
{
	m_first = 0;
	m_second = 0;
	m_third = 0;
}
