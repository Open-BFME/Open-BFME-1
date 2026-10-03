// cl: /O2 /MD
// Retail 0x00C6DB60 initializes the singleton at 0x0130C0D4 and registers its cleanup.
class BfmeThingTB
{
public:
    BfmeThingTB *bfmeGoTB();
};

// Retail VA 0x0130C0D4 is the singleton instance S3SingletonForwarders.cpp
// spells TheBfmeObject_00C70E50 (dir32_addresses.csv:
// ?TheBfmeObject_00C70E50@@3VGen_00C70E50Target@@A,0x0130C0D4); this TU used
// to invent g_bfmeRva0130C0D4Static for it, which nothing defines.  The
// instance is still an owner of no datum row, so the reference below is
// external-only until someone carries the singleton at 0x0130C0D4.
extern BfmeThingTB TheBfmeObject_00C70E50;

void bfmeForward_00C70E50();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DB60Initialize()
{
    TheBfmeObject_00C70E50.bfmeGoTB();
    atexit(bfmeForward_00C70E50);
}
