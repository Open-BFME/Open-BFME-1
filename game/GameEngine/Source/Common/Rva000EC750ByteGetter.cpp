// Byte-field getter at 0x000EC750.
//
//     mov al, byte ptr [ecx+0x32C] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000EC750
{
public:
	unsigned char get();
	char m_lead[0x32C];
	unsigned char m_value;
};

unsigned char Rva000EC750::get()
{
	return m_value;
}
