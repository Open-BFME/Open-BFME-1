// ?walk@Gen0029BDE0@@QAEXPAVBfmeHelperD77@@_N@Z
// partial score=0.94 date=2026-09-04
// ?d_0029bde0@@YAXXZ
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0029BDE0: walk this+0xC (next at +0x40) up to (flag?5:1) matches
// of type 1 or 3 against the query object.

class BfmeHelperD77
{
public:
	char query(void *);
};

struct Gen0029BDE0Node
{
	void *m_unused0;
	int m_type;
	void *m_key;
	void *m_unused0C;
	void *m_payload;
	unsigned char m_pad14[0x2c];
	Gen0029BDE0Node *m_next;
};

class Gen0029BDE0
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

	void walk(BfmeHelperD77 *target, bool flag);

private:
	void *m_unused4;
	void *m_unused8;
	Gen0029BDE0Node *m_head;
};

// ?walk@Gen0029BDE0@@QAEXPAVBfmeHelperD77@@_N@Z
void Gen0029BDE0::walk(BfmeHelperD77 *target, bool flag)
{
	Gen0029BDE0Node *node = m_head;
	int remaining = flag ? 5 : 1;
	if (!remaining)
		return;
	do
	{
		if (!node)
			return;
		if (node->m_type == 1 || node->m_type == 3)
		{
			if (target->query(node->m_key))
			{
				applyPayload(node->m_payload);
				node = m_head;
				remaining--;
				continue;
			}
		}
		node = node->m_next;
	} while (remaining);
}
