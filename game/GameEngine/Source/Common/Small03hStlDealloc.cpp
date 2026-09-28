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
	template<bool THREADS, int INSTANCE>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *node, unsigned int bytes);
	};
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
	_STL::__node_alloc<true, 0>::_M_deallocate(p, bytes);
}
