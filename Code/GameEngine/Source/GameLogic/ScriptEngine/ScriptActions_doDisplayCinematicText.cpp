// cl: /DNDEBUG /MD /EHsc
// ScriptActions::doDisplayCinematicText, retail RVA 0x002F3BD0 (553 bytes).
//
// The retail body uses the BFME string and virtual layouts rather than the
// Zero Hour declarations: GameText::fetch takes an AsciiString by value,
// Display's cinematic methods are slots 79-81, and FontLibrary::getFont takes
// an AsciiString pointer and a Real point size.  Keep those ABI shims local to
// this recovered body. The font parser preserves the retail pointer traversal.

#include <stdlib.h>
#include <string.h>

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;
typedef float Real;

template <typename T>
class StringBase
{
protected:

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void concat(const T *text, Int length);
	Bool endsWith(const T *text, Int length) const;

	void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other)
	{
	}
	~UnicodeString();
};

class AsciiString : private StringBase<char>
{
public:
	static AsciiString TheEmptyString;

	AsciiString() {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}
	~AsciiString();

	void translate(const UnicodeString &source);
	void concat(const char *source)
	{
		((StringBase<char> *)this)->concat(source,
			source ? (Int)strlen(source) : 0);
	}
	void concat(const char source)
	{
		((StringBase<char> *)this)->concat(&source, 1);
	}
	Bool endsWith(const char *suffix) const
	{
		return ((const StringBase<char> *)this)->endsWith(
			suffix, (Int)strlen(suffix));
	}
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 :
			(const char *)0x0107388B;
	}
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

class GameFont;

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

class GlobalLanguageData
{
public:
	Int adjustFontSize(Int pointSize);
};

class BFMERetailDisplayVTable
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void setCinematicText(AsciiString string) = 0;
	virtual void setCinematicFont(GameFont *font) = 0;
	virtual void setCinematicTextFrames(Int frames) = 0;
};

extern GameTextInterface *TheGameText;
extern FontLibrary *TheFontLibrary;
extern GlobalLanguageData *TheGlobalLanguageData;
extern BFMERetailDisplayVTable *TheDisplay;

class ScriptActions
{
protected:
	void doDisplayCinematicText(const AsciiString &displayText,
		const AsciiString &fontType, Int timeInSeconds);
};

void ScriptActions::doDisplayCinematicText(const AsciiString &displayText,
	const AsciiString &fontType, Int timeInSeconds)
{
	UnicodeString uStr = TheGameText->fetch(displayText);
	AsciiString aStr;
	aStr.translate(uStr);
	TheDisplay->setCinematicText(aStr);

	AsciiString fontName = AsciiString::TheEmptyString;
	char buf[256];
	char *c;
	strcpy(buf, fontType.str());
	for (c = buf; c != '\0'; *c++)
	{
		if (*c != ' ' && *c++ != '-')
			fontName.concat(c);
		else
			break;
	}
	while (*c != ':')
		*c++;
	*c++;

	AsciiString fontSize = AsciiString::TheEmptyString;
	for (; *c != '\0'; *c++)
	{
		if (*c != '\0' && *c != ' ')
			fontSize.concat(*c);
		else
			break;
	}
	Int size = atoi(fontSize.str());

	Bool bold = false;
	if (fontType.endsWith("[Bold]"))
		bold = true;

	GameFont *font = TheFontLibrary->getFont(&fontName,
		(Real)TheGlobalLanguageData->adjustFontSize(size), bold);
	TheDisplay->setCinematicFont(font);

	Int frames = 5 * timeInSeconds;
	TheDisplay->setCinematicTextFrames(frames);
}
