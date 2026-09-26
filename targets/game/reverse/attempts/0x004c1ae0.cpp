// ?clone@Rva004C1AE0Adapter@@QBE?AURva004C1AE0Handle@@XZ
// partial score=0.366337 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 004C1AE0 / 101. Heap clone returning an owning adapter handle.
// The shared vtable is identified by its destructor route, not by the
// suspicious PartitionFilterPossibleToAttack label on the vtable address.
void *__cdecl operator new(unsigned int n);

class Rva004C1150AdapterBase {
public:
    virtual ~Rva004C1150AdapterBase() {}
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
};

struct Rva004C1AE0Handle {
    Rva004C1AE0Handle(void *p) : m_ptr(p) {}
    Rva004C1AE0Handle(Rva004C1AE0Handle &other) : m_ptr(other.m_ptr) { other.m_ptr=0; }
    ~Rva004C1AE0Handle();
    void *m_ptr;
};

class Rva004C1AE0Adapter : public Rva004C1150AdapterBase {
public:
    Rva004C1AE0Adapter(const Rva004C1AE0Adapter &other)
        : m_a(other.m_a), m_b(other.m_b), m_c(other.m_c) {}
    virtual ~Rva004C1AE0Adapter() {}
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    Rva004C1AE0Handle clone() const;
    unsigned m_a;
    void *m_b;
    unsigned m_c;
};

Rva004C1AE0Handle Rva004C1AE0Adapter::clone() const
{
    return Rva004C1AE0Handle(new Rva004C1AE0Adapter(*this));
}
