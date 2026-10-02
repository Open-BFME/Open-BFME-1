# RVA 0x0006BD3C is an engine-loop continuation, not a function entry

The ledger's 611-byte generated row at RVA 0x0006BD3C is the resumed main
control-flow range of the 959-byte engine loop beginning at RVA 0x0006BBE0.
The existing bank/source calls the full function GameEngine::execute. This
proof establishes the interior boundary; it does not land or rename either
row, nor prove a separate callable method at 0x0006BD3C.

All binary addresses below were checked with pefile and capstone against
retail-1.03-unpacked lotrbfme.exe, base 0x00400000. GhidraMCP creating a function
at VA 0x0046BD3C reports 648 bytes, not the ledger's 611; creation/decompilation
of an arbitrary address is not proof of an independent entry.

## The alleged ILT is an internal branch

The only executable E9 targeting RVA 0x0006BD3C is at RVA 0x0006BC39.
Decoding from the actual full entry, RVA 0x0006BBE0, shows:

    0046BBE0 push ebp
    0046BBE1 mov ebp,esp
    0046BBE3 push -1
    0046BBE5 push 00FF2AF0h
    ... install FS exception frame ...
    0046BC05 mov ebx,ecx
    0046BC0A mov [ebp-1Ch],ebx
    0046BC20 mov al,[ebx+0Ch]
    ... virtual update call ...
    0046BC36 call [eax+14h]
    0046BC39 jmp 0046BD3Ch

This is a branch over inlined catch funclets, not a five-byte ILT entry.
There are no absolute pointers to VA 0x0046BC39 or VA 0x0046BD3C. The actual
entry RVA 0x0006BBE0 has a distinct ILT at RVA 0x000173E6, stored in tables
at VA 0x01075BF0 and 0x0111C9D0.

## Receiver, frame and backward control flow prove one enclosing body

At RVA 0x0006BD3C, execution immediately uses the enclosing EBP frame,
including [ebp-4] exception state. It later reads fields through EBX, the
receiver saved at VA 0x0046BC05. It establishes no prologue or receiver of
its own. VA 0x0046BEE4 jumps backward to VA 0x0046BC19, while the branch
from VA 0x0046BC25 reaches the common exit at VA 0x0046BF76. The final
block restores FS from [ebp-0Ch], pops the earlier saved registers and EBP,
and returns at RVA 0x0006BF9E. INT3 at RVA 0x0006BF9F closes the full body.

Thus the 611-byte span ends correctly but starts in the middle of one
function: 0x0006BF9F - 0x0006BD3C = 611; the actual outer extent is
0x0006BF9F - 0x0006BBE0 = 959. The two separately ledgered catch ranges,
0x0006BC3E/123 and 0x0006BCB9/122, already reside in GameEngine_execute.cpp
with the execute parent annotation. The executable branches, frame accesses
and common epilogue supply independent evidence for that relationship,
rather than relying on adjacency or the annotations alone.

The surrounding table's independently clean GameEngine::reset, update,
setFramesPerSecondLimit, getFramesPerSecondLimit and getQuitting methods
corroborate the engine owner. The resumed range performs pacing, watchdog
and subsystem work described by the existing full-loop bank. It must not
be converted as a standalone thiscall body or assigned a new method name.
Recover the outer body and validate its complete scope/EH contract before
retiring this interior scaffold; this proof does not change the ledger.
