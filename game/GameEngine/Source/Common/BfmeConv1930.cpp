class BfmeItemCV
{
public:
	BfmeItemCV(void *src);

	unsigned char m_bfmePadCV[0xc];
};

class BfmeNodeCV
{
public:
	BfmeNodeCV *bfmeCopyCV(const BfmeNodeCV &src);

	BfmeItemCV *m_bfmeItemCV;
	int m_bfmeBCV;
	int m_bfmeCCV;
};

BfmeNodeCV *BfmeNodeCV::bfmeCopyCV(const BfmeNodeCV &src)
{
	BfmeItemCV *p;

	if (src.m_bfmeItemCV != 0)
		p = new BfmeItemCV(src.m_bfmeItemCV);
	else
		p = 0;

	m_bfmeItemCV = p;
	m_bfmeBCV = src.m_bfmeBCV;
	m_bfmeCCV = src.m_bfmeCCV;

	return this;
}
