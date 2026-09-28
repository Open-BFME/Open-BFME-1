// ?Rva009F4ED0@Rva009F40E0Owner@@QAEXXZ
// partial score=0.67 date=2026-09-28
// Neutral raw-ABI reconstruction for retail RVA 0x009F40E0 (72 bytes).
// The retail boundary is a thiscall with two stack arguments: a pointer to a
// pointer-sized slot and an unsigned count.  No named caller survives in the
// current reverse inventory, so the address-derived owner is intentional.

struct Rva009F4ED0Vector
{
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

struct Rva009F4ED0ListNode
{
	unsigned char m_pad00[0x0c];
	Rva009F4ED0ListNode *m_next;
	void **m_slot;
};

class Rva009F40E0Owner
{
public:
	void run(void **slot, unsigned int count);
	void Rva009F4ED0();

private:
	unsigned char m_pad00[0x18];
	Rva009F4ED0Vector m_vectors[17];
	Rva009F4ED0ListNode *m_list;
};


void Rva009F40E0Owner::run(void **slot, unsigned int count)
{
	if (*slot == 0)
		return;

	*slot = 0;
	unsigned int childCount = count;
	slot += 2;
	childCount >>= 2;
	unsigned int stride = count * 8;
	unsigned int remaining = 4;
	while (remaining != 0)
	{
		run(slot, childCount);
		slot = (void **)((char *)slot + stride);
		--remaining;
	}
}

void Rva009F40E0Owner::Rva009F4ED0()
{
	Rva009F4ED0ListNode *node = m_list;
	while (node != 0)
	{
		*node->m_slot = 0;
		node->m_slot = 0;
		node = node->m_next;
	}

	int byteCount = static_cast<char *>(m_vectors[0].m_end)
		- static_cast<char *>(m_vectors[0].m_begin);
	if ((byteCount & 0xfffffff8) != 0)
	{
		Rva009F4ED0Vector *vector = m_vectors;
		int remainingVectors = 0x11;
		do
		{
			void **slot = static_cast<void **>(vector->m_begin);
			int count = (static_cast<char *>(m_vectors[0].m_end)
				- static_cast<char *>(m_vectors[0].m_begin)) >> 3;
			if (*slot != 0)
			{
				*slot = 0;
				slot += 2;
				int remaining = 4;
				do
				{
					run(slot, count >> 4);
					slot += (count >> 2) * 2;
					--remaining;
				} while (remaining != 0);
			}
			++vector;
			--remainingVectors;
		} while (remainingVectors != 0);
	}
}
