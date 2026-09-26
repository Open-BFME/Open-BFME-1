// Byte getter at 0x000E8860: mov al, [ecx+0x90] / ret.
// Identity not recovered; class name is the retail RVA.
class Rva000E8860
{
public:
	unsigned char get();
	char m_lead[0x90];
	unsigned char m_value;
};
unsigned char Rva000E8860::get()
{
	return m_value;
}
