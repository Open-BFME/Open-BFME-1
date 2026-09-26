// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTag<0> ConcreteModuleTemplate::clone
// Retail: new(0x98); copy-ctor; return.

namespace FXParticleSystem
{

template <int N>
class DefaultModuleTag
{
};

template <int N>
class DefaultModuleTemplate
{
public:
	virtual ~DefaultModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<DefaultModuleTag<0> > : public DefaultModuleTemplate<0>
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual DefaultModuleTemplate<0> *clone() const;

private:
	unsigned char m_pad[0x94];
};

DefaultModuleTemplate<0> *ConcreteModuleTemplate<DefaultModuleTag<0> >::clone() const
{
	return new ConcreteModuleTemplate<DefaultModuleTag<0> >(*this);
}

}
