// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};

class DefaultModuleTemplate7CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate7Concrete_vtbl0;
extern "C" char DefaultModuleTemplate7Concrete_vtbl4;
extern "C" char DefaultModuleTemplate7Concrete_vtbl8;

class DefaultModuleTemplate7Allocation
{
public:
	DefaultModuleTemplate7Allocation()
	{
		((DefaultModuleTemplate7CtorShim *)this)->construct();
		*(void **)((char *)this + 0) = &DefaultModuleTemplate7Concrete_vtbl0;
		*(void **)((char *)this + 4) = &DefaultModuleTemplate7Concrete_vtbl4;
		*(void **)((char *)this + 8) = &DefaultModuleTemplate7Concrete_vtbl8;
	}

private:
	unsigned char bytes_[0x50];
};

template<class Tag>
class ConcreteModuleClass
{
public:
	virtual DefaultModuleTemplate<7> *createTemplate() const;
};

template<class Tag>
DefaultModuleTemplate<7> *ConcreteModuleClass<Tag>::createTemplate() const
{
	return (DefaultModuleTemplate<7> *)new DefaultModuleTemplate7Allocation;
}

template class ConcreteModuleClass<DefaultModuleTag<7> >;

}
