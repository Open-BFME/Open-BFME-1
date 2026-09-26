// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// GameLogic::destroyObject at0x0038B0C0,190B. The previous naked body is
// replaced by the original deferred-destruction sequence. Duplicate requests
// are ignored after status bit0 is set. Module callbacks run before marking;
// AI goals/path are cleared, then the object is appended to the destruction
// list at+104 and its internal onDestroy virtual at+24 runs.
// Object status is the independently recovered BitFlags<86> at+90.
// DestroyModuleInterface is BehaviorModule's secondary interface slot+14;
// AI setLocomotorGoalNone is the primary virtual at+1E8. Unused virtual slots
// below specify layout only; their signatures are not asserted recovered.
#include <list>
#include <bitset>
template<int N> class BitFlags { public:
 enum Init { kInit };
 BitFlags(Init, int bit) { bits.set(bit); }
 _STL::bitset<N> bits;
};
class DestroyModuleInterface { public: virtual void onDestroy(); };
class BehaviorModuleInterface {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10();
 virtual DestroyModuleInterface *getDestroy();
};
class BehaviorModule {
public:
 char pad00[12]; BehaviorModuleInterface behavior;
 DestroyModuleInterface *getDestroy() { return behavior.getDestroy(); }
};
class AIUpdateInterface {
public:
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
 virtual void slot068();
 virtual void slot06C();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07C();
 virtual void slot080();
 virtual void slot084();
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
 virtual void slot15C();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16C();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17C();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18C();
 virtual void slot190();
 virtual void slot194();
 virtual void slot198();
 virtual void slot19C();
 virtual void slot1A0();
 virtual void slot1A4();
 virtual void slot1A8();
 virtual void slot1AC();
 virtual void slot1B0();
 virtual void slot1B4();
 virtual void slot1B8();
 virtual void slot1BC();
 virtual void slot1C0();
 virtual void slot1C4();
 virtual void slot1C8();
 virtual void slot1CC();
 virtual void slot1D0();
 virtual void slot1D4();
 virtual void slot1D8();
 virtual void slot1DC();
 virtual void slot1E0();
 virtual void slot1E4();
 virtual void setLocomotorGoalNone();
 void destroyPath();
};
class Object {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void onDestroy();
 void setStatus(const BitFlags<86>&, bool);
 char pad04[0x8c]; unsigned status[3]; char pad9C[0x154];
 BehaviorModule **modules; char pad1F4[0x10]; AIUpdateInterface *ai;
};
class GameLogic {
public:
 char pad00[0x104]; _STL::list<Object *> objectsToDestroy;
 void destroyObject(Object *obj);
};
void GameLogic::destroyObject(Object *obj)
{
    if (!obj || (obj->status[0] & 1))
        return;
    for (BehaviorModule **m = obj->modules; *m; ++m)
    {
        DestroyModuleInterface *destroy = (*m)->getDestroy();
        if (destroy)
            destroy->onDestroy();
    }
    obj->setStatus(BitFlags<86>(BitFlags<86>::kInit, 0), true);
    AIUpdateInterface *ai = obj->ai;
    if (ai)
    {
        ai->setLocomotorGoalNone();
        ai->destroyPath();
    }
    objectsToDestroy.push_back(obj);
    obj->onDestroy();
}
