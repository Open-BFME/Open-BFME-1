// ?run@Rva003B8CC0Owner@@QAEXXZ
// partial score=0.8913 date=2026-11-02
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <set>

struct Rva000643F0Triple { int v0, v4, v8; };
class Rva000643F0Value {
public:
    Rva000643F0Triple *copyTo(Rva000643F0Triple *destination) const;
    int v0, v4, v8;
};
class Rva00064390 {
public:
    Rva00064390();
    int v0, v4, v8, vc;
    float v10, v14;
    int v18;
};
class Rva00064880Tree {
public:
    bool atEnd(unsigned int limit);
    _STL::_Rb_tree_node_base *head;
    _STL::_Rb_tree_node_base *begin;
};
typedef bool (Rva00064880Tree::*Rva003B8CC0Lookup)(unsigned int, Rva00064390 *);
extern void j_00026887();
extern bool Rva007397E0(void *object, float a, float b, float c);

class Rva003B8CC0Result {
public:
    virtual void release();
    int m_refCount;
};
class Rva003B8CC0Item {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28();
    virtual Rva003B8CC0Result *slot29(int key);
};
struct Rva003B8CC0Entry {
    int pad0;
    Rva003B8CC0Item *m_item;
    _STL::set<int> m_keys;
};
class Rva003B8CC0Owner {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02(int);
    void run();
    Rva00064880Tree m_tree;
    int m_0C;
    unsigned int m_cursor;
    _STL::vector<Rva003B8CC0Entry> m_entries;
};

void Rva003B8CC0Owner::run()
{
    if (m_tree.atEnd(m_cursor)) {
        slot02(0);
        return;
    }
    Rva00064390 value;
    ++m_cursor;
    union { void (*raw)(); Rva003B8CC0Lookup member; } treeCall;
    treeCall.raw = j_00026887;
    (m_tree.*treeCall.member)(m_cursor, &value);
    Rva000643F0Triple output;
    reinterpret_cast<const Rva000643F0Value *>(&value)->copyTo(&output);
    for (unsigned int i = 0; i < m_entries.size(); ++i) {
        for (_STL::set<int>::iterator it = m_entries[i].m_keys.begin(); it != m_entries[i].m_keys.end(); ++it) {
            Rva003B8CC0Result *result = m_entries[i].m_item->slot29(*it);
            Rva007397E0(result, *(float *)&output.v0, *(float *)&output.v4, *(float *)&output.v8);
            if (--result->m_refCount == 0)
                result->release();
        }
    }
}
