// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt operand resolver; retail 0x008CE430.
struct BfmeHdrVKI { unsigned short m_bfme00; };
// Retail RVA 0x008CE50F loads VA 0x01337A30, then calls slot +4
// with one pointer and caller cleanup. Apt.cpp owns this allocation pair.
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class BfmeStrVKI {
public:
 void bfmeSetVKI(const char *);
 BfmeStrVKI(const char *s) { bfmeSetVKI(s); }
 ~BfmeStrVKI() { BfmeHdrVKI *p=m_bfme00; --p->m_bfme00; if(p->m_bfme00==0) reinterpret_cast<void (__cdecl **)(void *)>(g_rva01337A30AllocPair)[1](p); }
 BfmeHdrVKI *m_bfme00;
};
class EAStringC { public: EAStringC &rva0089F530(const char *); };
class Rva8CCCE0Value {
public:
 virtual void addRef(); virtual void release();
 char m_04[0x48]; Rva8CCCE0Value *m_4C;
};
Rva8CCCE0Value *rva8CC570Resolve(void *,void *,void *);
struct Rva008CE430Context { unsigned m_00; Rva8CCCE0Value *m_04; Rva8CCCE0Value *m_08; unsigned m_0C; };
__forceinline Rva8CCCE0Value *walk008CE430(const char *p,Rva8CCCE0Value *value) {
 while(*p=='.' && p[1]=='.' && value->m_4C) {
  p+=2;
  value=value->m_4C;
 }
 return value;
}
void resolveOperand008CE430(void *state,Rva008CE430Context *context) {
 const char **operand=(const char **)((context->m_00+3)&~3u);
 context->m_00=(unsigned)(operand+1);
 if(**operand==0) {
  if(context->m_08) context->m_08->release();
  context->m_08=0;
  return;
 }
 BfmeStrVKI name(*operand);
 const char *p=*operand;
 Rva8CCCE0Value *value;
 if(*p!='/' && *p!='.') {
  ((EAStringC *)&name)->rva0089F530("/");
  value=rva8CC570Resolve(context->m_04,0,&name);
 } else {
  value=walk008CE430(*operand,context->m_04);
 }
 context->m_0C=0;
 context->m_08=value;
 value->addRef();
}
