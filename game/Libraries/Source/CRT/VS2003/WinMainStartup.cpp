// cl: /O1 /G7 /Ob2 /MD /D_CRTBLD /Iinputs/toolchains/vs2003/native/Vc7/PlatformSDK/Include
// Complete native crtexew.obj: static PE/CLR-image test plus GUI CRT entry.
// Authored from retail instructions, original COFF symbols/relocations and
// public Platform SDK declarations. No CRT implementation source was read.
// Native SEH filter belongs to the 511-byte entry, not a separate function.
// Unsigned command bytes preserve >0x20 comparisons and DBCS lead handling.
#include <windows.h>
// Existing native 6-byte address-owned _XcptFilter import provider.
// Its actual current declaration is used; no new symbol alias or pin.
int __cdecl Rva009F7EEC_XcptFilter(unsigned long,void *);
extern "C" {
typedef void (__cdecl *InitProc)();
typedef int (__cdecl *ExitProc)();
extern ExitProc *__onexitbegin, *__onexitend;
extern int _fmode, _commode, _adjust_fdiv, __defaultmatherr, _newmode, _dowildcard;
extern InitProc __xi_a[], __xi_z[], __xc_a[], __xc_z[];
__declspec(dllimport) void __cdecl __set_app_type(int);
__declspec(dllimport) int *__cdecl __p__fmode();
__declspec(dllimport) int *__cdecl __p__commode();
extern int *_imp___adjust_fdiv;
struct _exception;
int __cdecl _matherr(_exception *);
__declspec(dllimport) void __cdecl __setusermatherr(int (__cdecl *)(_exception *));
__declspec(dllimport) int __cdecl __getmainargs(int *,char ***,char ***,int,int *);
__declspec(dllimport) char *_acmdln;
__declspec(dllimport) int __cdecl _ismbblead(unsigned int);
__declspec(dllimport) void __cdecl exit(int);
__declspec(dllimport) void __cdecl _exit(int);
__declspec(dllimport) void __cdecl _cexit();
__declspec(dllimport) void __cdecl _c_exit();
void __cdecl _RTC_Initialize();
void __cdecl _RTC_Terminate();
int __cdecl _setargv();
void __cdecl _setdefaultprecision();
void __cdecl _initterm(InitProc *,InitProc *);
int __cdecl atexit(InitProc);
void __cdecl _amsg_exit(int);
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
static int check_managed_app() {
 IMAGE_DOS_HEADER *dos=(IMAGE_DOS_HEADER *)GetModuleHandleA(0);
 if(dos->e_magic!=IMAGE_DOS_SIGNATURE)return 0;
 IMAGE_NT_HEADERS32 *nt=(IMAGE_NT_HEADERS32 *)((char *)dos+dos->e_lfanew);
 if(nt->Signature!=IMAGE_NT_SIGNATURE)return 0;
 switch(nt->OptionalHeader.Magic) {
 case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
  if(nt->OptionalHeader.NumberOfRvaAndSizes<=IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR)return 0;
  return nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress!=0;
 case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
  {IMAGE_NT_HEADERS64 *nt64=(IMAGE_NT_HEADERS64 *)nt;
  if(nt64->OptionalHeader.NumberOfRvaAndSizes<=IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR)return 0;
  return nt64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress!=0;}
 }
 return 0;
}
int __cdecl WinMainCRTStartup() {
 int in_quotes=0;
 int managed=check_managed_app();
 int result;
 __try {
  __set_app_type(2);
  __onexitbegin=__onexitend=(ExitProc *)-1;
  *__p__fmode()=_fmode;
  *__p__commode()=_commode;
  _adjust_fdiv=*_imp___adjust_fdiv;
  _RTC_Initialize();
  _setargv();
  if(!__defaultmatherr)__setusermatherr(_matherr);
  _setdefaultprecision();
  _initterm(__xi_a,__xi_z);
  atexit(_RTC_Terminate);
  int mode=_newmode;
  int argc; char **argv; char **env;
  int args=__getmainargs(&argc,&argv,&env,_dowildcard,&mode);
  if(args<0)_amsg_exit(8);
  _initterm(__xc_a,__xc_z);
  unsigned char *cmd=(unsigned char *)_acmdln;
  while(*cmd>' ' || (*cmd && in_quotes)) {
   if(*cmd=='"')in_quotes=!in_quotes;
   if(_ismbblead((unsigned char)*cmd))++cmd;
   ++cmd;
  }
  while(*cmd && *cmd<=' ')++cmd;
  STARTUPINFOA info;
  info.dwFlags=0;
  GetStartupInfoA(&info);
  result=WinMain(GetModuleHandleA(0),0,(LPSTR)cmd,info.dwFlags&STARTF_USESHOWWINDOW?info.wShowWindow:SW_SHOWDEFAULT);
  if(!managed)exit(result);
  _cexit();
 } __except(Rva009F7EEC_XcptFilter(GetExceptionCode(),GetExceptionInformation())) {
  result=GetExceptionCode();
  if(!managed)_exit(result);
  _c_exit();
 }
 return result;
}
}



#include <stddef.h>
typedef char NativePointerSize[(sizeof(void*)==4)?1:-1];
typedef char NativeStartupInfoSize[(sizeof(STARTUPINFOA)==68)?1:-1];
typedef char NativeStartupFlagsOffset[(offsetof(STARTUPINFOA,dwFlags)==44)?1:-1];
typedef char NativeStartupShowOffset[(offsetof(STARTUPINFOA,wShowWindow)==48)?1:-1];
typedef char NativeDosLfanewOffset[(offsetof(IMAGE_DOS_HEADER,e_lfanew)==60)?1:-1];
typedef char NativeNtOptionalOffset[(offsetof(IMAGE_NT_HEADERS32,OptionalHeader)==24)?1:-1];
typedef char NativePe32DirectoryCountOffset[(offsetof(IMAGE_OPTIONAL_HEADER32,NumberOfRvaAndSizes)==92)?1:-1];
typedef char NativePe64DirectoryCountOffset[(offsetof(IMAGE_OPTIONAL_HEADER64,NumberOfRvaAndSizes)==108)?1:-1];
