// ?Rva008B9080@@YAPAVAptValue@@PAURva008B9080Owner@@@Z
// partial score=0.3645 date=2026-10-02
// cl: /DNDEBUG /MD /O2
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);
class AptValue;
extern AptValue *g_bfmeFallbackDB;
struct Rva008B9080Owner
{
    unsigned int m_unmodelled00;
    unsigned int m_bits04;
    unsigned char m_unmodelled08[0x18];
    unsigned int *m_slots20;
    unsigned int m_unmodelled24;
    int m_count28;
    bool isArray() const {
        unsigned int bits = m_bits04;
        unsigned int type = bits & 0x3f;
        return type == 0x16 &&
            !((unsigned char)~(bits >> 15) & 1);
    }
};
AptValue *__cdecl Rva008B9080(Rva008B9080Owner *owner)
{
    AptValue *fallback = g_bfmeFallbackDB;
    if (!owner->isArray()) return fallback;
    if (owner->m_count28 <= 0) return fallback;
    AptValue *result = (AptValue *)(owner->m_slots20[0] & ~1u);
    if (!result) result = fallback;
    int count = --owner->m_count28;
    if (count) memmove(owner->m_slots20,owner->m_slots20+1,count*4);
    owner->m_slots20[owner->m_count28]=0;
    return result;
}
