// cl: /O2 /Ob0

class Rva00696200
{
	char m_lead[0x954];
	unsigned m_limit;
	unsigned m_value;

public:
	int below() const;
};

int Rva00696200::below() const
{
	return m_value < m_limit;
}
