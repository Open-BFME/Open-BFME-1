// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DisconnectMenu::showChat, retail 0x0050EF20, 112 bytes.
//
// The reference's body with the lookup gone: BFME keeps the display control in
// the menu at this+0x258 instead of finding it by name each time, and does not
// test it before use.  What is left is one call, and almost all the bytes are
// the by-value UnicodeString the callee takes -- copy-constructed into the
// outgoing slot and destroyed after, which is what the SEH frame is for.
//
// The list box call takes a sixth argument BFME added, passed true.

typedef int Int;
typedef bool Bool;

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase(const StringBase<T> &src);			// 0x00888400
	~StringBase();						// 0x008881D0

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>	// G is unsigned short: MSVC 7.1 without /Zc:wchar_t
{
};

class GameWindow;

Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Int color, Int row, Int column, Bool overwrite);	// ILT 0x0003FE86

extern Int chatNormalColor;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	void showChat(UnicodeString text);

private:
	unsigned char m_unmodelled_000[0x258];
	GameWindow *m_textDisplayControl;			// this+0x258
};

void DisconnectMenu::showChat(UnicodeString text)
{
	GadgetListBoxAddEntryText(m_textDisplayControl, text, chatNormalColor, -1, -1, true);
}
