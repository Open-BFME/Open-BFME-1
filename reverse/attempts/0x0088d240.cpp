// ?d_0088d240@@YAXXZ
// partial score=0.8 date=2026-09-14
// cl: /DNDEBUG /MD /EHs-c- /Oy-

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

extern "C" void d_0088d240( void *a, bool b )
{
	int ok = 0;
	void *hToken;
	Rva0088D240ExInfo exinfo;
	Rva0088D240MiniDump miniDump;
	unsigned long retLen;
	Rva0088D240Time st;
	Rva0088D240TokenPriv tp;
	Rva0088D240TokenPriv prev;
	char buf[264];
	void *hFile;

	if ( g_Va01336E80 == 0 )
		return;
	miniDump = (Rva0088D240MiniDump)GetProcAddress( (void*)g_Va01336E80, "MiniDumpWriteDump" );
	if ( miniDump == 0 )
		return;
	GetLocalTime( &st );
	_snprintf( buf, 0x106, "DUMP-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
		GetCurrentProcessId(), GetCurrentThreadId() );
	hFile = CreateFileA( buf, 0xC0000000, 3, ok, 2, ok, ok );
	if ( hFile == (void*)-1 )
		return;
	hToken = (void*)ok;
	if ( !OpenThreadToken( GetCurrentThread(), 0x28, 1, &hToken ) )
	{
		if ( GetLastError() != 0x3F0 )
			return;
		if ( !OpenProcessToken( GetCurrentProcess(), 0x28, &hToken ) )
			return;
	}
	exinfo.ThreadId = 0;
	exinfo.ExceptionPointers = 0;
	exinfo.ClientData = 0;
	exinfo.ThreadId = GetCurrentThreadId();
	exinfo.ExceptionPointers = a;
	exinfo.ClientData = 1;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = 2;
	if ( LookupPrivilegeValueA( ok, "SeDebugPrivilege", &tp.Privileges[0].Luid ) )
	{
		retLen = 0x10;
		if ( AdjustTokenPrivileges( hToken, ok, &tp, 0x10, &prev, &retLen ) )
		{
			if ( GetLastError() != 0x514 )
				ok = 1;
		}
	}
	miniDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, b ? 2 : 1, &exinfo, 0, 0 );
	if ( ok )
		AdjustTokenPrivileges( hToken, 0, &prev, 0, 0, 0 );
	bfmeClose1033( (int)hToken );
	bfmeClose1033( (int)hFile );
}
