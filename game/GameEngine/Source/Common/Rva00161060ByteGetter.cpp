// Byte-field getter at 0x00161060.
//
//     mov al, byte ptr [ecx+0x4CB] / ret
//
// Identity is not recovered. The class name is the retail RVA.
class Rva00161060
{
public:
	unsigned char get();
	char m_lead[0x4CB];
	unsigned char m_value;
};

unsigned char Rva00161060::get()
{
	return m_value;
}
