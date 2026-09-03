// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?setFont@SuperweaponInfo@@QAEXABVAsciiString@@H_N@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp

typedef int Int;
typedef float Real;
typedef bool Bool;

class AsciiString {};
class GameFont;

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

extern GlobalLanguageData *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class SuperweaponInfo
{
private:
	void *m_vtable;
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;

public:
	void setFont(const AsciiString &fontName, Int pointSize, Bool bold);
};

void SuperweaponInfo::setFont(const AsciiString &fontName, Int pointSize, Bool bold)
{
	m_nameDisplayString->setFont(TheFontLibrary->getFont(
		const_cast<AsciiString *>(&fontName),
		(Real)TheGlobalLanguageData->adjustFontSize(pointSize), bold));
	m_timeDisplayString->setFont(TheFontLibrary->getFont(
		const_cast<AsciiString *>(&fontName),
		(Real)TheGlobalLanguageData->adjustFontSize(pointSize), bold));
}
