// carved dump placeholder: d_0023c9c0
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
//
// Carved body at retail 0x0023C9C0. `this` is an interior interface pointer
// (owner object at `(char*)this - 0xdc`, the same interior-this shape as
// BfmeContainInterfaceView (this-0xac) in HordeContainAnyMemberHeldByAI.cpp,
// just a different private member). Both the owner and `other` share a
// 32-bit flags word at +0x94 (bit 29 tested) and a pointer at +0x23c
// (identity compared). When both objects fail or disagree on the bit-29
// flag, or the +0x23c pointers differ, or the caller's `flag` argument is
// false, the function returns false immediately. Otherwise it resolves
// `other`'s override chain (`other+4 -> +4 -> Overridable::getFinalOverride`)
// to a 16-bit id at +0x478 and scans a caller-owned AsciiString vector
// (`names`) through BfmeThingFactory::findTemplate (reached through the same
// ICF-shared ILT thunk 0x00028560 as Rva0020AA00Registry::bfmeLookupZF),
// returning true the first time a found template's +0x478 id matches.
//
// Retail leaves the 16-bit id (`bx`) unset when the override chain is null
// at either level: the comparison then reads ebx's pushed-in high byte
// (whatever ebx held on entry) paired with the `flag` argument's low byte,
// because the compiler puts both values in the same callee-saved register.
// That is reproduced here with a genuinely-conditional assignment (no
// default), not modelled as a proven semantic default.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

// other+0x04 -> Gen_0023c9c0_Link; Gen_0023c9c0_Link+0x04 -> Overridable.
struct Gen_0023c9c0_Link
{
	char m_pad00[4];
	Overridable *m_overridable;
};

// Shared object layout proven by the owner/other field offsets the body
// itself reads: +0x04 override link, +0x94 flags, +0x23c identity pointer.
struct Gen_0023c9c0_Obj
{
	char m_pad00[4];
	Gen_0023c9c0_Link *m_link;
	char m_pad08[0x94 - 0x08];
	UnsignedInt m_flags;
	char m_pad98[0x23c - 0x98];
	void *m_side;
};

// A resolved override/template carries its comparable id at +0x478.
struct Gen_0023c9c0_Kind
{
	char m_pad[0x478];
	UnsignedShort m_id;
};

struct Rva0020AA00Registry
{
	void *bfmeLookupZF( void *key );
};
extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

// The caller-owned name list: retail reads +0x00/+0x04 as begin/end, a
// 4-byte (AsciiString) stride.
struct Gen_0023c9c0_Names
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

class Gen_0023c9c0_View
{
public:
	Bool bfme( Gen_0023c9c0_Obj *other, void *mustBeNull,
		Gen_0023c9c0_Names *names, Bool flag ) const;

private:
	Gen_0023c9c0_Obj *const &owner() const
	{
		return *(Gen_0023c9c0_Obj *const *)( (const char *)this - 0xdc );
	}
};

Bool Gen_0023c9c0_View::bfme( Gen_0023c9c0_Obj *other, void *mustBeNull,
	Gen_0023c9c0_Names *names, Bool flag ) const
{
	if ( mustBeNull != 0 )
		return false;

	Gen_0023c9c0_Obj *self = owner();
	unsigned char otherBit = (unsigned char)( other->m_flags >> 29 ) & 1;
	unsigned char selfBit = (unsigned char)( self->m_flags >> 29 ) & 1;

	if ( otherBit || selfBit )
	{
		if ( !flag )
			return false;
		if ( other->m_side != self->m_side )
			return false;
		if ( otherBit != selfBit )
			return false;
	}

	Gen_0023c9c0_Link *link = other->m_link;
	const void *kindSrc = link;
	if ( link && link->m_overridable )
		kindSrc = link->m_overridable->getFinalOverride();
	UnsignedShort id = ( (const Gen_0023c9c0_Kind *)kindSrc )->m_id;

	for ( AsciiString *it = names->m_begin; it != names->m_end; ++it )
	{
		Gen_0023c9c0_Kind *found = (Gen_0023c9c0_Kind *)
			Rva0020AA00TheRegistry->bfmeLookupZF( it );
		if ( found && found->m_id == id )
			return true;
	}

	return false;
}
