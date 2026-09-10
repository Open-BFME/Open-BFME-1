// ?bfmeRemoveObjectA1C20@BfmeJ1017@@QAEXPAVBfmeObj4310@@@Z
// partial score=0.55 date=2026-09-10
// BFME object-removal helper reached by BfmeObj4310::bfmeCleanup at 0x008C3F10.
// The caller leaves the BfmeJ1017 holder in ECX and passes the object on the
// stack; the holder's 0x20-byte entries are drained through releaseAll.
// cl: /O2 /DNDEBUG /MD

class Rva008A0FF0ValueStack
{
public:
	void releaseAll(void);
};

class BfmeEntryA1C20
{
public:
	virtual void slot00(void) = 0;
	virtual void release(void) = 0;

	unsigned int m_flags;
	char m_gap08[0x1c];
	int m_key;
};

class BfmeObjectStateA1C20
{
public:
	char m_gap00[0x0c];
	int m_key;
};

class BfmeObj4310
{
public:
	char m_gap00[0x50];
	BfmeObjectStateA1C20 *m_state;
};

struct BfmeSlotA1C20
{
	void *m_value;
	BfmeEntryA1C20 *m_entry;
	char m_gap08[0x18];
};

class BfmeJ1017
{
public:
	char m_gap00[0x1230];
	BfmeSlotA1C20 *m_slots;
	int m_count;
	char m_gap1238[0x6c];
	int m_limit;

	void bfmeRemoveObjectA1C20(BfmeObj4310 *object);
};

extern BfmeJ1017 *g_bfmeJ1017;

// ?bfmeRemoveObjectA1C20@BfmeJ1017@@QAEXPAVBfmeObj4310@@@Z
void BfmeJ1017::bfmeRemoveObjectA1C20(BfmeObj4310 *object)
{
	int remaining = m_count;
	int index = 0;

	if (remaining == index)
		return;
	if (g_bfmeJ1017->m_limit <= index)
		return;

	unsigned int offset = 0;

	for (;;)
	{
		BfmeSlotA1C20 *slot =
			(BfmeSlotA1C20 *)((char *)m_slots + offset);

		if (slot->m_value != 0)
		{
			BfmeObjectStateA1C20 *state = object->m_state;
			if (state != 0)
			{
				BfmeEntryA1C20 *entry = slot->m_entry;
				unsigned int flags = entry->m_flags;
				if ((flags & 0x3f) == 0x0a && (flags & 0x8000) != 0 &&
					entry->m_key == state->m_key)
				{
					entry->release();
					((Rva008A0FF0ValueStack *)((char *)m_slots + offset))->releaseAll();
					*(void **)((char *)m_slots + offset) = 0;
					--m_count;
					if (--remaining == 0)
						return;
				}
			}
		}

		++index;
		offset += 0x20;
		if (index >= g_bfmeJ1017->m_limit)
			return;
	}
}
