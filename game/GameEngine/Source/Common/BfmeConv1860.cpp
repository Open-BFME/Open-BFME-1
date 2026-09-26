class BfmeSubYG
{
public:
	virtual void bfmeS0YG();
	virtual void bfmeS1YG();
	virtual void bfmeS2YG();
	virtual void bfmeS3YG();
	virtual void bfmeS4YG();
	virtual void bfmeS5YG();
	virtual void bfmeS6YG();
	virtual void bfmeS7YG();
	virtual int bfmeKindYG();
};

class BfmeThingYG
{
public:
	char bfmeLevelYG();
	char bfmeBusyYG();

	unsigned char m_bfmeHeadYG[0x200];
	BfmeSubYG *m_bfmeSubYG;
};

class BfmeOwnerYG
{
public:
	char bfmeCheckYG(BfmeThingYG *thing);

	unsigned char m_bfmeStartYG[8];
	BfmeThingYG *m_bfmeCurrentYG;
	char m_bfmeLevelYG;
};

char BfmeOwnerYG::bfmeCheckYG(BfmeThingYG *thing)
{
	if (m_bfmeLevelYG != 0 && m_bfmeLevelYG > thing->bfmeLevelYG())
		return 0;

	if (thing == m_bfmeCurrentYG)
		return 0;

	if (thing->bfmeBusyYG())
		return 0;

	BfmeSubYG *sub = thing->m_bfmeSubYG;

	if (sub == 0)
		return 1;

	return (char)(sub->bfmeKindYG() != 3 ? 1 : 0);
}
