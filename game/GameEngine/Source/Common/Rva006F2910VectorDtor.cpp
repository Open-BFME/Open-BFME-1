// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define private public
#include <vector>
#undef private

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString(void)
	{
		releaseBuffer();
	}

private:
	void releaseBuffer(void);
	void *m_data;
};

struct Rva006F2910Element
{
	BFMERetailAsciiString first;
	BFMERetailAsciiString second;
	unsigned char padding[0x30];
};

typedef char Rva006F2910Element_size_must_be_0x38[
	(sizeof(Rva006F2910Element) == 0x38) ? 1 : -1];

template <class T>
class Rva006F2910Allocator
{
public:
	typedef T value_type;

	Rva006F2910Allocator(void)
	{
	}

	template <class U>
	Rva006F2910Allocator(const Rva006F2910Allocator<U> &)
	{
	}

	T *allocate(unsigned int count, const void * = 0)
	{
		return (T *)_STL::__node_alloc<true, 0>::allocate(count * sizeof(T));
	}

	__forceinline void deallocate(T *memory, unsigned int bytes)
	{
		bytes *= sizeof(T);
		if (bytes > 0x80)
			::operator delete(memory);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(memory, bytes);
	}
};

namespace _STL
{
	template <class T, class U>
	Rva006F2910Allocator<U> &__stl_alloc_rebind(
		Rva006F2910Allocator<T> &allocator, const U *)
	{
		return reinterpret_cast<Rva006F2910Allocator<U> &>(allocator);
	}
}

typedef _STL::vector<Rva006F2910Element, Rva006F2910Allocator<Rva006F2910Element> >
	Rva006F2910CustomVector;

template class _STL::vector<Rva006F2910Element,
	Rva006F2910Allocator<Rva006F2910Element> >;
