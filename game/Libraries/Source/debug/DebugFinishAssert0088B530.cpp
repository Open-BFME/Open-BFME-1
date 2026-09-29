// cl: /DNDEBUG /MD /EHsc /Oy-
// BFME member finalizer; the old static AssertBegin identity had the wrong ABI.
// See targets/game/reverse/identity_evidence/0x0088b530-debug-finalizer.md.
#include <windows.h>
#include <string.h>
#include <stdlib.h>
extern void *DebugAllocMemory(unsigned);
extern "C" int Rva0088E1A0ShowAssertCrashDialog(const char *, const char *);
int __stdcall EnumThreadWndProc(void *, long);
struct BfmeThingQO
{
    void bfmeFlushQO(int);
};
void bfmeLogQO(BfmeThingQO *, int, const char *, ...);
class Rva0088A1F0Owner
{
  public:
    void broadcast();
};
class DebugStackwalk
{
  public:
    class Signature
    {
      public:
        unsigned count, addresses[256];
        Signature() : count(0)
        {
        }
    };
    static int StackWalk(Signature &, _CONTEXT *, bool);
};
class Debug
{
  public:
    virtual ~Debug();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual Debug &streamInt(int);
    virtual Debug &streamText(const char *);
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7c();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual bool isWindowed();
    struct FrameHashEntry
    {
        FrameHashEntry *next;
        unsigned frameAddr, frameType;
        const char *fileOrGroup;
        int line, hits, status;
    };
    char pad04[0x9c80];
    struct Buffer
    {
        char *buffer;
        unsigned used, allocated;
        bool lastWasCR;
    } ioBuffer[7];
    int curType;
    char curSource[256];
    long disableAssertsEtc;
    FrameHashEntry *curFrameEntry;
    char pad9e00[0x6d];
    bool field9e6d;
    char pad9e6e[0xde];
    bool field9f4c;
    char pad9f4d[0xb];
    bool field9f58;

  private:
    void AddPatternEntry(unsigned, bool, const char *);

  public:
    bool finishAssert0088B530(int mode);
};
Debug &operator<<(Debug &, const DebugStackwalk::Signature &);
class BfmeAwakenDebug;
extern BfmeAwakenDebug *TheBfmeAwakenDebug;
#define TheDebug ((Debug *)TheBfmeAwakenDebug)
struct BfmeCsDWA;
extern BfmeCsDWA g_bfmeCsDWC;
extern bool g_01336E79;
#define DebugLock ((LPCRITICAL_SECTION)&g_bfmeCsDWC)
#define DebugFlag g_01336E79
bool Debug::finishAssert0088B530(int mode)
{
    if (curType == 0)
    {
        if (curFrameEntry->hits > 1)
            streamText(" (hit #").streamInt(curFrameEntry->hits).streamText(")");
        if (!ioBuffer[curType].lastWasCR)
            streamText("\n");
        const char *addInfo = "\nBecause of the severity of this error the game will now exit.";
        if (mode != 1)
            addInfo = "";
        char *help = (char *)DebugAllocMemory(ioBuffer[curType].used + strlen(addInfo) + 1);
        strcpy(help, ioBuffer[curType].buffer + 84);
        strcat(help, addInfo);
        if (!field9e6d || mode == 1)
        {
            DebugStackwalk::Signature sig;
            if (DebugStackwalk::StackWalk(sig, 0, mode == 1))
                (*this) << sig;
        }
        streamText("\n\n");
        ((BfmeThingQO *)this)->bfmeFlushQO(1);
        if (mode == 0)
        {
            bool windowed = false;
            if (TheDebug->isWindowed() && curFrameEntry->status != 3)
                windowed = true;
            if (!field9f4c && windowed)
            {
                FrameHashEntry *frame = curFrameEntry;
                field9f58 = true;
                int result = Rva0088E1A0ShowAssertCrashDialog("Assertion failed", help);
                field9f58 = false;
                curFrameEntry = frame;
                switch (result)
                {
                case 1:
                    DebugFlag = true;
                    break;
                // The intrinsic __debugbreak moves the flag store past the trap in VC7.1.
                // An explicit debugger trap preserves the observed store-before-break behavior.
                case 2:
                    DebugFlag = true;
                    __asm { int 3 }
                    ;
                    break;
                case 3:
                    curFrameEntry = 0;
                    LeaveCriticalSection(DebugLock);
                    exit(1);
                    break;
                case 5: {
                    char pattern[200];
                    wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup, curFrameEntry->line);
                    AddPatternEntry(1, false, pattern);
                    curFrameEntry->status = 1;
                    DebugFlag = true;
                }
                break;
                case 7: {
                    char pattern[200];
                    wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup, curFrameEntry->line);
                    AddPatternEntry(1, false, pattern);
                    curFrameEntry->status = 3;
                    DebugFlag = true;
                }
                break;
                }
            }
            else if (curFrameEntry->hits == 20)
            {
                bfmeLogQO((BfmeThingQO *)this, 6, "");
                streamText("Assert hit too often - turning check off.\n");
                ((BfmeThingQO *)this)->bfmeFlushQO(1);
                char pattern[200];
                wsprintfA(pattern, "%s(%i)", curFrameEntry->fileOrGroup, curFrameEntry->line);
                AddPatternEntry(1, false, pattern);
                curFrameEntry->status = 1;
            }
        }
        else
        {
            ((Rva0088A1F0Owner *)this)->broadcast();
            HWND window = 0;
            EnumThreadWindows(GetCurrentThreadId(), (void *)EnumThreadWndProc, (LPARAM)&window);
            if (window)
                ShowWindow(window, 6);
            MessageBoxA(0, help, "Game crash", 0x11010);
            curFrameEntry = 0;
            LeaveCriticalSection(DebugLock);
            ((Rva0088A1F0Owner *)this)->broadcast();
            _exit(1);
        }
    }
    curFrameEntry = 0;
    LeaveCriticalSection(DebugLock);
    InterlockedDecrement(&disableAssertsEtc);
    return false;
}
