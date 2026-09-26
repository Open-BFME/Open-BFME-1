// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// thiscall copy-assign of a handle whose refcounted subobject sits at
// +0x70 of the stored pointer (refcount at +0x74). stdcall one argument.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

class Inner0070
{
public:
	virtual ~Inner0070();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Open2696480Handle
{
public:
	Open2696480Handle &assign(const Open2696480Handle &other);

	char *m_outer;
};

// ?assign@Open2696480Handle@@QAEAAV1@ABV1@@Z
Open2696480Handle &Open2696480Handle::assign(
	const Open2696480Handle &other)
{
	if (this != &other)
	{
		if (other.m_outer)
			InterlockedIncrement(
				&reinterpret_cast<Inner0070 *>(other.m_outer + 0x70)->m_refCount);
		if (m_outer)
			reinterpret_cast<Inner0070 *>(m_outer + 0x70)->Release_Ref();
		m_outer = other.m_outer;
	}
	return *this;
}
