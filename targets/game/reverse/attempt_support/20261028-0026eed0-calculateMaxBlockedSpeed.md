# 0x0026EED0 AIUpdateInterface::calculateMaxBlockedSpeed (289 B), bank 0.976

Identity: `ilt_oracle.py check '?calculateMaxBlockedSpeed@AIUpdateInterface@@IBEMPAVObject@@@Z' 0x0026EED0`
is CONFIRMED (protected const; the other access spellings are contradicted).
Zero Hour twin: GeneralsMD AIUpdate.cpp:1258. BFME replaces the physics
velocity length with `Object::bfmeGetNonnegativePreferredLocomotorHeight()`
(ILT 0x000047C8, pinned) and the formation id sits at Object+0x31C.

Bank: `targets/game/reverse/attempts/0x0026eed0.cpp` (session 466, a1),
289/289 B, 9 relocations, 7 non-reloc bytes. VC7.1 /O2, `/DNDEBUG /MD /EHsc`.

What moved it from the old 0.72 bank (295 B, frame 0x10):
- Frame 0x14: `Coord3D ourDir; ourDir.x = dir->x; ourDir.y = dir->y;` (a
  Coord3D whose z is never written). Coord2D or scalars give 0x10; a full
  `Coord3D ourDir = *dir` copies z and grows the code (302 B).
- Retail keeps otherDir.x/y on the x87 stack and CONSUMES them in the first
  dot (`fmul [dy]; fxch; fmul [dx]; faddp`). Locals in any scope (function,
  nested block, const, Coord2D, Real) stay live and are popped late (295 B).
  A `__forceinline` helper taking them BY VALUE, `projectTowards(Coord2D &v,
  const Object *to, const Object *from, Real oy, Real ox)` that writes v,
  normalizes and returns `v.x*ox + v.y*oy`, called with `odir->y, odir->x`,
  reproduces the loads at the call site and the consuming products. Plain
  `static inline` is NOT inlined (212 B call). Swapping the parameter order
  (ox, oy) gives 291 B.

Remaining 7 bytes:
1. +0x2C/+0x32/+0x3C: `getObject()` for the position delta is ECX in ours,
   EAX in retail. Inert: helper argument order (from, to), passing positions
   instead of objects (worse, 291 B), declaration order.
2. +0xB6..+0xC2: second dot `fld ourDir.y; fmul dy; fld ourDir.x; fmul dx`
   in retail; ours fld's vectorToOther and fmul's ourDir. Inert: all 8
   term/factor orders; vectorToOther declared before ourDir. Worse: a
   Coord2D/Coord3D dot member (295 B), a by-value dot helper (295 B),
   compound `+=` (295 B). Scalar ourDir copies keep the same choice (and lose
   the frame). Observation: ours always loads the operand written by FPU
   stores (vectorToOther), whatever its address.

Constants: the bank uses literals 0.0f/1.0f/0.55f; retail reads
0x01075350 (dir32 name ?BfmeBoundaryZero3D@@3MB), 0x01075334
(?g_bfmeDefaultBU@@3MA) and 0x010B933C (?g_real3f0ccccd@@3MB). The landing
gate will want the recorded names (see AIUpdateInterfacePrivateAttackPosition.cpp
for the extern pattern); swap them in before landing.

Later inert or worse trials (same session): a `__forceinline` second-dot
helper by reference or pointer, in either parameter order (295 B, like the
non-forced ones); a separate `ourDot` variable and dropping `speedFactor`
(both still 7 B).

Update (same session, bank now 0.986, 4 bytes): residue 1 is fixed by making
the helper a `__forceinline` const member of AIUpdateInterface that reads
`getObject()` itself, `projectTowards(Coord2D &v, const Object *to, Real oy,
Real ox)` (the from-object load then takes EAX as in retail). Only residue 2
(second-dot load choice, +0xB6..+0xC2) is left; the 8 term/factor orders are
still inert in the new context, and so are a Coord2D ourDir (11 B, frame
0x10) and a full Coord3D copy (296 B).

Session 467 (a1) re-probe: bank still 289/289, 4 bytes. Reading the slots:
ourDir lives at [esp+0x10]/[esp+0x14] (integer-copied at +0x18/+0x1E),
vectorToOther at [esp+8]/[esp+0xC]; retail fld's ourDir.y then fmul's
vectorToOther.y, ours the reverse. Further inert (4 B) or worse trials:
second dot through `const Coord3D *od = &ourDir` (4 B); through a
`const Coord2D *` to vectorToOther, alone or with od (295 B); `(double)`
promoted products (4 B); `-(-a - b)` (293 B); `dir->x/dir->y` read again
instead of ourDir (279 B); helper taking `Coord2D *` (4 B); vectorToOther
declared before ourDir (4 B); a block-scope copy of vectorToOther (311 B);
ourDir.y stored before ourDir.x (10 B, the copy order is load-bearing).

Landed s509 (claude-opus-5-5): volatile reads of both ourDir terms in the second dot product
(`*(const volatile Real *)&ourDir.x * vectorToOther.x + ...`) made it exact; the ZH copy in
AIUpdate.cpp became a 'defined in' note (its $L pin re-bound by eh_state_pins.py --fix).
