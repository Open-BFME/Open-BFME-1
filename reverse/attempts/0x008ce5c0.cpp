// ?rva8CE5C0AppendRecord@@YAXPAURva8CE5C0Cursor@@PAVRva8CE5C0State@@@Z
// partial score=0.65 date=2026-09-02
// ?rva8CE5C0AppendRecord@@YAXPAURva8CE5C0Cursor@@PAVRva8CE5C0State@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva8CE5C0StringBlock { unsigned short m_refs; };
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
extern void *(__cdecl *g_rva8CE5C0Allocate)(unsigned);

class Rva8CE5C0String
{
public:
	Rva8CE5C0String(const char *text);
	Rva8CE5C0String(const Rva8CE5C0String &other)
	{
		m_block = other.m_block;
		++m_block->m_refs;
	}
	~Rva8CE5C0String()
	{
		Rva8CE5C0StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}
	void set(const char *text);
	const char *text() const { return (const char *)m_block; }
private:
	Rva8CE5C0StringBlock *m_block;
};

class Rva8CE5C0Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual bool tagged();
	unsigned m_flags;
};

class Rva8CE5C0Object : public Rva8CE5C0Value
{
public:
	Rva8CE5C0Object(void *record, Rva8CE5C0Value *top, int property,
		void *context);
	static void *operator new(unsigned size)
	{
		void *raw = g_rva8CE5C0Allocate(size);
		return (char *)raw + 8;
	}
	static void operator delete(void *);
	char m_gap08[0x34];
};

class Rva8CE5C0State
{
public:
	void append(void *, void *, Rva8CE5C0String *, Rva8CE5C0Value *, int, int, int);
	char m_gap00[0x0c];
	int m_count;
	int m_unused;
	Rva8CE5C0Value **m_stack;
	char m_gap18[0x44];
	int m_line;
	int m_column;
};

struct Rva8CE5C0ContextRoot { char m_gap00[0x50]; int *m_properties; };
struct Rva8CE5C0Context { char m_gap00[0x50]; Rva8CE5C0ContextRoot *m_root; };
struct Rva8CE5C0Cursor { unsigned char *m_position; Rva8CE5C0Context *m_context; void *m_scope; };
struct Rva8CE5C0Record { const char *m_name; char m_gap04[8]; unsigned m_size; int m_line; int m_column; };

void rva8CE5C0AppendRecord(Rva8CE5C0Cursor *cursor, Rva8CE5C0State *state)
{
	unsigned char *aligned = (unsigned char *)(((unsigned)cursor->m_position + 3) & ~3u);
	Rva8CE5C0Record *record = (Rva8CE5C0Record *)aligned;
	cursor->m_position = aligned + 0x18;
	cursor->m_position += record->m_size;
	record->m_line = state->m_line;
	record->m_column = state->m_column;

	Rva8CE5C0String name(record->m_name);
	Rva8CE5C0Value *top = 0;
	if (state->m_count > 0)
	{
		top = state->m_stack[state->m_count - 1];
		top->addRef();
	}
	Rva8CE5C0Object *value = new Rva8CE5C0Object(record, top,
		cursor->m_context->m_root->m_properties[1], cursor->m_context);

	if (*name.text() == 0)
	{
		state->m_stack[state->m_count++] = value;
		if (((value->m_flags >> 30) & 1) == 0)
			value->addRef();
	}
	else
	{
		Rva8CE5C0String copy(name.text());
		state->append(cursor->m_context, cursor->m_scope, &copy, value, 1, 1, 0);
	}
}
