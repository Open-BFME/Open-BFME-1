// Retail 0x000E4520 allocates twelve-byte elements with STLport's threshold.

namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int bytes);
	};
}

void *operator new(unsigned int bytes);

// ?Rva000E4520StlAllocate@@YGPAXIPBX@Z
void *__stdcall Rva000E4520StlAllocate(unsigned int count, const void *)
{
	if (count != 0)
	{
		unsigned int bytes = count * 12;
		if (bytes > 0x80)
			return ::operator new(bytes);

		return _STL::__new_alloc::allocate(bytes);
	}

	return 0;
}
