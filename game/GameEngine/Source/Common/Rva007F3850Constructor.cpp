// cl: /DNDEBUG /MD /O2
// Retail 0x007F3850. The vtables installed at +0 and +4 are the same pair
// installed by the matched allocator/constructor at 0x007F40F0.
// Its second base installs 0x01129744 before the derived vtables replace it.
class Q3MakeBaseA
{
public:
    virtual void primary();
};

class Q3MakeBaseB
{
public:
    virtual void secondary();
    void *m_payload;
    Q3MakeBaseB(void *payload) : m_payload(payload) {}
};

class Rva007F40F0Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
    Rva007F40F0Object(void *payload);
    virtual void primary();
    virtual void secondary();
};

Rva007F40F0Object::Rva007F40F0Object(void *payload)
    : Q3MakeBaseB(payload)
{
}
