// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Same void assign as 0x0069B800 but the refcounted subobject sits at
// +0x70 of the stored pointer.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class Inner0070
{
public:
	virtual ~Inner0070();

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

class Open269B4B0Handle
{
public:
	void assign(char *p);

	char *m_outer;
};

// ?assign@Open269B4B0Handle@@QAEXPAD@Z
void Open269B4B0Handle::assign(char *p)
{
	if (p != m_outer)
	{
		if (m_outer)
		{
			reinterpret_cast<Inner0070 *>(m_outer + 0x70)->Release_Ref();
			m_outer = 0;
		}
		m_outer = p;
		if (p)
			reinterpret_cast<Inner0070 *>(p + 0x70)->Add_Ref();
	}
}
