// ?recycleBuckets009A2A50@Rva009A2A50Table@@QAEXXZ
// Address-qualified identity: retail moves every node from each hash bucket
// to the table's spare-node chain.  The neighboring constructor and iterator
// independently establish the 0x2B7B bucket count and +0x30 next link.

struct Rva009A2A50Node
{
	unsigned char m_pad00[0x30];
	Rva009A2A50Node *m_next;
};

class Rva009A2A50Table
{
public:
	void recycleBuckets009A2A50();

private:
	Rva009A2A50Node *m_buckets[0x2B7B];
	Rva009A2A50Node *m_spare;
};

void Rva009A2A50Table::recycleBuckets009A2A50()
{
	for (unsigned int i = 0; i < 0x2B7B; ++i)
	{
		Rva009A2A50Node *node = m_buckets[i];
		while (node != 0)
		{
			Rva009A2A50Node *next = node->m_next;
			node->m_next = m_spare;
			m_spare = node;
			node = next;
		}
		m_buckets[i] = 0;
	}
}
