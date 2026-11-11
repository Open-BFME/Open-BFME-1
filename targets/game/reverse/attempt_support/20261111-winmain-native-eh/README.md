# WinMain: complete native EH ownership and a 1362-byte near match

Date: 2026-11-11. Model: openai/gpt-6.1-sol. Target inputs: BFME1 retail1.03-unpacked; integration HEAD `5d2ac32d558726920d9fe2d4d27d01399b119eff`. This is **banked evidence, not a recovery or linking gain**. No nonmatching source was placed in `game/`, no function/data row changed, and no generated source was edited.

## Resume from the bank, not the old Zero Hour-only attempts

`targets/game/reverse/attempts/0x000600f0.cpp` contains the complete candidate and its same-TU tokenizer, trim and window initializer context. Its underlying source payload SHA256 is `e6937817964ed6d86f4eecfc131ebbafcda0b7c0da52b6f96a1f5f65dc7fc0e0` before re_log's two metadata lines. Actual MSVC13.10.3077 `/O2 /GR- /DNDEBUG /MD /EHsc` emission is **1362 bytes,97 relocation sites,25 non-relocation byte differences**, first at+0x255. Explicit1362-byte diagnostic fraction is0.9816446. The normal stash scorer uses the current1356-byte ledger extent and may report a lower score because the extra6 bytes remain separately claimed there; do not change a ledger extent to inflate this score.

Reproduce in this lane with its approved private Wine prefix:

```
env WINEPREFIX="$PWD/build/wineprefix-sol12h" WINEARCH=win64 BFME_OBJSTORE=off WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= python3 tools/probe.py targets/game/reverse/attempts/0x000600f0.cpp _WinMain@16 0x000600F0 --size 1362 --all
```

Another lane must use its own approved prefix, not borrow this mutable prefix. `probe.py` uses private experiment outputs; never compile a diagnostic into `build/match/`. `candidate-manifest.json` records the actual command, object/source hashes, retail image hash, and147 exact input/dependency hashes, including the real SDK/ATL headers and compiler components. `probe.raw.txt` is the complete comparison. Relocation masking is discovery only: this is **not** normal byte, DIR32, EH, class-contract or linking acceptance.

## Native identity and boundary: independently witnessed

The original MSVC CRT `_WinMainCRTStartup` calls `_WinMain@16` through the actual five-byte ILT0004AC0A→000600F0. The complete native body uses an EBP frame and returns `ret16`; this is the Win32 four-word stdcall entry, not an inferred name from donor offsets.

`native-eh.json` records the independent retail chain:

- Main's prologue pushes handlerVA00FF277C (RVA00BF277C).
- Its `MOV EAX,FuncInfo;JMP __CxxFrameHandler` points to FuncInfoRVA00DDFBDC: magic19930520,10states,1try.
- Sole TryBlockMap atVA011DFBC8 is try0..8/catchHigh9,1catch, HandlerType arrayVA011DFBB8.
- HandlerType words are `(0,0,0,0046063C)`: catch-all entryRVA0006063C.
- That entry is exactly `B8 D3 04 46 00 C3`, returning continuationVA004604D3, main+0x3E3. The continuation restores EH state and returns0/ret16. INT3 padding starts60642.

Thus6063C is **EH-owned catch code, not an ordinary constant-return API**. The existing6B `Rva0006063CGet` source is a false ordinary-getter identity, notwithstanding its byte match. Its source explicitly references the old `?d_000600f0@@YAXXZ`+3E3. Correct it together with main through normal identity/boundary admission; inspect former getter references and old dump consumers. Do not infer any parent from adjacency.

Parent independently parsed the same chain and approved main plus its metadata-linked catch/cleanup/handler family. Prefer one1362B `_WinMain@16` row only if actual clean emission and the normal gate support it, retiring both conflicting old claims/tombstones. An honestly separate1356B parent+6B emitted catch label is permissible if the compiler/tool requires it, never an invented handwritten gen-funclet. Do not overlap/double-count, add aliases/pins/masks, edit generated sources or weaken admission. A refusal reconciling the two old ranges must be preserved and discussed, not bypassed.

`candidate-coff-eh.json` independently walks the **actual candidate COFF** relocations: main prologue→its own emitted handler→FuncInfo10states/1try→try0..8/catchHigh9→its own catch at+54C→its own continuation+3E3. The candidate naturally emits the full1362B, including this6B catch. This supports the full extent without preselecting it to force green. EH topology matches; cleanup receiver slots do **not** all match yet.

## What the donor supplies, and what BFME1 proves

Read-only BFME2 revision `76f0baefa6f285d54bc1ca922397674312a5913f`, `Code/GameEngine/Source/Main/WinMain.cpp`, is a substantive clean source lead, unlike the repeatedly retried970–1003B Zero Hour-only forms. It establishes a semantic/structural guide for IMM32, command-line parsing, splash, mutex, launcher and teardown. Its1388B matched row includes its analogous formerly false6B getter/catch. The checkout is shallow: path history exposes only snapshot commit76f0baef; no older source commit was available locally and no per-transfer deepen/fetch was made. Relevant `docs/recipes.md` and the existing `reverse/attempt_support/0x00001c32-worker-20261019.md` WinMain-owner10/10 gate record were inspected, not treated as BFME1 verification. Donor Version has7strings/0x30 and teardown byte+C74; **neither is a BFME1 layout fact**.

BFME1's full decode, prior detailed attempt38049, actual callee bodies and original CRT independently establish: inline IMM32 lookup/call(-1)/FreeLibrary; inline command-line copy toVA012ED270; ANSI executable-directory setup; argc1/argv20; en-dash repair; per-token `-win`/`-automatch`; `-DX` symbol lookup; ATL splash JPG then BMP; mutex/window activation; Version0x24 with4string handles+10..1C and setVersion(1,3,0,13); launcher checks; actual GameMain edge; cleanup selected by the byte at GlobalData+D04. The bank uses a byte-offset view for that unproven member name, not the donor's field name/layout.

The first official donor trial failed only because BFME2's `// platformsdk` marker was not supplied by BFME1 trial defaults. An SDK-only map then lost the donor ASCII quoted include root. Neither failure is body evidence. A subsequent private direct compile supplied **both existing real SDK and donor ASCII roots**, preserved original donor quoted-header context, and succeeded with B1's toolchain; it emitted1631B, not a target match. No donor tree or nested BFME1 reference was modified/initialized.

The bank then adapts the witnessed B1 differences and uses the actual VS2003 `atlimage.h`, BFME1 canonical string headers and EA GeneralsMD `version.h`. Existing matched `NextParam.cpp` and initializer source provide the whole-TU inline/private-register context. Removing the fake support callers, using the real main, and preserving the initializer's proven EDI+2stack/AL ABI gives the407B initializer naturally. Strict SDK handle types originally changed its mangled name; keeping the existing opaque-pointer ABI/storage with explicit Win32 casts restored its existing symbol and the same407B. No bridge/alias/pin was introduced.

## Exact remaining mismatch and prerequisite graph

The initial mistaken argv32 interpretation emitted1362B with42 differences and a frame48B too large. Native's0x14 loop bound and80B argv span require **20**, restoring every prefix byte through the CImage block and leaving25 differences. Do not repeat argv32.

Current25 differences are stack-home/permutation operands, not missing startup branches:

- CImage base is EBP-48 instead of native EBP-44; its constructor stores, Load/bitmap use and destructor receivers follow that4B shift.
- First GetRegistryLanguage result uses dead argument EBP+10 in both. The second uses EBP-18 instead of native reusing EBP+10.
- Later Version allocation/by-value string temporary homes are permuted. In the emitted EH map: state1 uses-48 versus native-44; state5 allocation cleanup uses+10 versus native+14; states6/7/8 use+10/+14/+8 versus native+14/+8/-4C. States0,2–4,9 and the try/catch/continuation relationship agree.

Do not treat the candidate's full EH graph as verified while these cleanup homes differ.

Normal `compile_function` diagnostics, with **no gen-alias mode**, resolve every REL32 except two CImage destructor calls and two Version destructor calls. DIR32 operands in that diagnostic are retail-rebased, not identity-verified. The missing provider names correspond to existing opaque class identities:

- Actual SDK `ATL::CImage` constructor at5C110/90 and complete destructor at5EC20/134 are both emitted by this candidate and reproduce all requested bytes after ordinary REL32 resolution. Their existing rows call the class `Rva0005C110Surface`.
- SDK scalar deleting destructor at5FA60/30 matches all but the unresolved complete-dtor call. Its vtable relationship needs normal data/class-contract proof, not a second alias on the same body.
- Actual EA `Version` destructor at5F4B0/103 is emitted and similarly reproduces the requested bytes. Existing row is `Open2Dtor05F4B0`, one of six unrelated destructors in `Open2Destructors.cpp`; do not delete that whole file.

These are **diagnostic provider leads**, not reviewed identity changes or full DIR32/body-guard/EH proofs. `provider-diagnostic.json` preserves the exact limits. Any correction must reconcile providers, consumers, vtable/data ownership and their own EH families through normal tools. No shared header or existing class provider was edited here. Existing partial declaration views (`WW3D`, `Rva0006B610`, etc.) are still bank-only and require the canonical-header/class-contract review before landing, not a silent new private interface.

Three additional main globals are intentionally **unresolved declarations**, not invented providers: command-line bufferVA012ED270, windowed byteVA012ED23C, bitmap pointerVA012ED24C. The buffer's full native allocation extent remains unproved; never copy the512B diagnostic control into a provider. TheVersion's4B pointer is independently zero atVA012ED644, but its correct provider ownership is also a prerequisite. Known-extent/definition controls did not fix codegen and establish no array extent. No normal source/data admission was attempted for these declarations.

## Bounded experiments already ruled out

`trials.json` summarizes60 isolated trials; useful minimal source alternatives are in `selected-variants.patch`. Full local commands/objects/logs remain under `build/integration/winmain-*`. Do not rerun unchanged variants:

- Named first/second/both language values:1363–1366B and374–459differences; worse lifetime/EH shape.
- Extra full-expression blocks, filePath/image declaration order/scope, local image rename, old loop-index scope: unchanged25.
- Named Load HRESULT:27differences, not a cure. Goto/unbraced guard variations did not merge the return temporary; bounded format loops produced1454–1461B rather than native unrolling.
- Inline formatting/IMM32 helpers and IMM32 lexical scope: unchanged25. Placement-storage lifetime control grew27B/465differences and was rejected; not proposed source.
- Private inheritance versus canonical public inheritance, StringBase composition with explicit/implicit string destructor: unchanged25. No shared header change is justified by these controls.
- Hiding SDK destructor/actual LPCTSTR Load definitions in private header copies: unchanged25. The first IStream overload control is not evidence about the ANSI call; the later ANSI controls were run separately.
- `/G6`, `/Oy-`, `/Zc:forScope`, `/GX`: unchanged25; `/G7`:1309B/824differences. The `-GS-` control produced compiler warning D4002 unknown `-G-`; it is **not** a supported security-flag comparison.
- Parameter top-level const, new Version versus new Version(), named allocation and a lexical allocation block: unchanged25. Named command-line copy worsened66differences.
- Scalar-global definitions, declared array extent and an isolated512B array definition: unchanged25. The latter was only a codegen control, not a native-size hypothesis accepted as fact.

After roughly90minutes of substantive target work, the complete semantic reconstruction, exact emitted extent, metadata parentage and provider leads were preserved; further routine spelling searches had stopped improving the25-byte stack-home mismatch. Resume only with a new evidence-backed compiler/context/lifetime explanation and the prerequisite graph in view. Do not ship this nonmatching source or claim source closure/bootability.
