// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// _STL::__destroy_aux over a range of 4-byte refcounted handles. The element
// destructor inlines Release_Ref: InterlockedDecrement on the object's +4,
// then the scalar-deleting destructor when the count is no longer positive.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

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

class ThingRef
{
public:
	~ThingRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	RefCountedThing *m_ptr;
};

class ThingRefB
{
public:
	~ThingRefB()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	RefCountedThing *m_ptr;
};

namespace _STL
{

struct __false_type
{
};

void __destroy_aux(ThingRef *first, ThingRef *last, const __false_type &)
{
	for (; first != last; ++first)
		first->~ThingRef();
}

void __destroy_aux(ThingRefB *first, ThingRefB *last, const __false_type &)
{
	for (; first != last; ++first)
		first->~ThingRefB();
}

}
