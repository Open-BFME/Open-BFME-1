// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME5: address-derived Release dtor at retail 0x003B7740, 42 bytes.
// Empty user dtor so MSVC stores vtable 0x010EC768 first, then runs the
// member Holder dtor which InterlockedDecrements +0x08's refcount at +4 and
// on last ref scalar-deletes (push 1 / call [vtable]).

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class BfmeReleaseHolder
{
public:
	~BfmeReleaseHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	RefCountedThing *m_ptr;
};

class Rva003B7740
{
public:
	virtual ~Rva003B7740();

private:
	void *m_pad;
	BfmeReleaseHolder m_hold;
};

Rva003B7740::~Rva003B7740()
{
}
