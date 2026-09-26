// Five __thiscall const accessors that walk two pointers, tail-jump to a float
// getter when both are non-null, and load a float constant when either is not:
//
//     mov eax,[ecx+8] / test eax,eax / je zero
//     mov eax,[eax+12024h] / test eax,eax / je zero
//     mov ecx,eax / jmp <REL32>
//     zero: fld dword ptr [<CONST>] / ret
//
// WHAT THE BYTES SHOW.  The outer pointer is loaded ONCE and then indexed, so
// the source named it once and kept it; naming it twice would reload it.  The
// exit is `jmp`, so the callee returns a float on the x87 stack directly to our
// caller and takes no stack arguments.  The default arm is `fld` from a
// four-byte constant, which is a float literal, not a double.  The constant
// address is the same 0x01075350 in all five rows and holds 00000000, i.e. 0.0f.
//
// FIVE CALLEES, ONE OWNER SHAPE.  The two offsets (+8, then +0x12024) are
// identical in all five rows, so one pair of classes covers the family; only
// the getter differs, at bodies 0x00683900, 0x00683C00, 0x00683D80, 0x00683F00
// and 0x00684080, each reached through its own incremental-link thunk.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The 0x12024 bytes
// ahead of the inner pointer are unattributed padding here; the bytes only fix
// where the pointer is, not what precedes it.

class Gen00683900
{
public:
	float value00683900() const;
	float value00683C00() const;
	float value00683D80() const;
	float value00683F00() const;
	float value00684080() const;
};

class GenFloatOwner
{
public:
	char m_lead[ 0x12024 ];
	Gen00683900 *m_inner;
};

class Rva00681C10
{
public:
	float at00681C10() const;
	float at00681C70() const;
	float at00681CA0() const;
	float at00681CD0() const;
	float at00681D00() const;
	char m_lead[ 8 ];
	GenFloatOwner *m_owner;
};

#define BFME_NESTED_NULL_FLOAT( NAME, GETTER )                            \
	float Rva00681C10::NAME() const                                       \
	{                                                                     \
		GenFloatOwner *owner = m_owner;                                   \
		if( owner )                                                       \
		{                                                                 \
			Gen00683900 *inner = owner->m_inner;                          \
			if( inner )                                                   \
				return inner->GETTER();                                   \
		}                                                                 \
		return 0.0f;                                                      \
	}

// @?at00681C10@Rva00681C10@@QBEMXZ 0x00681C10
BFME_NESTED_NULL_FLOAT( at00681C10, value00683900 )
// @?at00681C70@Rva00681C10@@QBEMXZ 0x00681C70
BFME_NESTED_NULL_FLOAT( at00681C70, value00683C00 )
// @?at00681CA0@Rva00681C10@@QBEMXZ 0x00681CA0
BFME_NESTED_NULL_FLOAT( at00681CA0, value00683D80 )
// @?at00681CD0@Rva00681C10@@QBEMXZ 0x00681CD0
BFME_NESTED_NULL_FLOAT( at00681CD0, value00683F00 )
// @?at00681D00@Rva00681C10@@QBEMXZ 0x00681D00
BFME_NESTED_NULL_FLOAT( at00681D00, value00684080 )
