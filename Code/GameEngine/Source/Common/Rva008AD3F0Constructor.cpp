// cl: /DNDEBUG /MD /EHsc
// Retail 0x008AD3F0, 284 bytes. The installed vtable 0x0113693C
// leads to the matched Gen_008AC620 deleting/complete destructors at
// 0x008AD510/0x008AC620; derived vptr-only constructors also call this body.
// The owner is address-derived, not an asserted original game class name.
// The +0x24 member is constructed by 0x008BE660 and destroyed by
// 0x008BE6D0, independently called at +0x24 in the matched owner destructor.
// The child allocation uses a visible constructor forwarding to opaque
// initialize(), preserving retail's allocation-failure and EH lifetimes.
// No source-visible field names are established beyond these ABI offsets.
extern void *(*Rva008C5D70Alloc)(unsigned int);
extern "C" void (*TheBfmeFree)(void *, unsigned int);
struct Rva00899C20Registry;
extern Rva00899C20Registry *g_Va013387D8;
extern unsigned char g_Va013385F8;

class BfmeStateNode
{
public:
    virtual void retain();
    virtual void release();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual unsigned char slot5();
};
class Rva0089C860State
{
public:
    Rva0089C860State(int value) { initialize(value); }
    Rva0089C860State *initialize(int value);
    ~Rva0089C860State();
    static void *operator new(unsigned int bytes)
    { return Rva008C5D70Alloc(bytes); }
    static void operator delete(void *p, unsigned int bytes)
    { TheBfmeFree(p, bytes); }
    int m_value;
    int m_flags;
    BfmeStateNode *m_node;
    int m_tail;
};
class Gen_008BE660
{
public:
    Gen_008BE660();
    ~Gen_008BE660();
    void *m_value;
    int m_field28;
};
class BfmeLookupResult
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual BfmeLookupResult *getValue();
    unsigned char m_unmodelled04[8];
    BfmeStateNode *m_node;
};
class BfmeTab1024
{
public:
    int bfmeFind1024(int key);
};
class __declspec(novtable) Gen_008AC620Base
{
public:
    Gen_008AC620Base() : m_04(-1), m_08(0), m_0c(0), m_10(0), m_14(0) {}
    ~Gen_008AC620Base() { delete m_10; }
    virtual void slot0();
    int m_04;
    int m_08;
    int m_0c;
    Rva0089C860State *m_10;
    unsigned char m_14;
    unsigned char m_unmodelled15[3];
    int m_18;
    unsigned int m_1c;
    int m_20;
};
class Gen_008AC620 : public Gen_008AC620Base
{
public:
    Gen_008AC620();
    virtual ~Gen_008AC620();
    Gen_008BE660 m_member24;
    int m_2c;
};

Gen_008AC620::Gen_008AC620()
{
    m_20 = 0;
    m_member24.m_field28 = 0;
    m_1c = (m_1c & 0xf2000000) | 0x02000000;
    m_10 = new Rva0089C860State(8);
    m_18 = -1;
    m_2c = 0;
    BfmeLookupResult *result = (BfmeLookupResult *)
        ((BfmeTab1024 *)((char *)g_Va013387D8 + 8))->bfmeFind1024((int)&g_Va013385F8);
    BfmeLookupResult *valueResult = result->getValue();
    Rva0089C860State *state = m_10;
    BfmeStateNode *newNode = (BfmeStateNode *)((unsigned int)valueResult->m_node & ~1);
    BfmeStateNode *oldNode = (BfmeStateNode *)((unsigned int)state->m_node & ~1);
    if (newNode)
        newNode->retain();
    if (oldNode)
        oldNode->release();
    if (!newNode)
    {
        state->m_node = newNode;
        return;
    }
    if (newNode->slot5() == 1)
        newNode = (BfmeStateNode *)((unsigned int)newNode | 1);
    state->m_node = newNode;
}
