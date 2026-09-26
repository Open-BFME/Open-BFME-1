// cl: /O2 /Ob0

class BfmeAttackNuggetBase
{
public:
	BfmeAttackNuggetBase();
	virtual void handle();
};

class Rva0059F5C0 : public BfmeAttackNuggetBase
{
	int m_04;
	char m_08;
	char m_09;
	int m_0C;
	char m_gap[0x10];
	int m_20;

public:
	Rva0059F5C0();
};

Rva0059F5C0::Rva0059F5C0()
{
	m_04 = 6;
	m_0C = 0;
	m_20 = -1;
	m_09 = 1;
}
