// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail RVA 0x001DA4B0 / 290 bytes. Identity intentionally address-derived.
// docs/analysis/0x001d88c0.md proves the hidden vector result and ret24
// hub ABI. Aligned retail stack accesses correct the notes' final two args:
// arg1=source; arg2=position; arg3=destination; arg4=lifetime. Wrapper ret16.
// At +27 ESP is entryESP-0xB4, so [ESP+0xC4] is entryESP+0x10 (arg4).
// At +48 two registers remain saved: [ESP+0xC8] is entryESP+0x0C (arg3).
// Hub ILT 1B57C jumps to 1D88C0. Its three-word returned vector owns only
// pointer storage; final return copies it to incoming result storage and ret24.
// Native STL deallocation is out of line in this TU, reaching 1D35E -> 61D10.
// The inlined AI command builder retains retail's assignment/call scheduling.
// Object +204, adjusted AI interface +20, parms+8/+20 are retail witnesses.
#include <vector>
#include "coord3d.h"

namespace _STL { template<> void __node_alloc<true, 0>::deallocate(void *, size_t); }

inline Coord3D::~Coord3D() {}
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &that)
{
    struct Words { unsigned x, y, z; };
    *(Words *)this = *(const Words *)&that;
    return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &that)
{
    Coord3DBase *base = this;
    *base = that;
    return *this;
}

extern void j_0000de68();

template<class F> __forceinline F entry001DA4B0(void (__cdecl *p)())
{
    union { void (__cdecl *raw)(); F typed; } address;
    address.raw = p;
    return address.typed;
}

// Physical view of the 12-byte coordinate vector. Its existing ILT resolves
// the destructor at RVA 0x000D6230; the physical thiscall ABI is proved.
struct CoordVector001DA4B0
{
    Coord3D *begin, *end, *capacity;
    ~CoordVector001DA4B0()
    {
        typedef void (CoordVector001DA4B0::*Destroy)();
        (this->*entry001DA4B0<Destroy>(j_0000de68))();
    }
};

enum AICommandType { AICMD_MOVE_TO_POSITION = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
class Object;
struct AICommandParms
{
    AICommandType m_cmd;
    CommandSourceType m_cmdSource;
    Coord3D m_pos;
    Object *m_obj;
    Object *m_otherObj;
    void *m_team;
    CoordVector001DA4B0 m_coords;
    unsigned char m_opaque2c[0x70];
    AICommandParms(AICommandType, CommandSourceType);
};
typedef char AICommandParmsSize001DA4B0[(sizeof(AICommandParms) == 0x9c) ? 1 : -1];
typedef char ObjectVectorSize001DA4B0[(sizeof(std::vector<Object *>) == 12) ? 1 : -1];

class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *);
    __forceinline void move001DA4B0(const Coord3D *position, CommandSourceType source)
    {
        AICommandParms parms(AICMD_MOVE_TO_POSITION, source);
        parms.m_pos = *position;
        aiDoCommand(&parms);
    }
};
struct AIView001DA4B0
{
    unsigned char m_prefix[0x20];
    AICommandInterface m_command;
};
class Object
{
public:
    unsigned char m_prefix[0x204];
    AIView001DA4B0 *m_field204;
};
class ObjectCreation001DA4B0
{
public:
    void createAndMove(Object *, const Coord3D *, const Coord3D *, int);
    std::vector<Object *> buildObjects001D88C0(const Coord3D *, const void *, float, Object *, int);
};

void ObjectCreation001DA4B0::createAndMove(Object *source,
    const Coord3D *position, const Coord3D *destination, int lifetime)
{
    if (position == 0)
        return;
    std::vector<Object *> objects = buildObjects001D88C0(position, 0, 0.0f, source, lifetime);
    if (destination != 0)
    {
        for (unsigned i = 0; i < objects.size(); ++i)
        {
            Object *object = objects[i];
            if (object != 0 && object->m_field204 != 0)
            {
                AICommandInterface *ai = &object->m_field204->m_command;
                ai->move001DA4B0(destination, CMD_FROM_PLAYER);
            }
        }
    }
}

