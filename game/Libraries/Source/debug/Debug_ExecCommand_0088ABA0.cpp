// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::ExecCommand (0x0088ABA0).  Zero Hour twin: debug_debug.cpp
// Debug::ExecCommand.  BFME's Debug is polymorphic (operator<<(const char *)
// is virtual slot 14), so the command-group list head sits at +0x10 and the
// current command group at +0x9E08; the reply string types are one lower
// than Zero Hour's (CmdReply 4, StructuredCmdReply 5).

#include <string.h>

struct BfmeThingQO
{
    void bfmeFlushQO(int);
};

void bfmeLogQO(BfmeThingQO *, int, const char *, ...);

void *DebugAllocMemory(unsigned numBytes);
void DebugFreeMemory(void *ptr);

class Debug;

class DebugCmdInterface
{
public:
    enum CommandMode
    {
        Normal,
        Structured
    };

    virtual void Delete(void)=0;
    virtual bool Execute(class Debug &dbg, const char *cmd, CommandMode cmdmode,
                         unsigned argn, const char * const * argv)=0;
};

class Debug
{
public:
    virtual ~Debug(void);
    virtual void pad01(void);
    virtual void pad02(void);
    virtual void pad03(void);
    virtual void pad04(void);
    virtual void pad05(void);
    virtual void pad06(void);
    virtual void pad07(void);
    virtual void pad08(void);
    virtual void pad09(void);
    virtual void pad10(void);
    virtual void pad11(void);
    virtual void pad12(void);
    virtual void pad13(void);
    virtual Debug &operator<<(const char *);

private:
    struct CmdInterfaceListEntry
    {
        CmdInterfaceListEntry *next;
        const char *group;
        DebugCmdInterface *cmdif;
    };

    unsigned char m_pad04[0x0C];
    CmdInterfaceListEntry *firstCmdGroup;
    unsigned char m_pad14[0x9DF4];
    char curCommandGroup[100];

    void AddOutput(const char *str, unsigned len);
    void ExecCommand(const char *cmdstart, const char *cmdend);
};

// ?ExecCommand@Debug@@AAEXPBD0@Z
void Debug::ExecCommand(const char *cmdstart, const char *cmdend)
{
  // split off into command and arguments

  // alloc & copy string
  char *strbuf=(char *)DebugAllocMemory(cmdend-cmdstart+1);
  memcpy(strbuf,cmdstart,cmdend-cmdstart);
  strbuf[cmdend-cmdstart]=0;

  // for simplicity I'm using a fixed size argv array here...
  // if there are more arguments given than we have we're
  // just dropping the excess arguments
  char *parts[100];
  int numParts=0;
  char *lastNonWhitespace=NULL;
  char *cur=strbuf;

  // regular reply or structured reply?
  int reply;
  DebugCmdInterface::CommandMode mode;
  if (*cur=='!')
  {
    cur++;
    reply=5;
    mode=DebugCmdInterface::Structured;
  }
  else
  {
    reply=4;
    mode=DebugCmdInterface::Normal;
  }

  for (;;)
  {
    if (!lastNonWhitespace&&(*cur=='\''||*cur=='"'))
    {
      char quote=*cur++;

      if (numParts<sizeof(parts)/sizeof(*parts))
        parts[numParts++]=cur;

      while (*cur&&*cur!=quote)
        ++cur;
      if (*cur)
        *cur++=0;
    }
    else if (*cur==' '||*cur=='\t'||!*cur||*cur==';')
    {
      if (*cur==';')
        *cur=0;
      if (lastNonWhitespace)
      {
        if (numParts<sizeof(parts)/sizeof(*parts))
          parts[numParts++]=lastNonWhitespace;
        lastNonWhitespace=NULL;
        if (*cur)
          *cur++=0;
      }
      else if (*cur)
        ++cur;
      else
        break;
    }
    else
    {
      if (!lastNonWhitespace)
        lastNonWhitespace=cur;
      ++cur;
    }
  }

  if (numParts)
  {
    // part[0] is the command, part[1..numParts] are arguments

    // split off command group (if any)
    char *p=strchr(parts[0],'.');
    if (p&&p-parts[0]<sizeof(curCommandGroup))
    {
      memcpy(curCommandGroup,parts[0],p-parts[0]);
      curCommandGroup[p-parts[0]]=0;
      ++p;
    }
    else
      p=parts[0];

    bfmeLogQO((BfmeThingQO *)this,reply,"%s.%s",curCommandGroup,p);

    if (mode!=DebugCmdInterface::Structured)
      AddOutput("> ",2);

    // repeat current command first
    AddOutput(cmdstart,cmdend-cmdstart);
    AddOutput("\n",1);

    // command group known?
    CmdInterfaceListEntry *cur;
    for (cur=firstCmdGroup;cur;cur=cur->next)
      if (!strcmp(curCommandGroup,cur->group))
        break;
    if (!cur)
    {
      // nope, show error message
      (*this) << "Unknown command group " << curCommandGroup;
      *p=0;
    }

    if (*p)
    {
      // must have command...

      // search for a matching command handler
      for (cur=firstCmdGroup;cur;cur=cur->next)
      {
        if (strcmp(curCommandGroup,cur->group))
          continue;

        bool doneCommand=cur->cmdif->Execute(*this,p,mode,numParts-1,parts+1);
        if (doneCommand&&(strcmp(p,"help")||numParts>1))
          break;
      }

      // display error message if command not found, break away
      if (!cur&&mode==DebugCmdInterface::Normal)
      {
        if (strcmp(p,"help"))
          operator<<("Unknown command");
        else if (numParts>1)
          operator<<("Unknown command, help not available");
      }
    }

    // flush output only if there is already an active I/O class
    ((BfmeThingQO *)this)->bfmeFlushQO(0);
  }

  // cleanup
  DebugFreeMemory(strbuf);
}
