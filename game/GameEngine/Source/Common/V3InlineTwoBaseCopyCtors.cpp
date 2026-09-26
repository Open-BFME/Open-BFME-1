// cl: /EHs-c-
// Six 41-byte __thiscall copy constructors with NO call in them at all.
// Retail:
//
//     mov eax,ecx ; mov ecx,[esp+4]
//     mov [eax],  <FIRST BASE VFTABLE>      ; 0x01111D90 in all six
//     mov edx,[ecx+4] ; mov [eax+4],edx     ; the first base's int, copied
//     mov [eax+8],<SECOND BASE VFTABLE>     ; the second base's own ctor
//     mov [eax],  <DERIVED VFTABLE 0>
//     mov [eax+8],<DERIVED VFTABLE 8>
//     ret 4
//
// WHAT THE BYTES SHOW.  `ret 4` and `mov eax,ecx` make it a one-argument
// constructor returning this; the argument is dereferenced at +4 and the dword
// stored to this+4, so the argument is a pointer to the same layout -- a COPY
// constructor.  Offset 0 and offset 8 are each written twice with two different
// vftable addresses, which is a base and a derived class writing the same slot,
// so this is multiple inheritance from two polymorphic bases at 0 and 8, and
// BOTH base constructors are inlined -- there is no call anywhere.  The first
// base is eight bytes wide (vptr plus the copied int), which is why the second
// sits at 8.
//
// These are the callees of five of the 32-byte forwarders already landed in
// V3CopyCtorForwarders.cpp (0x005EA400 -> 0x005EA430 and so on), which is an
// independent confirmation of the two-slot layout: those bodies re-stamp
// exactly offsets 0 and 8.
//
// THE SIX SECOND-BASE VFTABLES ARE THE SIX FROM Q2MultipleBaseVtableSetters.cpp
// -- 0x0110F978, 0x01073760, 0x0110F9E4, 0x0110F9E8, 0x0110FA14, 0x0107375C --
// in that file's own words "the SAME six second-base vftable addresses appear in
// both".  That is now three families sharing them, and this one AGREES with that
// file about 0x0107375C being the wide one.  It agrees by a route worth writing
// down, because it looked at first like a contradiction.
//
// THE SECOND BASE IS DEFAULT-CONSTRUCTED, NOT COPIED, and the wide row is what
// proves it.  Spelling the initialiser list `: FIRST(o), SECOND(o)` and spelling
// it `: FIRST(o)` produce byte-identical 41-byte bodies for a four-byte second
// base -- the copy has nothing to copy -- so five of these six rows cannot tell
// the two apart.  The 0x0107375C row can: copy-constructing it emits `mov
// ecx,[ecx+0xC] ; mov [eax+0xC],ecx`, eight bytes retail does not have, and the
// body runs long.  Default-constructing it emits only the vptr store and all six
// rows land.  So the source omits the second base from the initialiser list, and
// Q2's extra dword survives rather than being refuted.
//
// ONE CLASS PER ROW: six different derived vftable pairs, six classes.  The
// first base is one class in all six -- one address, one type.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses.  All six vftable
// dwords per body are DIR32 relocation sites the gate takes from the target,
// leaving 17 of the 41 bytes concrete.

// first base -- vftable 0x01111D90, vptr plus one int, so eight bytes wide
class V3Vt01111D90
{
public:
	virtual void s0();
	virtual ~V3Vt01111D90() {}
	int m_unreconstructed_04;
};

#define V3_SECOND_BASE( ADDR )                                            \
	class V3Vt##ADDR                                                      \
	{                                                                     \
	public:                                                               \
		virtual void s0();                                                \
		virtual ~V3Vt##ADDR() {}                                          \
	};

#define V3_SECOND_BASE_WIDE( ADDR )                                       \
	class V3Vt##ADDR                                                      \
	{                                                                     \
	public:                                                               \
		virtual void s0();                                                \
		virtual ~V3Vt##ADDR() {}                                          \
		int m_unreconstructed_04;                                         \
	};

V3_SECOND_BASE( 0110F978 )
V3_SECOND_BASE( 01073760 )
V3_SECOND_BASE( 0110F9E4 )
V3_SECOND_BASE( 0110F9E8 )
V3_SECOND_BASE( 0110FA14 )
V3_SECOND_BASE_WIDE( 0107375C )

#define V3_INLINE_COPY_CTOR( NAME, SECOND )                               \
	class NAME : public V3Vt01111D90, public SECOND                       \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : V3Vt01111D90( o ) {}

V3_INLINE_COPY_CTOR( Rva005EA430, V3Vt0110F978 )
V3_INLINE_COPY_CTOR( Rva005EA6F0, V3Vt01073760 )
V3_INLINE_COPY_CTOR( Rva005EA9B0, V3Vt0110F9E4 )
V3_INLINE_COPY_CTOR( Rva005EABB0, V3Vt0110F9E8 )
V3_INLINE_COPY_CTOR( Rva005EAE70, V3Vt0110FA14 )
V3_INLINE_COPY_CTOR( Rva005EB090, V3Vt0107375C )
