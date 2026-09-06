// cl: /DNDEBUG /MD /EHsc
// Retail 0x006F92D0 constructs an unnamed W3D resource object.
// The vtable slots at 0x01120360 identify its run, return-address, and render
// methods. The constructor's member layout comes from the matching destructor.

namespace _STL
{
    class __new_alloc
    {
    public:
        static void *allocate(unsigned bytes);
    };
}

struct Rva006F92D0ListNode
{
    Rva006F92D0ListNode *m_next;
    Rva006F92D0ListNode *m_prev;
    unsigned char m_pad[4];
};

class Rva006F92D0List
{
public:
    Rva006F92D0List() : m_head(0)
    {
        Rva006F92D0ListNode *node = static_cast<Rva006F92D0ListNode *>(
            _STL::__new_alloc::allocate(12));
        node->m_next = node;
        node->m_prev = node;
        m_head = node;
    }

    ~Rva006F92D0List();

    Rva006F92D0ListNode *m_head;
};

__declspec(noinline) Rva006F92D0List::~Rva006F92D0List()
{
    m_head = 0;
}

struct Rva006F92D0RefPtr
{
    Rva006F92D0RefPtr() : m_value(0) {}
    ~Rva006F92D0RefPtr();

    void *m_value;
};

__declspec(noinline) Rva006F92D0RefPtr::~Rva006F92D0RefPtr()
{
    m_value = 0;
}

class Rva006F92D0Base
{
public:
    virtual ~Rva006F92D0Base() {}
};

class Rva006F92D0 : public Rva006F92D0Base
{
public:
    Rva006F92D0();
    virtual ~Rva006F92D0();
    virtual void run();
    virtual char *get();
    virtual void render();
    void init();

    void *m_04;
    void *m_08;
    void *m_0c;
    Rva006F92D0RefPtr m_10;
    void *m_14;
    void *m_18;
    Rva006F92D0RefPtr m_1c;
    Rva006F92D0List m_list;
    void *m_24;
    unsigned char m_28;
    unsigned char m_29;
    unsigned char m_2a;
};

Rva006F92D0::Rva006F92D0()
    : m_10(), m_1c(), m_list()
{
    m_28 = 0;
    m_0c = 0;
    m_04 = 0;
    m_08 = 0;
    m_14 = 0;
    m_18 = 0;
    m_24 = 0;
    init();
    unsigned char ready = 1;
    m_28 = ready;
    m_2a = ready;
}

