// cl: /DNDEBUG /MD /EHsc
// Retail resets four adjacent state fields to their sentinel values.

class Rva0048E2F0
{
public:
	void reset();

private:
	unsigned char m_padding[8];
	volatile unsigned int m_low;
	volatile unsigned int m_high;
	volatile unsigned int m_tailLow;
	volatile unsigned int m_tailHigh;
};

void Rva0048E2F0::reset()
{
	m_high = 0x0000FFFF;
	m_low = 0x0000FFFF;
	m_tailHigh = 0xFFFFFFFF;
	m_tailLow = 0xFFFFFFFF;
}
