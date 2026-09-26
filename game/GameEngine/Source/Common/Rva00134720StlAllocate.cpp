// Retail 0x00134720 allocates four-byte elements with STLport's threshold.

namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int bytes);
	};
}

void *operator new(unsigned int bytes);

void *__stdcall Rva00134720StlAllocate(unsigned int count, const void *)
{
	if (count != 0)
	{
		unsigned int bytes = count * 4;
		if (bytes > 0x80)
			return ::operator new(bytes);

		return _STL::__new_alloc::allocate(bytes);
	}

	return 0;
}
