// Constructor RVA 0x00200BA0 installs the DieModuleInterface vtable at VA
// 0x010A4DF0. Slot 0 reaches RVA 0x00200DF0 through ILT 0x0004AD63.
// The RET4 instruction at RVA 0x00200FFA closes the 525-byte body.
// Retail data has four vectors at offsets 0x34, 0x40, 0x4C, and 0x58.
// The last vector retains audio info before playback.
// stlport
// cl: /DNDEBUG /MD /EHsc
#include <vector>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);
extern int GetGameClientRandomValue(int, int, char *, int);
extern int GetGameLogicRandomValue(int, int, char *, int);


struct Coord3D { float x, y, z; };
enum ObjectID { INVALID_OBJECT_ID = 0 };
enum SlowDeathPhaseType { SDPHASE_INITIAL, SDPHASE_MIDPOINT, SDPHASE_FINAL };
class Object {
public:
    char pad00[0x38];
    Coord3D position;
    char pad44[0x30];
    ObjectID id;
    char pad78[0x204-0x78];
    class AIUpdateInterface *ai;
};
class FXList {
public:
    bool bfmeIsBlocked();
    void doFXObj(const Object *, const Object *) const;
    static void doFXObj(const FXList *fx, const Object *obj, const Object *victim) {
        if (fx && !const_cast<FXList *>(fx)->bfmeIsBlocked()) fx->doFXObj(obj, victim);
    }
};
class ObjectCreationList {
public:
    void createInternal(const Object *, const Object *, unsigned int) const;
    static void create(const ObjectCreationList *ocl, const Object *obj, const Object *victim) {
        if (ocl) ocl->createInternal(obj, victim, 0);
    }
};
class WeaponTemplate;
class WeaponStore {
public:
    void createAndFireTempWeapon(const WeaponTemplate *, const Object *, const Coord3D *);
};
extern WeaponStore *TheWeaponStore;

class AudioEventInfo {
public:
    virtual ~AudioEventInfo();
    long m_refCount;
    void Release_Ref() {
        if (InterlockedDecrement(&m_refCount) <= 0) delete this;
    }
};
struct AudioEventInfoRef {
    AudioEventInfo *ptr;
    AudioEventInfoRef(AudioEventInfo *other) : ptr(other) {
        if (ptr) InterlockedIncrement(&ptr->m_refCount);
    }
    ~AudioEventInfoRef() {
        if (ptr) ptr->Release_Ref();
    }
};
class AudioEventRTS {
public:
    AudioEventRTS(const AudioEventInfoRef &, ObjectID);
    ~AudioEventRTS();
private:
    char storage[0x70];
};
class AudioManager {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16();
    virtual unsigned int addAudioEvent(const AudioEventRTS *);
};
extern AudioManager *TheAudioClientUpdate;


class AIUpdateInterface {
public:
    char pad00[0x32b];
    bool dead;
    void markAsDead();
};
class DamageInfo;
class DieMuxData {
public: bool isDieApplicable(const Object *, const DamageInfo *) const;
};
class GameLogic { public: void destroyObject(Object *); };
extern GameLogic *TheGameLogic;
struct Rva00200DF0Data {
    char prefix[0x34];
    std::vector<const FXList *> fx;
    std::vector<const ObjectCreationList *> ocls;
    std::vector<const WeaponTemplate *> weapons;
    std::vector<AudioEventInfo *> sounds;
};
class Rva00200DF0 {
public:
    Object *getObject() const { return *(Object **)((char *)this-8); }
    const Rva00200DF0Data *getData() const { return *(const Rva00200DF0Data **)((char *)this-12); }
    virtual void onDie(const DamageInfo *);
};
void Rva00200DF0::onDie(const DamageInfo *damageInfo)
{
    if (!((DieMuxData *)((char *)getData()+8))->isDieApplicable(getObject(), damageInfo)) return;
    AIUpdateInterface *ai=getObject()->ai;
    if(ai) {
        if(ai->dead) return;
        ai->markAsDead();
    }
    const Rva00200DF0Data *d=getData();
    int idx, listSize;
    listSize=d->fx.size();
    if(listSize>0) {
        idx=GetGameLogicRandomValue(0,listSize-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\InstantDeathBehavior.cpp",135);
        const FXList *fx=d->fx[idx];
        FXList::doFXObj(fx,getObject(),0);
    }
    listSize=d->ocls.size();
    if(listSize>0) {
        idx=GetGameLogicRandomValue(0,listSize-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\InstantDeathBehavior.cpp",145);
        const ObjectCreationList *ocl=d->ocls[idx];
        ObjectCreationList::create(ocl,getObject(),0);
    }
    listSize=d->weapons.size();
    if(listSize>0) {
        idx=GetGameLogicRandomValue(0,listSize-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\InstantDeathBehavior.cpp",155);
        const WeaponTemplate *wt=d->weapons[idx];
        if(wt) TheWeaponStore->createAndFireTempWeapon(wt,getObject(),&getObject()->position);
    }
    listSize=d->sounds.size();
    if(listSize>0) {
        idx=GetGameLogicRandomValue(0,listSize-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\InstantDeathBehavior.cpp",169);
        AudioEventInfoRef sound=d->sounds[idx];
        if(sound.ptr && TheAudioClientUpdate) {
            Object *obj = getObject();
            ObjectID id = obj->id;
            AudioEventRTS event(sound,id);
            TheAudioClientUpdate->addAudioEvent(&event);
        }
    }
    TheGameLogic->destroyObject(getObject());
}
