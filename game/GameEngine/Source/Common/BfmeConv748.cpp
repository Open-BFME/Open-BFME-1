class BfmeOtherDPA
{
public:
	void bfmeCallDPA(void *value);
	unsigned char m_bfmeHead[8];
	char m_bfmeVal;
};

BfmeOtherDPA *bfmeGoDPA(BfmeOtherDPA *other, void *value, char *src)
{
	volatile int tmp = 0;
	other->bfmeCallDPA(value);
	other->m_bfmeVal = *src;
	return other;
}
