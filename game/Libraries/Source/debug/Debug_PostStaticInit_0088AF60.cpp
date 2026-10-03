// cl: /DNDEBUG /MD /EHa /Oy-
// BFME Debug::PostStaticInit (0x0088AF60).  Zero Hour twin: debug_debug.cpp
// Debug::PostStaticInit -- same strings ("con"/"Console window", "flat",
// "net", "ods", "debug", "default.dbgcmd", ".dbgcmd", the DBGHELP.DLL hint).
// BFME differences: a run-once guard byte (0x01336E7A, read only here), the
// singleton reached through the shared pointer 0x01336E5C (see
// Debug_PreStaticInit_00889500.cpp), polymorphic Debug (vtable 0x01133058:
// slot 0x58 is InstallExceptionHandler 0x00889680), and the command file name
// taken from _EA_RTS_FILENAME before GetModuleFileName; the command file is
// opened FILE_SHARE_READ.  DebugGetDefaultCommands is reached through ILT
// 0x0000344A (only caller) and returns NULL in BFME (body 0x0005CC10).

#include <windows.h>
#include <string.h>
#include <new>

void *DebugAllocMemory(unsigned numBytes);
const char *DebugGetDefaultCommands(void);

// Zero Hour DebugStackwalk::IsOldDbghelp / GetDbghelpHandle at these call
// positions; the ledger keeps address-derived names.
unsigned char Rva0088CDF0GetFlag(void);
int Rva0088CDE0Get(void);

// Debug::StartOutput / Debug::FlushOutput under their ledger names.
struct BfmeThingQO
{
	void bfmeFlushQO(int);
};
void bfmeLogQO(BfmeThingQO *, int, const char *, ...);

class DebugIOInterface;
class DebugIOFlat
{
public:
	static DebugIOInterface *Create(void);
};
class DebugIONet
{
public:
	static DebugIOInterface *Create(void);
};
class DebugIOOds
{
public:
	static DebugIOInterface *Create(void);
};
class Rva00891540DebugIOCon;
class Rva00891540DebugIOConFactory
{
public:
	static Rva00891540DebugIOCon *Create(void);
};

class DebugCmdInterfaceDebug
{
public:
	DebugCmdInterfaceDebug();
	virtual void slot00();
};

// Canonical pointer cell at retail VA 0x01336E5C.
extern void *g_Rva00F36E5C;

class Debug
{
public:
	class RepeatChar
	{
		char m_c;
		int m_cnt;

	public:
		RepeatChar(char c, int cnt): m_c(c), m_cnt(cnt) {}
	};

	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	// MSVC places an overload set in reverse: const char * at 0x38, RepeatChar at 0x3C
	virtual Debug &operator<<(RepeatChar &c);
	virtual Debug &operator<<(const char *str);
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void InstallExceptionHandler();
	virtual void slot5C(); virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74(); virtual void slot78();
	virtual void slot7C();
	virtual bool AddIOFactory(const char *io_id, const char *descr, void *func);
	virtual bool AddCommands(const char *cmdgroup, DebugCmdInterfaceDebug *cmdif);

private:
	void ExecCommand(const char *cmdstart, const char *cmdend);
	static void PostStaticInit(void);
};

#define Instance (*(Debug **)&g_Rva00F36E5C)

// ?PostStaticInit@Debug@@CAXXZ
void Debug::PostStaticInit(void)
{
	// run-once guard: a function-local static (0x01336E7A, referenced only
	// here); a file-scope global schedules the store before the vptr load
	static bool s_rva01336E7A;
	if (s_rva01336E7A)
		return;
	s_rva01336E7A = true;

	Instance->InstallExceptionHandler();

	// register our default IO classes
	Instance->AddIOFactory("con","Console window",Rva00891540DebugIOConFactory::Create);
	Instance->AddIOFactory("flat","Flat local file(s)",DebugIOFlat::Create);
	Instance->AddIOFactory("net","Network via named pipe",DebugIONet::Create);
	Instance->AddIOFactory("ods","OutputDebugString function",DebugIOOds::Create);

	// add debug command handler
	Instance->AddCommands("debug",new (DebugAllocMemory(sizeof(DebugCmdInterfaceDebug))) DebugCmdInterfaceDebug);

	/// exec dbgcmd file
	char ioBuffer[2048];
	if (!GetEnvironmentVariable("_EA_RTS_FILENAME",ioBuffer,sizeof(ioBuffer)))
		GetModuleFileName(NULL,ioBuffer,sizeof(ioBuffer));
	char *q=strrchr(ioBuffer,'.');
	if (q)
		strcpy(q,".dbgcmd");
	HANDLE h=CreateFile(ioBuffer,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
	                    FILE_ATTRIBUTE_NORMAL,NULL);
	if (h==INVALID_HANDLE_VALUE)
		h=CreateFile("default.dbgcmd",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
		             FILE_ATTRIBUTE_NORMAL,NULL);
	if (h!=INVALID_HANDLE_VALUE)
	{
		char cmdBuffer[512];
		unsigned long ioCur=0,ioUsed=0,cmdCur=0;
		ReadFile(h,ioBuffer,sizeof(ioBuffer),&ioUsed,NULL);
		for (;;)
		{
			if (ioCur==ioUsed)
			{
				ReadFile(h,ioBuffer,sizeof(ioBuffer),&ioUsed,NULL);
				ioCur=0;
			}
			if (ioCur==ioUsed||ioBuffer[ioCur]=='\n'||ioBuffer[ioCur]=='\r')
			{
				if (cmdCur)
				{
					Instance->ExecCommand(cmdBuffer,cmdBuffer+cmdCur);
					cmdCur=0;
				}
				if (ioCur==ioUsed)
					break;
				ioCur++;
			}
			else
			{
				if (cmdCur<sizeof(cmdBuffer))
					cmdBuffer[cmdCur++]=ioBuffer[ioCur];
				ioCur++;
			}
		}
		CloseHandle(h);
	}
	else
	{
		// exec default commands
		const char *p=DebugGetDefaultCommands();
		while (p&&*p)
		{
			const char *q=strchr(p,'\n');
			if (!q)
				q=p+strlen(p);
			if (p!=q)
			{
				Instance->ExecCommand(p,q);
				p=*q?q+1:NULL;
			}
		}
	}

	// check: are we using an old dbghelp.dll?
	if (Rva0088CDF0GetFlag())
	{
		// give a serious hint
		bfmeLogQO((BfmeThingQO *)Instance,6,"");
		*Instance << RepeatChar('=',79) <<
			"\nYou are using an older version of the DBGHELP.DLL library.\n"
			"Please update to the newest available version in order to\n"
			"get reliable stack and symbol information.\n\n";

		char buf[256];
		GetModuleFileName((HMODULE)Rva0088CDE0Get(),buf,sizeof(buf));
		*Instance <<
			"Hint: The DLL got loaded as:\n" << buf << "\n" << RepeatChar('=',79) << "\n\n";

		// flush output only if there is already an active I/O class
		((BfmeThingQO *)Instance)->bfmeFlushQO(0);
	}
}
