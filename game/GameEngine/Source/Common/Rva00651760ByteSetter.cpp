// Retail at 0x00651760 writes 1 to the byte at this+0x58 and returns.
// The owning type and field semantics were not recovered.
class Rva00651760
{
public:
	void apply();
	char m_lead[0x58];
	char m_flag;
};

void Rva00651760::apply()
{
	m_flag = 1;
}
