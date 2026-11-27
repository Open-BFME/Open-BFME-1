// cl: /O1 /G7 /Ob1 /MD /GX-
// Whole native B1 libc st_obj/userapi.obj; authored BFME2 donor147fd3.
// Original identities/types/storage independently reconciled against B1 COFF,
// CodeView, retail operands and public rtcapi.h. No implementation source read.
// B1 whole-member addition: native _RTC_NumErrors, complete4B public int(void).
// Getter is the native typed callback getter; it replaces an existing6B
// address-derived int getter without adding another6B of C++ credit.
// Public rtcapi.h supplies declarations; no CRT implementation source was read.
// The getter and setter share the original private callback datum, rather than
// an address-named external that would link as a separate symbol.
#include <rtcapi.h>
extern "C" {static _RTC_error_fn _RTC_ErrorReportFunc=0;}
_RTC_error_fn __cdecl _RTC_GetErrorFunc(const void*) {
 return _RTC_ErrorReportFunc;
}

_RTC_error_fn __cdecl _RTC_SetErrorFunc(_RTC_error_fn callback) {
 _RTC_error_fn old=_RTC_ErrorReportFunc;_RTC_ErrorReportFunc=callback;return old;
}

extern "C" {
 static const char *_RTC_errlist[4]={
  "Stack pointer corruption",
  "Cast to smaller type causing loss of data",
  "Stack memory corruption",
  "Local variable used before initialization"
 };
}
const char *__cdecl _RTC_GetErrDesc(_RTC_ErrorNumber errnum) {
 if(errnum<0 || errnum>=4)return 0;
 return _RTC_errlist[errnum];
}

extern int _RTC_ErrorLevels[4];
int __cdecl _RTC_SetErrorType(_RTC_ErrorNumber errnum,int type) {
 if(errnum<0 || errnum>=4)return -1;
 int old=_RTC_ErrorLevels[errnum];_RTC_ErrorLevels[errnum]=type;return old;
}

int __cdecl _RTC_NumErrors(void) { return _RTC_ILLEGAL; }

typedef char RtcUserapiNativeErrorCount[(_RTC_ILLEGAL==4)?1:-1];
typedef char RtcUserapiNativeCallbackSize[(sizeof(_RTC_error_fn)==4)?1:-1];
typedef char RtcUserapiNativeCallbackStateSize[(sizeof(_RTC_ErrorReportFunc)==4)?1:-1];
typedef char RtcUserapiNativeErrlistSize[(sizeof(_RTC_errlist)==16)?1:-1];
