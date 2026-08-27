// Open-BFME: functor-binding invoker reconstructed from retail RVA 0x00192120.
// The layout follows the byte-verified functor invoker family: a polymorphic
// two-dword head followed by a multiple-inheritance pointer-to-member binding.

class __multiple_inheritance Rva00192120FunctorTarget;

typedef void (Rva00192120FunctorTarget::*Rva00192120FunctorMethod)(void);

class Rva00192120FunctorHead
{
public:
    virtual void anchor();

    unsigned int m_unmodelled_04;
    unsigned int m_unmodelled_08;
};

class Rva00192120FunctorInvoker : public Rva00192120FunctorHead
{
public:
    void invoke(void);

    Rva00192120FunctorTarget *m_target;
    Rva00192120FunctorMethod   m_method;
};

void Rva00192120FunctorInvoker::invoke(void)
{
    (m_target->*m_method)();
}
