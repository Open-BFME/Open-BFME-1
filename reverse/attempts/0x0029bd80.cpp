// ?d_0029bd80@@YAXXZ
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0029BD80: walk a typed linked list at this+8, query the arg against
// node+8 when type is 1 or 3, then virtual slot +0x20 with node+0x10.
// Near-miss: size-exact register-mirror, this in edi instead of ebx and the
// arg in ebx instead of edi. Control flow, compares and call shape match.

class BfmeHelperD77
{
public:
	char query(void *);
};

struct Gen0029BD80Node
{
	void *m_unused0;
	int m_type;
	void *m_key;
	void *m_unused0C;
	void *m_payload;
	unsigned char m_pad14[0x28];
	Gen0029BD80Node *m_next;
};

class Gen0029BD80
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

	void find(BfmeHelperD77 *target);

private:
	void *m_unused4;
	Gen0029BD80Node *m_head;
};

// ?find@Gen0029BD80@@QAEXPAVBfmeHelperD77@@@Z
void Gen0029BD80::find(BfmeHelperD77 *target)
{
	Gen0029BD80Node *node = m_head;
	if (!node)
		return;
	do
	{
		BfmeHelperD77 *query = target;
		int type = node->m_type;
		if (type == 1 || type == 3)
		{
			if (query->query(node->m_key))
			{
				applyPayload(node->m_payload);
				return;
			}
		}
		node = node->m_next;
	} while (node);
}
