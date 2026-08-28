class BfmeThingBFH
{
public:
	void bfmeStepBFH();
	void bfmeGoBFH(void *what);
	unsigned char m_bfmeHead[0x4c5];
	bool m_bfmeFlag;
};

void BfmeThingBFH::bfmeGoBFH(void *what)
{
	bfmeStepBFH();
	m_bfmeFlag = false;
}
