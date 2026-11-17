# DXTraceA: the 0x64 EBP bias is a 13.00-only frame decision (2026-11-17)

Lane w48 DXTRACE round 1, model claude-opus-5-5, about 40 minutes, base
`30f455d61`, census `e27899673e`. **Partial bank, zero source bytes landed.**
Extends `tracea-blocked.md` (2026-11-12) and the 2026-11-13 Opus re-probe row;
it does not replace them. Compiler: MSVC 13.10.3077, private outputs under
`build/w48/` only (no shared `build/match/` object was written).

## Facts measured in BFME 1

1. Archive member `obj\i386\dxerr9.obj` has `@comp.id` 0x001d23da = Utc13_CPP
   build 9178 (13.00.9178), the same stamp as 205 d3dx9 members. The d3dx9 zlib
   members are 0x5f0813 (13.10.2067, C); their `_huft_build@40` is biased with
   eight disp8 references gained.
2. Retail's bias is 0x80-8-4*args (0x64 for 5 arguments): the largest bias that
   keeps every incoming argument in disp8 range. Retail `.text` holds exactly 92
   `push ebp; lea ebp,[esp-disp8]` frames, all in 0x009F6ADB-0x00AFD388 (13.00
   d3dx9/dxerr9 members, zlib `_huft_build@40` and the matched 13.10 ATL
   constructor at 0x009F6ADB); all 92 follow that formula.
3. Retail `_DXTraceW@20` (0x00AFD20F) is **not** biased: its 256-byte
   `strBufferLine` sits at -0x100. DXTraceA's 128-byte one sits at exactly -0x80.
4. Control: `tracew-candidate.cpp.txt` (same structure as the banked A body, wide
   buffers, narrow `strFile`/`strBufferFile` copied by `StringCopyWorkerA`, popup
   format `%S`) is **EXACT 377/377, 23 relocations** under `/O1 /G6 /MT /DNDEBUG`
   in `tools/probe.py` (private). Not landed here: 0x00AFD20F is claimed by the
   sibling w48 retirement lane. The source family, flags, layout and register
   allocation are therefore right; only the bias decision differs for A.
5. The banked A body (`attempts/0x00afd388.cpp`) is retail minus the bias:
   `probe.py --shape` leaves exactly three structural differences (`mov ebp,esp`
   inserted, `lea ebp,[esp-0x64]` and `add ebp,0x64` deleted). The 2026-11-12
   normalisation already showed that rebiasing reproduces all 374 bytes and 22
   relocations. The measured stash score is low only because every EBP
   displacement shifts by 0x64.

## Compiler-context hypotheses ruled out (all 369 B, unbiased, unless noted)

| Variant (base `-O2 -GR- -EHsc-` then the `// cl:` line) | Result |
|---|---|
| `/O1 /G6 /MT /DNDEBUG`, also `/G5`, `/G7`, `/GB`, `/ML`, `/MD`, `/Gz`, `/Gr`, `/Zi`, `/Z7`, `/Gs0`, `/Ob0`, `/Ob2`, `/Oi-`, `/Oa`, `/Ow`, `/Op`, `/GA`, `/Ge`, `/J`, `/Zp1`, `/Gm`, `/Gi`, `/GX`, `/EHsc`, `/GR`, `/QIfist` | no bias |
| `/Os`, `/Ox /Os`, `/O1 /Oy-`, `/Ox /Os /Oy-`, expanded `/Os /Og /Oy /Ob1 [/Gs /GF /Gy]` | no bias |
| `/O2`, `/Ox` | 418 B, ESP frame |
| `/O2 /Oy-`, `/Ox /Oy-`, `/Ot /Oy-`, `/Og /Oy-` | 379 B, no bias |
| `/Od` 411 B; `/Gs8192` 365 B (no `__chkstk`); `/GF- /Gy-` 368 B | no bias |
| `/GZ`, `/RTCs` with `/O1` | refused by cl |
| all 120 declaration orders of the five buffers at function scope | identical 369 B |
| inline `StringCchCopyA` wrapper plus `int nResult`; unused `int`/`char[4,40,100,128,260]` first/middle/last; the three `strBuffer` uses split into disjoint scoped buffers (packed to the native slot) | no bias |

The 2026-11-13 row already covered `/O1 /GS` (394 B with cookie) and
`#pragma optimize("s", on)`.

## 13.10.3077 bias decision (micro-benchmarks, `/O1 /G6`)

`tracea-bias-micro.cpp.txt` reproduces the decisive cases:

- When 13.10 biases a `__chkstk` frame it emits retail's exact prologue and
  epilogue (`push ebp; mov eax,N; lea ebp,[esp-0x64]; call __chkstk` ...
  `add ebp,0x64; leave`), so the instruction shape itself is reachable.
- The decision counts references to locals whose base moves into disp8 range.
  A 128-byte array at exactly -0x80 counts as already reachable: `b_128` is not
  biased, `b_129`/`b_132` (base -0x84) are biased 0x64 with the same references.
- DXTraceA's own geometry (buffers 128/260/256/1024/3000, all arguments
  referenced) is never biased, at any reference count of the second buffer.
- Measured but not needed here: roughly three or more gained references are
  required, three only when at least two distinct arguments are referenced; the
  biased side tolerates bases up to 8 bytes past -0x80; never-written arrays
  overlapped by packing also trigger bias. None applies to DXTraceA, whose five
  buffers are all address-taken and live together.

## Inference (not proof)

13.00.9178 apparently counted displacement -0x80 as out of disp8 range in this
heuristic. Under that reading DXTraceA gains its three `strBufferLine`
references, and four other low-gain biased 13.00 frames
(`_D3DXLoadSurfaceFromMemory@40`, `_D3DXWeldVertices@28`,
`?SetTypedFromPtrs@CConstantTable@D3DXShader@@...`,
`?AddPhaseLinkage@CPSLegacyProgram@D3DXShader@@...`) also gain three or more.
`_D3DXComputeNormals@8` is an unexplained unbiased counter-example. Either way,
no clean-C++ spelling of DXTraceA's native references and layout makes 13.10.3077
bias the frame: blocker `toolchain/compiler-version`.

## Resume

- Do not repeat flag, pragma, declaration-order or scoping trials: they cannot
  move a decision that depends only on the final layout and references.
- The member stays all-or-nothing. Its remaining non-source sections are
  DXTraceA (this), DXTraceW (exact candidate above, sibling claim) and
  `?StringVPrintfWorkerW@@YGJPAGIPBGPAD@Z` (import-route prerequisite).
- If the project wants retirement anyway, AGENTS.md "Verdicts and near misses"
  allows MASM only for a proven codegen blocker such as compiler machinery. This
  note is that evidence; the decision belongs to the retirement lane, not here.
