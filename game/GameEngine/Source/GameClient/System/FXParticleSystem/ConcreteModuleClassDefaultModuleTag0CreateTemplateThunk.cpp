// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};

class DefaultModuleTemplate1CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate1Concrete_vtbl0;
extern "C" char DefaultModuleTemplate1Concrete_vtbl4;
extern "C" char DefaultModuleTemplate1Concrete_vtbl8;

class DefaultModuleTemplate1Allocation
{
public:
	DefaultModuleTemplate1Allocation()
	{
		((DefaultModuleTemplate1CtorShim *)this)->construct();
		*(void **)((char *)this + 0) = &DefaultModuleTemplate1Concrete_vtbl0;
		*(void **)((char *)this + 4) = &DefaultModuleTemplate1Concrete_vtbl4;
		*(void **)((char *)this + 8) = &DefaultModuleTemplate1Concrete_vtbl8;
	}

private:
	unsigned char bytes_[0x8C];
};

template<class Tag>
class ConcreteModuleClass
{
public:
	virtual DefaultModuleTemplate<1> *createTemplate() const;
};

template<class Tag>
DefaultModuleTemplate<1> *ConcreteModuleClass<Tag>::createTemplate() const
{
	return (DefaultModuleTemplate<1> *)new DefaultModuleTemplate1Allocation;
}

template class ConcreteModuleClass<DefaultModuleTag<1> >;

}
