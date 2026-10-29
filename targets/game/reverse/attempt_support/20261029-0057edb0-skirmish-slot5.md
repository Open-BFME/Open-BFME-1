# 0x0057EDB0 BfmeAptScreenSkirmish slot 5 mode dispatch (bank 0.93)

Identity (BFME 1 target evidence): slot 5 of vtable 0x0110B030, installed by
the matched BfmeAptScreenSkirmish ctor 0x0057DA50 / dtor 0x00579480; the
body tail-calls its own slot (+0x14). Extent 0x0057EDB0..0x0057EFDC = 514 B
code + 2 B pad + 10-entry jump table at +0x204 (556 B; the ledger row is 514).
Name kept address-derived: `?rva0057EDB0@BfmeAptScreenSkirmish@@UAEHXZ`
(returns int: `mov eax,1`).

Prerequisite landed in the same session: `_bfme_refresh` (0x005792A0)
returns bool (identity_evidence/005792a0-bfme-refresh-bool-return.md).

Bank: targets/game/reverse/attempts/0x0057edb0.cpp, 556/556 B, 39 non-reloc
diffs (score 0.93), flags `/O2 /DNDEBUG /MD` (sibling `/Ob0` is worse: 45).

Found levers:
- Every case except 8 needs its own `flushPendingUpdates(); return 1;` copy,
  but case 10 must use `break` in both arms: explicit returns there CSE
  `this+0x25C` into EDI (push edi, 330 diffs); with breaks VC7.1 tail-
  duplicates the flush late and retail's recomputed `lea` returns.
- Case 1 condition written `if (!prefs()) { persona...; flush; return 1; }`
  then OpenDefault (polarity).
- State object view must end at +0x26D (pad to 0x3AC from there).

Residue (39 B): scratch registers at the four action-dispatch calls
(ILT 0x00015235): retail movie register eax/ecx/ecx/edx and receiver load
order; ours ecx/edx/eax/ecx; tail-call vptr register eax/edx swapped.
Ruled out: void vs pointer return of the dispatcher, void* movie, volatile
receiver/member, local copies of the receiver/movie/persona window/mode
(128-trial shape_search over 7 toggles), `/Ob0` `/Ob1` `/Ox`, explicit empty
cases/default placement, base-class receiver for MpGameSetup.
Next: try the dispatcher's real arity/types from the matched sibling
callers' variants, or a different slot-44 / GadgetTextEntrySetText spelling
upstream of the first rotated temp (+0x85).
