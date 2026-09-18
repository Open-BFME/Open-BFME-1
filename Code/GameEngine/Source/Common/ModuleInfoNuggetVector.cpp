// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Only the 87-byte copy at 0x00770E00 remains here. It assigns a string at
// +0, a vector<AsciiString> at +4, and a word at +0x10. The unrelated clear
// at 0x00771D00 belongs to Containers/Rva0013B8F0Vector.cpp.
// ModuleInfo::Nugget is a legacy emitter spelling, not proven type identity;
// this string/vector family is reserved for the following identity cleanup.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

class ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString first;
		_STL::vector<AsciiString> m_bfmeStrings;
		int m_bfmeTail;
	};
};

template ModuleInfo::Nugget *
_STL::__copy<ModuleInfo::Nugget *, ModuleInfo::Nugget *, int>(
	ModuleInfo::Nugget *, ModuleInfo::Nugget *, ModuleInfo::Nugget *,
	const _STL::random_access_iterator_tag &, int *);
