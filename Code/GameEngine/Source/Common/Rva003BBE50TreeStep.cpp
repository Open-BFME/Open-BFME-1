// cl: /DNDEBUG /MD /EHsc
// Retail 0x003BBE50, 227 bytes. The receiver identity is not proven by a
// named caller or vtable, so its class retains the address token. See
// reverse/identity_evidence/0x003bbe50-step-call-contract.md for the five
// physical call targets and the measured /EHsc and x87 source shapes.
// The two generated j_ symbols below claim only retail ILT addresses. Their
// typed member-pointer calls express the observed thiscall ABI without
// inventing a second semantic name for either physical body.
struct Rva000643F0Triple { int m_value00, m_value04, m_value08; };
struct Rva003BBE50Value {
    float m_00, m_04, m_08, m_0c, m_10, m_14;
    void *m_18;
};
class Rva000643F0Value {
public:
    Rva000643F0Triple *copyTo(Rva000643F0Triple *destination) const;
    int m_value00, m_value04, m_value08;
};
namespace _STL { struct _Rb_tree_node_base; }
class Rva00064880Tree {
public:
    bool atEnd(unsigned int limit);
    _STL::_Rb_tree_node_base *m_bfme00YJ;
    _STL::_Rb_tree_node_base *m_bfme04YJ;
};
class Rva003BBE50Tree : public Rva00064880Tree {};
typedef bool (Rva003BBE50Tree::*Rva003BBE50TreeLookup)(unsigned int, Rva003BBE50Value *);
extern void j_00026887();
class Keyboard { public: bool isShift(); };
extern Keyboard *TheKeyboard;
class GlobalData { public: unsigned char m_pad[0x90]; unsigned char m_flag90; };
extern GlobalData *TheWritableGlobalData;
extern volatile float g_01075954;
class Gen_00609320;
extern Gen_00609320 *g_bfmeStateDF;
struct Rva003BBE50PairBase {
    Rva003BBE50PairBase() {}
    Rva003BBE50PairBase(const Rva003BBE50PairBase &other) : m_first(other.m_first), m_second(other.m_second) {}
    int m_first, m_second;
};
struct Rva003BBE50Pair : Rva003BBE50PairBase {
    Rva003BBE50Pair(const Rva003BBE50PairBase &other) : Rva003BBE50PairBase(other) {}
    ~Rva003BBE50Pair() {}
};
class Rva003BBE50CallJ378F8 {};
typedef void (Rva003BBE50CallJ378F8::*Rva003BBE50Invoke)(Rva003BBE50Pair, float);
extern void j_000378f8();
class Rva003BBE50Owner {
public:
    unsigned char step(unsigned char enabled);
    unsigned char m_pad0[0x0c];
    Rva003BBE50Tree m_tree;
    unsigned char m_pad14[4];
    int m_count;
};
unsigned char Rva003BBE50Owner::step(unsigned char enabled)
{
    if (enabled)
    {
        ++m_count;
        if (m_tree.atEnd(m_count))
            return 1;
        if (TheKeyboard->isShift() && TheWritableGlobalData->m_flag90)
            m_count += 9;
        Rva003BBE50Value value = {0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0};
        union { void (*raw)(); Rva003BBE50TreeLookup member; } treeCall;
        treeCall.raw = j_00026887;
        (m_tree.*treeCall.member)(m_count, &value);
        Rva000643F0Triple output;
        union { void (*raw)(); Rva003BBE50Invoke member; } stateCall;
        stateCall.raw = j_000378f8;
        (reinterpret_cast<Rva003BBE50CallJ378F8 *>(g_bfmeStateDF)->*stateCall.member)(
            *reinterpret_cast<Rva003BBE50PairBase *>(
                reinterpret_cast<const Rva000643F0Value *>(&value)->copyTo(&output)),
            (*reinterpret_cast<volatile float *>(&value.m_0c)) * const_cast<const float &>(g_01075954));
    }
    return 0;
}
