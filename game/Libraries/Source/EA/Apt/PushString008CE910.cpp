// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt handler. Retail 0x008CE910 reads an aligned string
// operand, assigns global 0x012D5140, creates a value and pushes it.
extern "C" void __cdecl __identifier("?d_008cc940@@YAXXZ")();
struct BfmeHdrVKI { unsigned short m_bfme00; };
// VA 0x01337A30 is Apt.cpp's ?g_rva01337A30AllocPair@@3PAUBfmeStringPool3AF0@@A (data_rows).
struct BfmeStringPool3AF0 { void *m_alloc; void (__cdecl *m_free)(void *storage); };
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class BfmeStrVKI {
public:
 void bfmeSetVKI(const char *s);
 BfmeStrVKI(const char *s) { bfmeSetVKI(s); }
 ~BfmeStrVKI() { BfmeHdrVKI *p=m_bfme00; --p->m_bfme00; if(p->m_bfme00==0) g_rva01337A30AllocPair->m_free(p); }
 BfmeStrVKI &operator=(const BfmeStrVKI &s) {
  ++s.m_bfme00->m_bfme00;
  BfmeHdrVKI *p=m_bfme00;
  --p->m_bfme00;
  if(p->m_bfme00==0) g_rva01337A30AllocPair->m_free(p);
  m_bfme00=s.m_bfme00;
  return *this;
 }
 BfmeHdrVKI *m_bfme00;
};
extern BfmeStrVKI g_String012D5140;
class Rva00899770;
class Rva008CE910Value { public: virtual void invoke(); unsigned m_flags; };
class Rva008AE770Stack {
public:
 Rva00899770 * createString(void *const& a0,int const& a1,BfmeStrVKI * a2,int a3,int a4,int a5) {
  // retail body is still the gen-dump row ?d_008cc940@@YAXXZ (no C++ row yet); call it by that defined name
  // const& parameters keep retail's register choice for the pushed arguments
  union { void (__cdecl *symbol)(); Rva00899770 * (Rva008AE770Stack::*member)(void *,int,BfmeStrVKI *,int,int,int); } c;
  c.symbol = &__identifier("?d_008cc940@@YAXXZ");
  return (this->*c.member)(a0,a1,a2,a3,a4,a5);
 }
 int m_count; int m_unknown04; Rva008CE910Value **m_entries;
};
struct Rva008CE910Context { unsigned m_00; void *m_04; int m_08; };
void pushString008CE910(Rva008AE770Stack *state, Rva008CE910Context *context) {
 const char **operand=(const char **)((context->m_00+3)&~3u);
 context->m_00=(unsigned)(operand+1);
 g_String012D5140=BfmeStrVKI(*operand);
 Rva008CE910Value *value=(Rva008CE910Value *)state->createString(context->m_04,context->m_08,&g_String012D5140,1,1,0);
 state->m_entries[state->m_count]=value;
 ++state->m_count;
 unsigned char flags=(unsigned char)(value->m_flags>>30);
 if (!(flags&1)) value->invoke();
}
