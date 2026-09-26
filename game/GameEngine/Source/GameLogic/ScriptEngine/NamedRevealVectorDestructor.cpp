// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Iinputs/reference/shims/stringinline
// stlport
// The ScriptEngine named-reveal vector uses a sixteen-byte NamedReveal record.
// Its three AsciiString members occupy offsets 0x00, 0x04, and 0x0C.

#include <vector>

#include "StringInline.h"

struct NamedReveal
{
	AsciiString m_revealName;
	AsciiString m_waypointName;
	float m_radiusToReveal;
	AsciiString m_playerName;
};

template class _STL::vector<NamedReveal>;
