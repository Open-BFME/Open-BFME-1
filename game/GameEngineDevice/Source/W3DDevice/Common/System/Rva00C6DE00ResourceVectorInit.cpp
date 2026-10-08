// cl: /O2 /MD
// Retail 00C6DE00 is a 30-byte initializer ending RET+1D then two INT3.
// 00C6DE20 starts a separate VectorClass<Vector3> initializer.
// The receiver at VA013411F0 is the three-pointer device-reset resource
// vector witnessed by Rva0090F050. Its existing address-derived initializer
// Gen_0090ea50::m consumes one allocator-tag address and zeros all pointers.
struct Gen_0090ea50 { void *m(int allocatorTag); };
class Gen_00C71060Target
{
public:
    void *m_begin;
    void *m_end;
    void *m_capacity;
};
// Retail VA 0x013411F0 (zero-initialized): the 12-byte vector this initializer fills.
Gen_00C71060Target TheBfmeObject_00C71060;
void bfmeForward_00C71060();
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void Rva00C6DE00Initialize()
{
    char allocatorTag;
    reinterpret_cast<Gen_0090ea50 *>(&TheBfmeObject_00C71060)->m(reinterpret_cast<int>(&allocatorTag));
    atexit(bfmeForward_00C71060);
}
