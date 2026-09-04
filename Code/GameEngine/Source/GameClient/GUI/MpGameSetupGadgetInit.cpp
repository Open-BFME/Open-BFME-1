// Retail 0x00527050: MpGameSetup::GadgetInit.
// The callback is the single-inheritance 16-byte functor wrapper family.

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();

    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
};

class __single_inheritance FunctorTargetSingle
{
};
typedef void (FunctorTargetSingle::*FunctorMethodSingle)(void);

struct FunctorBindingSingle
{
    FunctorBindingSingle(FunctorMethodSingle method,
        FunctorTargetSingle *target)
        : m_target(target), m_method(method) {}

    FunctorTargetSingle *m_target;
    FunctorMethodSingle m_method;
};

class FunctorSingleWrapperHead
{
public:
    FunctorSingleWrapperHead() : m_refCount(0) {}
    virtual void anchor();

    unsigned int m_refCount;
};

class Rva00525A30FunctorSingleWrapper : public FunctorSingleWrapperHead
{
public:
    Rva00525A30FunctorSingleWrapper(const FunctorBindingSingle &binding)
        : m_binding(binding) {}

    FunctorBindingSingle m_binding;
};

class Rva0050F840FunctorHolder
{
public:
    Rva0050F840FunctorHolder(FunctorBindingSingle binding)
    {
        m_ptr = new Rva00525A30FunctorSingleWrapper(binding);
        if (m_ptr != 0)
            m_ptr->m_refCount++;
    }

    Rva0050F840FunctorHolder(
        const Rva0050F840FunctorHolder &other)
        : m_ptr(other.m_ptr) {}

    ~Rva0050F840FunctorHolder() {}

private:
    Rva00525A30FunctorSingleWrapper *m_ptr;
};

void EnableSlotListUpdates(bool enabled);
void _bfme_setAptScreenRef(const AsciiString &name,
    Rva0050F840FunctorHolder callback);

extern void j_00021cfb();

class AptMapPreview
{
public:
    void initGadgets()
    {
        union
        {
            void (*raw)(void);
            void (AptMapPreview::*member)(void);
        } call;
        call.raw = j_00021cfb;
        (this->*call.member)();
    }
};

class MpGameSetup : public FunctorTargetSingle
{
public:
    void GadgetInit();

private:
    unsigned char m_unmodelled[0x28];
    AptMapPreview m_mapPreview;
};

// ?GadgetInit@MpGameSetup@@QAEXXZ
void MpGameSetup::GadgetInit()
{
    union
    {
        void (*raw)(void);
        FunctorMethodSingle member;
    } callback;
    callback.raw = (void (*)(void))0x44529B;
    MpGameSetup *self = this;
    EnableSlotListUpdates(false);
    {
        AsciiString name("MpGameSetup::GadgetInit");
        _bfme_setAptScreenRef(name,
            Rva0050F840FunctorHolder(
                FunctorBindingSingle(callback.member, self)));
    }
    self->m_mapPreview.initGadgets();
}
