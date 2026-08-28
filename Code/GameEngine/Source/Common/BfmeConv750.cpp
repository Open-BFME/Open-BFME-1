class BfmeOtherDPC
{
public:
	void bfmeCallDPC(void *value);
	unsigned char m_bfmeHead[8];
	int m_bfmeVal;
};

BfmeOtherDPC *bfmeGoDPC(BfmeOtherDPC *other, void *value, int *src)
{
	volatile int tmp = 0;
	other->bfmeCallDPC(value);
	other->m_bfmeVal = *src;
	return other;
}
