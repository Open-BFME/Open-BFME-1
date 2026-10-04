// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: _STL::pair<const UnicodeString, AsciiString> dtor.

#include "ascii_string.h"
#include "unicode_string.h"

// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

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
