class BfmeStateSource
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void v5(void);
	virtual int bfmeState(void);
};

class Gen_002854E0
{
public:
	void bfmeTransition(int expected, int unused1, int unused2,
		unsigned int flags, int unused3);

private:
	char m_bfmeFields[8];
	int m_bfmeResult;
	char m_bfme0C[0x0C];
	BfmeStateSource *m_bfmeSource;
};

// ?bfmeTransition@Gen_002854E0@@QAEXHHHIH@Z
void Gen_002854E0::bfmeTransition(
	int expected,
	int,
	int,
	unsigned int flags,
	int)
{
	if (m_bfmeSource->bfmeState() == expected)
	{
		if ((flags & 0x2000) != 0)
			m_bfmeResult = 1;
		else if ((flags & 0x4000) != 0)
			m_bfmeResult = 2;
		else if ((flags & 0x8000) != 0)
			m_bfmeResult = 3;
	}
}
