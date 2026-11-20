# Native callable imports owned by matched source

The original import checker rejected independently proved authored C++ copies
of the six-byte callable imports `__controlfp` (RVA 0x009F7DF2) and
`___dllonexit` (0x009F7EE0) as unconditional duplicate thunks. The negative
control is real: linking the two source objects with the unchanged CODE
imports gives LNK2005 for those two public names and final LNK1169. Merely
removing their names from the import catalog would hide that conflict.

`import_binding.py` now retains the original CODE facts. It derives a
source-owned callable only from a unique current ordinary matched row and
its actual normal object, compile receipt and dependencies. The complete
six-byte executable function, real public COFF name, strong undefined IAT
symbol, zero-addend DIR32, original short-import header, both original archive
indexes and exact retail FF25 endpoint must independently agree. Generated
rows, aliases, raw assembly, token-pasted dependencies, weak routes and
source-defined IAT cells cannot enable this path. Missing or stale evidence
retains the previous refusal.

Only these proved entries receive disposable IAT-only library copies under
`build/`. Their native short-import CODE type becomes DATA; other header
fields and member payloads stay exact. Native lib.exe rebuilds both indexes.
Because it may reorder members, validation compares every member payload and
each public name's ordered provider sequence in both indexes, removing only
the proved callable publics. No original library is modified. The actual
link's MAP must select the proved authored objects, and its executable FF25
must select the strong PE import cell for the exact DLL/export. Input hashes
and compile currency are checked again after selection. Normal scoped import
checks and data-scaffold trial links use this same path.

Regression coverage includes changed members/timestamps, stale indexes,
missing index ownership, false public/MAP owners, stale sources, nonfunction
or longer-prefix bodies, wrong relocations/slots, owned cells, generated
sources and unchanged duplicate refusals. The real VC7.1 fixture contains the
two six-byte providers, complete native 18/38/18-byte CRT members and two
independent four-byte tentative COMMONs. Its original libraries fail as
above; scoped IAT-only preparation links successfully and proves both source
and PE-IAT owners. Unowned `__CIacos` remains CODE and `__onexit` remains DATA.
All 1004 projected members and 1879 retained public-provider sequences in
both indexes are verified. The fixture image is never executed.

Independent review found and reproduced a source-provenance false acceptance
before publication: VC7.1 treats backslash-newline-spliced naked/asm tokens
exactly like their ordinary spelling, emitting the same six-byte object, but
the first text guard missed them. The guard now performs C/C++ physical-line
joining before comment/literal removal, including dependency headers. Twelve
new controls cover split asm/naked/emit/token-paste, CRLF/bare-CR and a correctly
continued line comment; all twelve fail against the original guard and pass
with the fix, including a real compiler/current-receipt control. Root's final
normal native/import/archive/exploit suite passes 402 tests, with one existing
empty-fixture skip. The initial false-accepting implementation was never
published or used to admit a production provider.

A second independent fixture exposed an output/input path collision: a
library already named iat000.lib or iat000.raw.lib in the disposable output
folder could be replaced before the final hash check refused it. All resolved
frozen input paths are now excluded before any output unlink/write. Both
negative controls prove refusal before the librarian runs and preserve the
original input bytes. Only private fixture copies were used for this counterexample;
the original toolchain archives were never affected.

The reviewed BFME2 donor is 147fd3e52b36ee0306aaeef5b316beb09f7c7671,
`tools/link_cycle.py::make_import_libs/link_libraries`. Its general external
definition set was only a lead; BFME1 derives stronger evidence from actual
current source objects instead of accepting a names-only ownership set.

This is a verifier prerequisite, not a source-row admission or recovery
credit. It does not add callable pins, alter build.load_symbol_map, change a
baseline or establish full-game linking, retail placement, startup, memory,
crash or performance improvements. Provider ABI comes separately from the
native caller/public-header evidence; a jump instruction cannot prove it.
