class BfmeThingBEH
{
public:
	void bfmeStopBEH();
	void bfmeGoBEH();
	bool m_bfmeFlag;
};

void BfmeThingBEH::bfmeGoBEH()
{
	if (m_bfmeFlag)
	{
		bfmeStopBEH();
		m_bfmeFlag = false;
	}
}
