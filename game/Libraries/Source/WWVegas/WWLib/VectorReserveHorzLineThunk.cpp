// Native retail row target; typed member route preserves the observed thiscall ABI.
extern "C" void __identifier("?reserve@?$vector@UGen_t_00068fa0_p12cd@@V?$allocator@UGen_t_00068fa0_p12cd@@@_STL@@@_STL@@QAEXI@Z")();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DiscreteCircle.h
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

template <class Type, class Allocator>
void vector<Type, Allocator>::reserve(unsigned int n)
{
	union
	{
		void (*address)();
		void (vector<Type, Allocator>::*member)(unsigned int);
	} route = { __identifier("?reserve@?$vector@UGen_t_00068fa0_p12cd@@V?$allocator@UGen_t_00068fa0_p12cd@@@_STL@@@_STL@@QAEXI@Z") };
	(this->*route.member)(n);
}

template void vector<HorzLine, allocator<HorzLine> >::reserve(unsigned int);
}
