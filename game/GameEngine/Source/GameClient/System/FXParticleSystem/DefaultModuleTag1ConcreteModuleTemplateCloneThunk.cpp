// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTag<2> ConcreteModuleTemplate::clone
// Retail: new(0x4c); copy-ctor; return.

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
class ConcreteModuleTemplate<DefaultModuleTag<2> > : public DefaultModuleTemplate<2>
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual DefaultModuleTemplate<2> *clone() const;

private:
	unsigned char m_pad[0x48];
};

DefaultModuleTemplate<2> *ConcreteModuleTemplate<DefaultModuleTag<2> >::clone() const
{
	return new ConcreteModuleTemplate<DefaultModuleTag<2> >(*this);
}

}
