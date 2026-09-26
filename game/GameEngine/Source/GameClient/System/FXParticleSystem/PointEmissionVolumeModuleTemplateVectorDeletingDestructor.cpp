// cl: /O2
// BFME PointEmissionVolumeModuleTemplate vector-deleting destructor at retail
// RVA 0x005D59E0. The scalar destructor is matched at 0x005D58F0 and this
// wrapper reaches it through ILT 0x00041F56.

void operator delete[](void *block);

namespace FXParticleSystem
{
class PointEmissionVolumeModuleTemplate
{
public:
	virtual ~PointEmissionVolumeModuleTemplate();

private:
	unsigned char m_data[0x0c];
};

PointEmissionVolumeModuleTemplate *MakePointEmissionVolumeModuleTemplateArray()
{
	return new PointEmissionVolumeModuleTemplate[2];
}

void DeletePointEmissionVolumeModuleTemplateArray(PointEmissionVolumeModuleTemplate *array)
{
	delete[] array;
}
}
