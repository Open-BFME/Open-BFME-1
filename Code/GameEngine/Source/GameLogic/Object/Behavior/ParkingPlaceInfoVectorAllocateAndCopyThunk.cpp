// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport ParkingPlaceInfo vector allocation and copy helper.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
class ParkingPlaceBehavior
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
	struct ParkingPlaceInfo
	{
	private:
		unsigned char m_data[0x3c];
	};
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

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
