// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
#include <list>
typedef unsigned int UnsignedInt;
class Object;

struct Rva00237D70ListNode
{
    Rva00237D70ListNode *m_next;
    Rva00237D70ListNode *m_previous;
    Object *m_object;
};
typedef _STL::list<Object *> Rva00237D70MemberList;
struct Rva00237D70TreeNode
{
    UnsignedInt m_color;
    Rva00237D70TreeNode *m_parent;
    Rva00237D70TreeNode *m_next;
    Rva00237D70TreeNode *m_right;
    UnsignedInt m_key;
};
namespace _STL
{
struct _Rb_tree_node_base;
template <class T> struct _Rb_global
{
    static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

template <int N> class Rva00237D70Slots : public Rva00237D70Slots<N - 1>
{
public:
    virtual int slot(char (*)[N]) = 0;
};
template <> class Rva00237D70Slots<0> {};
class Rva00237D70MemberView : public Rva00237D70Slots<65>
{
public:
    virtual Rva00237D70MemberList *getMemberList() = 0;
};
class GameLogic
{
public:
    Object *findObjectByID(int id);
};
extern GameLogic *TheBfmeGameLogic;
extern int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);

class Rva00237D70
{
public:
    Object *rva00237d70();
private:
    char m_pad000[0x30];
    Rva00237D70TreeNode *m_memberIndex;
    UnsignedInt m_memberIndexCount;
};

// ?rva00237d70@Rva00237D70@@QAEPAVObject@@XZ
// Open BFME 2: Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
Object *Rva00237D70::rva00237d70()
{
    Rva00237D70MemberList *members =
        ((Rva00237D70MemberView *)((char *)this - 0xc4))->getMemberList();
    if (members->empty())
    {
        if (m_memberIndexCount == 0)
            return 0;
        Rva00237D70TreeNode *entry = m_memberIndex->m_next;
        for (int index = GetGameLogicRandomValue(0, m_memberIndexCount - 1,
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x1064); index != 0; --index)
            entry = (Rva00237D70TreeNode *)_STL::_Rb_global<bool>::_M_increment(
                (_STL::_Rb_tree_node_base *)entry);
        return TheBfmeGameLogic->findObjectByID(entry->m_key);
    }
    Rva00237D70MemberList::const_iterator first = members->begin();
    for (int index = GetGameLogicRandomValue(0, members->size() - 1,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x106a); index != 0; --index)
        ++first;
    return *first;
}
