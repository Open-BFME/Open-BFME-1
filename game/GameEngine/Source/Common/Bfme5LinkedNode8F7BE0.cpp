// Intrusive node with a pointer to the slot that refers to it.
class Gen_008F7BE0
{
public:
	void bfmeLinkTo(Gen_008F7BE0 *head);
	void bfmeUnlink8F7C00(void);

private:
	Gen_008F7BE0 *m_head;
	int m_reserved;
	Gen_008F7BE0 **m_previousLink;
	Gen_008F7BE0 *m_next;
};

void Gen_008F7BE0::bfmeLinkTo(Gen_008F7BE0 *head)
{
	m_head = head;
	m_next = head->m_head;
	if (m_next)
		m_next->m_previousLink = &m_next;
	m_previousLink = &head->m_head;
	head->m_head = this;
}

void Gen_008F7BE0::bfmeUnlink8F7C00(void)
{
	m_head = 0;
	if (m_next)
		m_next->m_previousLink = m_previousLink;
	*m_previousLink = m_next;
}
