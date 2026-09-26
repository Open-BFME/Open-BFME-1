// cl: /O2

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class Rva000877E0Counted
{
public:
	virtual ~Rva000877E0Counted();

	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva000877E0Ref
{
public:
	~Rva000877E0Ref();

private:
	Rva000877E0Counted *m_ptr;
};

Rva000877E0Ref::~Rva000877E0Ref()
{
	if (m_ptr)
	{
		m_ptr->Release_Ref();
		m_ptr = 0;
	}
}
