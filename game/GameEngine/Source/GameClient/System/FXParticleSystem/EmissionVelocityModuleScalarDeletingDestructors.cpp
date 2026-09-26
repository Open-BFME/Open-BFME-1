// cl: /O2
// Authentic scalar-deleting destructors for identified emission-velocity modules.
// Each retail wrapper calls the corresponding already-identified destructor ILT.
namespace FXParticleSystem
{
#define DECLARE_MODULE_DELETING_DESTRUCTOR(ModuleName) \
    class ModuleName { public: virtual ~ModuleName(); }; \
    ModuleName *Make##ModuleName() { return new ModuleName; } \
    void Delete##ModuleName(ModuleName *object) { delete object; }

DECLARE_MODULE_DELETING_DESTRUCTOR(OrthoEmissionVelocityModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(SphericalEmissionVelocityModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(HemisphericalEmissionVelocityModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(CylindricalEmissionVelocityModule)
DECLARE_MODULE_DELETING_DESTRUCTOR(OutwardEmissionVelocityModule)
}
