// cl: /O2
// Retail RVA 0x005DB7B0. Scalar destructor ILT 0x00043A8B routes to the
// matched ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> destructor at 0x005DB6F0.
void operator delete[](void *block);

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

OrthoVelocityTemplate *MakeOrthoVelocityTemplateArray()
{
    return new OrthoVelocityTemplate[2];
}

void DeleteOrthoVelocityTemplateArray(OrthoVelocityTemplate *array)
{
    delete[] array;
}
}
