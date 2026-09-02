// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib
//
// WindowManager::hideAptWindow.  Index is thiscall, slots live at this+0xa8
// with stride 0x14, and a set flag-bit 1 at slot+0x10 is required.  TheMouse
// (0x012F4C5C) gets an empty tooltip first; the UnicodeString by-value
// temporary needs the stringbaseunicode shim so the ctor emits retail's
// `mov [esp+N],esp` / `mov ecx,esp` order.  The inner hide is the already-
// pinned ILT 0x0003F3E1 (?bfmeHide1183@BfmeW1183@@QAEXI@Z).

#include <wchar.h>
#include "Common/UnicodeString.h"

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

extern Mouse *TheMouse;

class WindowManager
{
public:
	bool hideAptWindow(int index);
	bool hideAptWindowInternal(int index);

private:
	char m_unmodelled[0xA8];
	struct Slot
	{
		char m_unmodelled_00[0x10];
		unsigned char m_flags;
		char m_pad[3];
	} m_aptWindows[12];
};

bool WindowManager::hideAptWindow(int index)
{
	if (static_cast<unsigned int>(index) >= 12)
		return false;

	Slot &window = m_aptWindows[index];
	if (TheMouse)
		TheMouse->setCursorTooltip(UnicodeString::TheEmptyString, 0, 0, 1.0f);

	if (!(window.m_flags & 2))
		return false;

	return hideAptWindowInternal(index);
}
