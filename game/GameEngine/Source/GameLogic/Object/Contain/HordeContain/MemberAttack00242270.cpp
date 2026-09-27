// Retail 0x00242270 complete 411-byte body; address-qualified identity.
// Tree lookup is STLport _Rb_tree::_M_find with an inline iterator boundary.
// The first map selects a 16-byte roster slot; data+250 is a signed-key tree.
// ThingTemplate+0xd4 remains offset-named: name_oracle has no witness there.
// cl: /DNDEBUG /MD /EHsc-
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <map>
#include <set>
#include <list>
#include "../../object.h"
extern void j_000022bb(); extern void j_00031a7f(); extern void j_00028f74();
extern void j_00014b4b(); extern void j_0003f990(); extern void j_0002edcf();
class Route00242270 {};
struct Template00242270 {
 void *at000; Template00242270 *at004; char pad008[0xd4-8]; unsigned at0d4;
 __forceinline Template00242270 *finalOverride() {
  if(at004) { typedef Template00242270 *(Route00242270::*Call)(); union {void(*fn)();Call call;} route={j_000022bb}; return (((Route00242270*)at004)->*route.call)(); }
  return this;
 }
};
__forceinline Template00242270 *objectTemplate00242270(Object *obj) { if(!obj->m_template) return 0; return ((Template00242270*)obj->m_template)->finalOverride(); }
struct Weapon00242270 { void *at000; Route00242270 *at004; };
extern Route00242270 *g00242270Va012EF214;
template<int N> class Slots00242270 : public Slots00242270<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots00242270<0> {};
struct TreeNode00242270 { int color; TreeNode00242270 *parent,*left,*right; int key,value; };
struct Iterator00242270 {
 TreeNode00242270 *node; Iterator00242270(TreeNode00242270 *p):node(p) {}
 bool operator==(const Iterator00242270 &b) const {return node==b.node;}
 bool operator!=(const Iterator00242270 &b) const {return node!=b.node;}
 TreeNode00242270 *operator->() const {return node;}
};
struct Tree00242270 {
 TreeNode00242270 *head; unsigned count; int unused;
 __forceinline Iterator00242270 find(const int &key) { return Iterator00242270(findNode(key)); }
 __forceinline TreeNode00242270 *findNode(const int &key) {
  TreeNode00242270 *y=head,*x=head->parent;
  while(x) { if(!(x->key<key)) { y=x; x=x->left; } else x=x->right; }
  if(y==head || key<y->key) y=head; return y;
 }
 Iterator00242270 end() { return Iterator00242270(head); }
};
struct Slot00242270 { int at000; char pad004[12]; };
class MemberAttack00242270 : public Slots00242270<4> {
public:
 virtual void slot010(int)=0;
 char pad004[0x30-4]; _STL::set<unsigned> at030; Tree00242270 at03c; Slot00242270 *at048;
 void run();
 _STL::list<Object*>& members() { return *(_STL::list<Object*>*)((char*)this-0xac); }
};
void MemberAttack00242270::run() {
 Object *owner=*(Object**)((char*)this-0xdc);
 if(objectTemplate00242270(owner)->at0d4 & 0x400000) {
  typedef Weapon00242270 *(Route00242270::*GetWeapon)(int*);
  union {void(*fn)();GetWeapon call;} getWeapon={j_00031a7f};
  Weapon00242270 *weapon=(((Route00242270*)owner)->*getWeapon.call)(0);
  if(!weapon) return;
  typedef unsigned char (Route00242270::*GetByte)();
  union {void(*fn)();GetByte call;} getByte={j_00028f74};
  if((weapon->at004->*getByte.call)()) return;
 }
 if(!at030.empty()) slot010(0);
 _STL::list<Object*>::iterator it=members().begin();
 Tree00242270 *allowed=(Tree00242270*)(*(char**)((char*)this-0xe0)+0x250);
 while(it!=members().end()) {
  Object *obj=*it;
  int id=obj->m_id;
  if(at03c.find(id)==at03c.end()) { ++it; continue; }
  int index=at03c.find(id)->value;
  int key=at048[index].at000;
  if(allowed->find(key)!=allowed->end()) {
   typedef float (Route00242270::*Vision)();
   union {void(*fn)();Vision call;} vision={j_00014b4b};
   typedef Object *(Route00242270::*FindEnemy)(Object*,float,int,int,int);
   union {void(*fn)();FindEnemy call;} findEnemy={j_0003f990};
   Object *enemy=(g00242270Va012EF214->*findEnemy.call)(obj,(((Route00242270*)obj)->*vision.call)(),2,0,0);
   if(enemy) {
    typedef void (Route00242270::*Attack)(Object*,int,int);
    union {void(*fn)();Attack call;} attack={j_0002edcf};
    (((Route00242270*)((char*)obj->m_ai+0x20))->*attack.call)(enemy,0x7fffffff,2);
   }
  }
  ++it;
 }
}
