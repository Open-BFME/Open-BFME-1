# BFME's file-system family

Everything here is derived from the image, and every vtable below is pinned by
something that byte-matches retail — a claimed constructor that installs it, or
a matched caller that reaches it at a known slot. Nothing is inferred from Zero
Hour's class names alone.

## The one structural change to know first

BFME widened `openFile` to **four parameters** across the whole family and put
each wide form at the vtable slot immediately after its narrow one. The narrow
forms became forwarders that pass the extra pair as zero — `Win32LocalFileSystem::openFile`
is 22 bytes and does exactly that:

    openFile(filename, access)  ->  this->vtable[3](filename, access, 0, 0)

The two extra parameters are NOT dead. `Win32LocalFileSystem`'s wide form at
0x009CDF50 reads one of them on its success path, compares it against zero, and
when it is non-zero makes a further virtual call on the freshly opened file. So
the wide forms are not Zero Hour's bodies with two spare arguments; they have
BFME-only logic that uses them, and recovering one means reconstructing that
logic rather than retyping a signature.

The **third** parameter is a seek offset. `Win32LocalFileSystem`'s wide
`openFile` ends like this:

    mov  eax,[esp+0x40]      ; the third argument -- see the frame arithmetic below
    cmp  eax, ebp            ; against zero
    mov  byte [esi+0x0d], 1  ; deleteOnClose
    je   done
    mov  edx,[esi]
    push 1                   ; CURRENT
    push eax
    mov  ecx, esi
    call [edx+0x14]          ; File slot 5, seek

so on success it seeks the freshly opened file to that offset before returning
it. That explains why the whole family was widened rather than just one class:
an `openFile` that can hand back a file already positioned is what reading a
member out of a BIG archive needs, and it is why the narrow forms pass zero —
zero means "no seek", which is the old behaviour exactly.

`[esp+0x40]` is the third argument, not the fourth. The prologue moves esp down
by 52 bytes — `push -1`, the two SEH pushes, `sub esp,0x18`, then ebx, ebp, esi,
edi — so the incoming arguments sit at `[esp+0x38]`, `0x3c`, `0x40`, `0x44`. The
function checks that itself: at 0x009CE01B it loads `[esp+0x38]` and `[esp+0x3c]`
as the two arguments it hands to `File::open(filename, access)`, which pins the
first two, and the seek load is one slot past them. An earlier revision of this
document called it the fourth, which did not survive the arithmetic.

`Win32BIGFile::openFile` agrees independently. It is byte-matched at 0x009D1560
and is the other place a wide form consumes rather than forwards its extra pair;
it uses the third as an offset and the fourth as a size.

The remaining wide forms — `FileSystem::openFile` and
`ArchiveFileSystem::openFile`, both matched — are pure forwarders. They pass the
pair straight through and never read either, so they are not evidence about
which is which in any direction.

This is why Zero Hour's `Win32LocalFileSystem::openFile` — the big one that
allocates a `Win32LocalFile` and creates directories on the WRITE path — is at
the *wide* slot in BFME, not the narrow one. A copy of it sitting under the
narrow signature is at the wrong arity, not merely unmatched.

When declaring these in a shim, **declare the wide overload first**: MSVC lays
out a run of same-name virtual overloads in reverse declaration order, and the
slot numbers are what the emitted call offsets depend on.

## FileSystem — free functions on the two globals

`FileSystem` is not virtual. Both `openFile` forms live at fixed addresses and
dispatch through the two globals.

| function | address | size |
| --- | --- | --- |
| `openFile(const char*, int)` | 0x009C8860 | 394 |
| `openFile(const char*, int, int, int)` | 0x009C89F0 | 445 |
| `doesFileExist` | 0x009C86A0 | 134 |
| `createDirectory` | 0x009C8DC0 | 144 |

`byte_134CB4C` in both `openFile` bodies is not a suppressor: it selects search
**order**. False runs the archive block before the local one, true runs it
after. `byte_134CA48` is the localisation subdirectory — its setter's only
caller is `GameEngine::init+291`, formatting `"Lang\%s"`.

## ArchiveFileSystem — vtable 0x01143A08

Identified by its constructor at 0x009CA9E0, which the derived BIG file system's
constructor at 0x009CC350 chains to. It is **not** a `SubsystemInterface`: slot 2
is `_purecall` where all 147 real subsystem vtables carry
`loadIniFilesFromLegend`, and `m_archiveFileMap` sits at `this+4`, straight after
the vptr, which only works if no base contributes data.

| slot | address | size | function |
| --- | --- | --- | --- |
| 0 | 0x009CAA50 | 30 | `??_G` (scalar dtor 0x009CA550, 140) |
| 1–4 | `_purecall` | | init / update / reset / postProcessLoad |
| 5 | 0x009CA5E0 | 243 | `openFile` narrow |
| 6 | 0x009CA6E0 | 253 | `openFile` wide (`ret 0x10`) |
| 7 | `_purecall` | | |
| 8 | 0x009CA150 | 323 | `doesFileExist` |
| 9 | `_purecall` | | `loadBigFilesFromDirectory` |
| 10 | 0x009CACF0 | 898 | `loadIntoDirectoryTree` — **not yet claimed** |

Non-virtual: `getArchiveFilenameForFile` at 0x009CA2A0, 411 bytes, the only
callee of slot 5.

`loadIntoDirectoryTree` is blocked only on four callee names; the source note in
`ArchiveFileSystem.cpp` lists each with what is and is not known about it.

## Win32BIGFileSystem — vtable 0x01143B40

Derives from `ArchiveFileSystem`; overrides the six pure slots and inherits 5, 6,
8 and 10 unchanged. Named by the `"*.big"` literal at 0x0107532C in its `init`.

| slot | address | size | function |
| --- | --- | --- | --- |
| 0 | 0x009CC440 | 30 | `??_G` |
| 1 | 0x009CC590 | 111 | `init` — 109/111, see the source note |
| 2 | 0x009CC710 | 832 | `openArchiveFile` — constructs a `Win32BIGFile` at 0x009D14E0. Not claimed; restructured relative to Zero Hour, see below. |
| 3 | 0x009CD660 | 117 | `closeArchiveFile` — map find, one virtual call, `_M_deallocate` |
| 4 | 0x009CD780 | 261 | `closeAllArchiveFiles` — **claimed**. BFME-only body; Zero Hour leaves the method empty. Collects every entry's `getName()` into a vector, then calls slot 3 on each — collecting first because slot 3 erases from the map it would otherwise be iterating. |
| 7 | 0x009CC3B0 | 1 | `closeAllFiles` — bare `ret` |
| 9 | 0x009CDB90 | 459 | `loadBigFilesFromDirectory` — `init` calls it through `[eax+0x24]`. Not claimed; see below. |

`openArchiveFile` is restructured rather than adapted, so Zero Hour's body is a
poor starting point. Zero Hour reads the BIG header in three separate four-byte
`read` calls — the "BIG" tag, the archive size, then the file count. Retail reads
all sixteen bytes in one call and checks the return equals 16:

    push 0x10
    lea  eax,[esp+0x40]
    push eax
    call [edx+0x0c]        ; File slot 3, read
    cmp  eax, 0x10
    jne  fail

What that global at 0x012D9030 is turns out to matter beyond this function.
0x012D9030 and 0x012D9034 are pointers to the literals `"BIGF"` and `"BIG4"`, and
retail tries the header tag against **both** with `strncmp` — accepting either —
where Zero Hour only ever recognises one identifier. So BFME reads two BIG
container formats, which is a fact about the archive format rather than about
this function.

The rest of the header handling is inlined: after the sixteen-byte read and the
two `strncmp`s, the archive size and file count are byte-swapped in registers
(`and esi,0xff00` / `shl edx,0x10` / `shr eax,0x18` / `shl esi,8`) rather than
going through a call, which is `ntohl` expanded.

The bigger restructure is how the directory is read. Zero Hour walks the file
entry by entry, issuing a `read` per field and a one-byte-at-a-time loop for each
name. Retail allocates one buffer with `operator new[]` sized
`archiveFileSize - 0x10`, reads the **whole** directory into it in a single
`read`, checks the return equals that size, and then parses entries out of
memory — offsets and sizes byte-swapped in registers from `[ebx]` and `[ebx+4]`,
the name taken at `ebx+8`. So the loop does no file I/O at all.

It also builds a substring through `??0?$StringBase@D@@AAE@ABV0@HH@Z`, the
private three-argument `StringBase` constructor, which Zero Hour's code never
calls — consistent with names being sliced out of that in-memory buffer rather
than assembled a character at a time.

Expect to write this one from the disassembly. The shape is now known end to
end: open, sixteen-byte header, two-tag check, one bulk read of the directory,
then an in-memory parse loop.

`loadBigFilesFromDirectory` is the one that resists. Zero Hour's body plus the
widened declaration compiles to 332 bytes against retail's 459, with four
callee-saved registers and `0x20` of frame against three and `0x14` — about 127
bytes of logic BFME has and Zero Hour does not.

Two dead ends already walked, so don't repeat them. The comparator is not it:
using the real `rts::less_than_nocase<AsciiString>` for `FilenameList` changes
nothing. And `FilenameList` really is a `set` — `Win32LocalFileSystem::getFileListInDirectory`
fills it through `_Rb_tree::insert_unique` at 0x00197270, which is red-black
node traversal, not `push_back`.

What the extra bytes are is still open. Between the `getFileListInDirectory`
call and the iteration, retail calls three helpers that look like vector work:
0x009CD890 (123 B) compares a requested count against `(end - begin) / 4`, which
is a `resize`; 0x009CDB40 (74 B) halves a range repeatedly, which is sort or
heap machinery; and 0x009CC4C0 (61 B) takes five arguments. Copying the set into
a vector for a reason the set does not provide is the obvious guess — but it is
a guess, and the set is already ordered, so the reason is not ordering.

Which settles the base's virtual order, since the base leaves exactly these
pure. BFME's `ArchiveFileSystem` runs: dtor, `init`, `openArchiveFile`,
`closeArchiveFile`, `closeAllArchiveFiles`, `openFile`, `openFile` wide,
`closeAllFiles`, `doesFileExist`, `loadBigFilesFromDirectory`,
`loadIntoDirectoryTree`. That is not Zero Hour's declaration order — Zero Hour
has `init/update/reset/postProcessLoad` first and `openFile` ninth — so the
slots have to come from the image, which is what every entry above does.

## LocalFileSystem / Win32LocalFileSystem — 0x01143B78 / 0x01143B98

The base at 0x01143B78 is abstract: a deleting destructor and seven
`_purecall`s. The derived vtable at 0x01143B98 is pinned three ways, all by
functions that byte-match retail — `FileSystem::openFile` reaches slot 2,
`FileSystem::doesFileExist` slot 4, `FileSystem::createDirectory` slot 7.

| slot | address | size | function |
| --- | --- | --- | --- |
| 0 | 0x009CDE30 | 30 | `??_G` — **unclaimed**; was falsely claimed at 0x005BF290 |
| 1 | 0x009CDDA0 | 1 | `init` |
| 2 | 0x009CDD70 | 22 | `openFile` narrow (forwarder) |
| 3 | 0x009CDF50 | 571 | `openFile` wide — Zero Hour's body, unclaimed |
| 4 | 0x009CDDC0 | 25 | `doesFileExist` |
| 5 | 0x009CE190 | 974 | `getFileListInDirectory` (FindFirstFileA/FindNextFileA/FindClose) |
| 6 | 0x009CDE50 | 105 | `getFileInfo` |
| 7 | 0x009CDEC0 | 137 | `createDirectory` (CreateDirectoryA) |
| 8, 9 | 0x009CDDB0, 0x009CDD90 | 1, 1 | bare `ret` — the vtable is the only evidence |

## File and its subclasses

`MemoryReadFile` and `MemoryWriteFile` are fully claimed, so their vtables give
the complete 17-slot map every `File` subclass follows:

    0 ~dtor   1 open    2 close   3 read    4 write   5 seek
    6 nextLine  7 scanInt  8 scanReal  9 scanString  10 print
    11 size   12 position  13 readEntireAndClose  14 convertToRAMFile
    15 lock   16 unlock

Slots 15 and 16 are BFME additions with no Zero Hour name: a mutex pair over
`m_mutex`, read from the imports they call — 0x009CB760 reaches
`CreateMutexA`/`WaitForSingleObject`, 0x009CB790 reaches `ReleaseMutex`.

Each subclass vtable is named by its own claimed constructor:

| class | vtable | deleting dtor |
| --- | --- | --- |
| `File` | 0x01143AF8 | 0x009CB950 |
| `MemoryReadFile` | 0x01143A38 | 0x009CB440 |
| `MemoryWriteFile` | 0x01143AA8 | 0x009CB650 |
| `RAMFile` | 0x01143C58 | 0x009D1C30 — unclaimed |
| `StreamingArchiveFile` | 0x01143CA8 | 0x009D22B0 |
| `Win32LocalFile` | 0x01143C10 | 0x009D1960 — unclaimed |
| `LocalFile` | 0x01143D38 | 0x009D26C0 — unclaimed |

`Win32LocalFile`'s and `LocalFile`'s vtables share every slot but slot 0, so the
method bodies at 0x009D2480–0x009D2970 belong to both.

## The BFME string, which is where most of the work goes

Most functions here differ from the Zero Hour reference in the same three ways,
and all three are the reference header expanding something retail keeps thin:

* `getLength()` is a 16-bit field at buffer+4, not a `strlen`; characters start
  at buffer+8, not +4;
* `find(char)` is a length-bounded scan over that range, not `strchr`;
* the constructor from `const char*` (0x00888BC0), `set` (0x00887C90), the copy
  constructor (0x00887B60) and `releaseBuffer` (0x00887940) are all out-of-line,
  and the one-argument `concat`s are inline wrappers over the two-argument
  `StringBase<char>::concat` at 0x00887D60.

`inputs/reference/shims/asciistring_thin` un-inlines the first three; write the field
reads and the concat wrappers out in the source. Do **not** un-inline `concat`
itself — it resolves to the right address and looks close, but models as
out-of-line something retail inlines, and it does not match.

Also check the TU has `/D_STLP_USE_STATIC_LIB`. Without it the STLport allocator
comes out as an import thunk (`ff 15`) where retail calls it directly (`e8`).

And check the exception setting per function, not per class. `build.py`'s base is
`-EHsc-`; a per-file `// cl:` line that adds `/EHsc` turns them back on. Retail
built `Win32BIGFileSystem::closeArchiveFile` *without* exceptions — no SEH frame
at all, despite an `AsciiString` temporary with a destructor — and
`loadBigFilesFromDirectory` on the same class *with* them. Two methods of one
class that disagree about exceptions cannot have shared a translation unit, so
retail's sources were split more finely than Zero Hour's. If a function is the
right length but carries an `fs:[0]` prologue the target lacks, that is a flag
difference, not a code difference, and it may also mean the function belongs in
its own file.

## Two bodies that got close, and what happened to them

`Win32BIGFileSystem::openArchiveFile` (0x009CC710, 832 bytes) and
`Win32BIGFileSystem::loadBigFilesFromDirectory` (0x009CDB90, 459 bytes) each
reached their exact retail length without ever matching. Both lived under `game/`
as sources carrying no matched row, which the commit gate rejects — a source
nothing has byte-verified is a reconstruction, not a port, and there is
deliberately no exception list. An earlier revision of this work added
`targets/game/reverse/unclaimed_sources_whitelist.txt` believing it exempted them. It does
not: that file is read only by `tools/find_declared_unmatched.py`, which scans
`src/`, while the gate's own check in `tools/build.py` honours nothing.

`openArchiveFile` was removed on those grounds. Its body is recoverable in full:

    git show 1e975e7ea:game/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem_openArchiveFile.cpp

`loadBigFilesFromDirectory` **survives**, and the reason is worth recording. Its
TU no longer carries zero matched rows: five STL instantiations the vector work
below drags in — `fill`, `swap`, `__copy`, `__copy_backward` and
`__insertion_sort`, all over `AsciiString` — are claimed out of it. So the file
now earns its place by the same rule that would have removed it. That is the
general escape hatch for a body stuck one idiom short of matching: the templates
it instantiates are separate functions, and they can be landed on their own.

What they established, which is the part worth keeping:

**openArchiveFile.** BFME does not walk the directory entry by entry the way Zero
Hour does. It reads the sixteen-byte header in ONE read and checks the result
equals 16; it accepts either container tag, trying `"BIGF"` (0x012D9030) and
`"BIG4"` (0x012D9034) with `strncmp`; and it allocates a single buffer of
`archiveFileSize - 0x10` with `operator new[]`, reads the WHOLE directory into
it, and parses in memory. That last point is why it slices names with the private
three-argument `StringBase` constructor instead of building them a character at a
time — there is no file I/O in the parse loop. `ntohl` is expanded inline in
registers on the header fields and on every entry's offset and size, so no call
for it appears. The separator scan runs BACKWARDS from the end of the name
(`mov al,[esi+ebp]` / `cmp` / `dec ebp` / `jns`), and the frame needs two index
variables, not one.

**loadBigFilesFromDirectory.** BFME copies the filename set into a vector,
`stable_sort`s it, and then REVERSES it. That is not redundant even though the
set is already ordered: `FilenameList` is keyed on `rts::less_than_nocase`, so it
arrives in case-insensitive order and comes out in descending default order. For
`.big` files that sequence is load precedence, so it is a deliberate behaviour
change. Each step was pinned by the length it produced against retail's 459:

    Zero Hour's body, no vector at all      332
    + resize / copy / sort                  403
    + range-construct instead               397
    + assign instead                        387
    + stable_sort rather than sort          413
    + reverse after the sort                459   <- exact

Both stalled on the same thing that stalls `Win32LocalFileSystem::openFile`:
register assignment. Retail holds `this` in a register whose addressing costs one
byte less than the one MSVC picks here, and that single byte shifts everything
downstream. Worth retrying together, since one explanation probably covers all
three.
