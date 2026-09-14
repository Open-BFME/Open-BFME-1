// cl: /O2
// Authentic scalar-deleting destructors for the five emission-volume modules.
// Each retail wrapper calls the corresponding already-identified destructor ILT.
namespace FXParticleSystem
{
#define DECLARE_MODULE_DELETING_DESTRUCTOR(ModuleName) \
    class ModuleName { public: virtual ~ModuleName(); }; \
    ModuleName *Make##ModuleName() { return new ModuleName; } \
    void Delete##ModuleName(ModuleName *object) { delete object; }

DECLARE_MODULE_DELETING_DESTRUCTOR(PointEmissionVolumeModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(LineEmissionVolumeModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(BoxEmissionVolumeModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(SphereEmissionVolumeModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(CylinderEmissionVolumeModule)
}
