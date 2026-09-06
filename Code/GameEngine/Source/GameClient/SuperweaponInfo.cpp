// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?setFont@SuperweaponInfo@@QAEXABVAsciiString@@H_N@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ?drawName@SuperweaponInfo@@QAEXHHHH@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ?drawTime@SuperweaponInfo@@QAEXHHHH@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ??1SuperweaponInfo@@MAE@XZ: Code/GameEngine/Source/GameClient/InGameUI.cpp
//
// Four members of one class, so they need one declaration of it. Each body used
// to sit in its own file with its own partial view of SuperweaponInfo and of
// DisplayString, and the four views disagreed: three called the vtable pointer
// m_vtable while the destructor let the virtual destructor place it, and the
// same word at +0x0c was `Color m_color` in one file and `unsigned int m_color`
// in another.
//
// The layout below is the union those four views describe. The vtable pointer
// comes from the virtual destructor rather than a named m_vtable field, which
// puts the two DisplayString pointers at +0x04 and +0x08, the color at +0x0c,
// and the power template, name and tail that only the destructor sees after
// them. Every offset any of the four bodies touches is unchanged.
//
// DisplayString is likewise one table instead of three prefixes of one. The
// slots the bodies reach are setFont at +0x18, setColors at +0x28,
// drawAtOffsets at +0x38 and getWidth at +0x40; the rest are named for their
// offsets because these bodies do not say what they are.

typedef int Int;
typedef int Color;
typedef float Real;
typedef bool Bool;

class GameFont;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void setFont(GameFont *font) = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setColors(Color color, Color dropColor) = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void drawAtOffsets(Int x, Int y, Int xDrop, Int yDrop) = 0;
	virtual void slot3C() = 0;
	virtual Int getWidth(Int charPos) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void freeDisplayString(DisplayString *string) = 0;
};

class GlobalLanguageData
{
public:
	Int adjustFontSize(Int point);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameFont.h
class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, unsigned char bold);
};

extern DisplayStringManager *TheDisplayStringManager;
extern GlobalLanguageData *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class SuperweaponInfo
{
public:
	void setFont(const AsciiString &fontName, Int pointSize, Bool bold);
	void drawName(Int x, Int y, Color color, Color dropColor);
	void drawTime(Int x, Int y, Color color, Color dropColor);

protected:
	virtual ~SuperweaponInfo();

private:
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;
	Color m_color;
	const void *m_powerTemplate;
	AsciiString m_powerName;
	unsigned int m_tail[4];
};

// ?setFont@SuperweaponInfo@@QAEXABVAsciiString@@H_N@Z
// Both strings take the same font, and the point size passes through the
// language data's adjustment on the way in.
void SuperweaponInfo::setFont(const AsciiString &fontName, Int pointSize, Bool bold)
{
	m_nameDisplayString->setFont(TheFontLibrary->getFont(
		const_cast<AsciiString *>(&fontName),
		(Real)TheGlobalLanguageData->adjustFontSize(pointSize), bold));
	m_timeDisplayString->setFont(TheFontLibrary->getFont(
		const_cast<AsciiString *>(&fontName),
		(Real)TheGlobalLanguageData->adjustFontSize(pointSize), bold));
}

// ?drawName@SuperweaponInfo@@QAEXHHHH@Z
// x is the RIGHT edge: the name is drawn right-aligned by subtracting its own
// width, and a zero color means the one the info was built with.
void SuperweaponInfo::drawName(Int x, Int y, Color color, Color dropColor)
{
	if (color == 0)
		color = m_color;

	m_nameDisplayString->setColors(color, dropColor);
	m_nameDisplayString->drawAtOffsets(x - m_nameDisplayString->getWidth(-1), y, 1, 1);
}

// ?drawTime@SuperweaponInfo@@QAEXHHHH@Z
// The countdown hangs off the NAME's width, not its own, so it stays put as the
// digits change.
void SuperweaponInfo::drawTime(Int x, Int y, Color color, Color dropColor)
{
	if (color == 0)
		color = m_color;

	m_timeDisplayString->setColors(color, dropColor);
	m_timeDisplayString->drawAtOffsets(x - m_nameDisplayString->getWidth(-1), y, 1, 1);
}

// ??1SuperweaponInfo@@MAE@XZ
SuperweaponInfo::~SuperweaponInfo()
{
	if (m_nameDisplayString)
		TheDisplayStringManager->freeDisplayString(m_nameDisplayString);
	m_nameDisplayString = 0;

	if (m_timeDisplayString)
		TheDisplayStringManager->freeDisplayString(m_timeDisplayString);
	m_timeDisplayString = 0;
}
