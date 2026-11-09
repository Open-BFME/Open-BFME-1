class BfmeLexEAO
{
public:
	char skipComment();

	char *m_pos;
};

char BfmeLexEAO::skipComment()
{
	char *p = m_pos + 2;

	m_pos = p;

	if (*p != 0x2d)
		return 0;

	p++;
	m_pos = p;

	if (*p != 0x2d)
		return 0;

	p++;
	m_pos = p;

	if (*p == 0)
		return 0;

	for (;;)
	{
		char *q = m_pos;
		char c = *q;

		while (c != 0 && c != 0x2d)
		{
			c = q[1];
			q++;
		}

		m_pos = q;

		if (*q == 0)
			return 0;

		q++;
		m_pos = q;

		c = *q;

		if (c == 0)
			return 0;

		if (c == 0x2d)
		{
			q++;
			m_pos = q;

			c = *q;

			if (c == 0)
				return 0;

			if (c == 0x3e)
			{
				q++;
				m_pos = q;

				return 1;
			}
		}
	}
}
