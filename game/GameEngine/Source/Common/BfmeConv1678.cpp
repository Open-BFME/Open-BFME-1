class BfmeCrateERG
{
public:
	BfmeCrateERG(void);
	void bfmeAssignERG(const BfmeCrateERG &other);

	unsigned char m_bfmeVfERG[4];
	BfmeCrateERG *m_bfmeNextERG;
	char m_bfmeOverrideERG;
	char m_bfmePadERG[3];
	int m_bfmeAERG;
	int m_bfmeBERG;
	int m_bfmeCERG;
};

class BfmeCrateSystemERG
{
public:
	BfmeCrateERG *bfmeNewOverrideERG(BfmeCrateERG *crate);
};

BfmeCrateERG *BfmeCrateSystemERG::bfmeNewOverrideERG(BfmeCrateERG *crate)
{
	if (crate == 0)
		return 0;

	BfmeCrateERG *fresh = new BfmeCrateERG;
	fresh->bfmeAssignERG(*crate);
	fresh->m_bfmeAERG = crate->m_bfmeAERG;
	fresh->m_bfmeBERG = crate->m_bfmeBERG;
	fresh->m_bfmeCERG = crate->m_bfmeCERG;
	crate->m_bfmeNextERG = fresh;
	fresh->m_bfmeOverrideERG = 1;
	return fresh;
}
