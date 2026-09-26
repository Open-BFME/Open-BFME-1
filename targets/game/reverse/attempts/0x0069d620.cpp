// ?getSlot@Rva0069F740Owner@@QAE?AURva0069F740Ref@@HH@Z
// partial score=0.95 date=2026-09-25
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?getSlot@Rva0069F740Owner@@QAE?AURva0069F740Ref@@HH@Z
// Walks the circular list whose sentinel sits at +0x9d0, holding a counted
// reference to each node's value; returns the first node whose value is not
// flagged at +0x34, whose binding (value->+0x14) has a clear +0x84 word behind
// its +0x8 holder, and whose binding carries the requested group (+0x28) and
// inner (+0x64). The sentinel means none.
// Called through ILT 0x0001815B by the matched Rva0069F740Owner::check and
// bfmeGetYM; owner identity is not otherwise recovered.

extern "C" void _ReadWriteBarrier(void);
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_WriteBarrier)

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

struct Rva0069F740Holder
{
	char m_pad00[0x84];
	void *m_busy;
};

struct Rva0069F740Binding
{
	char m_pad00[0x8];
	Rva0069F740Holder *m_holder;
	char m_pad0c[0x28 - 0x0c];
	int m_group;
	char m_pad2c[0x64 - 0x2c];
	int m_inner;
};

class Rva0069F740Value
{
public:
	virtual ~Rva0069F740Value();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
	}

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	char m_pad08[0x14 - 0x08];
	Rva0069F740Binding *m_binding;
	char m_pad18[0x34 - 0x18];
	bool m_skip;
};

class Rva0069F740ValueRef
{
public:
	Rva0069F740ValueRef(Rva0069F740Value *value) : m_ptr(value)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}

	~Rva0069F740ValueRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva0069F740Value *operator->() const { return m_ptr; }
	Rva0069F740Value *get() const { return m_ptr; }

private:
	Rva0069F740Value *m_ptr;
};

struct Rva0069F740Node
{
	Rva0069F740Node *m_next;
	Rva0069F740Node *m_prev;
	Rva0069F740Value *m_value;
};

struct Rva0069F740Ref
{
	Rva0069F740Node *m_value;
};

class Rva0069F740Owner
{
public:
	Rva0069F740Ref getSlot(int group, int inner);

	char m_pad0[0x9d0];
	Rva0069F740Node *m_sentinel;
};

Rva0069F740Ref Rva0069F740Owner::getSlot(int group, int inner)
{
	for (Rva0069F740Node *node = m_sentinel->m_next; node != m_sentinel;
		node = node->m_next)
	{
		Rva0069F740ValueRef value(node->m_value);
		if (value.get() == 0)
			continue;
		if (value->m_skip)
			continue;
		Rva0069F740Binding *binding = value->m_binding;
		if (binding->m_holder->m_busy != 0)
			continue;
		if (binding->m_group == group && binding->m_inner == inner)
		{
			Rva0069F740Ref result;
			result.m_value = node;
			return result;
		}
	}
	Rva0069F740Ref result;
	result.m_value = m_sentinel;
	return result;
}
