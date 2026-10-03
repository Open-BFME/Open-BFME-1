// ?Rva009B4A10@@YAEPAEPAFH@Z
// partial score=0.1204 date=2026-10-03
// cl: /O2 /Ob1 /DNDEBUG /MD
// Decoder RVA 009B4A10..009B508D (1661 bytes). Draft only.
// Retail input: three cdecl arguments (context, short output, plane), AL result.
// 011429E8 = {0,1,2,3,4,5,7,11,19,35,67,0}; 01142A18 is the 64-entry
// coefficient band table; 01142BE0 is the 33-entry low-bit mask table.
// Both private readers are defined here so MSVC selects their real register ABI.
// The 74-byte reader probes exact. The 94-byte reader has retail EAX state / ECX
// width, but 50 differing bytes; do not pin or promote it as exact.
// Main:1643/1661 bytes,1425 nonreloc differences,frame14h versus0Ch.
// No strict relocation/data validation has passed for this draft.
// Decoder RVA 009B4A10. Layout and tree fields are address-qualified views
// of the offsets read by retail, not guesses at a vendor type identity.
struct Vp6RawBits { unsigned bits; unsigned value; const unsigned char *next; };
extern const unsigned Rva01142BE0Masks[33];
extern const int Rva011429E8Values[12];
extern const int Rva01142A18Bands[64];
static __forceinline unsigned Rva009B4A10Load(Vp6RawBits *s) {
 const unsigned char *p=s->next;
 unsigned v=p[0]; v=(v<<8)+p[1]; v=(v<<8)+p[2]; v=(v<<8)+p[3];
 s->next=p+4; s->value=v; return v;
}
static __forceinline int Rva009B4A10Bit(Vp6RawBits *s) {
 if(s->bits) { --s->bits; return (s->value>>s->bits)&1; }
 Rva009B4A10Load(s); s->bits=31; return s->value>>31;
}
static __declspec(noinline) int Rva009B47B0ReadBit(Vp6RawBits *s) {
 if(s->bits) { --s->bits; return (s->value>>s->bits)&1; }
 const unsigned char *p=s->next;
 unsigned v=p[0]; v=(v<<8)+p[1]; v=(v<<8)+p[2]; v=(v<<8)+p[3];
 s->value=v; s->next=p+4; s->bits=31; return s->value>>31;
}
static __declspec(noinline) unsigned Rva009B46E0(int n,Vp6RawBits *s) {
 unsigned old=s->value;
 unsigned remaining=s->bits;
 s->value=old & Rva01142BE0Masks[remaining];
 n-=remaining;
 unsigned result=0;
 if(n>0) {
  result=s->value<<n;
  const unsigned char *p=s->next;
  unsigned v=p[0]; v=(v<<8)+p[1]; v=(v<<8)+p[2]; v=(v<<8)+p[3];
  s->value=v; s->next=p+4; n-=32;
 }
 s->bits=-n;
 return (s->value>>s->bits)|result;
}
struct Rva009B4A10Edge { unsigned leaf:1,index:7,rest:24; };
struct Rva009B4A10Node { Rva009B4A10Edge child[2]; unsigned rest; };
struct Rva009B4A10Quick { unsigned short leaf:1,index:5,rest:6,bits:4; };
static __forceinline unsigned Rva009B4A10Token(Vp6RawBits *s,Rva009B4A10Quick *table,Rva009B4A10Node *tree) {
 unsigned prefix=s->value & ((1u<<s->bits)-1);
 if(s->bits>=6) prefix>>=s->bits-6;
 else prefix=((prefix<<8)|*s->next)>>(s->bits+2);
 s->bits-=table[prefix].bits;
 if((int)s->bits<0) { Rva009B4A10Load(s); s->bits+=32; }
 Rva009B4A10Quick entry=table[prefix];
 if(entry.leaf) return entry.index;
 Rva009B4A10Edge node;
 node.index=entry.index;
 do {
  if(Rva009B4A10Bit(s)) node=tree[node.index].child[1];
  else node=tree[node.index].child[0];
 } while(!node.leaf);
 return node.index;
}
struct Rva009B4A10Context {
 char at000[0x190]; Vp6RawBits at190;
 char at19c[0x4524-0x19c]; int at4524[2],at452c[2];
};
unsigned char Rva009B4A10(unsigned char *ctx,short *out,int plane) {
 Rva009B4A10Context *self=(Rva009B4A10Context*)ctx;
 Vp6RawBits *s=&self->at190;
 int coefficient=1;
 int context;
 if(self->at4524[plane]>0) { --self->at4524[plane]; context=0; }
 else {
  int token=Rva009B4A10Token(s,(Rva009B4A10Quick*)(ctx+0x30fc+plane*0x80),(Rva009B4A10Node*)(ctx+0xa20+plane*0x90));
  int value=Rva011429E8Values[token];
  if(token==11) return ctx[coefficient+0x5fb];
  if(token==0) {
   int run=Rva009B46E0(2,s)+1;
   if(run==3) run=Rva009B46E0(2,s)+3;
   else if(run==4) {
    if(Rva009B47B0ReadBit(s)) run=Rva009B46E0(6,s)+11;
    else run=Rva009B46E0(2,s)+7;
   }
   self->at4524[plane]=run-1;
   context=0;
  } else {
   if(token>4) value+=Rva009B46E0(token>9?11:token-4,s);
   int sign=Rva009B47B0ReadBit(s);
   out[0]=(short)((-sign^value)+sign);
   context=(value>1)+1;
  }
 }
 if(self->at452c[plane]>0) { --self->at452c[plane]; return ctx[coefficient+0x5fb]; }
 do {
  int index=(plane+context*2)*6+Rva01142A18Bands[coefficient];
  int token=Rva009B4A10Token(s,(Rva009B4A10Quick*)(ctx+0x31fc+index*0x80),(Rva009B4A10Node*)(ctx+0x1a70+index*0x90));
  int value=Rva011429E8Values[token];
  if(token==0) {
   int group=coefficient>5;
   unsigned run=Rva009B4A10Token(s,(Rva009B4A10Quick*)(ctx+0x43fc+group*0x80),(Rva009B4A10Node*)(ctx+0x2fac+group*0xa8));
   if(run<8) coefficient+=run;
   else coefficient+=8+Rva009B46E0(6,s);
   context=0;
  } else {
   if(token==11) {
    if(coefficient==1) {
     int run=Rva009B46E0(2,s)+1;
     if(run==3) run=Rva009B46E0(2,s)+3;
     else if(run==4) {
      if(Rva009B47B0ReadBit(s)) run=Rva009B46E0(6,s)+11;
      else run=Rva009B46E0(2,s)+7;
     }
     self->at452c[plane]=run-1; return ctx[coefficient+0x5fb];
    }
    return ctx[coefficient+0x5fb];
   }
   int sign;
   if(token<5) sign=Rva009B4A10Bit(s);
   else { value+=Rva009B46E0(token>9?11:token-4,s); sign=Rva009B47B0ReadBit(s); }
   out[ctx[coefficient+0x57c]]=(short)((-sign^value)+sign);
   context=(value>1)+1;
  }
 } while(++coefficient<64);
 return ctx[coefficient+0x5fb];
}
