# Voice FieldParse table

Corrected: g_voiceFieldParse is the const FieldParse array at VA 0x01093870. This descriptive role is retained; the composite WideFieldParse spelling is replaced. The defining source is the main getter owner, `game/GameEngine/Source/GameClient/Drawable/Behavior/RandomSoundSelectorFieldParse.cpp`.

Retail has no PE base-relocation directory (`build/rlink/contracts-retail.log`). Here a relocation means a verified pointer field and its compiled COFF DIR32 relocation. FieldParse is the reference structure of four 32-bit fields: token pointer, cdecl parser pointer, userData and destination offset. Retail `INI::initFromINIMulti` at RVA 0x00851910 passes `(INI *, instance, instance + tableOffset + fieldOffset, userData)` and removes the four arguments after the callback at VA 0x00C51A11. Its field lookup helper and MultiIniFieldParse appender provide the record and table contract. `build/rlink/contracts-retail.log` contains the instructions. Table-address consumers pass or return the table; the shared INI routines read it and write the destination instance. No direct table write appears in those measured consumers. The tables lie in retail read-only `.rdata`.

### VA 0x01093870: g_voiceFieldParse

The retail datum occupies 1760 bytes in `.rdata`. Its complete logical array contains 110 records, including the first all-zero terminator. The initial bytes are `60 38 09 01 da e2 42 00 00 00 00 00 00 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/01093870-retail.log`. Direct address-reference sites have RVAs 0x0013CE11, 0x0013E189. The next pre-existing named datum is at VA 0x010940B0; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?WideTblB0013E170@@3QBVWideFieldParse@@B` (1 game files), `?g_voiceFieldParse@@3QBUFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

All nonterminating records have null userData and callback ILT VA 0x0042E2DA, whose five bytes E9 C1 D6 08 00 lead to RVA 0x000BB9A0. That target already has the INIParseDynamicAudioEventRTSShim parser pin. The record keys are VoiceSelect through SoundCrushing, with every intervening key and destination offset recorded in the raw log. The no-argument getter at RVA 0x0013CE10 returns this address. ThingTemplate builder RVA 0x0013E170 adds it at instance offset 224. The matched RandomSoundSelector builder obtains the getter through its ILT and adds the same table at offset 8. These shared users establish a reusable voice and sound block, not a WideFieldParse class. Zero Hour ThingTemplate fields contain the corresponding voice and sound FieldParse roles; BFME expanded and separated the block.

A pointer that follows an E9 to a different final body, a token or scalar differing from the saved retail bytes, an interior DIR32 or overlapping data row, or a user passing a different record layout would refute this correction. Function bytes must continue matching in every changed source.

Complete pointer and token checks: `build/rlink/pin-voice-literals.log` and `add-01093870.log`.
