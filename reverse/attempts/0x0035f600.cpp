// ?_bfme_showEndGameScreen@VictoryConditions@@UAEXABVAsciiString@@_N00@Z
// partial score=0.96 date=2026-09-09
// ?_bfme_showEndGameScreen@VictoryConditions@@UAEXABVAsciiString@@_N00@Z
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

template <class Character>
struct StringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	Character text[1];
};

template <class Character>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

	private:
	StringBase() : m_data(0) {}
	StringBase(const Character *text);
	StringBase(const StringBase &other);
	~StringBase();

	StringData<Character> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	const char *str() const { return m_data ? m_data->text : ""; }
	bool hasData() const { return m_data != 0; }
	bool isNotEmpty() const { return m_data != 0 && m_data->length != 0; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}
	char m_pad[4];
};

class GameTextLabel : public AsciiString
{
public:
	GameTextLabel(const AsciiString &other) : AsciiString(other) {}
	~GameTextLabel() {}
};

class GameTextInterface
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
	virtual UnicodeString fetch(GameTextLabel label, Bool *exists = 0);
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
	void unidentified_00015235(Int movie, const char *eventName, Int argCount,
		const void *p1, const void *p2, const void *p3, const void *p4,
		const void *p5);
};

class Display
{
public:
	void setUnidentified13c(Bool value) { m_pad13c = value; }

private:
	char m_pad[0x13c];
	Bool m_pad13c;
};

extern GameTextInterface *TheGameText;
extern WindowManager *g_theWindowManager;
extern Display *TheDisplay;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class VictoryConditions
{
public:
	virtual void _bfme_showEndGameScreen(const AsciiString &titleKey, Bool evil,
		const AsciiString &cheerSound, const AsciiString &screenName);

private:
	AsciiString m_name;
	Int m_victoryConditions;
	Bool m_endGameShowing;
	char m_pad0d[3];
	UnsignedInt m_endGameShowTime;
};

void VictoryConditions::_bfme_showEndGameScreen(
	const AsciiString &titleKey, Bool evil,
	const AsciiString &cheerSound, const AsciiString &screenName)
{
	if (!g_theWindowManager || m_endGameShowing)
		return;
	{
		AsciiString fieldName((const char *)0x010e8e20);
		g_theWindowManager->bfme_setAptText(
			fieldName, TheGameText->fetch(*(const AsciiString *)&titleKey));
	}

	const char *screen = screenName.isNotEmpty()
		? screenName.str() : (const char *)0x0107301c;
	const void *table = evil
		? (const void *)0x01081238 : (const void *)0x01080fc0;
	const char *cheer = cheerSound.hasData()
		? cheerSound.str() : (const char *)0x0107388b;
	g_theWindowManager->unidentified_00015235(
		0xb, (const char *)0x010e8e10, 3, table, screen, cheer, 0, 0);
	m_endGameShowing = true;
	m_endGameShowTime = timeGetTime();
	TheDisplay->setUnidentified13c(false);
}
