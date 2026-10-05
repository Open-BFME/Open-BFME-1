# TheAudio at VA 0x012ED668

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?TheAudio@@3PAVAudioManager@@A`. This datum is one `AudioManager *` object in retail `.data`, with size 4 byte(s) and initial bytes `00000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

The reference Common/Audio/GameAudio.cpp defines AudioManager *TheAudio=NULL and GameAudio.h declares it. Retail matched audio-event users load the pointer as ECX and dispatch the addAudioEvent/removeAudioEvent virtual operations, with AudioEventRTS arguments. MilesAudioManager destructor RVA 0x006ACF50 compares this against the cell and clears it if equal, establishing the manager singleton independently of client-update view names. The reference MilesAudioManager destructor clears TheAudio for the same lifetime. GameEngine client-subsystem updates through this receiver do not establish a distinct AudioClient singleton. Existing local ABI views are retained as casts at their uses; no inheritance or callee identity is invented.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012ED668, 0x012ED66C)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x0006B910`, `0x00079060`, `0x0007C530`, `0x0007CAB0`, `0x0007EEB0`, `0x00087C30`, `0x00087CF0`, `0x00088480`, `0x000917D0`, `0x00091880`, `0x00091930`, `0x000919E0`, `0x00091A90`, `0x000B0DF0`, `0x000B1030`, `0x000B1360`, `0x000B1590`, `0x000B17C0`, `0x000B1B70`, `0x000B2370`, `0x000B2BA0`, `0x000B33F0`, `0x000B3630`, `0x000B4B70`, `0x000B6030`, `0x000BABF0`, `0x000BB9A0`, `0x000BBB60`, `0x000BD640`, `0x000BDD20`, `0x000C25B0`, `0x000C8610`, `0x000C8730`, `0x000CBEC0`, `0x000CBFA0`, `0x000CC0B0`, `0x000CC1C0`, `0x000CC2C0`, `0x001083D0`, `0x0010CAC0`, `0x001109CF`, `0x001112D0`, `0x0016B140`, `0x0016E6C0`, `0x00172430`, `0x00172600`, `0x00172D80`, `0x00174A20`, `0x0017ECB0`, `0x0018D390`, `0x0018D460`, `0x0018D600`, `0x0019FF20`, `0x001B2C70`, `0x001B2E20`, `0x001B3510`, `0x001B3900`, `0x001C81C0`, `0x001C8440`, `0x001CC250`, `0x001CDE30`, `0x001CEAD0`, `0x001D0610`, `0x001D22C0`, `0x001D88C0`, `0x001F2E80`, `0x001FC6B0`, `0x001FC7E0`, `0x001FC950`, `0x001FD970`, `0x001FE050`, `0x001FE910`, `0x001FEB50`, `0x001FEC30`, `0x001FECD0`, `0x001FF1C0`, `0x00200DF0`, `0x00201960`, `0x002080B0`, `0x0020A5A0`, `0x0020E580`, `0x00211D40`, `0x00217C10`, `0x00217E60`, `0x00218690`, `0x00218A00`, `0x00221570`, `0x00221630`, `0x00221720`, `0x00227DC0`, `0x0023E5F0`, `0x00254CF0`, `0x002563E0`, `0x00267D80`, `0x00268CB0`, `0x00285650`, `0x00286440`, `0x00293010`, `0x00293050`, `0x00293440`, `0x00293520`, `0x00294410`, `0x00299250`, `0x0029D460`, `0x0029DB60`, `0x0029E330`, `0x002A4F90`, `0x002A71E0`, `0x002A7670`, `0x002A7790`, `0x002A8540`, `0x002A8940`, `0x002A9420`, `0x002A9850`, `0x002AB690`, `0x002AC620`, `0x002AD670`, `0x002B5800`, `0x002B6A10`, `0x002B6A60`, `0x002B9E50`, `0x002B9EA0`, `0x002C82C0`, `0x002C85F0`, `0x002C8790`, `0x002D3080`, `0x002D3140`, `0x002D33E0`, `0x002D34B0`, `0x002D3550`, `0x002D35A0`, `0x002E39A0`, `0x002E64C0`, `0x002E6650`, `0x002E6710`, `0x002E6850`, `0x002ED960`, `0x002EDA50`, `0x002EDA90`, `0x002EDAC0`, `0x002EDAF0`, `0x002EE880`, `0x002EE950`, `0x002EEA10`, `0x002EEA30`, `0x002EEA50`, `0x002EF270`, `0x002EF2A0`, `0x002EF2E0`, `0x002EF310`, `0x002EF830`, `0x002EFE20`, `0x002EFE40`, `0x002EFE60`, `0x002EFE90`, `0x002EFEB0`, `0x002EFEE0`, `0x002EFF00`, `0x002F2000`, `0x002F4080`, `0x002F40E0`, `0x002F4360`, `0x002F44E0`, `0x002F4650`, `0x002FAF10`, `0x002FD280`, `0x00303BF0`, `0x00323980`, `0x003258E0`, `0x00337200`, `0x0034B9A0`, `0x0034E5B0`, `0x0034E810`, `0x0036BBA0`, `0x0036BC90`, `0x003720F0`, `0x00373B30`, `0x00383490`, `0x003839E0`, `0x003854C0`, `0x0038D100`, `0x00394260`, `0x00396B00`, `0x00396D40`, `0x00397350`, `0x00397540`, `0x0039B090`, `0x0039B2B0`, `0x0039B610`, `0x003A3E50`, `0x003A5670`, `0x003A5A10`, `0x003C29D0`, `0x003C2BD0`, `0x003C3850`, `0x003CC890`, `0x003CCB70`, `0x003D1A60`, `0x004092A0`, `0x0040F780`, `0x00411BE0`, `0x00411C30`, `0x00417430`, `0x004175F0`, `0x00417710`, `0x00418A60`, `0x00418DA0`, `0x00419A10`, `0x0041ABE0`, `0x0041AD20`, `0x0041AE50`, `0x0041B040`, `0x0041B150`, `0x0041CCD0`, `0x0041D290`, `0x004237E0`, `0x00423B70`, `0x004289B0`, `0x00428A60`, `0x0043E700`, `0x0046F1A0`, `0x00479770`, `0x00490630`, `0x00490890`, `0x004910C0`, `0x00491110`, `0x004916D0`, `0x00491940`, `0x00491A40`, `0x00491E30`, `0x00492400`, `0x004B4010`, `0x004B42F0`, `0x004B5E40`, `0x004B6190`, `0x004B85F0`, `0x004BBFC0`, `0x004C6AF0`, `0x004C6C60`, `0x004DFEF0`, `0x004ECD10`, `0x004EDAD0`, `0x0051B6B0`, `0x0051B720`, `0x0051B7E0`, `0x0051BCE0`, `0x0051C2D0`, `0x0051D590`, `0x0051D690`, `0x0051DE00`, `0x0051DE70`, `0x0051E010`, `0x0051E0F0`, `0x0051E280`, `0x0055DCB0`, `0x0055E470`, `0x0055F290`, `0x00560280`, `0x0056E230`, `0x00573000`, `0x005774E0`, `0x0057F100`, `0x0057F130`, `0x0057F250`, `0x0057F5B0`, `0x0057F7A0`, `0x0057FB40`, `0x00589940`, `0x00594010`, `0x0059D2D0`, `0x005A00B0`, `0x005A0130`, `0x005A8A10`, `0x005A92D0`, `0x005AA450`, `0x005AFFB0`, `0x005B3AD0`, `0x00605380`, `0x006059F0`, `0x00606180`, `0x006091B0`, `0x00609E30`, `0x0060A880`, `0x0060F3C0`, `0x0060F4B0`, `0x00610140`, `0x00613CC0`, `0x006145C0`, `0x006156A0`, `0x00615850`, `0x006176A0`, `0x0061BB50`, `0x0061BBB0`, `0x0061BC10`, `0x0061BD90`, `0x0061C060`, `0x00625AF0`, `0x00627FA0`, `0x00662CE0`, `0x00667060`, `0x00699AB0`, `0x00699AF0`, `0x00699B40`, `0x00699B90`, `0x006A3790`, `0x006A37A0`, `0x006A37B0`, `0x006ACF50`, `0x006B6480`, `0x006BA030`, `0x006BA610`, `0x006C3170`, `0x006ECF80`, `0x007E3C20`, `0x007E5420`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?AudioGlobal004092A0@@3PAUAudioView004092A0@@A` | 0 |
| `?AudioGlobal0040F780@@3PAUAudio0040F780@@A` | 0 |
| `?R2Ptr012ED668@@3PAVR2GlobalReceiver@@A` | 0 |
| `?Rva012ed668@@3PAVRva0041D290Audio@@A` | 1 |
| `?TheAudio@@3PAVAudioManager@@A` | 212 |
| `?TheAudio@@3PAVRva003CC890Audio@@A` | 0 |
| `?TheAudio@@3PAVRva004910C0Audio@@A` | 0 |
| `?TheAudio@@3PAVRva0051D690Audio@@A` | 0 |
| `?TheAudio@@3PAVRva007E5420AudioManager@@A` | 0 |
| `?TheAudioClientUpdate@@3PAURva005A00B0AudioClient@@A` | 1 |
| `?TheAudioClientUpdate@@3PAVAudioClient@@A` | 0 |
| `?TheAudioClientUpdate@@3PAVAudioClientUpdate@@A` | 0 |
| `?TheAudioClientUpdate@@3PAVAudioClientUpdateSub@@A` | 0 |
| `?TheAudioClientUpdate@@3PAVBfmeAudioClient@@A` | 0 |
| `?TheAudioClientUpdate@@3PAVBfmeAudioManager002EF2A0@@A` | 0 |
| `?TheAudioClientUpdate@@3PAVClientSubsystem@@A` | 1 |
| `?TheAudioClientUpdate@@3PAVRva0051D690Audio@@A` | 1 |
| `?TheAudioClientUpdate@@3PAVRva005A00B0AudioClient@@A` | 1 |
| `?TheAudioClientUpdate@@3PAXA` | 0 |
| `?TheAudioClientUpdate@@3RAVBfmeAudioManager002EF310@@A` | 0 |
| `?TheBattlePlanUpdateOwner@@3PAVBattlePlanUpdateOwner@@A` | 0 |
| `?TheBfmeAudio491110@@3PAVBfmeAudioManager491110@@A` | 0 |
| `?TheBfmeGlobal_012ed668@@3PAVBfmeGlobal_012ed668@@A` | 0 |
| `?TheBfmeTarget_002EDA90@@3PAVGen_002EDA90Target@@A` | 0 |
| `?TheBfmeTarget_002EDAC0@@3PAVGen_002EDAC0Target@@A` | 0 |
| `?TheGenReturner@@3PAVGenReturner@@A` | 0 |
| `?TheProductionUpdateOwner@@3PAVProductionUpdateOwner@@A` | 0 |
| `?g_Rva002EFEGlobal@@3PAVRva002EFEGlobal@@A` | 0 |
| `?g_Va012ED668@@3PAVBfmeAudioClientUpdate_001FE050@@A` | 0 |
| `?g_Va012ED668@@3PAVBfmeAudioClientUpdate_NT@@A` | 0 |
| `?g_Va012ED668@@3PAVVDispatch1@@A` | 0 |
| `?g_audio00294410@@3PAVAudio00294410@@A` | 0 |
| `?g_audio00299250@@3PAVAudioDispatch00299250@@A` | 0 |
| `?g_audio012ED668@@3PAVRva00411C30Audio@@A` | 0 |
| `?g_bfme935GlobA@@3PAVBfmeGlob935A@@A` | 0 |
| `?g_bfme939GlobC@@3PAVBfmeGlob939C@@A` | 0 |
| `?g_bfmeA1082@@3PAVBfmeA1082@@A` | 0 |
| `?g_bfmeAudioERR@@3PAVBfmeAudioERR@@A` | 0 |
| `?g_bfmeAudioFU@@3PAVBfmeAudioFU@@A` | 0 |
| `?g_bfmeAudioGG@@3PAVBfmeAudioGG@@A` | 0 |
| `?g_bfmeB1019@@3PAVBfmeB1019@@A` | 1 |
| `?g_bfmeB1058@@3PAVBfmeB1058@@A` | 0 |
| `?g_bfmeG1022@@3PAVBfmeG1022@@A` | 0 |
| `?g_bfmeG1023@@3PAVBfmeG1023@@A` | 0 |
| `?g_bfmeG1024@@3PAVBfmeG1024@@A` | 0 |
| `?g_bfmeGlobMC@@3PAVBfmeGlobMC@@A` | 0 |
| `?g_bfmeObjFFA@@3PAUBfmeGlobFFA@@A` | 1 |
| `?g_bfmeSinkBHD@@3PAVBfmeSinkBHD@@A` | 0 |
| `?g_bfmeSinkSB@@3PAVBfmeSinkSB@@A` | 0 |
| `?g_bfmeSinkY@@3PAVBfmeSinkY@@A` | 0 |
| `?g_rva002B6A60Audio@@3PAVRva002B6A60Audio@@A` | 0 |
| `?g_rva002B9EA0Audio@@3PAVRva002B9EA0Audio@@A` | 0 |
| `?g_rva002C8790Audio@@3PAVRva002C8790Audio@@A` | 0 |
| `?g_rva003A3E50Audio@@3PAVRva003A3E50Audio@@A` | 0 |
| `?rva004BBFC0_audio@@3PAVRva004BBFC0Audio@@A` | 0 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A manager lifetime publication or destruction using another global, an audio-event dispatch through a different singleton, or any differing byte in a changed function would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
