// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
//
// Address-derived niladic member at retail 0x003BEC30 (167 bytes), carved
// boundary (targets/game/reverse/carved.csv line "0x003BEC30,167,rel32-call/jmp;ghidra-start").
// The symbol ?finish@Rva003BEED0@@QAEXXZ is the existing targets/game/reverse/symbols.csv pin
// ("niladic member tail-jumped by the two-call forwarder at 0x003BEED0");
// ILT 0x0000A754 reaches this body and seven callers go through it, among them
// ?run@Rva003BFAB0@@QAEX_N@Z and ?run@Rva003BFB20@@QAEXH@Z.  No semantic class
// name is asserted: only the member ABI below is proven.
//
// The receiver is a pointer-vector owner: begin/end at this+0x0c and this+0x10
// (the loop's [edi+0x10] - [edi+0xc] >> 2 count), a sub-owner pointer at
// this+0x28.  Each element with the byte flag at +0x1d set has its name copied
// through the existing incremental-link thunk j_0004958a (target 0x003A4390,
// ECX=element plus one out-string stack argument, returning that pointer),
// the copy is handed to the global at 0x012F0898 through j_00044391
// (target 0x00383830), and a result other than -1 is ranked through
// j_0002437a (target 0x003C6310, ECX=this+0x28) before j_000394e6
// (target 0x003A4BD0, ECX=element) consumes it.  The name string is retail's
// by-value return temporary, not a named local: retail arms its EH state
// (mov [esp+0x20],0) only after the copy call returns, and releases it through
// the existing ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ body at 0x00887940.

struct Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;

// The generated declarations carry the existing thunks' identities.  The typed
// casts are TU-local ABI information recovered from the aligned call sites;
// they create no alternatename and no new ledger pin.
extern void j_0004958a(void);
extern void j_00044391(void);
extern void j_0002437a(void);
extern void j_000394e6(void);

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	char *m_data;

private:
	void releaseBuffer();
};

struct Rva003BEC30Entry
{
	char m_pad00[0x1d];
	unsigned char m_flag1d;
};

struct Rva003BEC30NameView
{
	BFMERetailAsciiString copyName(void);
};
typedef BFMERetailAsciiString (Rva003BEC30NameView::*Rva003BEC30Name)(void);

struct Rva003BEC30LogicView
{
	int invoke(const BFMERetailAsciiString &name);
};
typedef int (Rva003BEC30LogicView::*Rva003BEC30Invoke)(
	const BFMERetailAsciiString &name);

struct Rva003BEC30TierView
{
	int tier(int value);
};
typedef int (Rva003BEC30TierView::*Rva003BEC30Tier)(int value);

struct Rva003BEC30FinishView
{
	void finish(int value);
};
typedef void (Rva003BEC30FinishView::*Rva003BEC30Finish)(int value);

struct Rva003BEC30Range
{
	Rva003BEC30Entry **m_begin;
	Rva003BEC30Entry **m_end;

	Rva003BEC30Entry **begin(void) const
	{
		return m_begin;
	}

	unsigned int size(void) const
	{
		return (unsigned int)(m_end - m_begin);
	}
};

class Rva003BEED0
{
public:
	void finish(void);

	char m_pad00[0x0c];
	Rva003BEC30Range m_entries;
	char m_pad14[0x14];
	Rva003BEC30TierView *m_tierOwner;
};

void Rva003BEED0::finish(void)
{
	Rva003BEED0 *owner = this;
	int value;
	int index = 0;
	if (owner->m_entries.size() > 0)
	{
		union { void (*raw)(void); Rva003BEC30Name member; } nameCast;
		union { void (*raw)(void); Rva003BEC30Invoke member; } invokeCast;
		union { void (*raw)(void); Rva003BEC30Tier member; } tierCast;
		union { void (*raw)(void); Rva003BEC30Finish member; } finishCast;
		nameCast.raw = j_0004958a;
		invokeCast.raw = j_00044391;
		tierCast.raw = j_0002437a;
		finishCast.raw = j_000394e6;
		do
		{
			Rva003BEC30Entry *entry = owner->m_entries.begin()[index];
			if (entry->m_flag1d != 0)
			{
				value = (reinterpret_cast<Rva003BEC30LogicView *>(
					TheBfmeGameLogic)->*invokeCast.member)(
					(reinterpret_cast<Rva003BEC30NameView *>(entry)
						->*nameCast.member)());
				if (value != -1)
				{
					int tier = (owner->m_tierOwner->*tierCast.member)(value);
					(reinterpret_cast<Rva003BEC30FinishView *>(entry)
						->*finishCast.member)(tier);
				}
			}
			++index;
		} while ((unsigned int)index < owner->m_entries.size());
	}
}
