// cl: /O2

namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int bytes);
	};
}

void *operator new(unsigned int bytes);

void *__stdcall Rva00784AD0StlAllocate(unsigned int count, const void *)
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
