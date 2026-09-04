// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail 0x008BDD10. Walk a filtered node list and activate
// nodes of the three accepted types when their state bit is set.

class BfmeNode1236
{
public:
	void bfmeActivate1236();

	void *m_vtable;
	unsigned int m_flags;
	char m_padding[0x50];
	BfmeNode1236 *m_next;
};

struct BfmeList1236
{
	BfmeNode1236 *m_head;
};

class BfmeFilterWalk1236
{
public:
	void bfmeFilterWalk1236();

private:
	BfmeList1236 *m_list;
};

void BfmeFilterWalk1236::bfmeFilterWalk1236()
{
	BfmeNode1236 *node = m_list->m_head->m_next;
	while (node) {
		unsigned int flags = node->m_flags;
		unsigned int type = flags & 0x3f;
		if (type == 0x0d && !((unsigned char)(~(flags >> 15)) & 1))
			goto activate;
		type = flags & 0x3f;
		if (type == 0x12 && !((unsigned char)(~(flags >> 15)) & 1))
			goto activate;
		type = flags & 0x3f;
		if (type == 0x0e && !((unsigned char)(~(flags >> 15)) & 1)) {
		activate:
			node->bfmeActivate1236();
		}
		node = node->m_next;
	}
}
