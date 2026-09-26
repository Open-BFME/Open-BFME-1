struct BfmeNodeEQE;

struct BfmeOwnerEQE
{
	unsigned char m_bfmeHeadEQE[0x98];
	BfmeNodeEQE *m_bfmeLastEQE;
	BfmeNodeEQE *m_bfmeFirstEQE;
};

struct BfmeNodeEQE
{
	void bfmeLinkEQE(void);
	BfmeOwnerEQE *m_bfmeOwnerEQE;
	BfmeNodeEQE *m_bfmeNextEQE;
	BfmeNodeEQE *m_bfmePrevEQE;
};

void BfmeNodeEQE::bfmeLinkEQE(void)
{
	BfmeOwnerEQE *owner = m_bfmeOwnerEQE;
	BfmeNodeEQE **first = &owner->m_bfmeFirstEQE;
	m_bfmeNextEQE = *first;
	m_bfmePrevEQE = 0;
	*first = this;
	if (m_bfmeNextEQE != 0)
		m_bfmeNextEQE->m_bfmePrevEQE = this;
	else
		m_bfmeOwnerEQE->m_bfmeLastEQE = this;
}
