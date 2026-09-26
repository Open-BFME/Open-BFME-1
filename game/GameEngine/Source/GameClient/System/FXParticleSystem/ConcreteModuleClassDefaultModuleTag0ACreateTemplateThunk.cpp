// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{
template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};

class DefaultModuleTemplate0CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate0Concrete_vtbl0;
extern "C" char DefaultModuleTemplate0Concrete_vtbl4;
extern "C" char DefaultModuleTemplate0Concrete_vtbl8;

class DefaultModuleTemplate0Allocation
{
public:
	DefaultModuleTemplate0Allocation()
	{
		((DefaultModuleTemplate0CtorShim *)this)->construct();
		*(void **)((char *)this + 0) = &DefaultModuleTemplate0Concrete_vtbl0;
		*(void **)((char *)this + 4) = &DefaultModuleTemplate0Concrete_vtbl4;
		*(void **)((char *)this + 8) = &DefaultModuleTemplate0Concrete_vtbl8;
	}
private:
	unsigned char bytes_[0x98];
};

template<class Tag>
class ConcreteModuleClass
{
public:
	virtual DefaultModuleTemplate<0> *createTemplate() const;
};

template<class Tag>
DefaultModuleTemplate<0> *ConcreteModuleClass<Tag>::createTemplate() const
{
	return (DefaultModuleTemplate<0> *)new DefaultModuleTemplate0Allocation;
}

template class ConcreteModuleClass<DefaultModuleTag<0> >;
}
