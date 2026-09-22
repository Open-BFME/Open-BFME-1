// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail00494EC0,62B. Global map atVA012F3354 has an identity-hashed
// four-byte key and a pointer mapped value (the caller dereferences that value).
// Keep the key as the bank's opaque pointer ABI; no concrete owner is known.
// operator[]494E40 and erase494A20 independently match99B and146B.
// Native const-reference calls reproduce the ECX/count-store order absent
// from the bank's opaque pointer-to-key method declarations. Keep its local
// key copy/reassignment; passing the parameter directly emits a shorter body.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
class Rva00494EC0EntryView
{
public:
 unsigned char m_at00[8];
 int m_at08;
 unsigned char m_at0c[0x14];
 unsigned char m_at20;
};
struct Rva00494EC0Hash
{
 unsigned operator()(void *key) const { return (unsigned)key; }
};
typedef _STL::hash_map<void *, Rva00494EC0EntryView *, Rva00494EC0Hash> Rva00494EC0MapView;
extern Rva00494EC0MapView g_rva00494EC0Map;
// ?Rva00494EC0@@YAXPAX@Z
void __cdecl Rva00494EC0(void *p)
{
 void *key = p;
 Rva00494EC0EntryView *entry=g_rva00494EC0Map[key];
 if (entry != 0)
 {
  entry->m_at20 &= 0xfc;
  entry->m_at08 = 0;
  key = p;
  g_rva00494EC0Map.erase(key);
 }
}
