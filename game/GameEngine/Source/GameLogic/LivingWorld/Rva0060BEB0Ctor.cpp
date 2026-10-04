// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

// Retail 0x0060BEB0, 118 bytes.  The body takes an AsciiString by value, copies
// it into the by-value parameter of the constructor at 0x0061DA30, stores the
// vtable constant 0x01115E90 over the object's first word, clears three words
// at +0xA0, +0xA4 and +0xA8, and destroys its own parameter.  0x0060BEB0 is the
// only function in the image that writes 0x01115E90, and no caller, RTTI record
// or string names the class, so both names keep the address.
//
// The vtable store is volatile and the first cleared word is volatile for the
// same reason AIPickUpCrateStateConstructor.cpp marks its two stores: without
// them VC7.1 hoists the destructor receiver above the vtable store and swaps
// two instructions.

// Retail calls the base constructor through ILT 0x0001BD5B, whose matched row
// is ?j_0001bd5b@@YAXXZ in game/gen_small/thunks_013.cpp; the ILT jumps to the
// 252-byte body at 0x0061DA30.  The by-value AsciiString argument is copied to a
// stack temporary first, exactly as the base-constructor call spells it, so the
// call is made through the ILT name with a member-pointer cast to keep the
// observed receiver and argument shape.
extern void j_0001bd5b();

class Rva0061DA30Base
{
public:
	void rva0061da30BaseConstructor( AsciiString name );
};

typedef void (Rva0061DA30Base::*BaseConstructorCall)( AsciiString name );

extern int g_Rva0060BEB0VTable;

class Rva0060BEB0Object : public Rva0061DA30Base
{
public:
	Rva0060BEB0Object( AsciiString name );

private:
	int *volatile m_vftable;
	char m_gap04[ 0xA0 - 4 ];
	volatile int m_fieldA0;
	int m_fieldA4;
	int m_fieldA8;
};

Rva0060BEB0Object::Rva0060BEB0Object( AsciiString name )
{
	union { void (__cdecl *raw)(); BaseConstructorCall member; } base;
	base.raw = j_0001bd5b;
	( static_cast<Rva0061DA30Base *>( this )->*base.member )( name );
	m_vftable = &g_Rva0060BEB0VTable;
	m_fieldA0 = 0;
	m_fieldA4 = 0;
	m_fieldA8 = 0;
}
