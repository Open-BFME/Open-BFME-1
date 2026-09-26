// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class INI;

namespace FXParticleSystem
{

void __cdecl operator delete(void *);
template<int Category> class DefaultModuleTag {};

template<int Category>
class DefaultModuleTemplate
{
public:
	void parse(INI *ini);
};

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
	virtual DefaultModuleTemplate<2> *createTemplate(INI *) const;
};

template<class Tag>
DefaultModuleTemplate<2> *ConcreteModuleClass<Tag>::createTemplate(INI *ini) const
{
	DefaultModuleTemplate<2> *result = (DefaultModuleTemplate<2> *)
		new DefaultModuleTemplate2Allocation;
	struct ParseScope
	{
		ParseScope(DefaultModuleTemplate<2> *value) : value_(value) {}
		~ParseScope() { if (value_) operator delete(value_); }
		DefaultModuleTemplate<2> *value_;
	} scope(result);
	result->parse(ini);
	scope.value_ = 0;
	return result;
}

template class ConcreteModuleClass<DefaultModuleTag<2> >;

}
