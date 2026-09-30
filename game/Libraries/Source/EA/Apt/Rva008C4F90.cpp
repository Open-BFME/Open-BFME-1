// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x008C4F90 (6 bytes). The Apt initializer registers this
// address in the same native callback slots as RVA 0x008C6800.

class AptValue;
extern AptValue *g_bfmeFallbackDB;

AptValue *__cdecl rva008C4F90(void *, int)
{
    return g_bfmeFallbackDB;
}
