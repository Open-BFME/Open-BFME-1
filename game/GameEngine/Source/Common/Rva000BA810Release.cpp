// cl: /O2

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class Rva000BA810Counted
{
public:
	virtual ~Rva000BA810Counted();

	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
		{
			Rva000BA810Counted *n1 = this;
			if (n1)
				delete n1;
		}
	}

	long m_refCount;
};

class Rva000BA810Holder
{
public:
	Rva000BA810Counted *m_ptr;
};

void rva000ba810(Rva000BA810Holder *p)
{
	if (p->m_ptr)
		p->m_ptr->Release_Ref();
}
