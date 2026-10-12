// cl: /O2 /MD
//
// Address-qualified incremental-link tail thunks.  Their independently
// matched destinations establish the jump routes; the no-argument forwarding
// declarations preserve the real receiver and arguments on the caller stack.

extern void rva0000EF5CTarget(void);
extern void PopulateLobbyPlayerListbox(void); // ILT 0x000070B3 destination, called directly
extern void rva000078E7Target(void);
extern void rva0000CC3ETarget(void);
extern void rva0000A47ATarget(void);
extern void rva0000DFBCTarget(void);
extern void rva0000E43ATarget(void);
extern void rva00010B2CTarget(void);
extern void rva00011E87Target(void);
extern void rva00014470Target(void);
extern void rva000119E1Target(void);
extern void rva00011B76Target(void);
extern void rva00022683Target(void);
extern void rva0002F095Target(void);
extern void rva000399A5Target(void);
extern void rva0003D7B2Target(void);

extern void rva00016595Target(void);
extern void rva00033479Target(void);
extern void rva00006B4ATarget(void);
extern void rva000124AETarget(void);
extern void rva0000B686Target(void);
extern void rva00011F1DTarget(void);
extern void rva0001361FTarget(void);
extern void rva00014088Target(void);
extern void rva00026684Target(void);
extern void rva0002969FTarget(void);
extern void rva0002C34FTarget(void);
extern void rva00032867Target(void);
extern void rva00036458Target(void);
extern void rva00037F4CTarget(void);
extern void rva00044BFCTarget(void);
extern void rva0004B0F1Target(void);
#pragma comment(linker, "/alternatename:?rva0000EF5CTarget@@YAXXZ=??0PropagandaTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z")

#pragma comment(linker, "/alternatename:?rva000078E7Target@@YAXXZ=??$__copy@PBVProductionPrerequisite@@PAV1@H@_STL@@YAPAVProductionPrerequisite@@PBV1@0PAV1@ABUrandom_access_iterator_tag@0@PAH@Z")
#pragma comment(linker, "/alternatename:?rva0000CC3ETarget@@YAXXZ=??0FlightDeckBehaviorModuleData@@QAE@XZ")
#pragma comment(linker, "/alternatename:?rva0000A47ATarget@@YAXXZ=?_M_insert_overflow@?$vector@UFlightDeckInfo@FlightDeckBehavior@@V?$allocator@UFlightDeckInfo@FlightDeckBehavior@@@_STL@@@_STL@@IAEXPAUFlightDeckInfo@FlightDeckBehavior@@ABU34@ABU__false_type@2@I_N@Z")
#pragma comment(linker, "/alternatename:?rva0000DFBCTarget@@YAXXZ=??0StatusBitsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z")
#pragma comment(linker, "/alternatename:?rva0000E43ATarget@@YAXXZ=?messageCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPRecvBuddyMessageArg@@@Z")
#pragma comment(linker, "/alternatename:?rva00010B2CTarget@@YAXXZ=??0PropagandaTowerBehaviorModuleData@@QAE@XZ")
#pragma comment(linker, "/alternatename:?rva00011E87Target@@YAXXZ=??$_M_insert_dispatch@U?$_List_iterator@UCoord3D@@U?$_Const_traits@UCoord3D@@@_STL@@@_STL@@@?$list@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXU?$_List_iterator@UCoord3D@@U?$_Nonconst_traits@UCoord3D@@@_STL@@@1@U?$_List_iterator@UCoord3D@@U?$_Const_traits@UCoord3D@@@_STL@@@1@1ABU__false_type@1@@Z")
#pragma comment(linker, "/alternatename:?rva00014470Target@@YAXXZ=??$_M_allocate_and_copy@PBUPrereqUnitRec@ProductionPrerequisite@@@?$vector@UPrereqUnitRec@ProductionPrerequisite@@V?$allocator@UPrereqUnitRec@ProductionPrerequisite@@@_STL@@@_STL@@IAEPAUPrereqUnitRec@ProductionPrerequisite@@IPBU23@0@Z")
#pragma comment(linker, "/alternatename:?rva000119E1Target@@YAXXZ=?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z")
#pragma comment(linker, "/alternatename:?rva00011B76Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00022683Target@@YAXXZ=?readDict@DataChunkInput@@QAE?AVDict@@XZ")
#pragma comment(linker, "/alternatename:?rva0002F095Target@@YAXXZ=?copy@UnsignedPairTreeCopyShim@_STL@@QAEPAU?$_Rb_tree_node@U?$pair@$$CBGE@_STL@@@2@PAU32@0@Z")
#pragma comment(linker, "/alternatename:?rva000399A5Target@@YAXXZ=?setOrientation@Thing@@QAEXM@Z")
#pragma comment(linker, "/alternatename:?rva0003D7B2Target@@YAXXZ=?_M_insert_overflow@?$vector@UWeaponBarrelInfo@ModelConditionInfo@@V?$allocator@UWeaponBarrelInfo@ModelConditionInfo@@@_STL@@@_STL@@IAEXPAUWeaponBarrelInfo@ModelConditionInfo@@ABU34@ABU__false_type@2@I_N@Z")
#pragma comment(linker, "/alternatename:?rva00016595Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00033479Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00006B4ATarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva000124AETarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva0000B686Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00011F1DTarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva0001361FTarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00014088Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00026684Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva0002969FTarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva0002C34FTarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00032867Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00036458Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00037F4CTarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva00044BFCTarget@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")
#pragma comment(linker, "/alternatename:?rva0004B0F1Target@@YAXXZ=?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ")

void j_0000EF5C(void)
{
	rva0000EF5CTarget();
}

void j_000070B3(void)
{
	PopulateLobbyPlayerListbox();
}

void j_000078E7(void)
{
	rva000078E7Target();
}

void j_0000CC3E(void)
{
	rva0000CC3ETarget();
}

void j_0000A47A(void)
{
	rva0000A47ATarget();
}

void j_0000DFBC(void)
{
	rva0000DFBCTarget();
}

void j_0000E43A(void)
{
	rva0000E43ATarget();
}

void j_00010B2C(void)
{
	rva00010B2CTarget();
}

void j_00011E87(void)
{
	rva00011E87Target();
}

void j_00014470(void)
{
	rva00014470Target();
}

void j_000119E1(void)
{
	rva000119E1Target();
}

void j_00011B76(void)
{
	rva00011B76Target();
}

void j_00022683(void)
{
	rva00022683Target();
}

void j_000399A5(void)
{
	rva000399A5Target();
}

void j_0003D7B2(void)
{
	rva0003D7B2Target();
}

void j_0002F095(void)
{
	rva0002F095Target();
}

void j_00016595(void)
{
	rva00016595Target();
}

void j_00033479(void)
{
	rva00033479Target();
}

void j_00006B4A(void)
{
	rva00006B4ATarget();
}

void j_000124AE(void)
{
	rva000124AETarget();
}

void j_0000B686(void)
{
	rva0000B686Target();
}

void j_00011F1D(void)
{
	rva00011F1DTarget();
}

void j_0001361F(void)
{
	rva0001361FTarget();
}

void j_00014088(void)
{
	rva00014088Target();
}

void j_00026684(void)
{
	rva00026684Target();
}

void j_0002969F(void)
{
	rva0002969FTarget();
}

void j_0002C34F(void)
{
	rva0002C34FTarget();
}

void j_00032867(void)
{
	rva00032867Target();
}

void j_00036458(void)
{
	rva00036458Target();
}

void j_00037F4C(void)
{
	rva00037F4CTarget();
}

void j_00044BFC(void)
{
	rva00044BFCTarget();
}

void j_0004B0F1(void)
{
	rva0004B0F1Target();
}
