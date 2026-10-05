# FXList FieldParse identities

Corrected: the nine listed addresses are const FieldParse arrays. The shared FXNugget spelling and the eight derived FXNugget spellings describe their witnessed users; the invented WideFieldParse spellings are competing declarations of those same arrays. Each array is defined once in `game/GameEngine/Source/Common/WideBuildFieldParsePair.cpp`, which owns the matched retail builders. The old DIR32 rows remain additive history.

Retail has no PE base-relocation directory (`build/rlink/contracts-retail.log`). Here a relocation means a verified pointer field and its compiled COFF DIR32 relocation. FieldParse is the reference structure of four 32-bit fields: token pointer, cdecl parser pointer, userData and destination offset. Retail `INI::initFromINIMulti` at RVA 0x00851910 passes `(INI *, instance, instance + tableOffset + fieldOffset, userData)` and removes the four arguments after the callback at VA 0x00C51A11. Its field lookup helper and MultiIniFieldParse appender provide the record and table contract. `build/rlink/contracts-retail.log` contains the instructions. Table-address consumers pass or return the table; the shared INI routines read it and write the destination instance. No direct table write appears in those measured consumers. The tables lie in retail read-only `.rdata`.

The matched parser users are `?parse@AttachedModelFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C460), `?parse@BuffNuggetFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042D680), `?parse@CameraShakerVolumeFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C1C0), `?parse@CursorParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042CCA0), `?parse@DynamicDecalFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042BF50), `?parse@FXListAtBonePosFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C860), `?parse@LaserFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C090), `?parse@LightPulseFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042BE30), `?parse@ParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042CB80), `?parse@RayEffectFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042BD10), `?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042BBE0), `?parse@TerrainScorchFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C600), `?parse@TintDrawableFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C740), `?parse@ViewShakeFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042C320), `?parse@EvaEventFXNugget@@SAXPAVINI@@PAX1PBX@Z` (RVA 0x0042BAA0). Each per-address raw log identifies the actual row, source, full extent and disassembly. The shared table is appended by the base builder and each derived builder and parser. The Zero Hour `GameClient/FXList.cpp` declares the matching Sound, RayEffect and LightPulse local FieldParse arrays and class parse roles. BFME-only keys and classes are established by retail field strings and the matched FXList registrations, not extrapolated from Zero Hour.

Shader userData names ALPHA and ADDITIVE, and BuffType userData names DO_NOT_USE_THIS_TYPE, Healing, LeaderShip, GloriousCharge, Dominate and Cursed, are read completely in `build/rlink/contracts-retail.log`. Their address-bearing external spellings describe verified roles; no definition or data row for those dependency arrays is claimed. Callback spellings reference existing ledger bodies or pins. The shared model-condition callback keeps the matched address-derived Rva00369AD0 spelling rather than inventing a semantic identity.

### VA 0x010F2480: FXNuggetFieldParse

The retail datum occupies 128 bytes in `.rdata`. Its complete logical array contains 8 records, including the first all-zero terminator. The initial bytes are `1c 60 0a 01 65 98 43 00 00 00 00 00 0c 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2480-retail.log`. Direct address-reference sites have RVAs 0x00427481, 0x004274A6, 0x004274D6, 0x00427506, 0x00427536, 0x00427566, 0x00427596, 0x004275C6, 0x004275F6, 0x00427656, 0x00427796, 0x004277C6, 0x004277F6, 0x00427826, 0x00427C96, 0x00427CC6, 0x0042BB3F, 0x0042BC6F, 0x0042BD8F, 0x0042BEAF, 0x0042BFCF, 0x0042C11F, 0x0042C26F, 0x0042C3B3, 0x0042C4FF, 0x0042C694, 0x0042C7BF, 0x0042C8DF, 0x0042CBFF, 0x0042CD1F, 0x0042D6FF. The next pre-existing named datum is at VA 0x010F2550; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?FXNuggetFieldParse@@3QBUFieldParse@@B` (2 game files), `?WideTblB00427490@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB004274C0@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB004274F0@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427520@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427550@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427580@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB004275B0@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB004275E0@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427640@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427780@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB004277B0@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB004277E0@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427810@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427C80@@3QBVWideFieldParse@@B` (1 game files), `?WideTblB00427CB0@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F2550: EvaEventFXNuggetFieldParse

The retail datum occupies 64 bytes in `.rdata`. Its complete logical array contains 4 records, including the first all-zero terminator. The initial bytes are `3c 25 0f 01 65 4b 40 00 00 00 00 00 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2550-retail.log`. Direct address-reference sites have RVAs 0x00427498, 0x0042BB30. The next pre-existing named datum is at VA 0x010F259C; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?EvaEventFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA00427490@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F259C: SoundFXNuggetFieldParse

The retail datum occupies 32 bytes in `.rdata`. Its complete logical array contains 2 records, including the first all-zero terminator. The initial bytes are `94 c0 09 01 e0 1e c5 00 00 00 00 00 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f259c-retail.log`. Direct address-reference sites have RVAs 0x004274C8, 0x0042BC60. The next pre-existing named datum is at VA 0x010F25E8; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?SoundFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA004274C0@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F25E8: RayEffectFXNuggetFieldParse

The retail datum occupies 64 bytes in `.rdata`. Its complete logical array contains 4 records, including the first all-zero terminator. The initial bytes are `94 c0 09 01 e0 1e c5 00 00 00 00 00 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f25e8-retail.log`. Direct address-reference sites have RVAs 0x004274F8, 0x0042BD80. The next pre-existing named datum is at VA 0x010F2678; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?RayEffectFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA004274F0@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F2678: LightPulseFXNuggetFieldParse

The retail datum occupies 96 bytes in `.rdata`. Its complete logical array contains 6 records, including the first all-zero terminator. The initial bytes are `50 c7 07 01 50 2f c5 00 00 00 00 00 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2678-retail.log`. Direct address-reference sites have RVAs 0x00427528, 0x0042BEA0. The next pre-existing named datum is at VA 0x010F277C; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?LightPulseFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA00427520@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F2798: DynamicDecalFXNuggetFieldParse

The retail datum occupies 240 bytes in `.rdata`. Its complete logical array contains 15 records, including the first all-zero terminator. The initial bytes are `d4 9f 0e 01 e0 1e c5 00 00 00 00 00 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2798-retail.log`. Direct address-reference sites have RVAs 0x00427558, 0x0042BFC0. The next pre-existing named datum is at VA 0x010F2980; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?DynamicDecalFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA00427550@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F2980: BuffNuggetFXNuggetFieldParse

The retail datum occupies 192 bytes in `.rdata`. Its complete logical array contains 12 records, including the first all-zero terminator. The initial bytes are `74 29 0f 01 50 10 c5 00 bc 04 0f 01 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2980-retail.log`. Direct address-reference sites have RVAs 0x00427588, 0x0042D6F0. The next pre-existing named datum is at VA 0x010F2AB0; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?BuffNuggetFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA00427580@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F2AB0: LaserFXNuggetFieldParse

The retail datum occupies 64 bytes in `.rdata`. Its complete logical array contains 4 records, including the first all-zero terminator. The initial bytes are `a0 2a 0f 01 e0 1e c5 00 00 00 00 00 b4 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2ab0-retail.log`. Direct address-reference sites have RVAs 0x004275B8, 0x0042C110. The next pre-existing named datum is at VA 0x010F2B28; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?LaserFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA004275B0@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

### VA 0x010F2B28: CameraShakerVolumeFXNuggetFieldParse

The retail datum occupies 64 bytes in `.rdata`. Its complete logical array contains 4 records, including the first all-zero terminator. The initial bytes are `10 ee 08 01 20 2b c5 00 00 00 00 00 c0 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/010f2b28-retail.log`. Direct address-reference sites have RVAs 0x004275E8, 0x0042C260. The next pre-existing named datum is at VA 0x010F2BAC; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?CameraShakerVolumeFXNuggetFieldParse@@3QBUFieldParse@@B` (1 game files), `?WideTblA004275E0@@3QBVWideFieldParse@@B` (1 game files). Counts include macro declarations and do not decide identity.

A pointer that follows an E9 to a different final body, a token or scalar differing from the saved retail bytes, an interior DIR32 or overlapping data row, or a user passing a different record layout would refute this correction. Function bytes must continue matching in every changed source.

Verification: `build/rlink/pin-fx-literals.log`, `add-010f*.log`, `add-sound.log`, `build-fx-final.log` and the final per-file build logs. All fields and pointer targets are checked by add_data_match; string DIR32 spellings are added only after byte comparison.
