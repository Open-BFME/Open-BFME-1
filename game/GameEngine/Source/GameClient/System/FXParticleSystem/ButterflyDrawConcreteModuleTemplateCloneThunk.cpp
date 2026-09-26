// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ButterflyDraw ConcreteModuleTemplate::clone
// Retail: new(0x0c); copy-ctor; return.

namespace FXParticleSystem
{

struct ButterflyDrawModuleTag
{
};

class ButterflyDrawModuleTemplate
{
public:
	virtual ~ButterflyDrawModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<ButterflyDrawModuleTag> : public ButterflyDrawModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual ButterflyDrawModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x8];
};

// Mangled name matched via functions.csv claim for this source.
ButterflyDrawModuleTemplate *ConcreteModuleTemplate<ButterflyDrawModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<ButterflyDrawModuleTag>(*this);
}

}
