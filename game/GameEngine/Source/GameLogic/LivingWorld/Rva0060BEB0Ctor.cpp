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

class Rva0061DA30Base
{
public:
	Rva0061DA30Base( AsciiString name );
};

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
	: Rva0061DA30Base( name )
{
	m_vftable = &g_Rva0060BEB0VTable;
	m_fieldA0 = 0;
	m_fieldA4 = 0;
	m_fieldA8 = 0;
}
