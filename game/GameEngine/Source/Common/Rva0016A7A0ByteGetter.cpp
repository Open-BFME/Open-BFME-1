// Byte-field getter at 0x0016A7A0.
//
//     mov al, byte ptr [ecx+0x32F] / ret
//
// Identity is not recovered. The class name is the retail RVA.
class Rva0016A7A0
{
public:
	unsigned char get();
	char m_lead[0x32F];
	unsigned char m_value;
};

unsigned char Rva0016A7A0::get()
{
	return m_value;
}
