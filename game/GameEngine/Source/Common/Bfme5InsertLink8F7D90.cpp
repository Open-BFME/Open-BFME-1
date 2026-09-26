// Link an item ahead of the current head, retaining the back-link address.
struct BfmeLink8F7D90
{
	BfmeLink8F7D90 *m_first;
	int m_reserved;
	BfmeLink8F7D90 **m_previousLink;
	BfmeLink8F7D90 *m_next;
};

class Gen_008F7D90
{
public:
	bool bfmeInsert(BfmeLink8F7D90 *item, BfmeLink8F7D90 *head);
};

bool Gen_008F7D90::bfmeInsert(BfmeLink8F7D90 *item, BfmeLink8F7D90 *head)
{
	item->m_first = head;
	item->m_next = head->m_first;
	if (item->m_next)
		item->m_next->m_previousLink = &item->m_next;
	item->m_previousLink = &head->m_first;
	head->m_first = item;
	return true;
}
