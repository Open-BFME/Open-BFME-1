// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail calls HideControlBar(bool) through the five-byte ILT thunk at
// 0x00002847 (?j_00002847@@YAXXZ), not the 0x004C0C80 body directly.
extern void j_00002847();

typedef void (__cdecl *HideControlBarFn)(bool immediate);

void Rva002EF530()
{
	union { void (*raw)(); HideControlBarFn call; } hide;
	hide.raw = j_00002847;
	hide.call(1);
}
