// cl: /DNDEBUG /MD /EHsc
// Retail at 0x00799CD0 is mov eax, [ecx+0x294] / ret.
// Identity is not recovered.

class Rva00799CD0
{
public:
	int get();
	char m_lead[0x294];
	int m_value;
};

int Rva00799CD0::get()
{
	return m_value;
}
