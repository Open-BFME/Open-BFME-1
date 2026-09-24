// Nine twenty-one-byte __cdecl functions with one shape:
//
//     mov ecx,[<GLOBAL>] / test ecx,ecx / jz ret
//     mov eax,[esp+4] / push eax / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  A global POINTER VARIABLE is loaded (a `mov ecx,[abs]`
// -- the dereference of a variable, not the address of one), tested, and used
// as the receiver of a __thiscall call that takes this function`s single
// stacked argument.  The argument is read from [esp+4] and never cleaned up by
// this function, and the function itself does not adjust esp on return, so this
// side is __cdecl and the callee pops the pushed dword itself.  When the global
// is null the function returns having done nothing.
//
// TWO AXES: the global and the callee.  EIGHT of the nine load the SAME global
// and reach EIGHT DIFFERENT callees; the ninth (Rva005091B0) loads a different
// global and a different callee.  That is why there are two receiver classes
// here and not one: two distinct addresses at the same relocation site mean two
// distinct types, and collapsing them would still byte-match -- the patcher
// copies the DIR32 operand out of retail -- while asserting an identity the
// bytes do not support.  verify_dir32_consistency, not the byte gate, is what
// enforces that.
//
// WHAT THE BYTES CANNOT DECIDE.  THE FOUR RELOCATED BYTES OF EACH GLOBAL ARE
// NOT EVIDENCE.  What is evidence is which sites SHARE them.  The forwarded
// argument is spelled `int`; a pointer compiles the same.  The eight methods
// are grouped onto one class only because they share one receiver global -- the
// bytes say nothing about whether they are virtual, or in what order they are
// declared.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

class Q1Receiver0134FAAC
{
public:
	void m009F19E0( int value );
	void m009F1A60( int value );
	void m009F0BD0( int value );
	void m009F0D40( int value );
	void m009EEEC0( int value );
	void m009EC970( int value );
	void m009EC9A0( int value );
	void m009ECA30( int value );
};

extern Q1Receiver0134FAAC *g_q1Receiver0134FAAC;

class Q1Receiver012F4820
{
public:
	void m0003CAD3( int value );
};

extern Q1Receiver012F4820 *g_q1Receiver012F4820;

#define Q1_GLOBAL_GUARDED_FORWARD( NAME, GLOBAL, METHOD )                 \
	void NAME( int value );                                               \
	void NAME( int value )                                                \
	{                                                                     \
		if ( GLOBAL )                                                     \
		{                                                                 \
			GLOBAL->METHOD( value );                                      \
		}                                                                 \
	}

Q1_GLOBAL_GUARDED_FORWARD( Rva009EBA80, g_q1Receiver0134FAAC, m009F19E0 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBAA0, g_q1Receiver0134FAAC, m009F1A60 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBAC0, g_q1Receiver0134FAAC, m009F0BD0 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBB20, g_q1Receiver0134FAAC, m009F0D40 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBBC0, g_q1Receiver0134FAAC, m009EEEC0 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBBE0, g_q1Receiver0134FAAC, m009EC970 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBC00, g_q1Receiver0134FAAC, m009EC9A0 )
Q1_GLOBAL_GUARDED_FORWARD( Rva009EBC50, g_q1Receiver0134FAAC, m009ECA30 )
Q1_GLOBAL_GUARDED_FORWARD( Rva005091B0, g_q1Receiver012F4820, m0003CAD3 )
