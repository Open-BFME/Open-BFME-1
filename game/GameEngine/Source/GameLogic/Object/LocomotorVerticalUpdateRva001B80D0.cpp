// cl: /O2 /MD /EHsc-
// Retail 0x001B80D0 650B: locomotor vertical movement and orientation jitter.
extern "C" double __cdecl sin(double);
#pragma intrinsic(sin)
float normalizeAngle(float);
float Rva0002CCA5GetGameLogicRandomValueRealThunk(float,float,char*,int);
class Rva002BC310Owner { public: unsigned char checkHeight(); };
class Rva001B80D0AI { public:
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
virtual Rva002BC310Owner *query001B80D0(); };
enum BodyDamageType { BODY_OK, BODY_DAMAGED };
class Rva001B80D0Body { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual BodyDamageType damageState001B80D0(); };
struct Rva001B80D0Flags {
    unsigned m_bits[10];
    __forceinline unsigned test(unsigned i) const { return m_bits[i>>5] & (1u<<(i&31)); }
    __forceinline void set(unsigned i) { m_bits[i>>5] |= 1u<<(i&31); }
    __forceinline void reset(unsigned i) { m_bits[i>>5] &= ~(1u<<(i&31)); }
};
class Thing { public:
    float getHeightAboveTerrainOrWater() const;
    void setPositionZ(float);
    void setOrientation(float);
};
class Object : public Thing { public:
    char before40[0x40];
    float positionZ40;
    float m_cachedAngle;
    char before74[0x74-0x48];
    int objectId74;
    char beforec0[0xc0-0x78];
    float valueC0;
    char before110[0x110-0xc4];
    Rva001B80D0Flags m_modelConditionFlags;
    char before200[0x200-0x138];
    Rva001B80D0Body *body200;
    Rva001B80D0AI *ai204;
    void notifyModelConditionChanged();
};
class Overridable { public:
    void *vtable;
    Overridable *m_nextOverride;
    const Overridable *getFinalOverride() const;
};
struct Rva001B80D0Template : Overridable {
    char before14[0x14-8];
    float scale14;
};
// Retail's game-logic singleton (GameLogic *TheGameLogic, defined once in
// GameLogic.cpp).  This TU reads it through its own Rva001B80D0GameLogic view.
struct Rva001B80D0GameLogic { char before3c[0x3c]; unsigned m_frame; };
class GameLogic;
extern GameLogic *TheGameLogic;
static inline Rva001B80D0GameLogic *localTheGameLogic(void) { return (Rva001B80D0GameLogic *)TheGameLogic; }
class Locomotor { public: float rva001B5A30(Object*,BodyDamageType) const; };
class Rva002C12E0Locomotor { public:
    void *vtable;
    Rva001B80D0Template *m_template;
    char before44[0x44-8];
    float height44;
    char before9c[0x9c-0x48];
    float velocity9c;
    float angleDeltaA0;
    void locoUpdate1(void *object);
    Rva001B80D0Template *getResolved() const {
        Rva001B80D0Template *result=m_template;
        if(result && result->m_nextOverride) result=(Rva001B80D0Template*)result->m_nextOverride->getFinalOverride();
        return result;
    }
};
void Rva002C12E0Locomotor::locoUpdate1(void *object)
{
    Object *obj=(Object*)object;
    if(!obj) return;
    float amplitude=obj->valueC0*0.5f;
    if(getResolved()->scale14>1.0f) amplitude*=getResolved()->scale14;
    Rva001B80D0AI *ai=obj->ai204;
    if(!ai) return;
    Rva002BC310Owner *heightView=ai->query001B80D0();
    if(!heightView) return;
    Rva001B80D0Body *body=obj->body200;
    if(!body) return;
    float desired=(float)sin((int)(localTheGameLogic()->m_frame+obj->objectId74)*0.1f)*amplitude*0.2f+height44;
    float current=obj->getHeightAboveTerrainOrWater();
    bool outside=desired+amplitude*0.2f>current || desired*1.5f<current;
    if(heightView->checkHeight() | outside) velocity9c+=desired-current;
    float cap=((Locomotor*)this)->rva001B5A30(obj,body->damageState001B80D0());
    velocity9c*=0.25f;
    if(velocity9c>cap) velocity9c=cap;
    else if(velocity9c< -cap) velocity9c=-cap;
    if(velocity9c>0.3f) {
        if(obj->m_modelConditionFlags.test(71) || !obj->m_modelConditionFlags.test(102)) {
            obj->m_modelConditionFlags.reset(71);
            obj->m_modelConditionFlags.set(102);
            obj->notifyModelConditionChanged();
        }
    } else {
        if(obj->m_modelConditionFlags.test(102)) {
            obj->m_modelConditionFlags.reset(102);
            obj->notifyModelConditionChanged();
        }
    }
    obj->setPositionZ(obj->positionZ40+velocity9c);
    if(obj->m_modelConditionFlags.test(145)) {
        obj->m_modelConditionFlags.reset(145);
        obj->notifyModelConditionChanged();
    }
    angleDeltaA0+=Rva0002CCA5GetGameLogicRandomValueRealThunk(-0.06283185631036758f,0.06283185631036758f,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Locomotor.cpp",1410);
    if(angleDeltaA0>0.06283185631036758f) angleDeltaA0=0.06283185631036758f;
    if(angleDeltaA0< -0.06283185631036758f) angleDeltaA0=-0.06283185631036758f;
    float angle=obj->m_cachedAngle+angleDeltaA0;
    float normalized=normalizeAngle(angle);
    obj->setOrientation(normalized);
}
