// ?parseGameDataDefinition@GlobalData@@SAXPAVINI@@@Z
// partial score=0.86 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>

typedef unsigned char Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef short Short;
typedef unsigned short UnsignedShort;
typedef float Real;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

struct FieldParse;

extern "C" __declspec(dllimport) BOOL WINAPI CreateDirectoryW(LPCWSTR, void *);

class INI
{
public:
	INILoadType getLoadType(void) const
	{
		return (INILoadType)*(const int *)((const unsigned char *)this + 8);
	}

	void initFromINI(void *what, const FieldParse *parseTable);
};

extern const char g_bfmeEmptyAscii[];
extern const char g_bfmeEmptyUnicode[];

class AsciiString
{
public:
	AsciiString(void);
	AsciiString(const AsciiString &other);
	AsciiString(const char *text);
	~AsciiString(void) { releaseBuffer(); }

	void set(const AsciiString &other);
	void set(const char *text, int length);
	void set(const char *text) { set(text, strlen(text)); }
	void releaseBuffer(void);
	void clear(void) { releaseBuffer(); }

	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}

	int getLength(void) const
	{
		return m_data ? *(const unsigned short *)((const unsigned char *)m_data + 4) : 0;
	}

	const char *str(void) const
	{
		return m_data ? m_data + 8 : g_bfmeEmptyAscii;
	}

private:
	char *m_data;
};

template <class T> class StringBase
{
friend class UnicodeString;

public:
	void set(const T *text, int length);

protected:
	T *m_data;

private:
	void releaseBuffer(void);
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	~UnicodeString(void) { releaseBuffer(); }

	void clear(void) { releaseBuffer(); }
	void set(const unsigned short *text)
	{
		StringBase<unsigned short>::set(text, wcslen((const wchar_t *)text));
	}

	const unsigned short *str(void) const
	{
		return m_data ? m_data + 8 : (const unsigned short *)g_bfmeEmptyUnicode;
	}
};

class GlobalData
{
public:
	GlobalData(void);
	static void parseGameDataDefinition(INI *ini);

	static const FieldParse s_GlobalDataFieldParseTable[];

	unsigned char m_bfme_00[0x2c];
	Int m_xResolution;
	Int m_yResolution;
	unsigned char m_bfme_34[0x2c];
	Bool m_useAlternateMouse;
	unsigned char m_bfme_61[0xa75 - 0x61];
	Bool m_unitDecals;
	unsigned char m_bfme_a76[0xa8e - 0xa76];
	Bool m_allHealthBars;
	unsigned char m_bfme_a8f[0xb10 - 0xa8f];
	UnsignedInt m_defaultIP;
	Int m_firewallBehavior;
	Bool m_firewallSendDelay;
	unsigned char m_bfme_b19[0xb1c - 0xb19];
	UnsignedInt m_firewallPortOverride;
	Short m_firewallPortAllocationDelta;
	unsigned char m_bfme_b22[0xb64 - 0xb22];
	Real m_horizontalScrollSpeedFactor;
	Real m_verticalScrollSpeedFactor;
	unsigned char m_bfme_b6c[0xbbc - 0xb6c];
	Real m_keyboardScrollFactor;
	unsigned char m_bfme_bc0[0xc0c - 0xbc0];
	Bool m_bfme_c0c;
	Bool m_bfme_c0d;
	unsigned char m_bfme_c0e[0xc68 - 0xc0e];
	Real m_displayGamma;
	unsigned char m_bfme_c6c[0x127c - 0xc6c];
	AsciiString m_userDataDir;
	UnicodeString m_userDataDirUnicode;
	AsciiString m_userDataDirLegacy;
	AsciiString m_userDataLeafName;
	unsigned char m_bfme_128c[0x1290 - 0x128c];

private:
	GlobalData *newOverride(void);
};

extern GlobalData *TheWritableGlobalData;

class OptionPreferences
{
public:
	OptionPreferences(void);
	virtual ~OptionPreferences(void);

	Real getScrollFactor(void);
	UnsignedInt getLANIPAddress(void);
	bool getSendDelay(void);
	Int getFirewallBehavior(void);
	Short getFirewallPortAllocationDelta(void);
	UnsignedShort getFirewallPortOverride(void);
	Bool getAllHealthBars(void);
	Bool getUnitDecals(void);
	Bool getAlternateMouseSetup(void);
	Real getBrightness(void);
	void getResolution(Int *xres, Int *yres);

private:
	unsigned char m_bfme_body[0x10];
};

extern AsciiString GetRegistryUserDataLeafName(void);
extern UnicodeString GetRegistryUserDataLeafNameUnicode(void);

void GlobalData::parseGameDataDefinition(INI *ini)
{
	if (TheWritableGlobalData && ini->getLoadType() != INI_LOAD_MULTIFILE)
	{
		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
			TheWritableGlobalData->newOverride();
	}
	else if (!TheWritableGlobalData)
	{
		TheWritableGlobalData = new GlobalData;
	}

	ini->initFromINI(TheWritableGlobalData, s_GlobalDataFieldParseTable);

	TheWritableGlobalData->m_userDataDir.clear();
	TheWritableGlobalData->m_userDataDirUnicode.clear();
	TheWritableGlobalData->m_userDataDirLegacy.clear();

	AsciiString leafName = GetRegistryUserDataLeafName();
	if (leafName.getLength() > 0)
		TheWritableGlobalData->m_userDataLeafName = leafName;

	char temp[MAX_PATH];
	if (SHGetSpecialFolderPathA(NULL, temp, CSIDL_APPDATA, TRUE))
	{
		if (temp[strlen(temp) - 1] != '\\')
			strcat(temp, "\\");
		strcat(temp, TheWritableGlobalData->m_userDataLeafName.str());
		strcat(temp, "\\");
		CreateDirectoryA(temp, NULL);
		TheWritableGlobalData->m_userDataDir.set(temp);

		wchar_t wideTemp[MAX_PATH];
		if (SHGetSpecialFolderPathW(NULL, wideTemp, CSIDL_APPDATA, TRUE))
		{
			UnicodeString wideLeaf = GetRegistryUserDataLeafNameUnicode();
			if (wideTemp[wcslen(wideTemp) - 1] != L'\\')
				wcscat(wideTemp, L"\\");
			wcscat(wideTemp, wideLeaf.str());
			wcscat(wideTemp, L"\\");
			CreateDirectoryW(wideTemp, NULL);
			TheWritableGlobalData->m_userDataDirUnicode.set(
				(const unsigned short *)wideTemp);
		}
	}

	OptionPreferences optionPref;
	TheWritableGlobalData->m_keyboardScrollFactor = optionPref.getScrollFactor();
	TheWritableGlobalData->m_horizontalScrollSpeedFactor = optionPref.getScrollFactor();
	TheWritableGlobalData->m_verticalScrollSpeedFactor = optionPref.getScrollFactor();
	TheWritableGlobalData->m_defaultIP = optionPref.getLANIPAddress();
	TheWritableGlobalData->m_firewallSendDelay = optionPref.getSendDelay();
	TheWritableGlobalData->m_firewallBehavior = optionPref.getFirewallBehavior();
	TheWritableGlobalData->m_firewallPortAllocationDelta = optionPref.getFirewallPortAllocationDelta();
	TheWritableGlobalData->m_firewallPortOverride = optionPref.getFirewallPortOverride();
	TheWritableGlobalData->m_allHealthBars = optionPref.getAllHealthBars();
	TheWritableGlobalData->m_unitDecals = optionPref.getUnitDecals();
	TheWritableGlobalData->m_useAlternateMouse = optionPref.getAlternateMouseSetup();
	TheWritableGlobalData->m_bfme_c0c = 0;
	TheWritableGlobalData->m_bfme_c0d = 0;

	Int val = (Int)optionPref.getBrightness();
	if (val < 50)
	{
		if (val <= 0)
			TheWritableGlobalData->m_displayGamma = 0.6f;
		else
			TheWritableGlobalData->m_displayGamma =
				1.0f - (0.4f) * (Real)(50 - val) / 50.0f;
	}
	else if (val > 50)
	{
		TheWritableGlobalData->m_displayGamma =
			1.0f + (1.0f) * (Real)(val - 50) / 50.0f;
	}

	Int xres, yres;
	optionPref.getResolution(&xres, &yres);
	TheWritableGlobalData->m_xResolution = xres;
	TheWritableGlobalData->m_yResolution = yres;
}
