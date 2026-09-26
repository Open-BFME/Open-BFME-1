// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTag<7> ConcreteModuleTemplate::clone
// Retail: new(0x50); copy-ctor; return.

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
class ConcreteModuleTemplate<DefaultModuleTag<7> > : public DefaultModuleTemplate<7>
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual DefaultModuleTemplate<7> *clone() const;

private:
	unsigned char m_pad[0x4c];
};

DefaultModuleTemplate<7> *ConcreteModuleTemplate<DefaultModuleTag<7> >::clone() const
{
	return new ConcreteModuleTemplate<DefaultModuleTag<7> >(*this);
}

}
