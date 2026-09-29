// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic
// BFME retail 1.03 RVA 0x000C47F0 (275 bytes, switch tables follow at +0x114).
// Identity: ZH ActionManager::canDoSpecialPower twin, callers AIGroup::groupDoSpecialPower and ControlBar::isValidToUseOn.
// Adapted from EA Generals Zero Hour ActionManager.cpp (GPL-3.0-or-later).
// BFME-specific passenger, horde and power cases follow the retail branches.
// Opaque interface slots and unverified fields retain address-derived names.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "command_source_type.h"
class Pathfinder;
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x;y=v.y;z=v.z; }
enum Relationship {};
enum KindOfType {};
enum SpecialPowerType {};
enum NameKeyType {};
enum ObjectShroudStatus {OBJECTSHROUD_FOGGED=3};
class Object; class SpecialPowerTemplate;
class Overridable { public:
 virtual ~Overridable();
 Overridable *m_nextOverride; bool rva08;
 Overridable *friend_getFinalOverride() {if(m_nextOverride)return m_nextOverride->friend_getFinalOverride();return this;}
 const Overridable *friend_getFinalOverride() const {if(m_nextOverride) return m_nextOverride->friend_getFinalOverride();return this;}
};
class SpecialPowerTemplate:public Overridable { public:
 char rva0c[8]; SpecialPowerType m_type;
 SpecialPowerType getSpecialPowerType() const {return ((const SpecialPowerTemplate*)friend_getFinalOverride())->m_type;}
};
class Player {public: char pad00[0x24]; int m_playerIndex; char pad28[4]; int rva2c; int getPlayerIndex()const{return m_playerIndex;} };
class ThingTemplate { public: char pad00[0x48b]; bool rva48b; };
class Thing { public: bool isKindOf(KindOfType) const; const ThingTemplate *getTemplate() const; };
class Rva000C5FF0List {public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual Object *first(int,int,int);
};
class Rva000C5FF0Contain {public:
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00C();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01C();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02C();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03C();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04C();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05C();
 virtual void slot060();
 virtual void slot064();
 virtual Rva000C5FF0List *list() const;
 virtual void slot06C();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07C();
 virtual void slot080();
 virtual bool allow(const Object*,bool);
 virtual void slot088();
 virtual void slot08C();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09C();
 virtual void slot0A0();
 virtual void slot0A4();
 virtual void slot0A8();
 virtual void slot0AC();
 virtual void slot0B0();
 virtual void slot0B4();
 virtual void slot0B8();
 virtual void slot0BC();
 virtual void slot0C0();
 virtual void slot0C4();
 virtual void slot0C8();
 virtual void slot0CC();
 virtual void slot0D0();
 virtual void slot0D4();
 virtual void slot0D8();
 virtual void slot0DC();
 virtual void slot0E0();
 virtual void slot0E4();
 virtual void slot0E8();
 virtual void slot0EC();
 virtual void slot0F0();
 virtual void slot0F4();
 virtual void slot0F8();
 virtual void slot0FC();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10C();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11C();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12C();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13C();
 virtual void slot140();
 virtual void slot144();
 virtual void slot148();
 virtual void slot14C();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual bool slot15c(const Object*,bool);
};
class SpecialPowerModuleInterface {public:
 virtual void slot00();
 virtual void slot04();
 virtual float getPercentReady();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual bool slot58(int);
};
class Rva000C5FF0ModuleData {public: char pad00[0x214];bool rva214;};
class Module {public: char pad00[4]; Rva000C5FF0ModuleData *rva04;};
class Rva000C5FF0AIUpdate {public:bool query();};
class Object : public Thing {public:
 char pad00[0x38];Coord3D rva38;
 char pad44[0x74-0x44];int m_id;
 char pad78[0x90-0x78];_STL::bitset<86> m_status;
 char pad9c[0x1fc-0x9c];Rva000C5FF0Contain *m_contain;
 char pad200[4];Rva000C5FF0AIUpdate *rva204;
 char pad208[0x214-0x208];Object *rva214;
 char pad218[0x344-0x218];unsigned char m_privateStatus;
 bool hasSpecialPower(SpecialPowerType) const;
 Relationship getRelationship(const Object*)const;
 SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate*)const;
 Player *getControllingPlayer()const;
 ObjectShroudStatus getShroudedStatus(int)const;
 Module *findModule(NameKeyType)const;
};
class BFMEActionObject {public:bool testStatus(int)const;};

struct Rva000C5FF0AI {char pad00[0xc];Pathfinder *rva0c; Pathfinder *pathfinder(){return rva0c;}};
extern Rva000C5FF0AI *rva000C5FF0_ai;
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_0000142e();
// ILT 0x0001A95B routes to verified Pathfinder::getLayer (0x003D93A0).
// Its struct-tag signature differs from the shared Coord3D class tag.
extern void j_0001a95b();
class ThiscallReceiverView {};
template<class T> __forceinline T member(void(*raw)()) {union{void(*raw)();T ptr;}f;f.raw=raw;return f.ptr;}
typedef bool(ThiscallReceiverView::*BoolQuery)();
typedef int(ThiscallReceiverView::*LayerQuery)(const Coord3D*);
#define CALL(T,obj,fn) (((ThiscallReceiverView*)(obj))->*member<T>(fn))
class ActionManager {public:
 bool canDoSpecialPower(const Object*,const SpecialPowerTemplate*,CommandSourceType,unsigned int,bool);
};
bool ActionManager::canDoSpecialPower(const Object *obj,const SpecialPowerTemplate *spTemplate,CommandSourceType commandSource,unsigned int commandOptions,bool checkSourceRequirements)
{
 if(!spTemplate)return false;
 if(checkSourceRequirements && !obj->hasSpecialPower(spTemplate->getSpecialPowerType()))return false;
 if(obj && obj->rva204 && CALL(BoolQuery,obj->rva204,j_0000142e)()) {
  Coord3D pos=obj->rva38;
  pos.z+=500.0f;
  if(rva000C5FF0_ai && CALL(LayerQuery,rva000C5FF0_ai->pathfinder(),j_0001a95b)(&pos)>=17)return false;
 }
 SpecialPowerModuleInterface *mod=obj->getSpecialPowerModule(spTemplate);
 if(mod) {
  if(checkSourceRequirements) {
   if(mod->getPercentReady()<1.0f)return false;
   if(!mod->slot58(0))return false;
  }
  switch(spTemplate->getSpecialPowerType()) {
  case 1:
  case 2:
  case 8:
  case 11:
  case 13:
  case 14:
  case 15:
  case 16:
  case 18:
  case 20:
  case 21:
  case 23:
  case 25:
  case 28:
  case 30:
  case 31:
  case 32:
  case 33:
  case 34:
  case 35:
  case 38:
  case 43:
  case 48:
  case 49:
  case 50:
  case 51:
  case 52:
  case 58:
  case 60:
  case 64:
  case 65:
  case 66:
  case 68:
  case 69:
  case 70:
  case 71:
  case 72:
  case 74:
  case 78:
  case 81:
  case 85:
  case 88:
  case 89:
  case 91:
  case 93:
  case 94:
  case 96:
  case 97:
  case 99:
  case 100:
  case 103:
  case 106:
  case 108:
  case 112:
  case 114:
   return false;
  case 19:
  case 22:
  case 27:
  case 36:
  case 37:
  case 39:
  case 40:
  case 41:
  case 42:
  case 44:
  case 45:
  case 47:
  case 53:
  case 54:
  case 55:
  case 56:
  case 57:
  case 59:
  case 61:
  case 62:
  case 63:
  case 67:
  case 73:
  case 75:
  case 76:
  case 77:
  case 79:
  case 80:
  case 82:
  case 83:
  case 84:
  case 86:
  case 87:
  case 90:
  case 92:
  case 95:
  case 98:
  case 101:
  case 102:
  case 105:
  case 107:
  case 109:
  case 110:
  case 111:
  case 115:
   return true;
  }
 }
 return false;
}
