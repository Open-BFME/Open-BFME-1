// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};

class DefaultModuleTemplate6CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate6Concrete_vtbl0;
extern "C" char DefaultModuleTemplate6Concrete_vtbl4;
extern "C" char DefaultModuleTemplate6Concrete_vtbl8;

class DefaultModuleTemplate6Allocation
{
public:
	DefaultModuleTemplate6Allocation()
	{
		((DefaultModuleTemplate6CtorShim *)this)->construct();
		*(void **)((char *)this + 0) = &DefaultModuleTemplate6Concrete_vtbl0;
		*(void **)((char *)this + 4) = &DefaultModuleTemplate6Concrete_vtbl4;
		*(void **)((char *)this + 8) = &DefaultModuleTemplate6Concrete_vtbl8;
	}

private:
	unsigned char bytes_[0x0C];
};

template<class Tag>
class ConcreteModuleClass
{
public:
	virtual DefaultModuleTemplate<6> *createTemplate() const;
};

template<class Tag>
DefaultModuleTemplate<6> *ConcreteModuleClass<Tag>::createTemplate() const
{
	return (DefaultModuleTemplate<6> *)new DefaultModuleTemplate6Allocation;
}

template class ConcreteModuleClass<DefaultModuleTag<6> >;

}
