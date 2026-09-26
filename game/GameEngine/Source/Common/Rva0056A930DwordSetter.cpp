// Retail at 0x0056A930 writes 1 to the dword at this+0x258 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva0056A930
{
public:
	void apply(int);
	char m_lead[0x258];
	unsigned int m_val;
};

void Rva0056A930::apply(int)
{
	m_val = 1;
}
