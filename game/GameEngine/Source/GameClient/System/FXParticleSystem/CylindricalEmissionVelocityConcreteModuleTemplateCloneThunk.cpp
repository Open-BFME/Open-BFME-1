// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CylindricalEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct CylindricalEmissionVelocityModuleTag
{
};

class CylindricalEmissionVelocityModuleTemplate
{
public:
	virtual ~CylindricalEmissionVelocityModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<CylindricalEmissionVelocityModuleTag> : public CylindricalEmissionVelocityModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual CylindricalEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x20];
};

// ?clone@?$ConcreteModuleTemplate@UCylindricalEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylindricalEmissionVelocityModuleTemplate@2@XZ
CylindricalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<CylindricalEmissionVelocityModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<CylindricalEmissionVelocityModuleTag>(*this);
}

}
