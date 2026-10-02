// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address identity only. Vtable pointer VA 0x01136990 names this start.
// Retail returns at 0x008D55F8; following switch tables end at 0x008D5648.
struct R4Word { const char *name; int value; };
const R4Word *Rva008D4F80(const char *, unsigned int);
class AptValue;
class AptBoolean { public: static AptBoolean *Create(bool); };
class AptInteger { public: static AptInteger *Create(int); };
AptValue *Rva008A4EA0MakeFloat(float);
class Rva008B2EA0Node { public: void append(void *); };
Rva008B2EA0Node *rva008B2EA0Create();
struct Rva008A9A70Str { void *block; };
class Rva008A9A70 { public: void set(const Rva008A9A70Str &); };
// Retail setter RVA 008A9A70 loads one pointer from each source holder.
// Initialization also reads/writes these cells as dwords at VA 013385D8,
// 01338678 and 01338524; their initial retail .data bytes are all zero.
Rva008A9A70Str g_013385D8 = { 0 };
Rva008A9A70Str g_01338678 = { 0 };
Rva008A9A70Str g_01338524 = { 0 };
extern AptValue *g_bfmeFallbackDB;
extern char g_012D5298;
struct Rva008D5430String { unsigned short refs, len; int capacity; char text[1]; };
class Rva008D5430 {
public:
 AptValue *method(void *, Rva008D5430String **);
 char pad[0x20];
 Rva008D5430String *f20;
 union { float f24; unsigned int bits24; };
 int f28;
 unsigned int f2c, f30;
 int f34, f38, f3c;
};
AptValue *Rva008D5430::method(void *arg, Rva008D5430String **key) {
 if (arg) {
 const R4Word *word = Rva008D4F80((*key)->text, (*key)->len);
 if (word) {
 switch (word->value) {
 case 1: {
  Rva008B2EA0Node *result = rva008B2EA0Create();
  switch(f2c) {
  case 0: ((Rva008A9A70*)result)->set(g_013385D8); return (AptValue*)result;
  case 1: ((Rva008A9A70*)result)->set(g_01338678); return (AptValue*)result;
  case 2: ((Rva008A9A70*)result)->set(g_01338524); return (AptValue*)result;
  case 3: return g_bfmeFallbackDB;
  }
  return g_bfmeFallbackDB;
 }
 case 3: if (f30 & 0x10000) { bool b=false; if(f30 & 1) b=true; return (AptValue*)AptBoolean::Create(b); } return g_bfmeFallbackDB;
 case 5: if(f28 != -1) return (AptValue*)AptInteger::Create(f28 & 0xffffff); return g_bfmeFallbackDB;
 case 6: if(f20 != (Rva008D5430String*)&g_012D5298) { Rva008B2EA0Node *r=rva008B2EA0Create(); r->append(f20->text); return (AptValue*)r; } return g_bfmeFallbackDB;
 case 7: if(f34 == -1) return g_bfmeFallbackDB; else return (AptValue*)AptInteger::Create(f34);
 case 8: if(f30 & 0x100000) { bool b=false; if(f30 & 0x10) b=true; return (AptValue*)AptBoolean::Create(b); } return g_bfmeFallbackDB;
 case 10: if(f38 == -1) return g_bfmeFallbackDB; else return (AptValue*)AptInteger::Create(f38);
 case 11: if(f3c == -1) return g_bfmeFallbackDB; else return (AptValue*)AptInteger::Create(f3c);
 case 14: if(bits24 != 0xbf800000) return Rva008A4EA0MakeFloat(f24); return g_bfmeFallbackDB;
 case 15: if(!(f30 & 0x1000000)) return g_bfmeFallbackDB; else { bool b=false; if(f30 & 0x100) b=true; return (AptValue*)AptBoolean::Create(b); }
 default: break;
 }
 }
 }
 return 0;
}
