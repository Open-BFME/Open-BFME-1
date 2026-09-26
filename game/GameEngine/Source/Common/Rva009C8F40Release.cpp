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

struct Rva009C8F40Element
{
	char bytes[0x18];
};

// ?Rva009C8F40Release@@YGXPAXI@Z
void __stdcall Rva009C8F40Release(void *block, unsigned int count)
{
	if (block)
	{
		unsigned int bytes = count * sizeof(Rva009C8F40Element);
		if (bytes > 0x80)
			operator delete(block);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
	}
}
