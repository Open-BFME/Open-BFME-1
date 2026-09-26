// Byte-field getter at 0x0016A8D0.
//
//     mov al, byte ptr [ecx+0x529] / ret
//
// Identity is not recovered. The class name is the retail RVA.
class Rva0016A8D0
{
public:
	unsigned char get();
	char m_lead[0x529];
	unsigned char m_value;
};

unsigned char Rva0016A8D0::get()
{
	return m_value;
}
