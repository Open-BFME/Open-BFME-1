// Byte getter at 0x003BC760: retail reads the byte at this+0x14.
// Identity is not recovered, so the class name keeps the retail RVA.
class Rva003BC760
{
public:
	unsigned char get();

	char m_pad[0x14];
	unsigned char m_value;
};

unsigned char Rva003BC760::get()
{
	return m_value;
}
