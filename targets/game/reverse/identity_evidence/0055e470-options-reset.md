# Options reset callback, RVA 0x0055E470

The matched Options constructor at RVA 0x00563370 installs this callback:
at 0x00563586 it pushes VA 0x01109678, whose complete NUL-terminated bytes
are `AptOptions::Reset\0`; at 0x00563595 it loads callback VA 0x00407D0B.
The five-byte ILT at RVA 0x00007D0B jumps to VA 0x0095E470. The constructor
pairs that code pointer with its primary `this` and registers the selector.
The existing named Options factory at 0x00104CC0 and matched constructor
establish the owner. `_bfme_reset` follows the established callback naming
scheme, rather than asserting an original exported C++ spelling.

Independent linear retail decode and Ghidra function creation agree on the
1806-byte extent [0x0055E470,0x0055EB7E). The last instruction is `ret 4` at
0x0055EB7B; INT3 padding begins at 0x0055EB7E. Incoming ECX is the screen,
and the unused four-byte stack parameter follows the registered text callback
contract. No function boundary was inferred from Ghidra pseudocode alone.

## Native calls and data

`callees.py` was run before reconstruction. The eight direct targets are the
existing matched GameWindow winGetUserData (0x00478C70) and winEnable
(0x004782E0), checkbox setter (0x004B31D0), combo setter (0x004B3C70),
BfmeAptScreenSetComboFromIndex::setComboFromIndex (0x0055E070),
OptionPreferences::rva00090900IdealStaticGameDetail (0x00090900),
Rva0007C510::ge (0x0007C510), and the CRT float conversion helper.
The preference receiver is screen+0x260, while ge consumes TheGameLODManager:
its independent 24-byte body compares receiver+0x171C against receiver+0x1738
and returns a full integer 0/1. No replacement pins were introduced.

GameWindow uses the existing BFME gamewindow header. The preference method
is an address-qualified BFME-only declaration already used by its matched
defining TU. The canonical game UserPreferences header adds that declaration
to the complete upstream class; it changes no field or virtual slot.
All other unknown layouts use address-qualified views, not guessed identities.
The screen's page at +0x258 and controls +0x284..+0x300 are witnessed by
this body's reads and the matched constructor; opaque field names avoid
propagating conflicting older checkbox/slider names.

The native globals retain their established symbols, including TheAudio,
TheWindowManager, TheDisplay, TheGameLogic, TheWritableGlobalData,
TheGameLODManager and g_aptPalantirUIState. The dynamic virtual views record
only witnessed slots: window +0xD4 takes window/message/value/zero;
display +0x50 takes four floats; audio +0x120 returns a settings pointer,
+0xC0/+0xC4/+0xC8/+0xCC/+0xD0 take one float, and +0x16C takes false.
No semantic names are invented for those virtual methods.

The preset array has 0x30-byte records at the LOD-manager base and a signed
selection at +0x16C4. Values outside [0,6), or equal to 5, select entry 4.
The exact accessed offsets are dword +0/+0x1C and bytes
+4/+5/+6/+8/+9/+0x18/+0x21/+0x22. These retain opaque names. Retail negates
byte +0x21; it copies the other bytes unchanged. The audio settings pointer
supplies float defaults at +0x80/+0x84/+0x88/+0x8C/+0x90.

## Verification

The first complete draft was 1807 bytes. Moving the audio volume local to
function scope and indexing each preset access independently restored 1806.
Assigning preset fields in control order closed the final 12 scheduling bytes.
No inline assembly, volatility, barriers, fabricated helpers, or compiler-flag
sweeps were needed.

The scoped add_match gate passed 1/1 functions, all 17 floating constants and
43 DIR32 references. The probe independently reports 1806/1806 exact outside
81 relocation slots. The strict gate resolves the actual callees and constants;
probe equality alone is not the landing proof.

## Review follow-up for fe212ebbae0

The reviewer requires the canonical OptionPreferences declaration despite the
initial lead exception. The proposed shared game header preserves the complete
upstream declaration and adds only the already-matched BFME member. The reset
TU includes it and removes its local class. The scoped strict gate still passes
1806B, 17 constants and43 global references. This header cutover is queued for
the lead full gate; the body is banked until that coordinated change lands.

## h1 coordinated integration

Restore the withdrawn recovery fe212ebbae0 together with the canonical-header
repair queued by b4. The game header preserves the upstream UserPreferences,
OptionPreferences and LANPreferences declarations, adding only the already
matched address-qualified nonvirtual rva00090900IdealStaticGameDetail member.
No local OptionPreferences declaration survives. Independent retail reads
reconfirm PUSH01109678 at00563586, callback00407D0B at00563595, ILT7D0B to55E470,
and RET4 at55EB7B before INT3. Ghidra read_memory confirms the complete
AptOptions::Reset string through NUL. The usual shared-header commit gate
verifies dependent sources before this recovery can land.
