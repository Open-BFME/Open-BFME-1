// Byte-field getter at 0x00160490.
//
//     mov al, byte ptr [ecx+0x681] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva00160490
{
public:
	unsigned char get();
	char m_lead[0x681];
	unsigned char m_value;
};

unsigned char Rva00160490::get()
{
	return m_value;
}
