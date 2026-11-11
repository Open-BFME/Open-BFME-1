# Native set<AsciiString> constructor at RVA00078100

BFME 1 retail SHA256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Input HEAD8efcc0937c; only the Miles consumer is under repair. This corrects
`tg_00078100`'s generated tree<int> spelling, not its54-byte extent.

## Independent target identity and boundary

The existing symbols.csv constructor entry records3 native calls through ILT
00022FA7 (006B8C06,00773AEF,00773C07). They construct function-static sets whose
find uses the AsciiString tree and whose insert is insert_unique, not a
multiset insertion. Raw PE disassembly independently verifies the two static
sets at01305A68/01305A58: constructor calls00773AEF/00773C07 -> thunk22FA7,
find calls00773B10/00773C28 -> thunk3071 ->38C0E0, and insert calls00773B30/
00773C48 -> thunk1BC02 ->C0430. Their matched Rva007739F0ModelVariant.cpp
uses static set<AsciiString> values, and the find provider's tracked
0038c0e0-00076a90-asciistring-set-tree.md establishes its AsciiString keys.
Raw routes/disassembly are preserved in build/miles-set-native-{routes,callers}.txt. The native constructor allocates a0x14-byte header node,
clears its color/count and self-links the empty tree. RET at+0x35, followed by
INT3, establishes54 bytes. The only direct callee is the existing
`_STL::__node_alloc<true,0>::_M_allocate`, called with20 bytes; no pin is added.

The exact existing decorated identity is:
`??0?$set@VAsciiString@@U?$less@VAsciiString@@@_STL@@V?$allocator@VAsciiString@@@3@@_STL@@QAE@XZ`.
Its ILT oracle result is CONFIRMED, p_false=1.96e-04. The old generated
Rb_tree<int> identity is contradicted. This is not an inference from equal
constructor bytes: the typed native users, unique-insert relationship and
independent thunk-name ordering supply identity evidence.

## Miles relationship and ABI

Native Miles constructor006B0E00 operands+282/+287 pass destructor ILT0003B2B9
and constructor ILT00022FA7 to the EH vector constructor, count3, stride12,
receiver+998. The destructor routes through matched5-byte set<AsciiString>
forwarder00077FB0 to000775F0; tree erase00076A90 destroys the AsciiString value
at node+10. The destructor oracle independently confirms the exact existing
set identity (p_false=6.52e-04). Thus the12-byte array may use the canonical
set<AsciiString> type rather than the opaque Rva00478100 view. No per-view
semantic member name is inferred; m_998 remains unchanged.

PeerDefs.cpp already emits the native54-byte constructor and5-byte destructor.
That unchanged provider is selected for the row, rather than adding another
provider or an alias. Existing correct deque providers independently use
Rva006AADB0Element as char[4]; native initialize_map shifts by5 and advances
nodes by0x80, establishing32 four-byte values per128-byte node. The Miles
int[2] view is incompatible. class_contract's4-byte majority is corroboration,
not retail identity/layout proof by itself.

## Donor provenance and rejected adaptation

Pinned BFME 2 revision76f0baefa6f285d54bc1ca922397674312a5913f,
Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp:
set<AsciiString> m_atA14[3] and declaration-only template specializations provide
a structural/emission lead. BFME 2+A14 is NOT imported as a BFME 1 offset:
BFME 1+998 and the callbacks/stride/count above establish this mapping.
No donor headers, compiler settings or address pins are used. Local consumer
is the existing game/GameEngineDevice/Source/MilesAudioDevice/
MilesAudioManagerConstructor.cpp; provider is existing
 game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp.

The prior repair-milesaudio-ilt-debts-20261111.md rejected fake pins and a bare
type swap, attributing two failed funclets to inlining. Current measurements
correct that interpretation: native EH-state repinning fixes the two apparent
mismatches. A private no-destructor-specialization control preserves ALL495
nondebug sections (bytes, flags, owners, normalized relocations). The declaration
has no measured effect and is removed. No suppression policy is required.
Specializing the constructor is rejected: it stops the required native inline
initialization of the separate set at+64 and removes a rowed empty_initialize
COMDAT. Keep the native constructor visible. The12 compiler-local cleanup
labels drift by11; eh_state_pins binds native unwind-map owners/states before
updates. Private control: build/miles-no-dtor-specialization-proof.json.

## Scoped result and limits

Normal4-source provider/consumer gate:228/228 functions,2 data rows,1 literal,
55 DIR32 refs, no unverified refs (`build/miles-ownership-minimal-final.log`, exit0).
All12 Miles cleanup pins are now unique native-state proofs (final EH check
exit0). The sole-writer fix applied/byte-verified all12 and returned its
pre-fix wrong-count exit1; the independent final check above is the verdict.

Strict RetailTruth: the Miles initialize_map203B changes f582d958812f/wrong to
8b3835f0e2c8/retail, matching both unchanged canonical providers. Default queue
ctor44B d6c67c173461 and set ctor54B cc0bacb6efc2/dtor5B230a5843c270 are retail
in their current emitters. All related same-name copies agree across the4
objects; related unplaced helpers are explicitly NOT claimed native matches.
Old opaque ctor/dtor undefined references disappear. Evidence and original
objects: build/miles-ownership-{before,truth.json,truth.py}.

add_match's supported scaffold --replace-rva path replaces tg_00078100;
--correct-identity is for real-source claims and is not applicable to this
scaffold. Its automatic hatch pruning removes the constructor's object_symbol
and an already-stale3C8F80 entry (that row already lacks object-symbol at HEAD;
no identity/source change there). No counter grows. Obsolete opaque set-dtor
body_guard debt remains: repair_queue pass-test refuses `no source spells`,
so no alternate writer or manual baseline deletion is used.

Historical queue preview1827B is not an actual linked-byte gain. Current live
link_check --compile-limit0 exceeded200s in dependency inspection; it was not
restarted, no child remained, and current linking remains UNKNOWN. The scoped
proof does not stand in for a new maintainer census or complete family closure.

Compiler: MSVC7.1 13.10.3077, original /O2 /MD /EHsc and
_STLP_USE_STATIC_LIB/_STLP_NO_EXCEPTIONS context; approved classes-private
WoW64 Wine prefix, WINEARCH=win64, BUILD_POOL=2. No baseline growth or new pin.
