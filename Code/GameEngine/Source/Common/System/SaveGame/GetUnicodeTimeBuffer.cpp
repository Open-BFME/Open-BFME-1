// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define NULL 0

typedef unsigned short WideChar;

// forward only: used solely as the declared parameter type of
// UnicodeString::translate so the call mangles to the real matched function
class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/string_base.h
template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void set(const T *text, int length);

private:
	void releaseBuffer();

	void *m_data;
};

// UnicodeString: real out-of-line body only for translate() (0x008891F0);
// ctor/copy-ctor/dtor stay inline forwarders to StringBase<WideChar> so the
// compiler emits direct calls to the base's real bodies instead of an
// out-of-line UnicodeString ctor/dtor (those mangled names are already
// claimed elsewhere in the ledger at different addresses).
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	~UnicodeString() { releaseBuffer(); }

	void translate(const AsciiString &name);
	void set(const WideChar *text, int length) { StringBase<WideChar>::set(text, length); }
};

// BFMERetailAsciiString: alias name for the StringBase<char> ctor/dtor pair
// (0x00888BC0 / 0x00887940) used for this call site's transient ansi buffer.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

struct _SYSTEMTIME { unsigned short w[8]; };

struct OSVERSIONINFO_
{
	unsigned long dwOSVersionInfoSize;
	unsigned long dwMajorVersion;
	unsigned long dwMinorVersion;
	unsigned long dwBuildNumber;
	unsigned long dwPlatformId;
	char szCSDVersion[128];
};

extern "C" __declspec(dllimport) int __stdcall GetVersionExA(OSVERSIONINFO_ *);
extern "C" __declspec(dllimport) int __stdcall GetTimeFormatA(unsigned long, unsigned long, const _SYSTEMTIME *, const char *, char *, int);
extern "C" __declspec(dllimport) int __stdcall GetTimeFormatW(unsigned long, unsigned long, const _SYSTEMTIME *, const WideChar *, WideChar *, int);
__declspec(dllimport) unsigned int bfmeLenVGI(const WideChar *);

enum { LOCALE_SYSTEM_DEFAULT_ = 0x0800 };
enum { TIME_NOSECONDS_ = 2, TIME_NOTIMEMARKER_ = 4, TIME_FORCE24HOURFORMAT_ = 8 };
enum { VER_PLATFORM_WIN32_WINDOWS_ = 1 };

#define DATE_BUFFER_SIZE_ 256
#define TIME_BUFFER_SIZE_ 256

// ?getUnicodeTimeBuffer@@YA?AVUnicodeString@@U_SYSTEMTIME@@@Z
UnicodeString getUnicodeTimeBuffer(_SYSTEMTIME timeVal)
{
	UnicodeString displayTimeBuffer;
	OSVERSIONINFO_ osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO_);
	if (GetVersionExA(&osvi))
	{
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS_)
		{
			char timeBuffer[DATE_BUFFER_SIZE_];
			GetTimeFormatA(LOCALE_SYSTEM_DEFAULT_,
										 TIME_NOSECONDS_ | TIME_FORCE24HOURFORMAT_ | TIME_NOTIMEMARKER_,
										 &timeVal,
										 NULL,
										 timeBuffer, sizeof(timeBuffer));
			{
				BFMERetailAsciiString ansi(timeBuffer);
				displayTimeBuffer.translate(*(const AsciiString *)&ansi);
			}
			return displayTimeBuffer;
		}
	}
	WideChar timeBuffer[TIME_BUFFER_SIZE_];
	GetTimeFormatW(LOCALE_SYSTEM_DEFAULT_,
								 TIME_NOSECONDS_,
								 &timeVal,
								 NULL,
								 timeBuffer,
								 sizeof(timeBuffer));
	displayTimeBuffer.set(timeBuffer, bfmeLenVGI(timeBuffer));
	return displayTimeBuffer;
}
