// Byte-field getter at 0x000C8910.
//
//     mov al, byte ptr [ecx+0x341] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000C8910
{
public:
	unsigned char get();
	char m_lead[0x341];
	unsigned char m_value;
};

unsigned char Rva000C8910::get()
{
	return m_value;
}
