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
	virtual DefaultModuleTemplate<0> *createTemplate(INI *) const;
};

template<class Tag>
DefaultModuleTemplate<0> *ConcreteModuleClass<Tag>::createTemplate(INI *ini) const
{
	DefaultModuleTemplate<0> *result = (DefaultModuleTemplate<0> *)
		new DefaultModuleTemplate0Allocation;
	struct ParseScope {
		ParseScope(DefaultModuleTemplate<0> *value) : value_(value) {}
		~ParseScope() { if (value_) operator delete(value_); }
		DefaultModuleTemplate<0> *value_;
	} scope(result);
	result->parse(ini);
	scope.value_ = 0;
	return result;
}

template class ConcreteModuleClass<DefaultModuleTag<0> >;
}
