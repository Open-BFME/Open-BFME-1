// ?bfmeOneCGF@BfmeOwnerCGF@@QAEXPAX@Z
// partial score=0.9 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: BfmeOwnerCGF::bfmeOneCGF at retail 0x003A01E0.
// The 0x0001D4B2 thunk and the bfmeGoCGF and Rva0039B2B0 callers identify this
// method. It transfers the 136-byte attribute entry held by this object.
//
// probe.py: ours=410B retail=437B, 274 non-reloc diffs, first at +0x38 (the
// first 0x38 bytes match retail exactly, including the xferVersion call).
// Two confirmed fixes over the prior 0.9 stash (author gpt-5, ours=443B,
// 285 diffs):
//   - `temporary` must be raw storage (UnsignedByte[sizeof(Gen00043699)]),
//     not an automatic Gen00043699 local. The prior stash declared both
//     `Gen00043699 temporary(0);` and `Gen00043699 entry;` as normal locals,
//     which auto-constructs/destructs BOTH and emits two separate EH-state
//     transitions; retail's disassembly has exactly ONE constructor call
//     (0xffc67e87, relative) before the first isSaving() branch, reused
//     again at the placement-new site inside the branch, so `temporary`'s
//     lifetime must start only at `new (temporaryStorage) Gen00043699` and
//     end only at the explicit `~Gen00043699()` call, never through
//     automatic construction.
//   - `source` must be assigned lazily, in an explicit `else { source =
//     &entry; }` of the `if (xfer->isSaving())`, not eagerly initialized
//     before the branch. Retail's `lea edi,[esp+0x18]` (the `&entry`
//     computation) sits physically AFTER the isSaving()-true block's code,
//     immediately before an unconditional `jmp` from the true block skips
//     over it -- the textbook "then-block; jmp past; else-block; merge"
//     layout of `if (cond) {..} else { source = &entry; }`. Initializing
//     `source = &entry` unconditionally up front (as the prior stash did)
//     computes that address too early and drops the sourced skip-over jump.
// Still unresolved: retail keeps `owner` (this) in ebp for the whole
// function and reserves ebx purely for the late `index` variable in the
// closing linear-search loop (confirmed by grepping every ebx/ebp use in
// the full retail disassembly -- ebx is untouched between the version-byte
// scratch write near the top and `xor ebx,ebx` at the loop). Every source
// variant tried here (this one, `index` at function scope vs. loop scope,
// `register` on/off) instead puts `owner` in ebx and burns ebp as a
// scratch zero register for one of the EH-state-slot stores, where retail
// uses a bare immediate (`mov dword ptr [esp+0x130], 0`) with no register
// at all. That register-preference difference, and a related instruction-
// width difference in the EH state stores (retail narrows a later store of
// the same slot to a single byte; ours does not), are unresolved and drive
// most of the remaining 274 diffs.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

__declspec(align(4)) struct BfmeVersion
{
	UnsignedByte m_major;
	UnsignedByte m_minor;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual void slot04();
	virtual bool isSaving();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(BfmeVersion *version);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void xferBool(void *value);
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void xferInt(void *value);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
};

struct BfmePtrVec
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

class BfmeAttributePlainBlock
{
public:
	void xfer(Xfer *xfer);

	UnsignedInt m_values[6];
};

class Gen00043699
{
public:
	Gen00043699();
	Gen00043699(int) {}
	~Gen00043699();
	bool operator==(const Gen00043699 &other) const;

	BfmePtrVec m_names;
	BfmePtrVec m_values;
	BfmePtrVec m_list0;
	BfmePtrVec m_list1;
	BfmePtrVec m_list2;
	BfmePtrVec m_list3;
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	UnsignedInt m_kind;
	UnsignedInt m_index;
	UnsignedByte m_enabled;
	UnsignedByte m_pad[3];
	UnsignedInt m_useCount;
};

struct BfmeAttributePool
{
	Gen00043699 *m_start;
	Gen00043699 *m_finish;
	Gen00043699 *m_end;
};

extern BfmeAttributePool TheBfmeAttributePool;
extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);
extern void bfmeProcessAttributeEntry(Gen00043699 *entry);

class BfmeOwnerCGF
{
public:
	void bfmeOneCGF(void *what);
	void transferAttributeStrings(Xfer *xfer, void *vector);
	void transferAttributeVectors(Xfer *xfer, void *first, void *second);

private:
	UnsignedInt m_handle;
};

void BfmeOwnerCGF::bfmeOneCGF(void *what)
{
	register Xfer *xfer = (Xfer *)what;
	register BfmeOwnerCGF *owner = this;
	BfmeVersion version = { 1, 1 };
	xfer->xferVersion(&version);
	// Raw storage, not a Gen00043699 local: an automatic Gen00043699 object
	// here would auto-construct/destruct and add its own EH unwind state,
	// but retail's disassembly shows exactly one constructor call before the
	// branch (entry's), so this stays uninitialized bytes until the
	// placement new below runs.
	__declspec(align(4)) UnsignedByte temporaryStorage[sizeof(Gen00043699)];
	Gen00043699 entry;
	register Gen00043699 *source;

	if (xfer->isSaving())
	{
		if (owner->m_handle == BFME_NO_ATTRIBUTE_HANDLE)
		{
			owner->m_handle = bfmeInternAttributeEntry(
				new (temporaryStorage) Gen00043699);
			((Gen00043699 *)temporaryStorage)->~Gen00043699();
		}

		source = TheBfmeAttributePool.m_start + owner->m_handle;
	}
	else
	{
		source = &entry;
	}

	((Xfer *)xfer)->xferBool((char *)source + 0x80);
	((Xfer *)xfer)->xferInt((char *)source + 0x78);
	((BfmeAttributePlainBlock *)((char *)source + 0x48))->xfer(xfer);
	((BfmeAttributePlainBlock *)((char *)source + 0x60))->xfer(xfer);
	((Xfer *)xfer)->xferInt((char *)source + 0x7C);

	if (xfer->isSaving())
	{
		owner->transferAttributeVectors(xfer, (char *)source + 0x18,
			(char *)source + 0x30);
		owner->transferAttributeVectors(xfer, (char *)source + 0x24,
			(char *)source + 0x3C);
	}
	else
	{
		transferAttributeStrings(xfer, (char *)source + 0x00);
		transferAttributeStrings(xfer, (char *)source + 0x0C);
		bfmeProcessAttributeEntry(source);

		int count = (int)(TheBfmeAttributePool.m_finish
			- TheBfmeAttributePool.m_start);
		if (count > 0)
		{
			register int index = 0;
			Gen00043699 *candidate = TheBfmeAttributePool.m_start;
			do
			{
				if (*candidate == *source)
				{
					owner->m_handle = index;
					break;
				}
				++index;
				++candidate;
			}
			while (index < (UnsignedInt)count);
		}
	}
}
