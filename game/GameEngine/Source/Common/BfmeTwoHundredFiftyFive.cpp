// cl: /Od
// stlport
// A run named by its start and length passed on as a pair of ends, built
// without optimisation. The frame holds something this body never names.

namespace _STL
{
template <class T> class char_traits;
template <class T> class allocator;

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string &assign(const CharT *first, const CharT *last);
};
}

class BfmeThingOT
{
public:
	void bfmeSetOT(char *at, int many);
};

void BfmeThingOT::bfmeSetOT(char *at, int many)
{
	unsigned char spare[0x68];

	reinterpret_cast<_STL::basic_string<char, _STL::char_traits<char>,
		_STL::allocator<char> > *>(this)->assign(
		static_cast<const char *>(at), static_cast<const char *>(at + many));
}
