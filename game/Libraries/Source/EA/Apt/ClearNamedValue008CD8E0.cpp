// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt handler, retail 0x008CD8E0: clear named value and
// replace the stack operand with pooled integer 1. Factory layout and tables
// agree with the existing AptInteger::Create at 0x008A11E0.
struct Rva8CD130StringBlock { unsigned short m_refs; };
extern Rva8CD130StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class Rva8CD130String {
public:
 Rva8CD130String() { m_block=&g_bfmeDefaultString1284; ++g_bfmeDefaultString1284.m_refs; }
 ~Rva8CD130String() { Rva8CD130StringBlock *block=m_block; --block->m_refs; if(block->m_refs==0) Rva01337A30ReleaseTable[1](block); }
 Rva8CD130StringBlock *m_block;
};
class Rva8CD130Value {
public:
 virtual void addRef(); virtual void release();
 void getName(Rva8CD130String *);
 unsigned m_flags;
};
struct Rva008CD8E0Integer {
 void *m_vtable; unsigned m_flags;
 union { Rva008CD8E0Integer *m_next; int m_value; };
};
struct Rva00899560Pool {
 int m_capacity,m_count; Rva008CD8E0Integer **m_items;
 __forceinline void add(Rva008CD8E0Integer *v) {
  int &count=m_count;
  if(count>=m_capacity) v->m_flags&=0xbfffffff;
  else { m_items[count]=v; ++count; }
 }
};
extern Rva008CD8E0Integer *Rva013387D0Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
__forceinline Rva8CD130Value *integerOne008CD8E0() {
 Rva008CD8E0Integer *v=Rva013387D0Head;
 if(v) {
  Rva013387D0Head=v->m_next;
  g_rva8CD130IdleHook->add(v);
  v->m_value=1;
  return (Rva8CD130Value *)v;
 }
 v=(Rva008CD8E0Integer *)Rva008C5D70Alloc(12);
 if(v) {
  v->m_vtable=(void *)0x01135D68;
  v->m_flags=(v->m_flags&0xf0008007)|0x40008007;
  g_rva8CD130IdleHook->add(v);
  v->m_vtable=(void *)0x01136400;
  v->m_value=1;
  return (Rva8CD130Value *)v;
 }
 return 0;
}
class Rva008CF3C0String;
class Rva008A9B00;
class Rva008CF3C0State {
public:
 void append(void *,void *,Rva008CF3C0String *,Rva008A9B00 *,int,int,int);
 int m_00; int m_04; Rva8CD130Value **m_08;
};
struct Rva008CD8E0Context { unsigned m_00; void *m_04; void *m_08; };
void clearNamedValue008CD8E0(Rva008CF3C0State *state,Rva008CD8E0Context *context) {
 Rva8CD130Value *top=state->m_08[state->m_00-1];
 Rva8CD130String name;
 top->getName(&name);
 state->append(context->m_04,context->m_08,(Rva008CF3C0String *)&name,0,1,1,0);
 Rva8CD130Value *old=state->m_08[state->m_00-1];
 if(!((unsigned char)(old->m_flags>>30)&1)) old->release();
 --state->m_00;
 Rva8CD130Value *value=integerOne008CD8E0();
 state->m_08[state->m_00]=value;
 ++state->m_00;
 if(!((unsigned char)(value->m_flags>>30)&1)) value->addRef();
}
