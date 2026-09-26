// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

struct BfmeRva449E0Key
{
	int m_key;
};

bool operator<(const BfmeRva449E0Key &left,
	const BfmeRva449E0Key &right)
{
	return left.m_key < right.m_key;
}

struct BfmeRva449E0Value
{
	BfmeRva449E0Value(void);
	unsigned char m_data[16];
};

class Rva002449E0
{
public:
	BfmeRva449E0Value &lookup(const BfmeRva449E0Key &key);

	_STL::map<BfmeRva449E0Key, BfmeRva449E0Value> m_map;
};

namespace _STL
{
template <>
__declspec(noinline) pair<const BfmeRva449E0Key,
	BfmeRva449E0Value>::pair(const BfmeRva449E0Key &firstValue,
	const BfmeRva449E0Value &secondValue);
}

template BfmeRva449E0Value &
_STL::map<BfmeRva449E0Key, BfmeRva449E0Value>::operator[](
	const BfmeRva449E0Key &key);

BfmeRva449E0Value &Rva002449E0::lookup(
	const BfmeRva449E0Key &key)
{
	return m_map[key];
}
