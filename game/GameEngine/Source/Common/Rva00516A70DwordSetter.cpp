// Retail at 0x00516A70 writes 5 to the dword at this+0x3A8 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva00516A70
{
public:
	void apply(int);
	char m_lead[0x3A8];
	unsigned int m_val;
};

void Rva00516A70::apply(int)
{
	m_val = 5;
}
