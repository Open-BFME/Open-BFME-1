// cl: /O2 /MD
// Retail .CRT initializer 0x00C6E0B0 (26 bytes; ret +0x19 then CC).
// Initializes the 24-byte singleton VA 0x0134B188 with two zero arguments.
// 0x0094E2B0 is the existing matched BfmeThingAWA::bfmeInitAWA body:
// forwards both arguments to 0x00912FE0; installs its vector vptr;
// clears active count +0x10 and sets growth step +0x14 to ten; ret 8.
// Registered cleanup 0x00C71480 tail-calls 0x0094EA80 on the same object.
// Existing opaque names preserve the unresolved application-level identity.
class BfmeThingAWA
{
public:
    void bfmeBaseAWA(void *one, void *two);
    BfmeThingAWA *bfmeInitAWA(void *one, void *two);
    void *m_bfmeVft;
    unsigned char m_bfmeGap[0xc];
    int m_bfmeZero;
    int m_bfmeCount;
};
class Gen_00C71480Target
{
public:
    unsigned char m_bfmeStorage[0x18];
};
// Retail VA 0x0134B188 (zero-initialized): the 24-byte singleton; the next
// recorded datum starts at 0x0134B1A0.
Gen_00C71480Target TheBfmeObject_00C71480;
void bfmeForward_00C71480();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void rva00C6E0B0Initialize()
{
    ((BfmeThingAWA *)&TheBfmeObject_00C71480)->bfmeInitAWA(0, 0);
    atexit(bfmeForward_00C71480);
}
