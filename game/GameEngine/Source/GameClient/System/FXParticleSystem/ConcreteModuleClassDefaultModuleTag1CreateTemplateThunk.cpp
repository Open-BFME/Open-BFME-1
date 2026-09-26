// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

template<int Category> class DefaultModuleTag {};
template<int Category> class DefaultModuleTemplate {};

class DefaultModuleTemplate2CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate2Concrete_vtbl0;
extern "C" char DefaultModuleTemplate2Concrete_vtbl4;
extern "C" char DefaultModuleTemplate2Concrete_vtbl8;

class DefaultModuleTemplate2Allocation
{
public:
	DefaultModuleTemplate2Allocation()
	{
		((DefaultModuleTemplate2CtorShim *)this)->construct();
		*(void **)((char *)this + 0) = &DefaultModuleTemplate2Concrete_vtbl0;
		*(void **)((char *)this + 4) = &DefaultModuleTemplate2Concrete_vtbl4;
		*(void **)((char *)this + 8) = &DefaultModuleTemplate2Concrete_vtbl8;
	}

private:
	unsigned char bytes_[0x4C];
};

template<class Tag>
class ConcreteModuleClass
{
public:
	virtual DefaultModuleTemplate<2> *createTemplate() const;
};

template<class Tag>
DefaultModuleTemplate<2> *ConcreteModuleClass<Tag>::createTemplate() const
{
	return (DefaultModuleTemplate<2> *)new DefaultModuleTemplate2Allocation;
}

template class ConcreteModuleClass<DefaultModuleTag<2> >;

}
