// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?addNamedTimer@InGameUI@@QAEXABVAsciiString@@ABVUnicodeString@@_N@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp

#include <map>

typedef int Int;
typedef float Real;
typedef unsigned char Bool;
typedef unsigned int Color;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
	bool operator<(const AsciiString &other) const;

private:
	void *m_data;
};

class UnicodeString;

template <class T>
class StringBase
{
private:
	friend class UnicodeString;

	StringBase(const StringBase<T> &other);
	~StringBase();

protected:
	StringBase() : m_data(0) {}

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other);

	static UnicodeString TheEmptyString;
};

class GameFont;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void reset();
	virtual void setFont(GameFont *font);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual DisplayString *newDisplayString();
};

class GlobalLanguageData
{
public:
	Int adjustFontSize(Int pointSize);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameFont.h
class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern DisplayStringManager *TheDisplayStringManager;
extern GlobalLanguageData *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class NamedTimerInfo
{
public:
	virtual ~NamedTimerInfo();

	AsciiString m_timerName;
	UnicodeString timerText;
	DisplayString *displayString;
	unsigned int timestamp;
	Color color;
	Bool isCountdown;
};

typedef std::map<AsciiString, NamedTimerInfo *> NamedTimerMap;

struct BfmeInGameUINamedTimerLayout
{
	unsigned char m_unreconstructed_000[0x77C];
	NamedTimerMap m_namedTimers;
	unsigned char m_unreconstructed_788[0x1C];
	AsciiString m_namedTimerNormalFont;
	Int m_namedTimerNormalPointSize;
	Bool m_namedTimerNormalBold;
	unsigned char m_unreconstructed_7AD[3];
	Color m_namedTimerNormalColor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	void addNamedTimer(const AsciiString &timerName, const UnicodeString &text, bool isCountdown);
	void removeNamedTimer(const AsciiString &timerName);
};

// BFME kept this block at the older offsets while Zero Hour grew InGameUI substantially.
void InGameUI::addNamedTimer(const AsciiString &timerName, const UnicodeString &text, bool isCountdown)
{
	BfmeInGameUINamedTimerLayout *ui = reinterpret_cast<BfmeInGameUINamedTimerLayout *>(this);
	NamedTimerInfo *info = new NamedTimerInfo;
	info->m_timerName = timerName;
	info->color = ui->m_namedTimerNormalColor;
	info->timerText = text;
	info->displayString = TheDisplayStringManager->newDisplayString();
	info->displayString->reset();
	info->displayString->setFont(TheFontLibrary->getFont(&ui->m_namedTimerNormalFont,
		(Real)TheGlobalLanguageData->adjustFontSize(ui->m_namedTimerNormalPointSize),
		ui->m_namedTimerNormalBold));
	info->displayString->setText(UnicodeString::TheEmptyString);
	info->timestamp = -1;
	info->isCountdown = isCountdown;

	removeNamedTimer(timerName);
	ui->m_namedTimers[timerName] = info;
}
