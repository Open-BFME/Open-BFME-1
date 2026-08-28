// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: four tiny INI parse callbacks, 34 or 35 bytes.  Retail:
//
//     push ecx                              ; one local, 1 or 4 bytes
//     mov ecx,[esp+8]                       ; the INI*
//     push 0 ; lea eax,[esp+<L>] ; push eax ; push 0 ; push ecx
//     call ?parseBool@INI@@SAXPAV1@PAX1PBX@Z    ; or parseInt
//     mov edx,[esp+0x1C]                    ; the INSTANCE, not the store
//     mov al,[esp+0x13] ; mov [edx+<N>],al  ; or the dword form
//     add esp,0x14 ; ret
//
// WHAT THE BYTES SHOW.  `ret` with no operand and four argument slots read from
// [esp+4] upward: a __cdecl function with the INI parse-callback signature
// `void (INI *, void *instance, void *store, const void *userData)`.  It runs
// one of INI's own scalar parsers into a LOCAL and then copies that local into
// the second argument -- the instance -- at a fixed offset.  The `store`
// argument is never read, which is what makes these hand-written callbacks
// rather than plain `{ "X", INI::parseBool, NULL, offsetof(...) }` rows.
//
// THE KEYWORDS COME FROM THE TABLE AT 0x00C83270, five contiguous rows:
// Human, Computer, LoadAIScripts, ForcePlayerTeam and AllowedFactions, each
// `{ keyword, <parse thunk>, 0, 0 }` with a zero offset -- the zero offset is
// the same fact from the other side, since a table-driven field would carry
// one.  The first four are these bodies; AllowedFactions is 227 bytes and is
// not converted here.
//
// THE OFFSETS ARE 0, 1, 2 AND 4, so the three flags are one byte each and share
// a dword with nothing, and the fourth field is an Int.  The local for a flag is
// one byte -- `lea eax,[esp+7]` inside the four-byte slot `push ecx` reserved --
// and for the Int it is the whole slot.  That one-byte local is what makes Bool
// a byte type here.
//
// IDENTITY IS NOT RECOVERED beyond the keywords: nothing here names the struct
// the instance points at, so its fields carry the keyword and its offset.

typedef int Int;
typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	static void parseBool( INI *, void *, void *, const void * );
	static void parseInt( INI *, void *, void *, const void * );
};

struct SideFlags
{
	Bool m_human;			// +0
	Bool m_computer;		// +1
	Bool m_loadAIScripts;	// +2
	Int m_forcePlayerTeam;	// +4
};

void parseHuman( INI *ini, void *instance, void *, const void * )
{
	Bool value;
	INI::parseBool( ini, 0, &value, 0 );
	( (SideFlags *)instance )->m_human = value;
}

void parseComputer( INI *ini, void *instance, void *, const void * )
{
	Bool value;
	INI::parseBool( ini, 0, &value, 0 );
	( (SideFlags *)instance )->m_computer = value;
}

void parseLoadAIScripts( INI *ini, void *instance, void *, const void * )
{
	Bool value;
	INI::parseBool( ini, 0, &value, 0 );
	( (SideFlags *)instance )->m_loadAIScripts = value;
}

void parseForcePlayerTeam( INI *ini, void *instance, void *, const void * )
{
	Int value;
	INI::parseInt( ini, 0, &value, 0 );
	( (SideFlags *)instance )->m_forcePlayerTeam = value;
}
