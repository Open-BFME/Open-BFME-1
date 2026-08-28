// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapObject.h
class MapObject
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionCell
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class SightingInfo
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(Type const &);
};

class DequePushBackAuxVThunkShim
{
public:
	void push_back_aux(void const *x);
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(Type const &x)
{
	((DequePushBackAuxVThunkShim *)this)->push_back_aux((void const *)&x);
}
template void deque<MapObject *, allocator<MapObject *> >::_M_push_back_aux_v(MapObject * const &);
template void deque<PartitionCell *, allocator<PartitionCell *> >::_M_push_back_aux_v(PartitionCell * const &);
template void deque<SightingInfo *, allocator<SightingInfo *> >::_M_push_back_aux_v(SightingInfo * const &);
}
