# 0x008B2F50 `PropertyLookup008B2F50::lookup` handoff (2026-11-14, claude-opus-5.5)

Target: RVA 0x008B2F50, 2396 B (2331 B code + NOP + 16-entry jump table at +0x91C),
ledger row `?d_008b2f50@@YAXXZ` (game/gen_asm/d_0084de40.asm).
Bank: `targets/game/reverse/attempts/0x008b2f50.cpp` (partial 0.9858, 34 non-reloc diffs).

## Session blocker: no compiler on this host

`tools/probe.py` stops at `wine not found. Install Wine to run MSVC 7.1 on this host.`
`which wine winepath` finds nothing, and `build/` was empty apart from this directory, so
no cached objects existed. Installing Wine needs a network fetch, which this lane forbids.
**This session ran no probes.** The baseline below (34 diffs) comes from the recorded
attempt log, not a fresh measurement. Everything here is static analysis, prepared sources
and a ready sweep driver. Syntax was checked with clang `--target=i686-pc-windows-msvc`
only. That is not codegen evidence.

## Prior verdicts read

- re_attempts.log has 24+ verdicts for this RVA. The latest are lines 54092-54633 (Wave14/15)
  and 51033 (donor port).
- identity_evidence: `008b2f50-native-property-dispatch.md`, `0x008b2f50_this_ebx_tie.md`,
  `008b2f50-bfme2-donor.md`, `008b3aa0-boundaries-and-008b3c40-callee.md`,
  `008b3c40_placeholder_names.md`.
- `targets/game/reverse/analysis/register_mirror_experiments.md`.
- Trials already spent: about 150 respellings, 90 flag sets, 42 rotations, 21 callee-EH
  trials, 13 EH-lever trials, shape_family_levers/shape_search, the self alias, merged
  object webs (byte-identical), extern TU-order dummies, /G3..G7 /Ob1 /Os /Oy and others,
  visible noinline constructor and allocators, and the complete BFME 2 donor port. All of
  them stay at 34 or regress.

## Retail register roles (static, from tools/dis_retail.py)

| web | retail | bank |
|---|---|---|
| `this` (all cases, `[reg+0x20]`) | EBX | EDI |
| case 2 object (bfmeGo911F result), case 3 index, case 13 `v` | EDI | EBX |
| pooled string / list item (cases 2, 3, 10, 12) | ESI | ESI |
| EH `-1` constant (case 2), case 3 array | EBP | EBP |
| case 11 integer from slot3C (after `this` dies) | EBX | EBX (unchanged; +0x5B8 is not a diff) |

Diff excerpt (retail vs bank; bytes from evidence `0x008b2f50_this_ebx_tie.md` and
`008b2f50-bfme2-donor.md`):

```
+0x022  8b d9  mov ebx,ecx      | 8b f9  mov edi,ecx
+0x0F7  8b f8  mov edi,eax      | 8b d8  mov ebx,eax     (case 2 object)
+0x1D2  8d 4f 08 lea ecx,[edi+8]| 8d 4b 08 lea ecx,[ebx+8]
+0x22D  8b c7  mov eax,edi      | 8b c3  mov eax,ebx     (case 2 return)
+0x7B1  8b f8  mov edi,eax  ... +0x7B5 8b c7 mov eax,edi | ebx forms (case 13 return)
```

All 34 bytes are this one EBX<->EDI exchange of every callee-saved web. Under a
colour-in-priority-order reading (an inference; this session took no traces), retail
assigns ESI-web > object/index (EDI) > `this` (EBX) > EBP-web. The bank ranks `this`
above object/index.

## The one recorded lead (not yet exploited)

Log lines 40405 (gpt-6-codex) and 42614 (gpt-6-luna) record that **a named local native
pointer in case 11** (`NativeSlots008B2F50 *native = m_value20; if (!native) ...;
native->slot3C()`) **moved `this` to EBX across the whole body**. Its only loss was retail's
`mov ecx,eax` at +0x5B1: the local is loaded straight into ECX. That shortens the code by 2
bytes, adds an alignment NOP and moves the table from +0x91C to +0x920. The 685 differing
bytes are therefore mostly a positional shift, not 685 wrong instructions. Nobody rechecked
that variant with `--shape` or reloc-masked alignment, and later sessions dismissed it as
"685".

Interpretation (hypothesis): in the bank, case 11 names `m_value20` twice. C2 merges the two
reads into one load, but the second `this` reference still counts toward the web's
priority. Removing one `this` reference drops `this` just below the object and index webs.
That fits the Open-BFME-2 `docs/recipes.md` C2 priority entries ("Equivalent control paths
can retain allocation costs after merging", "A stack-tested flag can still change another
value's register priority"). There, one reference or candidate moved a priority across the
ordering threshold.

What remains: find a spelling that removes one `this` reference without turning the
merged EAX temporary into a user local loaded directly into ECX. That might be in case 11
or in any of the 8 cases with the `mov eax,[this+0x20]; test eax,eax; je; mov ecx,eax`
pattern (5, 8, 9, 10, 11, 12, 13, 14).

## Ready sweep (run on a host with Wine)

`python3 build/wf/0x008b2f50/variants.py --probe` writes `v/<name>.cpp` plus
`v/<name>.probe.txt` and prints size/diffs per variant. Without `--probe` it only
generates the files; all 29 currently generate and parse.

- **B5..B14:** case-local named native pointer, used for both the test and the call. This
  generalises the recorded flip. Expect `this` in EBX and a lost `mov ecx,eax` in that
  case. Check with `--shape` whether the lost move is the only structural delta.
- **C5..C14:** test the member, then copy it into a local used only for the call.
- **D5..D14:** local used only for the test; the call goes through the member.
- **S10_12, S_all:** idiom from the matched sibling 0x008B3C40. A function-scope
  `native = m_value20` after `if (word)`; tests stay on the member and calls go through
  `native`. Retail 0x008B3C40 hoists this load before the switch, so this probably changes
  the prologue, but it is the same author/class family.
- **W1, W2:** duplicated-equivalent-path and post-increment priority levers for the case-2
  object and case-3 index.

If a variant flips `this` while keeping 2396 B, it is the candidate. If every flip costs
one `mov ecx,eax`, combine two half-levers next: put the local in a case whose CSE copy
survives, and test the member in another. Also consider the donor's read-only C2 trace
harness, which reports the actual refs/cost/priority of the `this` web against the object
web. It is in Open-BFME-2 `reverse/attempt_support/collision-7586f0-recovery-20261022/`
(`trace.py.txt`, `wdbg.py.txt`) and needs Wine and winedbg. Do not edit priorities to
land; use the traces only to choose the source change.

Rules respected: no volatile, no dummy variables, no pragmas, no inline asm. The W
variants duplicate side-effect-free tests, the donor-recipe pattern; drop them if
reviewers treat that as a dummy.

## Best candidate

`build/wf/0x008b2f50/landing.cpp`: the bank's control flow and descriptive names
unchanged, with recorded bindings. Expected 34 diffs (unverified). Compiler flags are on
line 1, `// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`, the same as the matched sibling
and home TU 0x008B3C40. The bank's descriptive types are kept; the array class keeps
`ArrayValue008B9C60` as a typedef because the ledger constructor name requires the class
`Rva008B9C90HeaderedDeleting`.

### Landing notes

- **ILT oracle:** `python3 tools/ilt_oracle.py check
  ?lookup@PropertyLookup008B2F50@@QAEPAURva00899560Value@@PAVNativeProperties008B3C40@@PAUString008B3C40@@@Z
  0x008B2F50` prints `UNTESTABLE p_false=None (not a thunk target (lib region, static, label, data))`.
- **Callees** (`tools/callees.py 0x008B2F50 2331`, all 15 bound): Rva008D5DC0,
  Rva00897640, Rva008B2B40, Rva008A90F0, Rva008B2AE0, append@Rva008B2EA0Node,
  add@Rva8D0D80Table, bfmeSetVKI, bfmeTruncVKK, ??0Rva008A9B00, ??0Rva008B2EF0@@QAE@II@Z,
  rva008B8E10@BfmeN1242, `??0Rva00899FC0@@QAE@H@Z` (symbols.csv pin at 0x00899FC0; ledger
  body bfmeGo1029A), `??0Rva008B9C90HeaderedDeleting@@QAE@XZ` (ledger 0x008B9C60).
  `??0Rva008D5750Object@@QAE@HPAX@Z` is **still unpinned**. The ledger body at 0x008D5750
  is `?bfmeGo911F@BfmeThing911F@@QAEPAV1@HPAX@Z`. A `new` expression with EH state 1 needs
  a constructor symbol, so landing needs one ABI pin, 0x008D5750 -> `??0Rva008D5750Object@@QAE@HPAX@Z`
  (evidence: complete 34-byte body, RET 8, returns its receiver; `008b2f50-bfme2-donor.md`),
  followed by `pin_consistency.py --check`.
- **Funclet sized deletes** (retail map E47D88): in-class inline forwarders bind them
  without new pins. `Rva008B2EF0` goes to `?Rva008B2B10@@YAXPAD0@Z` (size 0x28),
  `Rva008D5750Object` to `?Rva008B2B70@@YAXPAD0@Z` (0x24), the array to
  `??3Rva008A9120HeaderedDelete@@SAXPAXI@Z` (0x2C), `Rva00899FC0` to
  `??3Rva00897670HeaderedDelete` (0x24), and `Rva008A9B00` to the `??3Rva008A9B00@@SAXPAXI@Z`
  pin (0x00891A80, 0x10). Verify that the funclets `?d_00c58ae4`, `?d_00c58aaf` and the
  others still match; the forwarders should be byte-neutral (the same direct cdecl call),
  but this is unprobed.
- **Globals** (data rows or dir32 names): `g_rva01337810GcRoots` (data row; the bank
  used dir32 alias g_rva8CD130IdleHook), `g_rva01338478NodeHead` (data row, sibling
  accessor), `g_rva012D5298Empty` (data row, sibling macro), `g_bfmeFallbackDB` as
  `AptValue *` (data row; the bank's `Rva00899560Value *` spelling is unrecorded),
  `Rva008C5D70Alloc` (data row), `Rva01337A30ReleaseTable` (dir32), `Rva013387D0`
  (dir32), `g_rva008B2EA0Base` (dir32 0x01338608), and `g_rva008B2BD0_0..5` (dir32 for
  0x01338360..74, typed `Rva008B2BD0Item *` as in the matched
  `Rva008B2BD0ReleaseGlobals.cpp`, reached through `nativeCacheN` reference macros like
  the BFME 2 donor's `xmlCacheN`).
- **Callback addresses:** the matched functions `Rva008B2DB0Get`, `Rva008B2DC0Get`,
  `Rva008B2DD0Get`, `Rva008B2DE0Get`, `aptQueryBool` and `rva008B2EA0Walk` replace the
  bank's `Va00CB2DB0[]` char arrays.
- **Vtables:** `??_7Rva00899560Value@@6B@` (dir32 0x01135D68) and `??_7Rva008A1110Value@@6B@`
  (dir32 0x01136400), installed by the inline constructors in pooledInteger.
- **COMDATs it emits** (clang MSVC-ABI object as a proxy): `??_7Rva00899560Value@@6B@`,
  `??_7Rva008A1110Value@@6B@`, `??_GRva00899560Value@@UAEPAXI@Z`, `??_GRva008A1110Value@@UAEPAXI@Z`.
  The deleting destructors reference unpinned `??1Rva00899560Value@@UAE@XZ` and `??3@YAXPAX@Z`.
  The sibling has the same pattern and its unit is `linked=no` (11 unresolved).
- **Home TU:** the ledger row names the gen_asm dump. The natural home is beside the
  matched caller, `game/Libraries/Source/EA/Apt/NativeProperties008B3C40.cpp`. Its private
  views of `Rva00899FC0` (non-virtual `vtable` field, out-of-line `operator new`) and
  `Rva008A9B00` conflict with this body's views, so either reconcile the classes in that
  unit or use a new sibling unit, `game/Libraries/Source/EA/Apt/PropertyLookup008B2F50.cpp`.

## Donor review (read only)

- Open-BFME-2 at f6c3838e7b58025531e09913bc42b810f1a01216.
- `Code/Libraries/Source/Apt/AptObject/Rva006F1360XmlLookup.cpp` (game.dat 0x006F1600,
  1956 B). This is the near twin `AptXmlNode::objectMemberLookup`; a previous session
  ported it completely at cc9f29f8 with the same 34. The receiver there is a
  checked-cast call result, which BFME 1 does not have.
- From the same file: the cache-slot reference-macro idiom over a shutdown provider's
  typed globals. It was adopted here for the recorded names.
- Open-BFME-2 `docs/recipes.md` lines 492-506 and 709-745 (C2 priority levers).
- Donor ledger row `??0Rva006F1360@@QAE@HPAX@Z` (0x006F1310).
- Zero Hour GeneralsMD has no Apt sources (Apt is a BFME library), so there was no ZH donor.

## Files

- `build/wf/0x008b2f50/landing.cpp`: best landing-ready candidate (unverified).
- `build/wf/0x008b2f50/base.cpp`: verbatim copy of the bank.
- `build/wf/0x008b2f50/variants.py` and `v/*.cpp`: the sweep.
- `build/wf/0x008b2f50/retail.dis`: retail disassembly, 2331 B.
- `build/wf/0x008b2f50/landing.syms.txt`: defined and referenced symbols (clang proxy).

## Measured 2026-11-14 (Wine 11, MSVC 7.1, `/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`)

`landing.cpp` (ledger-bound names) reproduces at 34 diffs, first at +0x23. These are the global EBX/EDI exchange.

I probed the 29 `variants.py` sources:

| Family | Diffs |
|---|---|
| D5..D14 | 34, ties the bank |
| B and C families | 292-1132 |

No variant moves `this` into EBX. The lead in this handoff is therefore exhausted at this granularity.

[exited with code 0]
D10.cpp: diffs    34 non-reloc byte(s); first at +35
D11.cpp: diffs    34 non-reloc byte(s); first at +35
D12.cpp: diffs    34 non-reloc byte(s); first at +35
D13.cpp: diffs    34 non-reloc byte(s); first at +35
D14.cpp: diffs    34 non-reloc byte(s); first at +35
D5.cpp: diffs    34 non-reloc byte(s); first at +35
D8.cpp: diffs    34 non-reloc byte(s); first at +35
D9.cpp: diffs    34 non-reloc byte(s); first at +35
W1.cpp: diffs    34 non-reloc byte(s); first at +35
W2.cpp: diffs    34 non-reloc byte(s); first at +35
base.cpp: diffs    34 non-reloc byte(s); first at +35
B14.cpp: diffs    292 non-reloc byte(s); first at +35
C14.cpp: diffs    292 non-reloc byte(s); first at +35
B13.cpp: diffs    362 non-reloc byte(s); first at +35
C13.cpp: diffs    362 non-reloc byte(s); first at +35
B12.cpp: diffs    404 non-reloc byte(s); first at +35
C12.cpp: diffs    404 non-reloc byte(s); first at +35
B11.cpp: diffs    685 non-reloc byte(s); first at +38
C11.cpp: diffs    685 non-reloc byte(s); first at +38
B10.cpp: diffs    727 non-reloc byte(s); first at +35
C10.cpp: diffs    727 non-reloc byte(s); first at +35
B9.cpp: diffs    870 non-reloc byte(s); first at +35
C9.cpp: diffs    870 non-reloc byte(s); first at +35
B8.cpp: diffs    916 non-reloc byte(s); first at +35
C8.cpp: diffs    916 non-reloc byte(s); first at +35
B5.cpp: diffs    1132 non-reloc byte(s); first at +35
C5.cpp: diffs    1132 non-reloc byte(s); first at +35
S10_12.cpp: diffs    1533 non-reloc byte(s); first at +35
S_all.cpp: diffs    1569 non-reloc byte(s); first at +2
