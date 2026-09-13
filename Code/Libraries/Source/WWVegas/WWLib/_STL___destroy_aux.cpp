// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of 0x0069CE20 (Rva0069CE20DestroyAux.cpp): _STL::__destroy_aux over a
// range of 4-byte refcounted handles, byte-identical shape. Address-derived
// — owning type is not recovered.

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

class Rva000BB5D0Ref
{
public:
	~Rva000BB5D0Ref()
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

void __destroy_aux(Rva000BB5D0Ref *first, Rva000BB5D0Ref *last, const __false_type &)
{
	for (; first != last; ++first)
		first->~Rva000BB5D0Ref();
}

}
