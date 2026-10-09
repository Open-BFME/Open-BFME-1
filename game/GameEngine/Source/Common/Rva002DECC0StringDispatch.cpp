// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>
// Retail 0x002DECC0. Its owner identity is unresolved, so keep it RVA-qualified.
#include "ascii_string.h"

class Rva002DECC0Owner
{
public:
	void dispatch(unsigned unused, class Rva001BE220Receiver *receiver);

	unsigned char m_pad00[0x58];
	_STL::vector<AsciiString> m_strings;
	unsigned m_ownerWord;
};

class Rva001BE220Receiver
{
public:
	void dispatch(int bit, unsigned ownerWord);
};

int __cdecl Rva001C0930FindNameIndex(const char *name);

// Matched ledger row at RVA 0x001C0930, reached through ILT 0x000190F1.
// Its object defines BitFlags<304>::getSingleBitFromName (BitFlags<304> is
// spelled ?$BitFlags@$0BDA@@ in the mangled name).
template<int Bits> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

// Matched ledger row at RVA 0x001BE220, reached through ILT 0x0002852E.
class Rva001BE220
{
public:
	void invoke();
};

// The 0x1BE220 body is a __thiscall pointer tail-jump thunk; its name encodes
// no parameters, but its tail callee consumes the caller's signed bit and
// unsigned owner word (ret 8). Reach the body through that name while passing
// the two arguments the retail call site pushes.
typedef void (Rva001BE220::*Rva001BE220InvokeFn)(int bit, unsigned ownerWord);

void Rva002DECC0Owner::dispatch(unsigned, Rva001BE220Receiver *receiver)
{
	Rva001BE220Receiver *target = receiver;
	if (target == 0)
		return;

	Rva001BE220InvokeFn invoke = (Rva001BE220InvokeFn)&Rva001BE220::invoke;

	for (unsigned i = 0;
		 i < m_strings.size();
		 ++i)
	{
		AsciiString local = m_strings[i];
		int bit = BitFlags<304>::getSingleBitFromName(local.str());
		(((Rva001BE220 *)target)->*invoke)(bit, m_ownerWord);
	}
}
