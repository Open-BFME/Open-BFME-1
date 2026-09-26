// Byte getter at 0x000C3ED0: mov al, [ecx+0x48B] / ret.
// Identity not recovered; class name is the retail RVA.
class Rva000C3ED0
{
public:
	unsigned char get();
	char m_lead[0x48B];
	unsigned char m_value;
};
unsigned char Rva000C3ED0::get()
{
	return m_value;
}
