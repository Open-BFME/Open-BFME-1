// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaSideSounds
{
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
	void _M_insert_overflow(Type *, Type const &, __false_type const &, unsigned int, bool);
};

class EvaSideSoundsInsertOverflowShim
{
public:
	void insert_overflow(EvaSideSounds * pos, const EvaSideSounds & x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<EvaSideSounds, allocator<EvaSideSounds> >::_M_insert_overflow(
	EvaSideSounds * pos, const EvaSideSounds & x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((EvaSideSoundsInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
