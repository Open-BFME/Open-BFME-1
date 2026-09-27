// cl: /DNDEBUG /MD /EHsc
// RVA 008B4480: eight independently looked-up channels; address-derived layouts.
class AptValue { public: int toInteger() const; };
class BfmeTab1024 { public: int bfmeFind1024(int); };
struct Value008B4480 {
 int m_f0;
 union { unsigned m_flags; struct { unsigned m_type:6; unsigned rest:26; }; };
 char pad08[0x20]; float m_f28,m_f2C,m_f30,m_f34,m_f38,m_f3C,m_f40,m_f44;
};
struct Owner008B4480 { char pad00[0x20]; Value008B4480 *m_f20; };
extern Value008B4480 **g_bfmeArr1233;
extern int g_stack01338748;
extern AptValue *g_bfmeFallbackDB;
extern int key01338668,key01338670,key01338568,key0133856C,key01338514,key01338518,key013384F4,key013384F8;
AptValue *aptApplyChannels008B4480(Owner008B4480 *self,int argc) {
 if(argc<=0) goto done;
 {
  Value008B4480 *v=g_bfmeArr1233[g_stack01338748-1];
  Value008B4480 *out=self->m_f20;
  if(!((unsigned char)~(out->m_flags>>15)&1)) {
   unsigned bits=v->m_flags;
   if(bits&0x8000) {
    if(v->m_type==0x1b && !((unsigned char)~(bits>>15)&1)) {
     BfmeTab1024 *tab=(BfmeTab1024*)((char*)v+8);
     AptValue *value=(AptValue*)tab->bfmeFind1024((int)&key01338668);
     if(value) out->m_f2C=value->toInteger()*0.01f;
     value=(AptValue*)tab->bfmeFind1024((int)&key01338670);
     if(value) out->m_f3C=value->toInteger()*(1.0f/255.0f);
     value=(AptValue*)tab->bfmeFind1024((int)&key01338568);
     if(value) out->m_f30=value->toInteger()*0.01f;
     value=(AptValue*)tab->bfmeFind1024((int)&key0133856C);
     if(value) out->m_f40=value->toInteger()*(1.0f/255.0f);
     value=(AptValue*)tab->bfmeFind1024((int)&key01338514);
     if(value) out->m_f34=value->toInteger()*0.01f;
     value=(AptValue*)tab->bfmeFind1024((int)&key01338518);
     if(value) out->m_f44=value->toInteger()*(1.0f/255.0f);
     value=(AptValue*)tab->bfmeFind1024((int)&key013384F4);
     if(value) out->m_f28=value->toInteger()*0.01f;
     value=(AptValue*)tab->bfmeFind1024((int)&key013384F8);
     if(value) out->m_f38=value->toInteger()*(1.0f/255.0f);
    }
   }
  }
 }
done:
 return g_bfmeFallbackDB;
}
