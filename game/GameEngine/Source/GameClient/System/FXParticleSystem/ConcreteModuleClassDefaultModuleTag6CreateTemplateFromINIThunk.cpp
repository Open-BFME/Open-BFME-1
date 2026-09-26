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
	virtual DefaultModuleTemplate<7> *createTemplate(INI *) const;
};

template<class Tag>
DefaultModuleTemplate<7> *ConcreteModuleClass<Tag>::createTemplate(INI *ini) const
{
	DefaultModuleTemplate<7> *result = (DefaultModuleTemplate<7> *)
		new DefaultModuleTemplate7Allocation;
	struct ParseScope
	{
		ParseScope(DefaultModuleTemplate<7> *value) : value_(value) {}
		~ParseScope() { if (value_) operator delete(value_); }
		DefaultModuleTemplate<7> *value_;
	} scope(result);
	result->parse(ini);
	scope.value_ = 0;
	return result;
}

template class ConcreteModuleClass<DefaultModuleTag<7> >;

}
