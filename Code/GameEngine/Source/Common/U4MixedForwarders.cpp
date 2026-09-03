// cl: /EHs-c-
//
// Six unrelated small bodies from the 0x005E97B0..0x0060D680 slice, grouped
// only because each is decided by its own bytes plus one pinned callee.
//
// 0x005EF5C0 (42 bytes) -- forward every argument to a virtual and return the
// first slot:
//
//     mov edx,[esp+0x18] / mov eax,[ecx] / push esi / mov esi,[esp+8]
//     push edx / <four more re-pushes of [esp+0x1C]> / push esi
//     call dword ptr [eax+0x1C] / mov eax,esi / pop esi / ret 0x18
//
// Six dwords are popped and all six are pushed back UNCHANGED, in reverse
// order, to a virtual reached through the receiver's own vptr; the first of
// them is also what comes back in eax.  A stack slot that is both argument one
// and the return value is MSVC's hidden struct-return pointer, so this is a
// member returning a class by value that does nothing but hand the whole call
// to a virtual returning the same class -- the buffer is passed straight
// through, with no copy anywhere in the body.  Slot 0x1C is vtable index seven.
//
// 0x005F5080 (30 bytes) and 0x005F79A0 (25 bytes) -- fill an out-parameter and
// return it:
//
//     mov eax,[esp+8] / fld dword ptr [eax] / push esi / mov esi,[esp+8]
//     sub esp,8 / fstp qword ptr [esp] / push esi / call <G> / add esp,0xC
//     mov eax,esi / pop esi / ret
//
// Nothing is popped by these, so both are __cdecl, and both return their FIRST
// argument unchanged.  The second argument is DEREFERENCED before use -- a
// reference, not a value -- and in 0x005F5080 the loaded float is widened to
// eight bytes on the stack, which is a `double` parameter on the callee.  The
// buffer they return is the one they hand the callee, so the callee writes
// through it; a struct RETURNED by the callee and then returned again copies
// four dwords into place (verified: 64 and 59 bytes, not 30 and 25), so the
// out-pointer is explicit in the source rather than a hidden sret.
//
// 0x005F7A30 (19 bytes) -- a guarded INI callback:
//
//     mov eax,[esp+0x10] / cmp dword ptr [eax],0 / je OUT
//     mov [esp+0x10],eax / jmp <NEXT>
//     OUT: ret
//
// Four dwords, __cdecl, tail-jumped: the same (INI *, void *instance, void
// *store, const void *userData) shape
// Code/GameEngine/Source/Common/U4IniParseIntFlagSetters.cpp reads out, here
// gating the forward on the first dword of `userData`.  The redundant
// `mov [esp+0x10],eax` writing back the value it just loaded is the same tell:
// the source passes a CAST pointer, not the parameter.
//
// 0x0060D3B0 (21 bytes) -- two literals into a global, then a constant:
//
//     mov ecx,[<GLOBAL>] / push 0 / push 1 / call <P>
//     mov eax,3 / ret
//
// The global is loaded into ecx, so it is a pointer and the call is a
// __thiscall on it; the pushes are two literal arguments, first-pushed last, so
// the source wrote (1, 0).  The return value is a constant the call cannot
// affect, so it is a `return 3;` written after the statement.  No stack
// argument, nothing popped: __cdecl of no arguments.
//
// 0x006038C0 (47 bytes) -- start a timed span:
//
//     push esi / push edi / mov edi,[esp+0xC] / test edi,edi / mov esi,ecx
//     jbe OUT
//     mov byte ptr [esi+0x31],1
//     mov ecx,[<GLOBAL>] / mov eax,[ecx] / call dword ptr [eax+0x68]
//     mov [esi+0x40],eax / add eax,edi / mov [esi+0x44],eax
//     mov [esi+0x3C],0x3F800000
//     OUT: pop edi / pop esi / ret 4
//
// `test edi,edi` followed by `jbe` and not `je` is an UNSIGNED `> 0`: the
// argument is unsigned, and the source compares it against zero rather than
// testing it.  A virtual through slot 0x68 of a global object returns a value
// that is stored at +0x40 and, plus the argument, at +0x44 -- a begin and an
// end.  MSVC 7.1 does not reorder straight-line stores, so the field order in
// the source is 0x31, 0x40, 0x44, 0x3C, which is why the float at 0x3C is
// written last despite being the lowest of the three dwords.  0x3F800000 is
// 1.0f.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address, the two
// globals are DIR32 operands copied from retail, and each REL32 callee is
// pinned in reverse/symbols.csv at the address it resolves to.  The `slotNN`
// declarations carry vtable positions and nothing else.

struct U4Ret005EF5C0 { int m_a[ 4 ]; };
class U4Fwd005EF5C0
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18();
	virtual U4Ret005EF5C0 make( int a, int b, int c, int d, int e );
	U4Ret005EF5C0 build( int a, int b, int c, int d, int e );
};
U4Ret005EF5C0 U4Fwd005EF5C0::build( int a, int b, int c, int d, int e )
{
	return make( a, b, c, d, e );
}

struct U4Ret005F5080 { int m_a[ 4 ]; };
void u4Widen005F5080( U4Ret005F5080 *out, double v );
U4Ret005F5080 *u4From005F5080( U4Ret005F5080 *out, const float &v )
{
	u4Widen005F5080( out, v );
	return out;
}

struct U4Ret005F79A0 { int m_a[ 4 ]; };
void u4Take005F79A0( U4Ret005F79A0 *out, int v );
U4Ret005F79A0 *u4From005F79A0( U4Ret005F79A0 *out, const int &v )
{
	u4Take005F79A0( out, v );
	return out;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void u4Indent( int width );
	void u4Append( const void *value );
	void u4Finish( int radix );
};
struct U4Rec005F7A30 { int m_first; };
void u4Then005F7A30( INI *ini, void *instance, void *store, const void *userData );
extern const char g_u4Separator[];
void __cdecl u4FormatInt( INI *ini, int value );

void u4Then005F7A30( INI *ini, void *instance, void *store, const void *userData )
{
	unsigned int depth = (unsigned int)instance;
	if ( depth > 0 )
	{
		do
		{
			ini->u4Indent( 32 );
		}
		while ( --depth );
	}

	ini->u4Append( store );
	ini->u4Append( g_u4Separator );
	u4FormatInt( ini, ((const U4Rec005F7A30 *)userData)->m_first );
	ini->u4Finish( 10 );
}

void u4Guard005F7A30( INI *ini, void *instance, void *store, const void *userData )
{
	const U4Rec005F7A30 *rec = (const U4Rec005F7A30 *)userData;
	if ( rec->m_first != 0 )
		u4Then005F7A30( ini, instance, store, rec );
}

class U4Sink0060D3B0
{
public:
	void push( int a, int b );
};
extern U4Sink0060D3B0 *g_u4Sink0060D3B0;
int u4Emit0060D3B0( void )
{
	g_u4Sink0060D3B0->push( 1, 0 );
	return 3;
}

class U4Clock006038C0
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64();
	virtual unsigned int now( void );
};
extern U4Clock006038C0 *g_u4Clock006038C0;
struct U4Timer006038C0
{
	char m_pad00[ 0x31 ];
	unsigned char m_active;
	char m_pad32[ 0x0A ];
	float m_rate;
	unsigned int m_begin;
	unsigned int m_end;
	void start( unsigned int duration );
};
void U4Timer006038C0::start( unsigned int duration )
{
	if ( duration > 0 )
	{
		m_active = 1;
		m_begin = g_u4Clock006038C0->now();
		m_end = m_begin + duration;
		m_rate = 1.0f;
	}
}
