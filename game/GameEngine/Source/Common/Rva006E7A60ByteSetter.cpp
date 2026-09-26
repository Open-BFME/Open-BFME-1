// Retail at 0x006E7A60 writes 1 to the byte at this+0x20 and returns.
// The owning type and field semantics were not recovered.
class Rva006E7A60
{
public:
	void apply();
	char m_lead[0x20];
	char m_flag;
};

void Rva006E7A60::apply()
{
	m_flag = 1;
}
