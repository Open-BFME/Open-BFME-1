// Retail 0x0036F1B0, 228 bytes. Address-derived identity.
// Iterates an ObjectID vector, resolves each object through the STLport registry,
// finds CastleMemberBehavior by the retail literal, and writes its +0x14 payload.
// Retail has cdecl cleanup; global registry +0xB0 and node offsets match the
// independently landed GameLogicFindObjectByID.cpp. The enclosing semantic name
// is unproved, so this function retains the unique address token.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>
enum NameKeyType {};
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
// Retail's Object::findModule (0x001BEE60) is a protected member, so the mangled
// call name carries that access; only the friend may call it here.
class Object { protected: Module *findModule(NameKeyType) const; friend void SetMemberPayload0036F1B0(_STL::vector<int> *,int); };
typedef _STL::hash_map<int,Object*,_STL::hash<int>,_STL::equal_to<int> > ObjectPtrHash;
class ObjectRegistry0036F1B0 {
 char pad[0xb0]; ObjectPtrHash objects;
public:
 __forceinline Object *lookup(int id) {
  if (!id) return 0;
  ObjectPtrHash::iterator it=objects.find(id);
  if(it==objects.end()) return 0;
  return it->second;
 }
};
class GameLogic;
extern GameLogic *TheGameLogic;
void SetMemberPayload0036F1B0(_STL::vector<int> *ids,int payload) {
 static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 for(_STL::vector<int>::iterator it=ids->begin();it!=ids->end();++it) {
  Object *object=((ObjectRegistry0036F1B0*)TheGameLogic)->lookup(*it);
  if(object) {
   Module *module=object->findModule(key);
   if(module) *(int*)((char*)module+0x14)=payload;
  }
 }
}
