// cl: /EHs-c-
//
// Two heap allocations followed by a constructor -- MSVC 7.1's whole `new T`
// sequence, and nothing else.
//
// 0x005EA530 (34 bytes):
//
//     push esi / push 0xB0 / mov esi,ecx / call ??2@YAPAXI@Z / add esp,4
//     test eax,eax / je NULL / push esi / mov ecx,eax / call <CTOR>
//     pop esi / ret
//     NULL: xor eax,eax / pop esi / ret
//
// WHAT THE BYTES SHOW.  `operator new` is called with a literal size, its
// result is tested, and on success it becomes the `this` of a __thiscall
// constructor whose one argument is the RECEIVER OF THIS FUNCTION.  That
// null-test-then-construct, with a `xor eax,eax` arm that returns the null the
// allocator gave back, is exactly what MSVC 7.1 emits for `new T(args)` under
// the non-throwing operator new this image links -- the source contains no test
// of its own.  0xB0 is `sizeof(T)`, and the object being constructed is
// returned unchanged, so the whole body is `return new T(this);`.
//
// 0x0060CD80 (56 bytes) allocates 0x74 the same way and then does two more
// things with the result:
//
//     ... new (0x74) ... / mov esi,eax  (or esi=0)
//     mov ecx,[esp+8] / push <TABLE> / push esi
//     call ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z
//     mov eax,[<GLOBAL>] / mov [eax+0x28C],esi / pop esi / ret
//
// `initFromINI` is already in the ledger at 0x008520A0 and is __thiscall on an
// `INI *`; the receiver it gets is this function's only stack argument, so this
// is an INI block handler.  Its two pushed arguments are the fresh object and a
// .rdata address -- a `FieldParse` table -- in that order.  Then a global
// pointer is loaded and the fresh object is parked at +0x28C of whatever it
// points at.  The `eb 02 / xor esi,esi` merge is the same allocator null arm as
// above, here folded into a register rather than duplicated returns because the
// tail is shared.
//
// EXCEPTION FLAGS ARE EVIDENCE.  Under the project default (`-EHsc-`, which cl
// reads as EHs ON) both bodies gain a three-push fs:[0] frame and, in
// 0x0060CD80, an EH-state store around the constructed object -- 62 and 50
// bytes of difference.  Retail has neither, hence this file's `/EHs-c-`.
//
// IDENTITY IS NOT RECOVERED.  Both constructors are pinned by the addresses
// their REL32s resolve to; the FieldParse table and the global are DIR32
// operands copied from retail; `char m_body[]` carries only the size
// `operator new` was asked for.

class U4Made005EA530;
class U4Maker005EA530
{
public:
	U4Made005EA530 *make( void );
};

class U4Made005EA530
{
public:
	U4Made005EA530( U4Maker005EA530 *owner );
	char m_body[ 0xB0 ];
};

U4Made005EA530 *U4Maker005EA530::make( void )
{
	return new U4Made005EA530( this );
}

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI( void *what, const FieldParse *parse );
};

class U4Thing0060CD80
{
public:
	U4Thing0060CD80();
	char m_body[ 0x74 ];
};

struct U4Store0060CD80
{
	char m_pad[ 0x28C ];
	U4Thing0060CD80 *m_thing;
};

extern U4Store0060CD80 *g_u4Store0060CD80;
extern const FieldParse g_u4FieldParse0060CD80[];

void u4Parse0060CD80( INI *ini )
{
	U4Thing0060CD80 *thing = new U4Thing0060CD80;
	ini->initFromINI( thing, g_u4FieldParse0060CD80 );
	g_u4Store0060CD80->m_thing = thing;
}
