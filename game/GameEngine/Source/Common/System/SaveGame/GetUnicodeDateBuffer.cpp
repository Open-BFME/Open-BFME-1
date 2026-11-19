// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#define NULL 0

#include "../../../../Include/Common/ScalarTypes/WideChar.h"

#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString() : m_text(0) {}

inline UnicodeString::UnicodeString(const UnicodeString &other)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
        *(const StringBase<unsigned short> *)&other);
}

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

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
extern "C" __declspec(dllimport) unsigned int wcslen(const WideChar *);

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
				AsciiString ansi(dateBuffer);
				displayDateBuffer.translate(ansi);
			}
			return displayDateBuffer;
		}
	}
	WideChar dateBuffer[DATE_BUFFER_SIZE_];
	GetDateFormatW(LOCALE_SYSTEM_DEFAULT_, DATE_SHORTDATE_, &timeVal, NULL,
					   dateBuffer, sizeof(dateBuffer));
	((StringBase<unsigned short> *)&displayDateBuffer)->set(dateBuffer, wcslen(dateBuffer));
	return displayDateBuffer;
}
