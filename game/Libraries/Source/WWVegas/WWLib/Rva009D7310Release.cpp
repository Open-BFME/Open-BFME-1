
namespace _STL
{
template <bool THREADS, int INSTANCE>
class __node_alloc
{
public:
	static void _M_deallocate(void *block, unsigned int bytes);
};
}

void __cdecl operator delete(void *block);

struct Rva009D7310Element
{
	char bytes[0x14];
};

// ?Rva009D7310Release@@YGXPAXI@Z
void __stdcall Rva009D7310Release(void *block, unsigned int count)
{
	if (block)
	{
		unsigned int bytes = count * sizeof(Rva009D7310Element);
		if (bytes > 0x80)
			operator delete(block);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
	}
}

struct Rva009D7390Element
{
	char bytes[0x0c];
};

// ?Rva009D7390Release@@YGXPAXI@Z
void __stdcall Rva009D7390Release(void *block, unsigned int count)
{
	if (block)
	{
		unsigned int bytes = count * sizeof(Rva009D7390Element);
		if (bytes > 0x80)
			operator delete(block);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
	}
}
