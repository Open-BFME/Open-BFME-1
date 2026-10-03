# ILT 0x00029311 is AIInternalMoveToState::onExit

The ledger previously held this five-byte ILT under the opaque, calling-convention-wrong name
`?Rva00029311AIInternalMoveToStateOnExitThunk@@YAXXZ`. It is the real member `AIInternalMoveToState::onExit(StateExitType)`.

1. The ILT's tail jump reaches the matched 189-byte body at 0x00172D80. That body clears the model-condition bits,
   calls `TheAudio->removeAudioEvent(m_ambientPlayingHandle)`, resets the handle and calls the AI's end-of-move hook:
   the ZH `AIInternalMoveToState::onExit` shape (stop the ambient movement sound, `ai->friend_endingMove()`).
2. Matched retail derived-state exits (0x00177A40, 0x00178B40, 0x00179A90, 0x0017ADC0, 0x0017AE70, 0x0017EE60) are byte-verified
   callers whose ZH source calls `AIInternalMoveToState::onExit(status)`; their base-class call is a REL32 to this ILT.
3. `symbols.csv` already pins `?onExit@AIInternalMoveToState@@UAEXW4StateExitType@@@Z` at 0x00029311, and the sibling ILTs of this class
   (`onEnter` 0x00021E27, `update` 0x000488F6) are ledgered under their real names the same way.

The old name described the same five bytes as a cdecl no-argument function, which is why callers needed a union cast.
