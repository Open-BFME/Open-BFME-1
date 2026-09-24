// ?rva8CE5C0AppendRecord@@YAXPAVRva8CE5C0State@@PAURva8CE5C0Cursor@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt record append, retail 0x008CE5C0 (383 bytes).

struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	void bfmeSetVKI(const char *text);
	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
	}
	BfmeStrVKI &operator=(const BfmeStrVKI &source)
	{
		++source.m_data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
		m_data = source.m_data;
		return *this;
	}
	BfmeStringData3AF0 *m_data;
};

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
void Gen00897300(void *block);

class Rva008BA800HeaderedDelete
{
public:
	static void operator delete(void *storage, unsigned int size);
};

class Rva8CE5C0Value
{
public:
	virtual void addRef();
	virtual void release();
	bool maxRefCountHit() const { return ((m_flags >> 30) & 1) != 0; }
	unsigned m_flags;
};

// 0x34-byte value built by the constructor at 0x008D6290; freed through 0x008BA800.
class Rva8CE5C0Object : public Rva8CE5C0Value, public Rva008BA800HeaderedDelete
{
public:
	Rva8CE5C0Object(void *record, Rva8CE5C0Value *top, int property, void *context);
	static void *operator new(unsigned int bytes)
	{
		char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
		char *block = raw + 8;
		Gen00897300(block);
		return block;
	}
	char m_gap08[0x2c];
};

class Rva8CD130String;
class Rva8CD130Value;

class Rva8CD130State
{
public:
	void append(void *first, void *second, Rva8CD130String *name,
		Rva8CD130Value *top, int one1, int one2, int zero);

	int m_count;
	int m_unused;
	Rva8CE5C0Value **m_stack;
};

struct Rva8CE5C0Stack
{
	int size() const { return m_count; }
	Rva8CE5C0Value *top() const { return m_stack[m_count - 1]; }

	int m_count;
	int m_unused;
	Rva8CE5C0Value **m_stack;
};

class Rva8CE5C0State : public Rva8CD130State
{
public:
	Rva8CE5C0Stack m_stack0C;
	char m_gap18[0x44];
	int m_line;
	int m_column;
};

struct Rva8CE5C0ContextRoot { char m_gap00[0x0c]; int *m_properties; };
struct Rva8CE5C0Context
{
	int *properties() { return m_root->m_properties; }

	char m_gap00[0x50];
	Rva8CE5C0ContextRoot *m_root;
};
struct Rva8CE5C0Cursor { unsigned char *m_position; Rva8CE5C0Context *m_context; void *m_scope; };
struct Rva8CE5C0Record { const char *m_name; char m_gap04[8]; unsigned m_size; int m_line; int m_column; };

// ?rva8CE5C0AppendRecord@@YAXPAVRva8CE5C0State@@PAURva8CE5C0Cursor@@@Z
void rva8CE5C0AppendRecord(Rva8CE5C0State *state, Rva8CE5C0Cursor *cursor)
{
	Rva8CE5C0Record *record = (Rva8CE5C0Record *)(((unsigned)cursor->m_position + 3) & ~3u);
	cursor->m_position = (unsigned char *)(record + 1);
	cursor->m_position += record->m_size;
	record->m_line = state->m_line;
	record->m_column = state->m_column;

	BfmeStrVKI name(record->m_name);
	Rva8CE5C0Value *top;
	if (state->m_stack0C.size() > 0)
	{
		top = state->m_stack0C.top();
		top->addRef();
	}
	else
		top = 0;
	Rva8CE5C0Value *value = new Rva8CE5C0Object(record, top,
		cursor->m_context->properties()[1], cursor->m_context);

	if (*record->m_name == 0)
	{
		state->m_stack[state->m_count++] = value;
		if (!value->maxRefCountHit())
			value->addRef();
	}
	else
	{
		name = BfmeStrVKI(record->m_name);
		state->append(cursor->m_context, cursor->m_scope, (Rva8CD130String *)&name,
			(Rva8CD130Value *)value, 1, 1, 0);
	}
}
