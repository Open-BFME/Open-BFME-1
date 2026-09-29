// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport ParkingPlaceInfo vector allocation and copy helper.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
class ParkingPlaceBehavior
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
	struct ParkingPlaceInfo
	{
	private:
		unsigned char m_data[0x3c];
	};
};

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

template <class T1, class T2>
void _Construct(T1 *destination, const T2 &value);

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

	if (first != last)
	{
		int offset = (char *)result - (char *)first;
		do
		{
			_Construct((Type *)((char *)first + offset), *first);
			++first;
		}
		while (first != last);
	}
	return result;
}

template ParkingPlaceBehavior::ParkingPlaceInfo *vector<
	ParkingPlaceBehavior::ParkingPlaceInfo,
	allocator<ParkingPlaceBehavior::ParkingPlaceInfo>
>::_M_allocate_and_copy<ParkingPlaceBehavior::ParkingPlaceInfo *>(
	unsigned int, ParkingPlaceBehavior::ParkingPlaceInfo *, ParkingPlaceBehavior::ParkingPlaceInfo *);
}
