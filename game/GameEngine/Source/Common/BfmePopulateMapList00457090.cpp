// cl: /DNDEBUG /MD
// Retail 0x00457090 (66 B): cdecl map-list flag builder called from both
// map-select menus (LanMapSelectMenuSystem 0x004D0820 via ILT 0x00029CEE,
// Rva00503FA0InitializeMapSelectMenu 0x00503FA0). Twin of the landed
// ?bfmeSendBL@@YAXPAXDD0@Z at 0x00457050 (51 B), which folds the same
// two-byte flag choice into one tail; this body keeps both call arms and
// needs a distinct barrier per arm so MSVC does not merge them.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

void __cdecl bfmeRunBL(void *first, int flags, void *last);

void __cdecl bfmePopulateMapListFlags(void *target, char first, char second, void *extra)
{
	int flags = (first == 0) ? 2 : 1;
	if (second != 0) {
		_WriteBarrier();
		bfmeRunBL(target, flags | 8, extra);
	} else {
		_ReadWriteBarrier();
		bfmeRunBL(target, flags | 4, extra);
	}
}
