// cl: /DNDEBUG /MD /EHsc
// Retail 0x00417060 (99 bytes) — Drawable list-query with two identical tails.
// The 99-byte body walks an Entry** table at this+0x158, calling Entry vtable+0x2c
// to get a finder and then finder vtable+8 with an out-parameter. On success it
// returns the out-parameter. Otherwise it returns parent->m_result where parent
// is this+0x4 (Overridable). Retail keeps both null-parent and resolved-parent
// tails as mov eax,[eax+0x430] with distinct copies. MSVC 7.1 folds a provably-null
// base to moffs and cross-jumps identical tails, so two levers are needed:
//   * test the MEMBER m_rva00417060Parent for null while returning via the local
//     copy, defeating the absolute fold;
//   * put DIFFERENT barrier intrinsics in the two identical tails
//     (_WriteBarrier in the early null return, _ReadWriteBarrier in the late
//     return) to keep both copies, per docs/shape_levers.md tail-merge row.
// Neither barrier emits an instruction.

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

class Rva00417060Query;
class Rva00417060Entry;
class Rva00417060Parent;

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
};

// Retail routes this call through the ILT thunk at 0x000022bb.
extern void j_000022bb();

class Rva00417060Query
{
public:
	virtual void rva00417060QuerySlot00();
	virtual void rva00417060QuerySlot04();
	virtual bool rva00417060QuerySlot08(void **result);
};

class Rva00417060Entry
{
public:
	virtual void rva00417060EntrySlot00();
	virtual void rva00417060EntrySlot04();
	virtual void rva00417060EntrySlot08();
	virtual void rva00417060EntrySlot0c();
	virtual void rva00417060EntrySlot10();
	virtual void rva00417060EntrySlot14();
	virtual void rva00417060EntrySlot18();
	virtual void rva00417060EntrySlot1c();
	virtual void rva00417060EntrySlot20();
	virtual void rva00417060EntrySlot24();
	virtual void rva00417060EntrySlot28();
	virtual Rva00417060Query *rva00417060EntrySlot2c();
};

class Rva00417060Parent : public Overridable
{
public:
	unsigned char m_rva00417060Pad08[0x428];
	void *m_rva00417060Result;
};

class Rva00417060
{
public:
	void *rva00417060() const;

private:
	void *m_rva00417060Head;
	Rva00417060Parent *m_rva00417060Parent;
	unsigned char m_rva00417060Pad08[0x150];
	Rva00417060Entry **m_rva00417060Entries;
};

void *Rva00417060::rva00417060() const
{
	void *result;
	Rva00417060Entry **entry = m_rva00417060Entries;

	if (entry != 0)
	{
		do
		{
			Rva00417060Entry *current = *entry;
			if (current == 0)
				break;

			Rva00417060Query *query = current->rva00417060EntrySlot2c();
			if (query != 0 && query->rva00417060QuerySlot08(&result))
				return result;

			++entry;
		}
		while (entry != 0);
	}

	Rva00417060Parent *parent = m_rva00417060Parent;
	if (m_rva00417060Parent == 0)
	{
		_WriteBarrier();
		return parent->m_rva00417060Result;
	}

	if (parent->m_nextOverride != 0)
	{
		typedef const void *(Overridable::*FinalOverride)() const;
		union { void (*fn)(); FinalOverride call; } final = { j_000022bb };
		parent = (Rva00417060Parent *)((parent->m_nextOverride->*final.call)());
	}

	_ReadWriteBarrier();
	return parent->m_rva00417060Result;
}
