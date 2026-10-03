// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: _STL::pair<const UnicodeString, AsciiString> dtor.

#include "ascii_string.h"
#include "unicode_string.h"

namespace _STL
{
template <class _T1, class _T2>
struct pair
{
	~pair();
	_T1 first;
	_T2 second;
};
}

// ??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ
_STL::pair<const UnicodeString, AsciiString>::~pair()
{
}
