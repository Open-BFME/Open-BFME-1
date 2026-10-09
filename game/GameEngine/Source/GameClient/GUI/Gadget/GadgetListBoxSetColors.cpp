// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BFME's ListboxData child slots are at +0x1c/+0x20/+0x24, four bytes after
// the vendored ZH declaration.  The retail body also proves GameWindow's
// draw-data arrays at +0x48/+0xb4/+0x120 (see IMECandidateMainDraw.cpp).
// Keep this ABI slice TU-local: changing the shared ZH headers would move
// already matched GameWindow and GadgetListBox bodies.

typedef int Color;

struct Image;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
	int winSetEnabledColor(int index, Color color);
	int winSetEnabledBorderColor(int index, Color color);
	int winSetDisabledColor(int index, Color color);
	int winSetDisabledBorderColor(int index, Color color);
	int winSetHiliteColor(int index, Color color);
	int winSetHiliteBorderColor(int index, Color color);
	GameWindow *winGetChild(void);

	// Retail inlines these reads; use the fields without emitting getter copies.
	unsigned char m_bfmeHead[0x48];
	WinDrawData m_enabledDrawData[9];
	WinDrawData m_disabledDrawData[9];
	WinDrawData m_hiliteDrawData[9];
};

struct BFMEListboxDataView
{
	// Retail xrefs and the matched BFME list-box helpers establish the child
	// slots below; the preceding BFME-only portion is not used by this body.
	unsigned char m_unreconstructed_00[0x1c];
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
};

void GadgetListBoxSetColors(GameWindow *listbox,
	Color enabledColor,
	Color enabledBorderColor,
	Color enabledSelectedItemColor,
	Color enabledSelectedItemBorderColor,
	Color disabledColor,
	Color disabledBorderColor,
	Color disabledSelectedItemColor,
	Color disabledSelectedItemBorderColor,
	Color hiliteColor,
	Color hiliteBorderColor,
	Color hiliteSelectedItemColor,
	Color hiliteSelectedItemBorderColor)
{
	BFMEListboxDataView *listboxData =
		(BFMEListboxDataView *)listbox->winGetUserData();

	listbox->winSetEnabledColor(0, enabledColor);
	listbox->winSetEnabledBorderColor(0, enabledBorderColor);
	listbox->winSetEnabledColor(1, enabledSelectedItemColor);
	listbox->winSetEnabledBorderColor(1, enabledSelectedItemBorderColor);
	listbox->winSetDisabledColor(0, disabledColor);
	listbox->winSetDisabledBorderColor(0, disabledBorderColor);
	listbox->winSetDisabledColor(1, disabledSelectedItemColor);
	listbox->winSetDisabledBorderColor(1, disabledSelectedItemBorderColor);
	listbox->winSetHiliteColor(0, hiliteColor);
	listbox->winSetHiliteBorderColor(0, hiliteBorderColor);
	listbox->winSetHiliteColor(1, hiliteSelectedItemColor);
	listbox->winSetHiliteBorderColor(1, hiliteSelectedItemBorderColor);

	GameWindow *slider = listboxData->slider;
	if (slider)
	{
		GameWindow *upButton = listboxData->upButton;
		GameWindow *downButton = listboxData->downButton;

		slider->winSetEnabledColor(0, listbox->m_enabledDrawData[0].color);
		slider->winSetEnabledBorderColor(0, listbox->m_enabledDrawData[0].borderColor);
		slider->winSetDisabledColor(0, listbox->m_disabledDrawData[0].color);
		slider->winSetDisabledBorderColor(0, listbox->m_disabledDrawData[0].borderColor);
		slider->winSetHiliteColor(0, listbox->m_hiliteDrawData[0].color);
		slider->winSetHiliteBorderColor(0, listbox->m_hiliteDrawData[0].borderColor);

		upButton->winSetEnabledColor(0, slider->m_enabledDrawData[0].color);
		upButton->winSetEnabledBorderColor(0, slider->m_enabledDrawData[0].borderColor);
		GameWindow *thumb = slider->winGetChild();
		upButton->winSetEnabledColor(1, thumb ? thumb->m_enabledDrawData[1].color : 0x00FFFFFF);
		thumb = slider->winGetChild();
		upButton->winSetEnabledBorderColor(1, thumb ? thumb->m_enabledDrawData[1].borderColor : 0x00FFFFFF);
		upButton->winSetDisabledColor(0, slider->m_disabledDrawData[0].color);
		upButton->winSetDisabledBorderColor(0, slider->m_disabledDrawData[0].borderColor);
		thumb = slider->winGetChild();
		upButton->winSetDisabledColor(1, thumb ? thumb->m_disabledDrawData[1].color : 0x00FFFFFF);
		thumb = slider->winGetChild();
		upButton->winSetDisabledBorderColor(1, thumb ? thumb->m_disabledDrawData[1].borderColor : 0x00FFFFFF);
		upButton->winSetHiliteColor(0, slider->m_hiliteDrawData[0].color);
		upButton->winSetHiliteBorderColor(0, slider->m_hiliteDrawData[0].borderColor);
		thumb = slider->winGetChild();
		upButton->winSetHiliteColor(1, thumb ? thumb->m_hiliteDrawData[1].color : 0x00FFFFFF);
		thumb = slider->winGetChild();
		upButton->winSetHiliteBorderColor(1, thumb ? thumb->m_hiliteDrawData[1].borderColor : 0x00FFFFFF);

		downButton->winSetEnabledColor(0, slider->m_enabledDrawData[0].color);
		downButton->winSetEnabledBorderColor(0, slider->m_enabledDrawData[0].borderColor);
		thumb = slider->winGetChild();
		downButton->winSetEnabledColor(1, thumb ? thumb->m_enabledDrawData[1].color : 0x00FFFFFF);
		thumb = slider->winGetChild();
		downButton->winSetEnabledBorderColor(1, thumb ? thumb->m_enabledDrawData[1].borderColor : 0x00FFFFFF);
		downButton->winSetDisabledColor(0, slider->m_disabledDrawData[0].color);
		downButton->winSetDisabledBorderColor(0, slider->m_disabledDrawData[0].borderColor);
		thumb = slider->winGetChild();
		downButton->winSetDisabledColor(1, thumb ? thumb->m_disabledDrawData[1].color : 0x00FFFFFF);
		thumb = slider->winGetChild();
		downButton->winSetDisabledBorderColor(1, thumb ? thumb->m_disabledDrawData[1].borderColor : 0x00FFFFFF);
		downButton->winSetHiliteColor(0, slider->m_hiliteDrawData[0].color);
		downButton->winSetHiliteBorderColor(0, slider->m_hiliteDrawData[0].borderColor);
		thumb = slider->winGetChild();
		downButton->winSetHiliteColor(1, thumb ? thumb->m_hiliteDrawData[1].color : 0x00FFFFFF);
		thumb = slider->winGetChild();
		downButton->winSetHiliteBorderColor(1, thumb ? thumb->m_hiliteDrawData[1].borderColor : 0x00FFFFFF);
	}
}
