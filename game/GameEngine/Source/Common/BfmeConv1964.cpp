class BfmeInfoERW
{
public:
	unsigned char m_bfmeHeadERW[0x24];
	int m_bfmeValueERW;
};

class BfmeSubERW
{
public:
	BfmeInfoERW *bfmeInfoERW();
	char bfmeAERW();
	char bfmeBERW();
};

class BfmeBaseERW
{
public:
	char bfmeCheckERW(int what);
};

class BfmeHostERW
{
public:
	int bfmeQueryERW();

	unsigned char m_bfmeHeadERW[0x1d0];
	BfmeSubERW *m_bfmeSubERW;
	unsigned char m_bfmeMidERW[0x104];
	unsigned char m_bfmeFlagsERW;
};

int BfmeHostERW::bfmeQueryERW()
{
	BfmeSubERW *sub = m_bfmeSubERW;

	if (sub != 0)
	{
		BfmeInfoERW *info = sub->bfmeInfoERW();

		if (info != 0)
		{
			if ((m_bfmeFlagsERW & 2) != 0)
				return -1;

			if (!((BfmeBaseERW *)((char *)this - 0x6c))->bfmeCheckERW(0x36))
			{
				sub = m_bfmeSubERW;

				if (sub != 0 && !sub->bfmeAERW() && !sub->bfmeBERW())
					return info->m_bfmeValueERW;
			}
		}
	}

	return -1;
}
