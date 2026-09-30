// ?d_008a1e80@@YAXXZ
// partial score=0.2381 date=2026-09-30
// ?d_008a1e80@@YAXXZ
// cl: /O2 /DNDEBUG /MD /EHsc
// Partial 0x008A1E80: 485B vs retail 483B; normalized instruction shape 0.928.
// Startup registers this callback beside matched Rva008A1DF0 for the
// 0x12B4-byte object constructed by the matched BfmeThingUEW ctor. The name
// stays address-derived because registration gives no semantic method name.
// Record indexing is 0x20-byte stride, as retail's two SHL EAX,5 instructions
// and the ctor's BfmeVecEVE element size independently show.
// Remaining first divergence: retail saves EBP only at +0x16E for the final
// record scan, while MSVC currently saves EBP at +0x26 for the whole body.
class BfmeSlotLD
{
public:
	int m_words[5];
};

class Gen_008A0C90
{
public:
	BfmeSlotLD *bfmeAt(int offset) const;
private:
	BfmeSlotLD *m_bfmeBegin;
	BfmeSlotLD *m_bfmeEnd;
	int m_bfmeGap[1194];
	int m_bfmeSlots;
};

class BfmeItemGC;
BfmeItemGC *bfmeCheckGC(BfmeItemGC *item);

class Rva008BD1B0Node
{
public:
	int count() const;
};

class BfmeNodeDB;
class Gen_008BD1D0
{
public:
	BfmeNodeDB *bfmeAdvance(int count) const;
private:
	BfmeNodeDB *m_bfmeHead;
};

struct Rva008A1E80Record
{
	int m_value00;
	void *m_value04;
	int m_value08;
	int m_value0c;
	int m_value10;
	int m_count14;
	int m_value18;
BfmeItemGC **m_values1c;
};

struct Rva008A1E80Block
{
	void *m_value00;
	char m_gap04[0x18];
};

struct Rva008A1E80State
{
	int m_vptr;
	char *m_begin;
	char *m_end;
	void **m_values0c;
	int m_count10;
	int m_value14;
	void *m_inline18[0x200];
	int m_count818;
	Rva008A1E80Block *m_value81c;
	char m_gap820[4];
	BfmeItemGC *m_values824[0x40];
	char m_gap924[4];
	BfmeItemGC *m_values928[0x40];
	char m_gapA28[4];
	void *m_valuesA2C[0x200];
	void *m_node122C;
	Rva008A1E80Record *m_records1230;
	int m_count1234;
	char m_gap1238[0x34];
	void *m_value126C;
	char m_gap1270[0x2c];
	void *m_value129C;
	int m_count12A0;
	int m_count12A4;
	char m_gap12A8[8];
	int m_count12B0;
};

int __cdecl Rva008A1E80(Rva008A1E80State *state, int offset)
{
	if (offset == 0)
		return reinterpret_cast<int>(state->m_value126C);
	if (offset == 1)
		return reinterpret_cast<int>(state->m_value129C);

	int index = offset;
	index -= 2;
	int difference = reinterpret_cast<int>(state->m_begin);
	difference = reinterpret_cast<int>(state->m_end) - difference;
	int count = difference / 20;
	int wrapped;
	if (count >= 0)
		wrapped = count;
	else
		wrapped = state->m_count12B0 + count;
	if (index < wrapped * 2)
	{
		BfmeSlotLD *slot = ((Gen_008A0C90 *)state)->bfmeAt(index / 2);
		if (slot->m_words[0] == 0)
		{
			if ((index & 1) != 0)
				return slot->m_words[4];
			return 0;
		}
		if (slot->m_words[0] == 1)
		{
			if ((index & 1) != 0)
				return slot->m_words[2];
			return reinterpret_cast<int>(bfmeCheckGC((BfmeItemGC *)slot->m_words[3]));
		}
	}
	int wrappedCount;
	if (count >= 0)
		wrappedCount = count;
	else
		wrappedCount = state->m_count12B0 + count;
	index = index - wrappedCount * 2;
	if (index < state->m_count10)
		return reinterpret_cast<int>(state->m_values0c[index]);
	index -= state->m_count10;
	if (index < 0x200)
		return reinterpret_cast<int>(state->m_inline18[index]);
	index -= 0x200;
	if (index < state->m_count818)
		return reinterpret_cast<int>(state->m_value81c[index].m_value00);
	index -= state->m_count818;
	if (index < 0x40)
		return reinterpret_cast<int>(bfmeCheckGC(state->m_values824[index]));
	index -= 0x40;
	if (index < 0x40)
		return reinterpret_cast<int>(bfmeCheckGC(state->m_values928[index]));
	index -= 0x40;
	if (index < 0x200)
		return reinterpret_cast<int>(state->m_valuesA2C[index]);
	index -= 0x200;
	int nodeCount = ((Rva008BD1B0Node *)state->m_node122C)->count();
	if (index < nodeCount)
		return reinterpret_cast<int>(((Gen_008BD1D0 *)state->m_node122C)->bfmeAdvance(index));

	int originalNodeCount = ((Rva008BD1B0Node *)state->m_node122C)->count();
	int remaining = index - originalNodeCount;
	int recordsRemaining = state->m_count1234;
	int recordsToScan = state->m_count12A4;
	Rva008A1E80Record *base = state->m_records1230;
	Rva008A1E80Record *record = base;
	for (int recordIndex = 0; recordIndex < recordsToScan; ++recordIndex, ++record)
	{
		if (record->m_value00 != 0)
		{
			if (remaining == 0)
				return reinterpret_cast<int>(base[recordIndex].m_value04);
			--remaining;
			if (remaining < record->m_count14)
			{
				return reinterpret_cast<int>(bfmeCheckGC(
					*(base[recordIndex].m_values1c - 1 +
						(record->m_count14 - remaining))));
			}
			remaining -= record->m_count14;
			--recordsRemaining;
			if (recordsRemaining == 0)
				return 0;
		}
	}
	return 0;
}
