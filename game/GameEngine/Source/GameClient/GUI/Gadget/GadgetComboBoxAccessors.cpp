// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/languagefilter /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// The three combo-box accessors that live outside GadgetComboBox.cpp:
//
//   GadgetComboBoxGetText       0x004B3xxx   the edit field's text, or empty
//   GadgetComboBoxSetText       0x004B3xxx   clear the selection, set the text
//   GadgetComboBoxSetIsEditable 0x004B38B0   64 B
//
// All three reach the same record through winGetUserData, and all three named
// it differently: two called the field at +0x28 m_entry, the third called it
// editBox, and the third also proved the editable flag at +0x00 that the other
// two never look at. One struct now, with every field either file had.
//
// Two things in these bodies are deliberate and neither survives being
// "cleaned up":
//
//   winGetUserData is called twice rather than once into a local, in SetText
//   and in SetIsEditable both. Retail reissues it, and the second call is what
//   the source is naming.
//
//   SetText keeps its two accessors INSIDE the argument lists. Arguments
//   evaluate right to left, so the by-value UnicodeString copy is built before
//   the second winGetUserData call, which is exactly where retail puts it;
//   hoisting the accessor to its own statement swaps the two.
//
// The UnicodeString is the languagefilter shim's, not the Zero Hour header's:
// retail's `return UnicodeString::TheEmptyString` encodes 0x00888400 =
// ??0?$StringBase@G@@AAE@ABV0@@Z, so the string body lives on
// StringBase<WideChar> with UnicodeString as its friend and the forwarding copy
// constructor inlined at the call site. The Zero Hour header would emit
// ??0UnicodeString@@QAE@ABV0@@Z instead. The private /I is what keeps that
// spelling out of GadgetComboBox.cpp.
//
// Probed before merging: the three carried three different flag lines, and
// SetText's is a superset of the other two. All three still matched under it,
// unchanged otherwise.

#include "Common/UnicodeString.h"

typedef int Int;

enum { GWS_COMBO_BOX = 0x00008000 };	// GameClient/Gadget.h

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetComboBox.h
struct ComboBoxData
{
	bool m_isEditable;					// +0x00
	unsigned char m_head[0x28 - 1];
	GameWindow *m_entry;					// +0x28, the edit box
	GameWindow *m_listBox;					// +0x2c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	UnsignedInt winGetStyle(void);
	void *winGetUserData(void);
	unsigned int winClearStatus(unsigned int status);
	unsigned int winSetStatus(unsigned int status);
};

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetTextEntrySetText(GameWindow *entry, UnicodeString text);
void GadgetListBoxSetSelected(GameWindow *listBox, Int index);

// ?GadgetComboBoxGetText@@YA?AVUnicodeString@@PAVGameWindow@@@Z
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox)
{

	// sanity
	if (comboBox == NULL)
		return UnicodeString::TheEmptyString;

	// verify that this is a combo box
	if (BitTest(comboBox->winGetStyle(), GWS_COMBO_BOX) == FALSE)
		return UnicodeString::TheEmptyString;

	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	return GadgetTextEntryGetText(
		comboBoxData && comboBoxData->m_entry ? comboBoxData->m_entry : NULL);
}

// Both accessors stay inside the argument lists via these. Hoisting the
// user-data call to its own statement evaluates it before the string copy,
// where retail -- evaluating right to left -- builds the copy first.
static GameWindow *comboListBox(GameWindow *comboBox)
{
	ComboBoxData *data = (ComboBoxData *)comboBox->winGetUserData();
	return data && data->m_listBox ? data->m_listBox : 0;
}

static GameWindow *comboEntry(GameWindow *comboBox)
{
	ComboBoxData *data = (ComboBoxData *)comboBox->winGetUserData();
	return data && data->m_entry ? data->m_entry : 0;
}

// ?GadgetComboBoxSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z
void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text)
{
	if (!comboBox)
		return;

	GadgetListBoxSetSelected(comboListBox(comboBox), -1);
	GadgetTextEntrySetText(comboEntry(comboBox), text);
}

// ?GadgetComboBoxSetIsEditable@@YAXPAVGameWindow@@_N@Z
void GadgetComboBoxSetIsEditable(GameWindow *comboBox, bool isEditable)
{
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	ComboBoxData *componentData = (ComboBoxData *)comboBox->winGetUserData();
	GameWindow *editBox = componentData ? componentData->m_entry : 0;

	if (!editBox)
		return;

	comboData->m_isEditable = isEditable;
	if (isEditable)
		editBox->winClearStatus(0x600);
	else
		editBox->winSetStatus(0x600);
}
