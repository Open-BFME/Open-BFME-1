// Retail at 0x00537A30 writes 7 to the dword at this+0x188 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva00537A30
{
public:
	void apply(int);
	char m_lead[0x188];
	unsigned int m_val;
};

void Rva00537A30::apply(int)
{
	m_val = 7;
}
