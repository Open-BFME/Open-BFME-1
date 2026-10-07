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

// The callee is ILT 0x0002126F -> 0x00456A90, matched as the map listbox
// population routine (its int result is unused here).
class GameWindow;
class AsciiString;
int __cdecl populateMapListboxRva00456A90(GameWindow *listbox, unsigned int flags, const AsciiString &selected);

void __cdecl bfmePopulateMapListFlags(void *target, char first, char second, void *extra)
{
	int flags = (first == 0) ? 2 : 1;
	if (second != 0) {
		_WriteBarrier();
		populateMapListboxRva00456A90((GameWindow *)target, flags | 8, *(const AsciiString *)extra);
	} else {
		_ReadWriteBarrier();
		populateMapListboxRva00456A90((GameWindow *)target, flags | 4, *(const AsciiString *)extra);
	}
}
