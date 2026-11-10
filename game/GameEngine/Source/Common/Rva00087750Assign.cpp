// cl: /O2

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class Rva00087750Counted
{
public:
	virtual ~Rva00087750Counted();

	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva00087750Ref
{
public:
	Rva00087750Ref &operator=(const Rva00087750Ref &rhs);

private:
	Rva00087750Counted *m_ptr;
};

Rva00087750Ref &Rva00087750Ref::operator=(const Rva00087750Ref &rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_ptr)
			InterlockedIncrement(&rhs.m_ptr->m_refCount);
		if (m_ptr)
			m_ptr->Release_Ref();
		m_ptr = rhs.m_ptr;
	}
	return *this;
}

// Retail 0x00087860: a second, byte-identical copy-assign with its own body
// (no identical-COMDAT folding in retail). MapObject 0x00088480 calls it on
// its +0x5C custom-info reference (call at +0x2C4, ILT 0x00043C07), a member
// the 0x00087750 callers never touch, so it is a distinct reference class.
class Rva00087860Ref
{
public:
	Rva00087860Ref &operator=(const Rva00087860Ref &rhs);

private:
	Rva00087750Counted *m_ptr;
};

Rva00087860Ref &Rva00087860Ref::operator=(const Rva00087860Ref &rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_ptr)
			InterlockedIncrement(&rhs.m_ptr->m_refCount);
		if (m_ptr)
			m_ptr->Release_Ref();
		m_ptr = rhs.m_ptr;
	}
	return *this;
}
