// ??1Rva008A6410HeaderedDeleting@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc
// Retail 0x008A61F0 is the complete destructor paired with the existing
// scalar deleting destructor at 0x008A6410. The class owns two ref-counted
// strings before the common Q4 teardown.

class Q3EhMember0089C900
{
public:
	~Q3EhMember0089C900();
};

class Q4Base00D35D68
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void notify(int a, int b);
	~Q4Base00D35D68() { }
};

// The Apt allocator-hook pair pointer at VA 0x01337A30, defined once by
// game/Libraries/Source/Apt/Apt.cpp.  Slot +4 is the deallocator this TU calls;
// the view below is the TU-local spelling of that second slot.
struct BfmeStringPool3AF0;
extern struct BfmeStringPool3AF0 *g_rva01337A30AllocPair;

struct Rva01337A30PoolView
{
	void *m_alloc;
	void (__cdecl *m_release)(void *);
};

struct Rva008A6410RefCount
{
	unsigned short m_count;
};

class Rva008A6410Ref
{
	public:
	~Rva008A6410Ref()
	{
		Rva008A6410RefCount *ref = m_reference;
		--ref->m_count;
		if (ref->m_count == 0)
			((Rva01337A30PoolView *)g_rva01337A30AllocPair)->m_release(ref);
	}

	private:
	Rva008A6410RefCount *m_reference;
};

class Rva008A6410Middle : public Q4Base00D35D68
{
public:
	virtual void v3();
	virtual void v4();
	virtual void v5();
	__forceinline virtual ~Rva008A6410Middle()
	{
		notify(0, 0);
		m_flag = 0;
	}

	char m_gap0[8 - 4];
	Q3EhMember0089C900 m_sub;
	char m_gap1[0x18 - 9];
	int m_flag;
};

class Rva008A6410HeaderedDeleting : public Rva008A6410Middle
{
public:
	virtual ~Rva008A6410HeaderedDeleting();

private:
	char m_gap2[0x20 - 0x1C];
	Rva008A6410Ref m_ref20;
	Rva008A6410Ref m_ref24;
};

Rva008A6410HeaderedDeleting::~Rva008A6410HeaderedDeleting()
{
}
