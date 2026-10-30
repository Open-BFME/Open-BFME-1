# 0x008D3860 BfmeNode1236List::bfmeProcess1236

Facts from BFME 1 retail:

- Code ends with `ret 0xC` at +0x1D6; `lea ecx,[ecx]` pads to the five-entry
  case table at +0x1DC (targets +0xC8, +0x185, +0xA2, +0x194, +0x1B9), then
  INT3. Extent 496 B.
- The matched BfmeNode1236::bfmeActivate1236 (0x008D2810,
  game/GameEngine/Source/Common/BfmeNode1236Activate.cpp) calls this body as
  `?bfmeProcess1236@BfmeNode1236List@@QAEXPAX0H@Z` (symbols.csv pin), passing
  the child's walk record, the node and the frame number; the matched
  Rva008D2130.cpp step makes the same call.
- Pass one hands kind-8 commands to the Apt bytecode runner
  (Rva008CCED0BytecodeRunner::run at 0x008CCED0) and logs the literal
  "doFrameControls" through BfmeR1226::bfmeLine1226.

Naming: the old bank called the method `doFrameControls` (from that trace
literal) and a callee `apply`. The literal is a lead for EA's method name,
not proof, so the body keeps the pinned address-derived name its callers
use; the callee takes its ledger name `BfmeSubmitter1283::rva008BEF00`.
