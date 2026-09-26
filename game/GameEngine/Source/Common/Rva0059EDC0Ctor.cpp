// cl: /O2 /Ob0

class BfmeAttackNuggetBase
{
public:
	BfmeAttackNuggetBase();
	virtual void handle();
};

class Rva0059EDC0 : public BfmeAttackNuggetBase
{
	int m_04;
	char m_08;
	char m_09;
	int m_0C;

public:
	Rva0059EDC0();
};

Rva0059EDC0::Rva0059EDC0()
{
	m_04 = 2;
	m_0C = 0;
	m_09 = 1;
}
