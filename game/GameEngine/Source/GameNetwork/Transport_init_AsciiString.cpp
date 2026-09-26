// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Transport::init(AsciiString, UnsignedShort), 0x00684490, 127 bytes.
//
// Its own translation unit rather than a body in Transport.cpp, for the reason
// the note there recorded: retail calls AsciiString's copy constructor OUT OF
// LINE to build ResolveIP's by-value argument, and the AsciiString every
// GameEngine header in the tree hands Transport.cpp defines that constructor
// inline, so the copy happens in place and the SEH prologue lands six bytes
// off. inputs/reference/shims/stringbaseascii is the cure -- its copy constructor is
// a visible delegation to StringBase<char>'s, which is declared and never
// defined, so the call goes out of line to the retail body at 0x00887B60 and
// the __$SEHRec$ store precedes `mov ecx, esp` exactly as retail has it.
//
// Identity: the body resolves an AsciiString host through ResolveIP
// (0x00682EF0), drops the result and the caller's port into an eight-byte
// TransportAddress on the stack, and tail-forwards to
// Transport::init(const TransportAddress *) at 0x00684200 -- which is the
// reference's two-overload init pair with BFME's address-struct signature
// substituted for the reference's (UnsignedInt, UnsignedShort).
//
// Only what this body touches is declared: Transport's other members would
// drag in the whole shim header set for nothing, and the address struct is
// only ever passed by pointer here, so its two fields at +0 and +4 are all
// that has to be right.

#include "Common/AsciiString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct TransportAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

UnsignedInt ResolveIP(AsciiString host);

class Transport
{
public:
	Bool init(const TransportAddress *addr);
	Bool init(AsciiString ip, UnsignedShort port);
};

Bool Transport::init(AsciiString ip, UnsignedShort port)
{
	TransportAddress addr;
	addr.ip = ResolveIP(ip);
	addr.port = port;
	return init(&addr);
}
