# Frame-only EH stubs 0x003C7D20 / 0x004C6A70 / 0x0072EAA0 (session 520)

All three retail bodies are an SEH registration and restore with no other
code: `push -1; push handler; mov eax,fs:[0]; push eax; mov fs:[0],esp;
mov ecx,[esp]; mov fs:[0],ecx; add esp,0xC; ret[ 4]` (0x4C6A70 adds
`mov al,1`). FuncInfo (magic 19930520) has no try blocks; every unwind entry
has a NULL action: 0x72EAA0 one state, 0x3C7D20 and 0x4C6A70 two (1 -> 0).
No frame slot is allocated, yet the push-first registration order is used.
0x0072EAA0's matched row is still inline asm in GridDispatch006D2130.cpp.

Trial drivers: build/a1s520/vq.py (0x72EAA0 symbol) and vpp.py (0x3C7D20),
`/DNDEBUG /MD /EHsc`, probe.py. A = `{char *s; A():s(0){} ~A(){if(s)release(s);}}`.

| source shape | result |
|---|---|
| one destructible local, or any constant-false / unreachable block of them, `__noop(A())`, inline helpers with constant args | frame removed (1-9 B) |
| empty or inline-empty destructors (`~E(){}`, `~D(){nop();}`) | no EH at all |
| two locals, or one local live across a call that folds late (`A a; if (a.s) release(0);`) | 37 B (0x72EAA0 target 35): push-first form plus `push ecx` slot, 10 diffs |
| three locals, or 64-byte objects | `sub esp,N` and the fs-first form |
| 0x3C7D20 as `prepare(P item)` with by-value `P {Item *p; ~P(){if(!this)release(p);}}` plus `A a;` or an empty-class local | **37/37 B, 5 diffs: only the registration order (fs-first)** |
| same plus a late-dead call or a second local | 39 B, push-first with a slot |
| flags /O1 /Os /Ox /G5 /G6 /G7 /Og /Ot | no change (O1/Os drop the frame) |

Observation (objdump of our object): every variant that keeps the frame also
keeps a real unwind funclet (`lea ecx,[ebp-x]; jmp ~A`), and that funclet is
what holds the slot. Retail's actions are NULL, so retail's destructible
objects must have become dead (their cleanup proven unreachable, as in the
0x0013BE40 dead-loop state) before frame layout while the EH frame decision
survived. The push-first order then seems to follow a slot that was planned
and later dropped (our measurements: push ecx -> push-first, sub esp ->
fs-first, no slot -> fs-first).

Open: a source shape whose destructible locals are dead only after EH-state
numbering but before frame layout, with no surviving code. Candidates not
yet tried: a loop over a container whose zero count is known only through a
member store made by an out-of-line base ctor (the 0x13BE40 mechanism, but
that leaves the ctor call), by-value parameter whose destructor is the only
state plus a dead nested block.
