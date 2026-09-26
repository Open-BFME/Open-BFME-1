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
