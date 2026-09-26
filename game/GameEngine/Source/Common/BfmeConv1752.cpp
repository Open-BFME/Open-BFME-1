class BfmeWakeBJ
{
public:
	void bfmeSetWakeBJ(void *object, int sleep);

	int m_bfmeWakeDataBJ;
};

class BfmeOwnBJ
{
public:
	void bfmeSleepBJ(int first, int second, int third, int fourth, int fifth);

	unsigned char m_bfmeHeadBJ[0x1c];
	char m_bfmeDoneBJ;
	char m_bfmeArmedBJ;
};

void BfmeOwnBJ::bfmeSleepBJ(int first, int second, int third, int fourth, int fifth)
{
	if (m_bfmeDoneBJ)
		return;

	if (m_bfmeArmedBJ)
		return;

	void *object = *(void **)((char *)this - 0x18);

	m_bfmeArmedBJ = 1;

	((BfmeWakeBJ *)((char *)this - 0x20))->bfmeSetWakeBJ(object, 1);
}
