// cl: /O2
// Authentic scalar-deleting destructors for identified Behavior ModuleData
// classes. Each retail wrapper sits 48 bytes before its already-matched
// destructor and is the unique 30-byte ??_G that calls that destructor.

#define DECLARE_MODULE_DELETING_DESTRUCTOR(ModuleName) \
    class ModuleName { public: virtual ~ModuleName(); }; \
    ModuleName *Make##ModuleName() { return new ModuleName; } \
    void Delete##ModuleName(ModuleName *object) { delete object; }

DECLARE_MODULE_DELETING_DESTRUCTOR(ClearanceTestingSlowDeathBehaviorModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(GiantBirdSlowDeathBehaviorModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(PassiveAreaEffectBehaviorModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(EnragedBehaviorModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(ShareExperienceBehaviorModuleData)
