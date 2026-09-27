// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt handler at 0x008CDAD0. Resolve a top-value name in
// the current owner stack or context, install fallback if invalid, then pop.
class BfmeStrVKI;
class Rva008CF3C0String;
class Rva008A9B00;
class Rva00899770;
class Rva008CDAD0Value {
public:
 virtual void addRef(); virtual void release();
 unsigned m_04; char m_08[0x18]; Rva008CDAD0Value *m_20;
 unsigned type() { return m_04&63; }
 BfmeStrVKI *name() { Rva008CDAD0Value *v; if(type()==1) v=this; else v=m_20; return (BfmeStrVKI *)((char *)v+8); }
 unsigned char invalid() { return (unsigned char)~(unsigned char)(m_04>>15); }
};
class Rva008AE770Stack { public: Rva00899770 *createString(void *,int,BfmeStrVKI *,int,int,int); };
class Rva008CF3C0State { public: void append(void *,void *,Rva008CF3C0String *,Rva008A9B00 *,int,int,int); };
struct Rva008CDAD0Stack { int m_count; int m_unused; void **m_items; int size() { return m_count; } void *top() { return m_items[m_count-1]; } };
struct Rva008CDAD0State {
 int sizeOwner() { return m_owner.size(); }
 void *topOwner() { return m_owner.top(); }
 int m_00; int m_04; Rva008CDAD0Value **m_08;
 Rva008CDAD0Stack m_owner;
 char m_18[0x24]; int m_3C; int m_40; Rva008CDAD0Value **m_44;
};
struct Rva008CDAD0Context { unsigned m_00; void *m_04; void *m_08; };
extern Rva008A9B00 *g_bfmeFallbackDB;
void ensureName008CDAD0(Rva008CDAD0State *state,Rva008CDAD0Context *context) {
 Rva008CDAD0Value *value=state->m_08[state->m_00-1];
 if(state->m_owner.size()>0) {
  Rva008CDAD0Value *found=(Rva008CDAD0Value *)((Rva008AE770Stack *)state)->createString(state->topOwner(),(int)context->m_08,value->name(),0,1,0);
  if(found->invalid()&1) {
   ((Rva008CF3C0State *)state)->append(state->m_owner.top(),context->m_08,(Rva008CF3C0String *)value->name(),g_bfmeFallbackDB,0,1,0);
  }
  state->m_44[state->m_3C]=value;
  ++state->m_3C;
  value->addRef();
 } else {
  Rva008CDAD0Value *found=(Rva008CDAD0Value *)((Rva008AE770Stack *)state)->createString(context->m_04,(int)context->m_08,value->name(),0,1,0);
  if(found->invalid()&1) {
   ((Rva008CF3C0State *)state)->append(context->m_04,context->m_08,(Rva008CF3C0String *)value->name(),g_bfmeFallbackDB,0,1,0);
  }
 }
 value=state->m_08[state->m_00-1];
 if(!((unsigned char)(value->m_04>>30)&1)) value->release();
 --state->m_00;
}
