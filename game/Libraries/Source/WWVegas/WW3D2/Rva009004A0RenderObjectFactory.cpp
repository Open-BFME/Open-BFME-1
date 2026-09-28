// cl: /DNDEBUG /MD /EHsc
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// Retail 009004A0: cdecl six-argument factory; legacy thiscall identity disproven.
// Proof: targets/game/reverse/identity_evidence/009004A0-cdecl-render-object-factory.md
// These local interface views preserve the already-landed helper decorations.
// The unknown factory/object identity stays address-qualified. No shared layout
// is changed. The prototype allocation and three-pointer containers are directly
// witnessed by this body and Rva00900FF0Constructor.cpp.
class Rva009EB7A0RefOwner { public: void Release_Ref(); };
class BfmeThingVGK { public: void bfmeGoVGK(const char*); };
class Rva009004A0Object {
public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
 virtual void s30(); virtual void s34(); virtual void s38();
 virtual Rva009004A0Object *create();
 void release() { ((Rva009EB7A0RefOwner*)this)->Release_Ref(); }
 void setName(const char *s) { ((BfmeThingVGK*)this)->bfmeGoVGK(s); }
};
class Rva009EBCE0AssetReference {
public:
 Rva009004A0Object *object;
 ~Rva009EBCE0AssetReference() { if(object) object->release(); }
};
extern Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char*);
class Gen008FF1B0 {
public:
 Gen008FF1B0(void*);
private:
 Gen008FF1B0 *bfmeInit(void*);
public:
 void assign(void *p) { bfmeInit(p); }
 Rva009004A0Object *object;
 ~Gen008FF1B0() { if(object) object->release(); }
};
// Retail STLport string calls are out of line. Preserve their real template
// names and the 12-byte storage view, without instantiating a different vendor
// implementation in this TU. The input string vector uses its existing opaque
// Rva00900FF0VecOfVec identity from the constructor, even though its elements
// here are demonstrably narrow strings.
namespace _STL {
template<class T> class char_traits {};
template<class T> class allocator {};
struct input_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
template<class T,class Traits,class Alloc> class basic_string {
public:
 T *first,*last,*end;
 basic_string();
 ~basic_string();
private:
 template<class It> basic_string &append(It,It,const forward_iterator_tag&);
public:
 void push_back(T);
 void add(const T &c) { push_back(c); }
 const T *c_str() const { return first ? first : ""; }
 void append(const T *s) { append(s,s+strlen(s),forward_iterator_tag()); }
};
}
typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > Rva009004A0String;
class Rva00900FF0VecOfVec {
public:
 Rva009004A0String *first,*last,*end;
 Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec&);
 ~Rva00900FF0VecOfVec();
 unsigned size() const {return last-first;}
 bool empty() const {return first==last;}
};
class Gen_ve_001f9520 {};
namespace _STL {
template<class T,class Alloc> class vector {
public:
 T *first,*last,*end;
 vector(const vector&);
 ~vector();
 unsigned size() const {return last-first;}
};
}
typedef _STL::vector<Gen_ve_001f9520*,_STL::allocator<Gen_ve_001f9520*> > Rva009004A0Ints;
class Rva00900FF0 {
 char bytes[0x74];
public:
 Rva00900FF0(const char*,const char*,int,int,Rva00900FF0VecOfVec,Rva00900FF0VecOfVec,Rva009004A0Ints);
};
extern bool g_flag12D6DA8;
extern bool Render_Obj_Exists(const char*);
extern void Add_Prototype(void*);
Rva009004A0Object *Rva009004A0CreateRenderObject(const char *name,float scale,unsigned color,const Rva00900FF0VecOfVec &a,const Rva00900FF0VecOfVec &b,const Rva009004A0Ints &c)
{
 if(!name || *name=='#') return 0;
 char lower[2048];
 strcpy(lower,name); _strlwr(lower);
 Gen008FF1B0 proto((void*)&Rva009EBCE0_GetPrototype(lower));
 if(!proto.object) return 0;
 if(!g_flag12D6DA8) color=0;
 float delta=scale-1.0f;
 // WWMath::Fabs uses this integer sign-bit mask, not an x87 fabs.
 *(unsigned*)&delta &= 0x7fffffff;
 bool scaled=delta>0.01f;
 bool colored=(color&0xffffff)!=0;
 if(!scaled && !colored && a.empty() && b.empty()) return proto.object->create();
 Rva009004A0String sa,sb,sc;
 for(unsigned i=0;i<a.size();++i) sa.append(a.first[i].first);
 for(unsigned j=0;j<b.size();++j) sb.append(b.first[j].first);
 for(unsigned k=0;k<c.size();++k) sc.add(char((int)c.first[k]+'0'));
 char combined[2048];
 sprintf(combined,"#%d!%g!%s#%s#%s!%s",color,scale,sa.c_str(),name,sb.c_str(),sc.c_str());
 _strlwr(combined);
 if(!Render_Obj_Exists(combined)) Add_Prototype(new Rva00900FF0(combined,name,*(int*)&scale,color,a,b,c));
 proto.assign((void*)&Rva009EBCE0_GetPrototype(combined));
 if(proto.object) {
  Rva009004A0Object *result=proto.object->create();
  if(result) {result->setName(name); return result;}
 }
 return 0;
}
