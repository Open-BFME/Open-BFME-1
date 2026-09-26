# AsciiString in BFME: a StringBase<char> subclass (2026-09-26)

`game/Libraries/Source/WWVegas/WWLib/ascii_string.h` used to declare
`AsciiString` as a standalone class holding one `char *`, forwarding every
method through `(StringBase<char> *)this` casts. Retail's AsciiString is
`class AsciiString : public StringBase<char>` with no data of its own. The
layout is the same (one pointer at +0), so most callers compiled identically
either way. Constructors did not: a constructor that runs code after its base
is built has to unwind that base, and a pointer member needs no unwinding.
That is why `??0AsciiString@@QAE@ABVUnicodeString@@@Z` (0x00889090, 110 B)
came out at 62/110 with no EH frame through the old header and matched exactly
from a standalone shim.

The header now derives from `StringBase<char>`. This note covers the evidence,
the blast radius, what changed and what is still open.

## Evidence

All counts come from scanning retail `.text` for `E8`/`E9` rel32 displacements,
following ILT thunks. The scratch scripts that did this were thin wrappers
over `tools/callers_of.py`'s image loader and thunk resolver, and are not
committed.

**A StringBase<char> base subobject exists.** 0x00889090's unwind funclet at
0x00C56930 is `mov ecx,[ebp-10h]; jmp 0x4A34`, and ILT 0x4A34 goes to
0x0005E490, which is `??1?$StringBase@D@@AAE@XZ`. That is the only funclet in the
image that unwinds a bare `StringBase<char>`. 5,818 funclets unwind through
ILT 0xD828, which goes to 0x0005EE90 (`??1AsciiString@@QAE@XZ`). A plain class
with a `char *` member has no base to unwind, so the old header could not
produce that funclet at all.

**The base default constructor is inline.** 0x00889090 builds its base with an
in-place `mov dword ptr [esi],0`, and the out-of-line COMDAT
`??0?$StringBase@D@@AAE@XZ` (0x00061D90, `mov eax,ecx; mov [eax],0; ret`) has
zero callers. The COMDAT exists only because StringBase.cpp explicitly
instantiates the template.

**AsciiString's destructor is an inline empty forwarder.** `??1AsciiString`
(0x0005EE90) is a bare `jmp 0x00887940`, and so is `??1?$StringBase@D`
(0x0005E490). 0x00887940 is the release body, with 7,606 direct calls from
3,139 functions. Nothing of AsciiString's own runs on destruction. Only 36
call sites (31 functions, mostly STL destroy loops and `??_GAsciiString`)
call `??1AsciiString` out of line, through ILT 0xD828. Those are the places
where MSVC did not expand the inline destructor.
`inputs/reference/shims/stringinline/StringInline.h` (probe lever
`eh-transposition`, `docs/shape_levers.md` row 2) had already found the
consequence: an out-of-line string destructor transposes the EH saved-esp
store and the argument `this` at by-value call sites. The copy and C-string
constructors were already inline forwarders in the header, and the evidence
for that is unchanged: the COMDATs 0x0005EE50 and 0x0005EE70 have 29 and 152
calls, against 2,857 and 4,287 direct calls to the StringBase bodies
0x00887B60 and 0x00888BC0.

**Other StringBase<char> members retail inlines.** These have explicitly
instantiated COMDATs but no direct caller anywhere: `str` (0x0005F270),
`getLength` (0x0005E4A0), `peek` (0x0005E5B0), `clear` (0x000680C0, itself
`jmp 0x00887940`), `swap`, `validate`, `set(char)`, `concat(char)`,
`isNotNone`, `compare/compareNoCase(const char*,int)`, `endsWith*(const
StringBase&)`, `format`, and `operator=`. `isEmpty` (66 calls) and
`isNotEmpty` (33) are mixed: many landed TUs inline them and some retail
callers do not, which is how an inline function looks when MSVC declines to
expand it in a large body. `compare(const StringBase&)` (0x0005FEB0) has 391
calls, all from the StringBase `operator<` and STL trees. AsciiString's own
`compare(const AsciiString&)` stays inline as before (repe cmpsb in
SubsystemLegend::findEntry).

## Blast radius (measured before the edit)

From the compiler's `/showIncludes` record of the baseline gate
(`build/match/*.deps.json`, joined to ledger sources through
`build.obj_path`):

| header | ledger sources that read it | matched rows they own | bytes |
|---|---:|---:|---:|
| `ascii_string.h` | 799 | 2,869 | 459,469 |
| `string_base.h` | 1,339 | 5,996 | 884,258 |

A path-suffix include-graph estimate gives 1,781 TUs and 19,421 rows. It
overcounts, because `Common/AsciiString.h` resolves to about a dozen
different shim directories depending on each TU's `// cl:` line. Use the
deps figure.

Among the 799, 55 TUs defined `inline AsciiString::~AsciiString() {
releaseBuffer(); }` themselves. With a base class, that body would release the
buffer twice: once in the body and once in the base destructor. Three
constructors in `AsciiStringNative.cpp` called the base constructor explicitly
inside the body, which would now run after an implicit default construction
and add a store.

## The change

* `template <> inline StringBase<char>::StringBase() { m_data = 0; }` in
  `ascii_string.h`. It is a specialization rather than an edit to
  `string_base.h`, so StringBase.cpp's explicit instantiation and the
  wchar_t side (1,339 readers) are untouched.
* `class AsciiString : public StringBase<char>` with the `char *m_text` member
  removed. The copy and C-string constructors are mem-initializers, and
  `AsciiString() {}` and `~AsciiString() {}` are inline. The forwarders call
  `StringBase<char>::method` directly instead of through pointer casts.
* The 55 local destructor definitions are deleted (the header's inline
  destructor replaces them). `AsciiStringNative.cpp`'s `(char)`, `(const
  char*,int)` and substring constructors use mem-initializers.
* `ascii_string.cpp`'s naked `__emit` copy of 0x00889090 could not survive the
  change: MSVC prepends the inline base construction even to a naked
  constructor. It is replaced by the real body, which matches 110/110:

      AsciiString::AsciiString(const UnicodeString &that)
      {
          format(AsciiString("%ls"), that.str());
      }

  (with a TU-local inline `StringBase<unsigned short>::str`, per the next
  section).
* Two classes of row needed a follow-up. The first gate left 8 new red rows
  out of 2,869:
  * S4DrainStringVector.cpp (4 rows): retail's `clear()` calls
    `??1AsciiString` out of line from STLport's `_Destroy`, with no argument.
    The TU now carries `#pragma inline_depth(7)`, which stops the inliner
    exactly at the destructor in the clear/erase/_Destroy chain. At the
    default depth MSVC expands it to the release body. At 6 it routes the
    explicit `p->~AsciiString()` through `??_GAsciiString` with a pushed 0,
    and at 5 `_Destroy` itself stays out of line. The destructor was
    also tried as the implicit one (no declaration). That also matches here
    at depth 7, but it perturbs register allocation in the 57 KB
    `ScriptEngine::init` (0x003107F0, script_engine.cpp, first difference at
    +0x1FF), so the header keeps `~AsciiString() {}`.
  * Four `a_` unwind-alias rows (AsciiStringUnwindCleanup.cpp,
    AsciiStringValueUnwindCleanup.cpp, AsciiStringArrayUnwindCleanup.cpp)
    are pinned by `object-symbol=$L<n>`. Those are compiler ordinals, and the
    header's different inline code renumbered them. Each one's retail bytes
    are held by exactly one label in the new object ($L853 -> $L829, $L853 ->
    $L823 twice, $L882 -> $L857), and the notes now name those labels.

`str()`, `getLength()` and `clear()` still forward to the out-of-line
StringBase members, which is deliberate. About 50 landed TUs already declare
`template<> inline ... StringBase<char>::str()` (and `isEmpty`/`getLength`)
after including the header, and they depend on that forwarding to reach their
own specialization. Defining `str()` inline in the header would make each of
them a redefinition, or make them silently bypass their own form. A new TU
that needs the inline form should keep using that one-line specialization
(the established pattern, e.g. `W3DShrubBufferRva007209F0.cpp`). Moving it
into the header means migrating those TUs in one gate, and is the next step
if anyone wants it.

## Full gate

`python3 tools/gate_baseline.py --check`, 170,710 rows:

| run | red rows | new vs baseline | null-reloc unreadable (limit 1000) |
|---|---:|---:|---:|
| before (HEAD 1d98d128c2) | 5 (all in `full_gate_baseline.txt`) | 0 | 920 |
| inheritance + `~AsciiString() {}`, no follow-ups | 13 | 8 | not checked |
| implicit destructor + follow-ups | 6 | 1 (`ScriptEngine::init`) | 1,012 |
| final (`~AsciiString() {}` + follow-ups) | 5 | 0 | 1,012 at first, 900 after the label refresh below |

The renumbered `$L` labels are also why null-reloc coverage dropped. The
function gate re-identifies a renumbered funclet by its bytes ("verified past
a renumbered $L label", 987 rows before and 1,079 after), but
`tools/null_reloc.py` reads the pinned label literally. The 799 affected TUs
held 114 stale pins (the gate counts 92 more renumbered rows after the change
than before, and the rest were already stale). Each now names the label that
`build.read_funclet`, the gate's own re-identification, resolves to a unique
body. Unreadable rows went from 920 to 900.

## Still open

The 32 bodies whose latest verdict cites this header (12.3 KB, scan below) are
mostly near misses that mention the header in passing. Their recorded walls
are register allocation, frame size or callee identity, not the string
layout. What this change actually unblocks:

* by-value AsciiString call sites that needed an inline destructor
  (`eh-transposition`). A TU no longer has to define its own inline
  destructor to get the retail order;
* AsciiString's own out-of-line constructors, and any class that derives from
  AsciiString, now get the base-subobject EH state retail has;
* header adoption for shims that were refused only because they spell the
  class as `AsciiString : public StringBase<char>`.

Scan used for the open list: the latest verdict per RVA in
`targets/game/reverse/re_attempts.log` matching
`/ascii_string\.h|StringBase<char>|canonical-header|header-inheritance|out-of-line str\(\)/i`
with status `partial` or `blocked`.
