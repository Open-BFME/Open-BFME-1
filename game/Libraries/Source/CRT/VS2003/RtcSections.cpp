// cl: /O1 /G7 /Oy- /Ob1 /MD
// Complete native RunTmChk.lib initsect.obj, reconstructed from original
// COFF identities, retail code and the verified BFME2 RtcSections.cpp context.
// COFF code: __RTC_Initialize, __RTC_Terminate.
// COFF data: ___rtc_iaa, ___rtc_izz, ___rtc_taa, ___rtc_tzz.
// Native opening operands have addend +4: the first callback follows the null
// start sentinel. Each callback is protected by its own real SEH region.
typedef void (__cdecl *RtcCallback)(void);
extern "C" {
#pragma section(".rtc$IAA",read)
#pragma section(".rtc$IZZ",read)
#pragma section(".rtc$TAA",read)
#pragma section(".rtc$TZZ",read)
__declspec(allocate(".rtc$IAA")) extern const RtcCallback __rtc_iaa[1]={0};
__declspec(allocate(".rtc$IZZ")) extern const RtcCallback __rtc_izz[1]={0};
__declspec(allocate(".rtc$TAA")) extern const RtcCallback __rtc_taa[1]={0};
__declspec(allocate(".rtc$TZZ")) extern const RtcCallback __rtc_tzz[1]={0};
#pragma comment(linker,"/MERGE:.rtc=.rdata")

void __cdecl _RTC_Initialize()
{
 for(const RtcCallback *p=__rtc_iaa+1;p<__rtc_izz;++p) {
  __try { if(*p) (*p)(); }
  __except(1) {}
 }
}

void __cdecl _RTC_Terminate()
{
 for(const RtcCallback *p=__rtc_taa+1;p<__rtc_tzz;++p) {
  __try { if(*p) (*p)(); }
  __except(1) {}
 }
}
}
typedef char RtcCallbackMustBeFourBytes[(sizeof(RtcCallback)==4)?1:-1];
typedef char RtcInitStartSize[(sizeof(__rtc_iaa)==4)?1:-1];
typedef char RtcInitEndSize[(sizeof(__rtc_izz)==4)?1:-1];
typedef char RtcTermStartSize[(sizeof(__rtc_taa)==4)?1:-1];
typedef char RtcTermEndSize[(sizeof(__rtc_tzz)==4)?1:-1];
