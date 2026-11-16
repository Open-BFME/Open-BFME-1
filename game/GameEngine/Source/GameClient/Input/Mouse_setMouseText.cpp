// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?setMouseText@Mouse@@: game/GameEngine/Source/GameClient/Input/Mouse.cpp
// Identity: ILT 0x0002FBD0 -> 0x005A5950 (symbols.csv pin) and the two
// setCursor calls at 0x005A5A91/0x005A5AB2. BFME layout: display string +0x4DAC,
// text color +0x4DB0, drop color +0x4DC0.

#include "string_base.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


struct RGBAColorInt
{
	unsigned int red, green, blue, alpha;
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
};

class Mouse
{
public:
	void setMouseText(UnicodeString text, const RGBAColorInt *color,
	                  const RGBAColorInt *dropColor);

private:
	char m_pad0[0x4DAC];
	DisplayString *m_cursorTextDisplayString;
	RGBAColorInt m_cursorTextColor;
	RGBAColorInt m_cursorTextDropColor;
};

void Mouse::setMouseText(UnicodeString text, const RGBAColorInt *color,
                         const RGBAColorInt *dropColor)
{
	if (m_cursorTextDisplayString == 0)
		return;

	m_cursorTextDisplayString->setText(text);

	if (color)
		m_cursorTextColor = *color;
	if (dropColor)
		m_cursorTextDropColor = *dropColor;
}
