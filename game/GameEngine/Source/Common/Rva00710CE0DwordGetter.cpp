// cl: /DNDEBUG /MD /EHsc
// Retail at 0x00710CE0 is mov eax, [ecx+0x330] / ret.
// Identity is not recovered.

class Rva00710CE0
{
public:
	int get();
	char m_lead[0x330];
	int m_value;
};

int Rva00710CE0::get()
{
	return m_value;
}
