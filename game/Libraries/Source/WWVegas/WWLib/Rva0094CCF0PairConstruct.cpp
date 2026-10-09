// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB

// Retail 0x0094C650 constructs the pair used by the tree whose _M_insert
// caller lives at 0x0094C9E0.  The first member points to a reference-counted
// record, and the second member copies sixteen bytes of value state.

struct Rva0094CCF0Value
{
	char m_body[ 16 ];
};

namespace _STL
{

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;

	T1 first;
	T2 second;
};

template <class T1, class T2>
void _Construct(T1 *destination, const T2 &source);

typedef pair<const unsigned int, Rva0094CCF0Value> Rva0094CCF0Pair;

template <>
__declspec(noinline) void _Construct(Rva0094CCF0Pair *destination,
	const Rva0094CCF0Pair &source)
{
	if (destination != 0)
	{
		const unsigned int *in = (const unsigned int *)&source;
		unsigned int *out = (unsigned int *)destination;
		unsigned int pointer = *in;
		*out = pointer;
		if (pointer != 0)
			++*(unsigned short *)(pointer + 4);

		Rva0094CCF0Value *outValue =
			(Rva0094CCF0Value *)((char *)out + 4);
		*outValue = *(const Rva0094CCF0Value *)((const char *)in + 4);
	}
}

}

namespace _STL
{
// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}
}

void *__stdcall rva0094C880AllocatePair(const _STL::Rva0094CCF0Pair &source)
{
	char *node = (char *)_STL::vectorSmallAllocate(36);
	_STL::_Construct((_STL::Rva0094CCF0Pair *)(node + 16), source);
	return node;
}
