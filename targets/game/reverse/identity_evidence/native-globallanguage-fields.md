# GlobalLanguage fields at compiler-measured BFME offsets

Matched initSubsystem<GlobalLanguage> RVA 0x00072F50 binds TheGlobalLanguageData and constructs through the named constructor RVA 0x00439E70 (549 bytes). The constructor installs vtable 0x010F4124 shared with the complete destructor RVA 0x0043A130 (512 bytes) and deleting destructor RVA 0x0043A4B0 (30 bytes). Matched INI::parseLanguageDefinition RVA 0x00438F70 reads that same global and binds the Language parse table; matched parseFontDesc RVA 0x00439150 writes the font descriptor storage.

The existing matched source views identify GlobalLanguage; their types, bases, packing,
sizes, signatures and bodies remain unchanged. Scratch copies compiled with the
same MSVC 7.1 options add nonvirtual static address/sizeof probes, called from
extern-C wrappers. Only relocation-free constant return bodies are accepted; no
probe is shipped. This measures the layout the handwritten offset model refuses.

Names are independently joined from retail FieldParse records to the INI keys'
`offsetof(GlobalLanguage, member)` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GlobalLanguage.cpp`. The raw terminated retail tables
and exact upstream key/owner/member triples were rechecked for each field; ZH
offsets are not used. `field_names.csv` records the witnesses.

Only metric-placeholders with a unique declaration spelling are rewritten.
Spans crossing another witnessed offset and already-declared target names are
refused. The declaration denominator is unchanged.

| Source view | Original field | BFME offset | Proven field | INI key |
|---|---|---:|---|---|
| `GlobalLanguageConstructor` | `m_font00` | `0x28` | `m_copyrightFont` | `CopyrightFont` |
| `GlobalLanguageConstructor` | `m_font01` | `0x34` | `m_messageFont` | `MessageFont` |
| `GlobalLanguageConstructor` | `m_font02` | `0x40` | `m_militaryCaptionTitleFont` | `MilitaryCaptionTitleFont` |
| `GlobalLanguageConstructor` | `m_font03` | `0x4c` | `m_militaryCaptionFont` | `MilitaryCaptionFont` |
| `GlobalLanguageConstructor` | `m_font05` | `0x64` | `m_superweaponCountdownNormalFont` | `SuperweaponCountdownNormalFont` |
| `GlobalLanguageConstructor` | `m_font06` | `0x70` | `m_superweaponCountdownReadyFont` | `SuperweaponCountdownReadyFont` |
| `GlobalLanguageConstructor` | `m_font07` | `0x7c` | `m_namedTimerCountdownNormalFont` | `NamedTimerCountdownNormalFont` |
| `GlobalLanguageConstructor` | `m_font08` | `0x88` | `m_namedTimerCountdownReadyFont` | `NamedTimerCountdownReadyFont` |
| `GlobalLanguageConstructor` | `m_font09` | `0x94` | `m_drawableCaptionFont` | `DrawableCaptionFont` |
| `GlobalLanguageConstructor` | `m_font10` | `0xa0` | `m_defaultWindowFont` | `DefaultWindowFont` |
| `GlobalLanguageConstructor` | `m_font11` | `0xac` | `m_defaultDisplayStringFont` | `DefaultDisplayStringFont` |
| `GlobalLanguageConstructor` | `m_font12` | `0xb8` | `m_tooltipFontName` | `TooltipFontName` |
| `GlobalLanguageConstructor` | `m_font13` | `0xc4` | `m_nativeDebugDisplay` | `NativeDebugDisplay` |
| `GlobalLanguageConstructor` | `m_font14` | `0xd0` | `m_drawGroupInfoFont` | `DrawGroupInfoFont` |
| `GlobalLanguageConstructor` | `m_font15` | `0xdc` | `m_creditsTitleFont` | `CreditsTitleFont` |
| `GlobalLanguageConstructor` | `m_font16` | `0xe8` | `m_creditsPositionFont` | `CreditsMinorTitleFont` |
| `GlobalLanguageConstructor` | `m_font17` | `0xf4` | `m_creditsNormalFont` | `CreditsNormalFont` |
| `GlobalLanguageDestructor` | `m_font00` | `0x28` | `m_copyrightFont` | `CopyrightFont` |
| `GlobalLanguageDestructor` | `m_font01` | `0x34` | `m_messageFont` | `MessageFont` |
| `GlobalLanguageDestructor` | `m_font02` | `0x40` | `m_militaryCaptionTitleFont` | `MilitaryCaptionTitleFont` |
| `GlobalLanguageDestructor` | `m_font03` | `0x4c` | `m_militaryCaptionFont` | `MilitaryCaptionFont` |
| `GlobalLanguageDestructor` | `m_font05` | `0x64` | `m_superweaponCountdownNormalFont` | `SuperweaponCountdownNormalFont` |
| `GlobalLanguageDestructor` | `m_font06` | `0x70` | `m_superweaponCountdownReadyFont` | `SuperweaponCountdownReadyFont` |
| `GlobalLanguageDestructor` | `m_font07` | `0x7c` | `m_namedTimerCountdownNormalFont` | `NamedTimerCountdownNormalFont` |
| `GlobalLanguageDestructor` | `m_font08` | `0x88` | `m_namedTimerCountdownReadyFont` | `NamedTimerCountdownReadyFont` |
| `GlobalLanguageDestructor` | `m_font09` | `0x94` | `m_drawableCaptionFont` | `DrawableCaptionFont` |
| `GlobalLanguageDestructor` | `m_font10` | `0xa0` | `m_defaultWindowFont` | `DefaultWindowFont` |
| `GlobalLanguageDestructor` | `m_font11` | `0xac` | `m_defaultDisplayStringFont` | `DefaultDisplayStringFont` |
| `GlobalLanguageDestructor` | `m_font12` | `0xb8` | `m_tooltipFontName` | `TooltipFontName` |
| `GlobalLanguageDestructor` | `m_font13` | `0xc4` | `m_nativeDebugDisplay` | `NativeDebugDisplay` |
| `GlobalLanguageDestructor` | `m_font14` | `0xd0` | `m_drawGroupInfoFont` | `DrawGroupInfoFont` |
| `GlobalLanguageDestructor` | `m_font15` | `0xdc` | `m_creditsTitleFont` | `CreditsTitleFont` |
| `GlobalLanguageDestructor` | `m_font16` | `0xe8` | `m_creditsPositionFont` | `CreditsMinorTitleFont` |
| `GlobalLanguageDestructor` | `m_font17` | `0xf4` | `m_creditsNormalFont` | `CreditsNormalFont` |
