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

struct Rva009C91C0Element
{
	char bytes[0x30];
};

// ?Rva009C91C0Release@@YGXPAXI@Z
void __stdcall Rva009C91C0Release(void *block, unsigned int count)
{
	if (block)
	{
		unsigned int bytes = count * sizeof(Rva009C91C0Element);
		if (bytes > 0x80)
			operator delete(block);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
	}
}
