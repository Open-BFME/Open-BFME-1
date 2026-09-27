// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00901B00, 1146 bytes. Address-qualified identity: name normalization,
// cached modified-prototype creation, and final instance naming are witnessed
// by the calls to 0x009EBCE0 / 0x008FED30 / 0x00900E40 / 0x0091FCC0.
// The seventh stack argument is preserved through both the munge helper and
// the prototype constructor. Prototype slot +0x3c creates the instance.
// Named string locals preserve the separate address loads and EH lifetimes
// before the three vector push_back calls. The munge helper is nonthrowing:
// its matched body only calls the imported sprintf and _strlwr routines.
// Container shims below retain the already-landed constructor's ABI spelling;
// all three local containers are native STLport vector<string> values.
#include <string.h>
#include <string>
#include <vector>

// The three aligned calls reach ILT 0x00008F17 -> 0x00755F10. The target
// appends a 12-byte element and invokes the string copy construction helper
// at 0x00754B20; retain the address-owned ILT rather than minting a body name.

class BfmeThingVGK { public: void bfmeGoVGK(const char *); };
class Rva009EB7A0RefOwner {
public:
 void Release_Ref();
};
class Prototype00901B00 {
public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
 virtual void s30(); virtual void s34(); virtual void s38();
 virtual BfmeThingVGK *create();
};
class Rva009EBCE0AssetReference {
public:
 Prototype00901B00 *m_object;
 ~Rva009EBCE0AssetReference() { if (m_object) ((Rva009EB7A0RefOwner *)m_object)->Release_Ref(); }
};
extern Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *);
class Gen008FF1B0 {
public:
 Gen008FF1B0(void *);
 ~Gen008FF1B0() { if (m_object) ((Rva009EB7A0RefOwner *)m_object)->Release_Ref(); }
 void assign(const Rva009EBCE0AssetReference &r) { bfmeInit((void *)&r); }
 Prototype00901B00 *m_object;
private:
 Gen008FF1B0 *bfmeInit(void *);
};
// Address-only call bridge: the ledger still gives the target an unrelated
// AnimSet instantiation name. Do not add a conflicting second body identity.
extern void j_00008f17();
static __forceinline void appendString00901B00(_STL::vector<_STL::string> &out, const _STL::string &value)
{
 typedef void (_STL::vector<_STL::string>::*Operation)(const _STL::string &);
 union { void *address; Operation method; } call;
 call.address = reinterpret_cast<void *>(j_00008f17);
 (out.*call.method)(value);
}
class Rva00900FF0VecOfVec {
public:
 Rva00900FF0VecOfVec() : m_start(0),m_finish(0),m_end(0) {}
 Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &);
 ~Rva00900FF0VecOfVec();
 void push_back(const _STL::string &);
 char *m_start,*m_finish,*m_end;
};
#pragma comment(linker, "/alternatename:??0Rva00900FF0VecOfVec@@QAE@ABV0@@Z=?d_008ffb80@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00900FF0VecOfVec@@QAE@XZ=?j_0000b109@@YAXXZ")
#pragma comment(linker, "/alternatename:?push_back@Rva00900FF0VecOfVec@@QAEXABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z=?j_00008f17@@YAXXZ")
class Rva00900FF0 {
public:
 Rva00900FF0(const char *,const char *,int,int,Rva00900FF0VecOfVec,Rva00900FF0VecOfVec,Rva00900FF0VecOfVec,int);
 char m_00[0x74];
};
struct StrView008FED30 { char *start,*finish; };
extern void Munge_Render_Obj_Name(char *,const char *,float,int,StrView008FED30 *,StrView008FED30 *,int) throw();
inline void munge00901B00(char *out,const char *name,float scale,int color,const _STL::string &texture,const _STL::string &sub,int extra) throw() {
 Munge_Render_Obj_Name(out,name,scale,color,(StrView008FED30 *)&texture,(StrView008FED30 *)&sub,extra);
}
extern bool Render_Obj_Exists(const char *);
extern void Add_Prototype(void *);
extern bool g_012D6DA8;
inline float abs00901B00(float x) { *(unsigned *)&x &= 0x7fffffff; return x; }
BfmeThingVGK *CreateModifiedRenderObj00901B00(const char *name,float scale,int color,const char *a,const char *b,const char *c,int extra)
{
 if (!name || *name=='#') return 0;
 char lowered[2048];
 strcpy(lowered,name);
 _strlwr(lowered);
 Gen008FF1B0 prototype((void *)&Rva009EBCE0_GetPrototype(lowered));
 if (!prototype.m_object) return 0;
 if (!g_012D6DA8) color=0;
 bool scaled=abs00901B00(scale-1.0f)>0.01f;
 bool colored=(color & 0xffffff)!=0;
 BfmeThingVGK *result;
 if (scaled || colored || a || b) {
   char modified[2048];
   munge00901B00(modified,name,scale,color,b?b:"",c?c:"",extra);
   if (!Render_Obj_Exists(modified)) {
     _STL::vector<_STL::string> first,second,third;
     if (a) { _STL::string value(a); appendString00901B00(first,value); }
     if (b) { _STL::string value(b); appendString00901B00(second,value); }
     if (c) { _STL::string value(c); appendString00901B00(third,value); }
     Add_Prototype(new Rva00900FF0(modified,name,*(int *)&scale,color,*(Rva00900FF0VecOfVec *)&first,*(Rva00900FF0VecOfVec *)&second,*(Rva00900FF0VecOfVec *)&third,extra));
   }
   prototype.assign(Rva009EBCE0_GetPrototype(modified));
   if (!prototype.m_object || !(result=prototype.m_object->create())) return 0;
   result->bfmeGoVGK(name);
 } else {
   result=prototype.m_object->create();
 }
 return result;
}
