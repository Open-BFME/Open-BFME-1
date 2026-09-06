class BfmePrimaryFA
{
public:
	virtual void bfmeInvokeFA(int value, int a, int b, void *target, int c);
};

class BfmeStateFA
{
public:
	unsigned char m_bfmeHeadFA[0x1a4];
	int m_bfmeBusyFA;
};

class BfmeHolderFA
{
public:
	unsigned char m_bfmeHeadFA[8];
	int m_bfmeValueFA;
};

class BfmeSecondFA
{
public:
	void bfmeGoFA(void *target);

	unsigned char m_bfmeHeadFA[8];
	int m_bfmeLimitFA;
};

void BfmeSecondFA::bfmeGoFA(void *target)
{
	if (m_bfmeLimitFA > 0)
		return;

	char *base = (char *)this;

	if ((*(BfmeStateFA **)(base - 0x1c))->m_bfmeBusyFA != 0)
		return;

	BfmeHolderFA *holder = *(BfmeHolderFA **)(base - 0x20);
	((BfmePrimaryFA *)(base - 4))->bfmeInvokeFA(holder->m_bfmeValueFA, 0, 0, target, 0);
}
