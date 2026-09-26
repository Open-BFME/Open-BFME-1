// Byte-field getter at 0x00160460.
//
//     mov al, byte ptr [ecx+0x294] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva00160460
{
public:
	unsigned char get();
	char m_lead[0x294];
	unsigned char m_value;
};

unsigned char Rva00160460::get()
{
	return m_value;
}
