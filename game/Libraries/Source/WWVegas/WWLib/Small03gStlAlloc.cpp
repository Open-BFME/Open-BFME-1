// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x0094C210 / 0x009A3450 are byte-identical STL threshold allocators
// for three-integer (12-byte) elements: a zero count returns null, otherwise
// the count is tripled and octupled (lea eax,[eax+eax*2] / shl eax,3) and
// sizes above 0x80 go through operator new at 0x00881F30 while smaller sizes
// go through __new_alloc::allocate at 0x0082E540. The nonzero-guard spelling
// is what emits retail's `test eax,eax / je null / lea / shl / cmp / push /
// jbe / call new / add esp,4 / ret 8 / call alloc / add esp,4 / ret 8 /
// xor eax,eax / ret 8` form (the early-return spelling merges the null tail
// and drifts); and the two-argument (count, tag) signature is what emits the
// `ret 8` tails. Same idiom as the landed Rva00784AD0StlAllocate precedent
// (four-byte elements, *4 scale). IDENTITY IS NOT RECOVERED: the allocators
// keep their address tokens and land under distinct opaque names
// (one-identity rule).
namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int bytes);
	};
}

void *operator new(unsigned int bytes);

void *__stdcall Rva0094C210Alloc(unsigned int n, unsigned int tag)
{
	(void)tag;
	unsigned int bytes = n;
	if (bytes != 0)
	{
		bytes = n + n * 2;
		bytes <<= 3;
		if (bytes > 0x80)
			return ::operator new(bytes);
		return _STL::__new_alloc::allocate(bytes);
	}
	return 0;
}

void *__stdcall Rva009A3450Alloc(unsigned int n, unsigned int tag)
{
	(void)tag;
	unsigned int bytes = n;
	if (bytes != 0)
	{
		bytes = n + n * 2;
		bytes <<= 3;
		if (bytes > 0x80)
			return ::operator new(bytes);
		return _STL::__new_alloc::allocate(bytes);
	}
	return 0;
}
