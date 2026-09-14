// cl: /O2
// Authentic scalar-deleting destructors for identified Upgrade ModuleData
// classes. Each retail wrapper sits 48 bytes before its already-matched
// destructor and is the unique 30-byte ??_G that calls that destructor.

#define DECLARE_MODULE_DELETING_DESTRUCTOR(ModuleName) \
    class ModuleName { public: virtual ~ModuleName(); }; \
    ModuleName *Make##ModuleName() { return new ModuleName; } \
    void Delete##ModuleName(ModuleName *object) { delete object; }

DECLARE_MODULE_DELETING_DESTRUCTOR(ProductionSpeedBonusModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(BaseUpgradeModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(CostModifierUpgradeModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(ExperienceScalarUpgradeModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(GeometryUpgradeModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(ObjectCreationUpgradeModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(UnpauseSpecialPowerUpgradeModuleData)
