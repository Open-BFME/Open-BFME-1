// ?Rva004F1210Deallocate@@YGXPAXI@Z
// cl: /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *pointer, UnsignedInt size);
};
}

void operator delete(void *pointer);

// The caller evidence proves a two-argument allocator helper. Its semantic
// owner remains unknown, so the function keeps the retail address in its name.
void __stdcall Rva004F1210Deallocate(void *pointer, UnsignedInt count)
{
	if (pointer != 0)
	{
		UnsignedInt bytes = count * 0x338;

		if (bytes > 0x80)
		{
			operator delete(pointer);
			return;
		}

		_STL::__node_alloc<true, 0>::_M_deallocate(pointer, bytes);
	}
}
