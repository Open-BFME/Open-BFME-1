extern void j_00025eff();

class BfmeThingBFH
{
public:
	void bfmeGoBFH(void *what);
	unsigned char m_bfmeHead[0x4c5];
	bool m_bfmeFlag;
};

void BfmeThingBFH::bfmeGoBFH(void *what)
{
	((void (__fastcall *)(BfmeThingBFH *))j_00025eff)(this);
	m_bfmeFlag = false;
}
