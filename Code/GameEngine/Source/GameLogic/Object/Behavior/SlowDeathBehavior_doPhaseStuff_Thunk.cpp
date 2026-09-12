// stlport
// cl: /DNDEBUG /MD /EHsc
#include <vector>
// SlowDeathBehavior::doPhaseStuff, retail RVA 0x002080B0 (504 bytes).
// beginSlowDeath at RVA 0x00209BB0 calls this dispatcher; the original
// SlowDeathBehavior.cpp establishes its phase, FX, OCL and weapon operations.
// BFME adds per-phase sounds and uses client RNG for FX and sounds, logic RNG
// for OCLs and weapons. Its four arrays start at +0x58/+0x88/+0xB8/+0xE8;
// the runtime gate is the module-data byte at +0x1A4.
//
// Audio ctor ILT 0x00008E86 -> 0x000B4440 -> helper 0x000B2610 consumes an
// AudioEventInfoRef: it reads the retained object's name at +8, then binds
// that ref to AudioEventRTS+8. Older ledger AsciiString spellings describe
// the same one-word ABI but do not describe this refcounted argument.
//
// Real STLport OCL/weapon vectors preserve the retail temporary ordering.
// The final sound-base/object/id locals also matter to MSVC register choice.

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
};
class FXList {
public:
    bool bfmeIsBlocked() const;
    void doFXObj(const Object *, const Object *) const;
    static void doFXObj(const FXList *fx, const Object *obj, const Object *victim) {
        if (fx && !fx->bfmeIsBlocked()) fx->doFXObj(obj, victim);
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
extern AudioManager *TheAudio;

template<class T> struct PhaseVector {
    T *begin;
    T *end;
    T *capacity;
    int size() const { return end - begin; }
    const T &operator[](int index) const { return begin[index]; }
};
struct SlowDeathBehaviorModuleData {
    char pad00[0x58];
    PhaseVector<const FXList *> fx[4];
    std::vector<const ObjectCreationList *> ocls[4];
    std::vector<const WeaponTemplate *> weapons[4];
    PhaseVector<AudioEventInfo *> sounds[4];
    char pad118[0x8c];
    unsigned char maskOfLoadedEffects;
};
class SlowDeathBehavior {
protected:
    void doPhaseStuff(SlowDeathPhaseType);
    void *vtable;
    const SlowDeathBehaviorModuleData *data;
    Object *object;
};
void SlowDeathBehavior::doPhaseStuff(SlowDeathPhaseType phase)
{
    const SlowDeathBehaviorModuleData *d = data;
    int idx, listSize;
    if (!d->maskOfLoadedEffects) return;
    listSize = d->fx[phase].size();
    if (listSize > 0) {
        idx = GetGameClientRandomValue(0, listSize - 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp", 535);
        const FXList *fx = d->fx[phase][idx];
        FXList::doFXObj(fx, object, 0);
    }
    listSize = d->ocls[phase].size();
    if (listSize > 0) {
        idx = GetGameLogicRandomValue(0, listSize - 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp", 545);
        const ObjectCreationList *ocl = d->ocls[phase][idx];
        ObjectCreationList::create(ocl, object, 0);
    }
    listSize = d->weapons[phase].size();
    if (listSize > 0) {
        idx = GetGameLogicRandomValue(0, listSize - 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp", 555);
        const WeaponTemplate *wt = d->weapons[phase][idx];
        if (wt) TheWeaponStore->createAndFireTempWeapon(wt, object, &object->position);
    }
    listSize = d->sounds[phase].size();
    if (listSize > 0) {
        idx = GetGameClientRandomValue(0, listSize - 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp", 568);
        AudioEventInfo **base = d->sounds[phase].begin;
        AudioEventInfoRef sound = base[idx];
        if (sound.ptr && TheAudio) {
            Object *obj = object;
            ObjectID id = obj->id;
            AudioEventRTS event(sound, id);
            TheAudio->addAudioEvent(&event);
        }
    }
}