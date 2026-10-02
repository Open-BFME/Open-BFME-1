// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// FILE: LivingWorldCampaignManager.cpp -- data only.
//
// The singleton the class's own TU owns, per EA's convention
// (`GameLogic *TheGameLogic = NULL;` in GameLogic.cpp:146). Retail links the
// definition into whichever object holds it, so the image has no symbol for
// it; only the class name and the address are proven.
//
// Identity (build/report_0x012F1028.md, section "0x012F1024 --
// TheLivingWorldCampaignManager"):
//   * GameEngine::init site RVA 0x0007A18E pushes the literal
//     "TheLivingWorldCampaignManager" (0x01076174, the image's only
//     occurrence, its only xref) into a BFMERetailAsciiString and then pushes
//     0x012F1024 as the `T*&` first argument of
//     `??$initSubsystem@VLivingWorldCampaignManager@@` (RVA 0x00075660), whose
//     `mov [esi],edi` at RVA 0x00075689 is the store. That is the top evidence
//     tier of docs/naming_evidence.md: the EA literal names the global at its
//     own address.
//   * The class, not just the variable: the ctor called at that site
//     (0x003B5100) installs vtable 0x010ECB78, and the block's secondary
//     `name()` virtual returns the literal "LivingWorldCampaignManager" at
//     0x010ECBA4.
//
// Type `LivingWorldCampaignManager *`: 44-byte pointee (`operator new(0x2C)`),
// vtable at +0, with the +0x1C evil-campaign and +0x1D victorious flags that
// matched callers read (V4CampaignLabelSelect.cpp, ScriptActions.cpp:461,1020,
// 1049). Retail .data at 0x012F1024 holds four zero bytes, so the
// NULL-initialised singleton is .bss.

#define NULL 0

class LivingWorldCampaignManager;

LivingWorldCampaignManager *TheLivingWorldCampaignManager = NULL;