// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: OrthoEmissionVelocity ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct OrthoEmissionVelocityModuleTag
{
};

class OrthoEmissionVelocityModuleTemplate
{
public:
	virtual ~OrthoEmissionVelocityModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> : public OrthoEmissionVelocityModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual OrthoEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x2c];
};

// ?clone@?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVOrthoEmissionVelocityModuleTemplate@2@XZ
OrthoEmissionVelocityModuleTemplate *ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>(*this);
}

}
