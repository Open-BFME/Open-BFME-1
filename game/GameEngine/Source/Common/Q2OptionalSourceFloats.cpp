// Seven 22-byte __thiscall const members that ask a stored object for a float
// and fall back to a literal when the object is absent:
//
//   mov ecx,[ecx+<MEMBER>] / test ecx,ecx / je fallback
//   mov eax,[ecx] / jmp dword ptr [eax+<SLOT>]
//  fallback:
//   fld dword ptr [<LITERAL>] / ret
//
// WHAT THE BYTES SHOW.  Control leaves the non-null arm through a JMP, so the
// callee's `ret` returns to OUR caller: a tail call, which means the callee is
// __thiscall with no stack arguments and returns a float in st0 exactly as
// this function does.  The receiver is loaded THROUGH the object, so it is a
// stored pointer and not a sub-object.  `mov eax,[ecx] / jmp [eax+SLOT]` is a
// virtual dispatch on that pointer, so the slot index is SLOT/4.
//
// THE LOAD GOES STRAIGHT INTO ecx, which is the detail that pins the source.
// Spelling the member access twice -- `return m_source ? m_source->f() : k;`
// or `if (m_source) return m_source->f();` -- makes MSVC load it into eax,
// test it there and then copy it to ecx for the call: 24 bytes with an extra
// `mov ecx,eax`.  Naming it ONCE into a local and using the local for both the
// test and the call is what produces retail's 22.  Writing the fallback first
// (`if (!s) return k; return s->f();`) also gives 22 but inverts the branch to
// `jne`, which retail does not have -- so the null arm is the SECOND one in
// the source.
//
// THE FALLBACK LITERALS ARE READ OUT OF RETAIL: the two addresses these rows
// fld from hold 0x00000000 and 0x3F800000, i.e. 0.0f and 1.0f.  The linker
// folds `__real@` constants by name, and `__real@00000000` resolves to the
// same 0x01075350 everywhere else in the ledger, so this is a check rather
// than a guess.
//
// THREE AXES: the member offset (0x94, 0x90, 0x1BC -- three different owner
// layouts), the vtable slot (4 through 8), and which of the two literals is
// returned.  18 of the 22 bytes are concrete; only the literal's address comes
// from the target.
//
// WHAT THE BYTES DO NOT DECIDE.  Whether the three owners point at ONE source
// interface or at three unrelated ones -- an indirect call through a slot says
// nothing about the class -- so one shared interface is used because it
// assumes the fewest types, not because the bytes require it.  How many
// virtuals that interface really has: only that slot 8 exists.  Everything in
// the owners before the pointer is padding.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Q2FloatSource
{
public:
	virtual float slot0() const;
	virtual float slot1() const;
	virtual float slot2() const;
	virtual float slot3() const;
	virtual float slot4() const;
	virtual float slot5() const;
	virtual float slot6() const;
	virtual float slot7() const;
	virtual float slot8() const;
};

#define Q2_OPTIONAL_SOURCE_FLOAT( OWNER, NAME, SLOT, FALLBACK )           \
	float OWNER::NAME() const                                             \
	{                                                                     \
		Q2FloatSource *source = m_source;                                 \
		if ( source )                                                     \
			return source->SLOT();                                        \
		return FALLBACK;                                                  \
	}

class Rva005C30A0Owner
{
public:
	float Rva005C30A0() const;
	float Rva005C30C0() const;
	float Rva005C30E0() const;
	float Rva005C3100() const;
	float Rva005C3120() const;
private:
	char m_unreconstructed_00[ 0x94 ];
	Q2FloatSource *m_source;						///< retail this+0x94
};

Q2_OPTIONAL_SOURCE_FLOAT( Rva005C30A0Owner, Rva005C30A0, slot4, 0.0f )
Q2_OPTIONAL_SOURCE_FLOAT( Rva005C30A0Owner, Rva005C30C0, slot5, 1.0f )
Q2_OPTIONAL_SOURCE_FLOAT( Rva005C30A0Owner, Rva005C30E0, slot6, 1.0f )
Q2_OPTIONAL_SOURCE_FLOAT( Rva005C30A0Owner, Rva005C3100, slot7, 1.0f )
Q2_OPTIONAL_SOURCE_FLOAT( Rva005C30A0Owner, Rva005C3120, slot8, 0.0f )

class Rva005C3160Owner
{
public:
	float Rva005C3160() const;
private:
	char m_unreconstructed_00[ 0x90 ];
	Q2FloatSource *m_source;						///< retail this+0x90
};

Q2_OPTIONAL_SOURCE_FLOAT( Rva005C3160Owner, Rva005C3160, slot5, 0.0f )

class Rva005C34D0Owner
{
public:
	float Rva005C34D0() const;
private:
	char m_unreconstructed_00[ 0x1BC ];
	Q2FloatSource *m_source;						///< retail this+0x1BC
};

Q2_OPTIONAL_SOURCE_FLOAT( Rva005C34D0Owner, Rva005C34D0, slot4, 0.0f )
