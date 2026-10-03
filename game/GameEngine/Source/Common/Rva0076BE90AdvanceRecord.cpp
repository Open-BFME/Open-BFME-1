struct BfmeRecord6BE90
{
	char m_data[0xBC];
};

struct BfmeRecordRange6BE90
{
	char m_pad00[0x24];
	BfmeRecord6BE90 *m_begin;
	BfmeRecord6BE90 *m_end;
};

class BfmeRecordHook6BE90
{
public:
	// bfmeSelect6BE90() is reached through the ILT thunk below, not declared here.
};

// The selection call goes through the five-byte ILT thunk at 0x000418E9, defined
// as ?j_000418e9@@YAXXZ in game/gen_small/thunks_031.cpp (target FUN_00b6b800)
// and pinned for this adjusted-this record hook. The thunk declares no arguments
// of its own: it jumps with the thiscall `this` in ECX and the caller's arguments
// already in place, so the call is spelled through a thiscall member pointer of
// the same shape.
extern void j_000418e9();

typedef void (BfmeRecordHook6BE90::*bfmeSelect6BE90Thunk)(
	BfmeRecord6BE90 *record, int activate, int reserved);

union BfmeSelect6BE90ThunkCast
{
	void (__cdecl *freeFunction)(BfmeRecord6BE90 *record, int activate, int reserved);
	bfmeSelect6BE90Thunk memberFunction;
};

class Rva0076BE90Cursor
{
public:
	void advanceRecord();

private:
	char m_pad00[8];
	BfmeRecord6BE90 *m_current;
	char m_pad0C[0x224 - 0x0C];
	bool m_active;
};

void Rva0076BE90Cursor::advanceRecord()
{
	BfmeRecordRange6BE90 *range =
		*reinterpret_cast<BfmeRecordRange6BE90 **>(reinterpret_cast<char *>(this) - 8);
	bool found = false;
	for (BfmeRecord6BE90 *record = range->m_begin; record != range->m_end; ++record)
	{
		if (found)
		{
			if (record)
			{
				m_active = true;
				BfmeRecordHook6BE90 *hook = reinterpret_cast<BfmeRecordHook6BE90 *>(
					reinterpret_cast<char *>(this) - 12);
				BfmeSelect6BE90ThunkCast cast;
				cast.freeFunction = reinterpret_cast<void (__cdecl *)(BfmeRecord6BE90 *, int, int)>(
					&::j_000418e9);
				(hook->*cast.memberFunction)(record, 1, 0);
			}
			return;
		}
		if (record == m_current)
			found = true;
	}
}
