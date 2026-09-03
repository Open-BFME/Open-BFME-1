// ?bfmeFirst@Gen_0022A7F0@@QAEPAXXZ
// partial score=0.85 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022A7F0. First-node payload getter, 47 bytes, no calls:
// when the limit at this+0x1C is nonzero, walk the circular node list at
// this+0x18 counting until back at the head; a zero count answers null,
// otherwise answer the +8 payload of the first node.

struct BfmeNodeA7F0
{
	BfmeNodeA7F0 *m_next;			// +0x00
	char m_pad[4];				// +0x04
	void *m_payload;				// +0x08
};

class Gen_0022A7F0
{
public:
	void *bfmeFirst();

private:
	char m_pad[0x18];
	BfmeNodeA7F0 *m_head;			// +0x18
	unsigned int m_limit;			// +0x1C
};

// ?bfmeFirst@Gen_0022A7F0@@QAEPAXXZ
void *Gen_0022A7F0::bfmeFirst()
{
	if (m_limit <= 0)
		return 0;

	BfmeNodeA7F0 *head = m_head;
	int count = 0;
	BfmeNodeA7F0 *n = head->m_next;

	while (n != head) {
		n = n->m_next;
		++count;
	}

	if (count == 0)
		return 0;

	return head->m_next->m_payload;
}
