class BfmeThingCDA
{
public:
	void bfmeStepCDA();
	void bfmeGoCDA(void *what);
	bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	void *m_bfmeVal;
};

void BfmeThingCDA::bfmeGoCDA(void *what)
{
	if (what != m_bfmeVal || !m_bfmeFlag)
	{
		bfmeStepCDA();
		m_bfmeVal = what;
		m_bfmeFlag = true;
	}
}
