// Open-BFME5: the 64-byte timed-operation pump at 0x0007B990.
//
// Retail keeps the list head in a global, calls the head node's update method,
// and, when bit 1 requests removal, advances the global and deletes that node
// through its virtual deleting destructor. An empty list clears bit 2 before
// the returned flags are reduced to bits 0 and 2.

class BfmeTimedOpNode
{
public:
	virtual ~BfmeTimedOpNode(void);
	unsigned int update(void);                         // retail 0x0007B8E0
	BfmeTimedOpNode *m_next;                           // +0x04
};

extern BfmeTimedOpNode *g_bfmeTimedOpHead;           // retail 0x012ED584

// ?_bfme_updateTimedOps@@YAIXZ
unsigned int _bfme_updateTimedOps(void)
{
	unsigned int flags = 0;

	if (g_bfmeTimedOpHead != 0)
	{
		flags = g_bfmeTimedOpHead->update();

		if (flags & 2)
		{
			BfmeTimedOpNode *head = g_bfmeTimedOpHead;
			g_bfmeTimedOpHead = head->m_next;
			delete head;

			if (g_bfmeTimedOpHead == 0)
				flags &= 4;
		}
	}

	return flags & 5;
}
