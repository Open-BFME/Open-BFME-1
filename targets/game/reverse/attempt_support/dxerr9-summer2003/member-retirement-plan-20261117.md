# DXErr9: retiring the vendored member `obj\i386\dxerr9.obj` (plan, 2026-11-17)

Lane w48 (route and retirement), model claude-opus-5-5. This replaces nothing in
`physical-member-feasibility-20261113.md`; it records how the member is retired now that
only one section is still archive-owned.

## How a vendored member drops out (mechanism, BFME 1 tools)

`tools/build.py` `extract_lib_members()` and `tools/link_census.py` (which links "the object of
every matched ledger row") reach an archive member only through matched functions.csv rows
whose `source` is the `.lib` and whose notes carry `member=`. No tool lists dxerr9 statically
(`rg -i dxerr tools/` finds only a progress_site.py display label). So the member is retired
by the landing that repoints its LAST ledger owner to source with
`tools/add_match.py ... --replace-existing`; no separate retirement step, file deletion or
tool change exists or is needed. Precedent: 4254c28d7 (libpng `pngtrans.obj`, every member row
repointed in one commit). Partial conversion keeps the member extracted, so its NODUP and
ANY definitions collide with the source objects (LNK2005) until the last row moves.

## Section inventory (archive sha256 07f40f67..., 14 `.text` sections, one function each)

| sec | symbol | B | COMDAT | retail owner |
|---|---|---|---|---|
| 3 | ?StringCopyWorkerA@@YGJPADIPBD@Z | 59 | ANY | d3dx9.lib cimage.obj row 0x00A2A893 (not dxerr9's) |
| 5 | ?StringCopyWorkerW@@YGJPAGIPBG@Z | 66 | ANY | strsafe.cpp 0x00AD5401 |
| 7 | ?StringVPrintfWorkerA@@YGJPADIPBD0@Z | 74 | ANY | d3dx9.lib cimage.obj row 0x00A2A8CE (not dxerr9's) |
| 9 | ?StringVPrintfWorkerW@@YGJPAGIPBGPAD@Z | 75 | ANY | strsafe.cpp 0x00AD5443 (this wave) |
| 11 | _DXGetErrorString9A@4 | 70599 | NODUP | dxerrstringa.cpp 0x00AD548E |
| 3510 | _DXGetErrorString9W@4 | 70612 | NODUP | dxerrstringw.cpp 0x00AE6855 |
| 7010 | _DXGetErrorDescription9A@4 | 10933 | NODUP | dxerrdescriptiona.cpp 0x00AF7C29 |
| 7600 | _DXGetErrorDescription9W@4 | 10933 | NODUP | dxerrdescriptionw.cpp 0x00AFA6DE |
| 8190 | ?StringCchCopyA@@YGJPADIPBD@Z | 23 | ANY | strsafe.cpp 0x00AFD193 |
| 8192 | ?StringCchCopyW@@YGJPAGIPBG@Z | 23 | ANY | strsafe.cpp 0x00AFD1AA |
| 8194 | ?StringCchPrintfA@@YAJPADIPBDZZ | 39 | ANY | strsafe.cpp 0x00AFD1C1 |
| 8196 | ?StringCchPrintfW@@YAJPAGIPBGZZ | 39 | ANY | strsafe.cpp 0x00AFD1E8 |
| 8198 | _DXTraceW@20 | 377 | NODUP | dxtracew.cpp 0x00AFD20F (this wave) |
| 8209 | _DXTraceA@20 | 374 | NODUP | **archive** 0x00AFD388: the last owner |

Every section's bytes equal retail at its owner's RVA outside relocation operands
(`reloc_ledger.masked_equal`, re-run this round). Other sections: `.drectve`
(`/DEFAULTLIB:"uuid.lib"` twice), one `.debug$S` (object path
`D:\BUILDS\NT32_FRE\multimedia\directx\misc\dxerr9\daytona\obj\i386\dxerr9.obj`, compiler
13.00.9176/9178), 14 associative `.debug$F`, 8187 `.rdata` string-literal COMDATs (ANY), all
re-emitted by the source TUs that reference them. Undefined externals of the member:
`__vsnprintf`, `__vsnwprintf`, `__chkstk`, `__imp__{OutputDebugString,MessageBox}{A,W}`,
`__imp__DebugBreak@0`. Retail imports no `_vsnwprintf`; once the member is gone that
non-retail import leaves the census link (the source worker imports
`?vswprintf@@YAHPAGIPBGPAD@Z`, retail's IAT 0x01359228).

## The one-step retirement (when `_DXTraceA@20` lands outside the archive)

1. Claim 0x00AFD388. Source: `game/Libraries/Source/DirectX/dxtracea.cpp` if a compiler
   reproduces the biased frame, else (route (b) below) a MASM body under
   `game/masm_dumps/`; identity evidence beside `dxerr9-summer2003-dxtracew.md`.
2. `python3 tools/add_match.py _DXTraceA@20 0x00AFD388 374 <source> --replace-existing --model <you> --notes '...'`
   (same name and extent, so no tombstone; add_match moves the row's source).
3. Prove retirement: `rg -n 'dxerr9.lib' targets/game/reverse/functions.csv` prints nothing.
4. `./build.sh` the seven units (dxerrstring{a,w}, dxerrdescription{a,w}, strsafe, dxtracew,
   the DXTraceA source); `python3 tools/import_binding.py check` on dxtracew.cpp and
   strsafe.cpp (both PASS on 2026-11-17) and on a C++ dxtracea.cpp.
5. `python3 tools/link_check.py` on the seven TUs before and after (quote both): expected,
   the duplicate obstacles on all four lookups and the six strsafe names disappear; any
   remaining obstacle is a separate blocker (literal COMDAT selection, imports).
6. Update `inputs/vendor/dxerr9/PROVENANCE.txt` "Coverage": no row is sourced from the
   archive any more; keep the archive as read-only identity evidence (recover.py,
   test_recovery.py, test_strsafe.py, physical_member_feasibility.py and the identity
   evidence read it). Do not delete it.
7. One commit (it is the retirement), Claim-Lease for 0x00AFD388, then release.

Until step 2 lands, LINKED for the DirectX TUs stays 0; landing more source sections
(as this wave did for 0x00AD5443 and 0x00AFD20F) adds duplicates only inside TUs that already
fail, so it costs no linked bytes.

## What blocks the last owner, `_DXTraceA@20`

Owned by the w48 DXTRACE lane (claim 0x00AFD388); its handoff
`tracea-bias-heuristic-20261117.md` (8278879ad) is the full record: ~60 flag/pragma/scoping
variants and all 120 declaration orders stay 369 B, retail's bias is 0x80-8-4*args, and
13.10 biases only when a referenced local based below -0x80 moves into disp8 range, so the
128-byte line buffer at exactly -0x80 never triggers it (13.00.9178 apparently did).

This lane measured one complementary control independently (before reading that handoff):
`dxtracea-bias-control-line132.cpp.txt` is the banked body with ONLY the line buffer grown to
132 B. Under the same `/O1 /G6 /MT /DNDEBUG` the whole 116-instruction body then equals native
except the 4-byte frame shift (`mov eax,0x1240`, `[ebp-0x20]`, `push 0x84`, every buffer
displacement -4) and relocation operands, including `lea ebp,[esp-0x64]` and `add ebp,0x64`.
`/Oxs` and `/O1 /Oi` leave the 128-byte original unbiased. Native DXTraceW (wide line at
-0x100, out of reach of any bias <= 0x67) is unbiased in both compilers, which is why 13.10
reproduces it.

Routes left for the retirement (a decision, not taken here because 0x00AFD388 is claimed):
(a) a 13.00-family compiler (not in `inputs/toolchains/`); (b) AGENTS.md "Verdicts and near
misses" allows MASM for a proven codegen blocker of compiler machinery, and the two records
above are that proof. A `.lib` row repointed to `game/masm_dumps/*.asm` is not a Rule B
reversal in `tools/conversion_gate.py` (no clean-C++ claim exists at 0x00AFD388), and
`game/masm_dumps/` already holds rows "carrying a proven VC7.1 codegen wall". This lane's
recommendation: take (b) once the DXTrace lane releases the claim, as one commit with the
checklist above; it retires the member and removes the duplicate obstacle from the four
lookups (162,756 B), strsafe.cpp and dxtracew.cpp. The C++ body stays banked
(`attempts/0x00afd388.cpp`) for a future 13.00 toolchain.

## Route (b) prerequisite: DXTraceA's literals (measured on census e27899673e)

A MASM body references data by name (`game/masm_dumps/*.asm` use `EXTERN` + `dd <name>`;
none references a `??_C@` literal). DXTraceA's 8 literal operands and their providers once
the member is gone:

| site | retail VA | literal | other definers in the census |
|---|---|---|---|
| +0x019 | 0x0112F770 | "%ld" | stlport x4 time facets (COMDAT) |
| +0x04B | 0x011BA158 | "%s(%s): " | none (dxerr9.obj only) |
| +0x079 | 0x011BA148 | "%s (0x%0.8x)" | none |
| +0x096 | 0x011BA13C | " (hr=%s)" | none |
| +0x0B4 | 0x01080294 | "\n" | 51 C++ objects |
| +0x0C4 | 0x0107301C | "" | 904 objects; data row ?g_Rva0107301CEmptyString@@3QBDB |
| +0x134 | 0x011BA0E8 | "File: %s\nLine: ..." | none |
| +0x14B | 0x011BA0C4 | "Unexpected error encountered" | none |

So route (b) also needs the five dxerr9-only narrow literals defined at their retail VAs
(`tools/add_data_match.py`, one datum each, a data-only TU), while the shared ones keep
their `??_C@` COMDAT names (an extra name at a literal another TU already provides would be a
second datum; `tools/duplicate_global.py`). Measure with `link_check` before landing.

## Outcome (2026-11-17, w48 DXTRACE lane round 2)

DXTraceA landed as C++ (`game/Libraries/Source/DirectX/dxtracea.cpp`, EXACT 374/374, 22
relocations) through a frame lever under 13.10.3077 (`tracea-bias-model-20261117.md`), so
neither route (a) nor (b) was needed and the literals above stay COMDATs emitted by that unit.
With DXTraceW and StringVPrintfWorkerW already on master, that landing was the retirement: no
functions.csv row reads dxerr9.lib, and `link_check` on the seven DirectX units no longer
reports a duplicate (previews UNKNOWN on the stale census). Step 6 is still open:
`inputs/vendor/dxerr9/PROVENANCE.txt` "Coverage" still describes the vendored rows, and any
edit under `inputs/vendor/` sends the commit through the full gate (`header_dependents.py`:
"toolchain/vendored: full gate"), so refresh it in a commit that pays that gate anyway.

## Verification and the ready step 6 (2026-11-17, w48 route/retirement lane round 2)

Re-checked independently at `8147b9c45` (the retirement is `87bbdd2a2`), model claude-opus-5-5:

- `rg -n 'dxerr9.lib' targets/game/reverse/functions.csv` prints nothing; the twelve rows of
  the seven DirectX units are the only owners of the member's sections (the A workers stay
  d3dx9 `cimage.obj` rows 0x00A2A893 / 0x00A2A8CE).
- `./build.sh` of the seven units: Functions OK 12/12, 8197 literals + 3 empty-string refs,
  6 DIR32 refs, body guard OK; `tools/import_binding.py check` PASS on `dxtracea.cpp`.
- `link_check.py` on the seven units at `8147b9c45` (311 s): "Lib members: 178 extracted from 5
  archive(s)", no duplicate, all seven LINKED PREVIEW UNKNOWN; before, at `b8a568e37`: 179 from
  6 archives and 12 duplicates over the six existing units. The UNKNOWN is the census index's
  `unknown_definers` state (22,801 ledger objects changed since census `e27899673e` are not
  built in a worker tree), so neither `--compile-limit` nor `--refresh` (about 22,000 compiles)
  is a cheap answer: the next census gives the LINKED figure. In the census index the
  dropped member's names fall back to single definers (`?StringCopyWorkerA` /
  `?StringVPrintfWorkerA`: `cimage.obj` only; `"%s(%s): "`-style literals: the new units only),
  for which `link_census.judge_selected` returns "ok" or no verdict, never "wrong", so nothing in
  the index predicts a new blocker.

Step 6 is ready as `provenance-coverage-retired.patch` (beside this file; `git apply --check`
clean at `8147b9c45`). It was not committed here: this worktree holds ~190 built objects, so
the full gate it forces would recompile ~22,000 units under the host-wide build lock. Apply it
in the next commit that pays the full gate anyway: `git apply
targets/game/reverse/attempt_support/dxerr9-summer2003/provenance-coverage-retired.patch`.
