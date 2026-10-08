// cl: /DNDEBUG /MD /EHs-c- /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: nineteen run-once latches, 0x005E83F0 through 0x005E8750, one
// every 0x30 bytes.
//
// The guard is the compiler's, not the source's: `mov cl,[g] / mov eax,1 /
// test al,cl / jne out / or [g],eax` is MSVC's function-local-static guard,
// which materialises 1 in eax so the same register serves the test and the
// set.  Hand-written flag code does not produce that pair; `if (!(g & 1))`
// compiles to `test byte ptr [g],1`.
//
// THE MISSING `mov ecx` IS THE WHOLE PUZZLE, AND ITS ANSWER IS INLINING.  A
// function-local static of class type normally loads the object's address
// into ecx before its constructor -- five bytes retail does not spend.  It is
// absent because the constructor is INLINE and never touches `this`: its
// whole body is one call, so MSVC inlines it and the object address is never
// needed.  Writing the constructor out-of-line instead lands the body at 43
// bytes with the `mov ecx` in front of the call.
//
// The destructor is inline and EMPTY, but user-declared, which is exactly
// what the bytes ask for: user-declared makes the type non-trivial so the
// static registers with atexit, and empty-and-inline makes the registered
// helper a bare `ret`.  Every one of the nineteen registers such a helper,
// and they sit at 0x00C706F0..0x00C70810 in descending order -- one per
// latch, in reverse declaration order, which is how MSVC lays them out.
//
// The guards are consecutive dwords from 0x00EF6C44 up, and the bodies are
// consecutive: nineteen statics of one translation unit, in declaration
// order.  That is why they are written as one file here.
//
// IDENTITY IS NOT RECOVERED.  Each latch is named for its own address and
// each initialiser for the ILT slot it is reached through.

// Each ILT slot jumps to the matched FXParticleSystem::ConcreteModuleClass<Tag>::getInstance
// body (ilt_oracle CONFIRMED); the old per-ILT names stay as forwarders.
#include "../GameClient/System/FXParticleSystem/fx_particle_system.h"

namespace FXParticleSystem
{
typedef ConcreteModuleClass<DefaultModuleTag<1> > S5LatchClass00015FB9;
typedef ConcreteModuleClass<DefaultModuleTag<0> > S5LatchClass0002969F;
typedef ConcreteModuleClass<DefaultModuleTag<3> > S5LatchClass00014088;
typedef ConcreteModuleClass<DefaultModuleTag<2> > S5LatchClass00011F1D;
typedef ConcreteModuleClass<DefaultModuleTag<7> > S5LatchClass00032867;
typedef ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > S5LatchClass00044BFC;
typedef ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > S5LatchClass00016595;
typedef ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > S5LatchClass000124AE;
typedef ConcreteModuleClass<OrthoEmissionVelocityModuleTag > S5LatchClass0000B686;
typedef ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > S5LatchClass000078A1;
typedef ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > S5LatchClass0004B0F1;
typedef ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > S5LatchClass0003D875;
typedef ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > S5LatchClass00036458;
typedef ConcreteModuleClass<PointEmissionVolumeModuleTag > S5LatchClass000101A9;
typedef ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > S5LatchClass00011B76;
typedef ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > S5LatchClass0001361F;
typedef ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > S5LatchClass00026058;
typedef ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > S5LatchClass00033479;
typedef ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > S5LatchClass000340FE;
}

#define bfmeInit00015FB9() FXParticleSystem::S5LatchClass00015FB9::getInstance()	// ILT 0x00015FB9
#define bfmeInit0002969F() FXParticleSystem::S5LatchClass0002969F::getInstance()	// ILT 0x0002969F
#define bfmeInit00014088() FXParticleSystem::S5LatchClass00014088::getInstance()	// ILT 0x00014088
#define bfmeInit00011F1D() FXParticleSystem::S5LatchClass00011F1D::getInstance()	// ILT 0x00011F1D
#define bfmeInit00032867() FXParticleSystem::S5LatchClass00032867::getInstance()	// ILT 0x00032867
#define bfmeInit00044BFC() FXParticleSystem::S5LatchClass00044BFC::getInstance()	// ILT 0x00044BFC
#define bfmeInit00016595() FXParticleSystem::S5LatchClass00016595::getInstance()	// ILT 0x00016595
#define bfmeInit000124AE() FXParticleSystem::S5LatchClass000124AE::getInstance()	// ILT 0x000124AE
#define bfmeInit0000B686() FXParticleSystem::S5LatchClass0000B686::getInstance()	// ILT 0x0000B686
#define bfmeInit000078A1() FXParticleSystem::S5LatchClass000078A1::getInstance()	// ILT 0x000078A1
#define bfmeInit0004B0F1() FXParticleSystem::S5LatchClass0004B0F1::getInstance()	// ILT 0x0004B0F1
#define bfmeInit0003D875() FXParticleSystem::S5LatchClass0003D875::getInstance()	// ILT 0x0003D875
#define bfmeInit00036458() FXParticleSystem::S5LatchClass00036458::getInstance()	// ILT 0x00036458
#define bfmeInit000101A9() FXParticleSystem::S5LatchClass000101A9::getInstance()	// ILT 0x000101A9
#define bfmeInit00011B76() FXParticleSystem::S5LatchClass00011B76::getInstance()	// ILT 0x00011B76
#define bfmeInit0001361F() FXParticleSystem::S5LatchClass0001361F::getInstance()	// ILT 0x0001361F
#define bfmeInit00026058() FXParticleSystem::S5LatchClass00026058::getInstance()	// ILT 0x00026058
#define bfmeInit00033479() FXParticleSystem::S5LatchClass00033479::getInstance()	// ILT 0x00033479
#define bfmeInit000340FE() FXParticleSystem::S5LatchClass000340FE::getInstance()	// ILT 0x000340FE

struct BfmeLatch005E83F0
{
	BfmeLatch005E83F0() { bfmeInit00015FB9(); }
	~BfmeLatch005E83F0() {}
};

struct BfmeLatch005E8420
{
	BfmeLatch005E8420() { bfmeInit0002969F(); }
	~BfmeLatch005E8420() {}
};

struct BfmeLatch005E8450
{
	BfmeLatch005E8450() { bfmeInit00014088(); }
	~BfmeLatch005E8450() {}
};

struct BfmeLatch005E8480
{
	BfmeLatch005E8480() { bfmeInit00011F1D(); }
	~BfmeLatch005E8480() {}
};

struct BfmeLatch005E84B0
{
	BfmeLatch005E84B0() { bfmeInit00032867(); }
	~BfmeLatch005E84B0() {}
};

struct BfmeLatch005E84E0
{
	BfmeLatch005E84E0() { bfmeInit00044BFC(); }
	~BfmeLatch005E84E0() {}
};

struct BfmeLatch005E8510
{
	BfmeLatch005E8510() { bfmeInit00016595(); }
	~BfmeLatch005E8510() {}
};

struct BfmeLatch005E8540
{
	BfmeLatch005E8540() { bfmeInit000124AE(); }
	~BfmeLatch005E8540() {}
};

struct BfmeLatch005E8570
{
	BfmeLatch005E8570() { bfmeInit0000B686(); }
	~BfmeLatch005E8570() {}
};

struct BfmeLatch005E85A0
{
	BfmeLatch005E85A0() { bfmeInit000078A1(); }
	~BfmeLatch005E85A0() {}
};

struct BfmeLatch005E85D0
{
	BfmeLatch005E85D0() { bfmeInit0004B0F1(); }
	~BfmeLatch005E85D0() {}
};

struct BfmeLatch005E8600
{
	BfmeLatch005E8600() { bfmeInit0003D875(); }
	~BfmeLatch005E8600() {}
};

struct BfmeLatch005E8630
{
	BfmeLatch005E8630() { bfmeInit00036458(); }
	~BfmeLatch005E8630() {}
};

struct BfmeLatch005E8660
{
	BfmeLatch005E8660() { bfmeInit000101A9(); }
	~BfmeLatch005E8660() {}
};

struct BfmeLatch005E8690
{
	BfmeLatch005E8690() { bfmeInit00011B76(); }
	~BfmeLatch005E8690() {}
};

struct BfmeLatch005E86C0
{
	BfmeLatch005E86C0() { bfmeInit0001361F(); }
	~BfmeLatch005E86C0() {}
};

struct BfmeLatch005E86F0
{
	BfmeLatch005E86F0() { bfmeInit00026058(); }
	~BfmeLatch005E86F0() {}
};

struct BfmeLatch005E8720
{
	BfmeLatch005E8720() { bfmeInit00033479(); }
	~BfmeLatch005E8720() {}
};

struct BfmeLatch005E8750
{
	BfmeLatch005E8750() { bfmeInit000340FE(); }
	~BfmeLatch005E8750() {}
};

// ?bfmeEnsure005E83F0@@YAXXZ		guard 0x00EF6C44, atexit helper 0x00C70810
void bfmeEnsure005E83F0( void )
{
	static BfmeLatch005E83F0 s_latch;
}

void bfmeEnsure005E8420( void )
{
	static BfmeLatch005E8420 s_latch;
}

void bfmeEnsure005E8450( void )
{
	static BfmeLatch005E8450 s_latch;
}

// ?bfmeEnsure005E8480@@YAXXZ		guard 0x00EF6C50, atexit helper 0x00C707E0
void bfmeEnsure005E8480( void )
{
	static BfmeLatch005E8480 s_latch;
}

// ?bfmeEnsure005E84B0@@YAXXZ		guard 0x00EF6C54, atexit helper 0x00C707D0
void bfmeEnsure005E84B0( void )
{
	static BfmeLatch005E84B0 s_latch;
}

void bfmeEnsure005E84E0( void )
{
	static BfmeLatch005E84E0 s_latch;
}

// ?bfmeEnsure005E8510@@YAXXZ		guard 0x00EF6C5C, atexit helper 0x00C707B0
void bfmeEnsure005E8510( void )
{
	static BfmeLatch005E8510 s_latch;
}

// ?bfmeEnsure005E8540@@YAXXZ		guard 0x00EF6C60, atexit helper 0x00C707A0
void bfmeEnsure005E8540( void )
{
	static BfmeLatch005E8540 s_latch;
}

// ?bfmeEnsure005E8570@@YAXXZ		guard 0x00EF6C64, atexit helper 0x00C70790
void bfmeEnsure005E8570( void )
{
	static BfmeLatch005E8570 s_latch;
}

// ?bfmeEnsure005E85A0@@YAXXZ		guard 0x00EF6C68, atexit helper 0x00C70780
void bfmeEnsure005E85A0( void )
{
	static BfmeLatch005E85A0 s_latch;
}

// ?bfmeEnsure005E85D0@@YAXXZ		guard 0x00EF6C6C, atexit helper 0x00C70770
void bfmeEnsure005E85D0( void )
{
	static BfmeLatch005E85D0 s_latch;
}

// ?bfmeEnsure005E8600@@YAXXZ		guard 0x00EF6C70, atexit helper 0x00C70760
void bfmeEnsure005E8600( void )
{
	static BfmeLatch005E8600 s_latch;
}

void bfmeEnsure005E8630( void )
{
	static BfmeLatch005E8630 s_latch;
}

void bfmeEnsure005E8660( void )
{
	static BfmeLatch005E8660 s_latch;
}

// ?bfmeEnsure005E8690@@YAXXZ		guard 0x00EF6C7C, atexit helper 0x00C70730
void bfmeEnsure005E8690( void )
{
	static BfmeLatch005E8690 s_latch;
}

// ?bfmeEnsure005E86C0@@YAXXZ		guard 0x00EF6C80, atexit helper 0x00C70720
void bfmeEnsure005E86C0( void )
{
	static BfmeLatch005E86C0 s_latch;
}

void bfmeEnsure005E86F0( void )
{
	static BfmeLatch005E86F0 s_latch;
}

// ?bfmeEnsure005E8720@@YAXXZ		guard 0x00EF6C88, atexit helper 0x00C70700
void bfmeEnsure005E8720( void )
{
	static BfmeLatch005E8720 s_latch;
}

// ?bfmeEnsure005E8750@@YAXXZ		guard 0x00EF6C8C, atexit helper 0x00C706F0
void bfmeEnsure005E8750( void )
{
	static BfmeLatch005E8750 s_latch;
}
