// ?ParsePath8C4DA0@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAD@Z
// partial score=0.986 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
extern "C" char *strcpy(char *,const char *);
#pragma intrinsic(strcpy)
struct BfmeHdrVKI { unsigned short refs,len,capacity,flags; };
struct Pool8C4DA0 { void *unused; void (__cdecl *free)(void *); };
extern Pool8C4DA0 *pool8C4DA0;
class BfmeStrVKI { public:
 BfmeHdrVKI *data;
 BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
 void bfmeSetVKI(const char *);
 ~BfmeStrVKI() { BfmeHdrVKI *p=data; if (--p->refs==0) pool8C4DA0->free(p); }
 const char *str() const { return (const char *)data+8; }
};
class BfmeNode1220 { public: int bfmeTest1220(int *,int); };
struct Root8C4DA0 { char pad[0x58]; BfmeNode1220 *root; };
struct Owner8C4DA0 { Root8C4DA0 *root; };
struct State8C4DA0 { char pad[0x122c]; Owner8C4DA0 *owner; };
extern State8C4DA0 *state8C4DA0;
bool ParsePath8C4DA0(BfmeNode1220 *inputScope,BfmeNode1220 *context,const BfmeStrVKI *path,BfmeNode1220 **out,char *name)
{
 BfmeNode1220 *scope=inputScope;
 const char *src=path->str();
 *name=0;
 bool absolute=false;
 if (*src=='/') {
  scope=state8C4DA0->owner->root->root;
  ++src;
  *out=scope;
  absolute=true;
 } else *out=scope;
 char buffer[256];
 char *dest=buffer;
 while (*src) {
  switch (*src) {
  case '.':
   if (src[1]=='.') {
    *dest++=*src;
    *dest++=*++src;
   } else {
    *dest=0;
    scope=(BfmeNode1220 *)scope->bfmeTest1220((int *)&BfmeStrVKI(buffer),(int)context);
    context=0;
    if (!scope) { *out=0; return absolute; }
    dest=buffer;
   }
   break;
  case ':': {
   *dest=0;
   BfmeNode1220 *found=(BfmeNode1220 *)scope->bfmeTest1220((int *)&BfmeStrVKI(buffer),(int)context);
   context=0;
   if (found) {
    *out=found;
    strcpy(name,src+1);
    return absolute;
   }
   dest=buffer;
   break;
  }
  default: *dest++=*src; break;
  }
  ++src;
 }
 *dest=0;
 if (context) scope=context;
 *out=scope;
 strcpy(name,buffer);
 return absolute;
}
