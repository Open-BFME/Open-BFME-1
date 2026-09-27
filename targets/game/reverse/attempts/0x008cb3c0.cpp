// ?d_008cb3c0@@YAXXZ
// partial score=0.642308 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt two-value selection at retail 0x008CB3C0.
class BfmeTab1024 { public: int bfmeFind1024(int); };
class Rva008CB3C0Value {
public:
 virtual void addRef();
 virtual void release();
 virtual void slot2(); virtual void slot3(); virtual void slot4();
 virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual void slot8(); virtual void slot9(); virtual void slot10();
 virtual void slot11(); virtual void slot12(); virtual void slot13();
 virtual void slot14(); virtual void slot15(); virtual void slot16();
 virtual void slot17(); virtual bool slot18(int);
 union { unsigned m_04; struct { unsigned type:6; unsigned rest:26; } bits; };
 BfmeTab1024 m_08;
 unsigned char invalid() { return (unsigned char)~(unsigned char)(m_04>>15); }
 bool is10() { unsigned f=m_04; unsigned t=f&63; unsigned char inv=(unsigned char)~(unsigned char)(f>>15); return t==10 && !(inv&1); }
 bool saturated() { return ((unsigned char)(m_04>>30)&1)!=0; }
};
extern Rva008CB3C0Value *g_bfmeFallbackDB;
extern char g_Key01338660;
struct Rva008CB3C0State { int m_00; int m_04; Rva008CB3C0Value **m_08; };
void selectValue008CB3C0(Rva008CB3C0State *state) {
 Rva008CB3C0Value *result=g_bfmeFallbackDB;
 Rva008CB3C0Value *left=state->m_08[state->m_00-2];
 Rva008CB3C0Value *right=state->m_08[state->m_00-1];
 if((right->m_04&63)==27 && !(right->invalid()&1) && left->is10()) {
  int found=left->m_08.bfmeFind1024((int)&g_Key01338660);
  if(right->slot18(found)) {
   result=right;
   right->addRef();
  }
 } else if(!((right->m_04&63)==10 && !(right->invalid()&1)) && !((right->m_04&63)==27 && !(right->invalid()&1)) && (right->m_04&63)==(left->m_04&63)) {
  result=right;
  right->addRef();
 }
 for(int i=1;i<=2;++i) {
  Rva008CB3C0Value *v=state->m_08[state->m_00-i];
  if(!v->saturated()) v->release();
 }
 state->m_00-=2;
 state->m_08[state->m_00]=result;
 ++state->m_00;
 if(!result->saturated()) result->addRef();
 result->release();
}
