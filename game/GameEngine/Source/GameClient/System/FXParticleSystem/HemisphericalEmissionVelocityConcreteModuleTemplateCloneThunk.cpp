// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: HemisphericalEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct HemisphericalEmissionVelocityModuleTag
{
};

class HemisphericalEmissionVelocityModuleTemplate
{
public:
	virtual ~HemisphericalEmissionVelocityModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag> : public HemisphericalEmissionVelocityModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual HemisphericalEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x14];
};

// ?clone@?$ConcreteModuleTemplate@UHemisphericalEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVHemisphericalEmissionVelocityModuleTemplate@2@XZ
HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag>(*this);
}

}
