// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_USE_NEWALLOC 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

typedef int Int;

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	MultiplayerColorDefinition(const MultiplayerColorDefinition &other);
	~MultiplayerColorDefinition();

private:
	unsigned char m_data[0x24];
};

namespace _STL
{
	template <>
	__declspec(noinline) pair<const Int, MultiplayerColorDefinition>::pair(
		const Int &firstValue, const MultiplayerColorDefinition &secondValue);
}

template MultiplayerColorDefinition &
_STL::map<Int, MultiplayerColorDefinition>::operator[](const Int &key);
