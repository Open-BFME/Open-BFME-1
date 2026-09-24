// ?rva00237d70@Rva00237D70@@QAEPAVObject@@XZ
// partial score=0.75 date=2026-09-25
// Scratch reconstruction of retail 0x00237D70; all member/class names are address-derived.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef unsigned int UnsignedInt;
class Object;

struct Rva00237D70ListNode
{
    Rva00237D70ListNode *m_next;
    Rva00237D70ListNode *m_previous;
    Object *m_object;
};
struct Rva00237D70MemberList
{
    Rva00237D70ListNode *m_head;
};
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
struct Rva00367E30Logic {};
extern Rva00367E30Logic *TheBfmeGameLogic;
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

Object *Rva00237D70::rva00237d70()
{
    Rva00237D70MemberList *members =
        ((Rva00237D70MemberView *)((char *)this - 0xc4))->getMemberList();
    Rva00237D70ListNode *head = members->m_head;
    if (head->m_next == head)
    {
        if (m_memberIndexCount == 0)
            return 0;
        Rva00237D70TreeNode *entry = m_memberIndex->m_next;
        UnsignedInt index = GetGameLogicRandomValue(0, m_memberIndexCount - 1,
            (char *)0x010aeb50, 0x1064);
        while (index != 0)
        {
            --index;
            entry = (Rva00237D70TreeNode *)_STL::_Rb_global<bool>::_M_increment(
                (_STL::_Rb_tree_node_base *)entry);
        }
        return ((GameLogic *)TheBfmeGameLogic)->findObjectByID(entry->m_key);
    }

    UnsignedInt count = 0;
    Rva00237D70ListNode *scan = head->m_next;
    Rva00237D70ListNode *first;
    if (scan != head)
        first = scan;
    while (scan != head)
    {
        scan = scan->m_next;
        ++count;
    }
    UnsignedInt index = GetGameLogicRandomValue(0, count - 1,
        (char *)0x010aeb50, 0x106a);
    while (index != 0)
    {
        --index;
        first = first->m_next;
    }
    return first->m_object;
}
