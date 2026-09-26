// The retail helper at 0x00485460 copies the three draw-data states from an
// optional source window, falling back to the three supplied state arrays.
// Its callers are the slider/listbox/combobox setup paths in createGadget.

struct WinDrawData
{
	const void *image;
	unsigned int color;
	unsigned int borderColor;
};

enum { MAX_DRAW_DATA = 9 };

class WinInstanceData
{
public:
	char pad[0x18];
	WinDrawData m_enabledDrawData[MAX_DRAW_DATA];
	WinDrawData m_disabledDrawData[MAX_DRAW_DATA];
	WinDrawData m_hiliteDrawData[MAX_DRAW_DATA];
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData(void);
};

#pragma intrinsic(memcpy)
extern "C" void * __cdecl memcpy(void *destination, const void *source,
	unsigned int count);

#pragma comment(linker, "/alternatename:?winGetInstanceData@GameWindow@@QAEPAVWinInstanceData@@XZ=?j_00034991@@YAXXZ")

// ?Rva00485460CopyDrawData@@YAXPAVGameWindow@@0PAVWinDrawData@@111@Z
void Rva00485460CopyDrawData(GameWindow *destination, GameWindow *source,
	WinDrawData *enabledData, WinDrawData *disabledData,
	WinDrawData *hiliteData)
{
	WinInstanceData *destinationData;
	WinInstanceData *sourceData;

	if (destination == 0)
		return;

	destinationData = destination->winGetInstanceData();
	if (source != 0)
		sourceData = source->winGetInstanceData();
	else
		sourceData = 0;

	memcpy(destinationData->m_enabledDrawData,
		sourceData ? sourceData->m_enabledDrawData : enabledData,
		sizeof(WinDrawData) * MAX_DRAW_DATA);
	memcpy(destinationData->m_disabledDrawData,
		sourceData ? sourceData->m_disabledDrawData : disabledData,
		sizeof(WinDrawData) * MAX_DRAW_DATA);
	memcpy(destinationData->m_hiliteDrawData,
		sourceData ? sourceData->m_hiliteDrawData : hiliteData,
		sizeof(WinDrawData) * MAX_DRAW_DATA);
}
