# C3 selected-copy audit

These are actual relocation identity discrepancies, not link_check false
rejects. Census 13 is only the before/after index; no census was built.
Fresh owner object bytes were compared to the native image outside every
relocation field. All five owners had zero nonrelocation differences.
The relevant link_census/link_check/COMMON/truth-fingerprint tests pass
(121 tests). No verifier change or escape hatch is needed.

## Mission, RVA 0x005BB9B0, 164 bytes

At +0x62, native REL32 calls ILT 0x00025306 -> 0x000B2CC0.
The owner previously named AudioEventRTS(const AsciiString &, ObjectID),
whose matched ledger body is 0x000B4350 (188 bytes), whereas 0x000B2CC0
is AudioEventRTS(const AsciiString &, int) (159 bytes). The additive
ObjectID pin points to the wrong overload's ILT and concealed this in the
byte gate. The corrected declaration uses int, retaining default value 2.

CampaignManager.cpp also emitted a wrong Mission constructor and protected
destructor with a different vtable. Removing those present-unmatched
lifetime definitions retains the three matched bodies in Mission_ctor_Thunk.
Both emitter TUs were supplied explicitly to link_check: 0/2 -> 1/2 clean,
LINKED 0 -> 381 bytes. Builds preserve 3/3 owner and 8/8 emitter rows,
plus the emitter's one verified data row. CampaignManager remains blocked
by independent debt. No header or pin was edited.

## WorkerAIUpdateModuleData, RVA 0x000D1690, 76 bytes: blocked

At +0x29, native REL32 calls ILT 0x0002671F -> 0x000CFA40.
The object instead names the virtual AudioEventRTS destructor; the ledger's
object-symbol for that name lives at 0x000B31F0. Existing independent
identity evidence in 000cfa40-gen000f9c60-destructor.md proves that CFA40
is a nonpolymorphic 28-byte Gen_000F9C60 record destructor, distinct from
the 112-byte AudioEventRTS lifetime. Reference WorkerAIUpdate.h declares
m_suppliesDepletedVoice as AudioEventRTS, so implicit destruction emits
the wrong member identity. Changing reference headers is prohibited in
this lane. ModuleFactory and Bfme5VectorDestroysWide were passed explicitly;
LINKED remains 0 -> 0. No body was changed.

## GameSpyStagingRoom assignment, RVA 0x004F15B0, 344 bytes: blocked

At +0x47, native calls StringBase<unsigned short>::set at 0x00888530;
the owner under /Ob0 names UnicodeString::operator= at 0x000680A0.
At +0x71, +0xE3 and +0xF5, native calls StringBase<char>::set at
0x00887C90; the owner names AsciiString::operator= at 0x0005C500.
All four object calls fail the ledger identity check despite additive pins
letting the byte gate match. PeerDefs.cpp and WOLGameSetupMenu.cpp also
emit implicit competing assignments from reference StagingRoomGameInfo.h,
whose member layout differs from the matched owner. A coordinated layout
and declaration repair is required; removing an implicit definition without
fixing its header/callers is insufficient. Both competing emitter TUs and
the owner were supplied explicitly; LINKED remains 0 -> 0. No body,
reference header, alias, or pin was changed.

## GameState::isInSaveDirectory, RVA 0x0010F1E0, 118 bytes

At +0x5E, native calls StringBase<char>::releaseBuffer at 0x00887940;
the old owner named AsciiString destruction whose ledger body is the
separate 5-byte tail-jump function at 0x0005EE90. A padded tail-jump
function is not an ILT stub and cannot stand in for a different relocation
identity. The shared ascii_string.h correctly inlines the derived/base
destructors to releaseBuffer. An inline specialization of the existing
StringBase<char> prefix overload preserves the original 118-byte shape.
The private string declarations and GameState.cpp's competing definition
were removed. No string-family implementation or reference header changed.

The edit renumbered 12 GameState.cpp EH labels. Each new label was identified
and verified with build.compile_function in its already-recorded parent's
group; the one masked-prefix tie was resolved by its native tail-jump target.
Only the existing object-symbol label values changed in the ledger.
Builds preserve 1/1 owner, 25/25 emitter and 2/2 caller rows plus three
emitter data rows. link_check with both emitter TUs and the ambient-light
caller reports 0/3 -> 2/3 clean, LINKED 0 -> 1056 bytes: 118 owner plus
938 caller. GameState.cpp retains separate pre-existing link debt.
