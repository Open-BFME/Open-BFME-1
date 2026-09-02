// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ThingRef assign from a raw pointer: Release the old, store the new,
// AddRef the new. thiscall with one stack argument, ret 4.

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

class Open269B800Ref
{
public:
	void assign(RefCountedThing *p);

	RefCountedThing *m_ptr;
};

// ?assign@Open269B800Ref@@QAEXPAVRefCountedThing@@@Z
void Open269B800Ref::assign(RefCountedThing *p)
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
