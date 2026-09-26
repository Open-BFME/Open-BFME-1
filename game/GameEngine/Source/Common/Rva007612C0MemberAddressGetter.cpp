// cl: /DNDEBUG /MD /EHsc
// Retail at 0x007612C0 is lea eax, [ecx+0x1B0] / ret.
// Identity is not recovered.

class Rva007612C0
{
public:
	int &get();
	char m_lead[0x1B0];
	int m_value;
};

int &Rva007612C0::get()
{
	return m_value;
}
