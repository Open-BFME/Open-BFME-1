class BfmeVecNH
{
public:
	BfmeVecNH(const BfmeVecNH &other) throw()
	{
		m_bfmeXNH = other.m_bfmeXNH;
		m_bfmeYNH = other.m_bfmeYNH;
		m_bfmeZNH = other.m_bfmeZNH;
	}
	~BfmeVecNH() throw() {}

	int m_bfmeXNH;
	int m_bfmeYNH;
	int m_bfmeZNH;
};

class BfmeOwnNH
{
public:
	virtual void bfmeSlot00NH(void);
	virtual void bfmeSlot01NH(void);
	virtual void bfmeSlot02NH(void);
	virtual void bfmeSlot03NH(void);
	virtual void bfmeSlot04NH(void);
	virtual void bfmeSlot05NH(void);
	virtual void bfmeSlot06NH(void);
	virtual void bfmeTakeNH(BfmeVecNH value);

	void bfmeSetNH(const BfmeVecNH &value);

	unsigned char m_bfmeHeadNH[0x4c];
	BfmeVecNH m_bfmeVecNH;
};

void BfmeOwnNH::bfmeSetNH(const BfmeVecNH &value)
{
	m_bfmeVecNH = value;
	bfmeTakeNH(m_bfmeVecNH);
}
