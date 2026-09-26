// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTag<6> ConcreteModuleTemplate::clone
// Retail: new(0x0c); copy-ctor; return.

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
class ConcreteModuleTemplate<DefaultModuleTag<6> > : public DefaultModuleTemplate<6>
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual DefaultModuleTemplate<6> *clone() const;

private:
	unsigned char m_pad[0x8];
};

DefaultModuleTemplate<6> *ConcreteModuleTemplate<DefaultModuleTag<6> >::clone() const
{
	return new ConcreteModuleTemplate<DefaultModuleTag<6> >(*this);
}

}
