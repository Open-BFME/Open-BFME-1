// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// Two-argument cdecl callback used at 0x00448456 and 0x004484E6, and passed
// to the view iterator at 0x0044842D / 0x004484BE. The supplied historical
// SelectionTranslator::selectFriends identity is incompatible with this ABI.
// It resembles ZH InGameUI.cpp's similarUnitSelection, with BFME producer and
// horde-member checks, but retains an opaque name until identity is proved.
// Capstone decodes 794 bytes: final RET at 0x00444279, INT3 at 0x0044427A.
// Native list lifetimes and a local containment pointer reproduce the frame
// and register allocation. Slot26 obtains the horde view; slot60 fills a
// list of Object pointers. Unwinding releases the list before UI selection.
#include <list>
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const UnicodeString& that) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&that); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
template<class T> inline const T *StringBase<T>::str() const { static const T TheNullChr=0;return m_data?m_data->data:&TheNullChr; }
class Object; class Drawable; class ThingTemplate;
enum KindOfType { Rva00443F60Kind108=108 };
enum ObjectID { INVALID_ID=0 };
class Overridable { public: const Overridable *getFinalOverride()const { if(at04) return at04->getFinalOverride();return this; } void *vptr; Overridable *at04; };
#define _OVERRIDABLE_H_
#include "Common/Override.h"
class ThingTemplate:public Overridable { public: bool isEquivalentTo(const ThingTemplate*) const; bool isKindOf(KindOfType)const; };
class Thing {
public:
virtual void rvaSlot00();
virtual void rvaSlot01();
virtual void rvaSlot02();
virtual void rvaSlot03();
virtual void rvaSlot04();
virtual void rvaSlot05();
virtual void rvaSlot06();
virtual void rvaSlot07();
virtual void rvaSlot08();
virtual void rvaSlot09();
virtual Drawable *getDrawable() const;
OVERRIDE<ThingTemplate> at04;
const ThingTemplate *getTemplate()const {return at04;}
bool isKindOf(KindOfType) const;
};
class Rva00443F60Horde;
class Rva00443F60Contain { public:
virtual void rvaSlot00();
virtual void rvaSlot01();
virtual void rvaSlot02();
virtual void rvaSlot03();
virtual void rvaSlot04();
virtual void rvaSlot05();
virtual void rvaSlot06();
virtual void rvaSlot07();
virtual void rvaSlot08();
virtual void rvaSlot09();
virtual void rvaSlot10();
virtual void rvaSlot11();
virtual void rvaSlot12();
virtual void rvaSlot13();
virtual void rvaSlot14();
virtual void rvaSlot15();
virtual void rvaSlot16();
virtual void rvaSlot17();
virtual void rvaSlot18();
virtual void rvaSlot19();
virtual void rvaSlot20();
virtual void rvaSlot21();
virtual void rvaSlot22();
virtual void rvaSlot23();
virtual void rvaSlot24();
virtual void rvaSlot25();
virtual Rva00443F60Horde *rvaSlot26();
};
class Rva00443F60Horde { public:
virtual void rvaSlot00();
virtual void rvaSlot01();
virtual void rvaSlot02();
virtual void rvaSlot03();
virtual void rvaSlot04();
virtual void rvaSlot05();
virtual void rvaSlot06();
virtual void rvaSlot07();
virtual void rvaSlot08();
virtual void rvaSlot09();
virtual void rvaSlot10();
virtual void rvaSlot11();
virtual void rvaSlot12();
virtual void rvaSlot13();
virtual void rvaSlot14();
virtual void rvaSlot15();
virtual void rvaSlot16();
virtual void rvaSlot17();
virtual void rvaSlot18();
virtual void rvaSlot19();
virtual void rvaSlot20();
virtual void rvaSlot21();
virtual void rvaSlot22();
virtual void rvaSlot23();
virtual void rvaSlot24();
virtual void rvaSlot25();
virtual void rvaSlot26();
virtual void rvaSlot27();
virtual void rvaSlot28();
virtual void rvaSlot29();
virtual void rvaSlot30();
virtual void rvaSlot31();
virtual void rvaSlot32();
virtual void rvaSlot33();
virtual void rvaSlot34();
virtual void rvaSlot35();
virtual void rvaSlot36();
virtual void rvaSlot37();
virtual void rvaSlot38();
virtual void rvaSlot39();
virtual void rvaSlot40();
virtual void rvaSlot41();
virtual void rvaSlot42();
virtual void rvaSlot43();
virtual void rvaSlot44();
virtual void rvaSlot45();
virtual void rvaSlot46();
virtual void rvaSlot47();
virtual void rvaSlot48();
virtual void rvaSlot49();
virtual void rvaSlot50();
virtual void rvaSlot51();
virtual void rvaSlot52();
virtual void rvaSlot53();
virtual void rvaSlot54();
virtual void rvaSlot55();
virtual void rvaSlot56();
virtual void rvaSlot57();
virtual void rvaSlot58();
virtual void rvaSlot59();
virtual void rvaSlot60(std::list<Object*>*);
};
class Object:public Thing {public:
unsigned char pad08[0x78-8]; ObjectID m_producerID;
unsigned char pad7C[0x1fc-0x7c]; Rva00443F60Contain *at1FC;
unsigned char pad200[0x214-0x200]; void *at214;
bool testStatus(int) const;
bool isLocallyControlled() const;
bool queryRva001C9980();
};
class Drawable {public: unsigned char pad00[0xfc];Object *atFC; unsigned char pad100[0x3ac-0x100];bool at3AC;};
class GameLogic {public: Object *findObjectByID(ObjectID);};
extern GameLogic *TheGameLogic;
class InGameUI {public:
virtual void rvaSlot00();
virtual void rvaSlot01();
virtual void rvaSlot02();
virtual void rvaSlot03();
virtual void rvaSlot04();
virtual void rvaSlot05();
virtual void rvaSlot06();
virtual void rvaSlot07();
virtual void rvaSlot08();
virtual void rvaSlot09();
virtual void rvaSlot10();
virtual void rvaSlot11();
virtual void rvaSlot12();
virtual void __cdecl message(UnicodeString,...);
virtual void rvaSlot14();
virtual void rvaSlot15();
virtual void rvaSlot16();
virtual void rvaSlot17();
virtual void rvaSlot18();
virtual void rvaSlot19();
virtual void rvaSlot20();
virtual void rvaSlot21();
virtual void rvaSlot22();
virtual void rvaSlot23();
virtual void rvaSlot24();
virtual void rvaSlot25();
virtual void rvaSlot26();
virtual void rvaSlot27();
virtual void rvaSlot28();
virtual void rvaSlot29();
virtual void rvaSlot30();
virtual void rvaSlot31();
virtual void rvaSlot32();
virtual void rvaSlot33();
virtual void rvaSlot34();
virtual void rvaSlot35();
virtual void rvaSlot36();
virtual void rvaSlot37();
virtual void rvaSlot38();
virtual void rvaSlot39();
virtual void rvaSlot40();
virtual void rvaSlot41();
virtual void rvaSlot42();
virtual void rvaSlot43();
virtual void rvaSlot44();
virtual void rvaSlot45();
virtual void rvaSlot46();
virtual void rvaSlot47();
virtual void rvaSlot48();
virtual void rvaSlot49();
virtual void rvaSlot50();
virtual void rvaSlot51();
virtual void rvaSlot52();
virtual void rvaSlot53();
virtual void rvaSlot54();
virtual void rvaSlot55();
virtual void selectDrawable(Drawable*);
virtual void rvaSlot57();
virtual void rvaSlot58();
virtual void rvaSlot59();
virtual int getSelectCount();
virtual int getMaxSelectCount();
virtual void rvaSlot62();
virtual void rvaSlot63();
virtual void rvaSlot64();
virtual void rvaSlot65();
virtual void rvaSlot66();
virtual void rvaSlot67();
virtual void rvaSlot68();
virtual void rvaSlot69();
virtual void rvaSlot70();
virtual void rvaSlot71();
virtual void rvaSlot72();
virtual void rvaSlot73();
virtual void rvaSlot74();
virtual void rvaSlot75();
virtual void rvaSlot76();
virtual void rvaSlot77();
virtual void rvaSlot78();
virtual void rvaSlot79();
virtual void rvaSlot80();
virtual void rvaSlot81();
virtual void rvaSlot82();
virtual void rvaSlot83();
virtual void rvaSlot84();
virtual void rvaSlot85();
virtual void rvaSlot86();
virtual void rvaSlot87();
virtual void rvaSlot88();
virtual void rvaSlot89();
virtual void rvaSlot90();
virtual void rvaSlot91();
virtual bool getDisplayedMaxWarning();
virtual void setDisplayedMaxWarning(bool);
};
extern InGameUI *TheInGameUI;
class GameTextInterface {public:
virtual void rvaSlot00();
virtual void rvaSlot01();
virtual void rvaSlot02();
virtual void rvaSlot03();
virtual void rvaSlot04();
virtual void rvaSlot05();
virtual void rvaSlot06();
virtual void rvaSlot07();
virtual void rvaSlot08();
virtual void rvaSlot09();
virtual UnicodeString fetch(const char*,bool * =0);
};
extern GameTextInterface *TheGameText;
struct Rva00443F60Data {const ThingTemplate *at00;std::list<Drawable*> at04; bool at08;};
bool rva00443F60(Drawable *test,void *userData)
{
 Rva00443F60Data *data=(Rva00443F60Data*)userData;
 const ThingTemplate *selectedType=data->at00;
 if(test) {
  const Object *object=test->atFC;
  if(!object) return false;
  if(object->m_producerID) {
   Object *parent=TheGameLogic->findObjectByID(object->m_producerID);
   if(parent && parent->isKindOf(Rva00443F60Kind108) && parent->testStatus(3)) return false;
  }
  bool isEquivalent=object->getTemplate()->isEquivalentTo(selectedType);
  if(!isEquivalent && !data->at08 && object->isKindOf(Rva00443F60Kind108) && !selectedType->isKindOf(Rva00443F60Kind108)) {
   Rva00443F60Contain *contain=object->at1FC;
   Rva00443F60Horde *horde=contain?contain->rvaSlot26():0;
   if(horde) {
    std::list<Object*> members;
    horde->rvaSlot60(&members);
    for(std::list<Object*>::iterator i=members.begin();i!=members.end();++i) {
     Object *member=*i;
     if(member && member->getTemplate() && member->getTemplate()->isEquivalentTo(selectedType)) {isEquivalent=true;break;}
    }
   }
  }
  if(isEquivalent && object->isLocallyControlled() && !object->at214 && !object->getDrawable()->at3AC && ((Object*)object)->queryRva001C9980()) {
   if(TheInGameUI->getMaxSelectCount()>0 && TheInGameUI->getSelectCount()>=TheInGameUI->getMaxSelectCount()) {
    if(!TheInGameUI->getDisplayedMaxWarning()) {
     TheInGameUI->setDisplayedMaxWarning(true);
     UnicodeString msg;
     msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(),TheInGameUI->getMaxSelectCount());
     TheInGameUI->message(msg);
    }
   } else {
    TheInGameUI->selectDrawable(test);
    TheInGameUI->setDisplayedMaxWarning(false);
    data->at04.push_back(test);
    return true;
   }
  }
 }
 return false;
}
