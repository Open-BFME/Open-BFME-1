// cl: /O2
// Retail RVA 0x005DB780. Destructor ILT 0x00043A8B routes directly to the
// matched ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> destructor at 0x005DB6F0.
namespace FXParticleSystem
{
struct OrthoEmissionVelocityModuleTag;

template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x2C];
};

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoVelocityTemplate;

OrthoVelocityTemplate *MakeOrthoVelocityTemplate()
{
    return new OrthoVelocityTemplate;
}

void DeleteOrthoVelocityTemplate(OrthoVelocityTemplate *object)
{
    delete object;
}
}
