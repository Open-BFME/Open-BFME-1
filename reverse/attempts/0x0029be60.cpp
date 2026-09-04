// ?d_0029be60@@YAXXZ
// partial score=0.94 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

class BfmeHelperD77
{
public:
	char query(void *);
};

struct Gen0029BE60Node
{
	void *m_unused0;
	int m_type;
	void *m_key;
	void *m_unused0C;
	void *m_payload;
	unsigned char m_pad14[0x28];
	Gen0029BE60Node *m_next;
};

class Gen0029BE60
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void applyPayload(void *payload);

	void walk(BfmeHelperD77 *target);

private:
	void *m_unused4;
	Gen0029BE60Node *m_head;
};

void Gen0029BE60::walk(BfmeHelperD77 *target)
{
	Gen0029BE60Node *node = m_head;
	if (!node)
		return;
	do
	{
		if (node->m_type == 1)
		{
			if (target->query(node->m_key))
			{
				void *payload = node->m_payload;
				Gen0029BE60Node *next = node->m_next;
				applyPayload(payload);
				node = next;
				continue;
			}
		}
		node = node->m_next;
	} while (node);
}
