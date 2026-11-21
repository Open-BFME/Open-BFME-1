// cl: /O1 /G6 /Oi /Ob1 /MD /GX- /GS- /Iinputs/toolchains/vs2003/native/Vc7/PlatformSDK/Include
// Complete native pdblkup.obj member (GetImageInfo, GetPdbDll, _RTC_GetSrcLine),
// independently authored from retail bytes, native COFF identities, CodeView
// records and call relationships, against public SDK declarations only.
// B1 private whole-member port: original libc st_obj/pdblkup.obj, root lease
// 2f26276958f64402b55e8afdc95d6a90. Preserve three native procedure identities,
// all21 private data objects, real callback types and native constant scopes.
// Source donor147fd3e52b36ee0306aaeef5b316beb09f7c7671; public headers only.
// Native CodeView uses mutable char* parameters for the two PDB-open callbacks.
// No Microsoft implementation source read. Prior evidence:
// reverse/attempt_support/0x0075b177-pdb-source-lookup/ and pdb-*-2026102x/.
#include <windows.h>
#include <tlhelp32.h>
// The original private data use these two names. Hide only unused public
// SDK function declarations while importing their genuine SDK types; no
// renamed SDK function is emitted, imported, defined or called.
#define GetModuleInformation PdbSdkDeclaration_GetModuleInformation
#define EnumProcessModules PdbSdkDeclaration_EnumProcessModules
#include <psapi.h>
#undef EnumProcessModules
#undef GetModuleInformation
#include <malloc.h>
struct PDB;struct DBI;struct Mod;
struct ImageInfo {
 unsigned long sig,BaseAddress,BaseSize;HMODULE hndl;
 IMAGE_NT_HEADERS *img;IMAGE_SECTION_HEADER *sectHdr;char *imgName;ImageInfo *next;
};
extern "C" {
static HMODULE mspdb=0,psapi=0,imghlp=0,kernel=0;
static int (__cdecl *PDBOpenValidate3)(char *,char *,long *,char *,char *,unsigned long *,unsigned long *,PDB **)=0;
static int (__cdecl *PDBOpenDBI)(PDB *,char *,char *,DBI **)=0;
static int (__cdecl *DBIQueryModFromAddr)(DBI *,unsigned short,long,Mod **,unsigned short *,long *,long *)=0;
static int (__cdecl *ModQueryLines)(Mod *,unsigned char *,long *)=0;
static int (__cdecl *ModClose)(Mod *)=0;
static int (__cdecl *DBIClose)(DBI *)=0;
static int (__cdecl *PDBClose)(PDB *)=0;
static IMAGE_NT_HEADERS *(WINAPI *ImageNtHeader)(void *)=0;
static BOOL (WINAPI *GetModuleInformation)(HANDLE,HMODULE,MODULEINFO *,DWORD)=0;
static BOOL (WINAPI *EnumProcessModules)(HANDLE,HMODULE *,DWORD,DWORD *)=0;
static HANDLE (WINAPI *CreateToolhelp32SnapshotW9x)(DWORD,DWORD)=0;
static BOOL (WINAPI *Module32FirstW9x)(HANDLE,MODULEENTRY32 *)=0;
static BOOL (WINAPI *Module32NextW9x)(HANDLE,MODULEENTRY32 *)=0;
static ImageInfo *lImages=0;
static const char *mspdbName="MSPDB71.DLL";
}
static ImageInfo *GetImageInfo(unsigned long address) {
 ImageInfo *cur;
 for(cur=lImages;cur;cur=cur->next)
  if(cur->BaseAddress<=address && address-cur->BaseAddress<=cur->BaseSize)return cur;
 while(lImages) {ImageInfo *next=lImages->next;HeapFree(GetProcessHeap(),0,lImages);lImages=next;}
 if(!imghlp) {
  kernel=LoadLibraryA("KERNEL32.DLL");imghlp=LoadLibraryA("IMAGEHLP.DLL");
  if(!kernel||!imghlp)return 0;
  ImageNtHeader=(IMAGE_NT_HEADERS *(WINAPI *)(void *))GetProcAddress(imghlp,"ImageNtHeader");if(!ImageNtHeader)return 0;
  CreateToolhelp32SnapshotW9x=(HANDLE(WINAPI *)(DWORD,DWORD))GetProcAddress(kernel,"CreateToolhelp32Snapshot");
  if(!CreateToolhelp32SnapshotW9x) {
   psapi=LoadLibraryA("PSAPI.DLL");if(!psapi)return 0;
   EnumProcessModules=(BOOL(WINAPI *)(HANDLE,HMODULE *,DWORD,DWORD *))GetProcAddress(psapi,"EnumProcessModules");if(!EnumProcessModules)return 0;
   GetModuleInformation=(BOOL(WINAPI *)(HANDLE,HMODULE,MODULEINFO *,DWORD))GetProcAddress(psapi,"GetModuleInformation");if(!GetModuleInformation)return 0;
  } else {
   Module32FirstW9x=(BOOL(WINAPI *)(HANDLE,MODULEENTRY32 *))GetProcAddress(kernel,"Module32First");if(!Module32FirstW9x)return 0;
   Module32NextW9x=(BOOL(WINAPI *)(HANDLE,MODULEENTRY32 *))GetProcAddress(kernel,"Module32Next");if(!Module32NextW9x)return 0;
  }
 }
 if(!CreateToolhelp32SnapshotW9x) {
  HANDLE hProcess=GetCurrentProcess();HMODULE hModules[512];DWORD imageCount;MODULEINFO info;
  if(!EnumProcessModules(hProcess,hModules,sizeof(hModules),&imageCount))return 0;
  imageCount/=sizeof(HMODULE);
  for(unsigned i=0;i<imageCount;++i) {
   if(!GetModuleInformation(hProcess,hModules[i],&info,sizeof(info)))return 0;
   ImageInfo *node=(ImageInfo *)HeapAlloc(GetProcessHeap(),0,sizeof(ImageInfo));if(!node)goto error;
   node->hndl=hModules[i];node->BaseAddress=(DWORD)info.lpBaseOfDll;node->BaseSize=info.SizeOfImage;
   node->imgName=0;node->next=lImages;lImages=node;
  }
 } else {
  HANDLE snap=CreateToolhelp32SnapshotW9x(TH32CS_SNAPMODULE,0);if(snap==INVALID_HANDLE_VALUE)return 0;
  MODULEENTRY32 *entry=(MODULEENTRY32 *)_alloca(sizeof(MODULEENTRY32));entry->dwSize=sizeof(MODULEENTRY32);
  BOOL exists=Module32FirstW9x(snap,entry);
  while(exists) {
   ImageInfo *node=(ImageInfo *)HeapAlloc(GetProcessHeap(),0,sizeof(ImageInfo));
   if(!node){CloseHandle(snap);goto error;}
   node->hndl=entry->hModule;node->BaseAddress=(DWORD)entry->modBaseAddr;node->BaseSize=entry->modBaseSize;
   node->imgName=0;node->next=lImages;lImages=node;
   exists=Module32NextW9x(snap,entry);
  }
  CloseHandle(snap);
 }
 for(cur=lImages;cur;cur=cur->next) {
  cur->img=ImageNtHeader((void *)cur->BaseAddress);
  cur->sectHdr=(IMAGE_SECTION_HEADER *)((char *)cur->img+sizeof(DWORD)+sizeof(IMAGE_FILE_HEADER)+cur->img->FileHeader.SizeOfOptionalHeader);
  char *buf=(char *)_alloca(513);buf[512]=0;
  if(!GetModuleFileNameA(cur->hndl,buf,512))goto error;
  int len=0;while(buf[len])++len;
  cur->imgName=(char *)HeapAlloc(GetProcessHeap(),0,len+1);if(!cur->imgName)goto error;
  int i=0;do{cur->imgName[i]=buf[i];}while(buf[i++]);
 }
 for(cur=lImages;cur;cur=cur->next)
  if(cur->BaseAddress<=address && address-cur->BaseAddress<=cur->BaseSize)return cur;
error:
 while(lImages) {
  ImageInfo *next=lImages->next;
  if(lImages->imgName)HeapFree(GetProcessHeap(),0,lImages->imgName);
  HeapFree(GetProcessHeap(),0,lImages);lImages=next;
 }
 return 0;
}
static HMODULE GetPdbDll() {
 static int alreadyTried=0;
 if(alreadyTried)return 0;
 alreadyTried=1;
 HMODULE result=LoadLibraryA(mspdbName);if(result)return result;
 HMODULE advapi=LoadLibraryA("ADVAPI32.DLL");if(!advapi)return 0;
 LONG (WINAPI *RegOpenKeyExA)(HKEY,LPCSTR,DWORD,REGSAM,PHKEY)=(LONG(WINAPI *)(HKEY,LPCSTR,DWORD,REGSAM,PHKEY))GetProcAddress(advapi,"RegOpenKeyExA");if(!RegOpenKeyExA)return 0;
 LONG (WINAPI *RegQueryValueExA)(HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD)=(LONG(WINAPI *)(HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD))GetProcAddress(advapi,"RegQueryValueExA");if(!RegQueryValueExA)return 0;
 LONG (WINAPI *RegCloseKey)(HKEY)=(LONG(WINAPI *)(HKEY))GetProcAddress(advapi,"RegCloseKey");if(!RegCloseKey)return 0;
 HKEY key1;DWORD len,type;
 if(RegOpenKeyExA(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\VisualStudio\\7.1\\Setup\\VS",0,KEY_QUERY_VALUE,&key1)) {FreeLibrary(advapi);return 0;}
 if(RegQueryValueExA(key1,"EnvironmentDirectory",0,&type,0,&len))return 0;
 len+=13;
 char *buf=(char *)_alloca(len);
 LONG status=RegQueryValueExA(key1,"EnvironmentDirectory",0,&type,(BYTE *)buf,&len);
 RegCloseKey(key1);FreeLibrary(advapi);if(status)return 0;
 if(buf[len-2]!='\\')buf[len-1]='\\';else --len;
 for(int i=0;i<12;++i)buf[len+i]=mspdbName[i];
 return LoadLibraryA(buf);
}
int _RTC_GetSrcLine(unsigned long address,char *source,int sourcelen,int *pline,char **moduleName) {
 struct SSrcModuleHdr {unsigned short cFile,cSeg;};
 struct SStartEnd {unsigned long start,end;};
 char *errname=(char *)_alloca(1024);
 int res=0;ImageInfo *info;long imageAddr,secAddr;WORD sectionIndex;
 PDB *ppdb;DBI *pdbi;Mod *pmod;long err,offsetRes,size;DWORD fo,cb;char *pdbname;WORD sectionIndexRes;static int PDBOK=0;
 *pline=0;source[0]=0;*moduleName=0;
 info=GetImageInfo(address);if(!info)goto done;
 imageAddr=address-info->BaseAddress;*moduleName=info->imgName;res=1;
 if(!PDBOK) {
  if(mspdb)goto done;
  mspdb=GetPdbDll();if(!mspdb)goto done;
  PDBOpenValidate3=(int(__cdecl *)(char *,char *,long *,char *,char *,DWORD *,DWORD *,PDB **))GetProcAddress(mspdb,"PDBOpenValidate3");if(!PDBOpenValidate3)return 0;
  PDBOpenDBI=(int(__cdecl *)(PDB *,char *,char *,DBI **))GetProcAddress(mspdb,"PDBOpenDBI");if(!PDBOpenDBI)return 0;
  DBIQueryModFromAddr=(int(__cdecl *)(DBI *,WORD,long,Mod **,WORD *,long *,long *))GetProcAddress(mspdb,"DBIQueryModFromAddr");if(!DBIQueryModFromAddr)return 0;
  ModQueryLines=(int(__cdecl *)(Mod *,BYTE *,long *))GetProcAddress(mspdb,"ModQueryLines");if(!ModQueryLines)return 0;
  ModClose=(int(__cdecl *)(Mod *))GetProcAddress(mspdb,"ModClose");if(!ModClose)return 0;
  DBIClose=(int(__cdecl *)(DBI *))GetProcAddress(mspdb,"DBIClose");if(!DBIClose)return 0;
  PDBClose=(int(__cdecl *)(PDB *))GetProcAddress(mspdb,"PDBClose");if(!PDBClose)return 0;
  PDBOK=1;
 }
 for(sectionIndex=0;sectionIndex<info->img->FileHeader.NumberOfSections;++sectionIndex) {
  if(info->sectHdr[sectionIndex].VirtualAddress<(DWORD)imageAddr && (DWORD)(imageAddr-info->sectHdr[sectionIndex].VirtualAddress)<info->sectHdr[sectionIndex].SizeOfRawData)goto sectionFound;
 }
 goto done;
sectionFound:
 secAddr=imageAddr-info->sectHdr[sectionIndex].VirtualAddress;if(secAddr==-1)goto done;
 pdbname=(char *)_alloca(260);
 if(!PDBOpenValidate3(info->imgName,"",&err,errname,pdbname,&fo,&cb,&ppdb))goto done;
 if(!PDBOpenDBI(ppdb,"r",0,&pdbi))goto closePdb;
 if(!DBIQueryModFromAddr(pdbi,++sectionIndex,secAddr,&pmod,&sectionIndexRes,&offsetRes,&size))goto closeDbi;
 if(!ModQueryLines(pmod,0,&size)||!size)goto closeMod;
 {
 BYTE *lineBuffer=(BYTE *)HeapAlloc(GetProcessHeap(),0,size);
 if(!ModQueryLines(pmod,lineBuffer,&size))goto closeMod;
 int i;
 SSrcModuleHdr *module=(SSrcModuleHdr *)lineBuffer;
 long *fileOffsets=(long *)(module+1);
 for(i=0;i<module->cFile;++i) {
  WORD *file=(WORD *)(lineBuffer+fileOffsets[i]);
  int segments=file[0];
  long *lineOffsets=(long *)(file+2);
  SStartEnd *ranges=(SStartEnd *)(lineOffsets+segments);
  char *srcName=(char *)(ranges+segments);
  int seg;
  for(seg=0;seg<segments;++seg)
   if(ranges[seg].start<=(DWORD)secAddr && (DWORD)secAddr<=ranges[seg].end)goto segmentFound;
  continue;
segmentFound:
  WORD *lines=(WORD *)(lineBuffer+lineOffsets[seg]);
  int count=lines[1];long *offsets=(long *)(lines+2);WORD *lineNums=(WORD *)(offsets+count);
  int best=-1;DWORD delta=0xffffffff;
  for(int j=0;j<count;++j) {DWORD dist=secAddr-offsets[j];if(dist<delta){best=j;delta=dist;}}
  if(best>=0) {
   *pline=lineNums[best];
   int copied=0;while(srcName[copied] && copied<sourcelen){source[copied]=srcName[copied];++copied;}
   source[copied<sourcelen?copied:sourcelen-1]=0;
  }
  break;
 }
 HeapFree(GetProcessHeap(),0,lineBuffer);
 }
closeMod:ModClose(pmod);
closeDbi:DBIClose(pdbi);
closePdb:PDBClose(ppdb);
done:
 return res;
}

#include <stddef.h>
typedef char PdbNativePointerWidth[(sizeof(void*)==4)?1:-1];
typedef char PdbNativeIntWidth[(sizeof(int)==4)?1:-1];
typedef char PdbNativeImageInfoSize[(sizeof(ImageInfo)==32)?1:-1];
typedef char PdbNativeModuleInfoSize[(sizeof(MODULEINFO)==12)?1:-1];
typedef char PdbNativeModuleEntrySize[(sizeof(MODULEENTRY32)==548)?1:-1];
typedef char PdbNativeNtHeaderSize[(sizeof(IMAGE_NT_HEADERS)==248)?1:-1];
typedef char PdbNativeImageFileHeaderSize[(sizeof(IMAGE_FILE_HEADER)==20)?1:-1];
typedef char PdbNativeSectionHeaderSize[(sizeof(IMAGE_SECTION_HEADER)==40)?1:-1];
typedef char PdbNativeImageInfo_sig[(offsetof(ImageInfo,sig)==0)?1:-1];
typedef char PdbNativeImageInfo_BaseAddress[(offsetof(ImageInfo,BaseAddress)==4)?1:-1];
typedef char PdbNativeImageInfo_BaseSize[(offsetof(ImageInfo,BaseSize)==8)?1:-1];
typedef char PdbNativeImageInfo_hndl[(offsetof(ImageInfo,hndl)==12)?1:-1];
typedef char PdbNativeImageInfo_img[(offsetof(ImageInfo,img)==16)?1:-1];
typedef char PdbNativeImageInfo_sectHdr[(offsetof(ImageInfo,sectHdr)==20)?1:-1];
typedef char PdbNativeImageInfo_imgName[(offsetof(ImageInfo,imgName)==24)?1:-1];
typedef char PdbNativeImageInfo_next[(offsetof(ImageInfo,next)==28)?1:-1];
typedef char PdbNativeModuleEntry_szModule[(offsetof(MODULEENTRY32,szModule)==32)?1:-1];
typedef char PdbNativeModuleEntry_szExePath[(offsetof(MODULEENTRY32,szExePath)==288)?1:-1];
typedef char PdbNativeSize_mspdb[(sizeof(mspdb)==4)?1:-1];
typedef char PdbNativeSize_psapi[(sizeof(psapi)==4)?1:-1];
typedef char PdbNativeSize_imghlp[(sizeof(imghlp)==4)?1:-1];
typedef char PdbNativeSize_kernel[(sizeof(kernel)==4)?1:-1];
typedef char PdbNativeSize_PDBOpenValidate3[(sizeof(PDBOpenValidate3)==4)?1:-1];
typedef char PdbNativeSize_PDBOpenDBI[(sizeof(PDBOpenDBI)==4)?1:-1];
typedef char PdbNativeSize_DBIQueryModFromAddr[(sizeof(DBIQueryModFromAddr)==4)?1:-1];
typedef char PdbNativeSize_ModQueryLines[(sizeof(ModQueryLines)==4)?1:-1];
typedef char PdbNativeSize_ModClose[(sizeof(ModClose)==4)?1:-1];
typedef char PdbNativeSize_DBIClose[(sizeof(DBIClose)==4)?1:-1];
typedef char PdbNativeSize_PDBClose[(sizeof(PDBClose)==4)?1:-1];
typedef char PdbNativeSize_ImageNtHeader[(sizeof(ImageNtHeader)==4)?1:-1];
typedef char PdbNativeSize_GetModuleInformation[(sizeof(GetModuleInformation)==4)?1:-1];
typedef char PdbNativeSize_EnumProcessModules[(sizeof(EnumProcessModules)==4)?1:-1];
typedef char PdbNativeSize_CreateToolhelp32SnapshotW9x[(sizeof(CreateToolhelp32SnapshotW9x)==4)?1:-1];
typedef char PdbNativeSize_Module32FirstW9x[(sizeof(Module32FirstW9x)==4)?1:-1];
typedef char PdbNativeSize_Module32NextW9x[(sizeof(Module32NextW9x)==4)?1:-1];
typedef char PdbNativeSize_lImages[(sizeof(lImages)==4)?1:-1];
typedef char PdbNativeSize_mspdbName[(sizeof(mspdbName)==4)?1:-1];
