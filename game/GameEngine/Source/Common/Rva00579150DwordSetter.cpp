// Retail at 0x00579150 writes 1 to the dword at this+0x400 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva00579150
{
public:
	void apply(int);
	char m_lead[0x400];
	unsigned int m_val;
};

void Rva00579150::apply(int)
{
	m_val = 1;
}
