# GlobalLighting parser virtual body at RVA 0x00747FF0

The original WorldHeightMap static three-argument callback decoration is the Zero Hour signature, not the BFME ABI.

Independent evidence:
- The byte-matched constructor `Rva0074A680ParserRegistration` at RVA 0x0074A680 constructs its registration base with the literal `GlobalLighting` (VA 0x01121ACC) and installs vtable VA 0x01121B30. Its source is game/GameEngine/Source/Common/Rva0074A680ParserRegistrationCtor.cpp.
- Vtable slot +4 is VA 0x0041D5A7. Its E9 branch reaches VA 0x00B47FF0, the assigned body.
- The body reads DataChunkInput from stack argument 1 and DataChunkInfo from argument 2, and terminates with RET 8 at +0x6B9. It is the parser object's virtual method, not a cdecl callback with userData.
- The Zero Hour WorldHeightMap::ParseLightingDataChunk provides the original lighting initialization and version-2/version-3 reads. BFME adds a third array at GlobalData+0x7A0 and version-5 through version-7 settings. Calls resolve to DataChunkInput::readInt/readReal/atEndOfChunk.

The class remains the address-qualified class already established by its landed constructor; ParseLightingDataChunk retains the descriptive operation name. No speculative BFME semantic class name is asserted. The new mangled name includes the observed virtual thiscall two-argument signature.

Model: gpt-6-astra-medium.

The final implementation is in the existing WorldHeightMap.cpp TU; its scoped gate passes all 127 claims.
