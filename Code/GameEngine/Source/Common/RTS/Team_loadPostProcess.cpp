// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc
// stlport
// Team::loadPostProcess, retail RVA 0x000F1800, 265 bytes.
// Adapted from the GeneralsMD Common/RTS/Team.cpp load-post-process body.
// BFME retains the object-ID hash table (the older implementation is visible
// in GameLogic.h), with buckets at +0xB4, and throws XferException(5, 0).
// Team's pending member-ID list is at +0x100; Object's TeamMemberList links
// are at +0x25C/+0x260. No changes to shared ZH layouts are needed here.
// Identity: TeamFactoryCreate.cpp names the constructor at 0x000F7790;
// that constructor installs vtable VA 0x01085F88. Slot +4 routes through
// 0x0003B764 to this body; slot +8 returns the literal "Team".

#define BFME_STLP_NODE_ALLOC
#include <list>
#include <hash_map>

// Retail ThrowInfo VA 0x011DFE5C describes an 8-byte XferException.
class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tagValue;
};

struct Object
{
    char padding[0x25c];
    Object *nextTeamMember;
    Object *previousTeamMember;
};

class GameLogic
{
public:
    char padding[0xb0];
    typedef _STL::hash_map<unsigned int, Object *> ObjectMap;
    ObjectMap objects;
    Object *findObjectByID(unsigned int id)
    {
        if (id == 0)
            return 0;
        ObjectMap::iterator it = objects.find(id);
        return it != objects.end() ? it->second : 0;
    }
};

extern GameLogic *TheGameLogic;

class TeamPrototype;

class Team
{
    virtual ~Team();
    TeamPrototype *m_proto;
    unsigned int m_id;
    Object *m_firstMember;
    char padding10[0x100 - 0x10];
    _STL::list<unsigned int> m_xferMemberIDList;
protected:
    virtual void loadPostProcess();
};

void Team::loadPostProcess()
{
    _STL::list<unsigned int>::const_iterator it;
    for (it = m_xferMemberIDList.begin(); it != m_xferMemberIDList.end(); ++it)
    {
        Object *obj = TheGameLogic->findObjectByID(*it);
        if (!obj)
            throw XferException(5, 0);
        if (m_firstMember != obj && !obj->nextTeamMember && !obj->previousTeamMember)
            throw XferException(5, 0);
    }
    m_xferMemberIDList.clear();
}
