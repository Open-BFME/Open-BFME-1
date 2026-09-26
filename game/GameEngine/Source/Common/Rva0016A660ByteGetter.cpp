// Byte-field getter at 0x0016A660.
//
//     mov al, byte ptr [ecx+0x31F] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva0016A660
{
public:
	unsigned char get();
	char m_lead[0x31F];
	unsigned char m_value;
};

unsigned char Rva0016A660::get()
{
	return m_value;
}
