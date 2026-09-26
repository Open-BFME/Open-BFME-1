// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};

class DefaultModuleTemplate3CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate3Concrete_vtbl0;
extern "C" char DefaultModuleTemplate3Concrete_vtbl4;
extern "C" char DefaultModuleTemplate3Concrete_vtbl8;

class DefaultModuleTemplate3Allocation
{
public:
	DefaultModuleTemplate3Allocation()
	{
		((DefaultModuleTemplate3CtorShim *)this)->construct();
		*(void **)((char *)this + 0) = &DefaultModuleTemplate3Concrete_vtbl0;
		*(void **)((char *)this + 4) = &DefaultModuleTemplate3Concrete_vtbl4;
		*(void **)((char *)this + 8) = &DefaultModuleTemplate3Concrete_vtbl8;
	}

private:
	unsigned char bytes_[0x28];
};

template<class Tag>
class ConcreteModuleClass
{
public:
	virtual DefaultModuleTemplate<3> *createTemplate() const;
};

template<class Tag>
DefaultModuleTemplate<3> *ConcreteModuleClass<Tag>::createTemplate() const
{
	return (DefaultModuleTemplate<3> *)new DefaultModuleTemplate3Allocation;
}

template class ConcreteModuleClass<DefaultModuleTag<3> >;

}
