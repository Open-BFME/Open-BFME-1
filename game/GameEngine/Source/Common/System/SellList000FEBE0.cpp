// Retail 0x000FEBE0 / 748 B. Address-qualified sell-list processing body.
// Follows the ZH BuildAssistant sell-list flow but BFME refunds immediately,
// displays GUI:AddCash, reports the damage source, then kills or resets the object.
// No semantic method name is claimed: the established update method is separate.
// Canonical Object/Thing/Coord3D layout; list and hash lookup use STLport.
// RefundValue+0x47C and GlobalData sellPercentage+0xC30 are name_oracle witnesses.
// Object+0x258 and Player+0x1C4 remain unnamed raw fields.
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringinline /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <hash_map>
#include <list>
#include "StringInline.h"
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
class Player;
class ProductionUpdateInterface;
class Rva001CE3F0 { public: void apply(); };
enum DamageType { Damage000FEBE0 = 8 };
enum DeathType { Death000FEBE0 = 0 };
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; ProductionUpdateInterface *getProductionUpdateInterface(); bool bfmeGetRecentDamageSource(unsigned int *,unsigned int) const; void kill(DamageType, DeathType);
#include "object.h"
class Overridable { public:
    const Overridable *getFinalOverride() const;
    void *field00;
    Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable { public:
    char field08[0xc0];
    unsigned int fieldC8,fieldCC,fieldD0,fieldD4,fieldD8;
    char fieldDC[0x47c-0xdc];
    unsigned short m_refundValue;
};
inline const ThingTemplate *Thing::getTemplate() const {
    if(!m_template) return 0;
    const ThingTemplate *t=m_template;
    if(t->m_nextOverride) t=(const ThingTemplate*)t->m_nextOverride->getFinalOverride();
    return t;
}
class BodyModuleInterface { public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual float slot05();
    virtual void slot06();
    virtual void slot07();
    virtual int slot08();
};
inline float health000FEBE0(BodyModuleInterface *body) {
    float health=1.0f; if(body) health=body->slot05(); return health;
}
class ProductionUpdateInterface { public:
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
    virtual void cancelAndRefundAllProduction();
};
class GeometryInfo { public: float getMaxHeightAbovePosition() const; };
class Money { public: void deposit(unsigned int, bool); };
class Player { public:
    char field00[0x48];
    Money field48;
};
class GlobalData { public: char field00[0xc30]; float m_sellPercentage; };
extern GlobalData *TheGlobalData;
class GameTextInterface { public:
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
    virtual UnicodeString fetch(const char *, bool *);
};
extern GameTextInterface *TheGameText;
class InGameUI { public:
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
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94(const UnicodeString &, const Coord3D *, unsigned int);
};
extern InGameUI *TheInGameUI;
class BFMEReportDamageSource { public: void report(Object *, int); };
typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;
class GameLogic { public:
    Object *findObjectByID(int id);
    char field00[0xb0];
    ObjectPtrHash fieldB0;
};
Object *GameLogic::findObjectByID(int id) {
    if(id==0) return 0;
    ObjectPtrHash::iterator it=fieldB0.find(id);
    if(it==fieldB0.end()) return 0;
    return (*it).second;
}
extern GameLogic *TheGameLogic;
class ObjectSellInfo { public:
    virtual ~ObjectSellInfo();
    int m_id;
    unsigned int m_sellFrame;
};
typedef _STL::list<ObjectSellInfo *> ObjectSellList;
class SellList000FEBE0 { public:
    void process();
    char field00[0x10];
    ObjectSellList field10;
};
void SellList000FEBE0::process() {
    ObjectSellInfo *sellInfo;
    Object *obj;
    ObjectSellList::iterator it, thisIterator;
    for(it=field10.begin();it!=field10.end();) {
        sellInfo=*it;
        thisIterator=it;
        ++it;
        obj=TheGameLogic->findObjectByID(sellInfo->m_id);
        if(!obj) {
            delete sellInfo;
            field10.erase(thisIterator);
            continue;
        }
        Player *player=obj->getControllingPlayer();
        if(player) {
            unsigned int sellValue;
            if(obj->getTemplate()->m_refundValue != 0)
                sellValue=obj->getTemplate()->m_refundValue;
            else { float cost=*(float*)((char*)obj+0x258); sellValue=(unsigned int)(cost * TheGlobalData->m_sellPercentage); }
            float health=health000FEBE0(obj->m_body);
            ((Money*)((char*)player+0x48))->deposit((unsigned int)(sellValue*health),true);
            UnicodeString message;
            message.format(TheGameText->fetch("GUI:AddCash",0),sellValue);
            Coord3D pos=obj->m_cachedPos;
            pos.z+=((GeometryInfo*)&obj->m_geometryInfo)->getMaxHeightAbovePosition();
            unsigned int color=*(unsigned int*)((char*)obj->getControllingPlayer()+0x1c4);
            TheInGameUI->slot94(message,&pos,color|0xe6000000);
        }
        ProductionUpdateInterface *production=obj->getProductionUpdateInterface();
        if(production) production->cancelAndRefundAllProduction();
        if((obj->getTemplate()->fieldC8 & 0x80) && obj->m_body->slot08()>1) {
            unsigned int id=0;
            if(obj->bfmeGetRecentDamageSource(&id,4)) {
                Object *source=TheGameLogic->findObjectByID(id);
                if(source) ((BFMEReportDamageSource*)source)->report(obj,1);
            }
        }
        if(obj->getTemplate()->fieldD8 & 0x200000)
            ((Rva001CE3F0*)obj)->apply();
        else obj->kill(Damage000FEBE0,Death000FEBE0);
        delete sellInfo;
        field10.erase(thisIterator);
    }
}
