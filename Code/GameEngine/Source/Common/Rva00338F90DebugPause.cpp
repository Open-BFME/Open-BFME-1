// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00338F90, 66 bytes.  The body reads a byte flag at this+0x17638 and
// the debug-window module handle at 0x012F0758, then answers from one of two
// state bytes that sit immediately after that handle: +5 when the flag is set
// and +4 when it is clear.  Both are addressed off the one pinned symbol, so
// the body needs no pin of its own.
//
// The shape lever is the width of the two answers.  Retail keeps them one byte
// wide (`test al,al` / `sete al` / `test al,al`), which a `bool`-typed
// conditional does not produce: as `bool` MSVC 7.1 widens each answer with an
// extra `xor eax,eax` and a 32-bit `test eax,eax`, spills the loads into ebx
// and lands seven bytes over.  A byte-typed conditional is exact.

typedef unsigned char UnsignedByte;

extern void *TheScriptDebugWindowDLL;

#define BFME_DEBUG_STATE_SET (*((UnsignedByte *)&TheScriptDebugWindowDLL + 5))
#define BFME_DEBUG_STATE_CLEAR (*((UnsignedByte *)&TheScriptDebugWindowDLL + 4))

class Rva00338F90Host
{
public:
	bool wantsDebugPause();

	unsigned char m_unreconstructed_00[0x17638];
	UnsignedByte m_flag;
};

bool Rva00338F90Host::wantsDebugPause()
{
	return ((m_flag && TheScriptDebugWindowDLL != 0)
			? (UnsignedByte)!BFME_DEBUG_STATE_SET : (UnsignedByte)0)
		|| ((!m_flag && TheScriptDebugWindowDLL != 0)
			? (UnsignedByte)!BFME_DEBUG_STATE_CLEAR : (UnsignedByte)0);
}
