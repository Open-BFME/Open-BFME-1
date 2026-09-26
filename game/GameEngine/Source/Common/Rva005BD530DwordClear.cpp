// Retail at 0x005BD530 writes 0 to the dword at this+0x1A0 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva005BD530
{
public:
	void apply(int);
	char m_lead[0x1A0];
	unsigned int m_val;
};

void Rva005BD530::apply(int)
{
	m_val = 0;
}
