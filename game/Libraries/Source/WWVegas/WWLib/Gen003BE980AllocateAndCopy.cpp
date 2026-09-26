// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003BE980 is the STLport vector<Gen_t_003c0ce0_p2pod>
// _M_allocate_and_copy body called by reserve in tgrid_114.cpp. The
// Gen_t_003c0ce0_p2pod record is two bytes wide, so the allocator branches and
// the copy loop both use a two-byte stride. The retail calls at 0x00881F30 and
// 0x0082E540 select the large and small allocation paths.

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(
	unsigned int count, Iterator first, Iterator last)
{
	Type *result;
	if (count)
	{
		unsigned int bytes = count * sizeof(Type);
		if (bytes > 128)
			result = (Type *)vectorLargeAllocate(bytes);
		else
			result = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		result = 0;
	}

	Type *source = first;
	Type *end = last;
	if (source != end)
	{
		int offset = (char *)result - (char *)source;
		do
		{
			if ((Type *)((char *)source + offset) != 0)
				*(short *)((char *)source + offset) = source->a;
			++source;
		}
		while (source != end);
	}
	return result;
}
}

struct Gen_t_003c0ce0_p2pod
{
	short a;
};

template Gen_t_003c0ce0_p2pod *_STL::vector<Gen_t_003c0ce0_p2pod,
	_STL::allocator<Gen_t_003c0ce0_p2pod> >::_M_allocate_and_copy<
	Gen_t_003c0ce0_p2pod *>(unsigned int, Gen_t_003c0ce0_p2pod *,
	Gen_t_003c0ce0_p2pod *);
