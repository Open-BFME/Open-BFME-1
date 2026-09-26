// cl: /O2
// Authentic scalar-deleting destructors for identified Update ModuleData
// classes. Each retail wrapper sits 48 bytes before its already-matched
// destructor and is the unique 30-byte ??_G that calls that destructor.

#define DECLARE_MODULE_DELETING_DESTRUCTOR(ModuleName) \
    class ModuleName { public: virtual ~ModuleName(); }; \
    ModuleName *Make##ModuleName() { return new ModuleName; } \
    void Delete##ModuleName(ModuleName *object) { delete object; }

DECLARE_MODULE_DELETING_DESTRUCTOR(RousingSpeechUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(AttributeModifierAuraUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(AutoPickUpUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(BoneFXUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(BroadcastStealthUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(CivilianSpawnUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(DynamicShroudClearingRangeUpdateModuleData)
DECLARE_MODULE_DELETING_DESTRUCTOR(PartTheHeavensUpdateModuleData)
