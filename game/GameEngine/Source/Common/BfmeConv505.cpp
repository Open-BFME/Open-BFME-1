void bfmeFreeBOG(void *what);

class BfmeThingBOG
{
public:
	void bfmeGoBOG();
	unsigned char m_bfmeHead[8];
	bool m_bfmeDone;
	unsigned char m_bfmePad[3];
	void *m_bfmeWhat;
};

void BfmeThingBOG::bfmeGoBOG()
{
	if (!m_bfmeDone)
	{
		bfmeFreeBOG(m_bfmeWhat);
		m_bfmeDone = true;
	}
}
