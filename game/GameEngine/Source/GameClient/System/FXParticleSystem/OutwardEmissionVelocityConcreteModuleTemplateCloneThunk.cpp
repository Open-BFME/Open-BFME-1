// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: OutwardEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct OutwardEmissionVelocityModuleTag
{
};

class OutwardEmissionVelocityModuleTemplate
{
public:
	virtual ~OutwardEmissionVelocityModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<OutwardEmissionVelocityModuleTag> : public OutwardEmissionVelocityModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual OutwardEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x20];
};

// ?clone@?$ConcreteModuleTemplate@UOutwardEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVOutwardEmissionVelocityModuleTemplate@2@XZ
OutwardEmissionVelocityModuleTemplate *ConcreteModuleTemplate<OutwardEmissionVelocityModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<OutwardEmissionVelocityModuleTag>(*this);
}

}
