// Retail at 0x00511250 writes 4 to the dword at this+0x258 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva00511250
{
public:
	void apply(int);
	char m_lead[0x258];
	unsigned int m_val;
};

void Rva00511250::apply(int)
{
	m_val = 4;
}
