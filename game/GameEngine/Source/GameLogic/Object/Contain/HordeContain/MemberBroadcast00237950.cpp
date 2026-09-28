// Retail 0x00237950..0x00237A59: complete return body.
// Address-qualified identity. Native list/hash traversal and index layout
// are independently shared with landed neighbour 0x002377A0.
// Calls Object::getControllingPlayer and slot 0x28; broadcast uses the
// exact existing ILT route to 0x004141C0.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>
class Player;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "GameLogic/Object/object.h"
class Rva004141C0 {public: void broadcast();};
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?broadcast@Rva004141C0@@QAEXXZ=?d_000376cd@@YAXXZ")
struct PlayerList00237950 {char at000[12]; Player *m_local;};
struct GlobalData00237950 {char at000[0xa76]; bool atA76;};
extern PlayerList00237950 *g00237950Va012ED748;
extern GlobalData00237950 *g00237950Va012ED5C8;
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
extern GameLogic00237950 *g00237950Va012F0898;
class MemberBroadcast00237950 {
public:
 char at000[0x30]; IndexNode00237950 *at030;
 void run();
};
void MemberBroadcast00237950::run() {
 Player *localPlayer=g00237950Va012ED748->m_local;
 bool forwardMembers=false;
 Object *owner=*(Object**)((char*)this-0xdc);
 if(owner) {
  if(owner->getControllingPlayer()==localPlayer) {
   Drawable *drawable=owner->getDrawable();
   if(g00237950Va012ED5C8->atA76) {
    if(drawable) ((Rva004141C0*)drawable)->broadcast();
   } else forwardMembers=true;
  }
 }
 _STL::list<Object*> &members=*(_STL::list<Object*>*)((char*)this-0xac);
 _STL::list<Object*>::const_iterator it=members.begin();
 while(it!=members.end()) {
  Object *member=*it;
  if(member) {
   Drawable *drawable=member->getDrawable();
   if(drawable && forwardMembers) ((Rva004141C0*)drawable)->broadcast();
  }
  ++it;
 }
 IndexNode00237950 *entry=at030->left;
 while(entry!=at030) {
  unsigned key=entry->key;
  if(key) {
   Object *member=g00237950Va012F0898->find(key);
   if(member) {
    Drawable *drawable=member->getDrawable();
    if(drawable && forwardMembers) ((Rva004141C0*)drawable)->broadcast();
   }
  }
  entry=(IndexNode00237950*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)entry);
 }
}
