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
	BfmeBase1283()
	{
		m_bfme04 = -1;
		m_bfme08 = 0;
		m_bfme0c = 0;
		m_bfme10 = 0;
		m_bfme14 = 0;
	}
	virtual ~BfmeBase1283();

protected:
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	unsigned char m_bfme14;
	char m_padding15[3];
};

class BfmeDerived1283 : public BfmeBase1283
{
public:
	BfmeDerived1283();

private:
	int m_bfme18;
	int m_bfme1c;
	Gen_008BE660 m_owned;
};

BfmeDerived1283::BfmeDerived1283() : m_bfme18(0), m_bfme1c(0) {}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
