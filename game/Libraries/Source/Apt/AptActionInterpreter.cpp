// ?rva8CF1B0ProcessRecord@@YAXPAVRva8CF1B0State@@PAURva8CF1B0Cursor@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva8CF1B0StringBlock { unsigned short m_refs; };
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	~BfmeStrVKI()
	{
		Rva8CF1B0StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}
	void bfmeSetVKI(const char *text);
private:
	Rva8CF1B0StringBlock *m_block;
};

class Rva8CF1B0Value
{
public:
	virtual void addRef();
	virtual void release();
	unsigned m_flags;
};

class BfmeR1226
{
public:
	void bfmeAdd1226(void *data, void *context, int size);
};

class Rva8CD130String;
class Rva8CD130Value;
class Rva8CD130State
{
public:
	void append(void *context, void *scope, Rva8CD130String *name,
		Rva8CD130Value *value, int a, int b, int c);
};

class BfmeA1232
{
public:
	void bfmePop1232(int count);
};

class Rva8CF1B0State
{
public:
	void addSegment(void *data, void *context, int size);
	void append(void *context, void *scope, BfmeStrVKI *name,
		Rva8CF1B0Value *value, int a, int b, int c);
	void popValues(int count);
	unsigned m_count;
	int m_unused04;
	Rva8CF1B0Value **m_stack;
	char m_gap0c[0x4c];
	Rva8CF1B0Value **m_slots;
	char m_gap5c[0x20];
	Rva8CF1B0Value *m_pending;
};

struct Rva8CF1B0Cursor { unsigned char *m_position; void *m_context; };
struct Rva8CF1B0Record
{
	unsigned m_firstSize;
	unsigned m_secondSize;
	unsigned m_thirdSize;
	unsigned char m_flags;
	unsigned char m_unused0d;
	unsigned char m_unused0e;
	unsigned char m_slot;
	const char *m_name;
};

extern Rva8CF1B0Value *g_bfmeFallbackDB;

void rva8CF1B0ProcessRecord(Rva8CF1B0State *state, Rva8CF1B0Cursor *cursor)
{
	int initialCount = state->m_count;
	unsigned char *aligned = (unsigned char *)(((unsigned)cursor->m_position + 3) & ~3u);
	Rva8CF1B0Record *record = (Rva8CF1B0Record *)aligned;
	cursor->m_position = aligned + 0x14;
	cursor->m_position += record->m_firstSize;
	cursor->m_position += record->m_secondSize;
	cursor->m_position += record->m_thirdSize;

	reinterpret_cast<BfmeR1226 *>(state)->bfmeAdd1226(
		aligned + 0x14, cursor->m_context, record->m_firstSize);
	Rva8CF1B0Value *pending = state->m_pending;
	if (pending != 0 && (record->m_flags & 1) != 0)
	{
		if ((record->m_flags & 4) != 0)
		{
			if (state->m_slots[record->m_slot] != 0)
				state->m_slots[record->m_slot]->release();
			state->m_slots[record->m_slot] = pending;
			pending->addRef();
		}
		else
		{
			BfmeStrVKI name(record->m_name);
			reinterpret_cast<Rva8CD130State *>(state)->append(cursor->m_context, 0,
				reinterpret_cast<Rva8CD130String *>(&name),
				reinterpret_cast<Rva8CD130Value *>(pending), 0, 1, 0);
		}

		state->m_pending->release();
		state->m_pending = 0;
		reinterpret_cast<BfmeR1226 *>(state)->bfmeAdd1226(
			aligned + 0x14 + record->m_firstSize,
			cursor->m_context, record->m_secondSize);
		if ((record->m_flags & 4) != 0)
		{
			state->m_slots[record->m_slot] = g_bfmeFallbackDB;
			pending->release();
		}
		else
		{
			BfmeStrVKI name(record->m_name);
			reinterpret_cast<Rva8CD130State *>(state)->append(cursor->m_context, 0,
				reinterpret_cast<Rva8CD130String *>(&name), 0, 0, 1, 0);
		}
	}

	if ((record->m_flags & 2) != 0)
	{
		pending = state->m_pending;
		if (pending != 0)
		{
			pending->addRef();
			state->m_pending->release();
			state->m_pending = 0;
		}
		unsigned *sizes = &record->m_firstSize;
		reinterpret_cast<BfmeR1226 *>(state)->bfmeAdd1226(
			(void *)(sizes[1] + sizes[0] + (unsigned)record + 0x14),
			cursor->m_context, sizes[2]);
		if (pending != 0 && state->m_pending == 0)
		{
			pending->addRef();
			state->m_pending = pending;
			pending->release();
		}
	}

	if (state->m_count > initialCount)
		reinterpret_cast<BfmeA1232 *>(state)->bfmePop1232(
			state->m_count - initialCount);
}
