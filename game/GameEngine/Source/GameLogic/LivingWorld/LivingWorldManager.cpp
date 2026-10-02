// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// FILE: LivingWorldManager.cpp -- data only.
//
// The singleton the class's own TU owns, per EA's convention
// (`GameClient *TheGameClient = NULL;` in GameClient.cpp:210). Retail links the
// definition into whichever object holds it, so the image has no symbol for it;
// only the class name and the address are proven.
//
// Identity (build/report_0x012F1028.md, section "0x012F706C -- The
// LivingWorldManager"):
//   * GameEngine::init site RVA 0x00079CAC pushes the literal
//     "TheLivingWorldManager" (0x010762FC, the image's only occurrence of that
//     string and its only xref) into a BFMERetailAsciiString and then pushes
//     0x012F706C as the `T*&` first argument of
//     `??$initSubsystem@VLivingWorldManager@@` (RVA 0x00074810), whose
//     `mov [esi],edi` at RVA 0x00074839 is the store. That is the top evidence
//     tier of docs/naming_evidence.md: the EA literal names the global at its
//     own address.
//   * The class, not just the variable: the ctor called at that site installs
//     vtable 0x01116BFC, and that block's secondary `name()` virtual returns
//     the literal "LivingWorldManager" at 0x01116C28, followed by EA's
//     method-qualified "POTENTIAL DESYNC: Forced into EnterLogic State.
//     (LivingWorldManager::update)" -- the primary slot 5 that literal
//     describes.
//   * EA wrote the variable name into its own assertion:
//     LivingWorldObjectParser00614F50.cpp:93 throws
//     INIException(3, "TheLivingWorldManager==NULL").
//
// Type `LivingWorldManager *`: 676-byte pointee (`operator new(0x2A4)`), vtable
// at +0, with the LivingWorldMapInfo record at +0x0C (INILivingWorld.cpp:27-30)
// the ctor initialises at +0x194. Retail .data at 0x012F706C holds four zero
// bytes, so the NULL-initialised singleton is .bss.

#define NULL 0

class LivingWorldManager;

LivingWorldManager *TheLivingWorldManager = NULL;