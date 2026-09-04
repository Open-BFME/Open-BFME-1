// ?sweep_Rva00699AF0@@YAXPAX@Z
// partial score=0.79 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Guarded TheAudio sweep: three 0x1C4-byte blocks at +0xB8, each visited
// with a (arg, 0) and (arg, 1) thiscall into the ILT at 0x00019E6B.
// Near-miss: retail hoists lea ecx before xor esi and reuses ecx across the
// inner calls; MSVC 7.1 reloads TheAudio/lea inside the inner loop (13B).

class Rva00699AF0Block
{
public:
	void apply(void *arg, int which);
};

extern char *TheAudio;

void sweep_Rva00699AF0(void *arg)
{
	if (TheAudio)
	{
		void *held = arg;
		for (int offset = 0; offset < 0x54C; offset += 0x1C4)
		{
			for (int which = 0; which < 2; ++which)
				((Rva00699AF0Block *)(TheAudio + 0xB8 + offset))->apply(held, which);
		}
	}
}
