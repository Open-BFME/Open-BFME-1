// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Clear the drop-down's selection, then put the text in its entry field.
//
// winGetUserData is called twice rather than once into a local -- retail reissues
// it before the second use, which is the source naming the accessor again.
//
// The text parameter arrives by value and is passed on by value, so a copy is
// made; because arguments evaluate right to left that copy is built before the
// second winGetUserData call, which is exactly where retail puts it. The
// UnicodeString is the shim's, which is what makes the copy come out in retail's
// order at all.
#include "Common/UnicodeString.h"

typedef int Int;

class GameWindow;

struct ComboBoxData
{
	unsigned char m_head[0x28];
	GameWindow *m_entry;
	GameWindow *m_listBox;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
};

void GadgetListBoxSetSelected(GameWindow *listBox, Int index);
void GadgetTextEntrySetText(GameWindow *entry, UnicodeString text);

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
