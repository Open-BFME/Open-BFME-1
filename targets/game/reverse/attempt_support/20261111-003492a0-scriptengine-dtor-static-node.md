# 0x003492A0 ScriptEngine::~ScriptEngine (928 B) - EXACT via file-static node pointer

> `build/wf/003492a0/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x003492a0.cpp` (final.cpp).

Best candidate: build/wf/003492a0/final.cpp (defines ??1ScriptEngine@@UAE@XZ; also
defines ?Rva00339A80ParticleSystemSinkStart@@YAXXZ). Flags unchanged from the bank:
`/DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib` + stlport.

probe: ??1ScriptEngine@@UAE@XZ 0x003492A0 928/928 EXACT; ?Rva00339A80ParticleSystemSinkStart@@YAXXZ
0x00339A80 107/107 EXACT; emitted COMDAT ??1Rva0033C070TailDtor@@UAE@XZ vs 0x0033C070 11/11 EXACT.
ilt_oracle check '??1ScriptEngine@@UAE@XZ' 0x003492A0: CONFIRMED (exact).

## The lever (resolves the 7-byte "regalloc/object-home-register" wall)
The pointer at 0x012F0754 must have INTERNAL linkage (`static`). Donor lead: BFME 2
`Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_dtor.cpp` (2bac16a6) keeps its
debug-window holder pointer file-static and notes an extern pointer gives other registers.
Measured (bank class views otherwise unchanged):

| form | linkage | result |
|---|---|---|
| bank: local + if + delete local | extern | 7 diffs (EDI home) |
| same | static | 4 diffs (v9) |
| bare `delete g; g = 0;` | extern | 929 B / 577 (A1 EAX form) |
| bare `delete g; g = 0;` | defined non-static | 929 B / 577 (v5) |
| bare `delete g; g = 0;` | **static** | **EXACT** (v10, bank class) |
| BFME2 model: derived w/ implicit dtor over base `~B(){clear();}` | static | EXACT (v1) |
| same, local+if form | static / extern | 4 / 7 |
| existing ledger view `Rva0033C070TailDtor : Rva00020BA3TailBase` (virtual out-of-line base dtor, inline `virtual ~D(){}`), local + `object->D::~D(); operator delete(object);` | static | **EXACT** (v7, final) |
| same view, test/use the global directly | static | 931 B / 574 (v6) |

Mechanism (hypothesis): with a static, MSVC knows no call can modify the global, so
the bare-delete expansion no longer reloads it and the single temp gets the
out-of-line-call-style ECX home + early EDI copy (as in W3DMouse 0xB0129A).

## Landing notes (read-only checks; nothing landed)
(a) ilt_oracle: CONFIRMED for ??1ScriptEngine@@UAE@XZ at 0x003492A0 (row is ?d_003492a0@@YAXXZ, gen_asm; replace via --replace-rva).
(b) Helper COMDATs final.cpp emits: ??1Rva0033C070TailDtor@@UAE@XZ (row 0x0033C070, VptrTailJumpDestructors.cpp) - retail-identical 11/11;
    ??_7Rva0033C070TailDtor@@6B@ and ??_GRva0033C070TailDtor@@UAEPAXI@Z also emitted, same as the existing view in
    VptrTailJumpDestructors.cpp. CAUTION: retail vtable 0x010E75C0 slot 0 = ILT 0x44BDE -> 0x00339120
    (?rva00339120@Rva00339120Owner@@...), not a ??_G, so the virtual-dtor class view (existing and final.cpp) is
    probably wrong; the faithful model is alt_single_class.cpp / v1 (non-virtual inline dtor `{ clear(); }`,
    first virtual = slot00, clear = 0x0033AFF0 via ILT 0x20BA3, fields +4 int / +8 char = BfmeHostERU id/active).
    Both models are EXACT; final.cpp is chosen because it binds to names the ledger already records.
(c) Relocations in the delete block (objdump of final.cpp): +0x70/+0x97 `_g_rva00339a80Node` (static, TU-local;
    data row ?g_rva00339a80Node@@3PAVRva00339A80ParticleNode@@A 0x012F0754 is currently an EXTERNAL definition in
    game/GameEngine/Source/Common/Rva00339A80ParticleSystemSinkStart.cpp and must become this TU's static),
    +0x7C ??_7Rva0033C070TailDtor@@6B@ (dir32 0x010E75C0), +0x81 ??1Rva00020BA3TailBase@@UAE@XZ (symbols.csv pin
    0x00020BA3), +0x87 ??3@YAXPAX@Z, +0x8F ?TheScriptDebugWindowDLL@@3PAXA (data row 0x012F0758).
    Other globals: 0x012F076C TheScriptEngine (dir32 has several typed names; bank's ?TheScriptEngine@@3PAVScriptEngine@@A
    is not among them), holder 0x012F0770 = data row ?TheBfmeObject_00C6FE50@@3VGen_00C6FE50Target@@A
    (+8 = ?g_rva00339a80Sink@@3PAVRva00339A80ParticleSink@@A 0x012F0778), holder vft 0x010E7530 =
    ??_7BfmeDualVtableReleaseDtor@@6B@ (and ??_7ShellGameLoadScreen@@6B@), dtor ILT 0x2842F =
    ??1ShellGameLoadScreen@@MAE@XZ pin. ScriptEngine vftables 0x010E7A30/0x010E7A18 and Snapshot 0x01073744 are
    not specific dir32 rows for ScriptEngine. Member-dtor ILTs (0x35D5 0x3A44 0x5A56 0xCE50 0xD152 0x191AF 0x1CD7D
    0x2240D 0x4772B 0x1900B) are only ?j_ gen-thunk names: bank's opaque Rva003492A0Member* dtors need pins.
(d) TU: the static forces the dtor and 0x00339A80 (only other user of 0x012F0754; ZH particleEditorUpdate analogue)
    into ONE TU - game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp (holds TheScriptDebugWindowDLL's data row),
    retiring Rva00339A80ParticleSystemSinkStart.cpp's definition. final.cpp shows 0x00339A80 stays EXACT under
    the bank flags (its home uses /Oa only).
Still not landing-ready: local SubsystemInterface/Snapshot views (prior verdict: existing headers keep the bytes),
member-dtor/vtable/holder names above, and the data-row move to a static.
