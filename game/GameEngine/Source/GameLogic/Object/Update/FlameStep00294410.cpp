// Retail RVA 0x00294410, 1163 bytes. The entry receives the secondary
// update-interface base, 0x10 bytes after the primary module pointer.
// FlammableUpdate calls and EntEnragedUpdate literal establish the behavior;
// the entry name and unwitnessed fields retain their address-derived identity.
// Inline primary-base and AI accessors preserve retail register lifetimes.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
struct Coord3D { float x,y,z; void set(float a,float b,float c) { x=a;y=b;z=c; } };
class ModelConditionFlags { public: bool test(int n) const { return bits.test(n); } void reset(int n) { bits.reset(n); } void set(int n) { bits.set(n); } _STL::bitset<320> bits; };
#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
enum NameKeyType { KEY_NONE=0 };
enum ObjectStatusTypes { STATUS10=10 };
class Module;
#define OBJECT_TU_MEMBERS Module* findModule(NameKeyType) const; void setStatusBit(int,bool); void clearStatus(ObjectStatusTypes); void notifyModelConditionChanged(); AIUpdateInterface* getAI00294410() const { return m_ai; }
#include "../object.h"
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
class GameLogic { public: void deselectObject(Object*,unsigned short,bool); char pad00[0x3c]; unsigned frame; };
extern GameLogic* TheGameLogic;

enum CommandSourceType { COMMAND1=1 };
class AICommandInterface { public: void aiMoveToPosition(const Coord3D*,CommandSourceType); };
class AiSlots00294410 { public: virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void set(int); char pad04[0x333]; bool at337; };
class AIUpdateInterface : public AiSlots00294410 { public: bool bfmeBlocksFormationRefresh(); void setFlag00294410(bool value) { at337=value; } };
class Terrain00294410 { public: virtual void slot00();
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
    virtual bool water(float,float,int,int);
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual float height(float,float); };
class Audio00294410 { public: virtual void slot00();
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
    virtual void remove(int); };
class Body00294410 { public: virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void notify(); };
extern Terrain00294410* g_terrain00294410;
class AudioManager;
extern AudioManager *TheAudio;
struct FlamePrimary00294410 { char pad00[0x34]; int at34; void stopSound() { if(at34) { ((Audio00294410*)TheAudio)->remove(at34); at34=0; } } };
class BfmeE1081;
class BfmeD1081 { public: char bfmeDo1081(BfmeE1081*,char*,char*,int); };
struct PathSystem00294410 { char pad00[12]; BfmeD1081* at0c; BfmeD1081* getPathfinder() { return at0c; } };
// 0x012EF214 is retail's TheAI singleton (`AI *TheAI`, mangled
// ?TheAI@@3PAVAI@@A), defined in GameLogic/AI/ai.cpp. PathSystem00294410
// stays as this TU's offset view of it.
class AI;
extern AI *TheAI;
class BfmeMarksYE { public: void bfmeSetYE(unsigned char,unsigned char); };
class Rva002918E0Object { public: void set(unsigned char); };
enum UpdateSleepTime { SLEEP1=1 };
class FlammableUpdate { public: void doAflameDamage(); UpdateSleepTime bfmeCalcSleepTimeGate(); };
class FlameCleanup00293E50 { public: void apply(); };
struct Config00294410 { char pad00[0x10]; unsigned at10; char pad14[0x21]; bool at35; char pad36[2]; float at38,at3c,at40; bool at44; };
inline const unsigned& minimum00294410(const unsigned& a,const unsigned& b) { return a<b?a:b; }
class FlameStep00294410 {
public: int update();
 Config00294410* config() { return *(Config00294410**)((char*)this-12); }
 Object* object() { return *(Object**)((char*)this-8); }
 FlammableUpdate* primary() { return (FlammableUpdate*)((char*)this-16); }
 char pad00[0x14]; unsigned at14,at18,at1c,at20; int at24; char pad28[8]; bool at30; char pad31[3]; unsigned at34; int at38; bool at3c;
};
int FlameStep00294410::update() {
 unsigned now=TheGameLogic->frame;
 Config00294410* data=config();
 Object* obj=object();
 if(at34>0) {
  if(now>=at34) {
   at34=0;
   if(data->at35) {
    const Coord3D* pos=&obj->m_cachedPos;
    Coord3D best={10000000.0f,10000000.0f,10000000.0f};
    AIUpdateInterface* ai=obj->m_ai;
    if(ai) {
     float radius=data->at3c;
     float step=data->at40;
     for(int x=(int)(pos->x-radius);x<=pos->x+radius;x+=step) {
      for(int y=(int)(pos->y-radius);y<=pos->y+radius;y+=step) {
       if(g_terrain00294410->height((float)x,(float)y)>config()->at38) {
        Coord3D candidate; candidate.set((float)x,(float)y,pos->z);
        float dx=pos->x-candidate.x,dy=pos->y-candidate.y;
        float bx=pos->x-best.x,by=pos->y-best.y;
        if(dx*dx+dy*dy<bx*bx+by*by && ((PathSystem00294410*)TheAI)->getPathfinder()->bfmeDo1081((BfmeE1081*)obj,(char*)pos,(char*)&candidate,0)) best=candidate;
       }
      }
     }
     static NameKeyType key=TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
     Module* enraged=obj->findModule(key);
     if(g_terrain00294410->water(best.x,best.y,0,0)) {
      if(data->at44 && obj->m_ai) {
       obj->getAI00294410()->set(4);
       obj->m_ai->at337=true;
       at3c=true;
      }
      ((AICommandInterface*)((char*)ai+0x20))->aiMoveToPosition(&best,COMMAND1);
      at30=true;
      TheGameLogic->deselectObject(obj,0xffff,true);
      obj->setStatusBit(3,true); obj->setStatusBit(5,true);
      if(enraged) { ((Rva002918E0Object*)enraged)->set(1); return 1; }
     } else if(enraged) ((BfmeMarksYE*)enraged)->bfmeSetYE(1,0);
    }
   }
  }
  return 1;
 }
 if(obj->m_ai && !obj->m_ai->bfmeBlocksFormationRefresh() && g_terrain00294410->water(obj->m_cachedPos.x,obj->m_cachedPos.y,0,0)) {
  unsigned end=TheGameLogic->frame+15;
  at18=minimum00294410(at18,end);
  at30=false;
 }
 if(at20 && now>=at20) { at20=data->at10+now; primary()->doAflameDamage(); }
 if(at1c && now>=at1c) {
  obj->setStatusBit(11,true);
  if(!obj->m_modelConditionFlags.test(79)) { obj->m_modelConditionFlags.set(79); obj->notifyModelConditionChanged(); }
 }
 if(at18 && now>=at18) {
  at14=(obj->m_status[0]>>10)&2;
  ((FlameCleanup00293E50*)primary())->apply();
  ((FlamePrimary00294410*)primary())->stopSound();
  obj->clearStatus(STATUS10);
  if(obj->m_modelConditionFlags.test(77)) { obj->m_modelConditionFlags.reset(77); obj->notifyModelConditionChanged(); }
  if(data->at44 && at3c && obj->m_ai) { obj->m_ai->setFlag00294410(false); obj->getAI00294410()->set(0); at3c=false; }
  ((Body00294410*)obj->m_body)->notify();
 }
 return primary()->bfmeCalcSleepTimeGate();
}


