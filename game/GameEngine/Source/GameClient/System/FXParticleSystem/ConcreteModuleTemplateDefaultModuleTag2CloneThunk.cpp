// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTag<3> ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DefaultModuleTemplate3CopyCtorShim
{
public:
    void construct(const void *source);
};

extern "C" char DefaultModuleTemplate3Concrete_vtbl0;
extern "C" char DefaultModuleTemplate3Concrete_vtbl4;
extern "C" char DefaultModuleTemplate3Concrete_vtbl8;

class DefaultModuleTemplate3Allocation
{
public:
    __forceinline DefaultModuleTemplate3Allocation(const void *source)
    {
        ((DefaultModuleTemplate3CopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &DefaultModuleTemplate3Concrete_vtbl0;
        *(void **)((char *)this + 4) = &DefaultModuleTemplate3Concrete_vtbl4;
        *(void **)((char *)this + 8) = &DefaultModuleTemplate3Concrete_vtbl8;
    }
private:
    unsigned char m_bytes[0x28];
};

template<class Tag>
class ConcreteModuleTemplate
{
public:
    virtual DefaultModuleTemplate<3> *clone() const;
};

template<class Tag>
DefaultModuleTemplate<3> *ConcreteModuleTemplate<Tag>::clone() const
{
    return (DefaultModuleTemplate<3> *)new DefaultModuleTemplate3Allocation(this);
}

template class ConcreteModuleTemplate<DefaultModuleTag<3> >;
}
