// cl: /EHsc

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void notify(int a, int b);
	~Q4Base00D35D68() { }
};

class Gen_uwm_00899380 : public Q4Base00D35D68
{
public:
	virtual void v3();
	virtual void v4();
	virtual void v5();
	~Gen_uwm_00899380();

	char m_gap0[8 - 4];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[0x18 - 9];
	int m_flag;
};

Gen_uwm_00899380::~Gen_uwm_00899380()
{
	notify(0, 0);
	m_flag = 0;
}
