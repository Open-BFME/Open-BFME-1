// Byte-field getter at 0x0016A820.
//
//     mov al, byte ptr [ecx+0x335] / ret
//
// Identity is not recovered. The class name keeps the retail address.
class Rva0016A820
{
public:
	unsigned char get();
	char m_lead[0x335];
	unsigned char m_value;
};

unsigned char Rva0016A820::get()
{
	return m_value;
}
