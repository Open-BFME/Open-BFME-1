// ??0BfmeChainRecord@@QAE@PAX0PAPAV0@@Z
// partial score=0.84 date=2026-09-02
// cl: /O2 /Ob0

class BfmeChainRecord
{
	void *volatile m_first;
	void *volatile m_second;
	BfmeChainRecord **m_ownerLink;
	BfmeChainRecord *m_next;
	void *m_value10;
	void *m_value14;
	void *m_value18;

public:
	BfmeChainRecord(void *first, void *second, BfmeChainRecord **ownerLink);
};

BfmeChainRecord::BfmeChainRecord(void *first, void *second, BfmeChainRecord **ownerLink)
{
	void *firstValue = first;
	void *secondValue = second;
	m_second = secondValue;
	m_first = firstValue;
	m_value10 = 0;
	m_value18 = 0;
	m_ownerLink = ownerLink;
	m_next = *ownerLink;
	if (m_next)
		m_next->m_ownerLink = &m_next;
	*ownerLink = this;
}
