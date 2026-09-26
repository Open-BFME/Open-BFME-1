# Native storage worker bank — 0065CA50

This is a partial reconstruction, not a game-source conversion. The old named
naked row remains intact. The bank defines `PSThreadClass::Thread_Function`
(public virtual, `?Thread_Function@PSThreadClass@@UAEXXZ`). Its identity is
supported by the same-receiver calls to independently native
`PSThreadClass::tryConnect` and the newly recovered `tryLogin` at 006549C0;
see `006549c0-storage-login.md`. The reference source is
`PersistentStorageThread.cpp`, but BFME's request behavior is substantially
extended and the old source must not be copied unchanged.

## Extent

The legacy row claims 3235 code bytes, ending immediately after the backward
loop jump at +C9E. The complete contiguous COFF contribution is **3292**:
3235 code bytes, the 6-byte catch handler at 0065D6F3, three alignment bytes,
then twelve four-byte switch destinations at 0065D6FC..0065D72B. The next
alignment begins at 0065D72C. The existing catch row separately owns those
six bytes, so a future complete landing must retire that overlapping claim
through the supported ledger tool. This bank changes neither extent claim.
Linear disassembly of the table produces probe's expected boundary warning;
it is data, not a truncated instruction.

## Recovered behavior and contracts

* A 0x210 PSRequest, native 0x1C4 PSPlayerStats, lock owner at thread+68,
  operation count +54, HTTP request map +5C, and queue local ID +68.
* The loop takes a one-millisecond MutexClass::LockClass, polls the queue,
  and stops only when the owner lock succeeds and no request remains.
* Requests 0/1/2/3 read stats, update stats, update locale, and read preorder
  CD-key data. Requests 5/6/7 manage GameSpy game creation/finalization/cancel;
  10 starts the additional HTTP request; 11 updates positive ladder ranks.
  Table entries 4/8/9 use the common continuation.
* The original six persisted desync/disconnect counters and requests 0/1/2/3
  are retained with BFME's map offsets, file path and callback signatures.
* The CD-key polling loop also uses the owner lock. HTTP requests advance
  their map iterator before `ghttpRequestThink`, permitting callback erasure.
* GameSpy's 2004 callback ABI adds a `time_t modified` argument: data callbacks
  have **nine** arguments and save callbacks **seven**. The bank includes
  this correction; Zero Hour's reference declarations are insufficient.
* `tools/callees.py 0065CA50 3235` identified 43 direct targets. The strict
  resolver reports zero unresolved direct callees after the separate login
  landing. This does not validate the nonmatching body's operand positions.

## Progress and exhausted levers

The first complete native body was 3308 bytes at 0.930 normalized shape.
Exposing the genuine tryConnect implementation recovered its five inlined
sites while retaining the one out-of-line call. Reversing the min arguments
recovered the loop's two compare/branch pairs. The independently proven
nonthrowing strdup helper contract removed extra string EH-state stores.

The bank is the clean structured version: **3308 vs 3292 bytes**. When only
real code is compared (excluding catch/table data), approximately **0.987**
of instructions share retail's normalized form. Full probe, which also
decodes the switch table as instructions, reports 0.967. Positional masked
score is much lower because the cleanup gap shifts the rest of the body:
2071 differing bytes, first branch displacement at +00AE. It is not exact.

The remaining structural differences are in request 6/7's shared
FreeGame/null-store/decrement tails and request 0's scheduling of the player
ID load around the operation-count increment. The rest has register/stack
allocation and alignment differences. The frame and first complete prefix
are exact. Explicit native cleanup labels and a shared inactive-game local
reach 3292 bytes and 0.992 code shape, but retain those scheduling differences;
the less shaped, structured version is banked deliberately.

Tested: normal and reversed connected branches; shared cleanup labels;
named inactive-game pointer; bool/int connected temporaries; authentic
inline free-game helper; result-length/pointer declaration order;
typed statsgame pointer and
request enum; early profile-ID local; visible exact 375-byte tryLogin body.
No volatile accesses, barriers or assembly were introduced. No symbols pins
were added, and no nonmatching source was placed under game/.

Model GPT-6, 2026-09-26; t=28 minutes including the dependency conversion and
short independent profile review. The next attempt should start here and
bring a new cleanup/aliasing hypothesis, not recopy the old naked body.
