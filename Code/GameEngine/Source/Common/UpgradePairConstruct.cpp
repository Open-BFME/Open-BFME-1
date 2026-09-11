// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the out-of-line STLport placement copy for upgradePair.
//
// AutoDepositUpdate.h defines upgradePair as a narrow STLport string followed
// by an Int. The retail body at 0x00647C60 calls the narrow basic_string copy
// thunk at 0x0001CB11 and then copies the trailing amount at +0xc.

#include <memory>

namespace _STL
{

template <class T>
class char_traits
{
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const basic_string &);
	~basic_string(void);

private:
	char m_body[12];
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>,
	_STL::allocator<char> > BfmeNarrowString;

struct upgradePair
{
	BfmeNarrowString type;
	int amount;
};

template void _STL::_Construct(upgradePair *, const upgradePair &);
