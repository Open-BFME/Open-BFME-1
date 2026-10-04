// ?Rva0002032EBitFlagsParseThunk@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

// Retail keeps the four parseFromINI arguments on the caller's stack and
// enters the existing BitFlags<116> body through this five-byte tail thunk.
// The thunk itself takes no arguments, so the body is reached by handing the
// compiler B's address in a zero-argument shape: /O2 folds the call through
// that constant pointer into `jmp ?parseFromINI@?$BitFlags@$0HE@@...`, which is
// what retail links here. A direct four-argument call would push the arguments
// and break the caller's stack contract, so the cast is load-bearing.

class INI;

template <int NUMBITS>
class BitFlags
{
public:
	// defined in game/GameEngine/Source/Common/BitFlagsParseFromINI.cpp
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

template <>
void BitFlags<116>::parseFromINI(INI *, void *, void *, const void *);

typedef void (__cdecl *BitFlagsParseFromINIFn)();

void Rva0002032EBitFlagsParseThunk()
{
	((BitFlagsParseFromINIFn)&BitFlags<116>::parseFromINI)();
}
