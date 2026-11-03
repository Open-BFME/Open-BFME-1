// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS 
// stlport
//
// Orders every contained member whose template carries kind bit 0x4000 to
// repair TARGET, after ActionManager::canRepairObject accepts the pair, and
// remembers the target's id at +0x348. Owner identity is not recovered; the
// name keeps the address. Shape follows the BFME 2 HordeWorkerAIUpdate private
// repair donor.
#define OBJECT_TU_MEMBERS void *unidentified_001BFE20() const;
#include "../GameLogic/Object/object.h"
#include "../GameLogic/command_source_type.h"
#include <list>
class ActionManager {
public: bool canRepairObject(const Object *,const Object *,CommandSourceType);
};
extern ActionManager *TheActionManager;
class AICommandInterface { public: void aiRepair(Object *,CommandSourceType); };
class Rva002C4EA0UpdateBase { public: virtual ~Rva002C4EA0UpdateBase(); char m_pad04[0x20-4]; };
class AIUpdateInterface : public Rva002C4EA0UpdateBase, public AICommandInterface {};
static __forceinline AIUpdateInterface *rva002C4EA0AI(const Object *object) { return object->m_ai; }
class Overridable { public: const Overridable *getFinalOverride() const; };
struct Rva002C4EA0Template {
 void *m_vptr;
 Overridable *m_override;
 char m_pad08[0xc8-8];
 unsigned int m_kindC8;
};
class BfmeRva493A0Object;
namespace _STL {
template<> list<BfmeRva493A0Object *,allocator<BfmeRva493A0Object *> >::list(const list<BfmeRva493A0Object *,allocator<BfmeRva493A0Object *> >&);
template<> _List_base<BfmeRva493A0Object *,allocator<BfmeRva493A0Object *> >::~_List_base();
}
template<int N> class Rva002C4EA0Slots:public Rva002C4EA0Slots<N-1>{public:virtual void slot(char(*)[N]);};
template<> class Rva002C4EA0Slots<0>{};
class Rva002C4EA0Contain:public Rva002C4EA0Slots<40>{public:
 virtual void slotA0(Object*);
 virtual void x41();virtual void x42();virtual void x43();virtual void x44();virtual void x45();virtual void x46();virtual void x47();virtual void x48();virtual void x49();virtual void x50();virtual void x51();virtual void x52();virtual void x53();virtual void x54();virtual void x55();virtual void x56();virtual void x57();virtual void x58();
 virtual const _STL::list<BfmeRva493A0Object*> &slotEC();
};
class Rva002C4EA0 {
public: void method(Object*,CommandSourceType); __forceinline void setAt348(unsigned int value) { m_at348=value; }
 char m_head00[8];Object *m_object08;
 char m_pad0C[0x348-0xc]; unsigned int m_at348;
};
void Rva002C4EA0::method(Object *target,CommandSourceType source){
 Object *me=m_object08;
 if(!TheActionManager->canRepairObject(me,target,source))return;
 Rva002C4EA0Contain *contain=(Rva002C4EA0Contain*)me->unidentified_001BFE20();
 if(!contain)return;
 _STL::list<BfmeRva493A0Object*> members=contain->slotEC();
 for(_STL::list<BfmeRva493A0Object*>::iterator it=members.begin();it!=members.end();++it){
  Object *member=reinterpret_cast<Object *>(*it);
  Rva002C4EA0Template *info=(Rva002C4EA0Template*)member->m_template;
  if(info&&info->m_override)info=(Rva002C4EA0Template*)info->m_override->getFinalOverride();
  if(info->m_kindC8&0x4000){
   contain->slotA0(member);
   rva002C4EA0AI(member)->aiRepair(target,CMD_FROM_AI);
   setAt348(target->m_id);
  }
 }
}
