// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define NULL 0

typedef unsigned short WideChar;

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

// Keep these wrappers local to the body so the retail out-of-line string
// helpers, rather than the full project headers, receive the same ABI.
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	~UnicodeString() { releaseBuffer(); }

	void translate(const AsciiString &name);
	void set(const WideChar *text, int length) { StringBase<WideChar>::set(text, length); }
};

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
extern "C" __declspec(dllimport) int __stdcall GetDateFormatA(unsigned long, unsigned long, const _SYSTEMTIME *, const char *, char *, int);
extern "C" __declspec(dllimport) int __stdcall GetDateFormatW(unsigned long, unsigned long, const _SYSTEMTIME *, const WideChar *, WideChar *, int);
__declspec(dllimport) unsigned int bfmeLenVGI(const WideChar *);

enum { LOCALE_SYSTEM_DEFAULT_ = 0x0800 };
enum { DATE_SHORTDATE_ = 1 };
enum { VER_PLATFORM_WIN32_WINDOWS_ = 1 };

#define DATE_BUFFER_SIZE_ 256

// ?getUnicodeDateBuffer@@YA?AVUnicodeString@@U_SYSTEMTIME@@@Z
UnicodeString getUnicodeDateBuffer(_SYSTEMTIME timeVal)
{
	UnicodeString displayDateBuffer;
	OSVERSIONINFO_ osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO_);
	if (GetVersionExA(&osvi))
	{
		if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS_)
		{
			char dateBuffer[DATE_BUFFER_SIZE_];
			GetDateFormatA(LOCALE_SYSTEM_DEFAULT_, DATE_SHORTDATE_, &timeVal, NULL,
							   dateBuffer, sizeof(dateBuffer));
			{
				BFMERetailAsciiString ansi(dateBuffer);
				displayDateBuffer.translate(*(const AsciiString *)&ansi);
			}
			return displayDateBuffer;
		}
	}
	WideChar dateBuffer[DATE_BUFFER_SIZE_];
	GetDateFormatW(LOCALE_SYSTEM_DEFAULT_, DATE_SHORTDATE_, &timeVal, NULL,
					   dateBuffer, sizeof(dateBuffer));
	displayDateBuffer.set(dateBuffer, bfmeLenVGI(dateBuffer));
	return displayDateBuffer;
}
