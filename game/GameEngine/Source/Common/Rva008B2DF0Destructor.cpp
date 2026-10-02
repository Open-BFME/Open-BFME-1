// RVA 0x008B2DF0, 97-byte destructor.
// Evidence: targets/game/reverse/identity_evidence/rva008b2df0.md
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

class Rva008B2DF0Middle : public Q4Base00D35D68
{
public:
    virtual void v3();
    virtual void v4();
    virtual void v5();
    __forceinline ~Rva008B2DF0Middle()
    {
        notify(0, 0);
        m_flag = 0;
    }
    char m_gap0[8 - 4];
    Q4Sub00C9CC70 m_sub;
    char m_gap1[0x18 - 9];
    int m_flag;
};

// Retail clears its two words before entering the common vptr-setting cleanup.
// The outer novtable layer is an address-derived ABI view of that ordering.
class __declspec(novtable) Rva008B2DF0TailBase : public Rva008B2DF0Middle
{
public:
    virtual ~Rva008B2DF0TailBase();
    char m_gap2[0x20 - 0x1c];
    int m_20;
    int m_24;
};

Rva008B2DF0TailBase::~Rva008B2DF0TailBase()
{
    m_20 = 0;
    m_24 = 0;
}
