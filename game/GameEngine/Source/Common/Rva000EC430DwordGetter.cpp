// Dword getter at 0x000EC430: mov eax, [ecx+0x274] / ret.
class Rva000EC430
{
public:
	unsigned int get();
	char m_lead[0x274];
	unsigned int m_value;
};
unsigned int Rva000EC430::get()
{
	return m_value;
}
