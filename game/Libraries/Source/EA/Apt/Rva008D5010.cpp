// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Opaque vtable method: slot VA 0x01136994 -> RVA 0x008D5010.
// Int3 before start; ret 12 at 0x008D53EB; dispatch table to next proven start 0x008D5430.
#include <string.h>
struct R4Word { const char *name; int value; };
const R4Word *Rva008D4F80(const char *, unsigned int);
struct Rva8CD130StringBlock { unsigned short refs, len; int capacity; char text[1]; };
extern Rva8CD130StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class Rva8CD130String {
public:
 Rva8CD130String() { block=&g_bfmeDefaultString1284; ++block->refs; }
 __forceinline ~Rva8CD130String() { Rva8CD130StringBlock *p=block; --p->refs; if(p->refs==0) Rva01337A30ReleaseTable[1](p); }
 Rva8CD130StringBlock *block;
};
class Rva8CD130Value { public: void getName(Rva8CD130String *); };
class AptValue { public: int toInteger() const; float toNumber(); };
class Rva008D5010 {
public:
 bool method(void *, Rva8CD130String *, AptValue *);
 char pad[0x20];
 Rva8CD130String f20;
 float f24;
 int f28, f2c;
 unsigned int f30;
 int f34,f38,f3c;
};
bool Rva008D5010::method(void *arg,Rva8CD130String *key,AptValue *value) {
 if(arg) {
 const R4Word *word=Rva008D4F80(key->block->text,key->block->len);
 if(word) {
 switch(word->value) {
 case 1: {
  Rva8CD130String s; ((Rva8CD130Value*)value)->getName(&s);
  if(!strcmp(s.block->text,"left") || !strcmp(s.block->text,"true")) f2c=0;
  else if(!strcmp(s.block->text,"center")) f2c=2;
  else if(!strcmp(s.block->text,"right")) f2c=1;
  else if(!strcmp(s.block->text,"false") || !strcmp(s.block->text,"none")) f2c=3;
  return true;
 }
 case 5: f28=value->toInteger(); return true;
 case 6: ((Rva8CD130Value*)value)->getName(&f20); return true;
 case 2: case 3: {
  Rva8CD130String s; ((Rva8CD130Value*)value)->getName(&s);
  if(!strcmp(s.block->text,"true")) f30 |= 0x10001;
  if(!strcmp(s.block->text,"false")) { f30 |= 0x10000; if(f30 & 1) f30 ^= 1; }
  return true;
 }
 case 4: case 7: f34=value->toInteger(); return true;
 case 8: {
  Rva8CD130String s; ((Rva8CD130Value*)value)->getName(&s);
  if(!strcmp(s.block->text,"true")) f30 |= 0x100010;
  if(!strcmp(s.block->text,"false")) { f30 |= 0x100000; if(f30 & 0x10) f30 ^= 0x10; }
  return true;
 }
 case 9: case 10: f38=value->toInteger(); return true;
 case 11: f3c=value->toInteger(); return true;
 case 12: case 13: case 15: {
  Rva8CD130String s; ((Rva8CD130Value*)value)->getName(&s);
  if(!strcmp(s.block->text,"true")) f30 |= 0x1000100;
  if(!strcmp(s.block->text,"false")) { f30 |= 0x1000000; if(f30 & 0x100) f30 ^= 0x100; }
  return true;
 }
 case 14: f24=value->toNumber(); return true;
 case 16: return true;
 }
 }
 }
 return false;
}

