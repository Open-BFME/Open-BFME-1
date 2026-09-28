// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// Retail RVA 0x00582A10: BannerUI movie callback (478 bytes).
// Installed through ILT 0x00020194 by the movie selector at RVA 0x00583190.
// The semantic callback name is unproved, so its address remains in the name.
// Retail reads the second stack argument as a byte and returns with bare ret.
// Layout views below model only witnessed loads: BannerUI +30/+34 is the
// 28-byte movie vector; entry +0/+4/+8/+C and pointed record +8/+C are used.
// Display +34 is tested then dispatched through video slot +20. Other virtual
// contracts are witnessed at callback +BE (+E4, four arguments), +10D (+F0),
// +E9/+197 (message +34), and +171 (script +88, AsciiString reference).
// All direct calls use existing matched functions; no new callee pins.
#include "ascii_string.h"
#include <algorithm>
#include "message_stream.h"
struct MovieRecord00582A10 { char at00[8]; AsciiString at08; int at0c; };
struct BannerMovieEntry { bool at00; char pad01[3]; int m_id; int at08; MovieRecord00582A10* at0c; char at10[12]; };
class BannerMovieEntryMatches {
public:
 BannerMovieEntryMatches(int id): m_id(id) {}
 bool operator()(const BannerMovieEntry& entry) const { return entry.m_id==m_id; }
private: int m_id;
};
class BannerUI {
public:
 void removeMovieBanner(int id);
 void removeCurrentBannerMovie();
};
struct BannerMovies00582A10 { char at00[0x30]; BannerMovieEntry* begin; BannerMovieEntry* end; };
class Display;
class GlobalData;
class GameLODManager;
class ScriptEngine;
class MessageStream;
extern Display* TheDisplay;
extern GlobalData* TheWritableGlobalData;
extern GameLODManager* TheGameLODManager;
extern ScriptEngine* TheScriptEngine;
extern MessageStream* TheMessageStream;
extern BannerUI* TheBannerUI;
extern int TheCurrentBannerMovie;
class Video00582A10 {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual int position();
};
class Display {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
 virtual bool movie00582A10(AsciiString name,int flags,int a,int b);
 virtual void slot58();
 virtual void slot59();
 virtual bool isMoviePlaying();
 void rva002ED2E0(float,float,float,float);
 char at04[0x30]; Video00582A10* at34;
};
class MessageStream { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual GameMessage* appendMessage(int type);
};
class ScriptEngine { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
 virtual void notify00582A10(const AsciiString&);
};
struct Lod00582A10 { char at00[0x16c4]; int at16c4; int getLevel() const { return at16c4; } };
struct Global00582A10 { char at00[0xa7d]; bool atA7d; };
int movieCallback00582A10(int unused, bool starting) {
 int result=1;
 BannerMovies00582A10* movies=(BannerMovies00582A10*)TheBannerUI;
 BannerMovieEntry* entry=std::find_if(movies->begin,movies->end,BannerMovieEntryMatches(TheCurrentBannerMovie));
 if(entry==movies->end) entry=0;
 if(!entry) return 3;
 if(starting) {
  TheDisplay->rva002ED2E0(0,0,1,1);
  if(!TheGameLODManager || ((Lod00582A10*)TheGameLODManager)->getLevel()>1) {
   const AsciiString& name=entry->at0c->at08; if(!TheDisplay->movie00582A10(name,64,-1,-1)) {
    result=2;
    TheBannerUI->removeCurrentBannerMovie();
    { GameMessage* message=TheMessageStream->appendMessage(0x45e); message->appendIntegerArgument(entry->at08); }
   }
  }
 } else {
  if(!TheDisplay->isMoviePlaying() ||
     (TheDisplay->at34 ? TheDisplay->at34->position() : -1)>=entry->at0c->at0c ||
     ((Global00582A10*)TheWritableGlobalData)->atA7d) {
   if(entry->at00) { AsciiString label("Reinforcements"); TheScriptEngine->notify00582A10(label); }
   else { GameMessage* message=TheMessageStream->appendMessage(0x45e); message->appendIntegerArgument(entry->at08); }
   result=2;
   if(TheCurrentBannerMovie!=-1) {
    int id=TheCurrentBannerMovie;
    TheCurrentBannerMovie=-1;
    TheBannerUI->removeMovieBanner(id);
   }
  }
 }
 return result;
}

