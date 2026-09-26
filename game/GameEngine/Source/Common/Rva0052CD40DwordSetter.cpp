// Retail at 0x0052CD40 writes 2 to the dword at this+0xA4 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva0052CD40
{
public:
	void apply(int);
	char m_lead[0xA4];
	unsigned int m_val;
};

void Rva0052CD40::apply(int)
{
	m_val = 2;
}
