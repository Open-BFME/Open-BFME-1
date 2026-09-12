// cl: /EHs-c-
// Twenty-five bodies that do nothing but store vtable pointers.  They fall
// into two shapes that share their base classes, which is why they share a
// file: the SAME six second-base vtable addresses appear in both, and a vtable
// address is a class, so those six classes are declared once here.
//
// SHAPE A -- 23-byte constructor of a class with TWO polymorphic bases:
//
//   mov eax,ecx                          ; a constructor returns this
//   mov [eax+4],<SECOND BASE VFTABLE>    ; the second base's own ctor, inlined
//   mov [eax],  <DERIVED VFTABLE FOR BASE 1>
//   mov [eax+4],<DERIVED VFTABLE FOR BASE 2>
//   ret
//
// SHAPE B -- 35-byte destructor of a class with THREE polymorphic bases:
//
//   mov [ecx+4],<DERIVED VFTABLE FOR BASE 2>
//   mov [ecx+X],<DERIVED VFTABLE FOR BASE 3>
//   mov [ecx+X],<THIRD BASE VFTABLE>       ; ~base3, inlined
//   mov [ecx+4],<SECOND BASE VFTABLE>      ; ~base2, inlined
//   mov [ecx],  <FIRST BASE VFTABLE>       ; ~base1, inlined
//   ret
//
// WHAT THE BYTES SHOW.  A slot written TWICE in one body with two different
// vtable addresses can only be a derived class and a base class writing the
// same vptr, so both shapes are multiple inheritance from polymorphic bases,
// and every base's own constructor or destructor is INLINED -- there is no
// call anywhere in either shape.  Shape A's leading `mov eax,ecx` and the use
// of eax as the base for the stores is the constructor's `return this`; shape
// B writes through ecx and never sets eax, so it returns nothing.  Shape B's
// bare `ret` makes it the plain destructor, not the scalar-deleting one.
//
// EXACTLY ONE STORE IS MISSING FROM EACH SHAPE, and it is always the FIRST
// base's own store: shape A should write four vptrs and writes three, shape B
// should write six and writes five.  MSVC drops the primary base's store
// because the derived one to the same slot kills it -- and, oddly, drops only
// that one, leaving the second base's store live even though the derived
// overwrites that slot too.  Both shapes reproduce that asymmetry exactly,
// which is why the hierarchies here are three bases and two, not four and
// three with something else eliminated.
//
// SHAPE B'S THIRD-BASE OFFSET IS THE SECOND BASE'S WIDTH: 0x08 when the second
// base is a bare vptr, 0x0C when it carries one more dword.  The one second
// base that appears at offset 0x0C (vftable 0x0107375C) is given that dword;
// every other one is four bytes wide.
//
// WHAT THE BYTES DO NOT DECIDE.  Nothing about any virtual function: only that
// each class has at least one, and the vtable CONTENTS are never touched by
// these bodies.  Shape A's FIRST base is completely unobservable -- its store
// is the eliminated one -- so Q2ElidedPrimaryBase carries no evidence at all
// beyond being polymorphic and four bytes wide.  Nothing says shape A's first
// base is or is not shape B's.  No data member of any derived class is
// visible.  11 of shape A's 23 bytes and 15 of shape B's 35 are concrete; the
// vtable dwords come from the target.
//
// SIX PAIRS OF SHAPE-B ROWS AND FIVE PAIRS OF SHAPE-A ROWS STORE IDENTICAL
// DERIVED VFTABLES, so by every byte here each pair is one class.  One class
// cannot have two constructor bodies or two destructor bodies, so each row
// gets its own class and the shared vtable addresses are recorded here instead
// of being hidden.  Same duplicate-translation-unit pattern as the range-loop
// and array-owner families.
//
// IDENTITY IS NOT RECOVERED.  Derived names come from the body address; base
// names come from the vtable address the bytes store.

#define Q2_VTABLE_BASE( ADDR )                                            \
	class PolymorphicVptrBase##ADDR                                       \
	{                                                                     \
	public:                                                               \
		virtual void slot0();                                             \
		virtual ~PolymorphicVptrBase##ADDR() {}                           \
	};

#define Q2_VTABLE_BASE_WIDE( ADDR )                                       \
	class PolymorphicVptrDwordBase##ADDR                                  \
	{                                                                     \
	public:                                                               \
		virtual void slot0();                                             \
		virtual ~PolymorphicVptrDwordBase##ADDR() {}                      \
		int m_unreconstructed_04;                                         \
	};

Q2_VTABLE_BASE( 0110F978 )
Q2_VTABLE_BASE( 0110F9E4 )
Q2_VTABLE_BASE( 0110F9E8 )
Q2_VTABLE_BASE( 0110FA14 )
Q2_VTABLE_BASE( 01073760 )
Q2_VTABLE_BASE_WIDE( 0107375C )

// ------------------------------------------------------------------- shape A

class Q2ElidedPrimaryBase
{
public:
	virtual void slot0();
	virtual ~Q2ElidedPrimaryBase() {}
};

#define Q2_TWO_BASE_CONSTRUCTOR( NAME, SECOND )                           \
	class NAME : public Q2ElidedPrimaryBase, public SECOND                \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
	};                                                                    \
	NAME::NAME() {}

Q2_TWO_BASE_CONSTRUCTOR( Rva005EE6B0, PolymorphicVptrBase0110F978 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005EE880, PolymorphicVptrBase0110F978 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005EFA20, PolymorphicVptrBase01073760 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005EFAF0, PolymorphicVptrBase01073760 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FC620, PolymorphicVptrDwordBase0107375C )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FDBA0, PolymorphicVptrBase0110F9E4 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FDC50, PolymorphicVptrBase0110F9E4 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FE920, PolymorphicVptrBase0110FA14 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FE9E0, PolymorphicVptrBase0110FA14 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FF9E0, PolymorphicVptrBase0110F9E8 )
Q2_TWO_BASE_CONSTRUCTOR( Rva005FFAA0, PolymorphicVptrBase0110F9E8 )

// ------------------------------------------------------------------- shape B

class PolymorphicVptrBase01111D20
{
public:
	virtual void slot0();
	virtual ~PolymorphicVptrBase01111D20() {}
};

class PolymorphicVptrBase01073744
{
public:
	virtual void slot0();
	virtual ~PolymorphicVptrBase01073744() {}
};

#define Q2_THREE_BASE_DESTRUCTOR( NAME, SECOND )                          \
	class NAME : public PolymorphicVptrBase01111D20, public SECOND, public PolymorphicVptrBase01073744 \
	{                                                                     \
	public:                                                               \
		virtual ~NAME();                                                  \
	};                                                                    \
	NAME::~NAME() {}

Q2_THREE_BASE_DESTRUCTOR( Rva005E54F0, PolymorphicVptrDwordBase0107375C )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7A30, PolymorphicVptrBase0110F9E8 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7AA0, PolymorphicVptrBase0110F9E8 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7CC0, PolymorphicVptrBase0110F978 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7D30, PolymorphicVptrBase0110F978 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7D90, PolymorphicVptrBase01073760 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7E00, PolymorphicVptrBase01073760 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7E60, PolymorphicVptrBase0110F9E4 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7ED0, PolymorphicVptrBase0110F9E4 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7F30, PolymorphicVptrBase0110F9E8 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E7FA0, PolymorphicVptrBase0110F9E8 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E8000, PolymorphicVptrBase0110FA14 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E8070, PolymorphicVptrBase0110FA14 )
Q2_THREE_BASE_DESTRUCTOR( Rva005E80E0, PolymorphicVptrDwordBase0107375C )
