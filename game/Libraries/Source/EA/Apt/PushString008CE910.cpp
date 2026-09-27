// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt handler. Retail 0x008CE910 reads an aligned string
// operand, assigns global 0x012D5140, creates a value and pushes it.
struct BfmeHdrVKI { unsigned short m_bfme00; };
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class BfmeStrVKI {
public:
 void bfmeSetVKI(const char *s);
 BfmeStrVKI(const char *s) { bfmeSetVKI(s); }
 ~BfmeStrVKI() { BfmeHdrVKI *p=m_bfme00; --p->m_bfme00; if(p->m_bfme00==0) Rva01337A30ReleaseTable[1](p); }
 BfmeStrVKI &operator=(const BfmeStrVKI &s) {
  ++s.m_bfme00->m_bfme00;
  BfmeHdrVKI *p=m_bfme00;
  --p->m_bfme00;
  if(p->m_bfme00==0) Rva01337A30ReleaseTable[1](p);
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
 Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
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
