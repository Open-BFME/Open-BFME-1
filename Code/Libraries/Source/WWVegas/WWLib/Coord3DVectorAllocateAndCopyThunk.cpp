// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport Coord3D vector allocation and copy helper.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

namespace _STL
{
struct __false_type {};

void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
Coord3D *__cdecl coord3DUninitializedCopy(const Coord3D *first,
	const Coord3D *last, Coord3D *result, const __false_type &);

template <class Type>
class allocator {};

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

	__false_type tag;
	coord3DUninitializedCopy(first, last, result, tag);
	return result;
}

template Coord3D *vector<Coord3D, allocator<Coord3D> >::_M_allocate_and_copy<const Coord3D *>(
	unsigned int, const Coord3D *, const Coord3D *);
}
