// cl: /O2 /Ob0

struct Rva0089E1E0Inner
{
	char m_lead[4];
	unsigned short m_value;
};

class Rva0089E1E0
{
	Rva0089E1E0Inner *m_inner;

public:
	unsigned char cmp(int value);
};

unsigned char Rva0089E1E0::cmp(int value)
{
	return (unsigned)value < m_inner->m_value;
}
