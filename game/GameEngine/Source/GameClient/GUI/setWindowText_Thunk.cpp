// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z: game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp
// setWindowText, retail 0x004864E0 (416 bytes): reject an empty label, fetch
// the translated text from TheGameText, then hand it to the gadget setter the
// window style selects, else GameWindow::winSetText.
//
// The body is a file static that retail compiled with MSVC's private
// convention: its one caller (createWindow, 0x004874A0) passes the GameWindow
// in ESI and the by-value AsciiString label on the stack.
//
// [BFME 2 donor] Code/GameEngine/Source/GameClient/GUI/
// GameWindowManagerScript_setWindowText.cpp (45afcff3): the same static with a
// caller scaffold for the convention, and a UnicodeString whose copy
// constructor body is visible and makes a call, which stores esp into the
// temporary's unwind slot before `mov ecx,esp` at every by-value argument as
// retail does. The setters are called by their ledger names: style bit 0x01
// reaches 0x004BC6E0 and bit 0x02 0x004BD400, both through ILT thunks.

#include "string_base.h"

template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
	void translate(const AsciiString &that);
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24();
	virtual UnicodeString fetch(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

class GameWindow
{
public:
	unsigned int winGetStyle(void);
	virtual int winSetText(UnicodeString newText);
};

void GadgetRadioSetText(GameWindow *window, UnicodeString text);
void GadgetButtonSetText(GameWindow *window, UnicodeString text);	// 0x004BD400, GadgetPushButton.cpp
void GadgetCheckBoxSetText(GameWindow *window, UnicodeString text);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

// ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z
static __declspec(noinline) void setWindowText(GameWindow *window, AsciiString textLabel)
{
	if (textLabel.isEmpty())
		return;

	UnicodeString theText, entryText;
	theText = TheGameText->fetch(textLabel.str(), 0);
	if (window->winGetStyle() & 0x00000001)
		GadgetRadioSetText(window, theText);
	else if (window->winGetStyle() & 0x00000002)
		GadgetButtonSetText(window, theText);
	else if (window->winGetStyle() & 0x00000004)
		GadgetCheckBoxSetText(window, theText);
	else if (window->winGetStyle() & 0x00000080)
		GadgetStaticTextSetText(window, theText);
	else if (window->winGetStyle() & 0x00000040)
	{
		entryText.translate(textLabel);
		GadgetTextEntrySetText(window, entryText);
	}
	else
		window->GameWindow::winSetText(theText);
}

// ?bfme_setWindowTextCaller@@YAXPAVGameWindow@@ABVAsciiString@@@Z absent-from-retail
// Codegen scaffold standing in for createWindow (0x004874A0, matched in its own
// unit): a visible caller keeps the static emitted with the private convention.
void bfme_setWindowTextCaller(GameWindow *window, const AsciiString &label)
{
	setWindowText(window, label);
}
