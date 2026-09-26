// cl: /O2 /Ob0

class Rva0073C620
{
	char m_lead[0x23BC];
	int m_value;

public:
	int is(int a) const;
};

int Rva0073C620::is(int a) const
{
	return m_value == a;
}
