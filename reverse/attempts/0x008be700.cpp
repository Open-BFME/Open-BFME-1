// ?d_008be700@@YAXXZ
// partial score=0.96 date=2026-08-30
extern char g_bfmeDerived1283Vtable;

class Gen_008BE660
{
public:
	Gen_008BE660();

private:
	void *m_value;
};

class BfmeBase1283
{
public:
	BfmeBase1283();
	~BfmeBase1283();

protected:
	void *m_vtable;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	unsigned char m_bfme14;
	char m_padding15[3];
	int m_bfme18;
	int m_bfme1c;
};

inline BfmeBase1283::BfmeBase1283()
{
	m_bfme04 = -1;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_vtable = &g_bfmeDerived1283Vtable;
	m_bfme18 = 0;
	m_bfme1c = 0;
}

class BfmeDerived1283 : public BfmeBase1283
{
public:
	BfmeDerived1283();

private:
	Gen_008BE660 m_owned;
};

BfmeDerived1283::BfmeDerived1283()
{
}
