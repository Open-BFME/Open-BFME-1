// Byte-field getter at 0x000C9D00.
//
//     8A 81 disp32: mov al, byte ptr [ecx+0x680] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000C9D00
{
public:
	unsigned char get();
	char m_lead[0x680];
	unsigned char m_value;
};

unsigned char Rva000C9D00::get()
{
	return m_value;
}
