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
// IDENTITY IS NOT RECOVERED.  All three callees are unclaimed and enter as
// declarations pinned by address; every name here comes from a row or callee
// address.

// ------------------------------------------------------------ float widening

class U1FloatSink;
void u1Widen_005C5E40( U1FloatSink *self, double value );

class U1FloatSink
{
public:
	void set( float value );
};

void U1FloatSink::set( float value )
{
	u1Widen_005C5E40( this, value );
}

// ---------------------------------------------------------- indexed element

class U1CallReceiver_005C5BD0
{
public:
	void step( int amount );
};

class U1CallSink
{
public:
	void add( const char *text );
};

class U1CallReceiver_005C47D0
{
public:
	class Argument;
	void apply( Argument *argument );
};

void u1Call_005C7110( void *a, void *b, void *c, void **element )
{
	U1CallReceiver_005C5BD0 *receiver = (U1CallReceiver_005C5BD0 *)a;
	U1CallSink *sink = (U1CallSink *)a;
	unsigned int count = (unsigned int)b;
	if( count > 0 )
	{
		do
		{
			receiver->step( 0x20 );
			--count;
		} while( count != 0 );
	}

	sink->add( (const char *)c );
	sink->add( (const char *)0x0110FCA8 );
	sink->add( (const char *)*element );
	((U1CallReceiver_005C47D0 *)a)->apply(
		(U1CallReceiver_005C47D0::Argument *)0x0A );
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
	void reserve( void *source, int count );

	void *m_first;
	char *m_end;
};

U1Buffer_005C5FB0::U1Buffer_005C5FB0( void *unused, int count, void *source )
{
	reserve( source, count + 1 );
	*m_end = 0;
}
