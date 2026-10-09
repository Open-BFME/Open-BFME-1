// ?update@Rva002C7780Owner@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.6543 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include/Lib /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/GameLogic
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "Coord3D.h"
template <int NUMBITS> class BitFlags {
public:
    bool test(int index) const { return m_bits.test(index); }
private:
    _STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<320> ModelConditionFlags;
#define BFME_HAVE_MODELCONDITIONFLAGS 1

#include "command_source_type.h"
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
#define BFME_HAVE_COORD3D 1
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS void setStatusBit(int bit, bool set); float getVisionRange() const;
#include "object.h"
class AICommandInterface {
public:
    virtual void aiDoCommand(const class AICommandParms *);
    void aiMoveToPosition(const Coord3D *, CommandSourceType);
    void aiAttackObject(Object *, int, CommandSourceType);
};
class PartitionFilter {
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual bool allow(Object *) = 0;
    virtual int rva000C3BA0();
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};
class Rva00260180SelfFilter : public PartitionFilter {
public:
    Rva00260180SelfFilter(Object *object) : m_object(object) {}
    virtual ~Rva00260180SelfFilter() {}
    virtual bool allow(Object *);
    Object *m_object;
};
class Rva0025ED50RootFilter : public PartitionFilter {
public:
    Rva0025ED50RootFilter() {}
    virtual ~Rva0025ED50RootFilter() {}
    virtual bool allow(Object *);
};
class __declspec(novtable) Rva001DCBB0Filter : public PartitionFilter {
public:
    Rva001DCBB0Filter(Object *, unsigned char);
    virtual ~Rva001DCBB0Filter() {}
    virtual bool allow(Object *);
    class Player *m_player;
    unsigned char m_match;
};
class Rva002C74F0 : public PartitionFilter {
public:
    Rva002C74F0() {}
    virtual ~Rva002C74F0() {}
    virtual bool allow(Object *);
};
class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter {
public:
    PartitionFilterRejectBuildings(const Object *);
    virtual ~PartitionFilterRejectBuildings() {}
    virtual bool allow(Object *);
    const Object *m_self;
    bool m_acquireEnemies;
};
class PartitionManager {
public:
    Object *getClosestObject(const Coord3D *, float, int, PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;
int GetGameLogicRandomValue(int, int, const char *, int);
struct Rva002C7780ModuleData {
    unsigned char m_before64[0x64];
    bool m_64;
    unsigned char m_before68[3];
    int m_68;
    bool m_6c;
};
class Rva002C7780Primary {
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
    virtual void slot94();
    virtual void slot95();
    virtual bool isIdle() const;
    Rva002C7780ModuleData *m_data;
    Object *m_object;
    unsigned int m_0c;
};
class Rva002C7780UpdateInterface {
public:
    virtual UpdateSleepTime update();
    unsigned char m_04[12];
};
// The base call has a conflicting ledger identity; this view keeps its retail address.
class Rva0027E5A0UpdateReceiver : public Rva002C7780Primary, public Rva002C7780UpdateInterface, public AICommandInterface {
public:
    virtual UpdateSleepTime update();
    Object *getObject() { return m_object; }
    const Rva002C7780ModuleData *getData() const { return m_data; }
};
class Rva002C7780Owner : public Rva0027E5A0UpdateReceiver {
public:
    virtual UpdateSleepTime update();
};

// ?copyCoordAt002C7780@@YAXAAUCoord3D@@PBU1@@Z absent-from-retail
static __forceinline void copyCoordAt002C7780(Coord3D &destination, const Coord3D *source)
{
    destination.x = source->x;
    destination.y = source->y;
    destination.z = source->z;
}

// ?update@Rva002C7780Owner@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime Rva002C7780Owner::update()
{
    Object *object = getObject();
    const Rva002C7780ModuleData *data = getData();
    Rva0027E5A0UpdateReceiver::update();
    if (data->m_68 != -1 && object->m_modelConditionFlags.test(data->m_68) && isIdle()) {
        if (data->m_6c && !(object->m_status[0] & 8))
            object->setStatusBit(3, true);
        if (data->m_64) {
            Coord3D position = *object->getPosition();
            Rva00260180SelfFilter selfFilter(object);
            Rva0025ED50RootFilter root;
            Rva001DCBB0Filter playerFilter(object, 0);
            Rva002C74F0 extraFilter;
            PartitionFilterRejectBuildings rejectBuildings(object);
            rejectBuildings.link(extraFilter.link(root.link(playerFilter.link(&selfFilter))));
            Object *target = ThePartitionManager->getClosestObject(&position, getObject()->getVisionRange(), 0, &rejectBuildings);
            if (target) {
                aiAttackObject(target, 0x7fffffff, CMD_FROM_AI);
            } else {
                Coord3D destination;
                copyCoordAt002C7780(destination, object->getPosition());
                destination.x += GetGameLogicRandomValue(5, 50, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\WanderAIUpdate.cpp", 0x6b);
                destination.y += GetGameLogicRandomValue(5, 50, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\WanderAIUpdate.cpp", 0x6c);
                aiMoveToPosition(&destination, CMD_FROM_AI);
            }
        } else {
            Coord3D destination;
            copyCoordAt002C7780(destination, object->getPosition());
            destination.x += GetGameLogicRandomValue(5, 50, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\WanderAIUpdate.cpp", 0x76);
            destination.y += GetGameLogicRandomValue(5, 50, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\WanderAIUpdate.cpp", 0x77);
            aiMoveToPosition(&destination, CMD_FROM_AI);
        }
    }
    return UPDATE_SLEEP_NONE;
}
