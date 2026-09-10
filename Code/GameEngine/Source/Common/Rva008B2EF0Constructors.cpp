// cl: /DNDEBUG /MD /EHsc
struct Rva00899560Value;

struct Rva00899560Pool
{
    int m_capacity;
    int m_count;
    Rva00899560Value **m_items;
    inline void addPooled(Rva00899560Value *value);
};

extern Rva00899560Pool *g_rva8CD130IdleHook;

struct Rva00899560Value
{
    virtual ~Rva00899560Value();
    unsigned int m_flags;

    __forceinline Rva00899560Value(unsigned int type)
    {
        unsigned int flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa)
        {
            m_flags = flags | 0x40000000;
            g_rva8CD130IdleHook->addPooled(this);
        }
        else
        {
            m_flags = flags & 0xBFFFFFFF;
        }
    }
};

// ?addPooled@Rva00899560Pool@@ absent-from-retail
inline void Rva00899560Pool::addPooled(Rva00899560Value *value)
{
    if (m_count >= m_capacity)
    {
        value->m_flags &= 0xBFFFFFFF;
        return;
    }
    m_items[m_count] = value;
    ++m_count;
}

struct Rva0089C860State
{
    Rva0089C860State(int value);
    int m_value;
    int m_first;
    int m_second;
    int m_third;
};

class Rva00899F00Base : public Rva00899560Value
{
public:
    Rva00899F00Base(unsigned int argument0, int argument1);
    virtual ~Rva00899F00Base();
    virtual void rva008991B0();

private:
    Rva0089C860State m_state;
    unsigned int m_stateBits;
    unsigned int m_bits;
};

Rva00899F00Base::Rva00899F00Base(unsigned int argument0, int argument1)
    : Rva00899560Value(argument0), m_state(argument1)
{
    *(unsigned char *)&m_bits = 0;
    m_bits &= 0xFFFFFCFF;
    m_stateBits = 0;
}

class Rva008B2EF0 : public Rva00899F00Base {
public:
    __declspec(noinline) Rva008B2EF0(unsigned int argument0, unsigned int argument1);
private:
    unsigned int m_value20;
    unsigned int m_value24;
};

class Rva008B38D0 : public Rva008B2EF0 {
public:
    Rva008B38D0(unsigned int argument0);
};

Rva008B2EF0::Rva008B2EF0(unsigned int argument0, unsigned int argument1)
    : Rva00899F00Base(argument0, 8), m_value20(argument1), m_value24(0) {}

Rva008B38D0::Rva008B38D0(unsigned int argument0)
    : Rva008B2EF0(0x21, argument0) {}
