// ?d_0089abc0@@YAXXZ
// partial score=0.35 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Recovered initialization of the built-in Apt value/function registry.

extern void *(*g_aptWideAllocate)(unsigned int);
extern void Gen00897300(void *);

class Rva899F00Base
{
public:
	Rva899F00Base(const char *, int);
	virtual void bump();
	virtual ~Rva899F00Base();
	void mark()
	{
		unsigned int *flags = reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(this) + 4);
		*flags = (*flags & 0xffffc07f) | 0x40;
	}

private:
	char m_baseData[0x1c];
};

class AptBuiltinFunction : public Rva899F00Base
{
public:
	AptBuiltinFunction(void *callback) :
		Rva899F00Base(reinterpret_cast<const char *>(9), 8),
		m_callback(callback)
	{
	}

	static void *operator new(unsigned int bytes)
	{
		char *allocation = static_cast<char *>(g_aptWideAllocate(bytes + 8));
		Gen00897300(allocation + 8);
		return allocation + 8;
	}

private:
	void *m_callback;
};

class AptBuiltinTable
{
public:
	void add(int key, int value);
	int find(int key);
};

struct AptBuiltinRegistry
{
	char m_pad[8];
	AptBuiltinTable m_table;
};

class AptRegistryStartup
{
public:
	void run();
};

extern AptRegistryStartup *g_aptRegistryStartup;
extern AptBuiltinRegistry *g_aptBuiltinRegistry;

class Rva0089C860State
{
public:
	Rva0089C860State *initialize(int);

private:
	int m_value;
	int m_first;
	int m_second;
	int m_third;
};

struct AptValueLinks;

class __declspec(novtable) AptLinkedValue
{
public:
	virtual void retain();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual bool usesTaggedPointer();
	virtual AptValueLinks *links();

	AptLinkedValue()
	{
		m_flags = (m_flags & 0xb000801c) | 0x801c;
		m_vtable = reinterpret_cast<void **>(0x011360e8);
		m_state.initialize(8);
		m_tail = 0;
	}

	static void *operator new(unsigned int bytes)
	{
		char *allocation = static_cast<char *>(g_aptWideAllocate(bytes + 8));
		Gen00897300(allocation + 8);
		return allocation + 8;
	}

	void **m_vtable;
	unsigned int m_flags;
	Rva0089C860State m_state;
	int m_tail;
};

struct AptValueLinks
{
	char m_pad[8];
	AptLinkedValue *m_left;
	AptLinkedValue *m_right;
};

extern AptLinkedValue *g_aptLinkedBuiltinRoot;
extern AptLinkedValue *g_aptLinkedBuiltinMidpoint;
extern AptBuiltinFunction *g_aptTerminalBuiltin;

static __forceinline AptLinkedValue *untag(AptLinkedValue *value)
{
	return reinterpret_cast<AptLinkedValue *>(
		reinterpret_cast<unsigned int>(value) & ~1u);
}

static __forceinline AptLinkedValue *tag(AptLinkedValue *value)
{
	if (value == 0)
		return 0;

	unsigned int bits = reinterpret_cast<unsigned int>(value);
	if (value->usesTaggedPointer())
		bits |= 1;
	return reinterpret_cast<AptLinkedValue *>(bits);
}

static __forceinline void replaceTagged(
	AptLinkedValue *&slot, AptLinkedValue *value)
{
	AptLinkedValue *old = untag(slot);
	if (value != 0)
		value->retain();
	if (old != 0)
		old->release();
	slot = tag(value);
}

static __forceinline AptLinkedValue *makeLinkedBuiltin(int key)
{
	AptLinkedValue *owner = reinterpret_cast<AptLinkedValue *>(
		g_aptBuiltinRegistry->m_table.find(key));
	AptLinkedValue *value = new AptLinkedValue;
	replaceTagged(owner->links()->m_right, value);
	return value;
}

static __forceinline AptLinkedValue *makeLinkedBuiltin(
	int key, AptLinkedValue *root)
{
	AptLinkedValue *owner = reinterpret_cast<AptLinkedValue *>(
		g_aptBuiltinRegistry->m_table.find(key));
	AptLinkedValue *value = new AptLinkedValue;
	replaceTagged(owner->links()->m_right, value);
	replaceTagged(owner->links()->m_left, root);
	owner->m_flags = (owner->m_flags & 0xffffc07f) | 0x40;
	value->m_flags = (value->m_flags & 0xffffc07f) | 0x40;
	return value;
}

#define ADD_BUILTIN(KEY, CALLBACK) \
	g_aptBuiltinRegistry->m_table.add( \
		(KEY), \
		reinterpret_cast<int>(new AptBuiltinFunction(reinterpret_cast<void *>(CALLBACK))))

void initializeAptBuiltinRegistry(void)
{
	g_aptRegistryStartup->run();

	ADD_BUILTIN(0x01338610, 0x00c98d10);
	ADD_BUILTIN(0x01338504, 0x00c98d10);
	ADD_BUILTIN(0x013386e4, 0x00c98d10);
	ADD_BUILTIN(0x01338530, 0x00c98d10);
	ADD_BUILTIN(0x01338544, 0x00c98d10);
	ADD_BUILTIN(0x0133870c, 0x00c98d10);
	ADD_BUILTIN(0x013385f8, 0x00c98d10);
	ADD_BUILTIN(0x0133873c, 0x00c98d10);
	ADD_BUILTIN(0x013385e8, 0x00c98d10);
	ADD_BUILTIN(0x01338548, 0x00c98d10);
	ADD_BUILTIN(0x013386f4, 0x00c98d10);

	AptLinkedValue *root = makeLinkedBuiltin(0x01338610);
	g_aptLinkedBuiltinRoot = root;

	AptLinkedValue *owner = reinterpret_cast<AptLinkedValue *>(
		g_aptBuiltinRegistry->m_table.find(0x01338610));
	owner->m_flags = (owner->m_flags & 0xffffc07f) | 0x40;
	root->m_flags = (root->m_flags & 0xffffc07f) | 0x40;

	makeLinkedBuiltin(0x01338504, root);
	makeLinkedBuiltin(0x013386e4, root);
	makeLinkedBuiltin(0x01338530, root);
	makeLinkedBuiltin(0x01338544, root);
	makeLinkedBuiltin(0x0133870c, root);
	g_aptLinkedBuiltinMidpoint = makeLinkedBuiltin(0x013385f8, root);
	makeLinkedBuiltin(0x0133873c, root);
	makeLinkedBuiltin(0x013385e8, root);
	makeLinkedBuiltin(0x01338548, root);
	makeLinkedBuiltin(0x013386f4, root);

	g_aptTerminalBuiltin = new AptBuiltinFunction(
		reinterpret_cast<void *>(0x00c99800));
	g_aptTerminalBuiltin->mark();
	g_aptTerminalBuiltin->bump();
}
