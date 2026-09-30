// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa /Oy- /Iinputs/reference/shims/debugvtable /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME: DebugIOCon's constructor, Zero Hour's debug_io_con.cpp body plus BFME's
// console title and close-button removal. /EHa /Oy- give retail's EH state for the
// DebugIOInterface base; Write is defined here so the constructor inlines it.
#include "_pch.h"
#include <string.h>

// ?bfmeIsBasic@@YGHH@Z
extern int __stdcall bfmeIsBasic(int kind);
extern "C" __declspec(dllimport) DWORD WINAPI GetConsoleTitleA(LPSTR, DWORD);
extern "C" __declspec(dllimport) HWND WINAPI FindWindowA(LPCSTR, LPCSTR);
extern "C" __declspec(dllimport) HMENU WINAPI GetSystemMenu(HWND, BOOL);
extern "C" __declspec(dllimport) BOOL WINAPI DeleteMenu(HMENU, UINT, UINT);
extern "C" __declspec(dllimport) BOOL WINAPI DrawMenuBar(HWND);

DebugIOCon::DebugIOCon(void):
  m_inputUsed(0), m_inputRead(0)
{
  // check: is there already a console window open?
  m_allocatedConsole=AllocConsole()!=0;
  if (m_allocatedConsole)
  {
    HANDLE h=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h,0);

    // make screen buffer same size as currently displayed area
    // (prevents that our input line gets scrolled out of view)
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h,&info);

    COORD newSize;
    newSize.X=info.srWindow.Right+1;
    newSize.Y=info.srWindow.Bottom+1;
    SetConsoleScreenBufferSize(h,newSize);

    // hide cursor
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize=1;
    ci.bVisible=FALSE;
    SetConsoleCursorInfo(h,&ci);

    SetConsoleCtrlHandler(bfmeIsBasic,TRUE);

    // find our console window by a unique title and remove its close entry
    char oldTitle[100];
    GetConsoleTitleA(oldTitle,sizeof(oldTitle));
    char title[52];
    wsprintfA(title,"CON@%08x",this);
    SetConsoleTitleA(title);
    Sleep(40);
    HWND hwnd=FindWindowA(NULL,title);
    if (hwnd)
    {
      HMENU menu=GetSystemMenu(hwnd,FALSE);
      DeleteMenu(menu,0xF060,0);  // SC_CLOSE, MF_BYCOMMAND
      DrawMenuBar(hwnd);
    }
    SetConsoleTitleA(oldTitle);

    Write(StringType::Other,NULL,"\n\nEA/Debug console open\n\n");
  }

  // title the console after the executable
  char moduleName[512];
  GetModuleFileNameA(NULL,moduleName,sizeof(moduleName));
  char *base=strrchr(moduleName,'\\');
  base=base?base+1:moduleName;
  char consoleTitle[512];
  strcpy(consoleTitle,base);
  strcat(consoleTitle," [debug console]");
  SetConsoleTitleA(consoleTitle);
}

// ?Write@DebugIOCon@@UAEXW4StringType@DebugIOInterface@@PBD1@Z present-unmatched
void DebugIOCon::Write(StringType type, const char *src, const char *str)
{
  if (type==StringType::StructuredCmdReply||!str)
    return;

  DWORD dwDummy;
  WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),str,strlen(str),&dwDummy,NULL);
}
