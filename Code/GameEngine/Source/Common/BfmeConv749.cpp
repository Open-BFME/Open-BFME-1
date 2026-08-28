class BfmeOtherDPB
{
public:
	void bfmeCallDPB(void *value);
	unsigned char m_bfmeHead[4];
	char m_bfmeVal;
};

BfmeOtherDPB *bfmeGoDPB(BfmeOtherDPB *other, void *value, char *src)
{
	volatile int tmp = 0;
	other->bfmeCallDPB(value);
	other->m_bfmeVal = *src;
	return other;
}
