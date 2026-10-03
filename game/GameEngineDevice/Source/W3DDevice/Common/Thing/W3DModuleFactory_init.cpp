// cl: /Igame/GameEngine/Source/Common/System /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

// The retail 0x006BFFE0 body is the W3DModuleFactory initializer.  Its
// registration strings identify the sixteen module owners, while the
// surrounding constructor/factory calls establish the W3DModuleFactory /
// ModuleFactory boundary.  The local six-argument ModuleFactory model is the
// ABI already used by the matched ModuleFactory::addModuleInternal body.

#include "module_factory.h"

// The earlier present-unmatched initializer remains in W3DModuleFactory.cpp:
// its inline registrations emit other held factory methods and EH funclets.
// This TU owns the sole matched ledger row for the BFME initializer.
class W3DModuleFactory : public ModuleFactory
{
public:
	virtual void init(void);
};

// Existing address-identified ILT symbols; used only as erased callback addresses.
extern void j_0000230b();
extern void j_00003de6();
extern void j_00004eb7();
extern void j_00005ba0();
extern void j_00005ee8();
extern void j_000063bb();
extern void j_000087d3();
extern void j_0000b67c();
extern void j_0000d03f();
extern void j_0000ddff();
extern void j_00015e33();
extern void j_00018282();
extern void j_00019a06();
extern void j_0001b293();
extern void j_0001b5e5();
extern void j_0001c373();
extern void j_0001f0fa();
extern void j_0002347f();
extern void j_00024915();
extern void j_00024974();
extern void j_0002583d();
extern void j_00026f5d();
extern void j_00028222();
extern void j_0002fd33();
extern void j_00032448();
extern void j_000326e6();
extern void j_00035733();
extern void j_000374a2();
extern void j_0003823a();
extern void j_000391c1();
extern void j_000398ce();
extern void j_0003abf7();
extern void j_0003bdcc();
extern void j_0003f468();
extern void j_00040444();
extern void j_00041722();
extern void j_00045e12();
extern void j_00047753();

void W3DModuleFactory::init(void)
{
	ModuleFactory::init();

	// The registration block proves callback/data roles. Use the already
	// ledgered ILT identities without assigning semantic callback names.
	// VA00424AFA has no existing symbol anchor and still needs a separate repair.
	addModuleInternal(reinterpret_cast<const void *>(&j_000063bb),
		reinterpret_cast<const void *>(&j_0001f0fa), 0, 1,
		AsciiString("W3DDefaultDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_0000230b),
		reinterpret_cast<const void *>(&j_0001f0fa), 0, 1,
		AsciiString("W3DDebrisDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_00019a06),
		reinterpret_cast<const void *>(&j_00026f5d),
		reinterpret_cast<const void *>(&j_0000ddff), 1,
		AsciiString("W3DScriptedModelDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_0003f468),
		reinterpret_cast<const void *>(&j_0002347f),
		reinterpret_cast<const void *>(&j_00024915), 1,
		AsciiString("W3DHordeModelDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_000398ce),
		reinterpret_cast<const void *>(&j_0000d03f), 0, 1,
		AsciiString("W3DLaserDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_00028222),
		reinterpret_cast<const void *>(&j_0002fd33),
		reinterpret_cast<const void *>(&j_00005ba0), 1,
		AsciiString("W3DQuadrupedDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_0000b67c),
		reinterpret_cast<const void *>(&j_0001f0fa), 0, 1,
		AsciiString("W3DRopeDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_00035733),
		reinterpret_cast<const void *>(&j_00005ee8),
		reinterpret_cast<const void *>(&j_00041722), 1,
		AsciiString("W3DSupplyDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_0001b5e5),
		reinterpret_cast<const void *>(&j_00032448),
		reinterpret_cast<const void *>(&j_00018282), 1,
		AsciiString("W3DTruckDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_00040444),
		reinterpret_cast<const void *>(0x00424AFAu),
		reinterpret_cast<const void *>(&j_0001c373), 1,
		AsciiString("W3DTankDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_0003abf7),
		reinterpret_cast<const void *>(&j_00047753),
		reinterpret_cast<const void *>(&j_0003bdcc), 1,
		AsciiString("W3DTreeDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_000374a2),
		reinterpret_cast<const void *>(&j_000087d3),
		reinterpret_cast<const void *>(&j_0001b293), 1,
		AsciiString("W3DFloorDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_00045e12),
		reinterpret_cast<const void *>(&j_000326e6),
		reinterpret_cast<const void *>(&j_0002583d), 1,
		AsciiString("W3DPropDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_00004eb7),
		reinterpret_cast<const void *>(&j_00015e33), 0, 1,
		AsciiString("W3DLightDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_0003823a),
		reinterpret_cast<const void *>(&j_00003de6), 0, 1,
		AsciiString("W3DBuffDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(&j_000391c1),
		reinterpret_cast<const void *>(&j_00024974), 0, 1,
		AsciiString("W3DStreakDraw"), 0x400);
}
