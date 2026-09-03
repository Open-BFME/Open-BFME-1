// ??1Rva008B2DF0TailBase@@QAE@XZ
// partial score=0.75 date=2026-09-02
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
	~Q4Base00D35D68() {}
};

class Rva008B2DF0TailBase : public Q4Base00D35D68
{
public:
	virtual void v3();
	virtual void v4();
	virtual void v5();
	~Rva008B2DF0TailBase();
	char m_gap0[8 - 4];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[0x18 - 9];
	int m_flag;
	char m_gap2[0x20 - 0x1C];
	int m_20;
	int m_24;
};

Rva008B2DF0TailBase::~Rva008B2DF0TailBase()
{
	m_20 = 0;
	m_24 = 0;
	notify(0, 0);
	m_flag = 0;
}
