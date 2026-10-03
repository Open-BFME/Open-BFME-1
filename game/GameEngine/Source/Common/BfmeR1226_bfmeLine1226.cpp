struct BfmeStringBlock1226
{
	unsigned short m_refs;
};

// The allocator-hook table this string block is released through.  The pointer
// to it is retail VA 0x01337A30, which the ledger's data row
// ?g_rva01337A30AllocPair@@3PAUBfmeStringPool3AF0@@A defines once, in
// game/Libraries/Source/Apt/Apt.cpp; this file used a second spelling
// (g_bfmeStringPool1284) that nothing defined, so the reference is respelled to
// the defined name and the DIR32 target is unchanged.  Only slot +4 (the free
// callback) is called here, as at the other 275 call sites.
struct BfmeStringPool3AF0
{
	void *m_alloc;
	void (__cdecl *m_free)(void *storage);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

// The shared empty EA string block at 0x012D5298 is defined once, with its
// proven type, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  It is
// named here through a file-local view cast at each use so the DIR32 target is
// the one retail address.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

static inline BfmeStringBlock1226 *rva012D5298Block()
{
	return (BfmeStringBlock1226 *)&g_rva012D5298Empty;
}
// Retail VA 0x0133783C is one cell of the thirty-three-slot runtime hook run at
// 0x01337800 that the matched installer
// game/GameEngine/Source/Common/BfmeOneHundredTwentyThree.cpp fills in
// ?bfmeInstallHandlersVB@@YAXXZ (RVA 0x00789440, 331 B).  That body's
//     mov dword ptr [0x133783c], 0x00B83210
// at RVA 0x00789468 is the sole writer and proves both the four-byte size and the
// callee: the ledger already owns 0x00B83210 as
// ?Rva00783210Format@@YAXPBDZZ, a cdecl void(char const *, ...) -- which is exactly
// the printf-style two-argument, caller-cleans shape both calls below use.  Three
// neighbouring cells of the same run already carry landed data rows
// (0x01337828 ?Rva008C5D70Alloc, 0x0133782C ?g_bfmeFreeDWF, 0x01337830
// ?TheBfmeFree); this one does not yet, and it is the name the proven writer TU
// itself declares (`extern BfmeProcVB g_bfmeSlot04VB;` and
// `g_bfmeSlot04VB = bfmeHandler04VB;`), so the reference is respelled from the
// invented _g_bfmeCallback1226 -- which no object defines and no owner TU uses -- to
// that owner spelling.  The DIR32 target is unchanged.
//
// NOTE for the parent: the size (4) and the ABI are proven above, but unlike
// VA 0x012F1000 this cell has no landed identity_evidence document, and the three
// landed sibling rows each chose a callee-derived name
// (?Rva008C5D70Alloc / ?g_bfmeFreeDWF / ?TheBfmeFree) rather than the writer's
// g_bfmeSlotNNVB spelling.  If the row lands under such a name, revert the two
// call-site casts here back to a bare call and this file is unblocked by it.
// The pointer's type must stay `void (*)(void)` -- the shape
// BfmeOneHundredTwentyThree.cpp gives BfmeProcVB -- because the type is inside the
// mangling and the row has to spell ?g_bfmeSlot04VB@@3P6AXXZA.  The proven callee
// takes (char const *, ...); that view is cast in at each call below, exactly as
// this file already casts g_rva01337A30AllocPair and g_rva012D5298Empty.
typedef void (__cdecl *BfmeProc1226)(void);
extern BfmeProc1226 g_bfmeSlot04VB;

class BfmeString1226
{
public:
	BfmeString1226()
	{
		++rva012D5298Block()->m_refs;
		m_block = rva012D5298Block();
	}

	~BfmeString1226()
	{
		BfmeStringBlock1226 *block = m_block;
		if (--block->m_refs == 0)
			g_rva01337A30AllocPair->m_free(block);
	}

	BfmeStringBlock1226 *m_block;
};

class Rva8CD130String;

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *out);
	virtual void slot00();
	virtual void release();
};

class BfmeR1226
{
public:
	void bfmeLine1226(char *text);

	char m_padding00[0x7c];
	Rva8CD130Value *m_pending;
};

void BfmeR1226::bfmeLine1226(char *text)
{
	Rva8CD130Value *pending = m_pending;
	if (pending != 0)
	{
		BfmeString1226 name;
		pending->getName((Rva8CD130String *)&name);
		((void (__cdecl *)(const void *, const void *))g_bfmeSlot04VB)(
			"<WARNING> Actionscript un-caught exception encountered during \"%s\"\n", text);
		((void (__cdecl *)(const void *, const void *))g_bfmeSlot04VB)(
			"<WARNING> Actionscript error message: \"%s\"\n",
			(char *)name.m_block + 8);
		m_pending->release();
		m_pending = 0;
	}
}
