// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h
struct MinefieldBehavior
{
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h
	struct DetonatorInfo
	{
	};
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class MinefieldBehaviorDetonatorInfoInsertOverflowShim
{
public:
	void insert_overflow(MinefieldBehavior::DetonatorInfo *pos, const MinefieldBehavior::DetonatorInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<MinefieldBehavior::DetonatorInfo, allocator<MinefieldBehavior::DetonatorInfo> >::_M_insert_overflow(
	MinefieldBehavior::DetonatorInfo *pos, const MinefieldBehavior::DetonatorInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((MinefieldBehaviorDetonatorInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
