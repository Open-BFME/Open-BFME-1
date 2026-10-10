// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The body occupies a vtable slot, but the owning class and semantic name are
// unproven. Keep the address-derived class token. The 124-byte extent includes
// the aligned 16-byte switch table beginning at +0x6c.
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
class BfmeStrVKI;
struct BfmeW1228 { const char *m_bfme00; int m_bfme04; };
class AptValue;

extern const BfmeW1228 *bfmeFind1228(const char *text, unsigned int length);
extern AptValue *g_bfmeFallbackDB;
// The installer at 0x00789440 owns these callback cells (VA 0x013378C8/CC)
// under their data-ledger names. Its generic storage type is void(), but
// the installed targets 0x007833A0/B0 each return float in ST(0): fld; ret.
extern void (__cdecl *g_bfmeSlot31VB)(void);
extern void (__cdecl *g_bfmeSlot32VB)(void);
extern AptValue *__cdecl Rva008A4EA0MakeFloat(float value);

class Rva008A6390
{
public:
    AptValue *method(void *arg1, BfmeStrVKI *arg2);
};

AptValue *Rva008A6390::method(void *arg1, BfmeStrVKI *arg2)
{
    if (arg1 == 0)
        return 0;

    BfmeStringData3AF0 *data = *reinterpret_cast<BfmeStringData3AF0 **>(arg2);
    const BfmeW1228 *entry = bfmeFind1228(reinterpret_cast<const char *>(data + 1), data->m_length);
    if (entry == 0)
        return 0;

    switch (entry->m_bfme04 - 1)
    {
    case 0:
    case 3:
        return g_bfmeFallbackDB;
    case 1:
        return Rva008A4EA0MakeFloat(reinterpret_cast<float (__cdecl *)(void)>(g_bfmeSlot31VB)());
    case 2:
        return Rva008A4EA0MakeFloat(reinterpret_cast<float (__cdecl *)(void)>(g_bfmeSlot32VB)());
    default:
        return 0;
    }
}
