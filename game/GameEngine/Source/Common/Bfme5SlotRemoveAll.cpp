// A slot remove-all.
//
// It sweeps an array of twelve-byte slots, and in every slot whose key matches
// it walks the chain and unlinks and frees each node holding the value it was
// given.
//
// Two details of the shape. The value comparison puts the parameter on the
// left -- "value == node->value", not the other way round -- which is the
// difference between cmp with the register first and cmp with the memory
// operand first, one byte. And with four callee-saved registers already spent,
// this itself is spilled to a stack slot in the prologue and reloaded at the
// bottom of the outer loop to re-read the end pointer.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeSlotNode
{
	BfmeSlotNode *m_bfmeNext;				// +0x00
	BfmeSlotNode *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

struct BfmeSlot
{
	int m_bfmeKey;						// +0x00
	int m_bfmeGap;						// +0x04
	BfmeSlotNode *m_bfmeList;				// +0x08
};

class Gen_002E0990
{
public:
	void bfmeRemoveAll(void *value, int key);

private:
	int m_bfmeHead;						// +0x00
	BfmeSlot *m_bfmeStart;					// +0x04
	BfmeSlot *m_bfmeEnd;					// +0x08
};

// ?bfmeRemoveAll@Gen_002E0990@@QAEXPAXH@Z
void Gen_002E0990::bfmeRemoveAll(void *value, int key)
{
	BfmeSlot *slot = m_bfmeStart;

	while (slot != m_bfmeEnd)
	{
		if (slot->m_bfmeKey == key)
		{
			BfmeSlotNode *head = slot->m_bfmeList;
			BfmeSlotNode *node = head->m_bfmeNext;

			while (node != head)
			{
				BfmeSlotNode *next = node->m_bfmeNext;

				if (value == node->m_bfmeValue)
				{
					BfmeSlotNode *previous = node->m_bfmePrev;

					previous->m_bfmeNext = next;
					next->m_bfmePrev = previous;

					bfmeDeallocate(node, sizeof(BfmeSlotNode));
				}

				node = next;
			}
		}

		slot = slot + 1;
	}
}
