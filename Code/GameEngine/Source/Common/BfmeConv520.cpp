class BfmeThingBRF
{
public:
	void bfmeStepBRF();
	void bfmeGoBRF();
	bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	void *m_bfmeWhat;
};

void BfmeThingBRF::bfmeGoBRF()
{
	void *saved = m_bfmeWhat;
	m_bfmeWhat = 0;
	m_bfmeFlag = false;
	bfmeStepBRF();
	m_bfmeWhat = saved;
	m_bfmeFlag = true;
}
