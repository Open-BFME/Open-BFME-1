// ?update@Rva008835C0Owner@@QAAXPAXPBDZZ
// partial score=0.6429 date=2026-10-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <stdarg.h>
#include <string.h>
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *,unsigned long,unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *,unsigned long,void *);
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *,unsigned,const char *,va_list);
struct Rva008835C0Record {Rva008835C0Record *m_next;unsigned m_field04;void *m_block;unsigned m_field0C,m_field10;char *m_description;char m_pad18[0x84];int m_field9C;};
struct Rva008835C0Owner {
 char m_pad00[12];Rva008835C0Record *m_buckets[0x2b7b];char m_pad282c0[0x282c0-12-0x2b7b*4];unsigned char m_disabled;char m_pad282c1[7];void *m_lock;
 void __cdecl update(void *,const char *,...);
};
void __cdecl Rva008835C0Owner::update(void *block,const char *format,...){
 char buffer[512];
 if(m_disabled)return;
 if(m_lock)EnterCriticalSection(m_lock);
 unsigned bucket=(unsigned)block%0x2b7b;
 Rva008835C0Record *node=m_buckets[bucket];
 Rva008835C0Record **link=&m_buckets[bucket];
 while(node && node->m_block!=block){link=&node->m_next;node=*link;}
 Rva008835C0Record *record=*link;
 if(record && record->m_field9C<0){
  if(record->m_description)HeapFree(GetProcessHeap(),4,record->m_description);
  if(format){
   va_list args;va_start(args,format);
   if(_vsnprintf(buffer,sizeof(buffer),format,args)<0)buffer[511]=0;
   va_end(args);
   unsigned length=(unsigned)strlen(buffer)+1;
   record->m_description=(char*)HeapAlloc(GetProcessHeap(),4,length);
   memcpy(record->m_description,buffer,length);
  }else record->m_description=0;
 }
 if(m_lock)LeaveCriticalSection(m_lock);
}
