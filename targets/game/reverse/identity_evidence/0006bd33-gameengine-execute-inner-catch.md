# 0x0006BD33: GameEngine::execute inner catch(...) {} block

2026-11-04, model=claude-opus-5-5. Link queue #7 (`<hard-coded image addresses>`).

## Retail evidence (BFME 1 target)

The 6-byte body `mov eax, 0x0046BCED; ret` was ledgered as the free function
`?Rva0006BD33Get@@YAPAXXZ` (`game/GameEngine/Source/Common/Bfme/Rva0006BD33Get.cpp`),
which spelled the value as a hard-coded image address. It is an empty MSVC 7.1
catch block returning its continuation.

GameEngine::execute's prologue at 0x0006BBE0 pushes handler 0x00FF2AF0, whose
FuncInfo 0x011E00E0 (magic 0x19930520, maxState 4) has two try blocks:

- try 0..0, catch state 3: `catch (INIException *)` (type 0x012A6FD4) handler
  0x0006BC3E and `catch (...)` handler 0x0006BCB9 (rows `uw_0006bc3e`,
  `uw_0006bcb9`);
- try 2..2, catch state 3: `catch (...)` handler **0x0006BD33**.

The second try block is the recorder clean-up `try` nested inside the outer
`catch (...)`; its handler starts right after `uw_0006bcb9` ends (0x0006BCB9 +
122) and its continuation 0x0006BCED lies inside `uw_0006bcb9`, after the
nested try, where `REPORT_CRASH("Uncaught Exception in GameEngine::update")`
resumes.

## Object evidence (BFME 1 build)

`game/GameEngine/Source/Common/GameEngine_execute.cpp` already spells that
nested `try { ... } catch (...) { }`. Its object emits the empty catch as
compiler label `$L1198` at execute+0x153, which is `$L1196` (the outer
catch-all, +0xD9) + 0x7A, matching retail 0x0006BCB9 + 0x7A = 0x0006BD33.

## Repair

The row is repointed to GameEngine_execute.cpp as `?dup_0006BD33@@YAXXZ`, a
`compiler-catch;gen-funclet` row bound by `object-symbol=`; the free-function
TU is deleted. No donor material used.
