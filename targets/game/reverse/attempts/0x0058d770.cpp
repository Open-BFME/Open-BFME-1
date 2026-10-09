// ?rank0058D770@@YAHPAVObject@@@Z
// partial score=1.0 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /I.
#include <new>
#include "game/GameEngine/Source/GameLogic/Object/object.h"
extern void j_000022bb();
extern void j_0000c117();
class BfmeHostBU;
namespace _STL
{
class __new_alloc
{
public:
    static void *allocate(unsigned int);
};
}
struct Rva00594FD0Template
{
    void *m_vtable;
    Rva00594FD0Template *m_next;
    char m_pad08[0xD0-8];
    unsigned int m_flags;
    char m_padD4[0x4D0-0xD4];
    int m_priority;
};
static __forceinline Rva00594FD0Template *template00594FD0(Object *object)
{
    Rva00594FD0Template *result = (Rva00594FD0Template *)object->m_template;
    if (!result)
        return 0;
    if (result->m_next)
    {
        typedef Rva00594FD0Template *(Rva00594FD0Template::*Final)() const;
        union { void (*fn)(); Final call; } final = { j_000022bb };
        result = (result->m_next->*final.call)();
    }
    return result;
}
class GameLogic
{
public:
    Object *findObjectByID(int);
    char m_pad00[0x3C];
    unsigned int m_frame;
};
extern GameLogic *TheBfmeGameLogic;
struct Rva00594FD0Entry
{
    Rva00594FD0Entry(int id, int rank) : m_id(id), m_rank(rank), m_extra(0) {}
    int m_id;
    int m_rank;
    int m_extra;
};
struct Rva00594FD0Node
{
    Rva00594FD0Node *m_next;
    Rva00594FD0Node *m_previous;
    Rva00594FD0Entry m_value;
};
class BfmeSubBU
{
public:
    void bfmeUnlinkBU(BfmeHostBU *);
    char m_pad00[4];
    Rva00594FD0Node *m_head;
};
class Object;
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
extern void j_0000dfc1();
extern void j_000012a8();

struct Iterator004B25D0
{
    void *a;
    void *b;
    Iterator004B25D0() {}
    Iterator004B25D0(const Iterator004B25D0 &p) : a(p.a), b(p.b) {}
};
struct Rva0037F190Result;
class ExperienceLevelSystem
{
public:
    void rva0037F190(Rva0037F190Result *, Object *);
};
class ExperienceView004B25D0
{
public:
    bool at0037E810(Iterator004B25D0 it)
    {
        typedef bool (ExperienceView004B25D0::*Call)(Iterator004B25D0);
        union { void (*fn)(); Call call; } target = { j_0000dfc1 };
        return (this->*target.call)(it);
    }
    int at0037D810(Iterator004B25D0 it)
    {
        typedef int (ExperienceView004B25D0::*Call)(Iterator004B25D0);
        union { void (*fn)(); Call call; } target = { j_000012a8 };
        return (this->*target.call)(it);
    }
};
// Open BFME 2: Code/GameEngine/Source/GameClient/GUI/ControlBar/UnitHelpSource.cpp
static __declspec(noinline) int rank0058D770(Object *object)
{
    Iterator004B25D0 it;
    TheExperienceLevelSystem->rva0037F190((Rva0037F190Result *)&it,object);
    typedef bool (ExperienceView004B25D0::*Check)(Iterator004B25D0);
    union { void (*fn)(); Check call; } check = { j_0000dfc1 };
    if (!(((ExperienceView004B25D0 *)TheExperienceLevelSystem)->*check.call)(it))
        return 0;
    typedef int (ExperienceView004B25D0::*Rank)(Iterator004B25D0);
    union { void (*fn)(); Rank call; } rank = { j_000012a8 };
    return (((ExperienceView004B25D0 *)TheExperienceLevelSystem)->*rank.call)(it);
}

void BfmeSubBU::bfmeUnlinkBU(BfmeHostBU *host)
{
    Object *object = (Object *)host;
    if (!(template00594FD0(object)->m_flags & 0x02000000))
        return;
    typedef void *(__cdecl *Portrait)(Rva00594FD0Template *, Object *);
    union { void (*fn)(); Portrait call; } portrait = { j_0000c117 };
    if (!portrait.call(template00594FD0(object),object))
        return;
    for (Rva00594FD0Node *node = m_head->m_next; node != m_head; node = node->m_next)
        if (node->m_value.m_id == object->m_id)
            return;
    int id = object->m_id;
    int rank = rank0058D770(object);
    GameLogic *logic = TheBfmeGameLogic;
    Rva00594FD0Node *position = m_head;
    if (logic->m_frame < 6)
    {
        int priority = template00594FD0(object)->m_priority;
        for (position = m_head->m_next; position != m_head; position = position->m_next)
        {
            Object *other = logic->findObjectByID(position->m_value.m_id);
            if (other && priority < template00594FD0(other)->m_priority)
                break;
        }
    }
    Rva00594FD0Node *node = (Rva00594FD0Node *)_STL::__new_alloc::allocate(sizeof(Rva00594FD0Node));
    new (&node->m_value) Rva00594FD0Entry(id,rank);
    node->m_previous = position->m_previous;
    node->m_next = position;
    position->m_previous->m_next = node;
    position->m_previous = node;
}
