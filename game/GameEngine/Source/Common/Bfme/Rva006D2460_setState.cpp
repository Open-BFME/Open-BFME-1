// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x006D2460 (21 bytes).
// Retail stores 1 for a nonzero byte argument and 2 for zero at this+0x3178.

class Rva006D2460
{
public:
	void setState(unsigned char value);

private:
	unsigned char m_unmodelled_000[0x3178];
	unsigned m_state;
};

void Rva006D2460::setState(unsigned char value)
{
	m_state = value ? 1 : 2;
}
