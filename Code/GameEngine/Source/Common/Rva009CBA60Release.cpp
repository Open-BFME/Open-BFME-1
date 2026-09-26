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

struct Rva009CBA60Element
{
	char bytes[0x08];
};

// ?Rva009CBA60Release@@YGXPAXI@Z
void __stdcall Rva009CBA60Release(void *block, unsigned int count)
{
	if (block)
	{
		unsigned int bytes = count * sizeof(Rva009CBA60Element);
		if (bytes > 0x80)
			operator delete(block);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
	}
}
