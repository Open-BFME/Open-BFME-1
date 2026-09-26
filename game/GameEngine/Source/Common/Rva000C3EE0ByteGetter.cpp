// Byte-field getter at 0x000C3EE0.
//
//     mov al, byte ptr [ecx+0x48C] / ret
//
// Identity is not recovered. The class name is the retail RVA.
class Rva000C3EE0
{
public:
	unsigned char get();
	char m_lead[0x48C];
	unsigned char m_value;
};

unsigned char Rva000C3EE0::get()
{
	return m_value;
}
