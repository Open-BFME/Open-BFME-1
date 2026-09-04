// cl: /DNDEBUG /MD /EHsc

struct BfmeNodeA7F0
{
	BfmeNodeA7F0 *m_next;
	char m_pad[4];
	void *m_payload;
};

class Gen_0022A7F0
{
public:
	void *bfmeFirst();

private:
	char m_pad[0x18];
	BfmeNodeA7F0 * volatile m_head;
	unsigned int m_limit;
};

// ?bfmeFirst@Gen_0022A7F0@@QAEPAXXZ
void *Gen_0022A7F0::bfmeFirst()
{
	if (m_limit <= 0)
		return 0;

	int count = 0;
	BfmeNodeA7F0 *head = m_head;
	BfmeNodeA7F0 *node = head->m_next;

	while (node != head) {
		node = node->m_next;
		++count;
	}

	if (count == 0)
		return 0;

	return m_head->m_next->m_payload;
}
