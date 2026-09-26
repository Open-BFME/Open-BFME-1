// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// readable body of ?postProcessLoad@W3DDisplayStringManager@@UAEXXZ: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringManager.cpp
// Open-BFME5: convert the retail display-string post-load routine to clean C++.

typedef unsigned short wchar_t;
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

typedef int Int;
typedef unsigned char Bool;

class GameFont;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual ~DisplayStringManager();
	virtual void init() = 0;
	virtual void postProcessLoad();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();
	virtual Bool bfme_dsm_6(void *) { return 0; }
	virtual void bfme_dsm_7() {}
	virtual void bfme_dsm_8(void *) {}
	virtual DisplayString *newDisplayString() = 0;
	AsciiString m_name;
	DisplayString *m_stringList;
	DisplayString *m_currentCheckpoint;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayStringManager.h
class W3DDisplayStringManager : public DisplayStringManager
{
public:
	virtual void postProcessLoad();
	DisplayString *m_groupNumeralStrings[10];
	DisplayString *m_formationLetterDisplayString;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DrawGroupInfo.h
class DrawGroupInfo
{
public:
	AsciiString m_fontName;
	Int m_fontSize;
	Bool m_fontIsBold;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameFont.h
class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, float pointSize, Bool bold);
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

extern DrawGroupInfo *TheDrawGroupInfo;
extern FontLibrary *TheFontLibrary;
extern GameTextInterface *TheGameText;

void W3DDisplayStringManager::postProcessLoad()
{
	GameFont *font = TheFontLibrary->getFont(
		&TheDrawGroupInfo->m_fontName,
		(float)TheDrawGroupInfo->m_fontSize,
		TheDrawGroupInfo->m_fontIsBold);

	for (Int i = 0; i < 10; ++i)
	{
		m_groupNumeralStrings[i] = newDisplayString();
		m_groupNumeralStrings[i]->setFont(font);

		AsciiString displayNumber;
		displayNumber.format("NUMBER:%d", i);
		m_groupNumeralStrings[i]->setText(TheGameText->fetch(displayNumber));
	}

	m_formationLetterDisplayString = newDisplayString();
	m_formationLetterDisplayString->setFont(font);
	AsciiString displayLetter;
	displayLetter.format("LABEL:FORMATION");
	m_formationLetterDisplayString->setText(TheGameText->fetch(displayLetter));
}
