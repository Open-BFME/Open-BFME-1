// cl: /DNDEBUG /MD /EHsc
struct Rva007849F0Target
{
    unsigned int m_prefix;
    unsigned short m_refs;
};
class Rva007849F0Handle
{
public:
    Rva007849F0Handle() : m_target(0) {}
    Rva007849F0Handle(const Rva007849F0Handle &other) : m_target(other.m_target)
    {
        if (m_target)
            ++m_target->m_refs;
    }
    ~Rva007849F0Handle();
private:
    Rva007849F0Target *m_target;
};
class Rva007849F0Source
{
public:
    virtual void slot0(); virtual void slot1();
    virtual void slot2(); virtual void slot3();
    virtual const Rva007849F0Handle *getHandle();
};
class Rva007849F0
{
public:
    Rva007849F0Handle getHandle();
private:
    Rva007849F0Source *m_source;
};
Rva007849F0Handle Rva007849F0::getHandle()
{
    Rva007849F0Source *source = m_source;
    if (!source)
        return Rva007849F0Handle();
    const Rva007849F0Handle *handle = source->getHandle();
    if (!handle)
        return Rva007849F0Handle();
    return *handle;
}
