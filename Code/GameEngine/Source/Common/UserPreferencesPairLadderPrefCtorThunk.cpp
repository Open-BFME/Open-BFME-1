// cl: /DNDEBUG /MD /EHsc

class LadderPref
{
public:
	LadderPref(const LadderPref &);
};

namespace _STL
{
template <class First, class Second>
class pair
{
public:
	First first;
	Second second;
	pair(const First &, const Second &);
};

template <>
pair<const long, LadderPref>::pair(const long &a, const LadderPref &b)
	: first(a), second(b)
{
}
}

template class _STL::pair<const long, LadderPref>;
