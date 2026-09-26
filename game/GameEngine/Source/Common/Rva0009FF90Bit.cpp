// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0009FF90Bit
{
public:
	int lowBit();

private:
	char m_pad[0x344];
	unsigned char m_bits;
};

int Rva0009FF90Bit::lowBit()
{
	return m_bits & 1;
}
