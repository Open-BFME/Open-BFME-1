// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail STL threshold deallocator 0x0093D480: a null pointer returns,
// otherwise the count is scaled x3 then x8 (24-byte elements) and sizes
// above 0x80 go through operator delete at 0x00881EB0 while smaller sizes
// go through __node_alloc<true, 0>::_M_deallocate at 0x0082E5F0.
// Template-declaration idiom per Rva004F1210Deallocate.cpp. IDENTITY IS NOT
// RECOVERED: the deallocator keeps its address token.
namespace _STL
{
	// The node allocator's pool entry points are private STLport members
	// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
	// 0x0082E5F0); these TU-local helpers reach them under their real names.
	template <bool __threads, int __inst> class __node_alloc;
	static void nodePoolDeallocate(void *block, unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void nodePoolDeallocate(void *, unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
		static void __cdecl _M_deallocate(void *__p, unsigned int __n);
	};
	static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}
void __cdecl operator delete(void *block);
void __stdcall Rva0093D480Free(void *p, unsigned int n)
{
	if (p == 0)
		return;
	unsigned int bytes = n + n * 2;
	bytes <<= 3;
	if (bytes > 0x80)
	{
		::operator delete(p);
		return;
	}
	_STL::nodePoolDeallocate(p, bytes);
}
// Retail 0x0094C0F0 scales x9 then x4 (36-byte elements); the same twin as
// the landed Small03gStlAlloc Rva0094C1C0Alloc. 0x0094C170 and 0x009A3400
// are byte-identical x3/x8 twins of 0x0093D480 with distinct opaque names
// (one-identity rule). 0x009CEAC0 scales x3 then x16 (48-byte elements);
// 0x009CEB00 is another x9/x4 twin of 0x0094C0F0.
void __stdcall Rva0094C0F0Free(void *p, unsigned int n)
{
	if (p == 0)
		return;
	unsigned int bytes = n + n * 8;
	bytes <<= 2;
	if (bytes > 0x80)
	{
		::operator delete(p);
		return;
	}
	_STL::nodePoolDeallocate(p, bytes);
}

void __stdcall Rva0094C170Free(void *p, unsigned int n)
{
	if (p == 0)
		return;
	unsigned int bytes = n + n * 2;
	bytes <<= 3;
	if (bytes > 0x80)
	{
		::operator delete(p);
		return;
	}
	_STL::nodePoolDeallocate(p, bytes);
}

void __stdcall Rva009A3400Free(void *p, unsigned int n)
{
	if (p == 0)
		return;
	unsigned int bytes = n + n * 2;
	bytes <<= 3;
	if (bytes > 0x80)
	{
		::operator delete(p);
		return;
	}
	_STL::nodePoolDeallocate(p, bytes);
}

void __stdcall Rva009CEAC0Free(void *p, unsigned int n)
{
	if (p == 0)
		return;
	unsigned int bytes = n + n * 2;
	bytes <<= 4;
	if (bytes > 0x80)
	{
		::operator delete(p);
		return;
	}
	_STL::nodePoolDeallocate(p, bytes);
}

void __stdcall Rva009CEB00Free(void *p, unsigned int n)
{
	if (p == 0)
		return;
	unsigned int bytes = n + n * 8;
	bytes <<= 2;
	if (bytes > 0x80)
	{
		::operator delete(p);
		return;
	}
	_STL::nodePoolDeallocate(p, bytes);
}
