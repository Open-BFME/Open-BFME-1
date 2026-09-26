class BfmeLexEAO
{
public:
	char bfmeSkipCommentEAO();

	char *m_bfmePosEAO;
};

char BfmeLexEAO::bfmeSkipCommentEAO()
{
	char *p = m_bfmePosEAO + 2;

	m_bfmePosEAO = p;

	if (*p != 0x2d)
		return 0;

	p++;
	m_bfmePosEAO = p;

	if (*p != 0x2d)
		return 0;

	p++;
	m_bfmePosEAO = p;

	if (*p == 0)
		return 0;

	for (;;)
	{
		char *q = m_bfmePosEAO;
		char c = *q;

		while (c != 0 && c != 0x2d)
		{
			c = q[1];
			q++;
		}

		m_bfmePosEAO = q;

		if (*q == 0)
			return 0;

		q++;
		m_bfmePosEAO = q;

		c = *q;

		if (c == 0)
			return 0;

		if (c == 0x2d)
		{
			q++;
			m_bfmePosEAO = q;

			c = *q;

			if (c == 0)
				return 0;

			if (c == 0x3e)
			{
				q++;
				m_bfmePosEAO = q;

				return 1;
			}
		}
	}
}
