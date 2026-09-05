// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Twin of 0x0069B800 (Rva0069B800ThingRefAssign.cpp): ThingRef assign from a
// raw pointer, byte-identical shape. Address-derived — owning type is not
// recovered.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

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
};

class Rva000B5FD0Ref
{
public:
	void assign(RefCountedThing *p);

	RefCountedThing *m_ptr;
};

// ?assign@Rva000B5FD0Ref@@QAEXPAVRefCountedThing@@@Z
void Rva000B5FD0Ref::assign(RefCountedThing *p)
{
	if (p != m_ptr)
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
		m_ptr = p;
		if (p)
			p->Add_Ref();
	}
}
