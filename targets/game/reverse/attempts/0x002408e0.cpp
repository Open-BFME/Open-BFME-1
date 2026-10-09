// ?destroyMember@Rva002408E0View@@QAEXPAVObject@@@Z
// partial score=0.7403 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/GameClient
// stlport
// HordeContain secondary receiver at complete owner +0xE4.
#include <list>
#include <map>

enum KindOfType { Rva002408E0Kind11 = 11 };
#define THING_TU_MEMBERS bool isKindOf(KindOfType kind) const;
enum ObjectID;
#define BFME_HAVE_OBJECTID 1
#define OBJECT_TU_MEMBERS ObjectID getID() const { return m_id; }
#include "object.h"
#include "drawable.h"

struct Rva00226FA0Less : std::less<int> {};
typedef std::map<int, int, Rva00226FA0Less> Rva002408E0Indices;

struct Rva002408E0Node
{
    Rva002408E0Node *next;
    Rva002408E0Node *previous;
    int value;
};
struct Rva002408E0List
{
    Rva002408E0Node *sentinel;
    __forceinline void push_front(const int &value)
    {
        Rva002408E0Node *position = sentinel->next;
        Rva002408E0Node *node = (Rva002408E0Node *)_STL::__node_alloc<true, 0>::allocate(sizeof(Rva002408E0Node));
        _STL::_Construct(&node->value, value);
        Rva002408E0Node *previous = position->previous;
        node->next = position;
        node->previous = previous;
        previous->next = node;
        position->previous = node;
    }
};

struct Rva002408E0Word08 { char pad00[8]; int value08; };
class BodyModuleInterface
{
public:
#define SLOT(N) virtual void slot##N();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
    virtual Rva002408E0Word08 *rvaSlot15();
};

class Rva002408E0Primary
{
public:
#define SLOT(N) virtual void slot##N();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
    SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
    SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
    SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
    SLOT(30) SLOT(31) SLOT(32) SLOT(33)
#undef SLOT
    virtual bool rvaSlot34();
};

struct Rva002408E0ModuleData { char pad00[0x2e4]; int message2E4; };
struct Rva002408E0BannerData { char pad00[0x10]; int value10; };
struct Rva002408E0Banner { char pad00[4]; Rva002408E0BannerData *data04; };
struct Rva002408E0GlobalData { char pad00[0xa76]; bool flagA76; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
enum EvaMessage {};
struct Coord3D;
class Eva { public: bool setShouldPlay(EvaMessage message, const Coord3D *position); };
extern Eva *TheEva;
class GameLogic
{
public:
    void destroyObject(Object *object);
    char pad00[0x3c];
    unsigned int frame3C;
};
extern GameLogic *TheGameLogic;
class Rva00413FF0GuardedVCall { public: void forward(int value); };
class Rva002408E0Erase { public: unsigned int erase(const int &key); };
extern void j_0000d517();
extern void j_0001eb1e();
extern void j_0003f5da();

class Rva00238BC0Filter;

class Rva002408E0View
{
public:
    void destroyMember(Object *member);
#define SLOT(N) virtual void slot##N();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
    SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
    SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
    SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
    SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34)
    SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
    SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44)
    SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
    SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54)
    SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
    SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64)
    SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
    SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74)
    SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
    SLOT(80) SLOT(81) SLOT(82) SLOT(83)
#undef SLOT
    virtual int rvaSlot84(Rva00238BC0Filter *filter) const;
    char pad04[0x30 - 4];
    char index30[12];
    Rva002408E0Indices indices3C;
    char pad48[0x54 - 0x48];
    Rva002408E0List available54;
    char pad58[0xd0 - 0x58];
    int memberD0;
    char padD4[0x110 - 0xd4];
    unsigned int frame110;
    int bodyValue114;
    bool flag118;
    bool flag119;
};

// ?destroyMember@Rva002408E0View@@QAEXPAVObject@@@Z
void Rva002408E0View::destroyMember(Object *member)
{
    Rva002408E0Primary *owner = (Rva002408E0Primary *)((char *)this - 0xe4);
    int id = member->getID();
    if (memberD0 != id && *(int *)((char *)owner + 0x1bc) != id && !member->isKindOf(Rva002408E0Kind11))
        available54.push_front(indices3C[int(id)]);

    if (member->m_body)
    {
        Rva002408E0Word08 *value = member->m_body->rvaSlot15();
        if (value)
            bodyValue114 = value->value08;
        else
            bodyValue114 = 0;
    }

    typedef unsigned int (Rva002408E0Erase::*Erase)(const int &);
    union { void (*fn)(); Erase call; } firstErase = { j_0000d517 };
    (((Rva002408E0Erase *)&indices3C)->*firstErase.call)(member->getID());
    union { void (*fn)(); Erase call; } secondErase = { j_0001eb1e };
    (((Rva002408E0Erase *)&index30)->*secondErase.call)(member->getID());

    while (owner->rvaSlot34()) {}
    if (((std::list<Object *> *)((char *)this - 0xac))->empty() && *(int *)((char *)this + 0x34) == 0)
    {
        Rva002408E0ModuleData *data = *(Rva002408E0ModuleData **)((char *)this - 0xe0);
        TheEva->setShouldPlay((EvaMessage)data->message2E4, 0);
        TheGameLogic->destroyObject(*(Object **)((char *)this - 0xdc));
    }
    frame110 = TheGameLogic->frame3C;
    if (((Rva002408E0GlobalData *)TheWritableGlobalData)->flagA76)
    {
        Drawable *drawable = (*(Object **)((char *)this - 0xdc))->getDrawable();
        if (drawable && *(bool *)((char *)drawable + 0x3ac))
            ((Rva00413FF0GuardedVCall *)drawable)->forward(rvaSlot84(0));
    }
    if (*(int *)((char *)owner + 0x1b4) == member->getID())
        *(int *)((char *)owner + 0x1b4) = 0;
    else if (*(int *)((char *)owner + 0x1bc) == member->getID())
    {
        *(int *)((char *)owner + 0x1bc) = 0;
        typedef Rva002408E0Banner *(Rva002408E0Primary::*FindBanner)(const Object *);
        union { void (*fn)(); FindBanner call; } findBanner = { j_0003f5da };
        Rva002408E0Banner *banner = (owner->*findBanner.call)(member);
        if (banner)
            *(int *)((char *)owner + 0x1cc) = banner->data04->value10;
    }
    flag119 = true;
}
