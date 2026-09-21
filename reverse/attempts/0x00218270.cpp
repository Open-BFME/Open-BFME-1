// ?Rva00218270Sweep@@YGXPAVRva00218270Wrap@@@Z (owner identity unknown)
// partial score=0.92 date=2026-09-07
// 81/81 bytes. Shape is settled and both copies of the inlined next() line up:
// the first next() must be PEELED (`thing = next(); while (thing) { ...; thing
// = next(); }`) -- a `while ((thing = next()))` collapses the two copies into
// one rotated loop at 54 bytes -- and the advance must be a post-increment in
// the return statement (`return (m_cur++)->m_thing;`), which is what makes the
// size exact.
// Residue: a whole-body register mirror. Retail keeps *wrap in ecx, so the
// cursor lands in eax and needs `mov edx,eax` before the load; MSVC keeps *wrap
// in edx, puts the cursor in ecx and skips the copy, spending the saved bytes
// on `jmp` + padding where retail has a 3-byte `lea ecx,[ecx]` align nop.
// 15 of 30 instructions differ, all by register name only. /G7, /Oy and /Ob1
// change nothing. ecx/edx-flip class.
class ExperienceTracker
{
public:
	bool gainExpForLevel(int levelsToGain, bool canScaleForBonus,
		bool provideFeedback);
};

class Rva00218270Thing
{
public:
	unsigned char m_unmodelled[0x210];
	ExperienceTracker *m_experienceTracker;
};

struct Rva00218270Slot
{
	Rva00218270Thing *m_thing;
	int m_unmodelled;
};

class Rva00218270Cursor
{
public:
	Rva00218270Thing *next(void)
	{
		if (m_bfmeCurKQ == m_bfmeEndKQ)
			return 0;

		return (m_bfmeCurKQ++)->m_thing;
	}

	int m_bfmeHeadKQ;
	Rva00218270Slot *m_bfmeEndKQ;
	int m_bfmeSpareKQ;
	Rva00218270Slot *m_bfmeCurKQ;
};

class Rva00218270Wrap
{
public:
	Rva00218270Cursor *m_cursor;
};

void __stdcall Rva00218270Sweep(Rva00218270Wrap *wrap)
{
	Rva00218270Thing *thing = wrap->m_cursor->next();

	while (thing)
	{
		if (thing->m_experienceTracker)
			thing->m_experienceTracker->gainExpForLevel(1, true, false);

		thing = wrap->m_cursor->next();
	}
}
