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
	virtual DefaultModuleTemplate<1> *createTemplate(INI *) const;
};

template<class Tag>
DefaultModuleTemplate<1> *ConcreteModuleClass<Tag>::createTemplate(INI *ini) const
{
	DefaultModuleTemplate<1> *result = (DefaultModuleTemplate<1> *)
		new DefaultModuleTemplate1Allocation;
	struct ParseScope
	{
		ParseScope(DefaultModuleTemplate<1> *value) : value_(value) {}
		~ParseScope() { if (value_) operator delete(value_); }
		DefaultModuleTemplate<1> *value_;
	} scope(result);
	result->parse(ini);
	scope.value_ = 0;
	return result;
}

template class ConcreteModuleClass<DefaultModuleTag<1> >;

}
