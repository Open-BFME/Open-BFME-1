class BfmeStrERE
{
public:
	~BfmeStrERE() { releaseBuffer(); }

	void *m_bfmeDataERE;

private:
	void releaseBuffer();
};

class BfmeSubERE
{
public:
	~BfmeSubERE();

	unsigned char m_bfmeBodyERE[12];
};

struct BfmeItemERE
{
	BfmeStrERE m_bfmeNameERE;
	BfmeSubERE m_bfmeSubERE;
};

class BfmeVecERE
{
public:
	void bfmeResizeERE(unsigned int count, BfmeItemERE value);
	void bfmeEraseERE(BfmeItemERE *first, BfmeItemERE *last);
	void bfmeInsertERE(BfmeItemERE *where, unsigned int count, BfmeItemERE *value);

	BfmeItemERE *m_bfmeFirstERE;
	BfmeItemERE *m_bfmeLastERE;
};

void BfmeVecERE::bfmeResizeERE(unsigned int count, BfmeItemERE value)
{
	if (count < (unsigned int)(m_bfmeLastERE - m_bfmeFirstERE))
		bfmeEraseERE(m_bfmeFirstERE + count, m_bfmeLastERE);
	else
	{
		unsigned int extra =
			count - (unsigned int)(m_bfmeLastERE - m_bfmeFirstERE);

		bfmeInsertERE(m_bfmeLastERE, extra, &value);
	}
}
