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
	virtual DefaultModuleTemplate<6> *createTemplate(INI *) const;
};

template<class Tag>
DefaultModuleTemplate<6> *ConcreteModuleClass<Tag>::createTemplate(INI *ini) const
{
	DefaultModuleTemplate<6> *result = (DefaultModuleTemplate<6> *)
		new DefaultModuleTemplate6Allocation;
	struct ParseScope
	{
		ParseScope(DefaultModuleTemplate<6> *value) : value_(value) {}
		~ParseScope() { if (value_) operator delete(value_); }
		DefaultModuleTemplate<6> *value_;
	} scope(result);
	result->parse(ini);
	scope.value_ = 0;
	return result;
}

template class ConcreteModuleClass<DefaultModuleTag<6> >;

}
