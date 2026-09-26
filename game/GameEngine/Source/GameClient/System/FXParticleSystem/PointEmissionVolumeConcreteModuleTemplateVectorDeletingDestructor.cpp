// cl: /O2
// Retail RVA 0x005DBF70. Scalar destructor ILT 0x00013D40 routes to the
// matched ConcreteModuleTemplate<PointEmissionVolumeModuleTag> destructor at 0x005DBEA0.
void operator delete[](void *block);

namespace FXParticleSystem
{
struct PointEmissionVolumeModuleTag;

template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x0C];
};

typedef ConcreteModuleTemplate<PointEmissionVolumeModuleTag> PointVolumeTemplate;

PointVolumeTemplate *MakePointVolumeTemplateArray()
{
    return new PointVolumeTemplate[2];
}

void DeletePointVolumeTemplateArray(PointVolumeTemplate *array)
{
    delete[] array;
}
}
