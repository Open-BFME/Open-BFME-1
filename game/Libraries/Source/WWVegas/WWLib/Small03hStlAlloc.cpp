// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail STL threshold allocator 0x0093D510: a zero count returns null,
// otherwise the count is scaled x3 then x8 (24-byte elements) and sizes
// above 0x80 go through operator new at 0x00881F30 while smaller sizes go
// through __new_alloc::allocate at 0x0082E540. Same nonzero-guard idiom as
// the landed Small03gStlAlloc trio (0x0094C210/0x009A3450/0x0094C1C0).
// IDENTITY IS NOT RECOVERED: the allocator keeps its address token.
namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int bytes);
	};
}

void *operator new(unsigned int bytes);

void *__stdcall Rva0093D510Alloc(unsigned int n, unsigned int tag)
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
