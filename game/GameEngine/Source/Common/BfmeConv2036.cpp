extern const float g_rva01075350;

class BfmeKeyEM
{
public:
	unsigned char m_bfmeHeadEM[4];
	float m_bfmeAEM;
	float m_bfmeBEM;
	float m_bfmeCEM;
};

class BfmeHostEM
{
public:
	char bfmeSmoothEM() const;

	volatile int m_bfmeFirstEM;
	int m_bfmeLastEM;
	BfmeKeyEM *volatile m_bfmeBeginEM;
	BfmeKeyEM *volatile m_bfmeEndEM;
};

char BfmeHostEM::bfmeSmoothEM() const
{
	if (m_bfmeBeginEM == m_bfmeEndEM)
		return 1;

	int first = m_bfmeFirstEM;
	BfmeKeyEM *p = m_bfmeBeginEM;
	BfmeKeyEM *last = m_bfmeEndEM - 1;

	if (first == 1 && p->m_bfmeBEM != g_rva01075350)
		return 0;

	if (m_bfmeLastEM == 1 && last->m_bfmeCEM != g_rva01075350)
		return 0;

	if (p != last)
	{
		BfmeKeyEM *q = p + 1;

		do
		{
			if (p->m_bfmeAEM != q->m_bfmeAEM)
				return 0;

			if (p->m_bfmeCEM != g_rva01075350)
				return 0;

			if (q->m_bfmeBEM != g_rva01075350)
				return 0;

			++p;
			++q;
		}
		while (p != last);
	}

	return 1;
}
