// ?d_00520670@@YAXXZ
// partial score=0.99 date=2026-09-08
// cl: /Og
// experiment for ??0Gen00529110Member28@@QAE@XZ

typedef unsigned short UnsignedShort;

extern "C" void *memset(void *, int, unsigned int);
#pragma intrinsic(memset)

void * __cdecl operator new(unsigned int);
__forceinline void *operator new(unsigned int, void *place) { return place; }

template <typename T>
class StringBase
{
public:
	~StringBase();
	void set(const T *text, int length);
	void *m_data;
private:
};

class UnicodeString : private StringBase<UnsignedShort>
{
};

class BfmeWideString
{
public:
	~BfmeWideString();
	__forceinline void set(const UnsignedShort *, int) {}
	void *m_data;
};

class Gen00529110Base
{
public:
	Gen00529110Base() : m_data00(0), m_data04(0), m_data08(0), m_data0c(0), m_data10(0) {}

	int m_data00;
	int m_data04;
	int m_data08;
	int m_data0c;
	int m_data10;
};

class BfmeWideVGI
{
public:
	~BfmeWideVGI();
	__forceinline void touch() {}
	__forceinline void clear()
	{
		m_zero = 0;
		m_text.m_data = 0;
		m_data0 = 0;
		m_data1 = 0;
		m_data2 = 0;
		m_data3 = 0;
		m_data4 = 0;
		m_data5 = 0;
	}

	int m_zero;
	BfmeWideString m_text;
	int m_data0;
	int m_data1;
	int m_data2;
	int m_data3;
	int m_data4;
	int m_data5;
};

class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

class MapMetaData
{
public:
	MapMetaData();
	~MapMetaData();

	StringBase<UnsignedShort> m_displayName;
	StringBase<UnsignedShort> m_description;
	char m_padding08[0x18];
	int m_numPlayers;
	unsigned char m_isMultiplayer;
	unsigned char m_isScenarioMP;
	unsigned char m_isOfficial;
	char m_padding2b[0x29];
	RetailLayoutString m_fileName;
	char m_padding54[0xa8];
};

extern const UnsignedShort g_emptyWide[];
extern const char g_emptyAscii[];
extern __declspec(dllimport) unsigned __cdecl bfmeLenVGI(const UnsignedShort *text);

class Gen00529110Member28
{
public:
	Gen00529110Member28();

private:
	Gen00529110Base m_base;
	BfmeWideVGI m_text;
	int m_data34;
	bool m_flag38;
	bool m_flag39;
	char m_padding3a[2];
	MapMetaData *m_mapData;
};

__forceinline void clearGen00529110Base(Gen00529110Base *base)
{
	base->m_data00 = 0;
	base->m_data04 = 0;
	base->m_data08 = 0;
	base->m_data0c = 0;
	base->m_data10 = 0;
}

// ??0Gen00529110Member28@@QAE@XZ
Gen00529110Member28::Gen00529110Member28()
{
	clearGen00529110Base(&m_base);
	m_data34 = 0;
	m_flag38 = false;
	m_flag39 = false;
	m_mapData = 0;
	BfmeWideVGI *text;
	text = &m_text;
	memset(&m_text, 0, sizeof(*text));
	m_mapData = new MapMetaData;
	m_text.touch();
	StringBase<UnsignedShort> *description = &m_mapData->m_description;
	description->set(g_emptyWide, bfmeLenVGI(g_emptyWide));
	MapMetaData *map = m_mapData;
	map->m_displayName.set(g_emptyWide, bfmeLenVGI(g_emptyWide));
	*((unsigned char *)m_mapData + 0x26) = 0;
	m_mapData->m_fileName.set(g_emptyAscii, 0);
	m_mapData->m_numPlayers = 8;
	m_mapData->m_isMultiplayer = 1;
}
