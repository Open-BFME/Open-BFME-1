// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /I.
typedef unsigned short wchar_t;
// The body at 0x0040F160 has no named caller or proven owner, so keep its
// owner and method RVA-qualified. The manager and DisplayString slots used
// here are grounded by GameWindowTransitionsStyles.cpp and SuperweaponInfo.cpp.
#include "reference/shims/stringbaseunicode/Common/UnicodeString.h"

typedef unsigned int UnsignedInt;
typedef float Real;

class GameFont;
class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void setText(UnicodeString text) = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void setFont(GameFont *font) = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setColors(UnsignedInt color, UnsignedInt dropColor) = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void drawAtOffsets(int x, int y, int xDrop, int yDrop) = 0;
	virtual void slot3C() = 0;
	virtual int getWidth(int line) = 0;
};

class Rva0048EC80Manager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual DisplayString *newDisplayString() = 0;
};
extern Rva0048EC80Manager *Rva0048EC80TheManager;

class Rva0040F160
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual UnsignedInt slot2C() = 0;
	virtual UnsignedInt slot30() = 0;

	DisplayString *rva0040F160();

private:
	unsigned char m_pad04[0xA8];
	UnicodeString m_text;
	GameFont *m_font;
	UnsignedInt m_color;
	UnsignedInt m_dropColor;
	unsigned char m_opaqueBC[4];
	Real m_factorC0;
	Real m_resultC4;
	Real m_resultC8;
};

DisplayString *Rva0040F160::rva0040F160()
{
	const wchar_t *text = *reinterpret_cast<const wchar_t *const *>(&m_text);
	if (text == 0)
		return 0;
	if (*reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(text) + 4) == 0)
		return 0;

	DisplayString *display = Rva0048EC80TheManager->newDisplayString();
	if (display != 0)
	{
		display->setFont(m_font);
		display->setText(m_text);
		display->setColors(m_color, m_dropColor);

		UnsignedInt width = display->getWidth(-1);
		UnsignedInt offset = slot2C() - width;
		m_resultC4 = (Real)(offset >> 1);
		m_resultC8 = (Real)slot30() * m_factorC0;
	}
	return display;
}
