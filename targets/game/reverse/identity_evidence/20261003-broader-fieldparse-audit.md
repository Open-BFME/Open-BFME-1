# Broader FieldParse audit findings (2026-10-03, v3)

Read-only comparisons start at actual matched code operands and the corresponding current COFF relocations. Ghidra and the unpacked PE independently agree on every complete retail table including its16-byte zero terminator, and each complete body/padding window. These are positive source/data contradictions; no production names, offsets or pins are changed here.

docs/matching.md Relocations requires checking what references point at. AGENTS.md requires one identity per body, forbids guessed names, and requires coordinated dependent repairs for shared layouts. The ordinary code/reference gates passed these sources before this extra initialized-data audit.

## INI::parseChallengeModeDefinition — 0x0040BFC0

Direct operand+E containsVA010F0B78; source12keys versus retail9. Boundary: 25B; RET40BFD8, CC40BFD9.

| Retail key | Retail offset | Source offset | Callback VA |
|---|---:|---:|---:|
| ScrollRate | 0x14 | absent | 0xc52a60 |
| ScrollRateEveryFrames | 0x18 | absent | 0xc52a60 |
| ScrollDown | 0x1C | absent | 0xc52e00 |
| TitleColor | 0x20 | absent | 0xc531e0 |
| MinorTitleColor | 0x24 | absent | 0xc531e0 |
| NormalColor | 0x28 | absent | 0xc531e0 |
| Style | 0x2C | absent | 0xc51130 |
| Blank | 0x0 | absent | 0x420c3e |
| Text | 0x0 | absent | 0x42e307 |

Source-only keys: GeneralPersona0, GeneralPersona1, GeneralPersona2, GeneralPersona3, GeneralPersona4, GeneralPersona5, GeneralPersona6, GeneralPersona7, GeneralPersona8, GeneralPersona9, GeneralPersona10, GeneralPersona11.

## INI::parseLanguageDefinition — 0x00438F70

Direct operand+E containsVA010F3AD8; source23keys versus retail31. Boundary: 25B; RET438F88, CC438F89.

| Retail key | Retail offset | Source offset | Callback VA |
|---|---:|---:|---:|
| DecimalSeparator | 0x8 | absent | 0xc51ee0 |
| ThousandSeparator | 0xC | absent | 0xc51ee0 |
| TimeMinuteToSecondSeparator | 0x10 | absent | 0xc51ee0 |
| UnicodeFontName | 0x14 | 0x8 | 0xc51ee0 |
| LocalFontFile | 0x0 | 0x0 | 0x4178ff |
| MilitaryCaptionSpeed | 0x24 | 0x14 | 0xc52a60 |
| UseHardWordWrap | 0x20 | 0x10 | 0xc52e00 |
| ResolutionFontAdjustment | 0x130 | 0xE8 | 0xc52b20 |
| AudioLanguage | 0x1C | absent | 0xc51ee0 |
| CopyrightFont | 0x28 | 0x1C | 0x40b41f |
| MessageFont | 0x34 | 0x28 | 0x40b41f |
| MilitaryCaptionTitleFont | 0x40 | 0x34 | 0x40b41f |
| MilitaryCaptionFont | 0x4C | 0x40 | 0x40b41f |
| AudioSubtitleFont | 0x58 | absent | 0x40b41f |
| SuperweaponCountdownNormalFont | 0x64 | 0x4C | 0x40b41f |
| SuperweaponCountdownReadyFont | 0x70 | 0x58 | 0x40b41f |
| NamedTimerCountdownNormalFont | 0x7C | 0x64 | 0x40b41f |
| NamedTimerCountdownReadyFont | 0x88 | 0x70 | 0x40b41f |
| DrawableCaptionFont | 0x94 | 0x7C | 0x40b41f |
| DefaultWindowFont | 0xA0 | 0x88 | 0x40b41f |
| DefaultDisplayStringFont | 0xAC | 0x94 | 0x40b41f |
| TooltipFontName | 0xB8 | 0xA0 | 0x40b41f |
| NativeDebugDisplay | 0xC4 | 0xAC | 0x40b41f |
| DrawGroupInfoFont | 0xD0 | 0xB8 | 0x40b41f |
| CreditsTitleFont | 0xDC | 0xC4 | 0x40b41f |
| CreditsMinorTitleFont | 0xE8 | 0xD0 | 0x40b41f |
| CreditsNormalFont | 0xF4 | 0xDC | 0x40b41f |
| HelpBoxNameFont | 0x100 | absent | 0x40b41f |
| HelpBoxCostFont | 0x10C | absent | 0x40b41f |
| HelpBoxShortcutFont | 0x118 | absent | 0x40b41f |
| HelpBoxDescriptionFont | 0x124 | absent | 0x40b41f |

Source-only keys: MilitaryCaptionDelayMS.

## INI::parseOnlineChatColorDefinition — 0x006250A0

Direct operand+5 containsVA01117700; source27keys versus retail29. Boundary: 20B; RET6250B3, CC6250B4.

| Retail key | Retail offset | Source offset | Callback VA |
|---|---:|---:|---:|
| Default | 0x0 | 0x0 | 0xc531e0 |
| CurrentRoom | 0x4 | 0x4 | 0xc531e0 |
| ChatRoom | 0x8 | 0x8 | 0xc531e0 |
| Game | 0xC | 0xC | 0xc531e0 |
| GameFull | 0x10 | 0x10 | 0xc531e0 |
| GameCRCMismatch | 0x14 | 0x14 | 0xc531e0 |
| PlayerNormal | 0x18 | 0x18 | 0xc531e0 |
| PlayerOwner | 0x1C | 0x1C | 0xc531e0 |
| PlayerBuddy | 0x20 | 0x20 | 0xc531e0 |
| OfflinePlayerBuddy | 0x24 | absent | 0xc531e0 |
| PlayerSelf | 0x28 | 0x24 | 0xc531e0 |
| PlayerIgnored | 0x2C | 0x28 | 0xc531e0 |
| OfflinePlayerIgnored | 0x30 | absent | 0xc531e0 |
| ChatNormal | 0x34 | 0x2C | 0xc531e0 |
| ChatEmote | 0x38 | 0x30 | 0xc531e0 |
| ChatOwner | 0x3C | 0x34 | 0xc531e0 |
| ChatOwnerEmote | 0x40 | 0x38 | 0xc531e0 |
| ChatPriv | 0x44 | 0x3C | 0xc531e0 |
| ChatPrivEmote | 0x48 | 0x40 | 0xc531e0 |
| ChatPrivOwner | 0x4C | 0x44 | 0xc531e0 |
| ChatPrivOwnerEmote | 0x50 | 0x48 | 0xc531e0 |
| ChatBuddy | 0x54 | 0x4C | 0xc531e0 |
| ChatSelf | 0x58 | 0x50 | 0xc531e0 |
| AcceptTrue | 0x5C | 0x54 | 0xc531e0 |
| AcceptFalse | 0x60 | 0x58 | 0xc531e0 |
| MapSelected | 0x64 | 0x5C | 0xc531e0 |
| MapUnselected | 0x68 | 0x60 | 0xc531e0 |
| MOTD | 0x6C | 0x64 | 0xc531e0 |
| MOTDHeading | 0x70 | 0x68 | 0xc531e0 |

Source-only keys: none.

The first table is wholly unrelated to the twelve GeneralPersona initializers. The same address already has a competing parseCredits row; independently trace the retail INI dispatch before completing any semantic identity correction. For language/color data, repair the canonical layouts or enum/storage and all dependent accesses; do not substitute isolated integer offsets or infer C++ member names from serialized keys.

## AudioManager::getFieldParseTable — RVA0058AE70/6B

Actual bytes are `B8 0A 00 00 00 C3`, followed byINT3 at0058AE76: MOV EAX,10; RET. The source instead returns a36-entry FieldParse array, using a local DIR32 relocation at+1. Masking/patching that immediate explains the otherwise green code check. VA0000000A is outside the image and cannot name that table. This positively contradicts the table-getter claim, without establishing the real owner or return-type spelling. Retire/correct this claim using an address-preserving identity if no stronger witness exists; do not invent another semantic getter name.

The generic FieldParse adapter labels this last reference incomplete rather than treating an unreadable target as an empty/equal table. The independent instruction decode is the stronger contradiction evidence.

Artifacts: build/audit_v3/s4_broader_fieldparse_raw.json and s4_fieldparse_wide_corpus.json. All four claims remain on origin/master after the required fetch. Ledger correction is blocked locally by separately held inherited aliases003C8340/00803080; no guard/baseline bypass or partial production layout patch is included. Record-only claims are released.
