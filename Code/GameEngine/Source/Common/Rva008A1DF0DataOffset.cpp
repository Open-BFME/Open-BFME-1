// Retail 0x008A1DF0 is the first callback registered at 0x008949CB beside
// 0x008A1E80 for the state object constructed by 0x008A2CF0. The callback
// registration proves the state layout, but retail exposes no method name.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva008BD1B0Node
{
	Rva008BD1B0Node *m_next;
	char m_pad[0x54];
	Rva008BD1B0Node *m_link;

	int count() const;
};

struct Rva008A1DF0Entry
{
	void *m_value;
	char m_pad[0x10];
	int m_size;
	char m_tail[8];
};

struct Rva008A1DF0State
{
	char m_pad00[4];
	unsigned int m_begin;
	unsigned int m_end;
	char m_pad0c[4];
	unsigned int m_offset;
	char m_pad14[0x804];
	char *m_buffer;
	char m_pad81c[0xa10];
	Rva008BD1B0Node *m_chain;
	Rva008A1DF0Entry *m_entries;
	int m_remaining;
	char m_pad1238[0x6c];
	int m_entryCount;
	char m_pad12a8[8];
	int m_wrapCount;
};

// ?Rva008A1DF0@@YAPAXPAURva008A1DF0State@@H@Z
void *Rva008A1DF0(Rva008A1DF0State *state, int unused)
{
	int difference = state->m_begin;
	difference = state->m_end - difference;
	int index = (difference / 20);
	int adjustedIndex;
	if (index >= 0)
		adjustedIndex = index;
	else
		adjustedIndex = state->m_wrapCount + index;

	char *result = state->m_buffer + state->m_offset + adjustedIndex * 2 + 0x482;
	int chainCount = state->m_chain->count();
	result += chainCount;

	int entryCount = state->m_entryCount;
	int remaining = state->m_remaining;
	int i = 0;
	if (entryCount > 0)
	{
		Rva008A1DF0Entry *entry = state->m_entries;
		do
		{
			if (entry->m_value != 0)
			{
				--remaining;
				result += entry->m_size + 1;
				if (remaining == 0)
					break;
			}
			++i;
			++entry;
		} while (i < entryCount);
		return result;
	}
	_ReadWriteBarrier();
	return result;
}
