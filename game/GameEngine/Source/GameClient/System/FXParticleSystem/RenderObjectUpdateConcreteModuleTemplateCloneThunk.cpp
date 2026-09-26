// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: RenderObjectUpdate ConcreteModuleTemplate::clone
// Retail: new(0xa0); copy-ctor; return.

namespace FXParticleSystem
{

struct RenderObjectUpdateModuleTag
{
};

class RenderObjectUpdateModuleTemplate
{
public:
	virtual ~RenderObjectUpdateModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<RenderObjectUpdateModuleTag> : public RenderObjectUpdateModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual RenderObjectUpdateModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x9c];
};

RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<RenderObjectUpdateModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<RenderObjectUpdateModuleTag>(*this);
}

}
