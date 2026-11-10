# 0x00357FC0 Parameter::ReadParameter: rotation-phase localisation (2026-11-10)

> `build/wf/00357fc0/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x00357fc0.cpp`.

Target `?ReadParameter@Parameter@@SAPAV1@AAVDataChunkInput@@@Z`, 748 B. Bank
`targets/game/reverse/attempts/0x00357fc0.cpp` still reproduces as logged:
748/748 B, 54 relocs, 6 non-reloc bytes. Compiler: VC7.1 via
`tools/probe.py`, `/DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib`
(same as the matched same-TU sibling ScriptActionParseAction.cpp, which uses
`/DNDEBUG /MD /EHsc`). Best candidate: `build/wf/00357fc0/best.cpp`. It is the
bank with `// cl:` first, canonical `Lib/Coord3D.h` and `BitFlags<86>` (the
ledger instantiation for 0x001C09C0). It still has the same 6 bytes.

## Residue

```
+026c retail lea ecx,[esp+0x18]; push ecx   ours lea eax / push eax   (throw ERROR_BUG temp)
+02c5 retail mov edx,[esi+8]; mov eax,[edx*4+tbl]; push eax
      ours   mov ecx,[esi+8]; mov edx,[ecx*4+tbl]; push edx           (empty-string KIND_OF arm)
```

## New measurements

The measurements below use the round-robin model in
`targets/game/reverse/analysis/allocation_residue.md`.

1. **The phase is set after +0x0C5, in program order, not layout order.**
   - Adding one visible temp (`pParm->m_coord.x = pParm->m_coord.y;`) at any
     point between the readAsciiString temp `lea edx` (+0x0C5) and the throw
     turns both residues into retail's registers: throw ECX, else EDX/EAX. The
     tested points were after the read, before UPGRADE, after OBJECT_STATUS,
     at the loop top, after the CRUSHER test, before the CASH format, after the
     MISSILE format and immediately before the throw.
   - The inserted temp always takes EAX. So in our build the pointer sits at
     EAX across that whole stretch, with zero turns (mod 3) there.
   - The CASH block is laid out after the throw, but inserting there still
     shifts the throw. Allocation therefore follows program order.
   - Swapping the isEmpty arms (else first) gives else EAX/ECX and throw EDX.
     This confirms program order again.
   - Retail therefore has exactly one more scratch turn (mod 3) than our
     build. It falls in program order between +0x0C5 and the throw and has no
     visible instruction, or it is a visible EAX def that our build allocates
     outside the rotation.
2. **The coord copy takes 4 turns** (ECX, EDX, EAX lea, ECX). Removing the
   coord block (`d_coord`), or copying `x` through extra Real locals
   (`f4_locals`), also flips both residues, but changes many other bytes. The
   coord block and the `lea edx` at +0x0C5 already match retail, so the
   missing turn cannot be before +0x0C5.
3. Deleting whole blocks (UPGRADE, OBJECT_STATUS, CASH, MISSILE, else) never
   moves the throw. Each block contributes 0 turns mod 3 in our build.

## Ruled out this session

Every result below stayed at throw EAX. Bodies that kept 748 B stayed at 6
diffs; others changed bytes elsewhere.

- (a) Control flow:
  - `if (found) return pParm; throw` (k3).
  - Swapped isEmpty arms (s1, 729 B).
  - Inverted COORD3D test (s3).
  - `found` declared at KIND_OF top (s4).
- (b) Lifetime and temporaries:
  - `AsciiString &str` alias in UPGRADE, OBJECT_STATUS and KIND_OF (n2-n4).
  - `AsciiString &` for the read (n1, changes bytes).
  - Named AsciiString local or const ref for readAsciiString (r4/q1). These
    flip the throw only by adding a visible `lea eax`: 134 diffs.
  - `AsciiString(...)` copy (q3).
  - `.set(file.readAsciiString())` (q4: 10 diffs, push/lea order).
  - `Int bit`, `const char *tok` and `rot()` identity copies on the str()
    argument, the getSingleBitFromName result, `kindofNames[i]` and `i` (g1,
    g2, w1-w5, l1). The pushed-load copy lever does not move the pointer here.
- (c) Types and spelling:
  - Four isEmpty spellings (ie1-3 change bytes; ie4 is inert).
  - UPGRADE through `operator==` (bool, int, `!compare`) (u1-u4).
  - Bool locals for the UPGRADE and first-match conditions (m1-m3).
  - Locals in the else arm (m6, m7).
  - `set(const char*)` strlen spellings (s1-s3 set variants).
  - Six str()/peek() spellings in a private header copy (y_peek*, y_str*).
- (d) Callee visibility:
  - setCoord3D defined out of line, before or after the function (c1, c2).
  - Coord copy via fields, memcpy, pointer, temp, `set()` members (c3-c8).
  - setCoord3D by reference or value, friend forwarder, direct assignment
    (f1-f3, f7).
  - In-TU BitFlags<86>/<181> bodies with `getBitNames()` (b2).
  - `throw()` on DataChunkInput, getSingleBitFromName, compare,
    compareNoCase, set, releaseBuffer, `operator=` and format (z*, y_*;
    readInt and `set(StringBase)` change EH and bytes).
- (e) Flags: nothing to change. The same-TU sibling uses the same base line. A
  dummy function before or after it in the TU does not move the pointer (tu*),
  so the pointer is reset per function.
- (f) Evaluation order: setter forms for readInt/readReal (r1, r3).
- (g) EH and throw: throw through an inline or `__forceinline` function with a
  by-value or reference parameter (k1, k2, k4, k5); `const ErrorCode&`,
  static const, Int cast and ternary throw values (t1-t7).
- Format arguments as explicit `AsciiString("...")` (h1-h3).

## Next lever to try

Find a construct between +0x0C5 and the throw that MSVC allocates as one
codegen temp and then folds away. Retail must contain one. Earlier logs list
these candidates, and all are inert in our build:

- a temp copy of a call result (readAsciiString, getSingleBitFromName or
  compareNoCase) that lands in EAX, so its `mov eax,eax` disappears;
- a read-modify-write fold;
- the str() ternary as a rotation temp.

No natural spelling found makes one survive copy propagation. The `/FAsc`
helper (`build/wf/00357fc0/cod.py`) shows our listing. All trial results are
in `build/wf/00357fc0/trials.log`.
