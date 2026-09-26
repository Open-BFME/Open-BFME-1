// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTag<1> ConcreteModuleTemplate::clone
// Retail: new(0x8c); copy-ctor; return.

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
class ConcreteModuleTemplate<DefaultModuleTag<1> > : public DefaultModuleTemplate<1>
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual DefaultModuleTemplate<1> *clone() const;

private:
	unsigned char m_pad[0x88];
};

DefaultModuleTemplate<1> *ConcreteModuleTemplate<DefaultModuleTag<1> >::clone() const
{
	return new ConcreteModuleTemplate<DefaultModuleTag<1> >(*this);
}

}
