// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Address-derived reconstruction of the callee reached by the
// Rva0026EDD0 offset-tail thunk.  The target walks 12-byte records, takes the
// first id from each non-empty STLport list, resolves that id through the
// already matched GameLogic hash map, and dispatches the resolved object.
// Neither the owning record type nor the final owner callback has a recovered
// semantic name, so both names remain neutral.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Object;
typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
    _STL::equal_to<ObjectID> > ObjectPtrHash;

struct Rva002E0E30ListNode
{
    Rva002E0E30ListNode *m_next;
    Rva002E0E30ListNode *m_previous;
    ObjectID m_id;
};

class GameLogic
{
public:
    char m_pad00[0xb0];
    ObjectPtrHash m_objectHash;
};

extern GameLogic *TheBfmeGameLogic;

class Rva002E0E30Owner
{
};

extern void j_000122a6(void);

class Rva002E5A70Call
{
public:
    void dispatch(void *recordData, Object *object, void *argument2,
        void *argument3);
};

static __forceinline void callRva002E5A70(Rva002E0E30Owner *owner,
    void *recordData, Object *object, void *argument2, void *argument3)
{
    typedef void (Rva002E5A70Call::*Function)(void *, Object *, void *, void *);
    union
    {
        void (*raw)(void);
        Function member;
    } fn;
    fn.raw = j_000122a6;
    (reinterpret_cast<Rva002E5A70Call *>(owner)->*fn.member)(recordData,
        object, argument2, argument3);
}

extern "C" Rva002E0E30Owner *g_bfmeOwnerBR;

struct Rva002E0E30Record
{
    int m_key;
    void *m_recordData;
    Rva002E0E30ListNode *m_ids;
};

class Rva002E0E30
{
public:
    void rva002E0E30Handle(int key, void *argument2, void *argument3);

private:
    char m_pad00[4];
    Rva002E0E30Record *m_begin;
    Rva002E0E30Record *m_end;
};

void Rva002E0E30::rva002E0E30Handle(int key, void *argument2,
    void *argument3)
{
    for (Rva002E0E30Record *record = m_begin; record != m_end; ++record)
    {
        if (record->m_key != key)
            continue;

        Rva002E0E30ListNode *ids = record->m_ids;
        Rva002E0E30ListNode *id = ids->m_next;
        while (id != record->m_ids)
        {
            ObjectID objectID = id->m_id;
            if (objectID != 0)
            {
                ObjectPtrHash::iterator object =
                    TheBfmeGameLogic->m_objectHash.find(objectID);
                if (object != TheBfmeGameLogic->m_objectHash.end())
                {
                    Object *resolved = (*object).second;
                    if (resolved != 0)
                    {
                        callRva002E5A70(g_bfmeOwnerBR,
                            record->m_recordData, resolved, argument2,
                            argument3);
                    }
                }
            }

            id = id->m_next;
        }
    }
}
