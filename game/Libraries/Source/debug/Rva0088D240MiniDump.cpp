// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// [BFME 2 donor] Crash minidump writer, retail 0x0088D240 (437 bytes): loads
// MiniDumpWriteDump from the dbghelp module handle at 0x01336E80, names the
// file "DUMP-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp" (VA 0x01133678), enables
// SeDebugPrivilege on the thread or process token and writes a full (flag
// set) or data-segment dump.  Callers: the exception filter
// (DebugExceptionhandler_ExceptionFilter.cpp) and Rva00889760.cpp.  The
// statement order is the BFME 2 donor's (open-bfme-2 45afcff3,
// Code/Libraries/Source/WWVegas/WWDebug/debug_stack.cpp, its 0x0003C550)
// minus the version strings BFME 1's file name lacks; that order (token
// cleared just before OpenThreadToken, info zero-initialised, the ok/adjusted
// pair) is what matched.  The old bank's declarations are kept.

extern "C" __declspec(dllimport) void *__stdcall GetProcAddress( void *module, const char *name );
extern "C" __declspec(dllimport) void __stdcall GetLocalTime( void *st );
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId( void );
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentProcessId( void );
extern "C" __declspec(dllimport) void *__stdcall GetCurrentProcess( void );
extern "C" __declspec(dllimport) void *__stdcall GetCurrentThread( void );
extern "C" __declspec(dllimport) void *__stdcall CreateFileA( const char *name, unsigned long access, unsigned long share, unsigned long sa, unsigned long disp, unsigned long attrs, unsigned long tmpl );
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError( void );
extern "C" __declspec(dllimport) int __stdcall OpenThreadToken( void *thread, unsigned long access, unsigned long openAsSelf, void **token );
extern "C" __declspec(dllimport) int __stdcall OpenProcessToken( void *process, unsigned long access, void **token );
extern "C" __declspec(dllimport) int __stdcall LookupPrivilegeValueA( unsigned long sys, const char *name, void *luid );
extern "C" __declspec(dllimport) int __stdcall AdjustTokenPrivileges( void *token, unsigned long disableAll, void *newState, unsigned long bufLen, void *prevState, unsigned long *retLen );
extern "C" __declspec(dllimport) int __cdecl _snprintf( char *b, int n, const char *f, ... );

__declspec(dllimport) void __stdcall bfmeClose1033( int h );

extern int g_Va01336E80;

struct Rva0088D240Time
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};

struct Rva0088D240Luid
{
	unsigned long LowPart;
	long HighPart;
};

struct Rva0088D240LuidAttr
{
	Rva0088D240Luid Luid;
	unsigned long Attributes;
};

struct Rva0088D240TokenPriv
{
	unsigned long PrivilegeCount;
	Rva0088D240LuidAttr Privileges[1];
};

struct Rva0088D240ExInfo
{
	unsigned long ThreadId;
	void *ExceptionPointers;
	int ClientData;
};

typedef int ( __stdcall *Rva0088D240MiniDump )( void *process, unsigned long pid, void *file, int dumpType, void *exinfo, void *user, void *cb );

extern "C" void d_0088d240( void *exptr, bool fullMemory )
{
	if ( !g_Va01336E80 )
		return;
	Rva0088D240MiniDump writeDump = (Rva0088D240MiniDump)GetProcAddress( (void*)g_Va01336E80, "MiniDumpWriteDump" );
	if ( !writeDump )
		return;

	Rva0088D240Time time;
	GetLocalTime( &time );
	char fileName[264];
	_snprintf( fileName, 0x106, "DUMP-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
		time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond,
		GetCurrentProcessId(), GetCurrentThreadId() );

	void *file = CreateFileA( fileName, 0xC0000000, 3, 0, 2, 0, 0 );
	if ( file == (void*)-1 )
		return;

	void *token = 0;
	if ( !OpenThreadToken( GetCurrentThread(), 0x28, 1, &token ) )
	{
		if ( GetLastError() != 0x3F0 )
			return;
		if ( !OpenProcessToken( GetCurrentProcess(), 0x28, &token ) )
			return;
	}

	Rva0088D240ExInfo info = { 0 };
	info.ThreadId = GetCurrentThreadId();
	info.ExceptionPointers = exptr;
	info.ClientData = 1;

	Rva0088D240TokenPriv privileges;
	privileges.PrivilegeCount = 1;
	privileges.Privileges[0].Attributes = 2;
	Rva0088D240TokenPriv previous;
	int ok = 0;
	ok = LookupPrivilegeValueA( 0, "SeDebugPrivilege", &privileges.Privileges[0].Luid );
	if ( ok )
	{
		unsigned long previousSize = sizeof(previous);
		ok = AdjustTokenPrivileges( token, 0, &privileges, previousSize, &previous, &previousSize );
	}
	int adjusted = ok && GetLastError() != 0x514;

	writeDump( GetCurrentProcess(), GetCurrentProcessId(), file, fullMemory ? 2 : 1, &info, 0, 0 );

	if ( adjusted )
		AdjustTokenPrivileges( token, 0, &previous, 0, 0, 0 );
	bfmeClose1033( (int)token );
	bfmeClose1033( (int)file );
}
