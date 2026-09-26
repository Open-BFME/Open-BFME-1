class BfmeLinkQF
{
public:
	unsigned char m_bfmeHeadQF[8];
	BfmeLinkQF *m_bfmeOtherQF;
	unsigned char m_bfmeGapQF[0x14];
	int m_bfmeKeyQF;
};

class BfmeOwnerQF
{
public:
	char bfmeLinkedQF(void);

	int m_bfmeSpareQF;
	BfmeLinkQF *m_bfmeFirstQF;
	unsigned char m_bfmeGapQF[8];
	BfmeLinkQF *m_bfmeSecondQF;
};

char BfmeOwnerQF::bfmeLinkedQF(void)
{
	BfmeLinkQF *a = m_bfmeFirstQF;

	if (!a)
		return 0;

	BfmeLinkQF *b = m_bfmeSecondQF;

	if (!b)
		return 0;

	unsigned int count = 0;

	while (a)
	{
		if (count++ >= 100)
			return 0;

		if (a->m_bfmeKeyQF != 0x7fffffff)
		{
			BfmeLinkQF *other = b->m_bfmeOtherQF;

			if (other == a)
				return 1;

			if (a->m_bfmeOtherQF == b)
				return 1;

			if (other && other->m_bfmeOtherQF == a)
				return 1;

			if (a == b)
				return 1;
		}

		a = a->m_bfmeOtherQF;
	}

	return 0;
}
