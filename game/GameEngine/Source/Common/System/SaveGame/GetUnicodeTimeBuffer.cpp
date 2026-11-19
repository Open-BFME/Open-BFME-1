// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#define NULL 0

#include "../../../../Include/Common/ScalarTypes/WideChar.h"

// forward only: used solely as the declared parameter type of
// UnicodeString::translate so the call mangles to the real matched function
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
extern "C" __declspec(dllimport) int __stdcall GetTimeFormatA(unsigned long, unsigned long, const _SYSTEMTIME *, const char *, char *, int);
extern "C" __declspec(dllimport) int __stdcall GetTimeFormatW(unsigned long, unsigned long, const _SYSTEMTIME *, const WideChar *, WideChar *, int);
extern "C" __declspec(dllimport) unsigned int wcslen(const WideChar *);

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
				AsciiString ansi(timeBuffer);
				displayTimeBuffer.translate(ansi);
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
	((StringBase<unsigned short> *)&displayTimeBuffer)->set(timeBuffer, wcslen(timeBuffer));
	return displayTimeBuffer;
}
