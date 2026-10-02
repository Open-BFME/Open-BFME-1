// cl: /O2 /Ob2 /MD /EHsc
// InGameUI::canSelectedObjectsDoAction, RVA 0x00447A40.
// Port of GeneralsMD/Code/GameEngine/Source/GameClient/InGameUI.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in that source.
// Identity: source twin's selected-list loop, rule counters and action dispatch.
// BFME removes the initial target-null guard and adds cases 9, 19 and 20.
// Case 6 follows the retail repair condition, not the different ZH expression.
// Layout: name_oracle witnesses Drawable::m_object +0xFC and
// Object::m_contain +0x1FC / m_id +0x74; canonical Object/Thing headers used.
// Boundary: final ret 16 ends at +0x37B, one NOP then 21 switch dwords;
// +0x3D0 is the end of that compiler-generated table, followed by INT3 padding.
// UI vslot 63 and interface slots are witnessed by this body and landed
// InGameUISiegeDockSelection.cpp; unnamed interface methods stay address-tagged.
enum KindOfType { KINDOF_INVALID = 0 };
enum ObjectID { INVALID_ID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum CanEnterType { CHECK_CAPACITY=0, DONT_CHECK_CAPACITY=1, COMBATDROP_INTO=2 };
class ExitInterface;
#define BFME_HAVE_OBJECTID
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS ObjectID getSoleHealingBenefactor() const; ExitInterface *getObjectExitInterface() const; bool isLocallyControlled() const;
#include "../GameLogic/Object/object.h"
class Drawable : public Thing {
 unsigned char m_unreconstructed_60[0xfc-0x60];
public: Object *m_object;
 Object *getObject() const { return m_object; }
};
class ContainModuleInterface { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual bool isHealContain() const;
 virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual bool rva00447A40Slot10() const;
};
class ExitInterface { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual bool rva00447A40Slot6() const;
};
class ActionManager { public:
 bool rvaC50C0DockPredicate(const Object*, const Object*, int, bool);
 bool canGetHealedAt(const Object*,const Object*,CommandSourceType);
 bool canRepairObject(const Object*,const Object*,CommandSourceType);
 bool canHijackVehicle(const Object*,const Object*,CommandSourceType);
 bool canConvertObjectToCarBomb(const Object*,const Object*,CommandSourceType);
 bool canCaptureBuilding(const Object*,const Object*,CommandSourceType);
 bool queryRva000C5EF0(Object*,Object*,int);
};
class Rva000C4D80Manager { public: bool evaluate(Object*,const Object*,int); };
class Rva000C41C0ActionManager { public: bool canMakeObjectDefector(const Object*,const Object*,CommandSourceType); };
class BFMEActionManager { public:
 bool canEnterObject(const Object*,const Object*,CommandSourceType,CanEnterType,bool*);
 bool rva000C4080(const Object*,const Object*,CommandSourceType);
 bool rva000C46A0(const Object*,const Object*,CommandSourceType);
 bool rva000C6820(const Object*,const Object*,CommandSourceType);
 bool rva000C4390(const Object*,const Object*,CommandSourceType);
};
// Retail: 0x012ED700 is EA's ActionManager *TheActionManager (see
// game/GameEngine/Source/Common/System/game_engine_subsystems.h); the members
// reached through it here keep their proven per-class spellings, so cast.
extern ActionManager *TheActionManager;
struct DrawableListNode { DrawableListNode *next,*prev; Drawable *value; };
class DrawableList { public:
 class const_iterator { DrawableListNode *node; public:
 const_iterator(DrawableListNode *n):node(n){}
 bool operator!=(const const_iterator &b)const{return node!=b.node;}
 Drawable *operator*()const{return node->value;}
 const_iterator &operator++(){node=node->next;return *this;}
 };
 DrawableListNode *head;
 const_iterator begin()const{return const_iterator(head->next);}
 const_iterator end()const{return const_iterator(head);}
};
class InGameUI { public:
 enum ActionType { ACTIONTYPE_NONE=0 };
 enum SelectionRules { SELECTION_ANY=0, SELECTION_ALL=1 };
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual const DrawableList *getAllSelectedDrawables() const;
 bool canSelectedObjectsDoAction(ActionType,const Object*,SelectionRules,bool) const;
};
extern InGameUI *TheInGameUI;
bool InGameUI::canSelectedObjectsDoAction(ActionType action,const Object *target,SelectionRules rule,bool additionalChecking) const {
 const DrawableList *selected=TheInGameUI->getAllSelectedDrawables();
 int count=0;
 int qualify=0;
 Drawable *other;
 for(DrawableList::const_iterator it=selected->begin();it!=selected->end();++it) {
  other=*it;
  count++;
  bool success=false;
  switch(action) {
   case 0: return true;
   case 2: success=((Rva000C4D80Manager*)TheActionManager)->evaluate(other->getObject(),target,0); break;
   case 20: success=((ActionManager*)TheActionManager)->rvaC50C0DockPredicate(other->getObject(),target,0,true); break;
   case 3: success=((ActionManager*)TheActionManager)->rvaC50C0DockPredicate(other->getObject(),target,0,false); break;
   case 4: success=((BFMEActionManager*)TheActionManager)->rva000C46A0(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 5:
    success=((ActionManager*)TheActionManager)->canGetHealedAt(other->getObject(),target,CMD_FROM_PLAYER);
    if(success) { ContainModuleInterface *contain=target->m_contain; if(contain && contain->isHealContain()) success=false; }
    break;
   case 6: {
    ObjectID currentRepairer=target->getSoleHealingBenefactor();
    success=((ActionManager*)TheActionManager)->canRepairObject(other->getObject(),target,CMD_FROM_PLAYER);
    if(success && !other->isKindOf((KindOfType)15) && (currentRepairer==INVALID_ID || currentRepairer==other->getObject()->m_id)) success=false;
    break;
   }
   case 15: success=((BFMEActionManager*)TheActionManager)->canEnterObject(other->getObject(),target,CMD_FROM_PLAYER,COMBATDROP_INTO,0); break;
   case 8: {
    bool special;
    success=((BFMEActionManager*)TheActionManager)->canEnterObject(other->getObject(),target,CMD_FROM_PLAYER,additionalChecking?CHECK_CAPACITY:DONT_CHECK_CAPACITY,&special);
    if(success && special) success=false;
    break;
   }
   case 9: {
    bool special;
    success=((BFMEActionManager*)TheActionManager)->canEnterObject(other->getObject(),target,CMD_FROM_PLAYER,additionalChecking?CHECK_CAPACITY:DONT_CHECK_CAPACITY,&special);
    if(success && !special) success=false;
    break;
   }
   case 1: return false;
   case 10: success=((ActionManager*)TheActionManager)->canHijackVehicle(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 11: success=((ActionManager*)TheActionManager)->canConvertObjectToCarBomb(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 16: success=((BFMEActionManager*)TheActionManager)->rva000C4080(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 12: success=((ActionManager*)TheActionManager)->canCaptureBuilding(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 17: success=((BFMEActionManager*)TheActionManager)->rva000C6820(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 13: success=((Rva000C41C0ActionManager*)TheActionManager)->canMakeObjectDefector(other->getObject(),target,CMD_FROM_PLAYER); break;
   case 18: success=((ActionManager*)TheActionManager)->queryRva000C5EF0(other->getObject(),const_cast<Object*>(target),0); break;
   case 14: {
    Object *obj=other->getObject();
    if(!obj) {success=false;break;}
    ContainModuleInterface *contain=target?target->m_contain:0;
    ExitInterface *exit=obj->getObjectExitInterface();
    if(contain && exit && contain->rva00447A40Slot10() && exit->rva00447A40Slot6()) success=true; else success=(obj->isKindOf((KindOfType)68) && obj->isLocallyControlled());
    break;
   }
   case 19: success=((BFMEActionManager*)TheActionManager)->rva000C4390(other->getObject(),target,CMD_FROM_PLAYER); break;
  }
  if(success) { if(rule==SELECTION_ANY) return true; ++qualify; }
 }
 if(rule==SELECTION_ALL && count>0 && qualify==count) return true;
 return false;
}
