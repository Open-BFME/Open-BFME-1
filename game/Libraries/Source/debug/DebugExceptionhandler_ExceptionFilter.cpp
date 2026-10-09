// cl: /DNDEBUG /MD /EHs-c- /Oy- /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME: DebugExceptionhandler::ExceptionFilter, converted from the
// Zero Hour debug_except.cpp twin.  BFME reaches the Debug singleton through
// the shared diagnostic-manager pointer at 0x01336E5C, walks the stack before
// logging, and exits the process after the crash dialog instead of returning.

#include <windows.h>
#include <commctrl.h>
#include <float.h>
#include <string.h>

// Debug singleton pointer (0x01336E5C); same spelling as Debug::PreStaticInit.
class BfmeAwakenDebug;
extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))

// Callees under their ledger spellings.  In the Zero Hour ExceptionFilter these
// positions are FlushOutput (0x0088A230), StartOutput (0x0088A8B0, varargs
// cdecl), LogExceptionLocation (0x0088D850) and StaticExit (0x0088A1F0).
struct BfmeThingQO
{
    void bfmeFlushQO(int);
};

void bfmeLogQO(BfmeThingQO *, int, const char *, ...);

class BfmeStreamSZA;
struct BfmeCtxSZA;
void bfmeGoSZA(BfmeStreamSZA *, BfmeCtxSZA *);

struct Rva0088A1F0Owner
{
    void broadcast();
};

// 0x0088D240 tests its second argument as a byte (test al,al / setne), so it
// takes a bool; the retail xor/mov zero-extension only reproduces bool->bool.
extern "C" int d_0088d240(void *, bool);

// EnumThreadWindows callback and dialog procedure, pushed by address.
void dup_0088dfe0();
void d_0088dc30();

class Debug;
#include "../WWVegas/WWDebug/debug_stack.h"

// Zero Hour debug_debug.h declares these overloads in this order; MSVC
// places the overload group in reverse, which reproduces the retail slots
// (+0x04 MemDump, +0x38 const char *, +0x3C RepeatChar).
class Debug
{
public:
    class HResult
    {
        long m_hresult;
    };

    class MemDump
    {
        friend class Debug;

        const unsigned char *m_startPtr;
        unsigned m_numItems;
        unsigned m_bytePerItem;
        bool m_absAddr;
        bool m_withChars;

        MemDump(const void *ptr, unsigned num, unsigned bpi, bool absAddr, bool withChars):
            m_startPtr((const unsigned char *)ptr), m_numItems(num),
            m_bytePerItem(bpi), m_absAddr(absAddr), m_withChars(withChars) {}

    public:
        static MemDump Char(const void *startPtr, unsigned numItems, unsigned bytePerItem=1)
        {
            return MemDump(startPtr,numItems,bytePerItem,true,true);
        }
    };

    class RepeatChar
    {
        friend class Debug;
        char m_char;
        int m_count;

    public:
        explicit RepeatChar(char ch, int count): m_char(ch), m_count(count) {}
    };

    virtual Debug &operator<<(RepeatChar &c);
    virtual Debug &operator<<(const char *str);
    virtual Debug &operator<<(int val);
    virtual Debug &operator<<(unsigned val);
    virtual Debug &operator<<(long val);
    virtual Debug &operator<<(unsigned long val);
    virtual Debug &operator<<(bool val);
    virtual Debug &operator<<(float val);
    virtual Debug &operator<<(double val);
    virtual Debug &operator<<(short val);
    virtual Debug &operator<<(unsigned short val);
    virtual Debug &operator<<(__int64 val);
    virtual Debug &operator<<(unsigned __int64 val);
    virtual Debug &operator<<(const void *ptr);
    virtual Debug &operator<<(const MemDump &dump);
    virtual Debug &operator<<(HResult hres);
    virtual bool AssertDone(void);
    virtual bool CheckDone(void);
    virtual bool LogDone(void);
    virtual bool CrashDone(bool die);
    virtual void SetPrefixAndRadix(const char *prefix, int radix);
    virtual void WriteBuildInfo(void);

    unsigned char m_unmodelled0004[0x9C84 - 0x4];

    // Zero Hour layout: seven 16-byte I/O buffers end exactly at curType
    // (+0x9CF4); BFME's exception stream is index 3 (StartOutput(3) below).
    struct
    {
        char *buffer;
        unsigned used;
        unsigned alloc;
        bool lastWasCR;
    } ioBuffer[7];                                  // +0x9C84
    int curType;                                    // +0x9CF4
    char curSource[256];                            // +0x9CF8
    long disableAssertsEtc;                         // +0x9DF8
    unsigned char m_unmodelled9DFC[0x9F4A - 0x9DFC];
    bool m_unmodelled9F4A;                          // +0x9F4A
    unsigned char m_unmodelled9F4B[0x9F58 - 0x9F4B];
    bool m_unmodelled9F58;                          // +0x9F58
};

Debug &operator<<(Debug &dbg, const DebugStackwalk::Signature &sig);

class DebugExceptionhandler
{
public:
    static const char *GetExceptionType(struct _EXCEPTION_POINTERS *, char *);
    static long __stdcall ExceptionFilter(struct _EXCEPTION_POINTERS *);

private:
    static void LogRegisters(Debug &, struct _EXCEPTION_POINTERS *);
    static void LogFPURegisters(Debug &, struct _EXCEPTION_POINTERS *);
};

static struct _EXCEPTION_POINTERS *exPtrs;
static char regInfo[1024],verInfo[256];
static DebugStackwalk::Signature sig;
extern unsigned char g_Rva012D4D98ExceptionDialog[];

// ?ExceptionFilter@DebugExceptionhandler@@SGJPAU_EXCEPTION_POINTERS@@@Z
LONG __stdcall DebugExceptionhandler::ExceptionFilter(struct _EXCEPTION_POINTERS* pExPtrs)
{
  // we should not be calling ourselves!
  static bool inExceptionFilter;
  if (inExceptionFilter)
  {
    MessageBox(NULL,"Exception in exception handler","Fatal error",MB_OK);
    return EXCEPTION_CONTINUE_SEARCH;
  }
  inExceptionFilter=true;

  if (pExPtrs->ExceptionRecord->ExceptionCode==EXCEPTION_STACK_OVERFLOW)
  {
    OutputDebugString("EA/DEBUG: EXCEPTION_STACK_OVERFLOW\n");
  }

  Debug &dbg=*(Debug *)TheBfmeAwakenDebug;

  DebugStackwalk::StackWalk(sig,pExPtrs->ContextRecord,true);
  d_0088d240(pExPtrs,dbg.m_unmodelled9F4A);

  InterlockedIncrement(&dbg.disableAssertsEtc);
  if (dbg.curType!=7)
    ((BfmeThingQO *)&dbg)->bfmeFlushQO(1);
  bfmeLogQO((BfmeThingQO *)&dbg,3,"");

  dbg << "\n" << Debug::RepeatChar('=',80) << "\n";
  dbg << GetExceptionType(pExPtrs,regInfo) << ":\n" << regInfo << "\n\n";
  bfmeGoSZA((BfmeStreamSZA *)&dbg,(BfmeCtxSZA *)pExPtrs); dbg << "\n\n";

  unsigned curOfs=dbg.ioBuffer[3].used;
  dbg.WriteBuildInfo();
  unsigned len=dbg.ioBuffer[3].used-curOfs;
  if (len>=sizeof(verInfo))
    len=sizeof(verInfo)-1;
  memcpy(verInfo,dbg.ioBuffer[3].buffer+curOfs,len);
  verInfo[len]=0;
  dbg << "\n\n";

  curOfs=dbg.ioBuffer[3].used;
  LogRegisters(dbg,pExPtrs); dbg << "\n";
  // fnclex has no C or intrinsic spelling in VC7.1; the Zero Hour exception
  // code reaches the x87 unit through _asm the same way (LogFPURegisters).
  _asm fnclex
  _control87(_MCW_EM,_MCW_EM);
  LogFPURegisters(dbg,pExPtrs); dbg << "\n";
  len=dbg.ioBuffer[3].used-curOfs;
  if (len>=sizeof(regInfo))
    len=sizeof(regInfo)-1;
  memcpy(regInfo,dbg.ioBuffer[3].buffer+curOfs,len);
  regInfo[len]=0;

  dbg << sig << "\n";

  dbg << "Bytes around EIP:" << Debug::MemDump::Char(((char *)(pExPtrs->ContextRecord->Eip))-32,80);

  ((BfmeThingQO *)&dbg)->bfmeFlushQO(1);
  ((Rva0088A1F0Owner *)&dbg)->broadcast();

  HWND appHWnd=NULL;
  EnumThreadWindows(GetCurrentThreadId(),(WNDENUMPROC)dup_0088dfe0,(LPARAM)&appHWnd);
  if (appHWnd)
    ShowWindow(appHWnd,SW_MINIMIZE);

  InitCommonControls();
  exPtrs=pExPtrs;
  dbg.m_unmodelled9F58=true;
  if (DialogBoxIndirect(NULL,(LPDLGTEMPLATE)g_Rva012D4D98ExceptionDialog,NULL,(DLGPROC)d_0088dc30)==IDRETRY)
  {
    dbg.m_unmodelled9F58=false;
    // Zero Hour's IDRETRY idiom (debug_debug.cpp AssertDone: `_asm int 0x03`).
    _asm int 0x03
  }
  dbg.m_unmodelled9F58=false;
  inExceptionFilter=false;
  ExitProcess(666);
}
typedef int(__stdcall *RvaIsDebuggerPresentFn)(void);

// Open BFME 2: Code/Libraries/Source/WWVegas/WWDebug/DebugExceptionFilter.cpp.
extern "C" INT_PTR __stdcall Rva0088DC30DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM)
{
	switch (msg)
	{
	case 0x110:
		break;
	case 0x111:
		if ((unsigned short)wParam == 1 || (unsigned short)wParam == 4)
			EndDialog(hDlg, (unsigned short)wParam);
	default:
		return 0;
	}

	HMODULE kernel = LoadLibraryA("kernel32");
	if (kernel)
	{
		RvaIsDebuggerPresentFn isDebuggerPresent =
			(RvaIsDebuggerPresentFn)GetProcAddress(kernel, "IsDebuggerPresent");
		if (isDebuggerPresent && !isDebuggerPresent())
			ShowWindow(GetDlgItem(hDlg, 4), 0);
	}

	SendDlgItemMessageA(hDlg, 103, 0xC, 0, (long)verInfo);

	char *p = regInfo;
	for (char *q = p;; q++)
	{
		if (!*q || *q == '\n')
		{
			bool quit = !*q;
			*q = 0;
			SendDlgItemMessageA(hDlg, 105, 0x180, 0, (long)p);
			if (quit)
				break;
			p = q + 1;
		}
		else if (*q == '\r')
			*q = 0;
	}

	SendDlgItemMessageA(hDlg, 105, 0x30, (unsigned int)CreateFontA(13, 0, 0, 0, 400,
		0, 0, 0, 0, 0, 0, 0, 0x31, 0), 1);

	SendDlgItemMessageA(hDlg, 100, 0xC, 0, (long)
		DebugExceptionhandler::GetExceptionType(exPtrs, regInfo));
	SendDlgItemMessageA(hDlg, 101, 0xC, 0, (long)regInfo);

	_CONTEXT &ctx = *exPtrs->ContextRecord;
	DebugStackwalk::Signature::GetSymbol(ctx.Eip, regInfo,
		sizeof(regInfo));
	SendDlgItemMessageA(hDlg, 102, 0xC, 0, (long)regInfo);

	HWND list;
	list = GetDlgItem(hDlg, 104);
	if (!sig.Size())
	{
		LVCOLUMNA c;
		c.mask = 6;
		c.pszText = "";
		c.cx = 690;
		ListView_InsertColumn(list, 0, &c);

		LVITEMA item;
		item.iItem = 0;
		item.iSubItem = 0;
		item.mask = 1;
		item.pszText = "No stack data available - check for dbghelp.dll";

		item.iItem = ListView_InsertItem(list, &item);
	}
	else
	{

		LVCOLUMNA c;
		c.mask = 6;
		c.pszText = "";
		c.cx = 0;
		ListView_InsertColumn(list, 0, &c);

		c.mask = 7;
		c.pszText = "Address";
		c.cx = 60;
		c.fmt = 1;
		ListView_InsertColumn(list, 1, &c);

		c.mask = 6;
		c.pszText = "Module";
		c.cx = 120;
		ListView_InsertColumn(list, 2, &c);

		c.pszText = "Symbol";
		c.cx = 300;
		ListView_InsertColumn(list, 3, &c);

		c.pszText = "File";
		c.cx = 130;
		ListView_InsertColumn(list, 4, &c);

		c.pszText = "Line";
		c.cx = 80;
		ListView_InsertColumn(list, 5, &c);

		for (unsigned k = 0; k < sig.Size(); k++)
		{
			DebugStackwalk::Signature::GetSymbol(sig.GetAddress(k),
				regInfo, sizeof(regInfo));

			LVITEMA item;
			item.iItem = k;
			item.iSubItem = 0;
			item.mask = 0;
			item.iItem = ListView_InsertItem(list, &item);
			item.mask = 1;

			item.iSubItem++;
			item.pszText = strtok(regInfo, " ");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, ",");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, ",");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, ":");
			ListView_SetItem(list, &item);

			item.iSubItem++;
			item.pszText = strtok(0, "");
			ListView_SetItem(list, &item);
		}
	}

	return 1;
}
