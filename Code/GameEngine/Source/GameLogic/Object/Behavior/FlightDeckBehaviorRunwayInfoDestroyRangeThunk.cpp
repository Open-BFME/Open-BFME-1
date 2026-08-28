// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the STLport _Destroy(first, last) instantiated for FlightDeckBehavior::RunwayInfo*,
// retail 0x002BDB00.
//
// Same destroy-the-range loop as the ModelConditionInfo instantiation at
// 0x0013C610: test first != last up front, then call the element destructor
// and step. The stride is what it pins -- **sizeof(RunwayInfo) is 0xb8, 184 bytes**.
//
// The packet names the one-parameter _Destroy overload; the body takes two
// iterators, so the decorated name carries a `0` backreference for the second.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	struct RunwayInfo
	{
		char m_unreconstructed_00[0xb8];
		~RunwayInfo();							///< ILT 0x00036241
	};
};

namespace _STL
{

template <class _Tp>
inline void _Destroy_one(_Tp *__pointer)
{
	__pointer->~_Tp();
}

template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
{
	for ( ; __first != __last; ++__first)
		_Destroy_one(&*__first);
}

template void _Destroy<FlightDeckBehavior::RunwayInfo *>(FlightDeckBehavior::RunwayInfo *, FlightDeckBehavior::RunwayInfo *);

}
