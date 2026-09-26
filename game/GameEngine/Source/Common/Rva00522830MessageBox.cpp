// ?messageBoxHidden@Gen00522E00@@QAEXH@Z
// cl: /MD /EHsc
//
// AptGuiFX::MessageBoxHidden callback, retail 0x00522830 (154B).
// The 0x00522E00 constructor registers this callback with ILT 0x00044198;
// its registration string is "AptGuiFX::MessageBoxHidden".  A live callback
// dispatches event code 3 and then clears the owning functor at +0x40.
//
// The throw expression intentionally remains a real C++ throw.  Under MSVC
// 7.1 it emits the retail FunctorNotSet construction and ThrowInfo sequence;
// retail DIR32 0x011E1CE4 is that ThrowInfo record, not message text.

#include <exception>

class FunctorNotSet : public std::exception
{
public:
    FunctorNotSet() : std::exception() {}
};

class Rva00522830Counted
{
public:
    virtual void release(int deletingFlag);
    virtual void apply(int eventCode);
    int m_refCount;
};

class Rva00522830Holder
{
public:
    Rva00522830Holder(int value) : m_ptr((Rva00522830Counted *)value) {}

    operator Rva00522830Counted *() const
    {
        return m_ptr;
    }

    __forceinline Rva00522830Counted *operator->() const
    {
        if (!m_ptr)
            throw FunctorNotSet();
        return m_ptr;
    }

    Rva00522830Holder &operator=(const Rva00522830Holder &other)
    {
        if (this != &other)
        {
            Rva00522830Counted *current = m_ptr;
            if (current)
            {
                if (--current->m_refCount <= 0)
                    current->release(1);
            }
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    ~Rva00522830Holder()
    {
        Rva00522830Counted *current = m_ptr;
        if (current)
        {
            if (--current->m_refCount <= 0)
                current->release(1);
        }
    }

private:
    Rva00522830Counted *m_ptr;
};

class Gen00522E00
{
public:
    void messageBoxHidden(int unused);

private:
    char m_lead[0x40];
    Rva00522830Holder m_40;
};

// ?messageBoxHidden@Gen00522E00@@QAEXH@Z
void Gen00522E00::messageBoxHidden(int)
{
    if (m_40)
    {
        m_40->apply(3);
        m_40 = 0;
    }
}
