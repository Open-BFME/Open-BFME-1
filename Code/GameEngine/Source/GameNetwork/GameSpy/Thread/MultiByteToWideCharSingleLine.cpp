// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail ThreadUtils UTF-8 message conversion at RVA 0x006617D0.
// Identity: the player-message callback calls ILT 0x00028C7C, which jumps here;
// BuddyThread callbacks and the ThreadUtils reference identify the same helper.
// BFME doubles the input byte count before allocating the wide buffer, clears
// the full allocation, converts UTF-8, and replaces CR/LF with spaces. Unlike
// the older reference, it releases the array with delete[]. The complete body
// is 307 bytes through its second return; the old 301-byte boundary cut its
// final exception-cleanup epilogue. Natural STLport headers supply the string
// constructors, allocator and destructor without private library impersonation.

#include <string>
#include <string.h>
#include <wchar.h>
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int,unsigned long,const char*,int,wchar_t*,int);
std::wstring MultiByteToWideCharSingleLine(const char *orig)
{
 int len=2*strlen(orig);
 wchar_t *dest=new wchar_t[len+1];
 memset(dest,0,(len+1)*sizeof(wchar_t));
 MultiByteToWideChar(65001,0,orig,-1,dest,len);
 wchar_t *c=0;
 do { c=wcschr(dest,L'\n'); if(c) *c=L' '; } while(c);
 do { c=wcschr(dest,L'\r'); if(c) *c=L' '; } while(c);
 std::wstring ret=dest;
 delete [] dest;
 return ret;
}
