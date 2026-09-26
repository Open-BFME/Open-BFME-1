// ??0BfmeOwnCC@@QAE@PAX@Z
// cl: /DNDEBUG /MD /EHsc
class Rva000FB260Guard
{
public:
	Rva000FB260Guard(void)
	{
		m_value = 0;
	}
	~Rva000FB260Guard();

	int m_value;
};

class BfmeSubCC
{
public:
	BfmeSubCC(void)
		: m_bfmeACC(0), m_bfmeBCC(0)
	{
	}

	void bfmeInitCC(int first, int second);

	int m_bfmeACC;
	int m_bfmeBCC;
	Rva000FB260Guard m_guard;
};

class BfmeOwnCC
{
public:
	BfmeOwnCC(void *value);
	virtual void bfmePureCC(void) = 0;

	BfmeSubCC m_bfmeSubCC;
	void *m_bfmeValueCC;
};

BfmeOwnCC::BfmeOwnCC(void *value)
{
	m_bfmeValueCC = value;

	BfmeSubCC *sub = &m_bfmeSubCC;

	sub->bfmeInitCC(sub->m_bfmeACC, sub->m_bfmeBCC);
}
