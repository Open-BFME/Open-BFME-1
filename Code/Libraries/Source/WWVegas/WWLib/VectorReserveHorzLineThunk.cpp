// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DiscreteCircle.h
struct HorzLine
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	void reserve(unsigned int);
};

class HorzLineVectorReserveShim
{
public:
	void reserve(unsigned int n);
};

template <class Type, class Allocator>
void vector<Type, Allocator>::reserve(unsigned int n)
{
	((HorzLineVectorReserveShim *)this)->reserve(n);
}

template void vector<HorzLine, allocator<HorzLine> >::reserve(unsigned int);
}
