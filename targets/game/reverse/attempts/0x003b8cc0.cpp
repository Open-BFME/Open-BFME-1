// ?d_003b8cc0@@YAXXZ
// partial score=0.45 date=2026-09-24
// cl: /DNDEBUG /MD /EHs-c-
// Unverified source-shape bank for 0x003B8CC0/276. The now-matched
// Rva000643F0Value::copyTo return contract and 0x00026887 typed ILT route
// from 0x003BBE50 make this compile without a new semantic pin. The retail
// owner remains unknown; the six calls and 20-byte vector element layout are
// independently observable, but this candidate has a +4-byte frame and
// different loop liveness, so it must not be landed without strict matching.
struct Rva000643F0Triple { int v0, v4, v8; };
class Rva000643F0Value { public: Rva000643F0Triple *copyTo(Rva000643F0Triple *out) const; int v0, v4, v8; };
class Rva00064390 { public: Rva00064390(); int v0,v4,v8,vc; float v10,v14; int v18; };
class Rva00064880Tree { public: bool atEnd(unsigned limit); void *head; void *begin; };
typedef bool (Rva00064880Tree::*Rva003B8CC0Lookup)(unsigned, Rva00064390 *);
extern void j_00026887();
namespace _STL {
struct _Rb_tree_node_base { unsigned char pad[0x10]; void *value; };
template <typename T> class _Rb_global { public: static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *); };
}
class Rva003B8CC0Result { public: virtual void release(); int refs; };
class Rva003B8CC0Item {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual Rva003B8CC0Result *slot74(void *value);
};
struct Rva003B8CC0Entry {
    int pad0;
    Rva003B8CC0Item *item;
    _STL::_Rb_tree_node_base *treeHeader;
    int padc, pad10;
};
extern void bfmeReportGN(Rva003B8CC0Result *,int,int,int);
class Rva003B8CC0Owner {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08(int);
    void run();
private:
    Rva00064880Tree m_tree;
    int m_padc;
    unsigned m_cursor;
    Rva003B8CC0Entry *m_begin;
    Rva003B8CC0Entry *m_end;
};
void Rva003B8CC0Owner::run()
{
    if (m_tree.atEnd(m_cursor)) {
        slot08(0);
        return;
    }
    Rva00064390 local;
    unsigned cursor = m_cursor + 1;
    m_cursor = cursor;
    union { void (*raw)(); Rva003B8CC0Lookup member; } lookup;
    lookup.raw = j_00026887;
    (m_tree.*lookup.member)(cursor, &local);
    Rva000643F0Triple triple;
    reinterpret_cast<const Rva000643F0Value *>(&local)->copyTo(&triple);
    unsigned index = 0;
    unsigned byteOffset = 0;
    while (index < unsigned(m_end - m_begin)) {
        Rva003B8CC0Entry *entry = reinterpret_cast<Rva003B8CC0Entry *>((char *)m_begin + byteOffset);
        _STL::_Rb_tree_node_base *node = *reinterpret_cast<_STL::_Rb_tree_node_base **>((char *)entry->treeHeader + 8);
        while (node != entry->treeHeader) {
            Rva003B8CC0Result *result = entry->item->slot74(node->value);
            bfmeReportGN(result, triple.v0, triple.v4, triple.v8);
            if (--result->refs == 0)
                result->release();
            node = _STL::_Rb_global<bool>::_M_increment(node);
        }
        ++index;
        byteOffset += sizeof(Rva003B8CC0Entry);
    }
}
