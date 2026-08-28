// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: _STL::__copy<NamedReveal *, NamedReveal *, int>, retail
// 0x0033A9F0, 91 bytes. The body carried only a machine byte-dump row; the
// symbols.csv pin fronts it from the ILT at 0x0004A1E7, which the tail shift of
// ScriptEngine::removeNamedMapReveal uses.
//
// The element is sixteen bytes -- the range is divided by a shift of four --
// and the inlined assignment is what pins its shape: an operator= on +0x00 and
// +0x04, a plain dword copy at +0x08, and another operator= on +0x0C. That is
// the same three-AsciiStrings-and-a-word layout the destructor at 0x00339C30,
// already ledgered, tears down at +0x0C, +0x04 and +0x00.
//
// The assignment is the compiler-generated one: it copies the members in
// declaration order and there is no user operator= to be seen in the bytes.
//
// The address is taken rather than called so MSVC emits the inline template out
// of line without an inline_depth pragma, which would also stop the element's
// assignment from folding into the loop the way retail has it.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);	// retail 0x00887C90

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
struct NamedReveal
{
	AsciiString m_bfmeName;					// +0x00
	AsciiString m_bfmeWaypoint;				// +0x04
	int m_bfmeWord;						// +0x08
	AsciiString m_bfmePlayer;				// +0x0C
};

typedef NamedReveal *(*BfmeNamedRevealCopyFn)(NamedReveal *, NamedReveal *,
	NamedReveal *, const _STL::random_access_iterator_tag &, int *);

BfmeNamedRevealCopyFn BfmeNamedRevealCopyAnchor =
	&_STL::__copy<NamedReveal *, NamedReveal *, int>;
