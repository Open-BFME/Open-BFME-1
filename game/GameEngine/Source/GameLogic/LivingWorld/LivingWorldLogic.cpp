// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// FILE: LivingWorldLogic.cpp -- data only.
//
// The singleton the class's own TU owns, per EA's convention
// (`GameLogic *TheGameLogic = NULL;` in GameLogic.cpp:146). Retail links the
// definition into whichever object holds it, so the image has no symbol for
// it; only the class name and the address are proven.
//
// Identity (build/report_0x012F1028.md, section "0x012F1028 -- The
// LivingWorldLogic"):
//   * GameEngine::init site RVA 0x00079DB3 pushes the literal
//     "TheLivingWorldLogic" (0x010762B4, the image's only occurrence of that
//     string and its only xref) into a
//     BFMERetailAsciiString and then pushes 0x012F1028 as the `T*&` first
//     argument of `??$initSubsystem@VLivingWorldLogic@@` (RVA 0x00074B10,
//     matched), whose `mov [esi],edi` at RVA 0x00074B39 is the store. That is
//     the top evidence tier of docs/naming_evidence.md: the EA literal names
//     the global at its own address.
//   * The class, not just the variable: the ctor called at that site
//     (0x007C2FC0) installs vtable 0x010EDBDC, and that block's secondary
//     `name()` virtual returns the literal "LivingWorldLogic" at 0x010EDC08,
//     immediately followed by EA's method-qualified
//     "LivingWorldLogic::StateSnapshotSave".
//
// Type `LivingWorldLogic *`: 220-byte pointee (`operator new(0xDC)`), vtable at
// +0, SubsystemInterface base (inherited loadIniFilesFromLegend /
// postProcessLoad in primary slots 2 and 3). Retail .data at 0x012F1028 holds
// four zero bytes, so the NULL-initialised singleton is .bss.

#define NULL 0

class LivingWorldLogic;

LivingWorldLogic *TheLivingWorldLogic = NULL;