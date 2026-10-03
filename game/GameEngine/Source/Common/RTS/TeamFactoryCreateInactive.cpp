// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
#include "StringInline.h"
#include "Common/Errors.h"
// BFME storage views: the ZH Team.h uses one-name factory methods and
// incompatible Team/TeamPrototype layouts. Existing matched TeamConstructor.cpp
// and TeamFactoryCreate.cpp prove this 0x110 allocation and constructor ABI.
// Reuse the canonical string and ErrorCode headers; no copied definitions.
class TeamPrototype;
class Team { char rva000f7790_storage[0x110]; public: Team(TeamPrototype *, unsigned int); };
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
// Only witnessed slots/arguments are asserted. ZH ScriptEngine has different
// signatures and the local script_engine.h only exposes init/template storage.
// The two BFME slots also occur in matched AIPlayerBuildSpecificAITeam.cpp.
class Rva000F7AB0Dispatch {
public:
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
virtual void slot25(AsciiString *, void *, Team *);
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
virtual void *slot53(const AsciiString *, const AsciiString *, AsciiString *);
};
class TeamFactory {
 char rva000f7ab0_prefix[0x1c];
 unsigned int m_uniqueTeamID;
public:
 TeamPrototype *findTeamPrototype(const AsciiString &,const AsciiString &);
 Team *createInactiveTeam(const AsciiString &,const AsciiString &);
};
// ZH Team.cpp createInactiveTeam twin, plus BFME's second string key and
// output-name argument. Evidence: identity_evidence/000f7ab0-native-factory.md.
Team *TeamFactory::createInactiveTeam(const AsciiString &owner,const AsciiString &name) {
 TeamPrototype *tp=findTeamPrototype(owner,name);
 if(!tp) throw ERROR_BAD_ARG;
 Team *t=0;
 if(*(const unsigned char *)((char *)tp+0x18)&1) {
  t=*(Team **)((char *)tp+0x274);
  if(t) {
   if(*(const bool *)((char *)tp+0x1ec)) {
    AsciiString out;
    void *script=((Rva000F7AB0Dispatch *)TheScriptEngine)->slot53((const AsciiString *)((char *)tp+0x10),(const AsciiString *)((char *)tp+0x1e8),&out);
    if(script) ((Rva000F7AB0Dispatch *)TheScriptEngine)->slot25(&out,*(void **)((char *)script+0x20),0);
   }
   return t;
  }
 }
 t=new Team(tp,++m_uniqueTeamID);
 if(*(const bool *)((char *)tp+0x1ec)) {
  AsciiString out;
  void *script=((Rva000F7AB0Dispatch *)TheScriptEngine)->slot53((const AsciiString *)((char *)tp+0x10),(const AsciiString *)((char *)tp+0x1e8),&out);
  if(script) ((Rva000F7AB0Dispatch *)TheScriptEngine)->slot25(&out,*(void **)((char *)script+0x20),0);
 }
 return t;
}
