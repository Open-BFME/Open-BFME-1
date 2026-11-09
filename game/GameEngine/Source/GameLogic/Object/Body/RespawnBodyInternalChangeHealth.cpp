// cl: /MD /GX
//
// RespawnBody::internalChangeHealth, retail 0x002147E0 (394 bytes, ret 8). The
// RespawnBody body-module vtable (0x010A90D0) reaches it through ILT 0x00030BBB
// as the internalChangeHealth override; it calls ActiveBody::internalChangeHealth
// (0x002103A0) as its base. A lethal hit that the module data allows to respawn
// (and whose damage source the filter does not exclude) hands the object to its
// RespawnUpdate instead of letting it die permanently.
//
// Ported from Open-BFME-2 Code/GameEngine/Source/GameLogic/Object/Body/RespawnBodyApply.cpp (commit ab7b62797a), matched there for the BFME2
// binary, with BFME1's differences: module data fields 8 bytes lower (filter
// +0x5C, canRespawn +0x60), no status-62 check, and status 79 where BFME2
// tests 80.

class Object;
class Player;
class Module;
enum NameKeyType;
enum ObjectID;
class DamageInfo { public: unsigned char before08[8]; ObjectID source; };
class GameLogic { public: Object *findObjectByID(ObjectID id); };
extern GameLogic *TheGameLogic;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_0003369f();  // retail reaches Object::onDie (0x001CEFC0) through this ILT
class Object {
public:
    Player *getControllingPlayer() const;
    bool testStatus(int status) const;	// ILT 0x000016A4
    void onDie(DamageInfo *);
protected:
    Module *findModule(NameKeyType) const;
    friend class RespawnBody;
};
struct Rva2225E0Filter { void *storage; bool accepts(Object *, Player *); };
struct Rva004C1395Data {
    unsigned char before5C[0x5C];
    Rva2225E0Filter filter;
    bool canRespawn;
};
// 0x002A30D0 (via ILT 0x0000E72D) is matched as LevelState002A30D0::apply; it
// takes the RespawnUpdate module as its receiver.
class LevelState002A30D0 { public: void apply(); };
class RespawnUpdate {
public:
    unsigned char before2C[0x2C];
    unsigned int state;
    void rva002A21F0();	// 0x002A21F0 via ILT 0x0001ABE5
};
class ActiveBody { public: virtual void internalChangeHealth(float, DamageInfo *); };
class RespawnBody {
public:
    // Only the health slot is used; other signatures carry no identity claim.
    virtual void slot00(); virtual void slot04();
    virtual void slot08(); virtual void slot0C();
    virtual float health();
    virtual void internalChangeHealth(float, DamageInfo *);
};

void RespawnBody::internalChangeHealth(float amount, DamageInfo *info)
{
    if (amount != 0.0f) {
        Object *obj = *(Object **)((char *)this - 8);
        Rva004C1395Data *data = *(Rva004C1395Data **)((char *)this - 12);
        bool lethal = false;
        bool permanent = false;
        if (-health() >= amount) {
            lethal = true;
            if (!data->canRespawn) {
                permanent = true;
            } else if (info) {
                Object *source = TheGameLogic->findObjectByID(info->source);
                if (source && data->filter.accepts(source, obj->getControllingPlayer()))
                    permanent = true;
            }
        }
        ((ActiveBody *)this)->ActiveBody::internalChangeHealth(amount, info);
        static NameKeyType respawnKey = TheNameKeyGenerator->nameToKey("RespawnUpdate");
        RespawnUpdate *respawn = (RespawnUpdate *)obj->findModule(respawnKey);
        if (!permanent) {
            if (lethal && respawn) {
                if (obj->testStatus(79)) {
                    respawn->rva002A21F0();
                    respawn->state = 0;
                } else {
                    ((LevelState002A30D0 *)respawn)->apply();
                }
                { typedef void (Object::*OnDieFn)(DamageInfo *); union { void (*fn)(); OnDieFn call; } u = { j_0003369f }; (obj->*u.call)(info); }
            }
        } else if (respawn) {
            respawn->rva002A21F0();
        }
    }
}

// Callee evidence (all original method names remain unknown):
// 4BF005..4BF186 RET8 reads float [ebp+8], info [ebp+C], and the same
// secondary receiver. 29A12B..29A205 RET uses the owner Object unchanged;
// 298517..298835 RET4 receives this caller's DamageInfo pointer unchanged.
// 4AF182..4AF1CE and 4AF63E..4AF79C RET use the RespawnUpdate module
// returned by the literal-key lookup; ctor 4AF096 fixes its state at +2C.
