# 005A7460: PickAndPlayInfo constructor

The 46-byte body at RVA 0x005A7460 (reached only through ILT 0x0000F164)
was matched under the placeholder ??0Gen_005A7460@@QAE@XZ. symbols.csv already
pins ??0PickAndPlayInfo@@QAE@XZ at ILT 0x0000F164; pin_consistency reports it
consistent with this body.

Caller evidence: CommandTranslator::issueMoveToLocationCommand (0x005ACBB0,
matched) calls ILT 0xF164 on a stack object and then passes that object to
ILT 0x196C8 -> 0x005AA450, matched as pickAndPlayUnitVoiceResponse, whose
third parameter is PickAndPlayInfo* (ZH CommandXlat.h:127). Fourteen other
callers in the census spell the same pair (ControlBarCallback, CommandXlat,
GUICommandTranslator_doGuardCommand, AIUpdateInterface_playMoveVoiceResponse...).

Layout evidence: the body clears a bool at +0 and words at +4, +8, +C (ZH
m_air, m_drawTarget, m_weaponSlot, m_specialPowerType), seeds a 12-byte
Coord3D at +0x10 from three globals and clears one BFME word at +0x1C. This
matches the PickAndPlayInfo the matched pickAndPlayUnitVoiceResponse TU
(CommandXlatVoice.cpp:59) uses: bool, Drawable*, int*, int, Coord3D, word.

Bytes are unchanged: only the class name in Bfme5SixtyNine.cpp changes.
