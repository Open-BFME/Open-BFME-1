// Three 20-byte __cdecl INI field-parse callbacks that set one flag on the
// instance and then TAIL-JUMP into the ordinary integer parser.
//
// Retail (0x00606890, 0x00607970, 0x00607DE0):
//
//     mov eax,[esp+8]
//     mov byte ptr [eax+<OFF>],1
//     mov [esp+8],eax
//     jmp 0x00852A60
//
// WHAT THE BYTES SHOW.  Nothing is popped and no frame is set up, so this is
// __cdecl; the jump target is `?parseInt@INI@@SAXPAV1@PAX1PBX@Z`, already in
// the ledger at 0x00852A60, which fixes the parameter list at four dwords --
// (INI *, void *instance, void *store, const void *userData) -- because a tail
// JUMP can only reuse a frame whose arguments are laid out exactly like the
// caller's.  `[esp+8]` is therefore `instance`, the second of the four.
//
// THE REDUNDANT WRITE-BACK IS THE EVIDENCE.  `mov [esp+8],eax` stores the value
// it just loaded from that same slot.  Passing `instance` through unchanged
// needs no store at all -- the slot already holds it -- so the store means the
// source did NOT pass `instance`: it passed a differently-typed expression that
// the compiler had to materialise into the argument slot.  The only such
// expression in evidence is the typed pointer the line above dereferenced.  So
// the body casts `instance` once, writes through the cast, and passes the CAST
// pointer on.
//
// THE FLAG IS ONE BYTE AND ITS VALUE IS ONE, written with an immediate rather
// than through a register, so it is a plain assignment of a true constant to a
// byte-wide field; the offsets are 0x1EC, 0x1D0 and 0x20C.  Three different
// offsets is three different classes -- one layout cannot put its flag in three
// places -- and each is sized here only far enough to place its own flag.
//
// IDENTITY IS NOT RECOVERED.  The callback names and the instance types are
// derived from addresses; `char m_pad[]` carries an offset and nothing else,
// and nothing here shows which INI field any of the three parses.

class INI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );
};

#define U4_INI_FLAG_PARSER( ROW, OFFSET )                                     \
	struct U4Inst##ROW                                                        \
	{                                                                         \
		char m_pad[ OFFSET ];                                                 \
		unsigned char m_flag;                                                 \
	};                                                                        \
	void u4IniFlag##ROW( INI *ini, void *instance, void *store,               \
	                     const void *userData )                               \
	{                                                                         \
		U4Inst##ROW *self = (U4Inst##ROW *)instance;                          \
		self->m_flag = 1;                                                     \
		INI::parseInt( ini, self, store, userData );                          \
	}

U4_INI_FLAG_PARSER( 00606890, 0x1EC )
U4_INI_FLAG_PARSER( 00607970, 0x1D0 )
U4_INI_FLAG_PARSER( 00607DE0, 0x20C )
