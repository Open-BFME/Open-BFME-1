// cl: /MD /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
#include <windows.h>

// Retail entries [0x0084D790,0x0084D7BF) and [0x0084D7C0,0x0084D7E7).
// The generated 87-byte row fused both bodies and one byte of INT3 padding.
// SDK imports: GetStringTypeW at IAT RVA00F58DF0; LCMapStringW at RVA00F58E70.
int __cdecl Rva0084D790(const void *unused, int character, int mask)
{
 WCHAR input[2] = {(WCHAR)character, 0};
 WORD result[2];
 GetStringTypeW(CT_CTYPE1, input, -1, result);
 return result[0] & mask;
}
struct Rva0084D7C0Locale { LCID m_00; };
WCHAR __cdecl Rva0084D7C0(Rva0084D7C0Locale *locale, int character)
{
 WCHAR result;
 LCMapStringW(locale->m_00, LCMAP_LOWERCASE, (const WCHAR *)&character, 1, &result, 1);
 return result;
}
