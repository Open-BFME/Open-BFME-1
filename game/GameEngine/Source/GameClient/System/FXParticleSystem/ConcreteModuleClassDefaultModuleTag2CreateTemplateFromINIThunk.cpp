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
	virtual DefaultModuleTemplate<3> *createTemplate(INI *) const;
};

template<class Tag>
DefaultModuleTemplate<3> *ConcreteModuleClass<Tag>::createTemplate(INI *ini) const
{
	DefaultModuleTemplate<3> *result = (DefaultModuleTemplate<3> *)
		new DefaultModuleTemplate3Allocation;
	struct ParseScope
	{
		ParseScope(DefaultModuleTemplate<3> *value) : value_(value) {}
		~ParseScope() { if (value_) operator delete(value_); }
		DefaultModuleTemplate<3> *value_;
	} scope(result);
	result->parse(ini);
	scope.value_ = 0;
	return result;
}

template class ConcreteModuleClass<DefaultModuleTag<3> >;

}
