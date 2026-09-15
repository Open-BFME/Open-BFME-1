// cl: /DNDEBUG /MD /EHsc
// Retail 0x008A2BA0, 186 bytes. Vtable 0x011364A4 is also installed by
// the matched Rva008A2C80 destructor at 0x008A2C80. The base constructor
// is the independently recovered Gen_008AC620 at 0x008AD3F0 (48-byte base).
// Argument and member are one-pointer owning handles: retail guards the
// by-value argument before base construction and drops it on normal exit.
// Names are address-derived ABI views, not asserted original game names.
class Rva00894D90Accessor
{
public:
    static unsigned int decrement(unsigned int *p);
};
class Rva00894D80Accessor
{
public:
    static unsigned int increment(unsigned int *p);
};
void bfmeDropA(void *p);
struct Rva008A2BA0Payload
{
    unsigned int m_refs;
    unsigned int m_unmodelled04[3];
    void *m_value10;
    void *getValue() const { return m_value10; }
};
class Rva008A2BA0Handle
{
public:
    Rva008A2BA0Handle() : m_ptr(0) {}
    Rva008A2BA0Handle(const Rva008A2BA0Handle &other) : m_ptr(other.m_ptr)
    { if (m_ptr) Rva00894D80Accessor::increment((unsigned int *)m_ptr); }
    ~Rva008A2BA0Handle()
    {
        if (m_ptr && !Rva00894D90Accessor::decrement((unsigned int *)m_ptr))
            bfmeDropA(m_ptr);
    }
    void operator=(const Rva008A2BA0Handle &other)
    {
        if (&other != this)
        {
            if (m_ptr && !Rva00894D90Accessor::decrement((unsigned int *)m_ptr))
                bfmeDropA(m_ptr);
            m_ptr = other.m_ptr;
            if (m_ptr) Rva00894D80Accessor::increment((unsigned int *)m_ptr);
        }
    }
    Rva008A2BA0Payload *m_ptr;
};
class Gen_008AC620
{
public:
    Gen_008AC620();
    virtual void slot0();
    virtual ~Gen_008AC620();
    virtual void slot2();
    unsigned char m_unmodelled04[8];
    void *m_value0c;
    unsigned char m_unmodelled10[0x20];
};
class Rva008A2C80 : public Gen_008AC620
{
public:
    Rva008A2C80(Rva008A2BA0Handle value);
    virtual void slot0();
    virtual ~Rva008A2C80();
    unsigned int m_value30;
    Rva008A2BA0Handle m_value34;
};
Rva008A2C80::Rva008A2C80(Rva008A2BA0Handle value)
{
    m_value30 = 0;
    m_value34 = value;
    m_value0c = value.m_ptr->getValue();
}
