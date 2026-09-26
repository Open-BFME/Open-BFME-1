// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x008994B0 (20 bytes).
// Retail copies the low byte of this+0x1C through the output pointer and
// returns the dword at this+0x18.

class Rva008994B0
{
public:
	unsigned copyLowByte(unsigned *output);

private:
	unsigned char m_unmodelled_000[0x18];
	unsigned m_result;
	unsigned m_value;
};

unsigned Rva008994B0::copyLowByte(unsigned *output)
{
	*output = m_value & 0xFF;
	return m_result;
}
