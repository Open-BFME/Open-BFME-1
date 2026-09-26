// Retail at 0x0051D160 writes 5 to the dword at this+0x264 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva0051D160
{
public:
	void apply(int);
	char m_lead[0x264];
	unsigned int m_val;
};

void Rva0051D160::apply(int)
{
	m_val = 5;
}
