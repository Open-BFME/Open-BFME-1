class BfmeOwnAH
{
public:
	int bfmeHandleAH(void *unused, int code, unsigned char kind, int flags);
	void bfmeNotifyAH(void);

	unsigned char m_bfmeHeadAH[0x8c];
	int m_bfmeStateAH;
};

int BfmeOwnAH::bfmeHandleAH(void *unused, int code, unsigned char kind, int flags)
{
	int kindValue = kind;

	if (code != 0x15)
		return 0;

	switch (kindValue)
	{
		case 1:
			break;

		default:
			return 0;
	}

	if (flags & 1)
	{
		int state = m_bfmeStateAH;

		if (state == 0 || state == 1)
			bfmeNotifyAH();
	}

	return 1;
}
