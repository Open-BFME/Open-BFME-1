// Five 55-byte __cdecl forwarders, each taking a pointer to a two-word string
// handle and pushing a fixed literal plus that string's characters into a
// global sink:
//
//     eax = [arg+0]                     ; the handle's one and only field
//     eax = eax ? eax + 8 : ""          ; branchy, both arms feed the push
//     ecx = [CONTEXT]
//     push 0 / 0 / 0 / 0 / eax / 1 / <literal> / ecx
//     ecx = [SINK] ; call <REL32>       ; no stack cleanup at our end
//
// WHAT THE BYTES SHOW.  The string handle is ONE dword and the characters live
// EIGHT bytes past what it points at, with a null handle substituting the empty
// string -- that is a refcounted-buffer handle whose header is two words and
// whose accessor is INLINE, because there is no call: the whole conditional is
// spliced into the caller.  The empty-string arm loads an address, not zero, so
// the fallback is a real "" in .rdata (the gate's string-ref check verifies it).
//
// Eight dwords are pushed and NOBODY pops them here, while ecx is loaded from a
// second global immediately before the call: __thiscall, eight stack arguments,
// callee-cleanup.  Our own `ret` is bare and our argument is read from [esp+4]
// before any push, so WE are __cdecl with one pointer argument.
//
// ONE AXIS: the literal.  Recovered from retail -- "SetPlayerFaction",
// "CreateButtonFlash", "DeleteButtonFlash", "ShowButtonFlash",
// "HideButtonFlash".  Sink, context, callee, the constant 1 and the four
// trailing zeros are identical in all five rows.
//
// IDENTITY IS NOT RECOVERED.  The handle's two header words are declared as
// two ints because their WIDTH is all the bytes fix -- nothing reads them.  The
// sink, the context and the eight parameter types are address-derived guesses
// constrained only by width and by the calling convention above.

struct GenStringData { int m_refCount; int m_allocated; };

class GenString
{
public:
	const char *str() const { return m_data ? (const char *)( m_data + 1 ) : ""; }
	GenStringData *m_data;
};

class GenActionSink
{
public:
	void add( void *ctx, const char *name, int kind, const char *value,
	          int a, int b, int c, int d );
};

extern GenActionSink *TheGenActionSink;
extern void *TheGenActionContext;

#define S3_ACTION( NAME, TEXT )                                           \
	void NAME( const GenString *value )                                   \
	{                                                                     \
		TheGenActionSink->add( TheGenActionContext, TEXT, 1,              \
			value->str(), 0, 0, 0, 0 );                                   \
	}

S3_ACTION( Rva00565D00, "SetPlayerFaction" )
S3_ACTION( Rva00565D50, "CreateButtonFlash" )
S3_ACTION( Rva00565DA0, "DeleteButtonFlash" )
S3_ACTION( Rva00565E90, "ShowButtonFlash" )
S3_ACTION( Rva00565EE0, "HideButtonFlash" )
