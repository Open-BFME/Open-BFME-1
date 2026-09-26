class BfmeAskerRJ
{
public:
	bool bfmeAskRJ(void *what, void *more);
};

class BfmeThingRJ
{
public:
	bool bfmeCheckRJ(void *what);
	unsigned char m_bfmeHead[8];
	BfmeAskerRJ *m_bfmeSub;
	void *m_bfmeExtra;
	bool m_bfmeFlag;
};

bool BfmeThingRJ::bfmeCheckRJ(void *what)
{
	if (m_bfmeSub->bfmeAskRJ(what, m_bfmeExtra))
		return m_bfmeFlag;
	return !m_bfmeFlag;
}
