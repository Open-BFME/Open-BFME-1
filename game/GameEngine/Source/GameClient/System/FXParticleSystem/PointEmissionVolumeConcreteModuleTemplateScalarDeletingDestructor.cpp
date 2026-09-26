// cl: /O2
// Retail RVA 0x005DBF40. Destructor ILT 0x00013D40 routes directly to the
// matched ConcreteModuleTemplate<PointEmissionVolumeModuleTag> destructor at
// 0x005DBEA0.
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

PointVolumeTemplate *MakePointVolumeTemplate() { return new PointVolumeTemplate; }
void DeletePointVolumeTemplate(PointVolumeTemplate *object) { delete object; }
}
