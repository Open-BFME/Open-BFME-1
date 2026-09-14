// cl: /ICode/GameEngine/Source/Common/System /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

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

void W3DModuleFactory::init(void)
{
	ModuleFactory::init();

	// These are the retail ILT values placed in the template records.  The
	// registration block proves their callback/data roles, but does not provide
	// a trustworthy source-level owner for every generated callee.  Keep them
	// as typed neutral addresses rather than introducing false names or pins.
	addModuleInternal(reinterpret_cast<const void *>(0x004063BBu),
		reinterpret_cast<const void *>(0x0041F0FAu), 0, 1,
		AsciiString("W3DDefaultDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x0040230Bu),
		reinterpret_cast<const void *>(0x0041F0FAu), 0, 1,
		AsciiString("W3DDebrisDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x00419A06u),
		reinterpret_cast<const void *>(0x00426F5Du),
		reinterpret_cast<const void *>(0x0040DDFFu), 1,
		AsciiString("W3DScriptedModelDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x0043F468u),
		reinterpret_cast<const void *>(0x0042347Fu),
		reinterpret_cast<const void *>(0x00424915u), 1,
		AsciiString("W3DHordeModelDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x004398CEu),
		reinterpret_cast<const void *>(0x0040D03Fu), 0, 1,
		AsciiString("W3DLaserDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x00428222u),
		reinterpret_cast<const void *>(0x0042FD33u),
		reinterpret_cast<const void *>(0x00405BA0u), 1,
		AsciiString("W3DQuadrupedDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x0040B67Cu),
		reinterpret_cast<const void *>(0x0041F0FAu), 0, 1,
		AsciiString("W3DRopeDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x00435733u),
		reinterpret_cast<const void *>(0x00405EE8u),
		reinterpret_cast<const void *>(0x00441722u), 1,
		AsciiString("W3DSupplyDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x0041B5E5u),
		reinterpret_cast<const void *>(0x00432448u),
		reinterpret_cast<const void *>(0x00418282u), 1,
		AsciiString("W3DTruckDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x00440444u),
		reinterpret_cast<const void *>(0x00424AFAu),
		reinterpret_cast<const void *>(0x0041C373u), 1,
		AsciiString("W3DTankDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x0043ABF7u),
		reinterpret_cast<const void *>(0x00447753u),
		reinterpret_cast<const void *>(0x0043BDCCu), 1,
		AsciiString("W3DTreeDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x004374A2u),
		reinterpret_cast<const void *>(0x004087D3u),
		reinterpret_cast<const void *>(0x0041B293u), 1,
		AsciiString("W3DFloorDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x00445E12u),
		reinterpret_cast<const void *>(0x004326E6u),
		reinterpret_cast<const void *>(0x0042583Du), 1,
		AsciiString("W3DPropDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x00404EB7u),
		reinterpret_cast<const void *>(0x00415E33u), 0, 1,
		AsciiString("W3DLightDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x0043823Au),
		reinterpret_cast<const void *>(0x00403DE6u), 0, 1,
		AsciiString("W3DBuffDraw"), 0x400);
	addModuleInternal(reinterpret_cast<const void *>(0x004391C1u),
		reinterpret_cast<const void *>(0x00424974u), 0, 1,
		AsciiString("W3DStreakDraw"), 0x400);
}
