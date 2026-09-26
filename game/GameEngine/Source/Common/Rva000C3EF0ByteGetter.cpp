// Byte getter at 0x000C3EF0: mov al, [ecx+0x4B0] / ret.
// Identity not recovered; class name is the retail RVA.
class Rva000C3EF0
{
public:
	unsigned char get();
	char m_lead[0x4B0];
	unsigned char m_value;
};
unsigned char Rva000C3EF0::get()
{
	return m_value;
}
