// cl: /O1 /G7 /Ob1 /MD
// Native libc init.obj: __RTC_InitBase; shutdown follows in its own admission.
// BFME1's native function-local bool is at VA 0x0134FB84, not the donor address.
// Original COFF names, retail calls and public rtcapi.h establish the identities.
// BFME2 donor: 147fd3e52b36ee0306aaeef5b316beb09f7c7671, CRT/RtcInit.cpp.
// No Microsoft CRT implementation source was read.
#include <rtcapi.h>

void __cdecl _RTC_InitBase()
{
    static bool init = false;
    if (!init) {
        init = true;
        _RTC_SetErrorFunc(_CRT_RTC_INIT(0, 0, 0, 1, 0));
    }
}
