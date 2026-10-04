// Retail 0x00237950..0x00237A59: complete return body.
// Address-qualified identity. Native list/hash traversal and index layout
// are independently shared with landed neighbour 0x002377A0.
// Calls the controlling-player query at 0x00020824 and slot 0x28; broadcast
// references the existing body at 0x000376CD, which jumps to 0x004141C0.
// Both calls are made directly through the linked names, with no linker
// name aliasing pragma.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>
class Player;
#include "GameLogic/Object/object.h"
extern void j_00020824();
extern void d_000376cd();
struct PlayerList00237950 {char at000[12]; Player *m_local;};
struct GlobalData00237950 {char at000[0xa76]; bool atA76;};
class PlayerList;
class GlobalData;
extern PlayerList *ThePlayerList;
extern GlobalData *TheWritableGlobalData;
struct IndexNode00237950 {unsigned color; IndexNode00237950 *parent,*left,*right; unsigned key;};
namespace _STL {struct _Rb_tree_node_base; template<class T> struct _Rb_global {static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base*);};}
typedef _STL::hash_map<unsigned,Object*,_STL::hash<unsigned>,_STL::equal_to<unsigned> > Hash00237950;
struct GameLogic00237950 {
 char at000[0xb0]; Hash00237950 at0b0;
 __forceinline Object *find(unsigned key) {
  Hash00237950::iterator it=at0b0.find(key);
  if(it==at0b0.end()) return 0;
  return (*it).second;
 }
};
class GameLogic;
extern GameLogic *TheGameLogic;
class MemberBroadcast00237950 {
public:
 char at000[0x30]; IndexNode00237950 *at030;
 void run();
};
class Rva004141C0 {};
static __forceinline void broadcast00237950(void *drawable) {
 typedef void (Rva004141C0::*Fn)();
 union { void (*fn)(); Fn call; } u = { d_000376cd };
 ((Rva004141C0*)drawable->*u.call)();
}
void MemberBroadcast00237950::run() {
 typedef Player *(Object::*Gcp)() const;
 union { void (*fn)(); Gcp call; } gcp = { j_00020824 };
 Player *localPlayer=((PlayerList00237950*)ThePlayerList)->m_local;
 bool forwardMembers=false;
 Object *owner=*(Object**)((char*)this-0xdc);
 if(owner) {
  if((owner->*gcp.call)()==localPlayer) {
   Drawable *drawable=owner->getDrawable();
   if(((GlobalData00237950*)TheWritableGlobalData)->atA76) {
    if(drawable) broadcast00237950(drawable);
   } else forwardMembers=true;
  }
 }
 _STL::list<Object*> &members=*(_STL::list<Object*>*)((char*)this-0xac);
 _STL::list<Object*>::const_iterator it=members.begin();
 while(it!=members.end()) {
  Object *member=*it;
  if(member) {
   Drawable *drawable=member->getDrawable();
   if(drawable && forwardMembers) broadcast00237950(drawable);
  }
  ++it;
 }
 IndexNode00237950 *entry=at030->left;
 while(entry!=at030) {
  unsigned key=entry->key;
  if(key) {
   Object *member=((GameLogic00237950*)TheGameLogic)->find(key);
   if(member) {
    Drawable *drawable=member->getDrawable();
    if(drawable && forwardMembers) broadcast00237950(drawable);
   }
  }
  entry=(IndexNode00237950*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)entry);
 }
}
