// Byte-field getter at 0x0016A650.
//
//     mov al, byte ptr [ecx+0x31E] / ret
//
// Identity is not recovered. The class name is the retail RVA.
class Rva0016A650
{
public:
	unsigned char get();
	char m_lead[0x31E];
	unsigned char m_value;
};

unsigned char Rva0016A650::get()
{
	return m_value;
}
