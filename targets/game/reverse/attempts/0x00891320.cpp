// ?d_00891320@@YAXXZ
// partial score=0.60 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa /Oy- /FAsc /Fabuild/DebugIOConConstructor.cod /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "../../Code/Libraries/Source/WWVegas/WWDebug/_pch.h"
#include <string.h>

extern int __stdcall bfmeIsBasic(int kind);
extern "C" __declspec(dllimport) DWORD WINAPI GetConsoleTitleA(LPSTR, DWORD);
extern "C" __declspec(dllimport) HWND WINAPI FindWindowA(LPCSTR, LPCSTR);
extern "C" __declspec(dllimport) HMENU WINAPI GetSystemMenu(HWND, BOOL);
extern "C" __declspec(dllimport) BOOL WINAPI DeleteMenu(HMENU, UINT, UINT);
extern "C" __declspec(dllimport) BOOL WINAPI DrawMenuBar(HWND);

struct DebugIOConConstructorLocals
{
  char consoleTitle[512];
  char moduleName[512];
  char oldTitle[100];
  union
  {
    char title[100];
    struct
    {
      char unused[52];
      CONSOLE_SCREEN_BUFFER_INFO info;
      char gap[6];
      CONSOLE_CURSOR_INFO ci;
      union
      {
        COORD newSize;
        DWORD dummy;
      };
    } setup;
  };
};

// ??0DebugIOCon@@QAE@XZ
DebugIOCon::DebugIOCon(void):
  m_inputUsed(0), m_inputRead(0)
{
  m_allocatedConsole=AllocConsole()!=0;
  if (m_allocatedConsole)
  {
    DebugIOConConstructorLocals locals;
    HANDLE h;
    h=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h,0);

    {
      h=GetStdHandle(STD_OUTPUT_HANDLE);
      GetConsoleScreenBufferInfo(h,&locals.setup.info);

      locals.setup.newSize.X=locals.setup.info.srWindow.Right+1;
      locals.setup.newSize.Y=locals.setup.info.srWindow.Bottom+1;
      SetConsoleScreenBufferSize(h,locals.setup.newSize);

      locals.setup.ci.dwSize=1;
      locals.setup.ci.bVisible=FALSE;
      SetConsoleCursorInfo(h,&locals.setup.ci);
    }

    SetConsoleCtrlHandler(bfmeIsBasic,TRUE);

    {
      GetConsoleTitleA(locals.oldTitle,100);
      wsprintfA(locals.title,"CON@%08x",this);
      SetConsoleTitleA(locals.title);
      Sleep(40);
      HWND window=FindWindowA(NULL,locals.title);
      if (window)
      {
        HMENU menu=GetSystemMenu(window,FALSE);
        DeleteMenu(menu,0xF060,0);
        DrawMenuBar(window);
      }
      SetConsoleTitleA(locals.oldTitle);
    }

    {
      WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),"\n\nEA/Debug console open\n\n",25,&locals.setup.dummy,NULL);
    }

    {
      GetModuleFileNameA(NULL,locals.moduleName,512);
      char *base=strrchr(locals.moduleName,'\\');
      if (base)
        ++base;
      else
        base=locals.moduleName;
      strcpy(locals.consoleTitle,base);
      strcat(locals.consoleTitle," [debug console]");
      SetConsoleTitleA(locals.consoleTitle);
    }
  }
}
