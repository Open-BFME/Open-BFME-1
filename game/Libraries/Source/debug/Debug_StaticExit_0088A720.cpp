// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::StaticExit (0x0088A720).  The Debug instance initializer at
// 0x0088AF30 stores the instance pointer in 0x01336E5C and registers this
// body with atexit, as Zero Hour's Debug::PostStaticInit registers
// StaticExit.  Zero Hour twin: debug_debug.cpp Debug::StaticExit.  BFME
// reference-counts the shutdown, releases the Debug critical section, and
// opens errors.txt when the extra error log is enabled.

extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *);
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteA(
    void *, const char *, const char *, const char *, const char *, int);

struct BfmeThingQO
{
    void bfmeFlushQO(int);
};

// Canonical pointer cell at retail VA 0x01336E5C.
extern void *g_Rva00F36E5C;

struct BfmeCsDWA;
extern BfmeCsDWA g_bfmeCsDWC;

class DebugIOInterface
{
public:
    virtual void pad00(void);
    virtual void pad01(void);
    virtual void pad02(void);
    virtual void pad03(void);
    virtual void pad04(void);
    virtual void pad05(void);
    virtual void Delete(void);
};

class DebugCmdInterface
{
public:
    virtual ~DebugCmdInterface(void);
    virtual void pad01(void);
    virtual void Delete(void);
};

class Debug
{
    struct IOFactoryListEntry
    {
        IOFactoryListEntry *next;
        const char *ioID;
        const char *descr;
        DebugIOInterface *(*factory)(void);
        DebugIOInterface *io;
    };

    struct CmdInterfaceListEntry
    {
        CmdInterfaceListEntry *next;
        const char *group;
        DebugCmdInterface *cmdif;
    };

    void *m_vtable;
    unsigned char m_pad04[0x08];
    IOFactoryListEntry *firstIOFactory;
    CmdInterfaceListEntry *firstCmdGroup;
    unsigned char m_pad14[0x9C68];
    int m_refCount;
    unsigned char m_pad9C80[0x74];
    int curType;
    unsigned char m_pad9CF8[0x253];
    bool errorLog;

    static void StaticExit(void);
};

#define Instance (*(Debug *)g_Rva00F36E5C)

// ?StaticExit@Debug@@CAXXZ
void Debug::StaticExit(void)
{
  if (--Instance.m_refCount)
  {
    DeleteCriticalSection(&g_bfmeCsDWC);
    return;
  }

  // yes, we do leave memory 'leaks' but Win32 will take care of these

  // however, I/O classes must be actively shut down
  if (Instance.curType!=7)
    ((BfmeThingQO *)&Instance)->bfmeFlushQO(1);
  for (IOFactoryListEntry *io=Instance.firstIOFactory;io;io=io->next)
    if (io->io)
    {
      io->io->Delete();
      io->io=0;
    }

  // and command group interfaces...
  for (CmdInterfaceListEntry *cmd=Instance.firstCmdGroup;cmd;cmd=cmd->next)
    if (cmd->cmdif)
    {
      cmd->cmdif->Delete();
      cmd->cmdif=0;
    }

  DeleteCriticalSection(&g_bfmeCsDWC);

  if (Instance.errorLog)
    ShellExecuteA(0,"open","errors.txt",0,0,1);
}
