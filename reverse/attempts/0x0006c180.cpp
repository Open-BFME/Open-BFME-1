// ?rotate@Rva6C180@@QAEXH@Z
// partial score=0.05 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: retail 0x0006C180, 430 bytes. Real identity unproven -- landed
// under an address-derived name (partial only, banked). Evidence in
// re_attempts.log / re_log notes: builds a rotated log/backup file path.
// Reads [ecx+0x10] (an already-open-count field on the object) and a stack
// arg clamped to [1,7] (a rotation slot count), then: GetModuleFileNameA
// (0x01358DC0) into a 0x200-byte stack buffer, GetEnvironmentStrings
// (0x01358D90) and walks its double-NUL-terminated block, GetCommandLineA
// (0x01358D5C), malloc (0x0135944C) sized off that walk plus 0x3E8, sprintf
// (0x0135948C) twice against string literals at 0x1075D0C / 0x1075CF4 (likely
// "%s%d" / directory-style formats -- not yet read out), strrchr (0x013594C8)
// to find the extension, then a loop of `slot count` iterations doing a
// second GetModuleFileNameA + more sprintf-style formatting against a literal
// at 0x1075CE8, ending with a FindFirstFile/FindNextFile-shaped call through
// [0x1358CFC] and bfmeFree1035 (__imp_?bfmeFree1035@@YAXPAX@Z, 0x013593D4) to
// release the malloc'd buffer. No ZH twin found under this exact shape in
// debug_io_flat.cpp / StackDump.cpp / MemoryInit.cpp (all share GetModuleFileName
// + strrchr + sprintf idioms individually, none combines GetEnvironmentStrings
// the same way) -- likely BFME-original log-rotation code, not a ZH port.
// Only a compiling skeleton with the entry shape (esp&-8 align, 0x274-byte
// frame, ebx/esi/edi saved) was produced in this session; the interior is
// NOT yet a faithful port.

extern "C" void *__cdecl memset(void *, int, unsigned int);

class Rva6C180 { public: void rotate(int slotCount); };

void Rva6C180::rotate(int slotCount)
{
	char pathBuf[0x200];
	char scratch[0x208];
	char work[0x44];
	memset(pathBuf, 0, sizeof(pathBuf));
	memset(scratch, 0, sizeof(scratch));
	memset(work, 0, sizeof(work));

	int clamped = slotCount;
	if (clamped > 7)
		clamped = 7;
	if (clamped < 1)
		return;

	for (int i = 1; i <= clamped; ++i)
	{
		pathBuf[0] = (char)i;
		scratch[0] = pathBuf[0];
	}
}
