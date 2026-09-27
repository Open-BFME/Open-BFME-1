// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B09A0. Retail offsets; no semantic class identity asserted.
struct RefBlock008B09A0 { unsigned short refs; };
struct Pool008B09A0 { void *unused; void (__cdecl *free)(void *); };
extern Pool008B09A0 *g_pool01337A30;
extern RefBlock008B09A0 g_default012D5298;
class Rva008AD2C0 {
public:
 Rva008AD2C0(const Rva008AD2C0 &);
 void assign(const Rva008AD2C0 &);
 RefBlock008B09A0 *m_block;
 float m_f4;
 int m_f8, m_fC, m_f10, m_f14, m_f18, m_f1C;
};
struct Value008B09A0 {
 int vptr;
 union { unsigned m_flags; struct { unsigned m_type:6; unsigned m_rest:26; }; };
 char pad08[0x18];
 Rva008AD2C0 m_f20;
};
struct State008B09A0 {
 char pad00[0x3c]; int m_f3C; char pad40[0x20]; float m_f60; int m_f64;
 Rva008AD2C0 *m_f68; unsigned m_f6C;
};
struct Owner008B09A0 { char pad00[0x50]; State008B09A0 *m_f50; };
extern Value008B09A0 **g_bfmeArr1233;
extern int g_stack01338748;
extern void *g_bfmeFallbackDB;
void *aptApplyRecord008B09A0(Owner008B09A0 *self, int argc) {
 if(argc<=3) {
  Value008B09A0 *v=g_bfmeArr1233[g_stack01338748-1];
  unsigned bits=v->m_flags;
  if (!(bits & 0x8000)) return g_bfmeFallbackDB;
  
  if (v->m_type==0x24 && !((unsigned char)~(bits>>15)&1)) {
   State008B09A0 *s=self->m_f50;
   int flags;
   if(!s->m_f68) {
    s->m_f68=new Rva008AD2C0(v->m_f20);
    flags=s->m_f68->m_f10 | v->m_f20.m_f10;
   } else {
    flags=s->m_f68->m_f10 | v->m_f20.m_f10;
    s->m_f68->assign(v->m_f20);
   }
   s->m_f68->m_f10=flags;
   if(v->m_f20.m_block!=&g_default012D5298) {
    Rva008AD2C0 *d=s->m_f68;
    ++v->m_f20.m_block->refs;
    RefBlock008B09A0 *old=d->m_block;
    if(--old->refs==0) g_pool01337A30->free(old);
    d->m_block=v->m_f20.m_block;
   }
   if(*(int *)&v->m_f20.m_f4 != (int)0xbf800000) {
    s->m_f60=v->m_f20.m_f4;
    if((int)s->m_f60<=0) s->m_f60=1.0f;
    s->m_f6C=(s->m_f6C & ~1)|0x10004;
   }
   if(v->m_f20.m_fC!=3) {
    s->m_f3C=v->m_f20.m_fC;
    s->m_f6C=(s->m_f6C & ~1)|0x20004;
   }
   if(v->m_f20.m_f8!=-1) s->m_f6C |= 0x400;
  }
 }
 return g_bfmeFallbackDB;
}
