// InGameUI slot90 in tableVA10F5B38 routes through ILT3DC76 to RVA4481C0.
// Matched caller rva00448700 and retail 25-callee structure corroborate identity.
// Exact 1066 instruction bytes; strict dependencies documented in astra_T/REPORT.md.
// Thing::isKindOf below independently reproduces its existing 64-byte retail body.
// The native Override.h wrapper and visible noinline read-only kind query are essential.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <set>
#include <list>
struct IRegion2D;
class Object; class Drawable; class ThingTemplate; class HordeContain;
class Overridable { public: const Overridable *getFinalOverride() const { if(at04) return at04->getFinalOverride(); return this; } void *vptr; Overridable *at04; };
#define _OVERRIDABLE_H_
#include "Common/Override.h"
class ThingTemplate : public Overridable { public: unsigned char pad08[0xd4-8]; unsigned int atD4; };
enum KindOfType { Rva00448337Kind=90 };
class Thing { public: unsigned char at00[4]; OVERRIDE<ThingTemplate> at04; __declspec(noinline) bool isKindOf(KindOfType) const; const ThingTemplate *getTemplate() const { return at04; } };
class Rva004482E4Contain { public:
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
virtual HordeContain *rva004482E4();
};
class HordeContain { public:
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
virtual void rva0044831A(std::list<Object*>*);
};
class Object : public Thing { public:
 unsigned char at08[0x74-8]; unsigned int at74;
 unsigned char at78[0x1fc-0x78]; Rva004482E4Contain *at1FC;
 bool isLocallyControlled() const;
};
class Drawable { public: unsigned char at00[0xfc]; Object *atFC; void *at100; Drawable *at104; };
typedef std::list<Drawable*> DrawableList;
struct Rva00442AB0Target;
typedef std::set<Rva00442AB0Target*> TemplateSet;
struct Rva00443F60Data { const ThingTemplate *at00; DrawableList at04; bool at08; };
extern bool rva00443F60(Drawable*,void*);
class View { public:
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
virtual int iterateDrawablesInRegion(IRegion2D*,bool (*)(Drawable*,void*),void*);
};
class GameClient { public:
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
virtual Drawable *firstDrawable();
};
class GameMessage { public: void appendBooleanArgument(bool); void appendObjectIDArgument(unsigned int); };
class MessageStream { public:
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
virtual GameMessage *appendMessage(int);
};
extern View *TheTacticalView; extern GameClient *TheGameClient; extern MessageStream *TheMessageStream;
class InGameUI { public:
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
virtual void rvaSlot60();
virtual void rvaSlot61();
virtual void rvaSlot62();
virtual const DrawableList *getAllSelectedDrawables() const;
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
virtual int selectMatchingAcrossRegion(IRegion2D*);
virtual void rvaSlot91();
virtual void rvaSlot92();
virtual void setDisplayedMaxWarning(bool);
};

bool Thing::isKindOf(KindOfType t) const { const ThingTemplate *tmpl=getTemplate(); return (((const unsigned int*)((const char*)tmpl+0xc8))[(unsigned)t>>5] & (1 << ((unsigned)t&31))) != 0; }

int InGameUI::selectMatchingAcrossRegion(IRegion2D *region)
{
 const DrawableList *selected=getAllSelectedDrawables();
 const Drawable *draw;
 TemplateSet templates;
 TemplateSet memberTemplates;
 for(DrawableList::const_iterator it=selected->begin();it!=selected->end();++it) {
  draw=*it;
  Object *object = draw ? draw->atFC : 0;
  if(object && object->isLocallyControlled()) {
   templates.insert((Rva00442AB0Target*)object->getTemplate());
   if(object->getTemplate()->atD4 & 0x1000) {
    Rva004482E4Contain *contain=object->at1FC;
    if(contain) {
     HordeContain *horde=contain->rva004482E4();
     if(horde) {
      std::list<Object*> members;
      horde->rva0044831A(&members);
      for(std::list<Object*>::const_iterator j=members.begin();j!=members.end();++j) {
       Object *member=*j;
       if(member && !member->isKindOf(Rva00448337Kind)) memberTemplates.insert((Rva00442AB0Target*)member->getTemplate());
      }
     }
    }
   }
  }
 }
 if(templates.size()==0 && memberTemplates.size()==0) return -1;
 TemplateSet::iterator iter;
 const ThingTemplate *templateName;
 Rva00443F60Data data;
 int count=0;
 for(iter=templates.begin();iter!=templates.end();++iter) {
  templateName=(const ThingTemplate*)*iter;data.at00=templateName;data.at08=false;
  if(region) count+=TheTacticalView->iterateDrawablesInRegion(region,rva00443F60,&data);
  else { Drawable *temp=TheGameClient->firstDrawable(); while(temp) {count+=rva00443F60(temp,&data);temp=temp->at104;} }
  setDisplayedMaxWarning(false);
 }
 for(iter=memberTemplates.begin();iter!=memberTemplates.end();++iter) {
  templateName=(const ThingTemplate*)*iter;data.at00=templateName;data.at08=true;
  if(region) count+=TheTacticalView->iterateDrawablesInRegion(region,rva00443F60,&data);
  else { Drawable *temp=TheGameClient->firstDrawable(); while(temp) {count+=rva00443F60(temp,&data);temp=temp->at104;} }
  setDisplayedMaxWarning(false);
 }
 if(count>0) {
  GameMessage *message=TheMessageStream->appendMessage(1002);
  message->appendBooleanArgument(false);
  for(DrawableList::const_iterator it=data.at04.begin();it!=data.at04.end();++it) {
   draw=*it;
   if(draw && draw->atFC) message->appendObjectIDArgument(draw->atFC->at74);
  }
 }
 return count;
}
