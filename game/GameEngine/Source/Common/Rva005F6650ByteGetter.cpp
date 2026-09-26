// Byte-field getter at 0x005F6650.
//
//     mov al, byte ptr [ecx+0x1A4] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva005F6650
{
public:
	unsigned char get();
	char m_lead[0x1A4];
	unsigned char m_value;
};

unsigned char Rva005F6650::get()
{
	return m_value;
}
