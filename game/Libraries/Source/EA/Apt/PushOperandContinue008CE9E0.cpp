// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt aligned string operand push followed by 0x008CDE50.
struct BfmeHdrVKI { unsigned short m_bfme00; };
// 0x012D5298: the shared empty EA string block, defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  This TU keeps its own
// BfmeHdrVKI view of it and casts at the use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class BfmeStrVKI {
public:
 void bfmeSetVKI(const char *);
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
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned); };
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
class Gen_uws16_00891a80 { public: static void operator delete(void *,unsigned); };
class Rva008A9B00 : public Gen_uws16_00891a80 {
public:
 Rva008A9B00();
 void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
 virtual void addRef(); virtual void release();
 unsigned m_flags; BfmeStrVKI m_name; Rva008A9B00 *m_next;
};
struct Rva00899560Pool {
 int m_capacity,m_count; Rva008A9B00 **m_items;
 void add(Rva008A9B00 *v) { int i=m_count; int *count=&m_count; if(i>=m_capacity) v->m_flags&=~0x40000000; else { m_items[i]=v; ++*count; } }
};
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern Rva008A9B00 *Rva008C3B60Head;
class Rva8CEE00State { public: int m_00; int m_04; Rva008A9B00 **m_08; };
struct Rva8CEE00Cursor { unsigned m_00; };
void rva8CDE50Continue(Rva8CEE00State *,Rva8CEE00Cursor *);
void pushOperandContinue008CE9E0(Rva8CEE00State *state,Rva8CEE00Cursor *cursor) {
 const char **operand=(const char **)((cursor->m_00+3)&~3u);
 cursor->m_00=(unsigned)(operand+1);
 Rva008A9B00 *value=Rva008C3B60Head;
 if(value) {
  Rva008C3B60Head=value->m_next;
  g_rva8CD130IdleHook->add(value);
  if(value->m_name.m_bfme00!=(BfmeHdrVKI *)&g_rva012D5298Empty)
   ((BfmeStrVKK *)&value->m_name)->bfmeTruncVKK(0);
 } else value=new Rva008A9B00;
 value->m_name=BfmeStrVKI(*operand);
 state->m_08[state->m_00]=value;
 ++state->m_00;
 if(!((unsigned char)(value->m_flags>>30)&1)) value->addRef();
 rva8CDE50Continue(state,cursor);
}
