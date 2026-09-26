// Byte-field getter at 0x001B20B0.
//
//     mov al, byte ptr [ecx+0x487] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva001B20B0
{
public:
	unsigned char get();
	char m_lead[0x487];
	unsigned char m_value;
};

unsigned char Rva001B20B0::get()
{
	return m_value;
}
