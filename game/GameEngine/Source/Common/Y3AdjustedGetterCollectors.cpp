// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Six bodies, 60 to 90 bytes, that read a run of null-checked pointer members,
// ask each one for a value through a SUBOBJECT AT +0x14, write the answer into
// a field of the supplied object, and then pass that object on to a member.
// Retail, the single-field arity:
//
//     push esi / mov esi,ecx
//     mov eax,[esi+<FIELD>] / test eax,eax / je null
//     lea ecx,[eax+0x14] / mov eax,[ecx] / call dword ptr [eax]
//     mov ecx,[esp+8] / mov [ecx+0x54],eax
//     push ecx / lea ecx,[esi+<K>] / call <REL32> / pop esi / ret 4
//     null: mov ecx,[esp+8] / mov dword ptr [ecx+0x54],0
//     push ecx / lea ecx,[esi+<K>] / call <REL32> / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, one dword parameter, `ret 4`, nothing
// returned: __thiscall taking a pointer.  The parameter is never read, only
// written and then handed on, so it is an OUT parameter.
//
// THE +0x14 IS A BASE CONVERSION THAT HAS ALREADY BEEN PROVED NON-NULL.  The
// member is loaded into EAX and tested there, and only inside the taken arm is
// `lea ecx,[eax+0x14]` emitted with NO null guard -- which is what MSVC 7.1
// does when the pointer is already known non-null on that path.  A member at
// +0x14 would need no guard anywhere; a base at +0x14 reached from a pointer
// that had not been tested would carry `test/je/lea/jmp/xor`.  So the pointee
// is a class whose SECOND base sits at 0x14, and the method dispatched is that
// base's SLOT 0, called with no arguments.
//
// THE NULL ARM DOES NOT MERGE AND STORES AN IMMEDIATE.  `mov dword ptr
// [ecx+0x54],0` is the tell that separates this family from the collectors in
// U1Slot2FieldCollectors.cpp, where the zero always arrives in a register:
// there the source is one assignment fed by a conditional expression, here it
// is an if/else with an assignment in each arm.  The whole tail duplicates
// into the null arm at the single-field arity and merges with a `jmp` at the
// two-field arity, purely because there is following code to merge into.
//
// THE OUT PARAMETER IS RELOADED FROM THE STACK in both arms -- it is never
// cached in a register across the virtual call -- and the fields written are
// 0x44, 0x48 and 0x54, inside the same displacement run the collectors write.
//
// THE TAIL IS A MEMBER SUBOBJECT: bare `lea ecx,[esi+K]` with no guard, K just
// past the last member read, and the out parameter re-pushed unchanged.  Five
// of the six call 0x005C98E0, which is not converted here and is pinned; the
// sixth, 0x005CEF10, calls 0x005CE6A0, which IS converted here and is
// therefore defined __declspec(noinline) so this file cannot inline what
// retail left as a `call`.
//
// THE MEMBER OFFSETS ARE 0, 4, 8, 0xC and (0, 0x10) -- one class per row, each
// with its own leading gap, and nothing in any body says what the gaps hold.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Y3AdjPad
{
public:
	virtual void adjPad0();
	int m_pad[4];
};

class Y3AdjGet
{
public:
	virtual void *get();
};

class Y3AdjSource : public Y3AdjPad, public Y3AdjGet
{
public:
	unsigned char m_pad18[4];
	unsigned char m_enabled;                         // +0x1c
};

#define _STLP_USE_STATIC_LIB 1
#include <vector>

// The collector builds a four-byte POD vector.  This is the same STLport
// instantiation whose overflow body is reached through ILT 0x0002321d.
struct Gen_t_005c8830_m4pod
{
	void *m_value;
};

class Y3AdjValueVector : public _STL::vector<
	Gen_t_005c8830_m4pod, _STL::allocator<Gen_t_005c8830_m4pod> >
{
};

class Y3AdjOut
{
public:
	int m_pad0[0x44 / 4];
	void *m_v44;
	void *m_v48;
	int m_pad1[2];
	void *m_v54;
	Y3AdjValueVector m_values;                         // +0x58
};

class Y3AdjTail_005C98E0
{
public:
	void collect( Y3AdjOut *out );

	Y3AdjSource **m_begin;
	Y3AdjSource **m_end;
};

void Y3AdjTail_005C98E0::collect( Y3AdjOut *out )
{
	Y3AdjValueVector values;
	for ( Y3AdjSource **it = m_begin; it != m_end; ++it )
	{
		Y3AdjSource *source = *it;
		if ( source->m_enabled )
		{
			Gen_t_005c8830_m4pod value;
			value.m_value = source->get();
			values.push_back( value );
		}
	}
	out->m_values.swap( values );
}

// ---- the run that ends at 0x005C98E0 --------------------------------------

#define Y3_ADJ_ROW( ROW, GAP )                                                \
	class Y3Adj_##ROW                                                         \
	{                                                                         \
	public:                                                                   \
		void collect( Y3AdjOut *out );                                        \
                                                                              \
		GAP                                                                   \
		Y3AdjSource *m_f0;                                                    \
		Y3AdjTail_005C98E0 m_tail;                                            \
	};                                                                        \
	void Y3Adj_##ROW::collect( Y3AdjOut *out )                                \
	{                                                                         \
		if ( m_f0 )                                                           \
			out->m_v54 = m_f0->get();                                         \
		else                                                                  \
			out->m_v54 = 0;                                                   \
		m_tail.collect( out );                                                \
	}

Y3_ADJ_ROW( 005CC3A0, )
Y3_ADJ_ROW( 005CD490, char m_gap[4]; )
Y3_ADJ_ROW( 005CD940, char m_gap[8]; )
Y3_ADJ_ROW( 005CDE00, char m_gap[12]; )

class Y3Adj_005CE6A0
{
public:
	__declspec(noinline) void collect( Y3AdjOut *out );

	Y3AdjSource *m_f0;
	char m_gap[12];
	Y3AdjSource *m_f1;
	Y3AdjTail_005C98E0 m_tail;
};

void Y3Adj_005CE6A0::collect( Y3AdjOut *out )
{
	if ( m_f0 )
		out->m_v48 = m_f0->get();
	else
		out->m_v48 = 0;
	if ( m_f1 )
		out->m_v54 = m_f1->get();
	else
		out->m_v54 = 0;
	m_tail.collect( out );
}

class Y3Adj_005CEF10
{
public:
	void collect( Y3AdjOut *out );

	Y3AdjSource *m_f0;
	Y3Adj_005CE6A0 m_tail;
};

void Y3Adj_005CEF10::collect( Y3AdjOut *out )
{
	if ( m_f0 )
		out->m_v44 = m_f0->get();
	else
		out->m_v44 = 0;
	m_tail.collect( out );
}
