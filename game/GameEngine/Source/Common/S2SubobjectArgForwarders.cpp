// Two __cdecl two-argument functions that hand their second argument to a
// __thiscall member of a sub-object of their first:
//
//     mov eax,[esp+8] / mov ecx,[esp+4] / push eax / add ecx,<OFFSET>
//     call <REL32> / ret
//
// WHAT THE BYTES SHOW.  The receiver is formed by loading the owner into ecx
// and ADDING the offset, not by `lea ecx,[reg+OFFSET]` off a separate copy:
// that is the encoding you get when the source names the owner ONCE, so the
// expression is not independent and there is nothing for the compiler to fold.
// The callee is reached with one dword on the stack and the caller pops
// nothing, so it is __thiscall with a single argument.  Nothing is popped after
// the call and nothing is done with eax, so this function returns void.
//
// ONE CALLEE, TWO OFFSETS: 0x0C and 0x04, both through the thunk at 0x0001581B
// (body 0x00065090), so one sub-object class covers both rows.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived and the forwarded
// argument is typed as an opaque pointer because it is only ever a dword.

class GenForwardedArg
{
public:
	int m_x;
};

class Gen0001581B
{
public:
	void take( GenForwardedArg *a );
};

#define BFME_SUBOBJECT_ARG_FORWARDER( NAME, OFFSET )                      \
	class NAME##Owner                                                     \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		Gen0001581B m_sub;                                                \
	};                                                                    \
	void NAME( NAME##Owner *owner, GenForwardedArg *a )                   \
	{                                                                     \
		owner->m_sub.take( a );                                           \
	}

// @?Rva003B7140@@YAXPAVRva003B7140Owner@@PAVGenForwardedArg@@@Z 0x003B7140
BFME_SUBOBJECT_ARG_FORWARDER( Rva003B7140, 0x04 )
// @?Rva003B70F0@@YAXPAVRva003B70F0Owner@@PAVGenForwardedArg@@@Z 0x003B70F0
BFME_SUBOBJECT_ARG_FORWARDER( Rva003B70F0, 0x0C )
