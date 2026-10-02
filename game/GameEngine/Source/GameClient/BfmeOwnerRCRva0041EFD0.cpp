// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva0041EFD0@BfmeOwnerRC@@QAEDPAX0@Z
//
// Walks the owner's +0xfc pointer, that object's +0x204 pointer and its
// +0x1cc holder; when the holder's override-resolved record has kind 1 at
// +0x70 it forwards the two arguments together with the two no-argument
// accessor results to the six-argument member at ILT 0x00036EA3.
// The same chain (Drawable+0xfc -> +0x204 -> +0x1cc -> override -> +0x70) is
// read by the landed Drawable::calcPhysicsXform at 0x004213F0. The accessors
// use their ledger owners; the six-argument target still has only its dump
// identity, d_00413a40 (ILT 0x00036EA3).
//
// Two shapes are load-bearing: the +0x204 read goes through an inline
// accessor inside the null ternary (retail keeps the xor eax,eax null arm
// instead of jump-threading it), and the kind read goes through a nullable
// accessor plus a one-level inline override walk (retail's register
// assignment: this=EDI, holder=EBX, first accessor result=ESI).
#define THING_TU_MEMBERS const Coord3D *getUnitDirectionVector2D() const;
#include "../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

extern void d_00413a40();

class BfmeThingRC
{
public:
	BfmeThingRC *getFinalRC()
	{
		if (m_bfmeInnerRC)
			return (BfmeThingRC *)m_bfmeInnerRC->getFinalOverride();
		return this;
	}

	unsigned char m_bfmeHeadRC[4];
	Overridable *m_bfmeInnerRC;
	unsigned char m_bfmeGapRC[0x68];
	int m_bfmeKindRC;
};

class BfmeHolderRC
{
public:
	BfmeThingRC *getThingRC() const
	{
		if (!m_bfmeThingRC)
			return 0;
		return m_bfmeThingRC->getFinalRC();
	}

	int m_bfmeSpareRC;
	BfmeThingRC *m_bfmeThingRC;
};

class BfmeStateRC
{
public:
	unsigned char m_bfmeHeadRC[0x1cc];
	BfmeHolderRC *m_bfmeHolderRC;
};

class BfmeUnitRC
{
public:
	BfmeStateRC *getStateRC() const { return m_bfmeStateRC; }

	unsigned char m_bfmeHeadRC[0x204];
	BfmeStateRC *m_bfmeStateRC;
};

class BfmeOwnerRC
{
public:
	char Rva0041EFD0(void *first, void *second);

	unsigned char m_bfmeHeadRC[0xfc];
	BfmeUnitRC *m_bfmeUnitRC;
};

char BfmeOwnerRC::Rva0041EFD0(void *first, void *second)
{
	BfmeUnitRC *unit = m_bfmeUnitRC;
	BfmeStateRC *state = unit ? unit->getStateRC() : 0;

	if (state)
	{
		BfmeHolderRC *holder = state->m_bfmeHolderRC;

		if (holder)
		{
			if (holder->getThingRC()->m_bfmeKindRC == 1)
			{
				const Coord3D *a = ((const BFMERopeDrawable *)this)->getPosition();
				const Coord3D *b = ((const Thing *)this)->getUnitDirectionVector2D();

				// The dump exports a free-function spelling, but retail uses
				// thiscall with six stack arguments. Keep that ABI at the call.
				union {
					void (*function)();
					char (BfmeOwnerRC::*method)(BfmeUnitRC *, BfmeHolderRC *,
						const Coord3D *, const Coord3D *, void *, void *);
				} target;
				target.function = d_00413a40;
				return (this->*target.method)(unit, holder, a, b, first, second);
			}
		}
	}

	return 0;
}
