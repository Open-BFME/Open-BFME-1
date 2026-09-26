// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// EvaSideSounds is the retail 16-byte AsciiString-plus-string-vector record.
// The exact push_back at 0x000DED70 and its overflow target at 0x000DEA80
// establish the owning vector instantiation for this adjacent fill-insert body.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct EvaSideSounds
{
	AsciiString m_side;
	std::vector<AsciiString> m_soundNames;
};

template class _STL::vector<EvaSideSounds>;
