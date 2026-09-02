void *bfmeAlloc1134(unsigned int bytes);

class BfmeBase1134
{
public:
	BfmeBase1134(void);
	virtual ~BfmeBase1134(void);

private:
	int m_bfme04;
};

struct BfmeBuffer1134
{
	BfmeBuffer1134(unsigned int bytes)
	{
		m_bfmeData = 0;
		m_bfmeData = (char *)bfmeAlloc1134(bytes);
		m_bfmeLength = 0;
		m_bfmeData[0] = 0;
		*(int *)(m_bfmeData + 4) = 0;
		*(char **)(m_bfmeData + 8) = m_bfmeData;
		*(char **)(m_bfmeData + 12) = m_bfmeData;
	}
	~BfmeBuffer1134(void);

	char *m_bfmeData;
	int m_bfmeLength;
};

class Gen_00587D40 : public BfmeBase1134
{
public:
	Gen_00587D40(void);
	virtual ~Gen_00587D40(void);

private:
	int m_bfme08;
	char m_bfme0C;
	char m_bfme0D;
	char m_bfme0E[10];
	BfmeBuffer1134 m_bfmeFirst;
	int m_bfme20;
	BfmeBuffer1134 m_bfmeSecond;
};

// ??0Gen_00587D40@@QAE@XZ
Gen_00587D40::Gen_00587D40(void) :
	m_bfme08(0),
	m_bfme0C(0),
	m_bfme0D(0),
	m_bfmeFirst(0x18),
	m_bfmeSecond(0x50)
{
}
