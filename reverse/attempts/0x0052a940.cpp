// ?bfmeFlush11@SkirmishScreenState@@QAEXXZ
// partial score=0.9 date=2026-09-08
// cl: /O2 /DNDEBUG /MD /EHsc

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class UserPreferences
{
public:
	bool getBool(AsciiString key, bool defaultValue) const;
};

class GameInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;

	AsciiString getMap(void) const;
};

class SkirmishScreenOwner
{
public:
	virtual void slot00(void) = 0;
	virtual UserPreferences *getPreferences(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual bool bfmeAccept(GameInfo *value) = 0;
};

typedef void (*GameWinTooltipFunc)(void *, void *, unsigned int);

class GameWindow
{
public:
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);
};

class SkirmishScreenState
{
public:
	void bfmeFlush11(void);
	void bfmeApplyMapList(int flags);
	void bfmeSelectMap(const AsciiString &mapName);

private:
	unsigned char m_unmodelled00[4];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	bool m_flag17;
	bool m_visible;
	unsigned char m_unmodelled19[3];
	int m_value1C;
	int m_value20;
	int m_value24;
	unsigned char m_unmodelled28[0xe0];
	GameWindow *m_mapList;
};

#pragma comment(linker, "/alternatename:?bfmeApplyMapList@SkirmishScreenState@@QAEXH@Z=?j_00017b07@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeSelectMap@SkirmishScreenState@@QAEXABVAsciiString@@@Z=?j_000430a9@@YAXXZ")

// Refresh the selected map and install the optional map-list tooltip callback.
// ?bfmeFlush11@SkirmishScreenState@@QAEXXZ
void SkirmishScreenState::bfmeFlush11(void)
{
	if (m_first && !m_owner->bfmeAccept(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeAccept(m_second))
		m_second = 0;

	if (m_first)
	{
		bool useMapListTooltips = m_owner->getPreferences()->getBool(
			AsciiString("UseMapListTooltips"), false);
		bool useSystemMapDir = m_owner->getPreferences()->getBool(
			AsciiString("UseSystemMapDir"), true);

		int flags = 0;
		if (useSystemMapDir)
			flags = 9;
		else if (!(m_value24 & 1))
			flags = 8;
		flags |= 2;
		flags |= 0x10;
		bfmeApplyMapList(flags);
		AsciiString mapName = m_first->getMap();
		bfmeSelectMap(mapName);

		if (m_mapList)
		{
			m_flag12 = true;
			if (useMapListTooltips)
				m_mapList->winSetTooltipFunc(
					(GameWinTooltipFunc)(void *)0x00924730);
		}
	}
}
