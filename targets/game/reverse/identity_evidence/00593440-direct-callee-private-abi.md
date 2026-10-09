# 0x00593440: direct declarations reproduce the private helper ABI

This is a partial bank tested at revision `3308e6e98b37d847e81639c1c375ba4c1a9b1ab4` with model `gpt-6.1-sol`. No source recovery or ledger promotion is claimed. The complete parent and complete companion remain together in `targets/game/reverse/attempts/0x00593440.cpp`. Trial sources and raw probe outputs are retained under `build/00593440-retry/`.

## Retry hypothesis

The saved bank's member-pointer relay calls conceal the direct callee declarations from MSVC. The current ledger has real source for the level lookup, next-level return, rank getter, experience getter and mode predicate. Replacing the companion's relays with independently decoded direct declarations should reproduce its private register inputs. An unchanged ABI or a result no closer than the original bank would refute this hypothesis. Trial 07 reproduces the private inputs. Trials 10 and 11 reproduce every companion instruction outside relocations. No additional identity claim follows from that equality.

## Complete boundaries and calling convention

The parent occupies `0x00593440..0x00593622`, with its only plain RET at `0x00593621` and INT3 padding after it. All branches stay inside that extent. The fully decoded landed caller at `0x00594740` has three calls through ILT `0x00013985`, which jumps to this parent. It passes Object after hidden result storage, cleans eight bytes, consumes all three result words and uses the returned EAX address. The parent initializes mode 0, rank 0 and progress 0.0. The caller's independent fallback initializes mode 2. These observations prove the existing address-derived 12-byte record query, not an EA function name.

The companion occupies `0x0058B610..0x0058B7AF`, with returns at `0x0058B648`, `0x0058B7A5` and `0x0058B7AE`. No branch or tail jump leaves its extent. Both fully decoded callers (`0x00593440` and `0x00595E60`) pass Object in ESI, rank storage in EDI and float storage in EBX, without stack arguments. The first caller tests AL. The companion's final success writes EAX=1, final failure writes EAX=0, and initial failure preserves the validity predicate's false result. A Boolean declaration with a combined Boolean return reproduces all paths; widening the return type is unnecessary.

The target's two unwind states reset bits 0 and 1 of its static-initialization guard. Complete cleanup actions at `0x00C378F0` and `0x00C378FE` contain no object or element destructor. This is not an owning constructor. The bank includes the canonical Object header and changes no shared header.

## Value construction and callee evidence

The complete `0x0037F190` body writes a borrowed list pointer at result+0 and a matching node pointer at result+4. Failure writes only result+0=0. It reads the level name at ExperienceTracker+8 and traverses the list's node links. The complete `0x0037F220` body advances the second pointer, compares it with the sentinel obtained through the first pointer, applies node flags +0xD9 and +0xDA, writes both fields and returns through hidden storage with RET12. The complete rank and experience getters at `0x0037D810` and `0x0037D840` consume both stack words with RET8, follow `0x00048C61 -> 0x00097880`, and read rank and signed experience fields. Every inline argument copy reads and writes exactly those two pointers. Allocation size is not the type evidence. Rva0058B610Pair remains an address-derived borrowed view; no new STL identity or payload claim is introduced.

The complete `0x00381200` predicate takes Object, returns a Boolean in AL and ends in RET4. The complete `0x001B2030` stub returns false and consumes four stack bytes. Its actual caller passes an address of integer storage and conditionally compares that storage as signed rank. Current experience is read as float at ExperienceTracker+0x0C. The complete ratio, clamp and rank-limit paths remain in every trial.

The parent routes to nameToKey, Object::findModule, the alternate-template query and `0x000022BB -> 0x00087A80`. The override walkers at `0x00087A80` and `0x00097880` are distinct complete bodies. Object::findModule separately calls vtable slot +0x10 on each behavior receiver and compares its returned key. The parent makes no indirect call. Template+0x487 is m_isTrainable, independently witnessed by the IsTrainable parser row and name_oracle; it does not establish a hero identity.

## Measured and rejected shapes

The following table is generated from raw probe output. Zero companion differences means relocation-masked equality, not a strict gate receipt. `build/00593440-retry/best-byte-evidence.json` retains every differing offset, source and target hashes, emitted bytes, relocation names and compiler object path.

| Trial source in the task folder | Parent bytes | Parent differences | First offset (decimal) | Companion bytes | Companion differences |
|---|---:|---:|---:|---:|---:|
| 00-saved.cpp | 487 | 289 | 109 | 434 | 301 |
| 01-nested-iterator.cpp | 487 | 289 | 109 | 434 | 303 |
| 02-explicit-result-copy.cpp | 487 | 289 | 109 | 434 | 301 |
| 03-typed-module-fields.cpp | 487 | 289 | 109 | 434 | 301 |
| 04-native-pair.cpp | 487 | 289 | 109 | 442 | 326 |
| 05-reference-outputs.cpp | 487 | 289 | 109 | 434 | 301 |
| 06-helper-after-caller.cpp | 487 | 289 | 109 | 434 | 301 |
| 07-direct-typed-callees.cpp | 477 | 286 | 109 | 412 | 14 |
| 08-visible-next-level.cpp | 487 | 289 | 109 | 437 | 317 |
| 09-return-valid.cpp | 477 | 286 | 109 | 412 | 14 |
| 10-ordered-progress.cpp | 477 | 286 | 109 | 415 | 0 |
| 11-negated-failure.cpp | 477 | 286 | 109 | 415 | 0 |
| 12-explicit-success.cpp | 477 | 286 | 109 | 412 | 12 |
| 13-record-copy.cpp | 475 | 284 | 109 | 415 | 0 |
| 14-timer-end-first.cpp | 477 | 286 | 109 | 415 | 0 |
| 17-ordered-timer-reads.cpp | 480 | 224 | 122 | 415 | 0 |
| 20-end-before-start-compare.cpp | 480 | 224 | 122 | 415 | 0 |
| 22-scalar-record-components.cpp | 484 | 340 | 23 | 415 | 0 |
| 23-inline-timer-record.cpp | 538 | 299 | 23 | 415 | 0 |
| 24-status-enum.cpp | 477 | 286 | 109 | 415 | 0 |
| 25-mode-after-ratio.cpp | 484 | 226 | 122 | 415 | 0 |
| 26-mode-after-clamp.cpp | 492 | 236 | 122 | 415 | 0 |

The eight valid mechanical EH combinations emit the unchanged parent shape. Their sources and manifest are in `build/shape_search/f45f2ac748bb45519070d8fa22311a29/`; per-trial raw probes are in the task folder. Initial encoding failures are preserved separately and are not shape results. The throw generator's invalid annotation on a call expression was excluded before the valid search.

Nested iterator typing, native pair typing, explicit return copy, reference outputs, helper definition order and typed module accessors do not recover the parent. The complete next-level donor is byte-equal at its own extent but worsens the companion; its actual source was inspected. The preferred parent preserves the observed opposite timer-read order in the two update branches. Reversing the comparison improves normalized instruction alignment without reducing the differing-byte count. Independent scalar result components, an inline timer record, enum status and moving mode stores after ratio or clamp are rejected by their measurements. Further unchanged register or x87 spellings are not justified.

## Acceptance blockers and reopening

The preferred parent is two bytes short. Its first differing byte is +0x7A: the lifetime-end load selects ECX instead of EAX. The defect path does not retain end in EDI and omits retail's MOV EAX,EDI at +0xDF. Mode materialization and the final aggregate copy consequently use other registers. New evidence for that timer-value lifetime or the native aggregate-return construction would justify reopening.

The official scoped function gate fails both explicit scratch rows. The parent still differs; the complete companion has seven unbound direct declarations. The caller also needs its private companion binding. Exact mangled names are retained below; no pin was introduced to force acceptance.

- `?rva001B2030@Rva0058B610TrackerCalls@@QAE_NPAH@Z`
- `?rva0037D810@ExperienceLevelSystem@@QAEHURva0058B610Pair@@@Z`
- `?rva0037D840@ExperienceLevelSystem@@QAEHURva0058B610Pair@@@Z`
- `?rva0037E810@ExperienceLevelSystem@@QAE_NURva0058B610Pair@@@Z`
- `?rva0037F190@ExperienceLevelSystem@@QAEXPAURva0058B610Pair@@PAVObject@@@Z`
- `?rva0037F220@ExperienceLevelSystem@@QAE?AURva0058B610Pair@@U2@@Z`
- `?rva00381200@ExperienceLevelSystem@@QAE_NPAVObject@@@Z`
- `?rva0058b610@@YA_NPAVObject@@PAHPAM@Z`

The raw gate is `build/00593440-retry/scoped-byte-gate-raw.txt`. A landing must bind each direct declaration to its independently decoded route and verify both full bodies together. No ledger, pin, baseline or shared policy was changed. No STL symbol or pin was added or changed. CSV, pin consistency, class gate and file-level name-regression comparison pass. This revision's name-regression CLI does not support two file paths, so its unchanged library comparison was used and returned no regressions. Complete callee inventories are retained as `*-checked.txt`, and the parent unwind map as `eh-retail.txt`.

The saved bank was reprobed after recording and reproduces both measurements. Its strict receipt is `build/00593440-retry/final-bank-scoped-byte-gate.txt`; CSV and class checks pass again. Exactly one verdict was appended, preserving the previous log bytes. `git diff --check` flags the appended verdict's CRLF as trailing whitespace. The standard re_log.py writer emits that CRLF explicitly; neither the log nor the tool was hand-edited. Its raw output is `build/00593440-retry/final-diff-check.txt`.
