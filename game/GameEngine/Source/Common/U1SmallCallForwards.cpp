// Three small bodies from the 0x005BFEE0 drawer, each of which does nothing
// but arrange arguments for one call.
//
// ---- 0x005C67A0, 22 bytes: A FLOAT PARAMETER WIDENED TO A DOUBLE.
//
//     fld dword ptr [esp+4] / sub esp,8 / fstp qword ptr [esp]
//     push ecx / call <REL32> / add esp,0xC / ret 4
//
// `ret 4` with ecx live on entry is __thiscall with one dword parameter, and
// that parameter is loaded as a FOUR-byte float and stored back as an EIGHT-
// byte double -- so the parameter's type is `float` and the callee's is
// `double`.  The receiver is then pushed as an ordinary argument and the
// CALLER cleans twelve bytes off the stack, which makes the callee __cdecl
// taking (this, double).  Nothing is returned.
//
// ---- 0x005C8320, 42 bytes: A GUARDED CALL ON AN INDEXED ELEMENT.
//
//     mov eax,[esp+0x10] / cmp eax,[esp+0x14] / je out
//     mov ecx,[esp+0x18] / lea edx,[ecx+eax*4]
//     mov eax,[esp+0xC] / mov ecx,[esp+8] / push edx / mov edx,[esp+8]
//     push eax / push ecx / push edx / call <REL32> / add esp,0x10
//     out: ret
//
// A bare `ret` with ecx dead on entry and reads out to [esp+0x18]: __cdecl
// with six parameters.  The FOURTH and FIFTH are compared to each other and
// nothing else is done with them, so they are the same scalar type; the SIXTH
// is scaled by the fourth times FOUR, which fixes the element width at four
// bytes and makes the sixth a pointer to them.  What the callee receives is
// the first three parameters unchanged plus that computed ADDRESS -- not a
// value loaded from it -- so the source hands over `array + index`.  The
// callee cleans sixteen bytes, so it is __cdecl with four parameters.
//
// ---- 0x005C5FB0, 33 bytes: A CONSTRUCTOR THAT IGNORES ITS FIRST PARAMETER.
//
//     mov eax,[esp+8] / push esi / mov esi,ecx / mov ecx,[esp+0x10]
//     inc eax / push eax / push ecx / mov ecx,esi / call <REL32>
//     mov edx,[esi+4] / mov eax,esi / mov byte ptr [edx],0
//     pop esi / ret 0xC
//
// `ret 0xC` pops three dwords and `mov eax,esi` returns `this`: a __thiscall
// constructor with three parameters.  The FIRST is never read -- no
// instruction touches [esp+4] -- while the second is incremented by one and
// the third re-pushed unchanged, giving the callee (third, second+1).  An
// unread parameter is not an error in the reading: T1ArgumentTakingVtableCtors
// .cpp shows the same thing two thousand bytes later, where the argument is
// real but consumed further down the hierarchy.
//
// AFTER THE CALL, a pointer is read from offset 4 of the object and a ZERO
// BYTE written through it.  The member at 4 is therefore a `char *` and the
// store is a null terminator; it happens after the call, so the callee is what
// puts a usable value there.
//
// The adapter identities remain address-derived. Their calls bind the
// existing matched STLport ostream and constructor identities proven by the
// retail ILT targets below.

// The ordinary retail ILTs resolve to the existing STLport ostream rows.
// Specialization declarations keep their bodies external to this TU.
// stlport
#include <ostream>

namespace _STL
{
template <> void basic_ostream<char, char_traits<char> >::_M_put_nowiden(const char *);
template <> void basic_ostream<char, char_traits<char> >::_M_put_char(char);
template <> basic_ostream<char, char_traits<char> > &
    basic_ostream<char, char_traits<char> >::put(char);
template <> basic_ostream<char, char_traits<char> > &
    _M_put_num<char, char_traits<char>, double>(
        basic_ostream<char, char_traits<char> > &, double);
}

// ILT 0x00016527 -> 0x005C46C0: ECX receiver, two pushed dwords,
// ret8 on both exits, EAX=this unused here. Its constructor is the matched
// Gen_005C46C0 row. This address declaration is used only to form the measured
// single-inheritance member-pointer call below; it is never called as cdecl.
extern "C" void __cdecl __identifier("??0Gen_005C46C0@@QAE@PAXI@Z")();

// ------------------------------------------------------------ float widening

class U1FloatSink;

class U1FloatSink
{
public:
	void set( float value );
};

void U1FloatSink::set( float value )
{
	_STL::_M_put_num(
        *reinterpret_cast<_STL::basic_ostream<char, _STL::char_traits<char> > *>(this),
        static_cast<double>(value));
}

// ---------------------------------------------------------- indexed element

void u1Call_005C7110( void *a, void *b, void *c, void **element )
{
	_STL::basic_ostream<char, _STL::char_traits<char> > *receiver =
        reinterpret_cast<_STL::basic_ostream<char, _STL::char_traits<char> > *>(a);
	_STL::basic_ostream<char, _STL::char_traits<char> > *sink = receiver;
	unsigned int count = (unsigned int)b;
	if( count > 0 )
	{
		do
		{
			receiver->put( ' ' );
			--count;
		} while( count != 0 );
	}

	sink->_M_put_nowiden( (const char *)c );
	sink->_M_put_nowiden( " = " );
	sink->_M_put_nowiden( (const char *)*element );
	receiver->_M_put_char( '\n' );
}

void u1Range_005C8320( void *a, void *b, void *c, int index, int end, void **array )
{
	if ( index != end )
	{
		u1Call_005C7110( a, b, c, array + index );
	}
}

// -------------------------------------------------------- reserving ctor

class U1Buffer_005C5FB0
{
public:
	U1Buffer_005C5FB0( void *unused, int count, void *source );

	void *m_first;
	char *m_end;
};

U1Buffer_005C5FB0::U1Buffer_005C5FB0( void *unused, int count, void *source )
{
    union
    {
        void (*address)();
        void (U1Buffer_005C5FB0::*member)(void *, unsigned int);
    } route = { __identifier("??0Gen_005C46C0@@QAE@PAXI@Z") };
    (this->*route.member)(source, static_cast<unsigned int>(count + 1));
	*m_end = 0;
}
