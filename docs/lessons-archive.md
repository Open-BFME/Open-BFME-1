* When hand-declaring a class just to carry a naked body's decorated name, the access specifier is part of the name: MSVC encodes public as Q, protected as I and private as A in the third character (`??0X@@QAE@XZ` vs `??0X@@IAE@XZ`). Declaring DisconnectManager's constructor under `protected:` produced ??0DisconnectManager@@IAE@XZ and the build failed with "symbol not found in object" rather than a byte mismatch, which is the tell. Match the reference header's section, not just the signature.

* A byte-exact function needs every call site to resolve, so a big function's
  cost is set by its least-known callee, not by its size. GameEngine::init is
  7123 bytes with 165 distinct call targets: 92 are named, 73 are not. Of those
  73, sixteen are the 154-byte initSubsystem bodies that cannot be claimed until
  their T is proven, and only seven reference a string that could anchor a name
  -- the other fifty have no evidence attached to them at all. So init is not
  blocked on effort or on codegen, it is blocked on roughly fifty independent
  naming problems, and counting them is cheaper than discovering them one
  mismatch at a time. Run the same count before committing to any large
  function: for each call, deref the thunk chain and check functions.csv plus
  symbols.csv. Applied to the 96 INI block parsers the same count sorts them
  into four with no blockers, eleven with exactly one, and the rest with two or
  more, which is a work queue rather than a list.

* A MASM dump byte-matches at any length you give it, because it is the retail
  bytes. That makes an over-long dump row invisible to the verifier in a way an
  over-long C++ row is not: ?parse@DataChunkInput@@QAE_NPAX@Z claimed 1006 bytes
  where the function is 231, ran past its ret 0x10 and the int3 padding after it,
  and silently swallowed three later functions -- one of which, LocalFile's
  constructor, then could not be claimed because its address was already inside
  somebody else's range. tools/audit_short_rows.py looks for the opposite
  mistake. Check a dump row's size against a real disassembly before trusting
  it, especially when a claim inside its range mysteriously will not land.


## A mangled name can encode an argument list the body does not have

`?queueSend@Transport@@QAE_NIGPBEH@Z` mangles four parameters
(`UnsignedInt, UnsignedShort, const UnsignedByte *, Int`), so a `__thiscall`
body would end in `ret 0x10`. BFME's body at 0x00683830 ends in `ret 0xc`, and
the caller (`NAT::sendAProbe`, 0x00671020) builds a local
`{ UnsignedInt ip; UnsignedShort port; }` on the stack and passes its address --
the callee reads `[ecx]` and `[ecx+4]` off it. BFME merged the reference's first
two scalars into one struct-by-pointer, so the name in the ledger cannot be the
name retail's linker emitted, and the struct's type name is not recoverable
from a POD with no RTTI.

The row is harmless as long as it only claims the 5-byte thunk, which is what it
does, but it will silently mislead anyone who trusts the name to write the body.
Check `ret imm16` against the mangled parameter list before writing a body from
a thunk-claimed name: the stack-pop is free evidence and it disagrees loudly.

## Compilers pick an induction base by a tie-break you cannot see from the source

`Transport::Transport` clears two 128-element arrays in one loop, and every
candidate base address gives the same instruction count and the same total
length. Retail anchors on `&m_inBuffer[i].length`; writing the out buffer first
anchors on `&m_outBuffer[i].length`, writing the in buffer first anchors on
`&m_inBuffer[i].data`. All three are 182 bytes of the same instructions. When a
body reaches the right length with the right instructions and differs only in
which base register displacement scheme was chosen, source-order permutations
are unlikely to be the lever; stop permuting and mark it present-unmatched.

* tools/find_declared_unmatched.py reads the `//` comment line immediately above
  a definition as that definition's declared symbol, so an explanatory comment
  whose line *begins* with a mangled name is taken as the symbol and the
  pre-commit hook rejects the file. This cost three cycles in one session --
  `// ??_7RAMFile@@6B@ is at 0x01143C58, which...`,
  `// ?newTerrain@TerrainTypeCollection@@, on the same receiver...`, and
  `// ?findNonConstCommandSet@ControlBar@@ -- so it is the CommandSet parser`.
  Write the name in prose form (`ControlBar::findNonConstCommandSet`) or push it
  off the start of the line. The failure looks like "staged sources define
  functions the ledger does not declare" for a function that is plainly in the
  ledger, which is the tell.


## A claimed address that is not an instruction boundary cannot be a function

MASM byte dumps byte-verify against whatever bytes they were cut from, so a dump
cut out of the middle of the wrong function passes the gate forever. Eight rows
in the ledger were exactly that, 4,502 bytes of coverage that was never real.
Every one of them claimed an address that lands *inside* an instruction of the
function containing it -- one of them three bytes into a `cmp`, another one byte
into an SEH prologue's `mov eax, fs:[0]`.

The test is decisive and needs no judgement: linear-disassemble from the
containing function's start; if the decode walks straight over the claimed
address without landing on it, the row is wrong. `tools/audit_claim_boundaries.py`
does this and stays silent on everything ambiguous -- a desynced decode, a claim
in a gap, a claim that is itself a known function start. That is why it finds
eight rows where two earlier attempts at ledger auditing found thousands of
things that were fine and got thrown away.

Two of the eight were also blocking real work: the bogus range covers the
function the dump was cut from, so no honest claim on that function can be
added while it exists. `?setGameOptions@GameSpyInfo@@UAEXXZ` sat 198 bytes
inside `NAT::notifyUsersOfConnectionFailed`, in a different translation unit
entirely -- which is its own tell, since functions from different TUs do not
interleave in the image.

* A row whose size makes it unfalsifiable can carry a wrong name past every check
  the gate has, and there are three shapes of it. A MASM dump is the retail
  bytes, so it matches at any length -- ?parse@DataChunkInput@@ claimed 1006
  bytes against a 231-byte function and swallowed three later ones. A five-byte
  thunk row matches any ILT entry, because every one is E9 xx xx xx xx --
  ?showBuildTooltipLayout@ControlBar@@ claimed the thunk whose body is
  ?friend_lookupScience@ScienceStore@@, and ?undoNamedMapReveal@ScriptEngine@@
  claimed the one whose body is ?removeNamedMapReveal@ScriptEngine@@. A one-byte
  row is a bare ret and matches every empty function in the image.
  For all three the test is the same and it is cheap: deref the thunk chain or
  measure the body by disassembly, then ask what the ledger already says that
  address is. Do it before adding the row, not after a mismatch elsewhere sends
  you looking.
  Note the comment trap interacts with this: writing the evidence into the source
  as `// ?showBuildTooltipLayout@ControlBar@@ claimed ...` makes
  find_declared_unmatched.py read that line as the next definition's symbol. The
  lesson above about prose form applies to the comment documenting this one --
  which is how it was hit for the fourth time in a day.

## Adding a shim header does not invalidate the build cache

The deps cache records the headers a TU resolved *last* time. A brand-new shim
header is a path it has never seen, so adding one and rebuilding reports
"Compile: 0 of 1 TU(s) (deps-cache: 1 current)" and silently compiles the old
output. This cost two rounds of "the shim isn't working" before the pattern was
obvious: the compiled bytes had not changed at all, which is the tell -- a shim
that is genuinely being ignored usually still shifts *something*.

Touching the file is not enough either; the cache keys on content. Change the
source, even by a character in a comment, and it recompiles.

## MSVC shaping rules that only turn up as byte diffs

Four of these cost an iteration each before the pattern was obvious. All were
found while matching functions that were otherwise structurally identical.

**A loop is not interchangeable with its unrolled form.** In
`Win32BIGFile::getFileInfo` the compressed-size decode only matched when written
as `for (i = 0; i < 4; i++) size = (size << 8) | header.size[i];`. MSVC unrolls
that two iterations at a time, and that is what pairs the byte loads into the
dword and word accesses retail emits. Every hand-unrolled spelling of the same
value -- including the one grouped exactly the way the target accumulates --
schedules the third byte's load early and loses the pairing.

**Splitting a byte buffer into named sub-arrays changes how loads widen.** The
same function needed `struct { unsigned char magic[2]; unsigned char size[4]; }`
rather than a flat `unsigned char[6]`. MSVC widens a pair of adjacent byte reads
to the widest access that stays inside *the array they belong to*, so `size[0]`
gets a dword and `size[2]`, with two bytes of the array left, gets a word. A flat
buffer gets neither.

**Naming a member through a reference is not cosmetic.** In
`Win32BIGFile::setNameAndPath`, writing `AsciiString &name = m_name;` once
instead of `m_name.set(...)` twice makes MSVC hoist the address into a
callee-saved register ahead of an inlined strlen. That costs the register that
forces `this` onto the stack, which is what grows the frame by the four bytes
retail's `chkstk` asks for. Same code, four bytes of frame apart.

**Initialiser list versus constructor body decides ordering against member
array construction.** `ChunkLoadClass`'s constructor only matched with its first
three members in the initialiser list: members initialise in declaration order,
which is what puts their stores ahead of `HeaderStack`'s 256 element
constructors. Written in the body they land after.

## CORRECTED: WW3DFormat is still dense; only one helper takes D3DFORMAT

This entry previously claimed BFME replaced `WW3DFormat` with Direct3D's own
enumeration, and that this was why the texture pipeline would not scan. The first
half is wrong and the second does not follow.

What is true: the 180-byte function at 0x0090C400 switches on 20 through 30, 40,
41, 50 through 52 and 'DXT1' through 'DXT5', which are `D3DFMT_` values exactly,
and it matches with those values declared locally in `ww3dformat_bits.cpp`.

What was assumed: that its parameter is a `WW3DFormat`. The mangled name
`?Get_Bits_Per_Pixel@@YIIW4WW3DFormat@@@Z` is **not** in `reverse/symbols.csv` --
it was invented when the row was added, so the `W4WW3DFormat@@` in it is a guess,
not evidence. The function takes a D3DFORMAT; the name is what needs revisiting.

The counter-evidence is direct: `WW3D_FORMAT_COUNT` sizes
`DX8Caps::SupportTextureFormat[]` and bounds seven loops in `dx8caps.cpp`, and
`Compute_Caps` (0x0091C230, 2220 bytes) matches today with the dense 26-entry
enum. Sparse D3D values would make that array absurd. So do **not** renumber
`ww3dformat.h`.

The texture pipeline's real blocker is still open. `locate.py` places nothing
from `texture.cpp` (0/53), `textureloader.cpp` (0/67), `surfaceclass.cpp`
(0/27), `ddsfile.cpp` (0/17), `bitmaphandler.cpp` (0/12) or `texproject.cpp`
(0/26). Whatever it is, it is shared across all six and it is not the enum.
Suspect a class layout -- `TextureBaseClass` is the common root -- and find it
the way `HRawAnimClass`'s was found: reconstruct one small function and let the
first wrong byte name the field.

## Header changes cost a full gate, and the gate lock is host-wide

`build.py` takes an exclusive lock for any build over 8 TUs, and the pre-commit
hook runs a full gate for any staged header or shim change. With sibling clones
running their own gates, a header commit sat queued for 44 minutes without
compiling a single TU -- the holder had burned 10 seconds of CPU in that time,
because it was serialised too.

Per-file verifies stay under 8 TUs and take no lock. So the way to land header
work is to make every header edit first, check the blast radius by hand with
`./build.sh` on each dependent source, and then pay the gate once. Landing them
one at a time costs a queue wait each.

Corollary: the union merge on `reverse/symbols.csv` can silently drop pins
during a rebase. Check `git status` before pushing -- two pins the converted
`Set_Animation` bodies needed went missing that way and only turned up because
the working tree still had them.

## To name a global, find its setter and then the setter's callers

`FileSystem::openFile` reads three globals that nothing named. Reading the
global itself is useless -- all three live in `.data`'s zero-fill tail, so their
file bytes are the next section's, and even with correct bytes they are written
at runtime.

What works is going up the write side, one hop at a time:

1. Scan `.text` for the 4-byte little-endian address. `tools/xref_global.py`
   does the claimed half; the unclaimed sites are the interesting ones, because
   a global's *writers* are usually small unclaimed helpers.
2. Disassemble each site. A write that stands alone between `int3` padding is a
   whole setter function -- `0x00061BE2` is literally
   `mov byte [0x0134CB4C], 1; ret`.
3. Scan for `E8` calls to that setter. Setters have few callers.
4. Read the caller's arguments. That is where the name lives.

For `byte_134CA48` the chain ended at `GameEngine::init+291`, which formats
`"Lang\%s"` and passes the result -- so the global is the localisation
subdirectory, and `sprintf("%s\\%s", byte_134CA48, filename)` is the
language-specific lookup path. No other evidence in the image says that.

The same sweep also settled `byte_134CB4C` against the reading that was already
written down. It had been guessed to suppress the archive lookup; the
disassembly shows two archive blocks, one gated on `!flag` before the local
block and one gated on `flag` after it. It selects search *order*, not
presence -- a distinction a byte dump cannot express and a guess got backwards.

Note what the chain does NOT give you: a retail identifier. Knowing a global is
the language path is not knowing what EA called it, so these stay
`byte_134CA48`-style address names. The evidence names the *role*; only a symbol
source names the symbol. Record the role in the header and leave the name alone.

## An inlined member call materialises its receiver at the inline site

`File::open` came out six bytes long and would not shrink. The extra bytes were
a `push esi`/`pop esi` pair and a loop-align nop, and the cause was one
instruction in the wrong place: retail computes `lea ecx,[edi+4]` immediately
before the `set` call, and we computed it before the null-check branch.

That one hoist cascades. Holding `&m_nameStr` in ecx across the branch means the
inlined strlen loop cannot use `cl`, so it uses `dl`; that pushes `filename` out
of `edx` into a callee-saved register; that is a third `push`/`pop`; and the
extra instructions push the loop off a 16-byte boundary so the compiler inserts
an align nop. Six bytes, none of them at the site of the actual difference.

The trigger is that `m_nameStr = filename` goes through `AsciiString::operator=`.
When an inlined member call is expanded, its receiver is a *parameter* of the
inlined body, so it is materialised where the body is spliced in -- the dominator
of everything inside, including the `s ? strlen(s) : 0` diamond. Writing the same
expression as a direct call on the member instead:

    ((StringBase<char> *)&m_nameStr)->set( filename, filename ? (int)strlen( filename ) : 0 );

lets the receiver sink to the call it belongs to, and retail's shape falls out
on its own -- one callee-saved register, `push len; push filename; lea ecx,[edi+4]`.

This is the same expression either way; only the spelling differs. So when a
function is a handful of bytes long and the diff is register choice rather than
control flow, suspect an inlined operator or accessor whose receiver got hoisted,
and try spelling the call out. Hoisting an address above a branch is cheap to
cause and expensive to spot, because the byte that differs is nowhere near the
line that caused it.

## Never pass `--no-verify` to `tools/add_match.py`

It writes `matched` into the ledger without building, so it manufactures a claim
that is simply false. Doing this to `HTreeClass::Combo_Update` repointed the row
from its MASM dump to `htree.cpp` and staged a lie for commit; only the
pre-commit full gate would have caught it, tens of minutes later. If a row needs
to move while the answer is still unknown, leave it on the dump.

## A folded body is not evidence about the class it is named after

MSVC folds identical COMDATs, so one address can serve many symbols, and a row
naming that address is only as good as whoever assigned it. Two rows claimed
`NodeMotionStruct`:

- `??0NodeMotionStruct@@QAE@XZ` at 0x005CD350 -- a constructor zeroing *eight*
  dwords
- `??_ENodeMotionStruct@@QAEPAXI@Z` at 0x005D5B60 -- a vector deleting destructor
  whose element destructor is `mov [ecx],0x1073744; ret`, a vtable store

`NodeMotionStruct` has no vtable, so the second was impossible on its face, and
neither address had a single xref. Both were generic bodies that happened to
compile the same.

The way to identify a constructor is to find the site that *passes* it: an array
`new` hands the constructor to `` `eh vector constructor iterator' `` as an
immediate, alongside the element size. `xrefs_imm(IMAGE_BASE+candidate)` found
exactly one site for 0x009594A0, and it was HRawAnimClass's node-motion
allocation -- `lea ecx,[esi+esi*8]` (nine dwords), `push 0x24`, result stored to
`[ebp+0x4c]`, which is the field `HTreeClass::Anim_Update` reads back.

## BFME's NodeMotionStruct has nine channels, and the ninth is a fade

Zero Hour's is X, Y, Z, XR, YR, ZR, Q, Vis -- eight pointers, 0x20 bytes. BFME
inserts a `MotionChannelClass * Fade` **ahead of Vis**, so Vis moves to +0x20 and
the array stride becomes 0x24. Three independent confirmations:

- `nodeMotion += 1` compiles to `add esi,0x24` (0x0095468B)
- the allocation pushes 0x24 as its element size (0x0095AE37)
- `~NodeMotionStruct` destroys +0x1c through `MotionChannelClass::~MotionChannelClass`
  (0x00978140) and +0x20 through a different one (0x00978160, BitChannelClass)

The destructor is worth a second look: it deletes X..Q, then **Vis, then the
fade**, even though the fade is declared first. Declaration order sets the
layout; the destructor body is hand-written and simply appends the new delete to
Zero Hour's existing run. Both orders have to be reproduced, and they differ.

## HAnimComboDataClass has no PrevFrame

Retail exposes exactly two float accessors on it, `fld [ecx+4]` and `fld [ecx+8]`,
and both `Get_` and `Peek_Pivot_Weight_Map` read `[edx+0xc]`. Three dwords ahead
of the pivot map leaves no room for a third float. `Combo_Update` multiplies the
+8 one by the pivot map entry and gates on it being non-zero, so it is the
weight, and the class is HAnim, Frame, Weight, PivotMap, Shared.

Our ledger had the +8 accessors named `Get_`/`Set_Prev_Frame`. Renaming them to
their Weight spellings keeps them matched -- the bytes never changed -- and drops
`Set_Frame` back to a plain store instead of Zero Hour's `PrevFrame = Frame;
Frame = frame;`, which let four more accessors land at once.

## BFME's HAnimClass is 0x10 bytes -- there is no embedded-sound bone

`HTreeClass::Anim_Update(HRawAnimClass*)` came out 2046 of 2047 bytes with a
single byte wrong: `mov esi,[esi+0x4c]` against our `+0x50`. That byte is
`Get_Node_Motion_Array`, and every member ahead of it is fixed, so the base class
was one dword too large.

`HAnimClass : public RefCountClass, public HashableClass` is two vptrs, `NumRefs`
and `NextHash` -- 0x10 exactly -- with no room for Zero Hour's
`EmbeddedSoundBoneIndex`. Its three accessors were declared *after* `Class_ID`,
so they sat at slots 23-25 and removing them costs no slot anything reaches.
Corroboration: both `Animatable3DObjClass::Set_Animation` bodies that were
reconstructed from retail contain no embedded-sound code at all, while the
unmatched Zero Hour copies in `animobj.cpp` do.

## CORRECTED: MotionChannelClass has no CompressedData at all

This entry previously concluded that `CompressedData` survives in BFME but sits
past `LastFrame`, because deleting it also deletes `Do_Data_Compression` -- its
only caller -- and that function is the only thing in the tree that emits
`WWMath::Float_To_Int_Floor`, which owned a matched row.

That reasoning preserved a row at the cost of the layout, and the layout was
wrong. `HRawAnimClass::read_channel` allocates the class at 0x00959AF6 with
**push 0x20**: eight dwords, which is PivotIdx, Type, VectorLen, ValueOffset,
ValueScale, Data, FirstFrame and LastFrame with nothing left over. The
constructor at 0x00977760 confirms it -- it zeroes +0 through +0x14 and sets
+0x18 and +0x1c to -1, then stops.

So `CompressedData` and `Do_Data_Compression` are both gone, and the
`Float_To_Int_Floor` row was dropped: nothing in the tree emits it any more.
Retail does contain it, at 0x007239D0 with no callers at all, so some other BFME
translation unit emits it as dead code; whoever finds that one can restore the
row there.

The general lesson stands but with the priority the other way round: removing
code can delete a matched symbol, and you should notice when it does -- but a
row is not worth a layout. Fix the layout, then go find where the orphaned
symbol really lives.

## Destructors are the blind spot of the byte gate

A destructor consists almost entirely of the two operands `build.py` masks:

  * `??1<C>` installs the vptr — `mov [ecx], offset <C>'s vtable` — a DIR32,
    filled in from the target;
  * `??_G<C>` calls the scalar destructor — a REL32, filled in from the target.

Strip those and a destructor is a prologue, a store, and an epilogue. So the
gate tests the *shape* and never the class, and a destructor row can carry any
name at all and stay green forever. This is the same unfalsifiable-size problem
as a 5-byte ILT thunk and a 1-byte bare `ret`, except it is not tied to a size,
so `audit_short_rows.py` and `audit_thunk_rows.py` both walk straight past it.

It is not hypothetical and it is not rare. When this was written the ledger had
205 different class names on 0x005BF290 alone, and 51 scalar-destructor
addresses claimed by more than one class.

What makes it tractable is that the masking has a floor. Identical bodies really
are folded by the linker, and folding really does put several correct names on
one address — so "several names, one address" is not by itself a defect. But
folding cannot join two bodies that install *different* vtable pointers, because
those bodies differ before masking, and a vtable belongs to exactly one class.
So n distinct class names on one body that installs a vtable means at least n-1
are wrong, and that conclusion needs no view on which one is right. By that test
alone, 111 rows are wrong.

Deciding which name survives needs the vptr read back out of the image and
matched against a claimed constructor that installs the same pointer.
`??0RAMFile@@` installs 0x01143C58, so the body at 0x009D19A0 installing
0x01143C58 is `~RAMFile` and the `??1SaveLoadSubSystemClass@@` row on it is
wrong. Note what that attribution rests on: a false `??0` would propagate
through it unchallenged, so confirm the owner against a vtable pinned by a
byte-matched *caller* before editing anything.

`tools/audit_dtor_aliases.py` runs both halves. The general lesson is worth
separating from destructors: whenever a construct's identity lives entirely in
relocated operands, the byte gate cannot see it, and the check has to come from
somewhere the relocation still exists — a vtable, a caller, or a string.

## MSVC lays out same-name virtual overloads in reverse declaration order

`Win32LocalFileSystem::openFile` is a 22-byte forwarder: BFME widened `openFile`
to four parameters and left the two-parameter form calling the wide one. Written
the obvious way —

    virtual File *openFile( const char *, Int );                // meant to be slot 2
    virtual File *openFile( const char *, Int, Int, Int );      // meant to be slot 3

— it compiled to 21 of 22 bytes, with `call [eax+0x08]` where retail has
`call [eax+0x0c]`. Overload resolution was right; the slot was not. Swapping the
two declarations, widest first, fixed it.

MSVC assigns vtable slots to a run of overloads sharing a name in *reverse* of
the order they are declared. So when the target calls one overload through the
vtable, the declaration order in the shim is load-bearing, and the natural
narrow-to-wide reads as the wrong slot.

The symptom is worth recognising because it is easy to misread: a one-byte diff
in a `call [reg+disp]` displacement looks like a wrong slot *number* — a
miscounted vtable — when the count is right and only the ordering is wrong.
Check for an overload set before recounting slots. Anywhere a shim declares two
virtuals with the same name, the order is a decision, not a formatting choice.

## A folded ??_G body can make two pools look like one symbol

Adding `??0HAnimComboClass@@QAE@H@Z` (0x00974820) tripped the gate's DIR32
consistency check:

```
?Allocator@?$AutoPoolClass@VHAnimComboDataClass@@$0BAA@@@0V?$ObjectPoolClass@...@A
    bases ['0x134b128', '0x134bc4c']
```

Retail is perfectly consistent: 0x134b128 is referenced only from the
dx8renderer range (0x009463C1, 0x009463DA, 0x009465F5, 0x00947668, 0x00949CA1,
0x00949CB0) and 0x134bc4c only from the HAnimCombo range (0x009745B1,
0x009745CA, 0x00974881, 0x0097492E, 0x00974E07). They are two different pools'
statics.

Our build conflates them. `PolyRenderTaskClass : AutoPoolClass<PolyRenderTaskClass,256>`
is declared correctly, so this is not a source typo -- it is that
`??_GPolyRenderTaskClass` and the HAnimComboDataClass `??_G` compile to identical
bodies, fold, and the surviving copy carries only one of the two relocations. The
claim at 0x00947668 therefore rests on a folded body, exactly like the
NodeMotionStruct rows did.

The row was dropped rather than whitelisted. Whitelisting would bury a real
ambiguity, and the remaining 31 rows from that batch are unaffected. Resolving it
properly means deciding which of the two `??_G` claims owns 0x00947668 -- do that
before re-adding the constructor.

Watch for this whenever a new row lands near a pooled class: the DIR32 check is
the only thing that sees it, and the per-file verify a delta commit runs does
not.

## Naming a temporary can decide which stack slot it gets

`ArchiveFileSystem::openFile` is Zero Hour's three lines unchanged:

    archiveFilename = getArchiveFilenameForFile(AsciiString(filename));

and written that way it came out the right length with the right calls, but the
two `releaseBuffer` calls at the end came out in the opposite order. Nothing was
wrong with the lifetimes — both temporaries die at the end of the full
expression either way, and in reverse construction order. What differed was
which stack slot each got: the argument temporary and the returned temporary had
swapped places, and that rippled into the register choices for the rest of the
function.

Giving the argument a name and a block fixed it:

    {
        AsciiString key(filename);
        archiveFilename = getArchiveFilenameForFile(key);
    }

Same lifetimes, same destruction order, same generated calls — different slot
assignment. So when a function is the right length, calls the right things in
the right order, and still differs in `[esp+N]` displacements and register
picks, look at the temporaries before doubting the structure. An unnamed
temporary inside a call expression and a named one in a block are not the same
input to the register allocator, even though they are the same C++.

Worth pairing with the note on inlined member calls materialising their
receiver: both are cases where the spelling, not the semantics, is what the
compiler is responding to.

## A compiler-generated name cannot be checked by anything but its relocations

A full gate failed on a DIR32 conflict:
`?Allocator@?$AutoPoolClass@VHAnimComboDataClass@@$0BAA@@@` resolved to two
different bases, both from `hanim.cpp`. `??0HAnimComboClass@@` gave 0x0134BC4C,
which is that class's pool. A row named `_$E8` at 0x00C71350 gave 0x0134B128 —
the `PolyRenderTaskClass` pool, which `dx8renderer.cpp` owns. So the funclet at
0x00C71350 belongs to a different translation unit, and `hanim.cpp` still
verifies 66/66 without it.

`_$E8` is an exception funclet: a compiler-generated symbol. That makes it the
worst case of the unfalsifiable-row problem, for two reasons at once.

The *body* is unfalsifiable in the usual way — its only distinguishing operand
is a DIR32, which `build.py` fills in from the target, so it byte-matches
wherever you put it. And the *name* is unfalsifiable too: `_$E8` says nothing
about a class, a signature, or a translation unit, so none of the naming oracles
apply. There is no vtable slot to read, no string literal to anchor to, no
sibling class whose method set constrains it. Every technique that resolved a
wrong `??1` or `??_G` row is unavailable here.

What caught it is the one check that looks at the masked operand instead of the
bytes: DIR32 consistency, which noticed that two rows in the same TU disagreed
about where one symbol lives. That only works when the funclet happens to touch
a global some *other* row in the same TU also touches. Thirty-one `_$E` rows
remain in the ledger; none is currently contradicted, but that is the absence of
a coincidence rather than evidence they are right.

So treat a compiler-generated row as carrying no claim at all. If one is
blocking something, prefer deleting it to relocating it — there is nothing in it
to be right about.

## `locate.py --emit` will re-add a row you deliberately dropped

`??0HAnimComboClass@@QAE@H@Z` (0x00974820) is dropped because it trips the DIR32
consistency check -- see the folded-`??_G` entry above. It locates cleanly, so
every `tools/locate.py Code/Libraries/Source/WWVegas/WW3D2/hanim.cpp --emit`
puts it straight back, and the next full gate rejects the commit again. It has
cost two gate runs so far.

There is no suppression list. After an `--emit` sweep, diff the staged ledger
(`git diff --cached -- reverse/functions.csv`) and check nothing deliberately
excluded has returned, rather than trusting `check_csv` -- a re-added row is
perfectly well-formed, so `check_csv` is silent about it.

## If every shell command starts failing, check the session temp directory

Symptom: commands that produce output exit 1 and return nothing, while `true`
and `echo hello > /dev/null` succeed. It looks like the shell died; it has not.
The harness writes each command's output to a file under its session directory
in `/tmp`, and if that directory goes missing -- `/tmp` here is a 16G tmpfs that
sits around 80% full with four clones building -- every command that writes
anything fails while silent ones still work.

`mkdir -p` on the session directory restores it. Until then, `cmd > /tmp/x 2>&1`
followed by reading `/tmp/x` with the Read tool is a working escape hatch, and is
how to run diagnostics (`df`, `ls`) while the capture is broken.

Do not read this as a disk-full problem without checking: the root filesystem had
237G free throughout.

## The near-miss tie-breaks are not a compiler-flag mismatch

A recurring failure looks like this: the body compiles to retail's exact length
with retail's exact instructions, and differs only in which registers hold what,
or in the order of two adjacent stores, or in where one block was placed. It has
now blocked Transport::queueSend, the Transport and NetPacket and Connection
constructors, getNATPortAllocationScheme, FrameDataManager::addNetCommandMsg,
DisconnectManager::processDisconnectVote, and two NAT notify functions.

Nine instances invites the theory that retail's netcode was built with different
optimisation settings than our `-O2 -GR- -EHsc-`. It was not. Tested per-source
against the NetPacket constructor, whose only defect is that retail stores the
vptr before two field zeroes and we hoist an inlined init's stack temp above
them: `-O1`, `-Ox`, `-G6`, `-G7`, `-Os` and `-Oy-` all still fail, and none of
them turns any part of it green.

So these are per-function source problems, not a global setting, and the lever
is the shape of the source -- statement order, whether a value is a named local,
argument evaluation order. When a body is the right length with the right
instructions, stop reaching for flags.

Note also what a global flag change would have to survive: about 14,000 rows
already byte-match under -O2, so any setting that fixes a near-miss must keep
all of those. Per-source `// cl:` flags are the only safe place to experiment.
## Do not run a per-file verify while a full gate is running

A full gate reported two NEW DIR32 inconsistencies:

```
__except_list:    bases ['0x0', '0xd', '0x83000000']
__real@4f800000:  bases ['0x1075358', '0x3b04c083', '0x8f4c8dc0']
```

Both look alarming and neither is real. `0x83000000`, `0x3b04c083` and
`0x8f4c8dc0` are instruction bytes, not addresses, and `__except_list` is a
compiler-internal symbol whose address is 0 by definition.

The cause is concurrency, not the ledger. `verify_dir32_consistency` reads the
`.obj` files, and an `add_match` (or any `build.py --files`) running alongside
rewrites them; the gate then reads a half-written object and the
`final - addend` arithmetic produces garbage. Re-running the check alone
afterwards gives a single base for both symbols and NEW: 0.

Two things follow. Per-file verifies take no lock, which is what makes them
usable while a full gate is queued -- but once the gate is actually *running*,
they corrupt its reading. And a DIR32 failure whose "addresses" do not look like
addresses should be re-checked in isolation before anything is whitelisted or
any row is blamed; the check is a real bug detector (it caught the
AutoPoolClass<HAnimComboDataClass> fold earlier today) and whitelisting noise
would blunt it.

Attribution warning from the same episode: the two outlying sites both landed in
ArchiveFileSystem rows added by peer commits that morning, which made a
tidy-looking story about a TU-scoped STLport shim changing the SEH epilogue.
Both rows verify as exact matches and were never at fault. A plausible culprit
turned up by `git log -S` is not evidence.

## An initialiser list and a body assignment are ordered differently

`MemoryWriteFile`'s constructor zeroes four members and also has an `AsciiString`
member that needs constructing. Retail does it in this order:

    mov [esi+0x14], edx     ; m_data
    mov [esi+0x18], edx     ; m_size
    mov [esi+0x1c], edx     ; m_pos
    mov [esi+0x20], edx     ; m_capacity
    mov [esp+0x14], edx     ; EH state
    mov [esi+0x24], edx     ; m_pendingName's construction

Writing the four as body assignments cannot produce that, and no amount of
reordering the body will. Every member is constructed before the body runs, so
body assignments necessarily land *after* `m_pendingName` is built. Four stores
in the wrong place, and nothing in the body to move.

They have to be initialisers. Members are initialised in declaration order, and
`m_data`..`m_capacity` are declared before `m_pendingName`, so as initialisers
they come first and the shape falls out.

The general form: if a constructor's stores are interleaved with a member's
construction rather than sitting wholly after it, the ones before it are
initialisers. That is a real structural fact about the retail source, readable
straight off the instruction order, and it is one of the few things in a
constructor that the byte comparison can actually tell you.

## Two things that decide what `delete p` compiles to

`Win32BIGFileSystem::closeArchiveFile` came out four bytes short and the wrong
shape in one place. Retail deletes the mapped value like this:

    mov ecx,[esi+0x14]   ; it->second
    test ecx,ecx
    jz  skip
    mov edx,[ecx]
    push 1
    call [edx]           ; deleting destructor, slot 0, delete flag set

and we emitted `mov edx,[edi+0x14]; push edx; call <operator delete>`. Same
source line. The difference is that `ArchiveFile` was only forward-declared, and
`delete` on an incomplete type has nothing to dispatch to, so it degenerates to a
plain `operator delete`. Completing the class *with a virtual destructor* is what
produces the null-check-and-dispatch pair.

So when a `delete` comes out too short, the question is not how the statement is
written — it is whether the compiler can see the type and whether that type's
destructor is virtual. Both are visible in the target: the null check and the
`push 1` before an indirect call are the signature of `delete` on a polymorphic
type, and their absence is the signature of an incomplete one.

The same function also needed exceptions turned OFF. Retail has no SEH frame at
all despite holding an `AsciiString` temporary with a destructor, so the TU was
built without them. `build.py`'s base is already `-EHsc-`; the per-file `// cl:`
line was switching them back on. `/GX-` restores it. Worth checking whenever a
function is the right length but carries an `fs:[0]` prologue the target lacks --
that prologue is not a code difference, it is a flag difference.

## A prose comment starting with `// ?` is read as a symbol annotation

`find_declared_unmatched.py` treats any line whose stripped form starts with
`// ?` as the mangled name of the next definition it sees, and it does not
clear that state until it finds one. A file-header paragraph that happens to
wrap so a line begins with a mangled name -- `// ??0?$StringBase@G@@AAE@...` --
therefore attaches itself to the first function defined dozens of lines later,
which then fails the pre-commit claims gate as an undeclared definition even
though its ledger row is right there.

The symptom is confusing because the reported function is not the one the
comment is about. Reflow the paragraph so no line starts with `// ?`.

This is the same parser state that makes `// <mangled> present-unmatched` work,
and the same reason that marker has to sit immediately above its definition.
## An opaque temporary and a transparent one schedule differently

`Win32BIGFileSystem::init` sat at 109 of 111 bytes for a long stretch. One
instruction pair, twice, in the wrong order:

    retail   push ecx; mov [esp+0xc],esp; mov ecx,esp; push offset "*.big"
    ours     push ecx; mov ecx,esp; mov [esp+0xc],esp; push offset "*.big"

`mov [esp+N],esp` is MSVC recording the temporary's address for the unwind
table. None of the usual levers moved it — explicit temporaries, a declared
rather than inline destructor, access changes, a defaulted argument, and ten
different codegen and exception flags. Nor argument order, which was already
right.

What fixed it was how the temporary's **type** was declared. The shim had

    AsciiString( const char *s );          // declared, never defined

and changing it to a visible delegation

    AsciiString( const char *s ) { ((StringBase<char> *)this)->StringBase<char>::StringBase( s ); }

reordered the pair to retail's. With an undefined extern constructor the
temporary is opaque: the compiler knows only that something happens to it, and
registers it for unwinding after computing the receiver. With the construction
visible it can order the two the other way.

Both spellings are the same program and produce the same call. The lesson is
where to look: when a diff is pure scheduling around a temporary, the lever may
not be at the call site at all but in how completely the temporary's type is
declared. Nothing in the byte diff points there, which is why it is worth
writing down — the same shim is used elsewhere in the tree as a plain extern and
will produce the same two-byte difference in any function that builds one of
these by value.

## `x = y` and `x.set(y)` schedule the destination differently

Two AsciiString setters sat one instruction apart from retail for several
rounds: retail emits `lea ecx,[esi+0x1c]` then `push eax`, and a source
written as `m_x.set(expr)` emits the push first. Nothing about registers or
flags -- the same two instructions, swapped.

The cause is the shape of the call, not the scheduler. Retail's source is
`m_x = expr`, and `operator=` is an inline that forwards to `set`. Inlining
materialises the assignment target before the argument, which is exactly the
order retail shows. Writing `.set()` by hand skips that step and lets the
argument go first.

So when a member-call near-miss differs only in whether the `this` adjustment
precedes the argument push, check whether retail was really calling an inline
wrapper. Reaching for a pointer local (`T *dst = &m_x; dst->set(...)`) can
force the same order, but it is a worse source and it moves the `lea` too
early as soon as the argument is itself a call.

## A nothrow `operator delete[]` declaration removes a spurious EH state

`~NetFileCommandMsg` initialised its EH state variable to 1 and stepped it
down to 0 before destroying its string member, where retail sets 0 once and
never moves. The extra state is the unwind entry MSVC adds for a function
body that can throw while a destructible member is alive -- and the only call
in the body was `delete[] m_data`.

Declaring `void __cdecl operator delete[](void *) throw();` in the TU is what
the real <new> does, and with it the body needs no state of its own. Without
any declaration the compiler assumes the array deallocation can throw.

## A temporary passed by value to an out-of-line function schedules differently

Four of NetPacket's readers sit exactly one instruction pair away from retail
and no closer. Retail writes the temporary's unwind pointer and then loads its
address into ecx:

    push ecx                  ; allocate the temporary
    lea  edx, [esp+0x14]      ; the argument to its constructor
    mov  [esp+0x18], esp      ; record the temporary for unwinding
    mov  ecx, esp             ; this
    push edx

and every source shape tried here emits `mov ecx, esp` before the record. The
difference survives writing the argument as an explicit constructor call, as an
implicit conversion, and via a pointer local.

What separates the readers that DO match is not the temporary -- it is the
call. readFileMessage and readFileAnnounceMessage build the same temporary and
match exactly, because their setter is inline, so there is no by-value argument
crossing a call boundary. The four that miss all hand the string to an
out-of-line setter by value.

So this is not a register-allocation or flag mismatch: it is specific to
materialising a temporary into an outgoing by-value class argument. Worth
revisiting with a matched caller elsewhere in the tree that does the same thing.

## The vptr store sinks unless a member constructor holds it in place

NetPacket's two constructors both start with the vptr store, then zero
`m_dest.ip` and `m_dest.port`, then do their own work. Writing those two zeroes
as ordinary statements makes MSVC sink the vptr store below them and hoist the
inlined `init()`'s stack temporary above everything -- a three-instruction
reordering that no statement order fixes.

Giving the address struct a default constructor puts the vptr first in both,
because member construction is ordered after the vptr and before the body. But
it also makes the struct non-POD, and `m_dest = dest` inside `init()` then
compiles to member-wise assignment (a word store plus the dword pair) where
retail copies the eight bytes as two dwords.

`: m_dest()` is not the answer either -- MSVC 7.1 restructures the whole copy.

So the zeroing reads like member construction and the assignment reads like POD
assignment, and no single declaration produces both. Worth revisiting if a
matched constructor elsewhere in the tree zeroes a POD member and still emits
its vptr first.

## Retail's search loops are bottom-tested; a while/for gets rotated

`Transport::queueSend` scans for a free slot. Retail emits a plain top-tested
body with the bound check at the bottom:

    lea eax, [ebp+0x404]
  L: cmp dword ptr [eax], 0
     je  found
     inc edi
     add eax, 0x40e
     cmp edi, 0x80
     jl  L
     ...return FALSE
  found:

Writing that as `while (...)`, as `for (i = 0; i < N; ++i)` with a `break`, or
as `for (;;)` with an internal `return` all miss -- MSVC rotates the loop,
peeling the first test into a separate `test ecx,ecx` above the loop and making
the value test the back edge. The `for` form additionally unrolls four ways.
Neither `/Os`, `/Ot`, a `volatile` read, a second induction variable nor an
explicit `goto` out of the body prevents it.

`do { ... } while (i < N);` with a `goto` for the early exit produces retail's
shape exactly, because there is nothing left to rotate. Reach for it whenever a
scan loop comes out with a peeled first test.

## Local declaration order picks the register initialisation order

The obfuscation pass next door was one swapped pair away: retail loads the key
constant before the walking pointer, and the source declared the pointer first.
Swapping the two declarations fixed it. Where two locals are initialised from
constants or parameters with no dependency between them, MSVC emits them in
declaration order.

## MSVC lays switch arms out in source order — read the order off the table

`NetPacket::addCommand` is a 29-way switch. Getting the arms to match is not
about the cases themselves, which are one instruction each; it is about their
order in the file. MSVC emits the arm bodies in the order the cases appear in
the source, so writing them in numeric order produces a function of exactly the
right length whose arms are all in the wrong places.

The order is recoverable: sort the jump-table entries by the address they point
at, and the sequence of case values is the source order. For addCommand that is
game command, the three ack stages, the frame command, the per-slot frame
ratios, then the rest -- very nearly the order
ConstructNetCommandMsgFromRawData tests in.

The same table names every handler, so a dispatcher like this can be matched
before any of the functions it dispatches to are owned: pin each arm's target
from the table.

Note the arms encode a thunk one hop further out than `build_call_thunks`
discovers, so pin both the handler body and the address the arm literally
encodes.
## A vtable slot belongs to the class that DECLARES the virtual

`Win32LocalFileSystem::openFile` reached `createDirectory` through `[eax+0x28]`
where retail uses `[eax+0x1c]`, and reordering the derived class's header did
nothing. It could not: `createDirectory` is declared on `LocalFileSystem`, so
its slot number is fixed by the base's layout and the derived class only
supplies the body. Shimming a derived header to fix a slot only works for
virtuals that derived class introduces.

Two things had to change in the base before the offset moved:

  * the declaration order, so the family's own order applies rather than Zero
    Hour's; and
  * the base list itself. The reference `LocalFileSystem` derives from
    `SubsystemInterface`, which contributes six slots and pushes
    `createDirectory` to 11. Standalone it lands at 7, which is retail's. That
    is the same finding already recorded for `ArchiveFileSystem`, so it is worth
    assuming for the rest of the family rather than rediscovering per class.

The same mechanism, one level down, explains a whole-class shift: the reference
`File` derives from `MemoryPoolObject`, which declares a virtual destructor AND
a pure `getObjectMemoryPool`. Two slots, so `File::open` lands at 2 where retail
calls it at `[eax+4]`, and `close`, `read`, `write` and `seek` are each one slot
out behind it. BFME's pooled objects carry only the destructor. A single wrong
base slot count moves every virtual in every derived class.

## Measure the function you think you are measuring

A flag sweep over `Win32LocalFileSystem.cpp` reported that `/G7` took the target
function from 271 differing bytes to 9 -- a spectacular-looking result, and
wrong. The TU had two failing functions, and the tool being swept took the first
`target:`/`compiled:` pair it found in the build output. The 9 belonged to
`doesFileExist`, a 25-byte function that had been matching until `/G7` broke it.
Measured against the function actually under test, `/G7` scores 495, worse than
the 271 it started from.

Retail is not `/G7` in any case, and one byte says so: it emits `inc eax` where
`/G7` emits `add eax,1`, because on Pentium 4 `inc` has a partial-flags stall.
That check costs nothing and would have caught the bad reading immediately.

The tool now requires `--symbol` when more than one function fails rather than
choosing one. Anything that silently picks a subject turns every later
measurement into a measurement of an unknown function, and the numbers still
look perfectly reasonable while it happens.

## A discarded return value turns the last call into a tail jump

`FrameDataManager::addNetCommandMsg` sat one instruction short for a long time:
retail saves esi, calls, restores and returns, where the same body written with
a `void` return compiles to a bare `jmp`. Nothing about the arithmetic differed.

The function returns the `NetCommandRef *` that `FrameData::addCommand` hands
back. With the value returned MSVC cannot tail-jump; with it discarded it can,
and does. The reference declares this one `void`, so the return type is a BFME
change and reading it off the call shape is the only way to see it.

Worth checking whenever a one-call function comes out as a tail jump and retail
has a real call: the missing piece may be a return value the reference throws
away.

## Use the reference's loop form; MSVC's rotation is the thing to reproduce

`readGameMessage` came out wrong when its two loops were hand-written as
guarded `do/while` shapes to mimic the emitted code, and right when they were
written as the reference's plain `for` loops. MSVC rotates a counted `for` whose
index the body never reads into a countdown -- `dec ebx; jne` -- and guards it
with the entry test, which is exactly what retail shows.

That is not in tension with the `queueSend` lesson: there the loop exits early
to a label past the loop, and no `for` or `while` produces that. The rule is to
write the loop the way the source plausibly had it and only reach for a
hand-rotated shape when the control flow genuinely is not a counted loop.

## A short claim can match the TAIL of a real function

`?stringLength@@YAHPBD@Z` is claimed at 0x000A30D4, 13 bytes, from
string_base.cpp, and it verifies exactly. `locate.py` nevertheless keeps placing
`?length@?$char_traits@D@_STL@@SAIPBD@Z` at 0x000A30D0, 17 bytes, and the two
overlap, which makes the full gate refuse to patch.

The bytes settle where the function starts:

```
000A30C8  cc cc cc cc cc cc cc cc      <- padding
000A30D0  8b 44 24 04    mov eax, [esp + 4]
000A30D4  8d 50 01       lea edx, [eax + 1]     <- the 13-byte claim starts HERE
000A30D7  8a 08          mov cl, [eax]
...
000A30E0  c3             ret
000A30E1  cc cc ...                              <- padding
```

Padding either side puts one function at 0x000A30D0 spanning 17 bytes. The
13-byte claim begins four bytes inside it, after the argument load -- and
`?stringLength@@YAHPBD@Z` demangles to `int __cdecl stringLength(char const *)`,
which cannot have a complete body that never touches the stack. It is `static` in
string_base.cpp, so MSVC is free to pass the pointer in a register, and that
13-byte register-convention body happens to equal the tail of the real function.

So an exact byte match at a given RVA is not by itself proof the claim is right:
the range has to start where the function starts. Two rows verifying and
overlapping means one of them is anchored inside the other.

Not changed here -- string_base.cpp owns 165 other rows so nothing is at risk
either way, and it is not mine to retire on inference alone. Whoever owns that
file should decide; the evidence is above. Until then `locate --emit` over any
file using char_traits<char> will keep re-adding the 0x000A30D0 row, and it has
to be dropped again each time.
## A shim on the include path loses to a sibling of the file that includes it

`reference/shims/bfme_mempool/Common/GameMemory.h` corrects one thing:
`MemoryPoolObject` contributes ONE vtable slot in BFME, not the two the
reference gives it (a virtual destructor AND a pure `getObjectMemoryPool`). That
second slot pushes every virtual in every pooled class down by one, so
`File::close` sits at slot 3 and every call through it is wrong — retail reaches
it at `[eax+8]`.

Putting that shim first on the include path fixed `Win32LocalFileSystem.cpp` and
did nothing at all for `ArchiveFile.cpp`. The difference is which file asks for
the header. `Win32LocalFileSystem.cpp` includes `"Common/GameMemory.h"` itself
from a directory with no such sibling, so the `-I` order decides and the shim
wins. `ArchiveFile.cpp` includes `"PreRTS.h"`, which lives in
`reference/shims/sweep/` and asks for `"Common/GameMemory.h"` — and MSVC
resolves a quoted include against the **including file's own directory first**,
which is `reference/shims/sweep/`, where `Common/GameMemory.h` exists. No `-I`
ordering can beat that, because `-I` is never consulted.

The fix is to get there first and let the guard do the work: include
`"Common/GameMemory.h"` in the .cpp BEFORE `"PreRTS.h"`, so `_GAME_MEMORY_H_` is
already defined when sweep's copy is reached. Pulling it in via a wrapper header
does not work — `PreRTS.h` sets up `__PLACEMENT_VEC_NEW_INLINE`, the CRT and
several engine headers before it includes `GameMemory.h`, and that header needs
them.

Two things follow. A shim that appears to be ignored is worth checking for a
sibling before assuming the `-I` order is wrong. And this one is worth trying
wherever a call lands exactly one slot late on a pooled class — it is a
tree-wide fact, not something about these two files.
## Recognise MSVC's inlined CRT intrinsics before hand-writing the loop

A 62-byte strdup resisted a dozen source shapes -- do/while, postfix increment
in the condition, an explicit counter, the length written as distance-to-NUL
plus one -- and every one of them came out a couple of instructions off. The
body is not open-coded at all: it is MSVC's intrinsic `strlen` and `strcpy`
expanded inline, and writing `malloc(strlen(str) + 1)` then `strcpy` matched on
the first try.

The tell for inline `strlen` is the shape:

    mov eax, str
    lea edx, [eax + 1]
  L: mov cl, byte ptr [eax]
     inc eax
     test cl, cl
     jne L
    sub eax, edx

The `lea` of `str + 1` before the loop and the `sub` against it afterwards are
not something a hand-written loop produces -- the compiler folds that to a
single subtraction. Inline `strcpy` is similarly recognisable: it walks the
source pointer and indexes the destination through a precomputed delta rather
than advancing two pointers.

When a byte loop is a couple of instructions off and no source shape moves it,
check whether the original called a CRT function and let the compiler expand it.

## The texture impl class is a BFME invention, not a modified Zero Hour one

The handle/impl entry above establishes that BFME's texture objects hold a
pointer at +0 to a separate 0x48-byte implementation object. This is the part
that decides how to approach the subsystem: that object has no Zero Hour
counterpart at all.

The evidence is a string. The cluster around the impl allocation references

```
0090D112  'dyntex_%08x'
0090E210  "Texture '"
0090EBC8  '.tga'   0090EBF0  '.dds'   0090EC42  '.jpg'
```

and `dyntex_%08x` appears nowhere in `reference/CnC_Generals_Zero_Hour` or in
`Code/`. It is a format for naming a dynamically created texture, and Zero Hour
has no such naming anywhere in WW3D2.

So the texture layer is not a port with drift. There is a class in retail that
was never in the Westwood source, the ported classes hand their state to it, and
every ported body reaches its members one indirection further than ours does.
`locate.py` placing 0 of 152 across all six texture sources is the expected
result, not a puzzle.

What that means for anyone picking this up: do not keep adjusting the Zero Hour
bodies. Reconstruct the impl class first -- its size is 0x48, its constructor
zeroes +4 through +0x20 and +0x34/+0x38 at 0x0090D211, it carries a vtable, the
D3D texture sits at +0x38, and three sibling vtables at VA 0x0113A668, 0x0113A6B0
and 0x0113A6F8 share slots 0, 4, 5, 6, 7, 8, 10, 11 with slot 0 a plain getter
rather than a destructor. The handle classes only make sense once it does.
2026-08-03: tools/land_ambiguous.py currently requires reverse/ghidra_functions.csv, which is absent in this checkout; regenerate that inventory before using the ambiguous-copy pass.
* BFME W3DModelDraw keeps ONE weapon-recoil vector where ZH has WEAPONSLOT_COUNT (3): each WeaponRecoilInfoVec is 12B and retail puts m_renderObject at this+0x28 vs our +0x40 - exactly two vectors. But the bytes come straight back: an already-matched row in the same TU reads a field at +0x58 that retail agrees with UNSHIFTED, so reference/shims/w3dmodeldraw pairs the [1] array with a 0x18 pad right after m_renderObject and all 130 rows survive. Same insert/remove shape as GlobalData - when a class-size hypothesis breaks exactly one matched row, look for the compensating pad before abandoning it. Probe trick for exact member offsets: a scratch TU with '#define private public' and an extern "C" unsigned[] of offsetof(...) values, then read the array out of the .obj (symbol gets a leading underscore: __bfme_probe); note a MINIMAL probe can disagree with the real TU (bases differed by 0x10 here) so build the probe with the TU's own cl line and headers.
* BFME WeaponTemplate is 0x53C bytes, not the 0x1D4 the ZH header adds up to (WeaponStore::newWeaponTemplate @0x1E7F50 passes 0x53C to operator new). A class whose only proven fact is its SIZE takes a tail pad, not a mid-class one: parked after the last member it changes sizeof alone and every existing member offset survives (45/45 rows in Weapon.cpp held). Also: BFME's Debug is polymorphic where ZH's has no virtuals at all - DebugIOCon::Execute @0x891200, DebugIONet::Execute @0x890810 and ExecCommand @0x88ABA0 all call operator<<(const char*) through slot 0x38, so ~1300B waits on triangulating that vtable; inventing 14 dummy virtuals is not viable because the vptr at offset 0 would shift every Debug member.
* BFME Display has THREE more virtuals ahead of getWidth than ZH: ControlBarResizer::sizeWindowsAlt @0x4AB1A0 calls getWidth via slot 0x2C and getHeight via 0x30 where we emit 0x20/0x24, and the pair stays one slot apart in both. reference/shims/display now carries the stubs - and note it must be based on reference/shims/sweep/GameClient/Display.h, NOT the raw reference header: the latter still has the DebugDisplayCallback default argument that vendored RTM cl rejects with C2383 (lesson above), so a fresh copy fails to compile. Display.cpp's setDisplayMode is NOT unlocked by this - it diverges structurally (220B) with extra TheTacticalView vtable calls.
* BFME puts ControlBar's six toggle-button images at this+0x2A0..0x2B4 (setUpDownImages @0x49D160), a uniform -0x40 from the ZH header's +0x2E0. Fixing it needs no pad at all: MOVING the six declarations up so they start where m_animateDownWin2Pos did displaces exactly 0x18 bytes downward into the space the block vacated, so everything from m_transitionHandler onward keeps its offset and all 43 rows in ControlBar.cpp survive. Prefer a move over a pad when the drift is a relocation rather than a size change - and note reference/shims/controlbar is a PARTIAL reconstruction of the class (interior replaced by blobs, ends at +0xFC) that ControlBar.cpp does not use; the new controlbarlayout shim is the full ZH header with one block moved.
* add_match writes the source path VERBATIM into the ledger, and on Windows a wrong-case path still opens fine - so passing NAT.cpp when git tracks nat.cpp lands a row that check_csv rejects at commit time with "source not in git". Confirm the spelling with `git ls-files` before add_match, not with ls.
* GameWindowManager.cpp CANNOT take reference/shims/gamewindow even though that shim already pins the field its dtor needs (GameWindow::m_next @0x1F8, where the unshimmed header gives 0x1E8): opting the TU in breaks 7 of its 112 matched rows outright. So either the shim's GameWindow reconstruction and those 7 rows disagree about the class, or some of the 7 are false matches - resolve that before touching this TU. Separately, CaveSystem::registerNewCave @0x378970 proves only sizeof(TunnelTracker)=0x20 vs our 0x24; the TU merely allocates it, so ANY 4-byte removal would verify and picking one (dropping the Snapshot base? a member?) would be a guess, not a finding.
* A `rep movsd` count IS a struct size pin: GameSpyBuddyMessageQueue::getRequest @0x63C770 moves 0xAE dwords where we emit 0x82, and getResponse @0x63C840 moves 0x219 vs 0xB6 - so BFME's BuddyRequest is 0x2B8 (ours 0x208) and BuddyResponse 0x864 (ours 0x2D8). Tail pads in reference/shims/buddythread fixed FOUR bodies at once (get/add x request/response, 704B) because add* copy the same structs. Scan for lone `mov ecx,<imm>` diffs before assuming a class-layout problem - a size-only pin with a tail pad is the cheapest fix there is.
* The GameWindowManager/gamewindow-shim conflict is RESOLVED, and the shim was the wrong half: BFME moves GameWindow's sibling-list pointers 0x10 later (m_next at +0x1F8, ours +0x1E8) but everything EARLIER is already correct - seven matched accessors in GameWindowManager.cpp pin m_instData.m_tooltipDelay at +0x1C4 and the win*Color array at +0x48. reference/shims/gamewindow spreads the same 0x10 as a BFME-only pointer at +0x04 plus three later fields, which shifts both pins and breaks all seven; its +0x04 field can only coexist with them if something before +0x48 is 4 bytes SMALLER in BFME, which nothing proves yet. New reference/shims/gamewindowlist puts the whole 0x10 immediately before the pointers and landed the dtor + linkWindow with all 112 rows intact. winDestroy still needs more: retail writes a field at [edi+8] where we emit [edi+4], and makes a VIRTUAL call where we emit a direct one.
* BFME's Render2DSentenceClass is 0xC bytes bigger than ZH's: W3DDisplayString embeds TWO of them, and its dtor @0x6F4C50 takes m_textRendererHotKey's address at [esi+0xE0] (ours 0xD4) and m_hotkey's at [esi+0x1B0] (ours 0x198) - +0xC then +0x18 cumulative, exactly one renderer's growth each. A third pin, +0x1C more before m_size (computeExtents @0x6F5420 writes it at +0x1F0), completes reference/shims/w3ddisplaystring. CONFLICT to resolve: computeExtents ALSO needs reference/shims/displaystring's claim that DisplayString has only one base virtual (its two vtable calls are one slot early), but adding that shim regresses the dtor from 0 to 19 diffs - the two cannot both be right, and the dtor is the one backed by field pins, so it is what landed.
* Two size-only pins in PeerDefs, and they NEST: GameSpyStagingRoom is 0xA8 bigger in BFME (removeStagingRoom @0x632A50 takes one by value and pops 0x468 where we emit ret 0x3C0) and GameSpyInfo is 0x700 vs our 0x624 (createNewGameSpyInfoInterface @0x637760 passes it to operator new) - but GameSpyInfo EMBEDS a staging room, so its own pad is 0x700-0x624-0xA8 = 0x34, not 0xDC. Adding both naively overshot to 0x7A8; when two tail pads land in classes that contain one another, subtract the inner growth from the outer pin.
* A by-value parameter read tells you WHICH field moved, not just that the class grew: work back through the prologue (push/sub esp AND the pushed registers) to get the parameter base, then subtract. Getting the base wrong by 0xC made me pad in front of m_requiresPassword when the pinned field was actually m_id. Then setExeCRC/setIniCRC - matched rows in the same TU keeping ZH offsets 0x398/0x39C right AFTER m_id - proved BFME RELOCATES m_id to +0x41C rather than shifting the block: the fix is a hole where it was plus a re-declaration in the appended region, not a pad. Also: adding a NEW header to a shim dir does not invalidate build.py's deps sidecar (it recorded the old resolution), so delete the .obj and .deps.json or the next build silently reuses the stale object.
* The GameWindow +0x04 field IS real - winDestroy @0x47CE30 reads and writes m_status at [win+8] where the ZH header gives +4 - but it is paid back before m_instData, since the seven matched win*Color accessors still index from +0x48 and setTooltipDelay still writes +0x1C4. So reference/shims/gamewindowlist declares the anchor and relocates ONE 4-byte member (m_userData, chosen only because nothing pins it) to the class tail. That reconciles the conflict logged earlier against reference/shims/gamewindow: its +0x04 field was right, its later placement of the remaining 0xC was not. Gotcha while doing it: relocating a member to 'the tail' means AFTER m_next/m_prev too - dropping it just past the sibling-list pad silently pushed those pointers 4 bytes and broke the two rows already landed.
* reference/shims/display's three stubs are NOT a clean prefix insertion into Display's vtable. They land sizeWindowsAlt (getWidth 0x20->0x2C, getHeight 0x24->0x30) but adding the same shim to ControlBar.cpp regresses setSquishedControlBarConfig from 2 diffs to 19: that body calls getHeight at the SAME +0xC shift yet its other Display calls do not move at all. So BFME both adds and removes slots inside Display, exactly like GameWindow and DisplayString - do not widen the display shim to another TU without first pinning the methods that stay put. Remaining ControlBar work also needs the m_specialPowerShortcut* block relocated (buttons 0xF8->0xCC with 10 elements not 11, currentlyUsed 0x17C->0xF4, parent 0x184->0xFC; the same offsets reference/shims/controlbar already documents) - a multi-member reshuffle inside a header whose 44 rows are matched, not a pad.
* BuildListInfo::duplicate @0x1944D0 gives two solid pins - sizeof is 0x8C (we emit push 0x90) and m_nextBuildList is read at +0x2C (ours 0x30) - and the offsets it DOES agree on (0x10/0x14 in m_location, 0x1C/0x20 in m_rallyPointOffset) prove everything up to 0x24 is unchanged. So exactly one 4-byte member between +0x24 and +0x30 is absent in BFME, but WHICH is unknowable from this body: dropping m_angle, m_isInitiallyBuilt or m_numRebuilds all satisfy both pins, so it stays unlanded rather than guessed 1-in-3. Worse, the ledger's three 10-byte BuildListInfo setters (setNumRebuilds@0x2C, setNextBuildList@0x30, setHealth@0x38) CONTRADICT duplicate - they encode our unshifted layout and are exactly the generic 'mov eax,[esp+4]; mov [ecx+N],eax; ret 4' shape that ICF-folds across classes, so treat them as suspect the way friend_setNext@UpgradeTemplate already is.
* BFME's AsciiString::isEmpty() tests the header's 16-bit LENGTH, not the first character: ModuleFactory::findModuleInterfaceMask @0x129100 emits `cmp word ptr [eax+4], 0` where the ZH body reads peek()[0] as a byte. Fixing it in reference/shims/asciistring8 landed newModule outright and is a second independent confirmation of the WWLib StringBase header (int ref_count @0, ushort len @4). findModuleInterfaceMask still needs one more thing and it is NOT a ModuleTemplate pad: it returns m_whichInterfaces from [tmpl+0xC] where ours gives +8, but padding ModuleTemplate breaks four matched ctor bodies that write the field at +8 - so either the object it dereferences is not a ModuleTemplate, or those ctors are wrong.
* BFME TerrainLogic has ONE more virtual ahead of getLayerHeight than ZH: Pathfinder::adjustCoordToCell @0x3D6040 calls it through slot 0x1C where the header gives 0x18. One stub in reference/shims/terrainlogic lands it with all 30 AIPathfind.cpp rows intact. Scanning tip that found it: grep the retail bytes of every candidate for the isEmpty signature `66 83 78 04 00` (cmp word [eax+4],0) - it groups the AsciiString-shaped bodies - but check the COMDAT length first, since a 60-byte retail body whose source compiles to a single `ret` (ThingTemplate::validateAudio) reports a fake 1-diff.
* BFME Radar carries 0x108 more bytes ahead of m_radarWindow than ZH (screenPixelToWorld @0x107C50 reads it at this+0x1438, ours +0x1330). One pad in reference/shims/radar landed that body AND findDrawPositions @0x106FC0 (302B) which dropped straight to zero diffs - after any single-field pad, re-scan the whole TU before moving on, since one offset often gates several bodies.
* Object is RELOCATED, not grown, and padding it is provably wrong. Three retail pins say fields move a long way - m_disabledMask 0x130->0x1A4 (doSpecialPowerUsingWaypoints @0x1C3850), m_triggerInfo 0x240->0x2D8 and m_numTriggerAreasActive 0x298->0x346 (isInside @0x1BEA90) - but six ALREADY-MATCHED accessors in Object.cpp pin fields that sit BETWEEN them and do not move at all: getBodyModule reads +0x194 and hasAnyWeapon +0x20C, both unshifted. So m_disabledMask cannot simply shift past +0x194; BFME reorders Object rather than inserting runs, the same shape as GameSpyStagingRoom::m_id. Padding in front of each pinned field breaks exactly those six rows - do not retry that. Probe note: Object.cpp compiles against reference/shims/sweep/GameLogic/Object.h, NOT the reference header, and one member there (m_hasDiedAlready) is behind an #ifdef, so an offsetof probe must be built from the sweep copy and must drop names the compiler rejects.
* A by-value parameter's teardown tells you whether the class has a REAL destructor: GameInfo::setSlot @0x61F630 ends with one call on the parameter's base, while our build inlined the member teardown and called UnicodeString::releaseBuffer at +0x28 instead. Declaring ~GameSlot() in reference/shims/gameinfo (no definition needed - build.py only compiles, and the ledger pin resolves the call) collapsed that to a single ??1GameSlot call and finished the body. Its other pin was the plain size one: GameSlot is 0x44 bytes, from `ret 0x48` vs our 0x44. Watch for this shape whenever the only leftover diff is an lea of a stack address near the epilogue.
* The W3DDisplayString shim conflict is RESOLVED and reference/shims/displaystring was right after all: DisplayString really does drop one base virtual (computeExtents' two vtable calls sit one slot early), it just also needs its DESTRUCTOR out-of-line. With the shim's inline `virtual ~DisplayString() { }` the compiler inlines the base teardown (lea ecx,[esi+4]; mov [esi],0) where retail CALLS the dtor thunk @0xD823 - the same GameSlot shape. w3ddisplaystring now carries a local copy declaring it, which lands computeExtents AND keeps the dtor at zero diffs. Note the mangling flips with access level: declaring it public gives ??1DisplayString@@UAE@XZ where the protected reference form is @@MAE@XZ, so both spellings need pinning to the same thunk.
* FontCharsClass in BFME is BOTH shorter at the front and roomier in the middle: Grow_Unicode_Array @0x93D320 reads UnicodeCharArray at +0x44C and FirstUnicodeChar at +0x45C where ours gave +0x45C/+0x460, which pins 0x10 removed before ASCIICharArray and only 0xC re-inserted after the pointer - a net -4. Moving four GDI handles past UnicodeCharArray gets the pointer right but leaves the uint16 pair 4 late; the fix is three moved there plus a fourth (GDIFont) parked at the class tail. Note render2dsentence.h lives in Code/, not reference/, so this is a direct header edit and a full-gate commit - no shim dir involved.
* Object IS reconstructable - the earlier 'padding breaks six accessors' finding was right about the method, not the class. Harvesting BOTH directions settles it: rows that already byte-match pin +0x124, +0x12C, +0x18C, +0x190, +0x194, +0x1A0, +0x1A8, +0x1F0 and +0x23C UNCHANGED, so BFME agrees with the ZH header nearly everywhere, and only three fields relocate - m_disabledMask +0x130->+0x1A4 (trading places with m_partitionData, both 4 bytes), m_triggerInfo +0x240->+0x2D8 and m_numTriggerAreasActive +0x298->+0x346, the latter two into a block BFME appends past the 0x29C end. reference/shims/bfmeobjectlayout encodes exactly that and keeps all 106 pre-existing rows green. GENERAL METHOD: for a class where naive padding fails, harvest the CONFIRMED offsets (from matched rows) before the moved ones - the confirmed set is what tells you it is a reorder, and it bounds where the moved fields may go.
* InGameUI pins harvested the same way as Object, but this one does NOT pay off yet: findSWInfo @0x449E70 indexes m_superweapons from +0x5CC where our header puts the array at +0x17F0, while matched rows in the TU pin +0xC8, +0xDC, +0x568, +0x570 and +0x7A1 unchanged. The destination is boxed in by confirmed offsets on both sides (+0x570 below, +0x7A1 above), so relocating the array there would displace fields that are proven stationary - it needs more pins before it can be encoded, and only one 75-byte body depends on it. Also note the Object shim does NOT generalise: of every candidate outside Object.cpp only getReadyFrame@SpecialPowerModule touches a known Object relocation, and it still has 6 other diffs, so opting other TUs in buys nothing.
* BFME ScriptEngine is 0x6868 bytes bigger ahead of m_freezeByScript, and TWO independent pins agree: m_freezeByScript ours +0x10DBC -> retail +0x17624 (the existing reference/shims/scriptengine stand-in) and m_objectsShouldReceiveDifficultyBonus ours +0x10DCC -> +0x17634 (doEnableOrDisableObjectDifficultyBonuses @0x2F0840). The old shim is a minimal stand-in CLASS, usable only by TUs that touch nothing else; reference/shims/scriptenginelayout is the real header with one pad and works for full TUs - all 56 rows in ScriptActions.cpp stay green. Note the old shim's comment says the delta is 27240 bytes, which is 0x6A68 and wrong by 0x200; the measured value is 0x6868.
* BFME declares EstablishConnectionsMenu's five public methods virtual where ZH has them as plain calls: NAT::setConnectionState @0x670DC0 reaches setPlayerStatus through slot 0x14 on TheEstablishConnectionsMenu's vtable. With the destructor already at slot 0, marking initMenu/endMenu/abortGame/setPlayerName/setPlayerStatus virtual IN THEIR EXISTING ORDER puts setPlayerStatus at index 5 with no stubs invented - when a whole small class turns out to be polymorphic in BFME, try promoting its declared methods before padding the vtable with placeholders.
* ModuleFactory::findModuleInterfaceMask @0x129100 is one byte from matching: retail reads the interface mask at ModuleTemplate+0xC where our 12-byte template puts it at +8. Do NOT widen ModuleTemplate - the already-matched newModule @0x127E00 calls (*m_createProc)() straight off the same node+0x14 base, pinning m_createProc at template+0, and the matched pair<NameKeyType,ModuleTemplate> copy ctors move exactly three dwords, pinning sizeof at 12. Widening the template fixes this one row and breaks four. Either retail reads a member we cannot see from a 12-byte layout or one of those four rows is an ICF mis-attribution; left unresolved.
* BFME does not stack MemoryPoolObject and Snapshot the way ZH does: retail TunnelTracker has ONE vptr (dtor @0xF8A40 touches only [this+0]), is still handed straight to Xfer::xferSnapshot, and still answers deleteInstance - so the two ZH bases are one merged base there. Its vtable @0x1085FD8 is dtor / loadPostProcess @0xF8F60 / a pool-name accessor @0xF8A30 / xfer @0xF8E20, four slots against the shared base table @0x1073744 of dtor plus three _purecall. Every member drops one dword versus ZH (xfer @0xF8E20 walks +4,+8,+0xC,+0x10,+0x14,+0x18,+0x1C in declaration order), making sizeof 0x20 - the operator new argument in CaveSystem::registerNewCave. A TU shim cannot express this by editing GameMemory.h: PreRTS.h pulls the reference copy first via MSVC's includer-relative quote search and the guard then blocks the shim, so derive the class from Snapshot alone and declare deleteInstance on it.
* LANAPI needs a whole-class reconstruction before its 34 markers can land, and RequestLobbyLeave @0x6850F0 measures all three axes at once: sizeof(LANMessage) is 0x1DC not 0x1D8, fillInLANMessage sits at vtable +0xC4 not +0xAC (six extra virtuals ahead of it), and m_transport is at +0x4C not +0x44. The already-matched rows pin the front of the class - LookupGameByListOffset reads m_games at +0xC and ResetGameStartTimer writes the start-timer pair at +0x1C/+0x20 - so the eight extra bytes appear between m_gameStartSeconds and m_transport. Only 8 of the 34 markers have ledger rows, so there is not enough matched code in the TU to place them; do LANAPI as a deliberate class job, not as a near-miss chase.
* BFME's View carries two more virtuals ahead of setHeight (slot +0x40, not +0x38) on top of the three Display already has ahead of getWidth, and ControlBar::setSquishedControlBarConfig @0x49D0B0 needs both at once - reuse the Display half of reference/shims/display but pair it with a REAL View.h, not that shim's synthetic slot skeleton, which has no usable API for a second TU. Separately: retail reaches ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate through the incremental-link thunk at 0x378EE, which jumps to 0x4ADE40 - an RVA nothing in the ledger claims - while functions.csv puts that same mangled name at 0x3865B0 from a string-anchor guess. The thunk is pinned in symbols.csv; the 0x3865B0 body claim is probably a misattribution and wants re-checking.
* ControlBar's special-power shortcut block is far smaller in BFME: animateSpecialPowerShortcut @0x49D3F0 puts m_specialPowerShortcutButtons at +0xCC and m_currentlyUsedSpecialPowersButtons at +0xF4, a 0x28-byte gap where the ZH header's three MAX_SPECIAL_POWER_SHORTCUTS arrays need 132 - ten dwords, not thirty-three - and the whole block also starts 0x2C lower than ours, so something ahead of it shrank too. m_specialPowerShortcutParent keeps its one-member gap after the counter (+0xFC vs our +0x184), and the animate-window-manager virtual it calls is one slot further along (+0x10 vs +0xC). Two independent shrinks over a class with 45 matched rows: treat ControlBar's tail as a deliberate reconstruction, not a near-miss fix.
* A lone JA-where-we-emit-JG is a type fact, not a layout fact: DisconnectManager::sendKeepAlive @0x66B2D0 matched byte for byte once the local holding timeGetTime() became UnsignedInt instead of ZH's time_t, because the usual arithmetic conversions then make (curTime - m_lastKeepAliveSendTime) > 500 an unsigned test. Check the signedness of the locals before reaching for a shim whenever the only difference is the condition code of one branch.
* The BFME slot 6-8 stub trio that sweep's GameWindowManager.h documents is not confined to the window family: DisplayStringManager has it too, which is the whole reason CreditsLine::~CreditsLine @0x40C230 calls freeDisplayString through vtable +0x28 instead of +0x1C. When a SubsystemInterface-derived class's vtable pin is exactly three slots late, try declaring the three stubs right after its destructor before assuming anything about the derived class itself - and keep doing it per class, since sweep's SubsystemInterface.h records that the base does NOT carry them.
* When only the operator new size is wrong, read the retail constructor rather than padding the tail blind: GameSpyPeerMessageQueue asks for 0x78 bytes where ours is 0x6C, and its ctor @0x64D650 shows exactly what the extra 12 are - MutexClass's ctor runs a THIRD time on this+0x6C (the same one used for the mutexes at +4 and +0xC) and then a dword at this+0x74 is zeroed. The five matched rows in PeerThread.cpp confirm +0x14, +0x24, +0x3C, +0x64 and +0x68, so the two new members can only sit at the tail. Also: BFME's WW3D::End_Render @0x8FD880 returns via mov al,1 on both paths, i.e. a one-byte true, not the four-byte WW3D_ERROR_OK our signature returns - the WW3D error enum may be a bool in BFME, which would rename the symbol, so it is left alone.
* AIUpdateInterface's turret block is 0x18 further along in BFME: m_turretAI is at +0x1E8, not +0x1D0. The matched rows bracket it - ignoreObstacleID pins m_ignoreObstacleID at +0x154 and the hand-rolled struct in setLocomotorUpgrade pins m_curLocomotorSet at +0x1D0 - which splits the 0x18 into 0x14 unaccounted bytes ahead of the locomotor block (most likely LocomotorSet being 0x2C rather than 0x18) and 4 more between m_locomotorGoalData and m_turretAI. Holding both as holes inside AIUpdateInterface rather than resizing LocomotorSet keeps that type unchanged for its other users in the TU, and lands getWhichTurretForCurWeapon and isWeaponSlotOnTurretAndAimingAtTarget together.
* StreakLineClass::Set_Widths @0x91A380 wants PointWidths - the DynamicVectorClass whose vptr/Vector/VectorMax/ActiveCount it walks - at +0xF4, while our layout puts it at +0xC0. That cannot simply be shifted: the matched Set_Merge_Abort_Factor row writes a float to [ecx+0xF4], and a one-instruction setter of that shape is exactly the ICF-folded evidence lessons.md already warns about. One of the two is wrong and the setter is the likelier suspect, so this is left alone until StreakLineClass gets a proper reconstruction.
* BFME's KindOf enum has two more entries than ZH's, and they sit between KINDOF_VEHICLE and KINDOF_AIRCRAFT: TunnelTracker::updateNemesis @0xF90D0 passes 7, 8 and 9 for STRUCTURE, INFANTRY and VEHICLE - the same numbers this header gives them - and then 12 for AIRCRAFT. Anything from KINDOF_AIRCRAFT onward is therefore two higher than the ZH header says, which is worth checking before blaming a layout whenever a lone isKindOf argument is off by a small constant.
* The merged pooled-snapshot base generalises: TurretAI, declared in ZH as MemoryPoolObject + Snapshot + NotifyWeaponFiredInterface, carries one vptr fewer in BFME exactly like TunnelTracker, which is why getWhichTurretForWeaponSlot @0x26EBB0 reads m_angle at +0x18 and m_pitch at +0x1C instead of +0x1C and +0x20. Same shim recipe both times: derive from Snapshot alone, keep the other non-pooled bases, and declare deleteInstance on the class. Expect any ZH class inheriting both MemoryPoolObject and Snapshot to be four bytes smaller in BFME with all its members shifted down a dword.
* Two separate layout jobs are now blocked by the same shape of bad evidence, one-instruction setters that ICF folds. ParticleSystem::getPosition @0x5BDDB0 puts m_localTransform at +0xC0 against our +0x274, and attachToDrawable's hand-rolled offset already pins m_attachedToDrawableID at +0xB4 - together they say BFME's ParticleSystemInfo base is about 0x1C0 bytes smaller. But the matched setControlParticle row insists m_controlParticle stays at +0x330, which a shrink of that size cannot leave alone; that row is mov [ecx+0x330],eax / ret 4, the same folding-prone shape as StreakLineClass's Set_Merge_Abort_Factor. Before starting either class, re-derive those two setter claims from a caller rather than trusting the ledger row.
* WinInstanceData::setText @0x499D60 comes down to six bytes once both display shims are applied together - displaystringmanager fixes newDisplayString at vtable +0x24 and displaystring fixes DisplayString::setText at +4 - and what is left is pure scheduling: retail emits mov [esp+8],esp before mov ecx,esp when constructing the by-value UnicodeString temporary, we emit them the other way round. Same instructions, same registers, same semantics. Nothing in the source expression appears to steer that order, so the pair is worth revisiting only if the compiler flags change; the two shims themselves are proven to compose.
* BFME's RenderObjClass has one more virtual than ZH's and it is the LAST slot, not an interior one: AABoxRenderObjClass @0x957880 and OBBoxRenderObjClass @0x957C20 reach BoxRenderObjClass's own first virtual, update_cached_box, through +0x20C where our header lands it at +0x208. Adding the slot in front of Set_Position instead broke 66 matched rows across WW3D2 and the draw modules, because everything from there down shifted - the extra slot only fits after every RenderObjClass virtual that existing rows already pin. Note the constructors call Set_Position directly and only update_cached_box through the vtable, so the pin is on the derived class's first own slot, not on Set_Position.
* One C++ function can sit in the ledger twice under two spellings of the same parameter type, and the wrong copy can be the one a symbols.csv pin points at. Matrix3D::Set(const Matrix3&, const Vector3&) is an 82-byte body at 0x8D6710, but the Matrix3x3 spelling that our TUs actually emit was pinned to 0x964150 - a 274-byte RVA shared with setEaseTimes@ParabolicEase, i.e. an ICF group that cannot be an 82-byte function. OBBoxRenderObjClass's constructor @0x957C20 calls 0x8D6710, and repointing the pin there kept the entire full gate green, so nothing else depended on the old target.
* BFME's WW3D entry points return bool, not ZH's four-byte WW3DErrorType, and two functions now say so independently: End_Render @0x8FD880 returns via mov al,1 on both paths, and Set_Render_Device @0x8FD120 ends test al,al / setne al / ret where we emit the neg/sbb/and/add sequence that turns the callee's bool into 0-or-5. Both are one-byte returns. Fixing it is not a shim job - it changes the mangled names, so every affected ledger row would have to be renamed, and add_match only replaces a row under its existing name while hand-editing functions.csv is what the tooling exists to prevent. Worth doing as a deliberate pass over the whole WW3D surface, with tooling for the rename, rather than one function at a time.
* The retail ParticleSystem layout is now pinned end to end, and it proves the setControlParticle ledger row wrong. Four neighbours of getPosition read it out: setLocalTransform @0x5BDE40 copies a full 48-byte Matrix3D into +0xC0..+0xEC, setPosition @0x5BDE00 writes only that matrix's translation column at +0xCC/+0xDC/+0xEC, and both then clear a byte at +0x1A4 - m_isLocalIdentity, the first of ZH's eight trailing Bools - while the stop/start pair @0x5BDD90 and @0x5BDDA0 write +0x1A7, which is m_isStopped, the fourth of them. That puts m_template at +0x19C, m_controlParticle at +0x1A0 and sizeof around 0x1AC, so the matched setControlParticle row claiming +0x330 cannot be this class at all - it is the ICF fold that lessons.md already suspected. Everything from m_localTransform down keeps ZH's order and spacing; only the ParticleSystemInfo base ahead of it is smaller, ending near +0xA0 given attachToDrawable's confirmed m_attachedToDrawableID at +0xB4.
* And the real body is findable: scanning .text for the exact setter MSVC would emit at the predicted offset - 8b 44 24 04 / 89 81 a0 01 00 00 / c2 04 00 - gives exactly one hit, 0x5BE2E0, unclaimed by any ledger row and sitting a few hundred bytes from getPosition @0x5BDDB0 in the same ParticleSystem cluster. That is where setControlParticle really lives. It cannot be repointed yet, because our header still puts m_controlParticle at +0x330 and the row would not verify until the ParticleSystemInfo base is reconstructed - but the address is settled, and the same trick (predict the offset from neighbours, then grep .text for the setter's exact encoding) is the way to re-derive any of the other ICF-suspect setter rows.
* LightEnvironmentClass looked like a clean one-dword insert and is not. Pre_Render_Update @0x94BB40 reads every member exactly four bytes later than ours - LightCount at +4, the loop base at +0x14, the fill-light floats at +0x164/+0x168/+0x16C - but adding a leading dword breaks six matched rows, among them getPointOrad @0x903370, whose imul 0x54 / fld [eax+ecx+0x48] pins InputLights at +0x10 exactly where we already have it. Both cannot hold with a single insert: something ahead of LightCount grows by 4, something between LightCount and InputLights shrinks by 4, and the tail grows again. Get_Light_Count @0x10BDB0 is no help either - three bytes of mov eax,[ecx] / ret is the most foldable shape in the binary. Needs the whole class done at once.
* GameSpyInfo is blocked by a bad ICF group, not by a layout puzzle, and the exact addresses are now known. An offsetof probe on the shimmed class gives our layout precisely (m_localName +0x64, m_localProfileID +0x68, m_cachedLocalPlayerStats +0x78, sizeof 0x700), and the 609-byte constructor @0x636D90 - far too big to fold - says BFME shifts everything from m_localName on by 8: it zeroes the four AsciiStrings at +0x6C/+0x74/+0x78/+0x7C with our exact 8/4/4 spacing and then runs a constructor on +0x80. Three matched rows contradict that, and all three are misattributions: getCachedLocalPlayerStats is claimed at 0x6372D0, whose body copies an AsciiString via StringBase's copy ctor at +0x78, while the real one - same shape at +0x80, calling the big EH-carrying map-copying constructor at 0x6577D0 - sits unclaimed at 0x637480; setLocalProfileID's real body at +0x70 is unclaimed at 0x637110, and setMaxMessagesPerUpdate's at +0x250 is unclaimed at 0x6307A0. Both are in the same cluster as the constructor. The root cause is the five-name ICF group at 0x887B60, 121 bytes of StringBase<char> copy constructor that also carries ??0PSPlayerStats@@QAE@ABV0@@Z - a class with 24 std::maps whose copy constructor cannot possibly be 121 bytes, and which really lives at 0x6577D0. Fixing GameSpyInfo means correcting that group first, which touches other TUs and needs its own pass.
* PersistentStorageThread.cpp is missing /D_STLP_USE_STATIC_LIB, and that one flag is worth more than any layout guess: without it the TU calls __new_alloc::allocate through __imp_ (a DIR32 indirect call) where retail calls it directly, which desynchronises every instruction after the first map. Adding it takes PSPlayerStats' copy constructor @0x6577D0 from 1374 byte differences down to 379 with the first 1249 bytes exact, and all 14 matched rows in the TU survive. Check that flag on any TU whose diff looks like a total desync right after the first container.
* With the flag on, PSPlayerStats reads out further. BFME has three more PerGeneralMaps than ZH - the copy ctor builds them at +0x124, +0x130 and +0x13C where our layout has already moved on - and the string block that follows is ordered differently: one dword at +0x148, a string at +0x14C, a lone dword at +0x158, then strings at +0x15C and +0x168, i.e. gamesAsRandom sits after options and there is a fourth std::string ZH does not have. The region between that block and the last string is two dwords shorter than ours, since the constructor copies plain dwords at +0x1B0 and +0x1B4 and then builds the final string at +0x1B8. Modelling all of that gets to 109 differences; what is left is register allocation around the string constructions, which means at least one more member is still in the wrong place. Note the class's copy constructor cannot be landed until its ledger row moves off the bogus 0x887B60 ICF group.
* PSPlayerStats is fully reconstructed and its ledger rows are off the bogus 0x887B60 ICF group. Three things had to be true at once: the TU needs /D_STLP_USE_STATIC_LIB (without it STLport's allocator is called through __imp_ and the instruction stream desyncs after the first map); BFME has three more PerGeneralMaps, drops QMwinsInARow and maxQMwinsInARow, orders the tail exactly the way the copy constructor assigns it, and carries a fourth std::string; and the copy constructor assigns that string between desyncsInARow and maxDesyncsInARow with lastLadderHost moved after lastLadderPort. All 1896 bytes then match. The two rows repointed are ??0PSPlayerStats@@QAE@ABV0@@Z (0x887B60 -> 0x6577D0) and the pair<const int, PSPlayerStats> constructor (0x0A9D80 -> 0x658880, found by grepping .text for that ctor's exact 30-byte shape and checking which hit calls the real copy ctor). Both old addresses were 121-byte StringBase<char> code that cannot copy a 0x1DC-byte class.
* The 0x887B60 ICF group had pulled a whole cluster of GameSpy rows onto wrong addresses, and once PSPlayerStats was reconstructed the rest fell out by one technique: take our compiled COMDAT, mask the reloc slots, find the longest reloc-free run, grep .text for it and keep the hits where every unmasked byte agrees, then disambiguate the survivors by which thunk their calls land on. That moved six rows into the GameSpyInfo cluster - getCachedLocalPlayerStats 0x6372D0 to 0x637480, setLocalProfileID 0x2ED490 to 0x637110, setMaxMessagesPerUpdate 0x0FB8A0 to 0x6307A0, the 0x34-node tree's dtor to 0x634060 and its _M_erase to 0x632FC0, and pair's scalar deleting dtor 0x4EA380 to 0x631E50 - and three symbols.csv pins onto the thunks retail actually encodes. Note the pins must name the THUNK, not the body: the copy ctor is reached through 0x1C783, _M_erase through 0x3EA2C and the pair dtor through 0x41C5E.
* add_match verifies the whole TU on every call, so a cluster of rows that are all wrong together cannot be repointed one at a time - each attempt fails on its siblings and reverts. Repoint all but one with --no-verify and let the last one run the verification; it byte-checks every row in the file, so nothing survives unverified.
* BFME keeps AsciiString::set and AsciiString::releaseBuffer OUT of line where the ZH header defines both inline, and that alone was the whole difference in GameSpyInfo::addToSavedIgnoreList @0x635670: retail calls 0x887C90 and 0x887940 at the points our build expands the ref-count dance inline. Deleting the two inline bodies from a TU-local AsciiString.h - the header is reachable through the include path because sweep does not shadow Common/AsciiString.h - took the function from 226 bytes with a divergence at +0x18 to an exact 149. Worth trying on any function that is a byte-for-byte prefix match until the first string assignment or destruction.
* Not every ledger row starts where its function does. joinBestGroupRoom's row claims 0x634EF2/433, but scanning back to the int3 padding shows the real function is 0x634EC0/483 - the claim begins eleven instructions in. That function also takes an argument (it compares it with 2 and picks a flag at +0x60 or +0x64 accordingly, which incidentally names the first dword of the 8-byte hole ahead of m_localName), so the row's NAME is wrong too: BFME's is not the void overload. Fixing it needs the row renamed, and add_match can only replace a row under its existing name.
* Two GameSpy shim facts were in the right size but the wrong place, and the constructor could not tell the difference. The 8 extra bytes in GameSpyInfo sit between m_currentGroupRoomID and m_gotGroupRoomList, not after it: addGroupRoom @0x636650 sets m_gotGroupRoomList at +0x68 where ours had +0x60, and joinBestGroupRoom @0x634EC0 reads the two new dwords at +0x60 and +0x64 - choosing between them on its argument - before clearing m_currentGroupRoomID at +0x5C. Likewise GameSpyGroupRoom's extra dword follows m_name rather than closing the class: addGroupRoom reaches the field after m_name with add eax,8 at four separate sites where we emitted add eax,4. Both placements leave every offset the constructor pins unchanged, which is exactly why it accepted the wrong ones - when a hole's position is only fixed by one function, look for a second.
* Rows that need renaming or removal are SKIPPED, never hand-edited. add_match can only replace a row under its existing name, and functions.csv is not to be edited by hand, so a function whose ledger row carries the wrong symbol name - or whose row would have to disappear - is left alone and written up instead. joinBestGroupRoom is the current example: its row claims 0x634EF2/433 while the real function is 0x634EC0/483 and takes an argument, so the void-overload name on that row cannot be right. It stays as it is until the tooling can express a rename.
* A candidate that matches as a long prefix and then makes one call too many is a source-content difference, not a layout one. ScriptActions::doBorderSwitch @0x2EFC50 matched 98 of its 102 bytes and then ran an extra ThePartitionManager->refreshShroudForLocalPlayer(); BFME returns straight after the observer re-reveal. Deleting that one statement matched all 102. The scan that finds these is cheap: for every candidate whose COMDAT is LONGER than retail, measure the common prefix - the high-percentage ones are either an inlined-versus-out-of-line call or a statement BFME does not have.
* UnicodeString::compareNoCase is out of line in BFME too - LANGameSlot::isUser @0x68E8F0 calls it at 0x9EFE0 where the ZH header's inline body expands the comparison into the caller - and taking it out of line drops that function from 166 bytes to 149 against retail's 132. It still does not match: our frame is 4 bytes larger and we write one more EH state slot than retail, so one extra temporary is being tracked. Reverted rather than left in, since it lands nothing on its own, but the out-of-line finding holds and the shim is two lines to recreate.
* sweep's Module.h already carries a BFME_MODULE_NO_MPO switch that drops MemoryPoolObject from Module's bases, and it is the same merged-base fact TunnelTracker and TurretAI showed: defining it on a module TU shifts every member down a dword. SwayClientUpdate's constructor @0x6044E0 went from writing +0x10/+0x14/+0x18 to the retail +0xC/+0x10/+0x14 the moment the define was added. Only eight TUs use it so far, so any module whose candidate is off by exactly 4 is worth trying it on. The remaining difference there was BFME zeroing two more dwords at +0x24 and +0x28 - two extra Reals after m_unused, held as holes.
* BuildListInfo was logged as a 1-in-3 ambiguity with three suspect setter rows, and the merged base settles it: BuildListInfo derives from MemoryPoolObject and Snapshot in ZH, so the same one-vptr merge that TunnelTracker, TurretAI and Module show applies, and duplicate @0x1944D0 matched all 194 bytes at once. The two setters it broke were indeed misattributed - setHealth and setWhiner really live at 0x191490 and 0x1914A0, right beside duplicate, while the ledger had them at 0x265BC0 and on a Snow ICF fold at 0x45A9A0. setHealth folds with setFrameToEvaluate, so it goes in as an --icf-owner alias. When a class is off by exactly 4 everywhere, check its ZH bases before doubting the near-miss.
* ControlBarSchemeManager's destructor @0x4AE850 shows the STLport flag is only half the story in some TUs. Without /D_STLP_USE_STATIC_LIB our build emits call dword ptr [__imp_] where retail emits a direct call - six bytes against five, which is the entire one-byte size difference - so the flag is proven here by the bytes. But adding it takes us to 156 against retail's 166 and exposes the rest: retail deallocates with a size, push 0xc / push eax / call 0x82E5F0 / add esp,8, while we call the unsized operator delete with add esp,4, and retail tracks one more EH state. That is a second STLport configuration axis - node allocator versus plain new/delete - not something the static-lib flag controls. Reverted, since half a fix lands nothing.
* Two of the four remaining -4 candidates are multi-cause and stay open. generateIndexBuffer @0x79EEA0 needs three things at once: a member at +0x128 rather than +0x12C, a literal 0 where we pass that member, and a vtable slot at +0x6C rather than +0x60 - and the object it calls through is a global in retail where ours is a member. parseImagePart @0x581480 has one local too many: retail's prologue is push ecx where ours is sub esp,8.
* AggregateDefClass::Initialize @0x980A50 is one byte from matching and the cause is a flag representation, not a layout. Retail reads the sub-object LOD flag as mov eax,[edi+0x10] / shr eax,0x14 / and eax,1 - a one-bit field at bit 20 of RenderObjClass::Bits - where our accessor returns Bits & SUBOBJS_MATCH_LOD and MSVC folds that into a byte load at +0x12. Rewriting the accessor as (Bits & SUBOBJS_MATCH_LOD) != 0 does NOT reproduce it: the compiler keeps the byte load and just appends and eax,1, which took the function from 1 differing byte to 86. Reverted. Getting the shr/and pair means declaring the flag as a real bitfield in Bits, which changes RenderObjClass for every TU and needs its own pass.
* AggregateDefClass::Initialize @0x980A60 needed three separate BFME facts and none of them was a layout offset. SUBOBJS_MATCH_LOD is bit 20 in BFME, not bit 16 - retail reads it with mov eax,[edi+0x10] / shr eax,0x14 / and eax,1, and bit 20 is exactly the slot IS_ADDITIVE vacated when it moved to 0x400000 - and the accessor returns a normalised 0/1 rather than the masked value. Initialize also calls the FREE Create_Render_Obj at 0x8FF290 instead of the virtual member. And Build_Subobject_List sits at vtable +0x40, two slots earlier than ours, because Load_Assets and Create_Render_Object are not virtual in BFME. Which two to demote is not a free choice: the ledger pins Free_Subobject_List, Add_Subobject, Find_Subobject and Is_Object_In_List as virtual through their MAE mangling, so demoting Is_Object_In_List makes its row's symbol vanish from the object - the build says symbol not found, which is a clean way to tell that a method must stay virtual.
* DX8Wrapper::Set_Default_Global_Render_States @0x9081D0 differed by one push: retail sends a single argument to 0x905990 where we sent two to the render-state helper, because BFME calls the dedicated Set_DX8_ZBias(0) rather than Set_DX8_Render_State(D3DRS_ZBIAS, 0). Switching the call was not enough - Set_DX8_ZBias is WWINLINE in dx8wrapper.h, so it expanded and took the function to 499 bytes. Retail keeps it out of line, and moving the body into dx8wrapper.cpp matched all 211. That move is safe precisely because every other call site in the tree is commented out, which is worth checking before demoting any WWINLINE.
* The Debug vtable was written off as needing fourteen invented virtuals; it needs none. BFME simply makes Debug polymorphic, and marking every non-static member function virtual IN DECLARATION ORDER - 35 of them, no destructor added, no placeholders - lands operator<<(const char*) at slot 14 exactly, which is the +0x38 that DebugIOCon::Execute @0x891200 calls through. All 239 bytes then match. The shim is reachable after all: _pch.h pulls debug/debug.h and sweep has no debug directory, so a shim carrying both debug.h and debug_debug.h wins on the include path and its sibling include resolves inside the shim. Same shape as EstablishConnectionsMenu - when a whole small class turns out to be polymorphic, promote what is already declared before inventing slots.
* Identification in a fresh clone is gated on one missing file. reverse/ghidra_functions.csv is gitignored and derived, and without it locate.py, anchor_by_string.py, audit_claim_boundaries.py and next_work.py's tier 3 all refuse to run - which is why only 619 of 10029 present-unmatched markers (6.2%) can even be byte-compared here. Regenerating it needs Ghidra plus a JDK 21; this machine has neither (Java 8 only), so the whole identification front is blocked on a one-time setup, not on analysis.
* int3 padding is a usable stand-in for Ghidra's function boundaries: scanning .text for runs of three or more 0xCC yields 82120 function starts against the README's estimate of ~78000, 9395 of which the ledger already claims. That is enough to reimplement locate.py's known-starts check without Ghidra, and enough to run the boundary audit - but only for the mid-INSTRUCTION verdict. The weaker mid-function-but-aligned verdict fires on 1263 rows and is mostly noise, because the linker does not always pad between functions; that class genuinely needs Ghidra's real boundaries.
* Two ledger rows claim an address inside an instruction, which no source can ever produce: assignDefaultGadgetLook is claimed at 0x4800FC while its function starts at 0x480090 (the claim lands inside mov [0x12F1BC0],eax), and parseFont at 0x485B60 while its function starts at 0x485B50 (inside the SEH prologue's mov fs:[0],esp). Both are MASM-dump rows, so they verify only because the dump reproduces bytes at the wrong place. Six other mid-instruction hits are artifacts - linear disassembly walking into the inline jump tables of the Get_DX8_*_Name switches - and must be filtered by checking whether the straddling instruction is code-like.
* next_work.py's structural-reconciliation queue proposes an RVA from shape similarity, and that RVA can be wrong - it is a hypothesis, not a claim. CommandButton::isReady was offered at 0x49AD65 with a 91%% shape ratio, but 0x49AD65 is 0x35 bytes inside the function that starts at 0x49AD30 (146 bytes, where the queue said 93). A masked scan of our compiled body finds no placement anywhere in .text, so that function genuinely differs: BFME's version null-checks the object first, then branches on a field at +0x10 being 0x16 and answers from a frame counter at Object+0x36C, and only otherwise runs the special-power and upgrade tests we have. Check a queued RVA against the int3 boundaries before trusting it.
* HeightMapRenderObjClass's destructor @0x6D33B0 is two facts deep. BFME does not delete m_extraBlendTilePositions there; it stores 0 to TheHeightMap and chains to the base destructor, which takes our 142 bytes down to 123 against retail's 116. The rest is a chain: our freeMapResources is a three-line wrapper that MSVC inlines into the destructor, while retail calls a real 122-byte function at 0x6D2690 (unclaimed) that releases the index and vertex buffers at +0x30D4/+0x30D8 directly. Our freeIndexVertexBuffers is 204 bytes and does not match it either, so BFME redistributed the work between the two - the destructor cannot land until freeMapResources is reconstructed.
* Smudge is not pool-allocated in BFME. SmudgeManager's destructor @0x5D4390 frees one with a plain single-argument operator delete where W3DMPO_GLUE routes through getClassMemoryPool and freeFromW3DMemPool; dropping the glue from a TU-local Smudge.h matched the whole function. Note SmudgeSet keeps its glue - its delete goes through the virtual destructor at vtable slot 0 and already matched - so the two structs in the same header differ. Also: the ledger row understated the size by 9 bytes (239 against the padding-delimited 248), and those last nine bytes match too, so verification had been comparing a truncated body. Worth checking the padding boundary whenever a row verifies but the COMDAT is longer than the claim.
* W3DProjectedShadowManager::init @0x7AF630 needed a layout shift and a shorter body. Every member from m_shadowCamera on sits 12 bytes later in BFME - the camera at +0x20 against our +0x14, the texture manager at +0x24C against our +0x240, the same +0xC for both - and the retail body returns straight after storing the camera, with no SpecialRenderInfoClass allocated and no light_environment assignment. Both together match all 156 bytes.
* Do not purge another TU's .obj while a full gate is running in the background: build.py opens the object it expects to find and dies with FileNotFoundError, so the commit fails for a reason that has nothing to do with the change being committed. Cost me one gate cycle.
* MeshMatDescClass::Init_Alternate @0x929410 is not a layout or statement problem and should not be chased as one. Ours is 1125 bytes against retail's 1047 with 423 differing bytes, but the first 0x161 are exact and the instruction streams stay in lockstep: the differences are SIB operand order - we emit mov eax,[ecx+ebx] where retail has [ebx+ecx], same effective address, different encoding - plus one extra reload of edi from [esp+0x24] at three points, i.e. one more value live across the loops. Both are compiler-choice symptoms of a slightly different source shape in the pass/stage loops, most likely how the default_materials pointer is hoisted. Nothing here is decidable from the bytes alone; it needs the loop rewritten by hand and re-measured, so it is a sit-down job rather than a near-miss fix.
* The freeMapResources that HeightMapRenderObjClass's destructor calls is at 0x6D2690, 122 bytes, unclaimed, and it is nothing like ours. Retail's body: if the pointer at +0x30D8 is non-null it takes a DX8 lock (call 0x903090, which waits on a handle with a 20-second timeout), deletes that pointer as an ARRAY of 196-byte objects with a destructor - the classic ??_M vector destructor iterator with count read from [p-4], element size 0xC4 and the element dtor pushed as 0x42B9A4, followed by operator delete[] on p-4 - releases the lock (call 0x905B10, which leaves a critical section), and nulls +0x30D8; then it zeroes +0x30E0, +0x30E4 and +0x30DC and deletes the array at +0x30D4. Our freeMapResources is a three-line wrapper (19 bytes) and our freeIndexVertexBuffers is 204 bytes releasing m_indexBuffer and the vertex-buffer tiles - neither matches. Writing this needs the members at +0x30D4..+0x30E4 named and the two lock functions identified, so it is blocked on evidence, not effort.
* SmudgeSet is not pool-allocated in BFME either: addSmudgeSet @0x5D4240 takes one from a plain single-argument operator new where W3DMPO_GLUE routes through getClassMemoryPool and allocateFromW3DMemPool. Note the destructor could not tell - SmudgeSet's delete goes through the scalar deleting destructor at vtable slot 0, which looks the same either way, so the allocation site is what discriminates. When a class looks pool-free on one side, check both new and delete before concluding.
* The AsciiString out-of-line lever applies to TUs that already use the asciistring8 shim, but the shim dirs must not be stacked: dropping asciistringsetoutofline in front of asciistring8 makes the plain 16-byte header win and silently discards the 8-byte AsciiStringData. Build a variant of the shim the TU already uses instead - asciistring8outofline is asciistring8's header with the set and releaseBuffer bodies removed - and swap it in place of the original. That took ImageCollection::addImage @0x5D3410 from 157 bytes with an inlined ref-count teardown to an exact 133, where retail calls releaseBuffer at 0x887940.
* W3DMouse needed three separate things and an offsetof probe to place them. The TU needs the 8-byte AsciiStringData - retail tests a cursor name with cmp word ptr [eax+4],0 where the plain header made us read a byte - and the Mouse hierarchy carries 0x368 more bytes than ours, arriving in three steps that two functions pin between them: 0x34C before Mouse::m_currentRedrawMode (+0x10E0 against our +0xD94), 0xC more before Mouse::m_currentCursor (+0x4DA8 against +0x4A50), and 0x10 more before Win32Mouse::m_currentWin32Cursor (+0x5E20 against +0x5AB8). The first and largest of the three is not a hole at all: BFME has ten more mouse cursors, so m_cursorInfo[NUM_MOUSE_CURSORS] is ten CursorInfo longer. The DIR32 consistency gate is what found it - the byte comparison masks reloc slots, so a wrong array length hides inside the loop's end-of-array pointer, and initPolygonAssets resolved the file-static cursorImages to two different bases until the enum grew. Retail's own imul eax,eax,0x54 in setCursorDirection fixes CursorInfo at 84 bytes, so ten entries are 0x348 of the 0x34C and only four bytes stay unexplained. The probe is what makes this placeable: offsetof on a copy of the TU with the access keywords redefined turns raw retail offsets into member names. Put those defines ABOVE the source's own prologue - after it they are too late, because the prologue has already pulled the headers.
* Another row with an understated size: initPolygonAssets was claimed at 174 bytes where the padding-delimited function is 184, and all 184 match. That is the second one today, so it is worth checking the int3 boundary routinely whenever our COMDAT is longer than the claim.
* BFME's InGameUI has nine more virtuals than ours ahead of isScrolling. W3DMouse::setCursorDirection @0x700820 calls isScrolling at vtable +0xA4 and getScrollAmount at +0xB4 where this header puts them at +0x80 and +0x90, and the two keep their four-slot spacing, so the count is exact even though the identities are not. Two notes for next time: the slot arithmetic has to come from the source line, not from counting virtual declarations in the header - the regex count put isSelecting at +0x80 and the first attempt at nine stubs landed between the two real calls, fixing one and leaving the other - and stubs belong immediately ahead of the first pinned slot so nothing below them moves.
* ModuleFactory::ModuleTemplate is 16 bytes in BFME and the tree contradicts itself about it. Two independent unique bodies say the fourth field sits at +0x8 and pushes m_whichInterfaces to +0xC: addModuleInternal @0x129AC0 writes [eax] [eax+4] [eax+8] and [eax+0xC] and rets 0x18 rather than 0x14 (a sixth argument), and findModuleInterfaceMask @0x129100 reads the mask at &it->second + 0xC where we read +8. module_factory.cpp already models exactly that and calls the field m_data - and it is a matched TU, so the repo asserts the 16-byte layout already. Three rows claimed to Thing/ModuleFactory.cpp assert the opposite: ??0ModuleTemplate@ModuleFactory@@QAE@XZ @0x5C5D0 zeroes three dwords and the two pair copy constructors @0x69580 and @0x695F0 copy three dwords of second. They are misattributed, not evidence. The 13-byte constructor is generic enough that 17 different classes in our own tree compile to those exact bytes, and retail holds 16 three-dword pair copies against 37 four-dword ones, so the real pair<NameKeyType,ModuleTemplate> constructors are among the four-dword bodies (tails at 0x69676D and 0x6970DD are the nearest). Adding m_data takes findModuleInterfaceMask to a byte-exact 84 and breaks those three, so the fix is blocked on re-attributing rows, which needs a rename the tooling does not offer - add_match's --icf-owner only registers a NEW row on an already-claimed RVA.
* The notes column has an object-symbol=<mangled> escape hatch that build.py's ledger_object_symbol reads, so a row whose name column is truncated or wrong does not have to be renamed to be repointed at a real COMDAT. ?loadD3DCursorTextures@W3DMouse@@ carries no signature in the ledger and is landable through it - the blocker there is the body, not the name: retail runs 559 bytes against our 332 because BFME loads cursor textures through a different API with an AsciiString temporary and a full EH frame.
* Ranking the whole backlog beats picking one candidate at a time. Every present-unmatched marker whose TU already compiles can be measured against its MASM-dump row in one pass - 503 of them are measurable, and the distribution is steep: one at a single differing byte, one at two, and roughly a dozen under ten. Prefilter the object files by searching the raw bytes for the retail pattern before parsing symbols, otherwise re-parsing each .obj per symbol makes the sweep unusable.
* Three pins harvested from the near-miss sweep, each a single delta and each blocked on a class being SMALLER in BFME rather than larger, which no shim can express by padding. ParticleSystem's transform matrix sits at this+0xC0 against our +0x274: getPosition @0x5BDDB0 reads its translation as three floats 0x10 apart at +0xCC, +0xDC and +0xEC, which is a row-major 4x4, so ParticleSystemInfo is 0x1B4 bytes shorter - and it is not the Generals-versus-Zero-Hour split, because the Generals header is the larger of the two. InGameUI::m_superweapons is at this+0x5CC against our +0x17F0, 0x1224 shorter, from findSWInfo @0x449E70. LANAPI has a member at +0x4C where we put it at +0x44, its LANMessage local is 0x1DC bytes rather than 0x1D8, and the virtual it calls is at +0xC4 against our +0xAC, all three from RequestLobbyLeave @0x6850F0.
* Growing a class is cheap and shrinking one is not. Every shim so far adds bytes or virtuals, which is why the Mouse, InGameUI-vtable and Debug cases landed; when retail puts a member EARLIER than we do the only honest fix is to find what we have that BFME does not, and that is class reconstruction, not a hole. Worth sorting the near-miss backlog by sign before picking work.
* LANAPI needed three separate growths and RequestLobbyLeave @0x6850F0 pins all of them at once: six more virtuals ahead of fillInLANMessage (called through +0xC4 against our +0xAC), eight more bytes ahead of m_transport (+0x4C against +0x44) and a LANMessage four bytes longer (0x1DC of frame against 0x1D8). The stubs go in LANAPIInterface, which owns the vtable, not in LANAPI which only overrides. Note the shape of the evidence: a 75-byte function carrying three independent structural facts is worth far more than its size suggests, so do not skip small functions that touch several subsystems.
* When a shim edit lands bytes in the wrong class, the symptom is that every member shifts by the same amount from offset zero. Anchoring on the string 'struct LANMessage' matched the forward declaration eighty lines above the definition, and brace-matching from there appended the padding to the end of a base class instead - which broke four previously matched rows at +8, +0xC, +0x1C and +0x20 while leaving the intended member alone. Anchor on the definition ('struct X' followed by a brace), and read a uniform low-offset shift as landing site error rather than as evidence about the class you were aiming at.
* LANAPI needed three separate growths and RequestLobbyLeave @0x6850F0 pins all of them at once: six more virtuals ahead of fillInLANMessage (called through +0xC4 against our +0xAC), eight more bytes ahead of m_transport (+0x4C against +0x44) and a LANMessage four bytes longer (0x1DC of frame against 0x1D8). The stubs go in LANAPIInterface, which owns the vtable, not in LANAPI which only overrides. A 75-byte function carrying three independent structural facts is worth far more than its size suggests.
* When a shim edit lands bytes in the wrong class the symptom is that every member shifts by the same amount from offset zero. Anchoring on the string 'struct LANMessage' matched the forward declaration eighty lines above the definition, and brace-matching from there appended the padding to the end of a base class - which broke four previously matched rows at +8, +0xC, +0x1C and +0x20 while leaving the intended member alone. Anchor on the definition, and read a uniform low-offset shift as landing-site error rather than as evidence about the class you were aiming at.
* Do not trust a local diff script that masks reloc slots to tell you a function is done: it hides exactly the calls that are not yet pinned. RequestLobbyLeave read as zero diffs while its call to LANAPI::sendMessage was unresolved, and only add_match's own verification caught it. The fix is a symbols.csv row for the call THUNK, not the body - 0x2B599 jmp 0x684CF0 here - and the file is CRLF despite check_csv describing it as LF-native, so append with the terminator the file actually uses.
* WinInstanceData::setText @0x499D60 gets to six differing bytes purely by attaching two shims that already exist, which is worth knowing as a pattern: before reconstructing anything, check whether some other TU already models the class. displaystringmanager's three stub virtuals in slots 6-8 move newDisplayString from +0x18 to +0x24, and displaystring's removal of the pool-glue virtual moves DisplayString::setText from +8 to +4 - both retail values, both hit exactly.
* What is left of setText is a pure instruction swap, and it resisted everything: retail emits mov [esp+8],esp then mov ecx,esp where we emit them the other way round, same six bytes reordered. Not a toolchain wall - our own compiler emits retail's order in 121 TUs, including the identical push ecx / lea edx / store / mov ecx,esp shape in W3DDisplay::gatherDebugStats. Insensitive to /O1, /Ot and /Oy-, and unchanged by removing the DEBUG_ASSERTCRASH between the two statements. Whatever perturbs the scheduler here is upstream of the flags, so the attempt was reverted rather than left as a near-match.

## RenderObjClass has no spare tail virtual, and two matched rows prove it

An attempt to give `RenderObjClass` one more virtual at the very end -- to move
`BoxRenderObjClass::update_cached_box` from slot +0x208 to the +0x20C that both
box constructors (`AABoxRenderObjClass` @0x957880, `OBBoxRenderObjClass`
@0x957C20) reach through -- is refuted by two rows that already match without it.
Adding a virtual to the base shifts every *derived* class's own slots by four,
and both of these are exact today:

- `Animatable3DObjClass::Simple_Evaluate_Bone` @0x982C20 forwards through
  `call [edx+0x214]`; with the extra slot it compiles to `[edx+0x218]`.
- `HLodClass::Get_Obj_Space_Bounding_Box` @0x97BC20 breaks the same way.

So the +4 the box constructors want cannot come from the end of
`RenderObjClass`. It is somewhere between `BoxRenderObjClass`'s own start and
`update_cached_box`, or the constructors' shape is wrong -- not settled here.
The two constructors stay as their naked thunk TUs, which do not depend on the
vtable at all, so no bytes are lost by leaving this alone. 495 bytes of matched
code outrank the 314 the conversion would have bought.

CRT functions reached under /MD are imported, so retail calls them indirectly through the IAT (ff 15); declare them __declspec(dllimport) or the compiler emits a direct rel32 that is one byte shorter and shifts every rel32 after it (hit on ceil in SupplyWarehouseDockUpdate::setCashValue).

The build's default -EHsc- only clears the /EHc half, so /EHs stays on and any destructor-bearing temporary gets an SEH prologue plus unwind state variable; a retail body with no unwind frame needs /EHs-c- on the source's cl line.

A boolean returned as `if (cond) return TRUE; return FALSE;` and as `return cond;` are not interchangeable: MSVC 7.1 computes the first in al (sbb al,al / inc al) and the second in eax (sbb eax,eax / inc eax). Read the ZH phrasing rather than assuming the compact form - it cost several attempts across the UserPreferences boolean getters. Check the String-ref verify line as well as Functions when batch-converting: a wrong literal still byte-matches because the DIR32 address is copied from the target.

## Two byte-equal candidates: count the thunk's callers, then name the cluster

`SimpleObjectIterator::firstWithNumeric` had two addresses on offer -- the
ledger's 0x001DE040 and 0x001CE6D0, which a masked-body sweep also reports as an
exact match for the same 51 bytes. Byte comparison cannot separate them and
never will: both really are those bytes.

Two cheap checks settle it, and neither needs a disassembly of the body.

**Who reaches it.** Both addresses are reached only through an ILT thunk, so the
question is who calls the thunk. 0x001DE040's thunk (0x000398C9) has exactly one
rel32 caller, at 0x001DE032 -- code sitting immediately above the body itself.
0x001CE6D0's thunk (0x00043126) has *zero* rel32 callers anywhere in `.text`: a
dead incremental-link entry, which is no evidence at all.

**Which translation unit owns the neighbourhood.** Functions from different TUs
do not interleave in the image, so the nearest claimed rows name the cluster.
0x001DE040 is surrounded by `sortFarToNear` (0x001DDF40), `next` (0x001DDFB0),
`~SimpleObjectIterator` (0x001DDFD0) and `??_GSimpleObjectIterator`
(0x001DE080) -- all SimpleObjectIterator.cpp. 0x001CE6D0 sits between
`Object::reactToTransformChange` (0x001CDC30) and `Object::setDisabled`
(0x001CE790), which is the Object.cpp/ObjectFields.cpp cluster and a different
TU entirely.

So the ledger row is right and the sweep's candidate is an unrelated 51-byte
body that happens to compile the same. Nothing was changed; the point is the
method. A sweep that reports several exact placements has not found several
candidates of equal standing -- caller count and cluster membership usually
leave exactly one, and both are two minutes of work against `functions.csv` and
the rel32 sites. Do that before spending a cycle on the bytes.

## The binary names the file that owns a gap, and the biggest gaps are not ours

`gaps.py`-style output is a list of addresses, which cannot be picked up as
work. It can be, though: retail kept the assert and DEBUG_LOG `__FILE__`
strings, and they are absolute paths out of the original build tree --
`F:\bfme\Code\gameengine\Source\GameLogic\Object\Update\AIUpdate.cpp`. A gap
whose code pushes one of those addresses is that translation unit's code, named
by the image rather than inferred. `tools/gap_owner.py` does the scan and rolls
the result up per source file.

Two things it establishes immediately.

**The largest holes in `.text` are vendored Microsoft middleware.** Everything
between roughly 0x9A0000 and 0xB00000 is statically linked library code:
0xAC8183 is 216KB of DirectX error-string tables (`E_ABORT`, the `CO_E_*` and
`DIERR_*` families), and 0xA40673 is 93KB of the D3DX shader assembler
(`POSITION`, `BLENDWEIGHT`, `TESSFACTOR`, "internal error: unknown node").
Those two alone are 310KB, they head every ranking of unclaimed bytes, and no
amount of work on them belongs in this project. The headline coverage number is
measured against a denominator that includes them.

**The largest holes that are ours, with their addresses**, are
`AIUpdate.cpp` (33,685 real bytes at 0x273DCE), `HordeContain.cpp` (26,101
across four gaps from 0x2369B5), `AIGroup.cpp` (24,566 at 0x1527B2 and
0x156C2E), `AptOnlineQuickMatch.cpp` (10,811 at 0x558F9E), `ScriptEngine.cpp`
(10,601 at 0x344291), `SpecialAbilityUpdate.cpp` (10,165 at 0x2A6588) and
`LuaScriptEngine.cpp` (9,695 at 0x2E3F04). Three of those -- HordeContain,
AptOnlineQuickMatch and LuaScriptEngine -- have no Zero Hour counterpart at
all, so they are reconstruction from the disassembly rather than porting.

The coverage is sparse by nature: a release build keeps only the asserts that
survived, and 118 gaps over 8KB hold 2.56MB of real bytes of which only 171KB
sits in a gap that names anything. Anonymity is not evidence that a region is
uninteresting -- it is usually just a file whose asserts were compiled out.

The OptionPreferences boolean getters backed by a GlobalData default compare their value with an inlined 4-byte repe cmpsb against "yes" plus sete, not a stricmp call - a plain memcmp with #pragma intrinsic still emits a real call under these flags, so that sub-shape is still unsolved and those rows remain naked.

SEH-framed bodies are convertible - findVeterancyUpgrade landed - but two have now died on MSVC bookkeeping order rather than logic: amIHost stores the EH frame pointer before setting up ecx for a by-value AsciiString temporary and parseAddModule pushes call arguments before storing a member flag, and neither order is reachable by rephrasing the source. Everything up to that point matched byte for byte in both.

For a by-value class argument built from a temporary at the call site, declare the copy constructor even though it is never called: without it MSVC materialises the temporary in a separate slot and re-pushes, with it the object is constructed straight into the reserved argument slot as retail does. That leaves only the EH-record store and the ctor this-pointer setup swapped (mov [esp+N],esp before mov ecx,esp in retail); no source phrasing and no /Ox /Og /O1 /Ob2 /Oy- /Gy /GF variation moved it, and it currently blocks ControlBarResizer::init and GameSpyStagingRoom::amIHost at one instruction pair.
## A dump row can be wrong at both ends, and the .asm file says so itself

`??0AIAttackMoveStateMachine@@QAE@PAVObject@@VAsciiString@@@Z` claimed 0x002C1061
for 501 bytes and byte-verified forever, because a MASM dump is the retail bytes.
It was wrong three ways over, each independently sufficient:

- **The start is inside another function.** The body containing 0x002C1061
  begins at 0x002C0FE0 — 16-byte aligned, preceded by `int3` padding — so the
  claim starts 129 bytes in. `audit_claim_boundaries.py` stays silent on this:
  it tests for a start inside an *instruction*, and 0x002C1061 is a clean
  instruction boundary. Being decodable is not being a function.
- **The range spans a boundary, and the dump admits it.** `0CCh` repeated
  twenty-seven times sits in the middle of the `db` lines. A function body does
  not contain a run of int3. Past that padding the claim covers two real
  functions, 0x002C11A0 and the thunk at 0x002C11D0.
- **The stack pop contradicts the name.** The body ends `c3`, `ret 0`. A
  `QAE@PAVObject@@VAsciiString@@` constructor is `__thiscall` with two
  parameters and must end `ret 8`.

Two things worth carrying forward. Reading the `db` lines of a dump for an int3
run costs nothing and catches the over-long ones directly — no disassembler
required. And with `reverse/ghidra_functions.csv` present you can ask the wider
question the boundary audit does not: which matched rows start strictly inside
a recovered function body? 319 rows do, overwhelmingly `Code/*.asm`. That is a
lead list, not a verdict — Ghidra also merges adjacent functions, so a row
ending exactly where its enclosing function ends is usually fine. Confirm with
padding and alignment before withdrawing anything.

### The address it was blocking is a trap of its own

`locate.py` places `??_GAIUpdateInterface@@MAEPAXI@Z` at the freed 0x002C11A0
and it will keep doing so. Do not land it. The body is the canonical scalar
deleting destructor — `push esi; mov esi,ecx; call <dtor>; test [esp+8],1; …;
ret 4` — whose only identifying operand is the destructor it calls, and
`build.py` fills that REL32 in from the target, so any class's `??_G` matches.
Following the call resolves through two thunks (0x0001E29F, 0x002C11D0,
0x0004AAF7) to a destructor body at 0x00172430, which sits among AIStates.cpp
and AIMoveToState code — a different translation unit from AIUpdate.cpp. So the
`??_G` belongs to one of the AI state classes, not to AIUpdateInterface. Chase
the destructor, never the deleting destructor.

## Interior int3 is the cheapest decisive test there is, and 18 rows fail it

The AIAttackMoveStateMachine withdrawal above turned on one observation that
generalises further than the row it killed: MSVC pads *between* functions with
0xCC and never inside one, so a run of int3 strictly inside a claimed range
proves the claim spans a function boundary. No disassembler, no Ghidra
inventory, no second opinion -- the retail bytes say it outright.

`tools/audit_internal_padding.py` runs it over the whole ledger. **Eighteen
matched rows fail**, twelve of them with runs of 64 int3 or more:

```
0x1699C2 1654B  body ends at +0x468, then 294 int3  AIPlayer::recruitSpecificAITeam
0x76E90A  568B  body ends at +0x15A, then 172 int3  Team::tryToRecruit
0x6000B0  807B  body ends at +0x274, then 172 int3  DefaultModuleTemplate<1>::writeINI
0x784783  984B  body ends at +0x0D2, then 171 int3  W3DRadar::drawViewBox
0x2AF8F9  523B  body ends at +0x126, then 129 int3  StructureToppleUpdate::doDamageLine
0x5A565D 1119B  body ends at +0x274, then 127 int3  LANAPI::handleRequestJoin
0x2BAFB8 1701B  body ends at +0x13E, then 122 int3  Locomotor::locoUpdate_moveTowardsPosition
0x6008AF 1257B  body ends at +0x2B9, then 120 int3  ParticleSystem::generateParticleInfo
0x37F2AD  711B  body ends at +0x19E, then 117 int3  Object::onVeterancyLevelChanged
0x4F1C4A  805B  body ends at +0x15E, then 104 int3  DownloadManagerMunkee::downloadFile
0x614F8E  496B  body ends at +0x10E, then  84 int3  ScriptActions::doTeamUseCommandButtonOnNearestKindof
0x0D93AC  487B  body ends at +0x11B, then  73 int3  Player::setRankLevel
```

Every one is a transcription of retail bytes -- a `.asm` dump, or the same
thing spelled as a `__declspec(naked)` body with an `__asm` block, which is why
three of the eighteen have `.cpp` sources. Both kinds byte-verify at any length,
so the gate has never had an opinion about them.

Worked example of what the overhang costs. `OptionPreferences::getLANIPAddress`
claims 0x092436 for 488 bytes. The body ends `add esp,0x10; ret 4` at
0x0924B1, 62 int3 follow, and 0x0924F0 -- 16-byte aligned -- opens `push -1;
push <handler>`, an SEH prologue. So the real function is 124 bytes and the row
has swallowed a whole SEH-bearing function that nobody can now claim, because
its address already belongs to getLANIPAddress.

Two cautions before acting on the list. Interior padding proves the *end* is
wrong; it says nothing about the start, which has to be checked separately (a
real start is 16-byte aligned or sits directly after a padding run). And these
rows belong to other people's work -- the tool reports, it does not edit.

- The if-form/expression-form split covers `!= 0` too: `if (x != 0) return true; return false;` gives `test eax,eax / setne al`, while `return x != 0;` gives the 32-bit `neg / sbb / neg`.
- `strcmp` is an intrinsic under `/Oi` so it inlines as `mov ecx,N / xor edx,edx / repe cmpsb`; `_stricmp` has no intrinsic and goes through the IAT. A retail `repe cmpsb` against a literal therefore means the case-sensitive one.
- A float local that MSVC keeps in st(0) is invisible except in the width of its constant loads: `fcom dword` / `fld dword` mean `float`, `fcom qword` / `fld qword` mean `double`. Assigning `atof`'s double to a float local emits no narrowing store at all, so the constants are the only evidence of the type.




## Ledger and git traps that cost pushes rather than cycles

Three of these are specific to how the ledgers are stored and one is generic
git, and between them they cost several failed pushes in a single session.

**`symbols.csv` is CRLF, but not uniformly.** At least one row ends with a bare
LF. Appending after such a row leaves `\n\r\n`, and the union merge driver then
sees your line and the peer copy of the same pin as different lines, so the next
rebase produces an exact duplicate and `check_csv` blocks the push. Append by
taking `upstream/master`'s copy of the file and adding your line with `\r\n`,
rather than appending to whatever the working tree happens to hold.

**Do not reach for `tools/dedup_csv.py` when that happens.** It rewrites both
ledgers with normalised terminators — a 157,000-line diff that conflicts with
every other agent and destroys the `\r\r\n` rows `add_match` indexes by raw
line. Delete the duplicated line by hand; it is one line.

**`git reset --soft upstream/master` while upstream is ahead of your rebase base
stages a revert of the peer commits in between.** The index keeps your tree,
which relative to the newer base looks like undoing their work. Check
`git status --short` for files you never touched before committing.

**`docs/lessons.md` conflicts on almost every push** because everyone appends to
it. Both sides are appends, so keeping both hunks is always the resolution — but
a conflicted rebase still needs the merge checked, since `functions.csv` uses
union merge and has no concept of a deletion.



## Frame size counts local slots, so it constrains the signature

`sub esp,N` is a direct count of the local slots MSVC allocated, and each is 4 bytes
(or the object's size). When a body otherwise matches and only the frame constant and
the esp displacements differ, do not look at the statements -- enumerate what would
occupy the slots. On ProcessAnimateWindowSlideFromLeft::updateAnimateWindow retail's
`sub esp,0x10` is exactly three locals: the saved `this`, one float temp, and the
8-byte Coord2D. Declaring the setter as `setVel(Coord2D)` reproduced every instruction
but added a fourth slot for the by-value copy; declaring it `setVel(const Coord2D &)`
removed that slot but cost a different one and spilled the FPU stack. The frame size
told me the accepted answer has three slots before any byte of the body was in doubt,
which is a much sharper constraint than reading the statements back.

## An inline accessor is not always the same code as the member read

ScriptActions::doUnitReceiveUpgrade came down to two bytes: retail loads the vtable
for the second virtual call with `mov eax,[esi]` where mine used `mov edx,[esi]`. The
first virtual call in the same block picks edx in both builds, because eax is busy
holding the argument there -- so the question was only why eax stayed unavailable in
mine. Neither the callee's return type nor the if-form moved it. What moved it was
reading the argument through `templ->getUpgradeMask()` instead of `templ->m_upgradeMask`.
Both are one `mov eax,[edi+0x20]`, but the inlined call and the direct member read reach
the allocator as different expressions and it frees eax afterwards in one and not the
other. So when a residue is nothing but a scratch-register choice, try swapping raw
member reads for the accessors the original almost certainly used -- it is a real
codegen lever, not just style.

## Two BFME facts that unlock ScriptEngine's callers

Both were needed for `ScriptAction::WriteActionDataChunk` (0x003513F0) and its
False twin, and a translation-unit-scoped shim keeps them off everyone else.

**ScriptEngine carries three more virtuals right after its destructor.**
WriteActionDataChunk reaches `getActionTemplate` through vtable +0x28 where the
Zero Hour header lands it at +0x1C. That is the same trio already recorded for
GameWindowManager and DisplayStringManager: a `SubsystemInterface` derivative
whose pin is exactly three slots late.

**Template has no base and no vtable.** `script_conditions.cpp` had already
derived the layout -- `lea edi,[esi+0x10720]` points straight at `m_uiName`, and
sizeof is 0x7C -- but the finding sat in one file's local stand-in class rather
than anywhere the real header could use it. It is why retail reads
`m_internalNameKey` at +0x0C where the pooled Zero Hour class, carrying
MemoryPoolObject's vptr in front, puts it at +0x10. Worth checking the other
locally-declared stand-ins in converted thunk files for layouts nobody promoted.

### And where the next three are NOT

`ScriptActions::doUnitGarrisonSpecificBuilding` (0x00302570) shows there are
three *more* BFME virtuals somewhere between `getActionTemplate` and
`getUnitNamed`: with only the trio after the destructor it reaches getUnitNamed
at +0x5C where retail has +0x68. Parking them immediately before getUnitNamed
gets that slot right and is still wrong -- it breaks
`doEnableOrDisableObjectDifficultyBonuses` and
`setObjectsShouldReceiveDifficultyBonus`, which pin slots in that range where
they are. Those two bound the search: the three go above whatever slots they
reach, not directly in front of getUnitNamed. Reverted rather than landed, so
ScriptActions.cpp stays 66/66.
## `jmp` over the alignment padding means a while loop, not a do-while

MSVC pads a loop head for alignment, and when the loop is pre-tested it has to jump
over that padding to enter the body: `je EXIT` / `jmp HEAD` / a multi-byte nop such as
`8d a4 24 00 00 00 00` / `HEAD:`. A do-while falls straight into the body and never
emits that `jmp`. On ScriptConditions::evaluateNamedOwnedByPlayer I wrote the mask walk
as a do-while, copying ScriptActions::doGiveMoney, and got the loop body byte-for-byte
with three things wrong outside it: the callee-saved `push esi` sat after the second
early return instead of before it, and consequently the two `return false` blocks
swapped which one was inlined and which one jumped. All three followed from the loop
form -- a pre-tested loop merges its entry test with the function's trailing
`return false`, which changes what the register save dominates. Changing do-while to
while fixed all of it in one edit. Read the entry jump before choosing the loop form,
and do not carry the form over from a sibling function just because the body matches.

### ScriptActions.cpp cannot take the same shim, and the reason is worth knowing

The trio works for Scripts.cpp and breaks ScriptActions.cpp: opting that file
into `reference/shims/scriptenginevtable` fails
`doEnableOrDisableObjectDifficultyBonuses` and
`setObjectsShouldReceiveDifficultyBonus`, whose setter writes
`[ecx+0x16F20]` where retail has `[ecx+0x17634]`.

The first guess -- that the shim, being a copy of the plain reference header,
had lost `reference/shims/scriptenginelayout`'s 0x6868 pad -- is wrong. Rebasing
it on the layout shim so the two differ *only* by the three stubs leaves the
member exactly 0x714 low all the same. So three added virtuals move a member of
that class by 1,812 bytes, which a normal derived class cannot do: whatever
`scriptenginelayout` declares, its ScriptEngine is a stand-in whose size and its
vtable are not independent. Anyone widening that shim has to understand that
first; ScriptActions.cpp was left on the layout shim alone, 66/66.

## The merged pooled-snapshot base fits State's members but not StateMachine's vtable

`TurretAIIdleState::onEnter` (0x0018CB40) reads the machine pointer at
`[esi+0x1C]` where `State : public MemoryPoolObject, public Snapshot` puts it at
+0x20, so State really does get BFME's merged base -- deriving it from Snapshot
alone moves that read onto retail's offset, which is the prediction the TurretAI
entry above makes for "any ZH class inheriting both".

The vtable does not follow, and the numbers are worth writing down because they
bound the answer. `TurretAI::recenterTurret` pins `StateMachine::setState` at
vtable +0x20. With both Zero Hour bases that needs two invented slots in front
of it, which is what `reference/shims/turretai` carries. Give StateMachine the
merged base and remove those two, and setState lands at **+0x24** -- one slot
too late. Each invented stub is worth 4, so the merged-base layout needs one
*fewer* virtual before setState than the Zero Hour declaration list provides,
not one more.

Counting the reference headers does not explain it: Snapshot has exactly three
pure virtuals and a non-virtual destructor, `MEMORY_POOL_GLUE_WITHOUT_GCMP`
contributes one virtual destructor, `GCMP_CREATE`'s getClassMemoryPool is
static, and StateMachine declares four virtuals before setState. That is slot 8
= +0x20 on paper against +0x24 measured. So one of those four is not virtual in
BFME, or the merged base contributes two slots rather than three -- and
recenterTurret alone cannot say which.

Reverted rather than landed: with the merged base and no stubs TurretAI.cpp goes
19/20, and the one casualty is recenterTurret itself. Anyone picking this up has
State confirmed, StateMachine's member offsets to check separately, and one slot
to account for.
## A declared copy constructor is what lets MSVC throw in place

`throw T(args)` should construct the exception object once. With `T` holding only
plain members and no declared copy constructor, MSVC 7.1 instead built the temporary,
then copied it memberwise into a second slot and threw that -- eight extra bytes of
frame and a run of movs the retail body does not have. The tell that it was a copy and
not just different addressing is that the loads came through the constructor's returned
`this` in eax rather than the stack slot the compiler had just written. Declaring a copy
constructor (no definition needed) removed the copy entirely and the function matched:
once the copy has to be a call, MSVC constructs directly into the exception temporary
instead. Same lever as forcing a hidden-pointer return -- a user-declared copy
constructor changes what the compiler is allowed to do inline -- but here it removes
work rather than adding it. /EHsc versus /EHs-c- made no difference at all.

## A naked byte dump proves its bytes, never its name

The byte gate compares a symbol's compiled bytes against the retail bytes at its recorded
address. For a `__declspec(naked)` body those bytes were copied from that address, so the
comparison is a tautology -- it passes for any name someone attached to the dump. Every
naked row therefore carries an unverified identity by construction, no matter which pass
produced it (the bad ones I have found span four different provenance tags, so this is not
one careless batch). Converting to real C++ is the first thing that actually tests a name,
because the mangled name has to compile from a declaration whose class, return type,
constness and arity all produce exactly those bytes.

So read the body against the claimed signature BEFORE starting. The cheapest tells:
a claimed `_N` return against a body ending `or eax,-1`; a claimed `X` (void) return
against a body that loads eax; `ret N` disagreeing with the decorated argument list; and
`this`-relative offsets that make no sense for the claimed class -- a GameLODManager method
has no reason to run _M_find over a map at this+4 while loading TheGameLODManager
separately from a global.

## The `mov [esp+N], esp` before a by-value AsciiString is still unsolved

Two unrelated functions emit the same idiom and neither reproduces it. In
OptionPreferences::getIdealStaticGameDetail (0x00090900) retail reserves the argument
slot with `push ecx`, then `mov [esp+0xC],esp`, then `mov ecx,esp` and only then
computes the source. In the AITunnelNetworkGuardState constructor (0x001717B0) it is
`push ecx` / `mov [esp+8],esp` / `mov ecx,esp` before building the name string. In both
cases the slot being written is an earlier `push ecx` reservation that nothing reads
again, so the compiler is stashing the address of a by-value class argument there.

What it is NOT: exception state (compiling /EHsc adds a full SEH prologue retail does
not have, and /EHs-c- reproduces everything else exactly); the argument expression
(member access, an explicit pointer cast and an explicit temporary all emit identical
bytes); or the ordering of the surrounding statements, which was already fixed and made
the rest of getIdealStaticGameDetail match to the byte.

This is worth solving once rather than per function: every preferences getter and every
named-state constructor passes an AsciiString by value, so the same six bytes block a
whole family. The next thing to vary is the shape of AsciiString itself -- how its
destructor and copy constructor are declared -- rather than anything at the call site.

## Probe the compiler directly instead of guessing through the byte gate

I spent six builds trying to make MSVC emit one `mov [esp+N],esp` by rewriting the
source around it -- five declarations of the class, three forms of the call site --
and every one of them compiled to identical bytes. The full build-and-compare loop is a
slow way to ask a narrow question.

Writing throwaway variants under Code/ and calling tools/build.py's own compile_source
on each answers the same question in one shot, and lets you check for two things at once
(does the idiom appear, does an SEH prologue appear) instead of eyeballing a diff. That
immediately localised it: the idiom is not a source-shape artifact at all, it is the
exception model. /EHs-c- never emits it, /EHs emits it cleanly, /EHsc and /EHa emit it
with an SEH prologue attached.

Two cautions the first pass got wrong. Search the object for BOTH the thing you want and
the thing that would disqualify it -- my first probe only looked for the idiom and
reported /EHs and /EHa as equal winners, when /EHa also drags in SEH. And remember the
probe is not the function: a probe with no destructible local said /EHs was clean, while
the real function has one and got an SEH prologue anyway. Give the probe the same locals
as the target, or drive the object with explicit init/destroy calls so it has none.
## A repointed pin leaves the wrong row behind, and both survive the gate

The Matrix3D entry above records that `?Set@Matrix3D@@QAEXABVMatrix3x3@@ABVVector3@@@Z`
was pinned to 0x00964150 -- a 274-byte ICF group shared with
`?setEaseTimes@ParabolicEase@@QAEXMM@Z` -- and that the pin was repointed to the
real 82-byte body at 0x008D6710. Two things it did not do survive today.

`reverse/symbols.csv` still carries **both** lines: line 2576 pins the symbol at
0x00964150 with no note, line 60243 pins it at 0x008D6710 with the repointing
rationale. The gate is happy either way, because a symbol legitimately has
several addresses -- the thunk and the body -- so nothing distinguishes a stale
pin from a real second one.

And `reverse/functions.csv` still claims the Matrix3x3 spelling **as a row** at
0x00964150, 274 bytes, from a `__declspec(naked)` `__emit` source, sharing that
address and size with `setEaseTimes`. The entry above already argues that
address cannot be an 82-byte function.

That is the shape to watch for whenever a pin is repointed: the note lands on
the new line, the old line stays, and a transcribed row keeps the wrong name
alive because it matches whatever bytes it was cut from. 498 symbols in
symbols.csv are pinned to more than one distinct address; most are the honest
thunk-and-body pair, and telling those apart from stale repoints needs the
5-byte `E9` test, not a count.

Next step for whoever picks it up: drop the 0x00964150 pin and the Matrix3x3
row, then re-check `??0OBBoxRenderObjClass@@QAE@ABVOBBoxClass@@@Z` (0x00957C20,
167 bytes), whose C++ is already in boxrobj.cpp and which the sweep reports at
exactly retail's size.

## Size the argument list before reading a single instruction

The decorated name says how many bytes a callee-cleaned function must pop, and the
body says how many it does pop. When they disagree the name is wrong and no amount of
getting the body right will make it build -- the mangled name is what the compiler
emits, so a five-argument name can never produce `ret 0x18`. This is the cheapest
possible check and it needs no disassembly beyond the last instruction.

The catch is sizing the list honestly. A first attempt that guessed at class and enum
return types reported 175 hits, nearly all noise from mis-consuming names. The fix is
to refuse rather than guess: a class passed by value has no size in the name, template
names embed their own `@@` so scanning for the terminator lands mid-name, and varargs
are caller-cleaned. Return None for all of those and treat None as no opinion. With
backreference digits resolved and a class-by-value return charged its hidden pointer,
the same screen reports 73 findings out of 964 naked rows, and the ones I have checked
by hand all hold up.

## A name on a byte-identical neighbour proves nothing -- follow the caller's thunk

`?getSlot@GameInfo@@QAEPAVGameSlot@@H@Z` sat on 0x0061E8E0 as `matched` and had done
for a long time. It was on the wrong body. The 25 bytes at 0x0061E8E0 are identical
to the 25 at 0x0061E900 that `getConstSlot` claims, so compiling our getSlot and
finding it agrees with one of them says only that we produced a plausible accessor,
not that we produced *this* accessor. Two byte-equal bodies mean the verifier cannot
tell them apart, and a `matched` row is then a coincidence dressed as evidence.

The discriminator is a caller. `checkForDuplicateColors` (0x00386520) calls getSlot
through the ILT thunk at 0x0001EC18, and that thunk jumps to 0x0061E8B0 -- a third,
32-byte body 0x30 earlier that nobody had claimed. Call sites encode the thunk, the
thunk names one body, and that is the only statement in the image about which of the
lookalikes carries the name. Whenever a short accessor has a byte-twin nearby, treat
its row as unproven until some caller points at it.

Two practical notes. First, the thunk target has to be decoded, not read off the
ledger note: functions.csv recorded `target=FUN_00a1e8b0` for 0x0001EC18, while the
`e9` displacement actually resolves to 0x0061E8B0. Second, repointing is cheap to
test -- the full gate went from 94119/94119 to 94119/94119 with the row moved, which
proves no matched caller had been leaning on the old address. Had the count dropped,
the old address would have been the right one.

## Confirm a source shape on a probe TU before touching the ledger

Rewriting a function to chase a hypothesis breaks its existing row the moment you
save, so the tree goes red while you are still guessing. Instead put the hypothesis
in a throwaway TU with just enough class around it to fix the offsets, compile it
with `build.compile_source`, and read the bytes back with `build.read_object_symbol_bytes`:

    import sys, pathlib; sys.path.insert(0, 'tools'); import build as B
    src = pathlib.Path('Code/probe.cpp').resolve()
    obj = pathlib.Path('build/obj_probe/probe.obj').resolve()
    B.compile_source(src, obj)                       # both args must be Path
    print(B.read_object_symbol_bytes(obj, '<mangled>', <size>)[0].hex(' '))

Compare against the retail bytes, and only edit the real source once they agree. This
is how the getSlot shape above was settled: the `&&`-for-`||` difference and the
never-firing array null check both had to be present, and the probe said so in one
compile without putting a single row at risk. `locate.py` is the wrong tool here --
it wants a unique placement in .text, and a short accessor with byte-twins is exactly
the case it refuses.

## BFME's INI parsers throw a variadic INIException where Zero Hour crashes

Zero Hour's parse helpers end with `DEBUG_CRASH((fmt, tok)); throw INI_INVALID_DATA;`,
which under NDEBUG leaves a bare throw of a constant. BFME replaced both with one
`throw INIException(code, fmt, ...)` -- a `__cdecl` variadic constructor, pinned at
0x00850600 as `??0INIException@@QAA@HPBDZZ`. In the image it shows up as pushes of the
argument, the format string, a small integer code, and a stack buffer, then the throw
helper with the same throw-info pointer the bare throw would have used. `ini.cpp` and
`GameLOD.cpp` already had the idiom; `parseDynamicGameLODLevel` (0x0007C390) needed it
with code 3 and the format string still readable at 0x01076BCC.

The same function also carries a content difference worth generalising: BFME's
`DynamicGameLODNames` has five entries, not four, with `"VeryLow"` inserted ahead of
`"Low"`, so every level constant after it shifts by one. When a parse loop's `cmp` is
one higher than the table you have, check the table before you check the codegen --
the pointers are sitting in .rdata and dumping them settles it immediately.

## A getter that returns a class zero-initialises what the scalar ones do not

Three preferences getters share one skeleton -- build a key, look it up in the map at
this+4, compare the node against the map header. Two of them return a scalar and
construct the key straight into its slot. The third returns AsciiString by value and
nulls the key slot first, `mov dword ptr [esp+0xc],0` immediately before the
constructor call, which was the entire eight-byte difference on an otherwise exact
body. In the shim that is `CustomAsciiStringShim key = { 0 };` rather than a plain
declaration. Worth remembering when porting a skeleton between siblings: the by-value
return changes more than the epilogue.

## BFME's INI object puts the scalars first and the buffers last

Zero Hour's `INI` starts with `File *m_file`, then drops an 8 KB `m_readBuffer`
immediately after it, so `m_loadType` lands at `+0x2010` and every other scalar sits
past the buffer too. BFME reordered the object: `parsePrerequisites` (0x001485B0)
reads the load type at `[ini+8]`, which is where it falls if `m_file`, `m_filename`
and `m_loadType` are the first three words and both character buffers move to the
end. `reference/shims/ini_bfme/Common/INI.h` is that reordering and nothing else.

The evidence is narrow but clean: with the shim in force parsePrerequisites compiles
to exactly retail's 63 bytes and the `cmp dword ptr [edi+8], 2` matches, where the
Zero Hour order gave 66 bytes and `[edi+0x2010]`. ThingTemplate.cpp's other 110
matched rows are untouched by the change, which is the useful half of the result --
nothing in that file was leaning on the old order, so the reorder is free to adopt
wherever it helps.

What it does not do is land the function. parsePrerequisites also reads
`m_prereqInfo` at `+0x2c4` where our ThingTemplate puts it at `+0x15c`, and 0x168
bytes of BFME additions inside a class that large is its own project.
`tools/ini_layout_diff.py` is the right instrument for it but refuses this block:
the source has 115 tokens against 110 live entries in the object because a
conditional entry compiles out, so position-based alignment is not safe. Teaching
the tool to skip conditional entries is the unblocking step, not more hand-reading.

Two smaller negatives from the same sweep, so nobody repeats them: parsePreferredAgainst
(0x0010FE90) compiles to 50 bytes against retail's 204 and parseArbitraryFXIntoMap
(0x00145C80) to 310 against 206, both with unresolved template callees. Neither is an
INI-layout problem and the shim does not move them.

## The field table names BFME's inserts, so stop guessing at pad sizes

With `ini_layout_diff.py` reading tokens out of the object, CommandButton falls out
in one run: every parsed field from `SpecialPower` onward is +16 against retail, and
retail's table has two entries ours does not at exactly the offsets that gap covers
-- `NeededUpgrade` at 0x24 and `BuildUpgrades` at 0x28. Four bytes for a pointer plus
twelve for a container is the 16, and `m_specialPower` moves from 0x24 to 0x34 where
`isReady` (0x0049AD30) reads it. No instruction-reading, no trial pad.

The general shape: when a run of parsed fields is off by a constant, look for retail
tokens missing from our table whose offsets fall inside the gap. They are the
insertion, they come with names, and the sizes are usually forced once you know
whether each is a scalar or a container.

Two operational notes. Adding a `std::vector` member introduces destructor unwind
funclets, so `rekey_funclets.py` reports a RAGGED shift (105 labels before, 107
after, three distinct deltas) rather than a uniform one. Ragged is a warning, not a
verdict -- here all 51 matched rows in ControlBar.cpp still verified, so the
positional mapping had been right. Build before believing the warning either way.
And `next_work.py`'s size for an unclaimed candidate is a hint: it offered isReady at
93 bytes, but the body branches to 0x49ADBB, and the int3 run does not start until
146 bytes in. Check the branch targets against the claimed extent before working to it.

## AsciiString's const char* constructor is out of line in retail

`reference/shims/asciistring_outofline` existed to push `operator=` out of line;
the `const char*` constructor needed the same treatment and did not have it. Retail
calls it at 0x00888BC0, already pinned as `??0AsciiString@@QAE@PBD@Z`, while the
inline body in the shim expands every construction from a literal into an
`ensureUniqueBufferOfSize` sequence. Removing the body -- leaving only the
declaration -- turns that into the single call retail makes.

The cost is nil where it has been tried: AIStates.cpp and Anim2DTemplate_ctor.cpp
both stay at 140/140 combined with the constructor out of line, so no matched row in
either was depending on the inline expansion. Any state or template constructor that
builds an AsciiString from a literal is a candidate for the same wiring.

## State's merged base does not generalise from TurretAI to AIStates

The entry above on `TurretAIIdleState::onEnter` concluded that State gets BFME's
merged pooled-snapshot base, and predicted the same for any Zero Hour class
inheriting both. AIStates.cpp says otherwise. Give `State` the merged base there --
`class State : public Snapshot` instead of `public MemoryPoolObject, public Snapshot`
-- and six matched rows break immediately: `setAdjustsDestination`,
`AIAttackPursueTargetState::onExit`, `AIPickUpCrateState::update`,
`AIAttackMoveToState::onExit`, `AIMoveAndDeleteState::update` and
`AIEnterState::update`. Those rows match today with both bases, which is direct
evidence against the merged layout for the State that AIStates.cpp compiles against.

So the prediction is narrower than it was written: TurretAI's own State-derived
classes want the merged base, and the AI states do not. Do not apply it file-wide on
the strength of the TurretAI measurement alone.

The concrete casualty of this is `??0AITunnelNetworkGuardState@@QAE@PAVStateMachine@@@Z`
(0x001717B0, 53 bytes). With the AsciiString constructor out of line it is two
differences from exact: an instruction-scheduling swap at the top, and one extra
`mov dword ptr [esi+4], 0` -- the second vptr that the two-base State installs and
retail's single-vptr State does not. Landing it needs a State whose layout is merged
without disturbing those six rows, which is a narrower shim than the one tried here.

## The by-value AsciiString stash is not reachable by any /EH setting

Eighteen flag combinations compiled against the exact shape of
OptionPreferences::getIdealStaticGameDetail, each object checked for three things at
once: the `mov [esp+N],esp` stash, an SEH prologue, and the frame size. The result is
clean and negative.

    /EHs-c-                     no stash,  no SEH,  4-byte frame   <- retail's frame
    /EHs, /EHsc, /EHc, and
      every /EHs + /GS- /Gy /GF
      /Gf /Ob0 /Ob1 /Ot /G6
      /G7 /GR /Gd variant       stash,     no SEH,  8-byte frame
    /EHa                        stash,     SEH,     8-byte frame
    /EHs /Oy-, /EHs /Os         no stash

Retail has the stash, no SEH, and a 4-byte frame. Nothing produces that combination:
turning exceptions on always buys the stash together with a 4-byte EH state slot, and
turning them off loses both. So this is not a flag we are missing on our side, and
further flag probing is wasted effort -- either the retail translation unit was built
by a compiler that differs from the vendored one in this detail, or the stash comes
from a source construct none of the shapes tried so far models. Five class
declarations and three call-site forms are already ruled out (see re_attempts).

## Keep names-on-the-wrong-body out of the queue that hands out work

Three candidates in a row from `list_naked_candidates.py` turned out to be
unconvertible for the same reason, and the reason was already known. The decorated
name says how many bytes a callee-cleaned function must pop; the transcribed bytes
say how many it does pop. When they disagree the name is on the wrong body and no
amount of writing the C++ correctly will ever produce those bytes.

  * `?getGroup@Object@@QAEPAVAIGroup@@XZ` at 0x008F9550 -- name takes nothing,
    body does `ret 8` and returns 0/1/2.
  * `?xfer@GarrisonContain@@MAEXPAVXfer@@@Z` at 0x00853EC0 -- name takes a pointer,
    body does `ret 0`, zeroes `[esi+4..0x10]` and returns `eax = esi`: a constructor.
  * `?removeObjectBuilt@ScoreKeeper@@QAEXPBVObject@@@Z` at 0x0056E160 -- name takes a
    pointer, body does `ret 0` and frees `[this]` with element size 0x44.

`audit_ret_arity.py` has flagged all three the whole time; the picker just was not
asking it. It does now, and the exclusion is reported rather than silent (8 rows at
--max-bytes 130). The general point is worth generalising beyond this tool: a check
that exists but is not wired into the thing that hands out work will keep costing
people the same afternoon.

Fixing the rows themselves is a separate job and harder than the getSlot repoint
was, because none of the three has a direct caller to name the body from -- 0x0056E160
is reached only through a vtable, so there is no call site whose thunk settles it.

## A rebased store group is a shape signal that survives guessing

`??0StealthUpgradeModuleData@@QAE@XZ` (0x00129C10, 90 bytes) is the friendliest kind
of body there is: no calls, no branches, no vtable, 0x68 bytes of members zeroed
except `+0x5c` which starts at -1. Writing the obvious struct with the obvious
constructor gets 86 of the 90 bytes and every store correct.

The four bytes are addressing. Retail does `mov edx, eax` and stores the first six
words through `[edx+0..0x14]`, then `lea edx, [eax+0x18]` and stores the next six the
same way, and only then switches to flat `[eax+0x30..]`. That is what an inlined
sub-object constructor looks like -- `ecx` is holding the zero constant, so the
inlined `this` has to live somewhere else. Ours addresses all twenty-two words
straight off `eax`.

Three shapes were tried and all three collapse to flat addressing: two named members
of a six-word class, the same with an initialiser list instead of assignments, and a
two-element array of it. Compile flags are not the lever either -- the sibling
thunk's `/GX- /O2 /Ob2` gives byte-identical output to `/EHsc` here. Whatever keeps
that pointer alive in retail is structural and is not any of those, so the row stays
a transcription rather than a 86-byte near-miss sitting in the tree.

Worth stating as a rule: a group of stores rebased onto a second register is
evidence about how the members are *nested*, not about how they are written. When
the flat version already gets every store right, stop varying the statements and go
looking for the sub-object.

## Two things stand between LifeEventModuleInfo's constructor and exact

`??0LifeEventModuleInfo@FXParticleSystem@@QAE@XZ` (0x005FC710, 90 bytes) is worth
writing down because the reconstruction is *known*, not guessed, and still does not
land. The class is a vtable, an int at +0x04, a `GameClientRandomVariable` at +0x08
and an int at +0x14; the three stores at `[esi+8..0x10]` are that variable's default
constructor zeroing `distribution`, `minimum` and `maximum`, and the call is
`setRange(0.0f, 0.0f, UNIFORM)`. All of that reproduces.

What does not:

  * **The unwind frame.** Written plainly the constructor compiles to 41 bytes with
    no SEH at all. Giving `GameClientRandomVariable` a declared destructor brings the
    frame in and gets to 85 of 90 with every store and the call present. The last
    five bytes are the state transition: retail writes `mov byte ptr [esp+0x1c], 1`
    after constructing the member, ours writes a dword zero and never transitions.
    So retail tracks one more constructed object than our shape does.

  * **The call goes through the export thunk.** Retail calls 0x00006C58, which is the
    `export_rva` on setRange's own functions.csv row; our build resolves the same
    name to the `target_rva` 0x00096F40 and emits a direct call. There is no
    symbols.csv pin for the thunk, and adding one under a name that already has a
    functions.csv row is not obviously safe, so this needs deciding rather than
    guessing.

The second point is general: a callee with both an export thunk and a body will be
reached by whichever the *call site* encodes, and rows carrying an export_rva do not
automatically make call sites use it.

## UnitCrateCollideModuleData's destructor: three bytes of EH state encoding

`??1UnitCrateCollideModuleData@@UAE@XZ` (0x001270F0, 83 bytes) reconstructs almost
completely. The body destroys two members at +0x58 then +0x44 -- reverse declaration
order, so +0x44 is declared first -- both through 0x00887940, which is
`StringBase<char>::releaseBuffer` and the body a dozen AsciiString-destructor rows
already alias. Afterwards the base vptr goes back at `[esi]` with no base destructor
call, so the base's destructor is trivial and inlined.

Two details that took a pass each to find, and both generalise:

  * The member class needs a name of its own. `??1AsciiString@@QAE@XZ` is a
    functions.csv row on the 5-byte jump at 0x0005EE90, so a member declared as
    AsciiString resolves to the jump rather than to the body. Aliasing under a
    distinct name with a symbols.csv pin at 0x00887940 is what
    BFMEPlayerTemplateAsciiString and its siblings already do.

  * `__declspec(novtable)` on the derived class is load-bearing, and the previous
    agent's naked stub already carried it. Without it MSVC stores the derived vptr
    at destructor entry, six bytes retail does not have; retail only restores the
    base vptr at the end.

With both, the body is 80 bytes against 83 and every instruction present. The
remainder is EH state encoding: retail writes state 0 then state 1, both as dwords,
where we write 1 as a dword then 0 as a byte. Increasing state indices in a
destructor is backwards from the usual pattern, and no arrangement of two members in
one class reproduces it -- swapping declaration order is impossible without moving
the offsets, and giving the two members distinct types changes nothing. Whatever
orders those states is structural, the same conclusion the StealthUpgradeModuleData
entry above reached from a different direction.

## The ModuleData destructor family: what reproduces and what does not

Three of these were attempted in one sitting and they fail in the same shape, so it
is worth one note rather than three. Each reconstructs to within a handful of bytes
with every instruction present, and the residue is always something the compiler
decides rather than something the source says.

`??1MinefieldBehaviorModuleData@@UAE@XZ` (0x0036CE20, 100 bytes) is one inlined WW3D
Release_Ref on a refcounted pointer at +0x24: null-check it, InterlockedDecrement its
counter at +0x04 through the IAT, and on reaching zero go through vtable slot 0 with
a 1, which is what `delete` on a polymorphic pointer compiles to. Unlike the
UnitCrate destructor this class is *not* novtable -- retail stores the derived vptr
at entry and the base vptr at the end, with no base destructor call.

That reconstructs to 96 of 100. The four bytes are a second `test esi,esi / je`
before the delete, on a pointer retail has already null-checked and cached in a
register. MSVC folds that check away for us under every spelling tried: `&&` versus
nested ifs, a local versus re-reading the member, an inline `Release_Ref` member, an
inline `Delete_Instance(p)` free function with the check written out explicitly, and
/Ob1 to hold inlining back. Retail keeps it every time.

Taken with the StealthUpgradeModuleData rebasing and the UnitCrate EH-state ordering,
the pattern across the family is that the last few bytes are never reachable by
rewriting the statements. They come from how the retail translation unit was
structured -- what was a separate function, what was in a header, what the inliner
saw -- and that is not recoverable by trying spellings. When a body of this kind
stalls within single digits of exact with all instructions present, stop varying the
source and record it; the next lever is evidence about the original TU, not another
rewrite.

## WW3DErrorType is not renumbered globally, whatever Save_Info looks like

`AggregateDefClass::Save_Info` (0x00980B90) reads unambiguously: `xor bl, bl` before
`Begin_Chunk`, `mov bl, 1` after a successful `Write`, and a subobject loop that runs
while `cmp bl, 1` holds. Taken alone that says BFME numbers the assume-error value 0
and `WW3D_ERROR_OK` 1 -- the reverse of Zero Hour -- and the appealing part is that
the Zero Hour source text would then already be correct with only the values changed.

It is refused by evidence elsewhere. Reordering the enum in
`Code/Libraries/Source/WWVegas/WW3D2/w3derr.h` breaks four matched rows in
meshmdlio.cpp -- `read_texture_stage`, `read_material_pass` and two neighbours --
each by a single byte in a jump displacement, meaning the Zero Hour numbering is what
those bodies were built against. A per-file enum is not a real thing, so one of the
two readings is wrong, and the four matched rows outweigh the one unmatched function.

The likeliest resolution is that `bl` in Save_Info is not a WW3DErrorType at all: the
virtual it calls through `[edx+0x24]` may return a Bool, with the 0/1 being FALSE and
TRUE and the conversion happening at the return. That would explain the byte-width
operations too, which are the other thing the enum theory never accounted for --
retail keeps this value in `bl` throughout while an int-sized enum gives `ebx`, and
the decorated name `?AW4WW3DErrorType@@` forbids changing the type to something
byte-sized.

So: do not renumber this enum, and treat a Save_/Load_ status variable held in a byte
register as evidence that the source variable is not the enum it is eventually
returned as.

## Save_Info's status is a byte, and that is the whole remaining gap

Following the entry above to its end: holding `ret_val` as `unsigned char` instead of
`WW3DErrorType` reproduces everything the enum theory could not. `xor bl, bl`,
`mov bl, 1`, `cmp bl, 1` and `mov bl, al` all match, and the subobject assignment is a
raw low-byte copy rather than a `test`/`setne` -- so `Save_Subobject`'s value is taken
as a byte, not converted from an int.

That leaves 111 bytes against 109, and the two are the return: retail does
`mov al, bl` and leaves the rest of eax alone, which is what MSVC emits when the
declared return type is byte-sized. Ours does `movzx eax, bl` because the declared
type is an int-sized enum. Both cannot be true of the same declaration, and the enum
cannot be byte-sized because meshmdlio.cpp's matched rows depend on the int one.

The reading that fits every observation is that BFME's Save_Info does not return
WW3DErrorType at all -- it returns a byte type, and the row's name came from Zero
Hour. If so the decorated name should be `_N` rather than `?AW4WW3DErrorType@@`, which
is checkable against the vtable slot and is the next step rather than another cast.
Reverted; a two-byte near-miss is still a near-miss.

## What actually blocks the naked backlog, counted

972 rows still carry a `__declspec(naked)` body. Sorting them by the first blocker
each one hits:

    625  64.3%  172,346B  SEH prologue -- needs unwind funclets
    224  23.0%   52,272B  no known blocker
     59   6.1%   27,352B  name contradicted by its own bytes (tools/screen_identity.py)
     44   4.5%   13,290B  by-value class stash, which no /EH setting reproduces
     20   2.1%    6,300B  ebp frame, so not /O2 as this build is configured

Two things worth taking from that. The SEH bucket is nearly two thirds of the backlog
and a third of its bytes, so learning to reproduce unwind funclets is worth more than
any number of individual conversions -- everything else is a rounding error beside it.

And the 224 unblocked rows are a real pool, not a residue. I had previously concluded
the easy candidates were exhausted; that was wrong, and wrong in an instructive way.
The sweep behind that claim also demanded a size window and an arity match, and the
arity check silently skips every row whose argument list cannot be sized from the name
-- classes by value, templates, varargs. Those skips are correct as "no opinion" for
flagging, but treating them as disqualifying turned a wide pool into a handful of rows.
A filter built from several signals inherits the narrowest one; check what it excluded,
not just what it returned.

## Probe in the context the code actually appears in -- and detect precisely

The blocker on two module-data constructors is that retail materialises each member's
address before storing -- `lea ecx,[esi+0x70]` then stores through ecx -- where my source
folds onto the object pointer. Probing source forms for this produced two wrong answers
in a row, each wrong for its own reason, and both are worth keeping.

The first probe compiled the constructor standalone and reported that several forms give
the register addressing. They do -- standalone, `this` already arrives in a register, so
the question was never asked. The real constructor is inlined into a factory after a
`new`, which is a different question entirely.

The second probe fixed the context but detected by searching the whole object for bytes
like `89 01`. Those occur in vtables and in neighbouring functions, so it reported success
for inline member constructors when there was none. Detecting the ABSENCE of the folded
form (`mov [esi+0x70], reg`) and counting `lea`s at the member offsets says the opposite:
across seven layouts -- same and different member types, int members, a nested type with
its own constructor, the +8 subobject as a base and as a member, with and without a
leading pad -- MSVC coalesces the two adjacent three-word members into one run of six
stores through the object pointer every single time. Retail keeps two groups, each with
its own `lea` and its own zeroing register.

So the state is: no source form tried reproduces this, and the reason is the coalesce, not
the addressing. Two rules fall out. Probe in the context the code actually appears in, and
search for the thing that would DISPROVE the result rather than the thing that would
confirm it -- a substring that can occur incidentally is not evidence.

## Group locals into the struct they came from to fix frame layout

W3DCameoMovieDraw came down to two displacement bytes: four out-parameters that retail
reaches high in the frame and my version placed the other way round. Written as four
loose Ints the pairs came out adjacent but in the wrong order, and swapping the
declaration order did not move them -- which looked like confirmation of the older note
here that local slot assignment is not steerable.

It is steerable, just not by declaration order. Declaring the position and size as two
ICoord2D structs -- which is what Zero Hour uses -- fixed it outright. A struct forces
both the adjacency and the relative order of its members, where separate locals leave
both to the allocator and it has its own opinion.

So when a body is otherwise byte-identical and only stack displacements differ, the
question is not what order the locals were declared in but whether they were locals at
all. Two Ints passed by address to a pair of accessors is very often one small struct in
the original, and the frame layout is the evidence for it.


## Repeated initialiser blocks are one member type, not many fields

ScriptList::updateDefaults allocates 0x4C bytes and then writes, in order, zero at +4
and +8, the vtable at +0, zero across +0x0C..+0x20, -1 at +0x24 and +0x28, zero across
+0x2C..+0x40, and -1 at +0x44 and +0x48. Written out as a flat class that is nineteen
fields to invent names and initialisers for, and getting any of their widths wrong
shifts everything after it.

Read as structure it is three declarations. The two 0x20-byte runs are byte-for-byte the
same initialiser -- six zeros then two -1s -- so they are one member type used twice, not
sixteen fields that happen to coincide. The stores at +4 and +8 land before the vtable
store, and MSVC always writes the vptr after the base constructors and before the member
initialisers, so those two belong to a base with no virtuals of its own, which MSVC
places at +4 with the derived vfptr taking offset 0. That leaves 4 + 8 + 0x20 + 0x20 =
0x4C exactly, so the size confirms the reading before anything is compiled.

The general rule: within a constructor the store order is base, then vptr, then members
in declaration order, and it is a total order you can invert. A store that precedes the
vptr came from a base; a repeated run of identical stores came from a repeated member
type. Both of those are structure the disassembly hands you for free, and both are the
kind of thing that costs several builds to find by trial if you start from a flat class.

Built byte-exact on the first attempt -- the first candidate this session chosen by
predicting which blocker family it would land in before writing any of it, rather than
discovering the blocker after two or three builds.


## A function-local static folds its own address, and that changes the whole body

ConcreteModuleClass<Tag>::getInstance is the MSVC function-local static idiom, and the
constructor it inlines is already byte-exact as its own row, so writing getInstance as
`static X theInstance; return theInstance;` looked like it should fall straight out.
It does not, and the reason generalises.

Retail materialises &theInstance into edx once and then stores from registers -- a3 for
the value in eax, 89 15 and 89 0d for edx and ecx. The rebuild folds the static's address
into every store as a c7 05 immediate, because to the compiler that address genuinely is
a compile-time constant. Fifteen bytes longer, every load otherwise identical and in the
same form.

The second-order effect is the interesting part. The constructor writes the base vtable
at +0 and then immediately overwrites it with the derived vtable. Retail eliminates the
first store; the rebuild keeps it. That is the same cause, not a separate one: once each
store is an independent absolute-address instruction rather than a chain through one
register, the redundant one no longer presents as dead in the same way. One allocation
decision moved both the encoding and the dead-store elimination.

So this joins the immediate-versus-register split as a blocker family, and it is worth
recognising early: whenever the target holds an object's address in a register across
several stores and the rebuild emits absolute forms, the difference is not going to be
fixed by rephrasing. Rewriting the inlined constructor to store through a named local
instead of `this` produced byte-identical output, which is the confirmation -- when two
genuinely different spellings compile to the same bytes, the lever is not in the source.

Also, second validation of the funclet re-key: tools/rekey_funclets.py reported RAGGED
again on this translation unit and was again correct, with all 559 other rows still
verifying. The warning flags a non-uniform shift, not a failure.


## Where a constant lives is the compiler's decision, and it cascades

removeAllShadows walks three shadow lists, clearing each head and setting a byte flag
on every node. The structure fell out of the disassembly immediately and the rebuild
reproduced all of it. The whole delta is that retail materialises zero into edx and uses
it nine times -- `cmp eax,edx` for six null tests and `mov [ecx+N],edx` for three head
clears -- where the rebuild emits `test eax,eax` and `c7` immediate stores.

The cascade is what makes this worth recording. Because retail spent edx on the zero,
the constant 1 for the flag had to go somewhere else, so it landed in ebx, so the
function pays a push and a pop it would not otherwise need. One allocation decision
changed the encoding of nine instructions, the choice of two registers, and the
prologue. Reading the diff as several independent problems would be wrong; it is one.

Three genuinely different source structures were tried: three inline loops, a named
null constant used by every site, and a helper taking the head by reference and inlined
three times. All three compiled to byte-identical output.

CORRECTION. This section originally went on to say that adding /O1 to the per-file cl
directive changed nothing either, and concluded the lever was not in the source. The
/O1 test was invalid: the file had been rewritten with PowerShell's
`Set-Content -Encoding UTF8`, which prepends a UTF-8 BOM, and a BOM stops build.py
matching `// cl:` on line 1, so the directive -- new flag and original flags alike --
was silently dropped. With /O1 actually applied the body changes substantially and
picks up retail's zero-in-register form: xor edx,edx, mov [ecx+N],edx, cmp eax,edx.
So this is a flag axis, not a dead end. See "The optimisation level decides which
constants get registers" below.

The source-spelling half of that still holds: three genuinely different spellings
compiling to identical bytes does mean no rephrasing will help. What does not follow --
and what was wrongly concluded here -- is that nothing will help. Identical output
across spellings only rules out the source; it says nothing about the flags, and the
flags turned out to be exactly where the difference lived.

Note also how the screening tool failed. tools/screen_blockers.py rejects rows carrying
a known blocker signature, and its first version matched the function-local static guard
as a byte load followed directly by `test al,cl`. MSVC puts `mov eax,1` in between, so
the pattern never matched and the entire family -- the one proven blocked an hour
earlier -- was reported as clear. It was caught only by running the screener against a
row already known to be blocked. A detector that has never been shown a true positive
is not yet evidence of anything.


## Check whether a family member is typical before reusing the family's template

friend_newModuleData is the largest family in the ledger: 269 rows across 141 source
files, and 140 of those files are already clean C++. Exactly one is still naked, which
looked like the easiest remaining conversion in the project -- copy the neighbour and
change the names.

It is not, and the reason is worth knowing before reaching for any family template. The
other 140 declare the module data constructor and never define it, so MSVC has nothing
to inline and emits a call, which is what their retail bodies contain. This one's retail
body inlines the constructor instead: the base sub-object is built through
lea ecx,[esi+8], the vtable goes in at +0, and two three-word member runs follow at
+0x70 and +0x7C. Same family, opposite requirement.

Defining the constructor in the translation unit did not produce the inlined form. MSVC
emitted an out-of-line call anyway and wrapped the allocation in an unwind frame so that
operator delete runs if a member constructor throws -- an SEH prologue retail does not
carry. Four builds, no movement.

One loose end recorded rather than asserted: removing /EHsc and then setting /EHsc-
explicitly changed the output by not one byte, which should not be true if the flag is
reaching the compiler. Worth confirming that the per-file `// cl:` directive is applied
before anyone spends more builds on the exception-handling axis, here or elsewhere.

The layout is settled and costs nothing to reuse when that is resolved: size 0x88, base
sub-object at +8 whose constructor is pinned at 0x0000F0A6, vtable 0x0108F4F0, field
parse table at 0x004102C6.

A separate process note. The cache line `Compile: 0 of 1 TU(s) (deps-cache: 1 current)`
appears when a re-run reuses an object, and it is easy to read a diagnostic re-run's
cache hit as evidence that an earlier real build never happened. build.py keys the cache
on the source hash and the full command fingerprint, so an edited source always
recompiles. Read that line against the run that actually did the work.


## The optimisation level decides which constants get registers

removeAllShadows differed from retail only in how constants were materialised: retail
holds zero in edx and one in bl, the rebuild emitted immediates. Three source spellings
could not move it. The optimisation flag moves it immediately, and not in the direction
a single switch would suggest:

  /O2 (base)   one in a register (mov dl,1), zero as c7 immediates, loops aligned
  /O1, /O2 /Os zero in a register (xor edx,edx, mov [ecx+N],edx), one as an immediate,
               no loop alignment
  retail       BOTH in registers, and loops aligned

So retail is not reproduced by either setting. Favour-size promotes the zero, favour-
speed promotes the one and aligns the loops, and retail has all three at once. /G6
changed nothing on this body. That is a real, narrow, still-open question, and it is
worth far more than another round of respelling: the same mixture shows up in the
immediate-versus-register family generally, which is the single largest blocker
recorded here after SEH.

Two process points came out of finding this.

A UTF-8 BOM silently disables the per-file `// cl:` directive, because build.py matched
`line.startswith("// cl:")` and the BOM sits in front of the slashes. Nothing warns; the
file simply compiles with base flags. Windows PowerShell's `Set-Content -Encoding UTF8`
writes a BOM by default, so any flag experiment driven from PowerShell was testing
nothing. build.py now reads with utf-8-sig, and the five files in the tree that already
carried a BOM -- every one of them with a `// cl:` line being ignored -- have been
stripped and reverified.

And the general lesson: an experiment that changes nothing is only evidence once the
experiment is known to have run. Four builds were spent concluding a flag did not
matter, when the flag was never passed. Before believing a negative result, prove the
input reached the thing under test -- here, a `#ifndef GUARD / #error` in the source
answered it in one build.


## A minimal reproducer is worth more than another blocked row

??0StealthUpgradeModuleData@@QAE@XZ is 90 bytes of straight-line stores with no calls
and no branches, and the rebuild gets 86 of them exactly right. The tail from +0x30
onward -- ten zeroed words, a byte store, a -1 written as an immediate, two more zeroed
words -- is byte-identical, which incidentally confirms the heuristic is not simply
"constants go in registers": retail keeps the zero it uses twenty-eight times in ecx and
still writes the single -1 as an immediate, exactly as the rebuild does.

The whole difference is four bytes. Retail walks the two six-word runs at +0 and +0x18
through a materialised pointer -- mov edx,eax, then lea edx,[eax+0x18] -- while the
rebuild folds both into [eax+disp] addressing off this. Nothing else differs anywhere in
the function.

That makes this row worth keeping as the reference case for the materialised-versus-
folded family, which is the same divergence that stopped friend_newModuleData. It is
far more useful than a normal blocked row: no calls to pin, no branches, no relocations,
no unwind, so a single build gives an unambiguous yes or no on any hypothesis. Anyone
testing a flag idea should try it here first and only then on a real candidate.

What has already been ruled out on it: two separately named members and a two-element
array of the same type both compile to byte-identical output, so the shape is not
source-steerable; and /EHsc, the base /O2, and the proven /GX- /O2 /Ob2 all produce the
same bytes, so it is not any of the settings the tree has already established.

Worth noting retail's form is the larger one -- 39 bytes against 35 -- so whatever
selects it is not favouring size, and /O1 is therefore unlikely to be the answer here
even though it was decisive on removeAllShadows.


## Two reusable levers: the element destructor, and signedness

??0FastAllocatorGeneral@@QAE@XZ went from nothing to three of its four divergences
solved in three builds, and two of the fixes generalise to any similar row.

The leading call is the vector constructor iterator ??_L. Its arguments are the whole
layout, free of charge: (this, 0x18, 0x80, ctor, dtor) says the first member is an array
of 128 objects of size 0x18 at offset 0, which is why the zeroed run that follows starts
at exactly +0xC00. Reading the helper's arguments settled the class in one step where
guessing offsets would have taken several builds.

Getting that helper emitted at all is the first lever. A member array of class type is
built with an inline loop calling the element constructor unless the element type has a
destructor -- then MSVC needs cleanup for a partially constructed array and switches to
??_L, passing the destructor as the fifth argument. So a call to ??_L in the target is
positive evidence that the element type has a declared destructor, and declaring one is
what makes the rebuild match.

The second lever is signedness, which is visible in a single byte. Retail compares the
running allocation size with jb, the unsigned branch; the same source with a signed int
gives jl. A `72` where the rebuild has `7c` is not a scheduling difference or a register
choice, it is the declared type of a local, and it is worth checking for directly
whenever a comparison is the only thing out of place.

What is still open is narrow and precisely stated: retail zeroes the 128-entry free list
with an explicit store loop -- lea, a down-counter in edx, then mov [eax],ecx / add
eax,4 / dec edx / jne -- while MSVC recognises the fill and emits rep stosd. An indexed
for loop, an explicit pointer walked with a do-while down-counter, and /Oi- all produce
rep stosd; /Oi- governs intrinsic functions like memcpy, not this loop-idiom
recognition, so it is the wrong knob. Everything else in the function, including the
whole second loop and the tail, already matches byte for byte.


## Bounding a blocker is a result: rep stosd lives inside /Og

The one thing still separating ??0FastAllocatorGeneral@@QAE@XZ from byte-exact is a
128-entry zero fill that retail writes as an explicit store loop and MSVC turns into
rep stosd. This pass bounded it rather than solved it, and the bound is worth recording
because it closes several axes at once.

Source form does not control it. An indexed for loop, an explicit pointer walked with a
do-while down-counter, and -- the most promising idea, since retail's shape is exactly
what MSVC's own array construction emits -- making the free list an array of a small
class whose constructor zeroes its member, all produce identical bytes. That last one is
the informative failure: MSVC builds the member array with an inline loop, inlines the
element constructor into it, and then recognises the resulting fill. The recognition
happens after inlining, so no amount of hiding the fill behind a constructor escapes it.

Flags do not control it either, within what is reachable. /Oi- governs intrinsic
functions like memcpy, not this loop idiom. /G5 changes nothing, so it is not a
processor-target decision. /Og- does remove the rep stosd -- which pins the transform
inside the global optimiser -- but /Og is load-bearing for everything else in the
function, and with it off the body degrades to an ebp frame with stack locals and
nothing else matches. There is no middle setting.

And the compiler itself is not an axis: only the vs2003 toolchain is vendored, so
"maybe this file was built with a different compiler" cannot be tested here even though
it remains the most likely explanation.

So the honest statement is that no configuration reachable from this tree reproduces
this loop, with everything else in the function -- the ??_L call, the four field stores,
the entire second loop and the tail -- already byte-identical. That is a much more
useful thing to leave behind than "blocked": it tells the next person which four ideas
not to spend builds on.


## The member-init list versus the constructor body is a real ordering lever

Every previous attempt to steer statement order in this project failed, and the note
here has been that the source cannot control scheduling. That is too strong. There is
one control that works, and W3DDebrisDraw's constructor is the demonstration.

Its retail body writes members at +0x10 through +0x24, then +0x34 through +0x44, and
only then +0x28 through +0x30. Those last three sit in the middle of the layout, so the
order is not declaration order and not address order. Writing every field as a plain
assignment in the constructor body reproduces none of it -- MSVC clusters the stores its
own way.

The explanation is that MSVC emits member-init list entries in declaration order, ahead
of the constructor body. So a field whose stores appear out of layout order in the
target was assigned in the body while its neighbours were in the init list. Moving
exactly those three fields into the body and leaving the rest in the init list
reproduced retail's ordering exactly, all fourteen stores in the right sequence.

That is worth remembering as a diagnostic and not just a fix: an out-of-order run of
stores in a constructor tells you which fields the original author assigned in the body.

Two smaller things fell out of the same row. A REL32 to a thunk resolves by decorated
name, so the base class has to be named for whatever is pinned at that address -- here
??0DrawableModule@@ among eight names ICF-folded onto 0x00002874. And an offset written
twice, first with one vtable and then another, means a base constructed inline: its own
vtable goes down first and the derived class overwrites it.

What remains is narrow and, again, scheduling. MSVC sinks every c7-form immediate store
-- both vtable pointers and the single -1 -- to the end of the function, where retail
leaves them in program order among the register-sourced zero stores. Both versions
contain the same instructions in the same count; only the order differs. /GX- /O2 /Ob2
does not change it. This is the immediate-versus-register family showing up a third way:
not encoding, not register allocation, but placement.


## vptr-store sinking is the blocker in front of the module-constructor family

Two constructors this session reached the same wall from different directions, and
together they characterise it well enough to name.

MSVC's canonical constructor order is: call the base constructors, write the derived
class's vtable pointers, then initialise members. Retail follows that exactly. The
rebuild instead sinks every compiler-generated vtable store past the member
initialisation to the end of the function, because nothing between them dispatches
virtually and the stores are free to move.

SlavedUpdate is the clean demonstration. It matches byte for byte from the prologue
through the last inlined base constructor -- the base call, three inlined base
constructors writing their own vtables at +0x0C, +0x10 and +0x20, the two -1s sharing
ecx through `or ecx,0xffffffff`, the zeros sharing eax -- and then diverges only in
where the four derived vtable stores sit. Same instructions, same count, same
registers. Placement alone.

W3DDebrisDraw shows the identical behaviour with two vtables rather than four, so this
is systematic rather than a scheduling coincidence. /EHsc, /O1 and the proven
/GX- /O2 /Ob2 all sink; /O1 additionally degrades the prologue, so it is strictly worse.

Two layout diagnostics are worth keeping from these rows, both free. An offset written
twice with two different vtable values is a base constructed inline: its own vtable
lands first and the derived class overwrites it -- so counting doubly-written offsets
counts the inline bases and gives their positions. And the gaps between those offsets
give each base's size, which fixes the whole layout before a line is written.

The scope matters for deciding whether to keep pushing: constructors of the form
??0X@@QAE@PAVThing@@PBVModuleData@@@Z number 240 rows across 222 source files, 139 of
them still naked. This one optimisation stands in front of most of that. It is a better
target than any individual row, and it is the strongest reason yet to suspect the
retail build used a compiler configuration this toolchain cannot express.


## Read a naked row's literals and its callers before trusting its name

A __declspec(naked) row byte-matches whatever name is attached to it, so the gate never
tests identity. tools/screen_identity.py catches the signature-level contradictions --
return width, stack cleanup -- but it cannot see meaning, and meaning is where this one
went wrong.

?validateAudio@ThingTemplate@@IAEXXZ at 0x0013E2F0 is sixty bytes that set the
AsciiString at +0x4c to "shadows" or "shadow" -- literals of length 7 and 6, passed to
?set@AsciiString@@QAEXPBDH@Z -- choosing between them on a test of a vector of 36-byte
elements. There is no audio anywhere in it. It is reachable only from
?parseObjectDefinition@INI@@ via the thunk at 0x0001D44E, and no vtable slot holds its
address. And Zero Hour's validateAudio is wholly inside #if defined(_DEBUG) ||
defined(_INTERNAL) and contains nothing but assertion macros, so a release build has no
such function at all.

Three cheap checks did that, and all three are worth running on any naked row before
spending build time on it: read its string literals, list its callers, and compare the
reference implementation's build-configuration guards. None of them needs a compile.

The row is flagged rather than tombstoned. The evidence does not support the pair, but
the correct name is not known yet, and tombstoning a row someone else may be anchored to
on the strength of "this looks wrong" would trade one error for another.

One mechanical trap found on the way. Function addresses in this project are RVAs, but
the absolute operands inside the instructions are virtual addresses, and the image base
is 0x00400000. Reading a string at the address printed in a disassembly listing without
subtracting the base silently lands outside every section -- which at least fails loudly.
Getting it wrong in the other direction, on an address that happens to map, would not.


## Two screeners that do not talk to each other will hand you a bad row

tools/screen_identity.py has been reporting ~60 naked rows whose bytes contradict their
own decorated names. tools/screen_blockers.py ranks naked rows by conversion difficulty.
Neither consulted the other, so a row already known to be misnamed was offered as a
clean candidate, chosen, and read in full before the contradiction surfaced.

?Unregister@SimpleSceneClass@@UAEXPAVRenderObjClass@@W4RegType@SceneClass@@@Z ends in
ret 4. Its name takes a pointer and a RegType enum, which is eight bytes of arguments,
and a callee-cleaned function pops exactly its argument list. The pair cannot be right,
and screen_identity had already said so. screen_blockers now runs that check and drops
such rows, which is a two-line change that would have saved most of a pass.

The body is not Unregister at all. It notifies the object through a virtual at +0x68,
removes it from lists at +0xbc, +0xd4, +0xec and +0x5c, and releases references twice.
Zero Hour's SimpleSceneClass::Remove_Render_Object is virtual, takes exactly one
RenderObjClass pointer, and does that work -- and that name appears nowhere in the
ledger. It is the obvious candidate.

It is recorded as a candidate and not applied. The arity contradiction is a proof that
the current name is wrong; it is not evidence that any particular replacement is right,
and those are different claims. Renaming on the strength of "this is the obvious one"
would replace a detectably wrong row with an undetectably wrong one -- strictly worse,
because the next screener pass would no longer flag it.

The general point, now true of three tools here: a check is only worth having if
whatever selects work actually consults it. screen_identity found this row weeks of
passes ago and nothing was reading it.


## A vtable slot plus its twin identifies a virtual almost for free

?Unregister@SimpleSceneClass@@ was provably misnamed -- ret 4 under a name whose
arguments size to 8 -- but knowing a name is wrong does not supply the right one. Four
cheap checks did, none of them a compile.

Search .rdata for the function's virtual address. It appeared at slot 3 of six
different vtables, and the neighbours were shared across all six while slot 1 varied,
which identifies slot 1 as the per-class destructor and everything below it as
inherited implementations. That fixes the slot numbering without needing to know how
many virtuals the base declares.

Then read the neighbours. Slot 2 notifies the object through a virtual at +0x64, calls
0x009DBF60, and increments the object's refcount. Slot 3 notifies through +0x68, calls
0x009DC100, and decrements it. Add and Remove, identified by behaviour rather than by
position -- which matters, because the position argument alone was ambiguous once BFME's
class turned out to declare more virtuals than Zero Hour's.

Then check what the body opens with. ?Remove_Render_Object@SceneClass@@ was already in
the ledger at 0x00942C20: fifteen bytes that tail-call the object's virtual at +0x68.
The body under investigation begins by doing exactly that inline, which is the base
class call the derived override is documented to make.

And confirm the gap. The SceneClass base was claimed; the SimpleSceneClass override was
absent. A body that behaves like the missing override, in the slot the missing override
would occupy, is the missing override.

Any one of those would be suggestive. Together they are a proof, and that distinction is
what separates a correction from a guess. The row was renamed, the impossible pair
tombstoned, and screen_identity's contradiction count went from 60 to 59.

The twin at 0x00942FA0 is still unclaimed, which is the obvious next thing to name.


## Vtable position identifies a function that is unidentifiable alone

Following one correction outward produced four functions over the last few passes, all
identified by position and by their twins rather than by disassembling them cold. That
is a method, not a coincidence, so it is now a tool: tools/vtable_gaps.py scans .rdata
for runs of code pointers, attributes each slot to a ledger row, and ranks the unclaimed
slots by how many named neighbours bound them.

One detail decides whether the output is usable. Most claimed rows in this image are
gen-thunks carrying synthetic names like ?j_00035eb8@@YAXXZ, and counting those as
"named" makes nearly every table look fully identified while burying the handful of gaps
that sit between real methods. Excluding them changed the top of the ranking completely.

Its first suggestion converted. Slot 2 of Pipe's vtable was unclaimed, bounded by Flush
at slot 1 and Put_To at slot 3. The body is five bytes -- load the vtable, jump to slot
1 -- and PIPE.H declares, inline, `virtual int End(void) {return(Flush());}`. Position
gave the candidate, the tail-call target confirmed it, and the reference header settled
the spelling. No disassembly of the body was needed to know what it was.

One MSVC detail cost the first build. Writing End inline in the class, exactly as the
header does, produced no symbol at all: an inline virtual is only emitted when something
forces it, and nothing in the translation unit constructs a Pipe. Defining it out of
line emits it, and the bytes are identical either way. So a faithful transcription of
the original declaration is not always the one that compiles to a checkable object --
match the header for layout, but define the function you are claiming.

Worth noting what this method is good for. It finds functions whose *identity* is the
obstacle, which is a different backlog from the one the byte-level blockers govern. 729
unclaimed slots currently sit next to a real name.


## A reciprocal multiply hands you sizeof(T) exactly

VectorClass<RenderDeviceDescClass>::ID has two overloads. Slot 4, taking a const
reference, was already claimed; slot 5 was not, and its body divides the byte distance
between a pointer argument and the Vector member by the element size -- which is the
pointer overload, `((unsigned long)ptr - (unsigned long)Vector) / sizeof(T)`.

Writing that byte-exact needs sizeof(T), and the division supplies it. MSVC compiles it
as a reciprocal multiply: load 0xB30F6353, multiply, keep the high dword, shift right by
ten. Only one divisor makes that sequence agree with integer division across the whole
range, and a short search finds it: 1464. Declaring RenderDeviceDescClass as 1464 bytes
of padding was enough; nothing about its actual members mattered.

So a magic constant is not an obstacle to reproducing a divide, it is a measurement of a
type whose definition you do not have. Solve for the divisor rather than trying to
reconstruct the class.

Two smaller results from the same pass.

vtable_gaps now rejects candidates whose first sixteen bytes carry an SEH prologue. An
identity found by position still has to be written as C++ afterwards, and the SEH family
has no source-level fix, so offering those wastes the pass -- which is exactly what
happened before the filter went in. Same integration mistake as screen_blockers not
consulting screen_identity, made twice now: a tool that selects work has to know what
the other tools already rule out.

And a caution about slot inference. SimpleVecClass<Vector3>::Resize looked like the
obvious name for an unclaimed slot bounded by that class's destructor -- but it is
already claimed, at a completely different address, because the same template is
instantiated in several translation units and the vtables hold different copies. Before
inferring a name from a slot, check the name is not already live somewhere else.


## Learn a template's vtable shape once and every instantiation opens up

VectorClass has a fixed six-slot vtable -- destructor, operator==, Resize, Clear,
ID(const T&), ID(const T*) -- and once that order is established from one vtable where
most slots are named, every other instantiation in the image can be read off by
position. Two more conversions came out of it this pass with no cold disassembly: slot 3
was Clear and slot 5 the pointer overload of ID, in a vtable whose other four slots were
already named.

Two details make the template case easier rather than harder.

The element size is visible in the divide. A pointer-element instantiation shifts right
by two; a class-element one does a reciprocal multiply whose divisor is recoverable, as
with the 1464-byte element earlier. So the same source text serves every instantiation
and the only thing to determine is sizeof(T), which the body states.

And identical instantiations fold. The bodies claimed here appear in several vtables at
once because pointer-element vectors compile to the same code, which is why a single
vtable can show Resize named for one instantiation and ID named for another -- the names
in a vtable listing are whichever instantiation happened to be claimed first, not
evidence about the class the table belongs to. Read the slot order, not the names.

The practical consequence: template families are the cheapest place to convert, because
the cost is understanding one class rather than one function. Worth preferring them over
individually-interesting rows while the ranking still has them.


## Template instantiation names are not reliably tied to addresses here

The last pass established VectorClass's six-slot vtable order and used it to convert two
slots, and the obvious next step was to scale it: 25 unclaimed ID(const T*) bodies sit in
the image, all byte-identical four-byte-element copies, each presumably belonging to a
different instantiation. Naming them needs the instantiation, and the method used so far
was to read it off a named neighbour in the same vtable. That method does not hold up.

Three findings, in order of how badly each damages it.

A single vtable carries names from four different instantiations. Table 0x011BC44C has
operator== named for VectorClass<int>, Resize for VectorClass<VertexMaterialClass*>, ID
for VectorClass<FontCharsBuffer*>. Identical instantiations fold, so the ledger name on
a slot records which instantiation somebody claimed first, not which class owns the
table.

The constructor evidence contradicts the body evidence. ??0?$VectorClass@G@@ stores that
same vtable -- unsigned short, a two-byte element -- while its slot 5 divides by four. A
two-byte element cannot do that, so at least one of those two attributions is wrong, and
nothing in the image says which.

And a claimed row can sit outside every vtable. Resize for VectorClass<FontCharsBuffer*>
is a genuine body at 0x0005E610, not a thunk, referenced by no vtable slot at all -- a
duplicate instantiation the linker kept while the vtables point at the folded copy.

RTTI would settle all of it, and is not available: the image is built with -GR-, so there
is no complete object locator behind these vtables.

The two rows already claimed this way are body-compatible -- Clear does not depend on the
element type at all, and the ID overload's shr 2 matches a four-byte element sitting at
slot 5 beside the slot 4 overload of the same name -- so they are recorded with the
caveat that the instantiation is inherited rather than proven, instead of being quietly
left to look verified.

The rule this leaves: vtable position is sound evidence for *which method* a body is, and
that is what it was introduced for. It is not evidence for *which instantiation* a
templated body belongs to. Twenty-five plausible-looking claims were one step away, and
plausible is the wrong standard for a ledger other people build on.


## Two more filters, and a way to tell a live body from a dead duplicate

vtable_gaps was reporting mostly noise, for two separate reasons now fixed.

Runs of .rdata dwords that merely fall inside the code range are not vtables. The tell is
free: a real vtable slot points at a function's entry, never into the middle of one. So
if any slot resolves to the interior of a claimed function, the whole run is data and gets
discarded. That alone took the candidate list from 432 to 113.

And template gaps are excluded by default now, per the previous pass: a slot identifies
which method a body is, not which instantiation it belongs to.

What the cleaned-up ranking then produced is worth recording as a technique in itself.
Vector3SolidSphereRandomizer had two gaps; v3_rnd.h gives the base's virtual order as
destructor, Class_ID, Get_Vector, Get_Maximum_Extent, Scale, Clone, so the slot after the
destructor is Class_ID and the one between Get_Vector and Scale is Get_Maximum_Extent.
Both bodies confirm it without reference to position -- one returns a constant unsigned
int, the other loads a float member onto the x87 stack, which is exactly how each
declared return type leaves a function.

Class_ID converted. Get_Maximum_Extent could not, because that name is already claimed --
at 0x0010BD90, a byte-identical four-byte body. Which raises the question of which copy is
real, and there is a clean answer: count vtable references. The claimed address is
referenced by no vtable slot anywhere in the image. The unclaimed one at 0x00B02050 is
referenced by exactly slot 10 of the SolidSphere vtable. The compiler emitted this
function in several translation units, the linker kept more than one copy, and only one of
them is ever dispatched to.

That generalises into an audit worth building: a claimed virtual method whose address
appears in no vtable, while an identical body elsewhere does appear in one, is anchored to
a dead duplicate. Recorded as a lead rather than acted on -- repointing another
contributor's row is not something to do on the strength of a single pass, and the
existing claim is not exactly wrong either, since both copies are genuinely that
function's code.


## Look for the reference header by class, not by the file you expect

GridCullSystemClass's vtable had three unclaimed slots after nine named ones, and the
obvious reference file -- cullsys.h, which defines the base CullSystemClass -- does not
mention the derived class at all. It would have been easy to conclude no reference
existed and either guess or move on. Grepping the whole tree for the class name found
gridcull.h immediately, and with it the declaration order.

That order settled slot 9 in one step: the header declares
`virtual int Get_Object_Count(void) const { return ObjCount; }` immediately after Save,
and slot 9 -- the first gap after Save at slot 8 -- is a four-byte getter returning the
int member at +0x54. Converted first build.

Two details from the same vtable worth keeping.

Overloads appear in reverse declaration order. The header declares Collect_Objects for
Vector3, AABox, OBBox then Frustum; the vtable holds Frustum, OBBox, AABox, Vector3.
That is normal for an overload group and would look like a mismatch to anyone checking
declaration order naively.

And slots 10 and 11 sit past the end of the reference's list, so they are additions this
build made and the reference cannot name them. Recognising where the reference stops
being evidence is as useful as reading it -- those two were left alone rather than
guessed at from their bodies.

Separately, the pre-commit hook now rejects a staged tools/*.py that will not parse. The
previous pass committed a tool with an unterminated string literal, cleanly, because the
hook byte-verifies Code/ sources and checks ledger integrity and a script is neither. One
ast.parse per staged tool closes it; verified by staging a deliberately broken file and
watching the commit fail with its filename and line number.


## An unclaimed vtable slot is not always unconverted work

ParticleEmitterDefClass looked like a rich seam: nine unclaimed slots in one vtable and a
reference header giving the full declaration order. Two of the gaps are thirteen-byte
inline setters sitting exactly where the header puts Set_Merge_Abort_Factor and
Set_Texture_Tile_Factor, writing consecutive floats at +0x214 and +0x218 -- confirmed by
the already-claimed Set_UV_Offset_Rate next door writing +0x21C and +0x220.

Both names are already in the ledger. Not at these addresses: Set_Merge_Abort_Factor is
claimed at 0x0021A220 and Set_Texture_Tile_Factor at 0x00253D20, and the bodies there are
byte-identical to the ones the vtable actually dispatches to. The same split shows up for
Set_Burst_Size, Set_Elasticity, Set_Emission_Rate and Set_Gravity.

So the seam is not new work at all. These functions are named; they are just named
against copies nothing calls, and the live copies then present as gaps. vtable_gaps now
detects that -- a slot whose bytes match an already-claimed row, ending at the same int3,
is labelled a duplicate and held back -- which takes its candidate list from 109 to 99.

Two things follow that are worth keeping separate.

The ranking overstated available work, and would have kept doing so. Ten of its
candidates were functions the project had already converted. Every filter added to this
tool so far has been of that kind: interior hits meant the run was not a vtable at all,
template neighbours meant the instantiation was unknowable, SEH meant the body was
unwritable. The tool is only as good as the things it knows to exclude, and each
exclusion was found by following a bad suggestion to the end.

And the Read_* group at slots 47 to 55 is genuinely unconverted -- but at 87 to 261 bytes
each they are chunk-loading routines, not the accessors this method has been landing.
Worth naming as a boundary: identifying a function by vtable position is cheap, and
writing it byte-exactly afterwards is not, so the two should be judged separately when
picking work.


## Rank by what a gap costs to write, not just by how identifiable it is

The vtable ranking sorted by how many named neighbours bounded a gap, which measures how
easy the function is to *identify* and says nothing about how hard it is to *reproduce*.
Those are unrelated: a four-byte accessor and a 260-byte chunk loader are equally
identifiable. Sorting by the distance from the entry to its trailing int3 puts the cheap
ones first, and the difference in what the tool offers is immediate.

The first two suggestions under the new order converted. HLodClass slots 100 and 101 are
seven-byte int getters bounded by Set_LOD_Level and Set_LOD_Bias, and hlod.h declares
exactly two virtuals in that gap -- Get_LOD_Level then Get_LOD_Count. Distinct names
rather than an overload group, so the vtable keeps declaration order, unlike the
Collect_Objects and Scale sets which appear reversed. Both first build.

Getting there meant lowering the duplicate filter from eight bytes to three. `ret 0xc`
and `xor eax,eax; ret` are entire functions in this image, and several are claimed
against copies nothing dispatches to, so the ranking kept offering
RenderObjClass::Scale(float,float,float) and Vector3SolidBoxRandomizer::Class_ID as
though they were unconverted work. Nineteen candidates are now held back on that basis,
up from ten.

At three bytes the anchoring question stops being answerable, and that is worth stating
plainly rather than papering over. Dozens of unrelated virtuals compile to `xor eax,eax;
ret`, ICF folds them onto one address, and which copy "belongs" to a given name is not a
question the image answers. Those rows are recorded as suspect and left alone. The
useful line is between a distinctive body claimed at a dead duplicate, which is a real
anchoring error worth fixing, and a generic stub, which is not an error at all.


## A returned constant can name the class, but only with a second witness

HLodClass::Class_ID is six bytes returning 0x19. Counting rendobj.h's ClassID enum from
CLASSID_MESH = 0 puts CLASSID_HLOD at 25, which is 0x19 -- so the constant identifies the
class outright, without reference to which slot the body sits in. That is a stronger kind
of evidence than position, because it survives the ICF folding that makes vtable slot
names unreliable.

It is also easy to over-apply, and the scan showed exactly how. Forty unclaimed bodies of
the form `mov eax,N; ret` sit in vtables with an N that lands inside that enum. Five of
them return 1. If all five were HModelClass::Class_ID they would have folded to one
address, so at most one is -- the rest are simply functions returning a small integer,
and the enum match is coincidence.

So the rule is two witnesses. CameraClass::Class_ID qualifies: the slots below it are
??_GCameraClass and Clone@CameraClass, rendobj.h declares destructor, Clone, Class_ID in
that order, and the value 8 is CLASSID_CAMERA. Both converted first build. The AABOX and
OBBOX candidates have only anonymous Gen_dtor neighbours, so the value stands alone and
they were left.

Worth noting what makes this pairing work: the two witnesses fail independently.
Position is corrupted by folding and by BFME's additions to the declaration lists; a
returned constant is corrupted by coincidence. Neither weakness touches the other, which
is why agreement between them is worth much more than either being individually
convincing.


## The two-witness rule, applied mechanically, converts three of forty

The previous pass established that a Class_ID override can be identified two ways --
by the constant it returns, mapped through rendobj.h's enum, and by its vtable position
-- and that neither is safe alone. Applying both mechanically across the whole image
turns out to be a short script and a sharp filter.

Forty unclaimed bodies of the form `mov eax,N; ret` sit in vtables with an N inside the
ClassID enum. Requiring that some class named in the three slots above also matches that
enum entry leaves three. All three converted first build, and all three have the same
shape: the class's own destructor two slots up, its Clone override one slot up, then the
candidate -- which is exactly rendobj.h's declaration order of destructor, Clone,
Class_ID.

The thirty-seven rejects are the useful part of the number. Five of them return 1, and
had they all been one class's Class_ID they would have folded to a single address, so at
most one is. The rest are ordinary functions returning a small integer, sitting in
vtables whose named slots say nothing about them. Each looked exactly as convincing as
the three that survived, right up until the second witness was demanded.

Worth stating as a rule of thumb for this project: when a body is small enough that its
bytes could belong to many functions, identification has to come from outside the body.
Two outside sources that fail for unrelated reasons are worth more than any amount of
staring at the disassembly, and the ratio here -- three of forty -- is a fair measure of
how often a single source would have been wrong.


## The constant-return trick needs a distinctive constant and a live body

Class_ID overrides fell to the two-witness rule, so the same treatment was tried on
Chunk_Type, which rendobj.h and hlod.h declare the same way -- inline, returning a
W3D_CHUNK constant. It produced nothing, and both reasons are worth keeping.

Most chunk ids are small. Scanning for bodies returning any W3D_CHUNK value found five
candidates, and one of them -- 0x009213D0, returning 2 -- had already appeared in the
Class_ID scan as CLASSID_DISTLOD. A constant of 2 belongs to every enum ever written. It
is only evidence when the value is large enough to be unusual, which for these means
0x100 and up.

Restricting to those leaves four bodies, returning W3D_CHUNK_LIGHTSCAPE, HIERARCHY,
LODMODEL and ANIMATION. All four have zero references anywhere in the image: no vtable
slot, no call site, no data pointer. They are copies the linker kept and nothing reaches.
So the second witness is not merely missing, it cannot exist, and naming them would
repeat the anchoring mistake this log has been documenting for several passes.

The zero-reference result was checked before being believed -- the same scanner reports
one reference for a Class_ID body known to sit in a vtable. A detector that has only
ever returned zero has not been shown to work.

The pass still converted CompositeRenderObjClass::Get_Name, which had three agreeing
witnesses: it sits between Class_ID and Set_Name exactly as rendobj.h orders them, it
reads the +0xC8 member that Set_Name writes, and the neighbouring slots hold
Get_Base_Model_Name and Set_Base_Model_Name of the same class. HLodClass derives from
CompositeRenderObjClass and does not override Get_Name, so the inherited implementation
is what the slot carries.


## A call through this-vtable pins the callee's slot, and overloads move it

RenderObjClass::Remove_Sub_Objects_From_Bone(const char *) is thirty-one bytes that
convert the argument through the virtual at vtable offset 0xC4 and pass the result to
the virtual at 0x9C. Those two offsets are the identification: a name-to-index
delegation, with the int overload it delegates to sitting in the adjacent slot.

They are also the whole difficulty. Reproducing the body means the placeholder class must
put Get_Bone_Index at slot 49 and the int overload at slot 39, because the emitted
instruction encodes the byte offset. Two MSVC behaviours interfere, and both took a
failed build to pin down.

An overload set occupies consecutive slots, placed where the *second* declaration
appears. Declaring the const char* version at the end of the class did not append it --
MSVC pulled it up beside the int version and pushed every later slot down by one, so both
call offsets came out four bytes high.

And within the group the order is reversed: the last declared overload takes the lower
slot. Declaring int then name put name at 39 and int at 40, so 0x9C was still wrong by
one slot after the first fix. Declaring name then int lands the int version at 0x9C, and
that reversal matches the image, where the name overload occupies the slot before the int
one.

The general point is that a virtual call at a fixed offset is strong evidence -- it names
the callee's slot exactly -- but cashing it in requires reproducing the class's vtable
layout, and the overload rules make that layout non-obvious. Both corrections showed up
as an offset wrong by exactly four, which is a useful signature: it means the slot
counting is off by one, not that the identification is wrong.

Separately, vtable_gaps offered 0x00007FD1 as a thirty-one byte candidate. It is an ILT
jump thunk, and the extent measure simply walked through the adjacent thunks to the next
int3. Thunk regions have no int3 padding between entries, so any size it reports there is
meaningless.


## A named local for an intermediate result can change register allocation

Add_Sub_Object_To_Bone's name overload is the three-argument sibling of the
Remove_Sub_Objects_From_Bone conversion: resolve the bone name through the virtual at
0xC4, forward object, index and offset to the int overload at 0x94. Both call offsets
matched immediately, so the identification was settled; what did not match was register
allocation. Retail re-reads the vtable pointer for each call, into eax and then edx.
Written as one nested expression, MSVC instead hoists it into edi and pays a push and pop
for the saved register.

Splitting it into two statements -- assign Get_Bone_Index's result to a named local,
then pass the local -- reproduces retail exactly.

What makes that worth recording is that the one-argument sibling matched with the nested
form. So this is not a style rule about how the original was written; it is register
pressure. With three arguments to marshal, keeping the vtable pointer live across both
calls costs a callee-saved register, and the source shape decides whether the compiler
takes that cost. Where a body differs only in which registers hold what, introducing or
removing a named temporary is a cheap thing to try before writing the row off.

Two smaller things from the same pass.

A parameter whose type is the enclosing class mangles as PAV1@, a backreference, not
PAVClassName@@. Spelling it out fails as "symbol not found in object" rather than as a
byte mismatch, which is a helpfully different error -- byte mismatches mean the code is
wrong, symbol-not-found means the name is.

And vtable_gaps was reporting ILT jump thunks with invented sizes, because thunk regions
have no int3 between entries and the extent walk ran through the neighbours. Resolving
the thunk to its target seemed like the fix but was worse: many claimed rows are the
thunks themselves, so rewriting slot addresses broke ownership and the candidate list
jumped from 84 to 427. Sorting thunks last instead leaves ownership alone and keeps them
out of the cheap end of the ranking.


## Half the remaining vtable gaps were not function entries

vtable_gaps already discarded runs containing an address interior to a claimed row, on
the grounds that a real vtable slot points at a function's entry. That test only sees
claimed rows, and most of the image is unclaimed, so it missed the commoner case: a run
whose first dword merely looks like a code pointer, landing partway into some unclaimed
body.

0x00184F42 was the example that surfaced it -- offered as slot 0 of a thirteen-slot
table, and actually the tail of another function, starting `mov ecx,edi` and popping ebp,
edi and ebx without ever pushing them. The five slots after it are genuine
VectorClass methods, so the table is real; it simply starts one dword later than the run
detector thought.

The fix is one line and does not need the ledger at all: a function entry in this image
is preceded by int3 padding. Requiring that took the candidate list from 83 to 38. More
than half of what remained was noise, and it had been at the top of the ranking for
several passes because the false entries tend to be small.

That is the fourth exclusion this tool has needed -- interior hits, template neighbours,
SEH bodies, duplicates of claimed rows, and now non-entries -- and every one was found by
following a bad suggestion far enough to see why it was bad. The ranking is only as
honest as the list of things it knows to leave out, and there is no way to enumerate
those in advance.

The pass converted nothing. Three candidates were examined and declined: two scalar
deleting destructors whose class is named only by a synthetic Gen_ symbol, so there is
nothing to call them; and a RenderObjClass slot whose body tests a virtual and two
members in a shape that matches none of the inline one-liners the header declares in that
range. Declining is the right outcome for all three -- what would have been wrong is
picking the closest-looking header declaration and calling it identified.


## One address fills 2519 vtable slots, and it is unclaimed

Chasing a filesystem vtable turned up seven consecutive slots all pointing at 0x0088C500.
Counting across the whole image, 2519 aligned .rdata slots hold that address. That is the
signature of the pure-virtual stub: MSVC puts one in every slot of an abstract class that
has no implementation, so a single body ends up referenced once per pure virtual in the
program.

It is unclaimed, and its body is not the three-instruction CRT stub -- it pushes an error
code, calls a reporter, then makes several virtual calls through a global at 0x01336E5C.
This build supplied its own handler.

Meanwhile __purecall is claimed, at 0x006CF680, three bytes, and its own ledger note
records icf-owner=?Get_Sort_Level@RenderObjClass@@UBEHXZ -- it is the shared
`xor eax,eax; ret` body. That cannot be a pure-virtual handler; returning zero is exactly
what such a stub must not do.

Not repointed. One name means one address, the existing row belongs to someone else, and
a 3-byte ICF-folded body is precisely the case established earlier as unadjudicable. But
the reference count is unusually strong evidence, so it is recorded as a correction
candidate rather than left to be rediscovered.

The same investigation exposed a limitation worth stating about vtable_gaps. A run of
consecutive code pointers spans several class vtables: run 0x01143AF8 begins with
??_GFile@@ and only reaches ArchiveFileSystem thirty slots later. So "slot k of n" is a
position in the run, not in any class's vtable, and neighbours several slots away may
belong to a different class entirely. Every conversion this method has produced relied on
immediate neighbours -- one or two slots either side -- which is the range where the run
and the real vtable still coincide. Distant neighbours in the tool's output are not
evidence.


## cmp al,1 is `== true`, and a bare if is test al,al

SimpleSceneClass::Add_Render_Object promoted from its byte dump to clean C++ in two
builds, and the second build turned on a single instruction pair. Everything matched
except the test after the first list insertion: retail has `cmp al,1; jne`, the rebuild
had `test al,al; je`.

Those are different source spellings. A bare `if (x)` on a bool compiles to test al,al;
writing `if (x == true)` compiles to cmp al,1. The original author wrote the comparison
out, and reproducing the byte requires writing it out too -- which looks redundant in C++
and is not.

Worth adding to the small list of source spellings that are visible in the output, beside
the named-temporary lever from the Add_Sub_Object_To_Bone pass. Both are cases where the
obvious way to write the code is not the way it was written, and both cost exactly one
build to find once the diff is down to a couple of bytes.

The rest of the function fell straight out of the layout the body dictates: the object
notified through the virtual at +0x64, three scene lists at this+0x5C, +0xBC and +0xD4,
a reference taken only when the first insertion reports the node was new, and the list
at +0xD4 fed only when the object's predicate at +0x19C agrees. Remove_Render_Object
does the mirror of all four, which is what made both safe to identify in the first place.

Separately, vtable_gaps now only reports neighbours within two slots. A run of code
pointers spans several class vtables, so a named slot thirty positions away belongs to a
different class and says nothing. That took the candidate list from 73 to 45 and removes
a class of suggestion that looked well-evidenced and was not.


## The thunk question answered itself

The previous entry stopped short of pinning a real name at an ILT thunk because it was
unclear whether a second mapping would conflict with the functions.csv row at the body.
Reading tools/build.py rather than reasoning about it settled the matter in one look:
build_call_thunks discovers the thunks on its own, a matched function maps to the pair
[thunk, body], and the comparison picks whichever the target actually encoded. The pin
mechanism is additive besides -- each pinned address is one more candidate, so a matched
name and a hand-pinned thunk coexist without ambiguity.

So Unregister was never blocked. Written as ordinary C++ against a RefMultiListClass whose
Remove is out-of-line, it matched on the first build with no ledger change at all. The cost
of the wrong conclusion was a whole tick spent recording a blocker that did not exist. The
tool was already documented; guessing at its behaviour was the mistake, and it is cheaper
to read a hundred lines of build.py than to write a paragraph of speculation about it.

## Two ways to reach a protected member, and only one keeps the name

Register's five arms call Internal_Add and Internal_Add_Tail on lists that SimpleSceneClass
merely owns -- it does not derive from GenericMultiListClass, so protected access does not
apply. The obvious fix is to make the primitives public. That builds, and then the linker
cannot find them: MSVC encodes the access specifier in the mangled name, Q for public and
I for protected, so ?Internal_Add@GenericMultiListClass@@QAE... is a different symbol from
the ?Internal_Add@GenericMultiListClass@@IAE... the ledger already carries. The build
reported them as unresolved calls needing new symbols.csv rows -- two pins for names that
do not exist in retail.

friend class SimpleSceneClass grants exactly the same access and changes nothing about the
declaration, so the name stays IAE and resolves against the existing row. Access widening
is a rename; friendship is not. Worth remembering because the failure is quiet -- it looks
like a missing pin rather than like the modelling error it is.

## Retail's shape says the wrapper was not there

The first attempt at Register modelled the lists as RefMultiListClass and MultiListClass
with Add defined in-class, mirroring the Unregister file that had just matched. MSVC 7.1
declined to inline them and emitted a call per arm; retail has the whole thing flat, with
Internal_Add called directly from each case and the reference count incremented in line.

Given the same compiler and the same flags, an inline the compiler refuses is an inline
retail did not have either. That is a usable signal in both directions: where the target is
flat and the model is not, the model has invented a layer. Rewriting the arms as direct
primitive calls reproduced all 232 bytes including the jump table, differing only in the
four relocations, which is what an unresolved call looks like.


## A vtable run tells you where it breaks, if you ask the bodies

vtable_gaps offered 0x008DCCB0 as slot 10 of a twelve-slot run whose other names
are all GridCullSystemClass, which made it look like an unnamed GridCullSystemClass
method sitting two slots past Get_Object_Count. It is nothing of the kind. The body
stores 0x01137808 into its object, and 0x01137808 is the address of slot 10 -- the
slot the body itself occupies. A constructor or destructor installs the vptr of the
table its class owns, so a body whose vptr equals its own slot address is slot 0 of
a new table, not slot N of the old one.

That single test partitions the run: ten slots of GridCullSystemClass, then a
one-slot table at 0x01137808, then a one-slot table at 0x0113780C. It needs no
names and no reference header, only the bytes, and it is the missing half of the
??_G observation -- a scalar deleting destructor is almost always slot 0, so a ??_G
neighbour is a boundary marker rather than evidence about the slot beside it. Both
of the leads this run produced were on the far side of a boundary from the names
that recommended them.

Naming the two tables afterwards was ordinary work: 0x0113780C is installed by
??0GridLinkClass, so it is GridLinkClass, and the destructor in it delegates to the
one that installs 0x01137808, so that class is GridLinkClass's base. cullsys.h has
exactly one candidate, CullLinkClass, and the single-slot tables agree with it --
the destructor is the only virtual either class declares.


## Fixing the search cost me the thing it was finding

Partitioning vtable runs made every recommendation correct and, in the same
stroke, deleted the cheapest family of work from the listing. A scalar deleting
destructor is slot 0 of its table; once runs were split at their real boundaries,
every one of them became a first slot, and a first slot has no neighbour above it
to be identified by. The tool that had just been made right stopped offering the
bodies that had just been proved easy.

They never needed a neighbour. A constructor installs the vptr of its own class,
so the code that stores a table's address names the class, and slot 0 of that
table is that class's destructor. That is a different question put to the same
bytes, and tools/vtable_owner.py asks it: four tables, two of which converted on
the first build.

Worth noticing that the fix and the loss came from one change. A filter that
removes false leads removes true ones whenever the property it filters on is
shared, and "is the first slot of a table" was shared by every bad suggestion and
every cheap conversion at once. The answer was not to loosen the filter -- it was
right -- but to find the second route to the same targets.

## The name may be spent already

The first two candidates vtable_owner produced were ??_GWin32LocalFileSystem and
??_GDefaultStaticSortListClass, both 31 bytes, both the shape that had just gone
through first try. Both were traps. The names are already in functions.csv at
other addresses, and each existing row is anchored to a different table from the
one the candidate installs -- 0x01143B98 against 0x01143B78, twenty bytes apart.

One anchor in each pair is wrong, and which one is a real question, but it is a
ledger question. Writing the candidate would have claimed a name the image
already spends elsewhere and left two rows fighting over it. The tool checked
whether the address was claimed and not whether the name was, which are different
checks: ICF folding and duplicate emission mean a name and an address are many to
many here. It now checks both, and the listing went from four to two.


## The store at the top of a destructor does not always name it

Both anchor conflicts from last tick came from one wrong inference, and the
inference is nearly right. A destructor sets the vptr to its own class's table
before running its body, so a store in the first few bytes of ??1X is X's table.
That held for every case until it did not.

When X's destructor is trivial and calls nothing virtual, the store is dead --
nothing can observe the vptr between setting it and the object ceasing to exist --
and MSVC drops it. What remains in the body is the inlined base destructor's
store, which is now first by default and reads exactly like X's own.
??1Win32LocalFileSystem is that case: its only vptr store is 0x01143B78 at +2,
and 0x01143B78 is LocalFileSystem's. ??1DefaultStaticSortListClass is the milder
version, where the base store sits at +0x43 with nothing above it.

So the accusation I recorded last tick was wrong in both directions. The existing
ledger anchors are correct -- Win32LocalFileSystem's table is 0x01143B98,
installed at 0x009CDE14, and its deleting stub is slot 0 of that -- and the
candidates were never those classes' destructors. They are their BASES', which is
a better outcome than the conflict I thought I had: two new functions rather than
two disputed rows.

The confirming witness costs nothing once you look for it. Slots 1 through 7 of
0x01143B78 are all the same address, the shared __purecall handler. Seven pure
virtuals and a virtual destructor is an abstract base, and LocalFileSystem
declares exactly that.

## A name can be spent even when the function is unclaimed

StaticSortListClass went in on the first build. LocalFileSystem did not, and not
for any reason to do with its bytes: ??_GLocalFileSystem is already in the ledger
at 0x005BF290, recorded as a C++ alias for a CategoryModuleTemplate body that
folded with it. The ledger enforces one name to one address, so the name is gone
even though 0x009CDDF0 is unclaimed and, by position and by the pure-virtual
slots, is the function that deserves it.

Freeing it means repointing a row that fx_particle_system.cpp currently verifies,
which is a different job from writing a destructor. Left alone and logged. The
useful part is that "is this function claimed" and "is this name available" are
two questions, and under ICF the second is the one that stops you.


## A backlog nine thousand deep that carries no addresses

Chasing destructor/stub pairs turned up something larger than the pairs. There
are 9842 `present-unmatched` markers across Code -- functions already written in
C++ that do not yet compile to the retail bytes. Every row in functions.csv has
status `matched`, so none of these has a ledger row, and build.py only verifies
claimed rows, which means a file can carry forty of them and still report OK.

The thing that makes them hard is not the C++. It is that the marker names a
function and nothing tells you where it lives. A naked-asm row at least has an
address and a size to compare against; a present-unmatched marker has neither, so
there is nothing to iterate against even though the draft is right there.

Which is what makes the destructor pairing worth keeping despite a forward yield
of zero. A claimed ??_GX calls ??1X, so the stub hands over the destructor's
address, and that turns two of these markers from untestable drafts into ordinary
work. ??1DebugIOFlat is at 0x00889620 and ??1DX8FVFCategoryContainer at
0x00946B20, both already drafted in their files. add_match reverted both, so the
drafts are wrong -- but now they are wrong at a known address, which is the
difference between a bug and a blank.

## Alias rows lie about what their source emits

The one candidate the forward pass produced was ??_GAIUpdateModuleData, paired
with a ??1AIUpdateModuleData row in string_base.cpp. String_base.cpp has no such
class. The row is an alias -- its note records the object symbol as
?releaseBuffer@?$StringBase@D@@AAEXXZ -- so the name in the ledger is not the
symbol the source produces.

That is the second tool this has caught out, after vtable_owner. Under ICF a name
and a body are many to many, and these rows are exactly where the two come apart,
so anything reasoning from ledger names has to drop them first. add_match caught
it regardless: it appended, rebuilt, failed to find the symbol, and reverted
without touching anything.


## Two offsets that cannot both be right, and what that told me

The DX8FVFCategoryContainer destructor reads a refcounted pointer at +0xD8 and a
loop bound at +0xE4, where the ported header puts index_buffer at +0xD0 and passes
at +0xDC. Eight bytes short, uniformly, so I inserted two words ahead of
index_buffer. The destructor then matched -- and the constructor broke, because it
writes index_buffer at +0xD0 and my insertion moved it to +0xD8.

Both functions store the same vtable, 0x0113D024, so they are the same class, and
one class does not have two layouts. The contradiction is the useful part. If the
constructor is right that index_buffer sits at +0xD0, the eight bytes cannot go in
front of it; putting them after used_indices instead leaves index_buffer where the
constructor wants it and still moves FVF to +0xE0 and passes to +0xE4, which is
what the destructor reads.

That relocates the conclusion. The pointer released at +0xD8 is then not
index_buffer at all -- it is one of the two members this build added -- and the
ported draft, which releases index_buffer because that is what the Generals
destructor does, is releasing the wrong field. The draft looked structurally
perfect against the disassembly and the resemblance was luck: a refcount release
followed by a loop over passes looks the same whichever pointer it releases.

Reverted at three builds with 109/109 still matching. The next attempt has a
specific shape to test rather than a delta to nudge.

## A ported draft can be the wrong function entirely

??1DebugIOFlat was the other address recovered from a stub, and it is not a
matching problem. Retail stores a vptr and makes one call on a member at +0x9E6F
under an SEH frame. The draft walks two linked lists freeing entries, which is
what the Generals destructor does and bears no relation to the bytes.

Worth separating from the DX8 case. There the draft was the right function with
the wrong field; here the draft is the wrong implementation, and no amount of
adjustment converges. The tell is structural: when the target's instruction count
and the draft's statement count are not even the same order, stop reading the
diff and start reading the target.


## The function that would not move told me where the bytes go

The contradiction from last tick resolved on the first build once I asked which
function was the more constrained. Inserting eight bytes ahead of index_buffer
matched the destructor and broke the constructor; the constructor is the one that
cannot be argued with, because it writes +0xC8, +0xCC and +0xD0 and then stops. It
pins index_buffer at +0xD0 and says nothing whatever about what follows.

So the eight bytes had to go above index_buffer rather than below it, and putting
them between used_indices and FVF moves passes to +0xE4 where the destructor reads
it while leaving every offset the constructor touches alone. 110/110 in the
translation unit, and 428/428 across all twelve that include the header.

The part worth keeping is the second conclusion, which fell out of the first. If
the released pointer is at +0xD8 and index_buffer is at +0xD0, then this build's
destructor does not release index_buffer at all -- it releases one of the added
members. The ported draft releases index_buffer because that is what the Generals
destructor does, and it was never going to converge by nudging offsets. A
refcount release followed by a loop over passes looks identical whichever pointer
it releases, which is exactly why the draft looked so close.

Ask which field an access reaches before deciding a layout is off by N. The offset
delta was real and uniform and still pointed at the wrong edit.


## The delta gate cannot see what the full gate checks

Committing a header change ran the full gate for the first time in many ticks, and
it failed -- not on the header change, which matched 94152/94152, but on three
DIR32 consistency violations that had been sitting in master unnoticed. One was
mine: ??_7CullLinkClass@@6B@ resolves to 0x01137808 in the deleting destructor I
landed several ticks ago and to 0x00000000 in gridcull.cpp.

The per-source gate that runs on an ordinary commit verifies the staged sources
byte for byte, which is exactly what it promises, and cross-object properties are
not that. So a source-only commit can introduce a whole-image inconsistency and
report OK, and the next person to touch a header inherits the failure. Worth
knowing which commits are cheap and which are the ones that actually check.

All three turned out to be genuine and irreconcilable rather than bugs.
??0CullLinkClass at 0x00087A50 is an ICF alias -- its own ledger note says so --
and the folded body is a generic two-word stub that stores a literal zero where a
constructor would store the vtable, so it resolves the symbol to 0 and always
will. __imp__fopen and __imp__strstr have two IAT slots each in the image itself,
and different objects bind to different ones. Whitelisted with the reasoning
written down, which is what that file is for.


## Do not soften a guard to make a tool run

locate.py died with a traceback because reverse/ghidra_functions.csv is absent,
and its own docstring calls the inventory optional. The obvious fix -- load it if
present, carry on if not -- would have been wrong. That dict gates acceptance in
two places, and this tool lands claims: without it, plausible_small_start loses
the check that rejects a start sitting inside a recovered function, which is the
common tail-match false positive, and ghidra_boundary loses its evidence
entirely. Running would not have degraded the search, it would have removed the
reason to trust the result.

So it now exits with the message land_ambiguous.py already gives for the same
missing file. A tool that cannot be trusted should refuse, not proceed quietly.

The machine has no JDK and no Ghidra, so the inventory cannot be regenerated
here. Worth recording what that costs: locate.py, land_ambiguous.py and
next_work's third tier are all unavailable, and vtables.tsv would give BFME's
exact vtable slot order -- which is precisely what vtable_gaps and vtable_owner
reconstruct by hand from byte evidence.

## A work queue is a suggestion, not an address

next_work's first pick was ?AddCommands@Debug@@SA_NPBDPAVDebugCmdInterface@@@Z at
0x00891510, 83 bytes. What is actually there is a 31-byte thiscall deleting
destructor -- push esi, mov esi ecx, call the destructor, test the flag, ret 4 --
followed by int3 padding. A static function taking two pointers is cdecl and
returns with ret; this is neither, and the queue's own hint admitted it had
drift-corrected the address by -31 bytes.

It is not an isolated slip. parseData and getDataTemplate are both queued at
0x004850C0 with different sizes, and two ScriptActions entries share 0x006827A0.
The queue is useful for finding candidates and its hint line says "verify the
prologue" for a reason. Check the calling convention against the mangled name
before spending a build: SA is static, QAE and UAE are thiscall, and the
prologue and return instruction say which one the bytes are.


## Which direction the unwind state counts says where the members live

A naked ModuleData destructor: two string members destroyed at +0x58 then +0x44,
both calls landing on the same folded releaseBuffer body, then a vptr store.
Modelled as two members of one class it came out nearly right and stayed wrong in
one place -- retail sets the unwind state to 0 before the first destruction and 1
before the second, and mine set 1 then 0.

Down is what a destructor does across members of a single class: they die in
reverse declaration order and the state counts down with them. Up means the two
objects are not peers. A derived member destroyed before an inlined base's member
gives +0x58 first and the state ascending, because the two belong to different
unwind scopes rather than to one list. Splitting the strings across a two-level
hierarchy -- one in the base, one in the derived -- matched on the next build.

The direction is worth reading first. It costs nothing, it is visible in two
instructions, and it decides a structural question that is otherwise invisible:
both layouts destroy the higher address first, so the order alone cannot tell
them apart.

## The lift already knew something I threw away

The naked file declared the class __declspec(novtable) and I dropped it when
rewriting, on the grounds that a class with a real base does not need it. It is
load-bearing. novtable suppresses the vptr store MSVC puts at the top of every
constructor and destructor, and without it the compiled body opened with a store
retail does not have -- the only vptr store in the target is Snapshot's, arriving
last from the inlined base destructor.

Whoever lifted the bytes had already worked that out. A naked lift is not just a
byte dump waiting to be replaced; the declarations wrapped around it are evidence,
and dropping them costs a build to rediscover.


## Correction: the naked lift did not know about novtable

Last entry claimed the naked wrapper's __declspec(novtable) was evidence I had
carelessly discarded. It is not. All forty naked ModuleData destructor thunks
declare it, and eighteen of them emit an early vptr store -- exactly what
novtable suppresses. The attribute is boilerplate on a wrapper whose body is
__asm, where the declaration only has to compile, so it says nothing about the
class. It was right for UnitCrateCollideModuleData by coincidence.

The real discriminator is in the bytes and costs one regex. An early
mov [reg], imm32 means the class installs its own vptr and novtable is wrong.
Its absence, with a store of some other class's table at the end, means the only
surviving store is an inlined base destructor's and novtable is right.

Correcting this matters more than the usual slip because the wrong version told
future work to trust the declarations wrapped around a byte dump. Half of them
contradict their own bytes.

## The family, measured

Forty naked ModuleData destructors, and they are not one shape. Fifteen have no
lea-based member destruction at all -- they are inlined STL container teardown,
with vector deallocations and node-allocator calls, and are a different problem.
The remaining twenty-five destroy between one and eight members, and several
shapes repeat exactly: three files destroy two members at +0x18 and +0x14 with
states 4 then 3, two share (2,1,0), two share (1,0,2) at +0x74/+0x70/+0x8, two
share (6,5,0).

Repeated shapes are the point. A shape solved once should transfer to its
siblings, which is why the census is worth more than any single conversion in it.
What blocks the two nearest siblings is not their shape but their callees:
ProductionUpdate and CommandSetUpgrade each destroy a member whose destructor is
unclaimed, reachable only through an ILT thunk, so converting them means naming a
function this project has not named yet.


## A redundant null check names the function it came from

The last two instructions of difference on this destructor were a test the
compiler should not have emitted: after the interlocked decrement, retail tests
the pointer again before the virtual delete, although the same pointer was
already tested a few instructions above and nothing could have changed it. My
version, with both halves written in one destructor, correctly omitted it -- and
no rearrangement of that one function was going to put it back, because the
optimiser is right.

The check survives only if the two tests are in different functions. delete this
inside RefCountedThing::Release_Ref does it: once inlined, the callee's this is a
value MSVC does not connect to the pointer the caller tested, so the delete
expansion's own null check stays. Writing it that way matched on the next build,
and the register allocation fell into place with it -- this moved to edi and the
pointer to esi, exactly as retail has them, because the two now have different
live ranges.

So a check that looks redundant is a boundary. It marks where one function ended
and another began before the inliner ran, which is otherwise invisible in the
bytes.

## dllimport is visible in one byte of the call

The same function needed InterlockedDecrement declared __declspec(dllimport).
Plain, it compiles to a direct e8 to a local thunk; dllimport compiles to
call dword ptr [__imp__...], and retail has the indirect form. That is a
one-line source fact recoverable from the opcode, and worth checking first
whenever a call to an OS API does not line up.


## Three files, one body, one template

GettingBuiltBehaviorModuleData, HordeUpdateModuleData and W3DLaserDrawModuleData
all claim 0x001FE260. ICF folded them because their destructors are byte
identical, which means the three classes have the same member layout as far as
destruction is concerned: three references at +0x08, +0x0C and +0x10 and two
strings at +0x14 and +0x18. Each file still has to emit its own symbol, so the
source differs only in the class name.

They went in on the first build because the previous conversion had already paid
for the hard part -- delete this inside Release_Ref, and dllimport on
InterlockedDecrement. That is the argument for censusing a family before working
it: the second, third and fourth members of a shape cost almost nothing once the
first is understood, and the census is what tells you a shape has siblings.

One thing fell out rather than being written. With a single dllimport call site
the compiler emits call dword ptr [__imp__...]; with three it loads the import
table entry into ebx once and calls through the register. Nothing in the source
says that, and trying to force it would have been a mistake -- it follows from
the number of uses.

## A path that exists for bash need not exist for python

The template went to /tmp/tmpl.txt, written by a bash heredoc and read by
Windows Python, which cannot see that path. The write succeeded, the read threw,
and the build that followed in the same command reported OK 1/1 -- because it had
compiled the unchanged naked file, which of course still matches.

That is the same trap as the silent no-op patch a few ticks ago, wearing a
different coat: a verification step that passes because it verified the old
thing. The assert that now checks the rewritten files contain no __emit is the
cheap guard, and the scratchpad directory is the path both halves of this
environment agree on.


## One define decides whether the allocator is visible at all

The vector teardown in these destructors is STLport's size-dispatched deallocate:
subtract the vector's start from its end_of_storage, round to a multiple of the
element size, and send anything above 128 bytes to operator delete and the rest
to the node allocator's _M_deallocate. My first attempt produced the capacity
arithmetic exactly and then made a single indirect call where retail has the
whole dispatch.

_STLP_USE_STATIC_LIB is the difference. Without it STLport declares its allocator
entry points dllimport, so the dispatch lives behind an exported function and the
call comes out as call dword ptr [...]. With it the inline body is visible to the
compiler and lands byte for byte. Several thunks in the tree already carry the
define, which is where I found it -- worth reading the flags on files that match
before theorising about the ones that do not.

Two other numbers in that sequence are free information. The sar N / shl N pair
gives sizeof(T) directly: 3 for an eight-byte element, 2 for a four-byte one. And
whether the base destructor is called or inlined says how to declare it -- a call
means a non-inline base destructor and no vptr store in the derived function,
while an inline empty base puts its store at the end.

With those, the second of these two took one build and differed from the first
only in two constants.


## Offset zero with no vptr means it is not the class you were told

PlayerUpgradeSpecialPowerModuleData's destructor destroys a vector whose start
pointer is at offset 0 of the object, with no vptr store anywhere and no base
destructor call. A class with a virtual destructor -- and the mangled name says
UAE, so it has one -- puts its vptr at offset 0, which leaves nowhere for that
vector to live. The body is vector<AsciiString>::~vector, and the ModuleData name
is sitting on it because ICF folded the two.

That is worth checking before modelling anything: if the first member lands at
offset 0 in a function whose name claims a virtual destructor, the name and the
bytes belong to different functions. It cost nothing to notice and would have
cost several builds to discover by fitting layouts.

## Whether the vector destructor is called or inlined is the element type

Two of these conversions inline the whole STLport deallocate dispatch; two call
an out-of-line destructor instead. The difference is not the container or the
flags -- it is whether the element has a destructor. A POD element leaves only
the deallocate, small enough to inline; an element with a destructor needs a
loop over the range first, which MSVC emits once as a COMDAT and calls from
every instantiation.

So the call is not an obstacle to reproduce, it is a description of the element.
Seeing it means writing vector<something-with-a-destructor> and letting the
compiler make the same choice, which it did.

The name that call resolves to needed a pin, and the address was already claimed
under a different name -- the folded one above. symbols.csv being additive is
what makes that legal: the vector destructor's real mangled name and the
ModuleData name it folded with can both point at 0x000658A0.


## Six out of seven x87 blockers were not x87

OCLSpecialPowerModuleData was tagged x87 by list_naked_candidates and I skipped it
for that reason in an earlier tick. It contains no floating point whatever. The
byte that triggered the tag is the dc in e8 82 32 dc ff -- part of a call
displacement.

The test was `any byte in D8..DF`, and an x87 escape opcode only means anything
when it starts an instruction. Decoding the naked thunks properly puts the damage
at 753 functions flagged where 150 really use x87: 603 false positives, each one
carrying an eighteen-point ranking penalty that pushed convertible work to the
bottom of the queue. My own screen_blockers had the same test; it at least
labelled the result x87? and documented it as loose, which is why the tally in
the earlier backlog census -- 41 x87 rows out of 400 -- has to be retracted
rather than trusted.

Both now decode with capstone and fall back to the byte test only when the
decoder is missing, saying so in the label when they do. The general point is
duller than the number: a substring test on machine code finds opcodes inside
displacements, immediates and ModRM bytes, and the more common the opcode range
the worse it gets. D8..DF is eight of 256 values, so a hundred-byte function hits
it by chance more often than not.

## Two more shapes, both first build

PartTheHeavensUpdateModuleData is three vectors of sixteen-byte PODs and a
string; OCLSpecialPowerModuleData is a vector of PODs and a vector of strings
over an out-of-line base. Both landed on the first build with no new levers --
element size from the sar/shl pair, inlined-or-called from whether the element
has a destructor, novtable from the absence of an entry vptr store. The catalogue
is doing the work now.


## The corrected filter opened a pool of seventy

With x87 decoded rather than pattern-matched, seventy naked thunks of 140 bytes
or less turn out to have no floating point and every callee already named. That
pool is entirely an artefact of fixing the detector; none of it was visible last
tick.

Two attempts from it, both reverted at the build limit, both landing a few
instructions short in the same way.

UnicodeStringLessThan::operator() is compareNoCase followed by setl, and that
part reproduces byte for byte. What does not is the unwind bookkeeping: retail
writes state 0 at entry and -1 before the last destructor, while two by-value
class parameters give 1, 0, -1. Retail is protecting one of the two parameters,
not both, and I could not find the source form that says so.

StealthUpgradeModuleData's constructor matches from +0x30 onward -- ten words, a
byte, a -1, two more words, all off a single base register. The first two
sub-objects do not. Retail copies this into edx, writes six dwords through it,
then advances with lea edx,[eax+0x18] and writes six more; every form I tried
(two members, an array of two, an out-of-line element constructor) folds those
twelve writes into the flat run through eax and loses the cursor.

Both are the same open question in different clothes: what makes MSVC 7.1 keep a
separate pointer for an inlined sub-object rather than folding its stores into
the enclosing base register. Recording it as such is more useful than either
individual failure, because the answer would unlock a family rather than a
function.


## Half an answer to the cursor question

LifeEventModuleInfo's constructor has the same shape that defeated
StealthUpgradeModuleData: a sub-object whose words are written through a register
rather than off this. Here the reason is plain. ecx holds the sub-object's
address because it is the this for the setRange call two instructions later, and
the inlined constructor's stores simply use the register that is already being
set up. The cursor is a thiscall argument, not a pointer variable.

That does not transfer to StealthUpgradeModuleData, which has the same cursor and
makes no call at all. Five source forms are now eliminated there -- two separate
members, an array of two, an out-of-line element constructor, an explicit member
function call, and a loop over the array -- and all five fold the writes into the
flat run. The question stays open, narrower than it was.

## A constructor's EH frame counts its destructible members

Modelling the random-variable member as a plain struct produced no EH frame at
all where retail has one, because a constructor only needs unwind protection if
something already built has to be torn down when a later step throws. Giving the
member a destructor produced the frame. One unwind state remained missing, and
that was the second destructible member -- the four-byte one at +0x04 that I had
modelled as an int.

So the count is readable: the number of states in a constructor is the number of
destructible sub-objects built before the last thing that can throw. It took two
builds to walk from no frame to the right frame with the right state count, and
both steps were determined rather than guessed.

What stopped it was scheduling. The final version has retail's instruction
multiset, the same call displacement and the same epilogue, but retail interleaves
the argument pushes with the member's zero stores and the compiler emits the
zeros first. I went a build past my own limit chasing it and should not have --
the residual had no source-level lever left in it, and that was visible one build
earlier.


## Who owns offset zero is written in one lea

UpgradeModuleModuleData's constructor calls its base with this passed straight
through in ecx. My first version emitted lea ecx,[esi+4] before that call, and
the reason was a modelling choice I had made without noticing: I gave the derived
class a virtual of its own and left the base non-polymorphic, which puts the
vptr at offset 0 and pushes the base subobject to +4.

Retail has no lea, so the base owns offset 0 -- it is polymorphic itself and the
derived merely overwrites the vptr with its own table. Making the base's
destructor virtual and dropping the derived's invented virtual matched on the
next build.

It is a cheap check worth doing before writing anything: a base constructor call
with a bare ecx means the base is at offset 0, and any lea in front of it is the
compiler stepping over something the derived class put there first.

## Screening by shape beat screening by size

Two ticks went into functions whose sub-objects are zeroed through a register
cursor that no source form I tried reproduces. Rather than keep drawing from the
same pool, the shape itself is now a filter -- a lea into a register followed
within two bytes by a store through that register. It takes the 28 clean naked
candidates to 24, and the one picked from what remained went in on the second
build.

The two it rejected were worth rejecting. SabotageMilitaryFactoryCrateCollide's
factory carries the cursor twice, with different registers and different zero
registers for each sub-object and no call after either -- the same open question
with more of it. DeflectSpecialPower stores six vptrs, at +0, +0xC, +0x10, +0x20,
+0x24 and +0x38, so every base of a multiple-inheritance hierarchy would have to
be laid out correctly before a single byte matched.


## Three failures, one cause: the compiler sinks vptr stores

W3DDebrisDraw's constructor reproduces completely -- the base call and its
displacement, the second base's inlined vptr store, both vtable values, and all
fourteen field stores in retail's deliberately unsorted order. One thing is out
of place: my compile puts this class's own two vptr stores at the END of the
body, and retail has them immediately after the base constructor returns.

That is worth stating as a cause rather than a symptom, because it is the same
thing that stopped LifeEventModuleInfo and it is what the StealthUpgrade cursor
work kept bumping into. MSVC 7.1 sinks a constructor's vptr initialisation past
the body when nothing in the body dispatches virtually; retail's compile did not.
Three functions, one difference.

Two things it is not. /O1 is not the answer -- it changes the prologue to
push [esp+N] forms and turns the -1 store into or dword ptr [esi+0x14], -1, so
/O2 is right. And moving field assignments between the member initialiser list
and the body produces byte-identical output, so that is not a lever either; MSVC
treats the two the same once inlining has run.

Which leaves the question narrowed rather than answered, and narrowed usefully:
what makes the vptr live across the body. Something in retail's source must make
the object's dynamic type observable inside the constructor, and finding it once
would settle a family rather than a function.


## The compiler is not the problem, and the arithmetic says so

Four functions now reproduce completely except for instruction order, and the
tempting conclusion is that the vendored MSVC 7.1 is not quite the build EA used
-- a different point release with a different scheduler would explain all four at
once.

It cannot be. 94158 functions match byte for byte with this compiler. A scheduler
that ordered stores differently from retail's would not fail four functions, it
would fail thousands. Whatever is moving these instructions is in the source, not
the toolchain, and the hypothesis is retired before it costs a tick.

The processor-targeting flags are ruled out too: /G5, /G6 and /G7 all leave
W3DDebrisDraw's store order exactly as the default blended model does. Together
with /O1 and the initialiser-list test from last tick, that is four flag-level
explanations eliminated.

## One transposed pair

ScriptConditions' destructor is the closest miss so far. Every byte matches --
the EH funcinfo, both vptr values, the global's address, the delete expansion's
single null test, the base destructor call and its displacement -- with one pair
of instructions swapped: retail loads ecx with this before clearing the global,
and the compile clears the global first.

Worth recording precisely because it is nearly a proof by exhaustion. The
structure is right: two vptr stores mean an intermediate base whose destructor is
empty and inlined, since a direct base would write its own vptr inside its own
destructor and nothing would appear here. The body is right: one delete and one
assignment, and the single null test is the delete expansion's rather than a
source-level if, which would have produced two. What remains is two instructions
in the wrong order, and no source form I have tried moves them.


## The vector destructor iterator hands over the array

LANGameInfo's destructor went in on the first build, and the reason is that one
of its three members required no inference at all. The call to ??_M takes four
arguments and they are the array: the element destructor's address, the count,
the element size, and the base pointer. Eight elements of 0x68 bytes at +0x58,
read straight off the pushes.

Two other things were free. The mangled name is QAE rather than UAE, so the
destructor is not virtual, the class has no vtable, and the layout starts with
data at offset zero -- no vptr store to place and none of the sinking that has
blocked four other functions. And the unwind state counting down 1, 0, -1 says
three members of one class rather than anything inherited.

Worth contrasting with the last few attempts: nothing here had to be guessed and
adjusted. Where a function's structure is fully determined by its arguments and
its mangling, the conversion is transcription. Where it depends on how the
compiler chose to order stores, it has not gone in yet.

## A hundred and seventy-nine names on one body

??_GLocalFileSystem sits at 0x005BF290, which I had suspected of being a
mis-naming that could be corrected to free the name for the real function at
0x009CDDF0. It is not. That address carries 179 rows, every one an alias of a
single thirty-byte deleting-destructor body that ICF folded across 179 classes,
and the whole set was recorded deliberately.

So declining to claim the name several ticks ago was right, for a better reason
than the one I had then. It also means individual names in that set are weak
evidence about anything -- they were produced in bulk -- and the class owning
vtable 0x01143B78 stays unidentified rather than being assumed.


## Two bytes out of a hundred and six

Anim2DCollection::newTemplate came down to a single transposed pair. Everything
else matches: the EH funcinfo, the size pushed to operator new, the copy
constructor and the template constructor with their displacements, the list
link-in, the epilogue. What differs is that retail writes the temporary's address
into the EH slot and then loads ecx with it, while the compile loads ecx first.

Both fixes that got it there were free readings rather than guesses. The size
pushed to operator new is the class size exactly -- 0x1C said seven words where I
had four -- and `mov [eax+4], ecx` said the list link is the second word, not the
first. Neither needed a build to discover, only a build to confirm.

/EHa is not the lever. It does not nudge the ordering, it changes the exception
model outright: byte-sized state writes instead of dword, an extra jump around
the constructor, different use of the funcinfo. /EHsc is right and is now
recorded as such alongside /O1 and the /G flags.

That is three functions differing by one or two transposed instructions around
compiler-generated bookkeeping. Reverting each is correct -- a near miss is not a
match -- but the pattern is sharp enough now to be worth attacking directly
rather than one function at a time.


## The stand-in was the bug

Three ticks went into instruction orderings I could not reproduce, and the answer
was not a flag, a scheduler or a compiler build. It was that I had been writing
minimal hand-rolled classes -- a four-byte AsciiString with a declared copy
constructor, a base with the right size and one virtual -- which reproduce a
class's layout but not its code generation.

Anim2DCollection::newTemplate differed from retail by exactly one transposed
pair. Replacing the stand-in AsciiString with #include "PreRTS.h" and the real
Common/AsciiString.h matched on the first build, with nothing else changed.

The way to find it was a control experiment rather than another guess. Scanning
.text for the byte sequence I could not produce -- 89 64 24 xx 8b cc -- and
attributing each hit to its ledger row gave 348 matched functions that emit it.
Filtering out naked dumps, which match by construction and so demonstrate
nothing, left 110 clean C++ sources. Every one of them includes the real headers.
Reading a single file answered what four builds of guessing had not.

Two habits fall out. When a difference resists source-level explanation, look for
a function that already produces the thing you want and read how. And prefer the
real header to a stand-in whenever one exists -- a stand-in is a claim that only
layout matters, and for anything with a constructor, a destructor or a temporary,
that claim is wrong.


## Scoping the real-header lever before trusting it

Last tick's finding -- that a hand-rolled stand-in, not a compiler flag, caused an
ordering residual -- was worth generalising, so I tried it on the three functions
it seemed to explain. All three still fail, each for a different reason, and the
lever is narrower than one success suggested.

ScriptConditions was written against the real SubsystemInterface and did not
budge. The stand-in that matters there is the type of the global being deleted,
and 0x012F06AC is unnamed in both ledgers, so there is no real class to reach
for.

LifeEventModuleInfo got worse. The reference GameClientRandomVariable has no
zeroing constructor, where BFME's zeroes three words, so including the real
header removed instructions instead of reordering them. BFME's class is simply
not Generals' class.

Template did not change at all, because the stand-in was never its problem -- the
AsciiString constructor call already matched byte for byte, and the residual is
field stores interleaved around the ??_L call plus a zero constant split across
edi and ecx.

So the rule is: a stand-in explains a residual only when the class it stands in
for both exists in the reference with the same definition AND is the thing whose
codegen differs. That is what newTemplate had -- a by-value AsciiString temporary
whose copy construction and destruction are the whole reason the function has an
EH frame. Where the stand-in is peripheral, replacing it changes nothing, and
where BFME diverged from Generals, it makes things worse.


## Selecting for the lever rather than hoping for it

Last tick scoped the real-header lever to functions whose by-value class
temporaries are the reason they carry an EH frame. This tick selected for that
directly -- naked thunks whose mangled signature mentions AsciiString -- and the
first two both went in on the first build.

That is the whole method. Rather than draw a candidate and hope the levers apply,
filter the pool by the property the lever needs. The filter is a substring of the
mangled name, which costs nothing, and it turned a queue that had produced one
conversion in four ticks into two conversions in one.

Both functions also confirmed each other. setCachedStats reaches virtual slot 7
at +0x1C and getCachedStats reaches slot 6 at +0x18, on the same class. Neither
number was checkable alone; together they are, and converting a pair from one
class gets that verification for free.

One thing worth writing down about argument order: by-value class arguments are
constructed right to left, so the last argument's temporary is built first. Both
of these construct the value or the default before the key, and the unwind states
number in that same order -- which is how the two temporaries can be told apart
in the bytes at all.


## Sometimes the reference has already written it

OptionPreferences::setLANIPAddress and HotKeyManager::searchHotKey are both
declared verbatim in the reference headers, down to the parameter types. Including
the header rather than hand-rolling means the class, its base chain, its layout
and the signature all arrive correct at once, and the only thing left to write is
the body -- one line in each case.

Three conversions this tick, all on the first build, all from the same filter:
naked thunks whose mangled signature mentions a class the reference defines
unchanged. The pool of four such AsciiString functions is now empty.

## Reading a backreference before believing an overload

?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABV2@@Z has two candidate
meanings, because the class declares both an AsciiString and a UnicodeString
overload. The ABV2@ settles it: 2 backreferences the return type, AsciiString, so
this is the AsciiString overload. The UnicodeString one is what it calls, not what
it is.

Getting that backwards would have modelled the wrong function and blamed the
mismatch on something else. Backreferences are cheap to resolve and worth
resolving whenever a class has overloads -- the numbering runs over every name
already seen in the mangling, return type included.


## A row whose name its own bytes refute

?getAlternateMouseModeEnabled@OptionPreferences@@QAE_NXZ is claimed at
0x00092670. QAE_NXZ is thiscall, no arguments, returning Bool, so the body should
end in a bare ret. It ends in ret 4, and what it does is build an AsciiString key
from a literal, subscript the preference map, and assign a by-value string into
it. That is a setter with one argument, and the key literal is GameSpyIPAddress,
which the reference header names setOnlineIPAddress.

The check that caught it costs nothing and I had already written it down two
ticks ago: compare the calling convention encoded in the mangled name against the
prologue and the return. XZ means no stack arguments; ret 4 means one. They
cannot both be right.

## Reference headers can be wrong about slots

WinInstanceData::setText reproduces completely once two vtable slots are
corrected: BFME reaches newDisplayString at +0x24 where the reference header puts
it at +0x18, and DisplayString::setText at +4 where the header puts it at +8.
Including those headers does not help, it actively supplies the wrong number.

So the real-header rule needs its own qualification. Including a reference header
is right when it fixes codegen -- a class's constructors, its temporaries, its
copy semantics -- and wrong when the thing you need from it is a vtable layout
BFME has changed. Here the answer was both at once: the real UnicodeString for
the temporary, hand-written interfaces for the two vtables.

And the lever is narrower than last tick suggested. The real UnicodeString did not
fix the transposition that the real AsciiString fixed in newTemplate, so
"include the real class" is not sufficient on its own.


## Retiring a name is three edits, not one

0x00092670 carried the name getAlternateMouseModeEnabled, which its own bytes
refute: QAE_NXZ promises no stack arguments and a Bool return, and the body ends
ret 4 having stored a by-value AsciiString into the preference map. The key is
GameSpyIPAddress, and the reference header ties that to setOnlineIPAddress.

Correcting it took three edits and all three matter. The row comes out of
functions.csv; the name and rva go into reverse/deleted_rows.csv; and only then
can the correct name be claimed. The tombstone is not bookkeeping -- functions.csv
merges with git's union driver, which has no concept of a deletion, so any branch
that forked before the removal silently resurrects the row. check_csv fails if a
tombstoned pair reappears, which is the only thing making the deletion stick.

The file was renamed too. A source called
OptionPreferences_getAlternateMouseModeEnabledMethodThunk.cpp defining
setOnlineIPAddress would be the next person's wrong turn.

## A note that argues with its own row

The retired row's note read "multi-xref Open-BFME4+Grok GameSpyIPAddress". Whoever
wrote it had already seen the key literal and recorded it, and still left the
getter's name on the row. The evidence for the correction was sitting in the
ledger the whole time.

Worth treating notes as claims rather than decoration. This one disagreed with
its own name field, and that disagreement was the finding.


## The easiest rows to check were the ones being skipped

audit_ret_arity compares the stack cleanup a decorated name implies against the
ret the retail body actually performs. It was checking 8636 rows and skipping
85522 as unparsable, and among the skipped were every constructor and every
destructor in the ledger.

The reason is small. A constructor or destructor encodes no return type -- the
convention letter is followed straight by '@' -- and handing that to the
return-type skipper drifts the parse, which the tool then correctly refuses to
accuse on. But these are the easiest rows in the whole ledger to check, not the
hardest: a destructor takes nothing and must pop nothing, and no parameter
parsing is needed to say so. Three lines later the tool checks 10852 rows and
reports 143 contradictions instead of 69.

Worth remembering that a conservative tool's skip list is where its blind spots
live. "Skipped 85522" reads like caution and was hiding a whole family.

## A destructor that returns this

??1SlavedUpdate@@UAE@XZ reads a stack argument, returns this in eax, and pops
eight bytes. Destructors do none of those things; constructors taking two
arguments do all three. The row is a constructor wearing a destructor's name.

It also settles something that had looked odd a few ticks earlier.
??0TensileFormationUpdate and ??0CritterEmitterUpdate both appeared to call
??1SlavedUpdate -- a constructor calling a destructor, which I noted as strange
and moved past. They were calling their base constructor all along, and the
strangeness was the name, not the code.


## The real header can delete calls the target makes

Two ticks ago including a reference header fixed a conversion; here it broke one,
and the rule that covers both is about what the header does rather than whether
it is authentic.

LANGameSlot::isUser calls GameSlot::getName and UnicodeString::compareNoCase out
of line. Both are declared inline in the reference headers, so including them
removes the two calls entirely and replaces them with inlined field reads and a
hand-written string comparison. Replacing both with plain declarations put the
calls back on the third build.

So: include the reference header when what you need from it is codegen the
compiler must see -- constructors, destructors, copy semantics of a temporary.
Declare it yourself when the target CALLS something the reference would inline.
The header is authoritative about Generals, and BFME moved several functions out
of line.

## When no evidence names a class

??1SlavedUpdate is a constructor by every available sign: it reads two stack
arguments, initialises members from them, stores a vptr, returns this in eax and
pops eight bytes. Destructors do none of that. But the obvious correct name,
??0SlavedUpdate with two parameters, is already claimed at another address, and
the vtable this function installs is stored nowhere else in the image, with slot
0 pointing at a synthetic thunk.

So the row is wrong and the right name is not recoverable from the binary. Worth
recording as exactly that rather than guessing: a wrong name with no evidence for
the right one is a different state from an unidentified function, and pretending
otherwise would put a fabricated name in a ledger that 94158 rows depend on.


## Two release idioms, told apart by one instruction

RenderObjClass releases its container with a plain dec of the count at +4 and, if
that reaches zero, a virtual call at slot 0 taking no argument. The ModuleData
family releases with InterlockedDecrement and then delete this. Both are
"Release_Ref", and the bytes tell them apart at a glance: dec versus an indirect
call through the import table, and a bare virtual call versus one preceded by a
push of 1 and a redundant null test.

Which matters because the second form's redundant null test is the inlining
boundary noted several ticks ago -- it is delete this inside the callee. The first
form has no such test because Delete_This is an ordinary virtual on a pointer the
caller already knows is good.

## A shape that failed once is not a shape that fails

ScriptConditions stalled on one transposed pair around its base destructor call,
and it would have been easy to write off the whole SubsystemInterface-derived
family. UpgradeCenter has the same base, the same out-of-line call, the same
entry vptr store, and matched on the first build.

So the residual there is specific to that function -- the global clear next to
the base call -- not to the shape. Worth checking a sibling before concluding a
family is blocked; two conversions this tick came from a list that included the
function I had failed on.


## A tool that reports 143 and prints 40

I grepped audit_ret_arity's output for ?onExit@AIAttackState, found nothing, and
concluded the audit had missed a contradiction I had just verified by hand. It had
not. The tool prints its first forty findings by default while its header reports
the true count, and onExit is there at --limit 200.

The mistake is worth recording because the output invites it: a header saying 143
above a list of 40 reads as a complete list unless you count. Anything scripted
against that output needs the limit raised first, and a negative result from a
truncated list is not a negative result.

## Screening candidates against the audit

Two of this tick's three picks were rows whose calling convention contradicts
their own name -- onExit pops nothing where its StateExitType parameter requires
four, and it is really an allocation of a 0x44-byte state machine built from
this+0x10 and a literal. No source can match a row like that, because the name it
must emit is not the name of the function that is there.

So candidate screens should subtract the audit's flagged set before ranking
anything. That is cheaper than discovering it one disassembly at a time, which is
what I did twice today.


## Screening against the audit, as promised

Last tick ended with two of three picks turning out to be rows whose calling
convention contradicts their own name -- functions no source can match, because
the name they must emit is not the name of the code that is there. The fix was to
subtract audit_ret_arity's flagged set from the candidate pool before ranking.

Done properly this tick, with the audit run at --limit 1000 so the list is
complete, it left 26 candidates out of the naked pool. The first pick converted,
and its sibling followed from the same source with the class name changed.

## The thunk already knows the base

The first build of the factory was byte-identical except one relocation: the base
constructor I had invented, ??0Module, resolves to nothing. Rather than pin a
name I made up, the answer was to look at what is already pinned at the
incremental-link thunk the call goes through. Eight module constructors share
0x00002874, and ClientUpdateModule is among them -- the right base for a client
behavior, and a name the ledger already carries.

Naming the base after one of those made the call resolve and the function match.
Inventing ??0Module and pinning it would also have "worked", and would have put a
fabricated symbol in symbols.csv forever.

The sibling then cost nothing. Its vtable addresses differ, but those are DIR32
relocations copied from the target, so the same source with one identifier
changed reproduces a different function exactly.


## Three in a row, and none of them needed a second build

Weapon's destructor, SlaughterHordeContainModuleData's constructor and
MaterialPassClass's constructor all went in first time, from the pool the audit
screen left behind. Nothing new was needed for any of them -- the levers already
written down did the work:

  - ??_L and ??_M spell an array out from their arguments: base, count, element
    size, constructor, destructor. Eight times twenty-four landing exactly on the
    next field is the confirmation that the reading was right.
  - The sar/shl pair after a vector's capacity subtraction gives sizeof(element),
    and no destroy loop before the free means the element has no destructor.
  - An entry vptr store means not novtable; a different vptr stored at the end
    means an inlined base destructor.
  - A refcount base whose constructor is inlined shows up as nothing more than
    the count at +4 set to one.

Two small things were new. MAE rather than UAE in the mangled name means a
protected member, and declaring the destructor public makes the symbol come out
UAE and vanish from the object -- a missing-symbol failure, not a byte mismatch.
And the tail fields have to be written in the order retail stores them:
MaterialPassClass writes +0x28, +0x2C, +0x34, then the byte at +0x30, and address
order would not reproduce it.

The screening is what made the difference rather than any single insight. Picking
from candidates that survive the convention audit means the remaining work is
modelling, and modelling is now mostly transcription.


## One load, two accessors

StructureBodyModuleData's constructor reads the global's string data pointer once
and does everything from that copy: tests it non-null, tests the length word at
+4, then adds eight to it or substitutes the empty literal. Written as two
separate inline accessor calls -- isNotEmpty() and str() on the same member --
that is exactly what MSVC produces, because it shares the load between them.

Which is why the shape is readable in the first place. A single register holding
the member across four uses looks like a hand-written temporary until you notice
the accessors would have produced it anyway.

The null test inside str() is worth pointing at again. The guard above already
proved the pointer good, and the test survives regardless, because str() is a
separate inline function and MSVC does not carry the fact across the boundary.
That is the same effect as delete this inside Release_Ref, seen from the other
side: a check that looks redundant marks where one function ended before the
inliner ran.

## An empty literal is still a literal

HeroModeSpecialAbilityUpdateModuleData pushes a pointer into .rdata and a length
of zero. The pointer is a real empty string, and writing set("", 0) reproduces
it -- the string-ref gate confirms it as an empty-string reference rather than a
literal, which is a distinction the gate makes and worth knowing before assuming
a zero length means no string at all.


## The transposition is a UnicodeString problem, not a stand-in problem

winSetText is the third function to come down to one transposed pair -- retail
writes the temporary's address into the EH slot then loads ecx with it, and the
compile does the reverse. newTemplate had exactly this and the real AsciiString
header fixed it. Here the real UnicodeString does not, and neither did it for
WinInstanceData::setText.

So the split is by type rather than by whether a stand-in was used: AsciiString
temporaries come out in retail's order with the reference header, UnicodeString
temporaries do not. Something about BFME's UnicodeString differs from the
reference's in a way the copy constructor's call site does not reveal -- the call
itself matches, only its surrounding order does not.

The practical response is to screen for it. A body containing mov [esp+N], esp
has a registered by-value temporary, and that is the family; removing those took
21 screened candidates to 17 and cost nothing.

## Offset zero rules out a class introducing its own vtable

Template's destructor destroys five things and the last of them sits at offset
zero, with no vptr stored anywhere in the function. Any class that introduces a
vtable puts the vptr at offset zero and pushes every member to +4, which is
precisely the error the first build produced -- every offset four too high.

Moving the data into a primary base does not rescue it: the base's implicit
destructor is non-trivial, so MSVC emits it out of line and the derived
destructor collapses to a thunk. And the mangling is MAE, protected virtual, so
the class certainly has a vtable somewhere.

Reverted with the constraint stated rather than a guess recorded: something owns
offset zero that is not a vptr, and the virtualness comes from elsewhere. Two
builds were enough to establish that much and not enough to place it.


## A store the optimizer is right to delete

WeaponChangeSpecialPowerModuleModuleData writes zero to +0x210 twice: once before
the two string members are constructed and once after. Moving the three words
into the initialiser list put the first group in the right place -- list entries
run in declaration order ahead of the body -- and reproduced everything except
that repeat, because MSVC eliminates the first store as dead.

It is right to. Nothing between the two writes is opaque: the string
constructors are inline stores through this, and the compiler can see straight
through them. For retail to keep both, something in the real source must break
that visibility, and it is not the member construction.

Recorded as an open question rather than guessed at. The alternative -- writing
the member twice and hoping -- produces a source that says something false about
the code even if the bytes were to line up.

## Choosing not to start

parseDrawCallback was the other candidate this tick and I read it without
building: two inline character loops, a quote scan and a strlen, a strstr through
the import table, and three globals. Every piece is recoverable and the whole is
a poor ratio of builds to bytes, which is the kind of function that has cost me
whole ticks before.

Worth noting the decision explicitly. Reading a disassembly costs one call;
discovering the same thing three builds in costs the tick.


## The arithmetic check I trusted cannot catch this

I have been reading ??_M's arguments as destructor, count, size, base and
confirming the reading by checking that count times size lands exactly on the
next member. For TeamTemplateInfo I read 4 elements of 0x20 where retail has 32
of 4 -- and the check passed, because 4 times 32 and 32 times 4 end in the same
place.

So the span landing correctly confirms the product and nothing else. When count
and size are both plausible sizes the two are indistinguishable that way, and the
only thing that separates them is the push order itself: destructor first, then
count, then size, then base.

Three builds went into structure before this surfaced, and it would have been the
first build if I had read the order rather than the product.

## A polymorphic member, not a polymorphic base

TeamTemplateInfo stores one vptr and stores it at the very end. Deriving from the
polymorphic type gives two stores -- the derived class gets its own table and
writes it at entry -- so the Snapshot at offset zero is a member, destroyed last
because it is declared first.

That alone was not enough. An implicit destructor on a polymorphic class is
trivial and emits nothing, so the member vanished from the output entirely.
Declaring it empty brings back both the vptr store and the twelfth unwind state,
which is how the state numbering starting at 0xB rather than 0xA gets explained
at the same time.

Two facts worth keeping together: where the single store falls says member versus
base, and whether it appears at all says declared versus implicit.


## One instruction separated two identical functions

SpecialPowerStore and RankInfoStore have the same destructor: delete every
element of a vector of pointers, clear it, let the member and base tear
themselves down. Both went in on the first build, and the only thing that had to
be read differently between them was the branch mnemonic.

jb and jbe mean the loop index is unsigned and compares directly against size().
jl and jle mean it is signed, which in source means the size was cast to int --
`i < (int)v.size()` rather than `i < v.size()`. The first test differs to match:
the unsigned form shifts the byte span right by two and tests the result, while
the signed form tests against 0xFFFFFFFC, masking the low two bits off before
checking the sign.

That is a satisfying kind of difference to find, because it is not a judgement
call. The mnemonic is either signed or it is not.

## What is left of a cleared vector

Both functions contain a compare of a register with itself followed by a branch
that can never be taken. That is vector::clear() after inlining --
erase(begin(), end()) reduces to a range copy whose two ends are the same
pointer, so the guard comparing them is trivially true and the copy path is dead
code the compiler kept anyway.

Worth recognising on sight rather than puzzling over: cmp eax,eax is not a
mistake in the disassembly, it is a container operation that optimised away to
almost nothing.


## Two categories of residual, and only one is worth another build

loadTable came down to a single instruction's register allocation: retail loads
the index into eax and this into ecx, the compile uses ecx and edx, and the store
is otherwise identical. Three builds got everything else -- the 0xC entry stride
with key before name, the table pointer at +8 behind a vptr, a named local rather
than an unnamed temporary so the string is read from its frame slot, and the loop
as a for so the next name loads before the pointer advances.

Stopping there was the call, and the reason is worth stating. TeamTemplateInfo
took four builds and the fourth was right, because its residual was a structural
misreading -- count and size swapped -- and structure is something source
controls. Register allocation is not. Across this session I have never moved a
register assignment from source, and every attempt has cost the rest of the tick.

So: a residual that names a structure is worth another build. A residual that
names a register is worth writing down.

## Screening on the byte before

??1Mission is claimed at 0x00BF4EB5, which is not a function start at all. The
byte before it is ff, where every real entry in this image is preceded by int3
padding, and the surrounding bytes repeat a fourteen-byte pattern -- load a
member, add a constant, jump -- so the row covers about fourteen small forwarding
stubs rather than one destructor.

The check is one byte and it would have dropped the row before it cost a
disassembly. It is now part of the screen, alongside the convention audit. Worth
noting that the naked dump still matches byte for byte, so nothing in the normal
gate could ever have flagged this.


## A name pinned to six addresses is a candidate set, not an identification

symbols.csv pins ??1DebugIOFlat to six addresses, all tagged "pinharvest x1
(body)". It pins ??1DebugIOOds to the same six. The harvest never separated the
DebugIO destructors from each other, so any row built by taking one of them is a
coin flip, and ??1DebugIOOds at 0x00890780 was exactly that -- backed by nothing
but a naked __emit dump, which carries no evidence about which class it is.

The bytes there free a split list, null m_firstSplit, then walk a stream list
calling OutputStream::Delete with m_copyDir at +0x114. That is DebugIOFlat's
layout and nothing else's, and the draft for it was already sitting in
debug_io_flat.cpp behind a present-unmatched marker.

## Compile the draft to get a fingerprint to search with

The route in was a wrong address. dtor_pairs' mirror pass follows the first call
in a claimed deleting stub, which pointed at 0x00889620, and the draft compiled
to something completely different. That failure was the useful part: it produced
142 bytes of real codegen, and the frame setup -- push ecx, push ebx, mov ebx ecx,
push esi, push edi, mov [ebp-0x10] ebx -- is a fingerprint that survives every
DIR32 difference. Matching that prefix against all six candidates hit 0x00890780
exactly, and the claim then verified 15/15 first try.

So when a name has an ambiguous pin set and a draft exists, compile the draft
first and let its prefix pick the address. It is cheaper than reading six bodies
and it does not depend on getting the vptr or literal addresses right beforehand.

## A check that had never fired once

find_declared_unmatched has always flagged a present-unmatched marker whose
function is matched from that same file -- the annotation is stale and the marker
lies about the state of the work. It compared the marker's label against ledger
names exactly, and across the whole tree it had reported zero.

Zero was wrong. There are 79 stale markers in 36 files, and every single one is
invisible to the exact test because the labels are abbreviated: the marker says
`??0OutputStream@@` where the ledger says
`??0OutputStream@DebugIOFlat@@AAE@PBDI@Z`. Not one marker in the tree uses the
full name, so the equality test never had a chance to match anything.

A check that has never fired is not evidence of a clean tree. It is equally
consistent with a check that cannot fire, and telling those apart costs one
query -- count what it would have caught under a looser rule.

The fix resolves the label by prefix, but only when the answer is unambiguous:
one marker carrying the label, and one matched row it could mean. Overloads
share an abbreviated label -- ?isPlayer@GameSlot@@ appears three times in
GameInfo.cpp -- and claiming one of them says nothing about the other two, so a
count mismatch is not evidence about any individual marker. GameInfo.cpp is
correctly silent under the new rule.

## What the markers were hiding

In debug_io_flat.cpp six of the nine markers were stale, and the file's real
state was three: one genuinely unmatched destructor, and two functions matched
from asm elsewhere, which is correct bookkeeping rather than pending work. The
count in the commit hook -- "9 unclaimed definition(s)" -- was inflated by two
thirds. cfind, the masked-body search, settled it in one run by placing every
compiled body at an address that was already claimed under its own name.


## Not inventing a symbol to get a match

SupplyTruckAIUpdateModuleData's constructor reads cleanly against the Generals
reference: three counters zeroed at 0x64, 0x68 and 0x6c, and
m_warehouseScanDistance holding 100.0f at 0x70 exactly as the reference
initialises it. BFME then adds a bool at 0x74, 50.0f at 0x78, and two ones at
0x7c and 0x80. All of that is solid.

It stops at the member at 0x84. The reference says AudioEventRTS, but the call
takes a global pointer and a zero, and the callee at 0x000B2CC0 carries only
?b_000b2cc0 -- a synthetic gen-thunk name, not an identification. Converting
would mean declaring a class and pinning a constructor signature I would be
guessing at.

A pin is an assertion about what a body is, and symbols.csv is consulted
project-wide. The DebugIOOds row cost a real correction precisely because
somebody wrote down a name that byte evidence did not support. A guessed
signature that happens to compile to the right bytes is the same mistake with
better luck, so this one is logged rather than forced.

## Where masked-body search pays and where it does not

cfind found nothing on hrawanim.cpp, debug_stack.cpp or camerashakesystem.cpp --
every compiled symbol was either already claimed or ambiguous. On parameter.cpp
the deleting stubs reported 2339 identical placements each. Under ICF a small
body is not a fingerprint at all.

It earns its keep on large distinctive bodies, which is how it settled
debug_io_flat.cpp in a single run. The 9729 unresolved drafts across 453 files
are concentrated in the big engine sources, and that is where to point it -- not
at files whose small functions have already been worked.


## The markers bind by position, not by label

Clearing markers whose label resolves to a matched row broke two files, and the
way it broke them is the useful part. Removing `??0MatBufferClass@@` from
meshmatdesc.cpp did not produce a complaint about MatBufferClass -- it produced
one about TexBufferClass::Get_Element. Removing `??0Format@@` from
debug_debug.cpp exposed Debug::StaticExit.

find_declared_unmatched associates a marker with the definition that follows it,
by position. The label is documentation and nothing checks that it names that
definition. So a marker can carry a label that is genuinely stale while still
being the only thing suppressing a different definition underneath it, and
removing it on the strength of the label alone uncovers work that was never
claimed.

The rule that survives: resolving the label is enough to suspect a marker, never
enough to delete one. Clear it, then run find_declared_unmatched --fail over the
changed files and restore anything that flips. That caught both of these; 29 of
31 removals in this batch were sound and the two that were not cost nothing
because the check ran before the commit.

## Silence from a search is not an answer

cfind on ScriptActions.cpp reported 770 defined symbols and printed 92 lines --
39 already claimed, 53 ambiguous. The other 678 produced no output whatsoever,
because a symbol with zero placements is simply not printed.

Read quickly, that looks like a file with 92 interesting symbols. It is really a
file where 678 compiled bodies do not appear in retail at all, which is a much
stronger statement about how far this source has drifted from the shipped one.
The same shape as the staleness check that had never fired: absence of output
and absence of findings are different claims, and only one of them was earned.


## A minimal reproduction of the by-value temporary transposition

AITunnelNetworkGuardState's constructor came within one transposition of exact.
51 of 53 bytes agree -- the string literal, the base call, the vptr store, the
member zero, the epilogue. The two that do not are adjacent and swapped: retail
runs `mov [esp+8],esp` then `mov ecx,esp`, the compile emits them the other way
round.

This is the same by-value temporary ordering that has blocked UnicodeString
arguments elsewhere, and it now has a 53-byte reproduction with nothing else
wrong, which is worth more than the conversion would have been.

Two things were settled on the way. The argument type is named AsciiString, not
the BFMERetailAsciiString stand-in used elsewhere in the tree -- the pinned
??0State@@QAE@PAVStateMachine@@VAsciiString@@@Z spells the parameter
VAsciiString@@, and the stand-in would encode VBFMERetailAsciiString@@ and miss
the call. And the temporary is owned by the callee: there is no unwind frame and
no destructor call on the way out. Dropping /EHsc, on the theory that the absent
EH frame meant the file should not opt into it, changed nothing at all.

## The ledger note is not the code

The AI state constructors carry notes reading "Open-BFME5 exact C++ isolated raw
AI state constructor". AIAttackAreaState is 54 bytes to this one's 53 and reads
as a sibling worth copying. It is a naked _emit dump. So are the rest of them.

The note describes an intention, not the file, and reading it as a description of
the source cost a detour. Open the file.


## The by-value transposition is not a source or a flag problem

Twelve builds against the 53-byte reproduction, all producing the same two
instructions in the same wrong order -- `mov ecx,esp` then `mov [esp+8],esp`
where retail has them reversed.

Source shapes tried: a declared destructor on AsciiString, a declared copy
constructor, and an explicit AsciiString(...) temporary rather than an implicit
conversion. The first two changed nothing at all. The explicit temporary changed
the frame instead, replacing `mov ecx,esp` with `lea ecx,[esp+8]` -- different,
and further away.

Flags tried: /O1, /Os, /Ox, /Oy-, /Gy, /GF, /Ob0, /MT. /O1, /Os and /Oy- add a
frame pointer the target does not have, which is strictly worse. The rest are
byte-identical to /O2.

So the ordering survives every source shape and every optimisation flag this
toolchain offers. That is worth knowing precisely because those are the two
things one would try first, and it points the remaining explanation somewhere
else -- a different compiler build for the shipped binary, or this function
having been compiled in a translation unit whose contents changed the schedule.
Both are testable, neither is testable from this file alone.

Also worth recording: the store is dead. It writes the temporary's address into
a slot nothing ever reads, in both retail and every compile here. The two
instructions disagree only about which order to be useless in.


## Aliasing keeps a dead store alive

The 50 ConcreteModuleClass::getInstance bodies in fx_particle_system_bulk.cpp are
all naked and none has been converted. The natural source -- a function-local
static and a return -- gets the hard parts right first time: the guard byte test,
the atexit registration, the instance address, the final vptr immediate.

It fails on one store. The constructor sets the base vptr 0x01110850 and then the
derived vptr 0x011113c4 into the same slot, and retail drops the first as dead.
The compile keeps it, and the reason is visible in the constructor's own source:
between the two vptr writes it stores through absolute addresses --
*(void **)0x012f64d0 = this and *(void **)0x012f64f4 = this. Nothing tells the
compiler those cannot be the object's first word, so the earlier store has to
stand.

That is not a fact about inlining, it is a fact about what the source says the
program might do. The idiom of writing globals as casts from integer literals is
what makes these functions tractable at all, and it is also what blocks this one.

Worth knowing before the next attempt: the constructor's standalone body is a
matched row, so the source that produces the aliasing cannot simply be reordered
to suit the inlined copy. Whatever fixes this has to leave the standalone
codegen alone.

## Cost of a build is part of the screen

That file verifies 560 rows on every build. A candidate inside it is not a
cheap three-build experiment, and that should be weighed before starting rather
than discovered halfway through.


## Screen on the things that actually blocked the last three attempts

Three ticks of picking uniformly at random hit three different walls, and all
three were visible in the bytes before a line of C++ was written. Six vptr
stores meant multiple inheritance. A callee whose only name was ?b_000b2cc0
meant pinning a guessed signature. A candidate inside a bulk file meant 560 rows
verified per build.

tools/screen_naked.py now ranks on exactly those: vtable stores in the body,
callees that resolve only to synthetic names, and how many rows the source file
carries. 240 candidates come back with at most one vtable, no synthetic callee,
and a single-row source. That is a queue where a three-build experiment costs
three short builds.

## Four ways not to get a sub-object cursor

StealthUpgradeModuleData zeroes two 0x18 blocks at 0 and 0x18 through a register
-- `mov edx,eax`, six stores, `lea edx,[eax+0x18]`, six more -- and then writes
everything from 0x30 up directly off the object pointer. The second half matches
byte for byte on the first build, including the byte at 0x58 and the -1 at 0x5c.

The cursor does not come from any of the obvious sources. A member type with an
inline constructor, the same constructor moved out of line, and an array of two
elements all produce byte-identical output: direct addressing off eax with no
cursor at all. Replacing the constructor with memset produces one merged 48-byte
rep stosd for both blocks, which is further away still.

That MSVC normalises all three of the first shapes to the same instructions is
the useful part -- it means the cursor is not a matter of how the sub-object's
initialisation is spelled, and the next hypothesis has to come from somewhere
else.

This took four builds against a three-build rule. The fourth was taken on a
specific stated hypothesis rather than another guess, and it was wrong; noting
the overrun because a limit that is quietly relaxed is not a limit.


## The same byte-matching mistake, made again

The first cut of screen_naked counted vtable stores by finding c7 and reading the
immediate four bytes later. That is only correct when the store has no
displacement. `mov [esi+0x38], imm32` encodes as c7 46 38 followed by the
immediate, so the read lands one byte early and returns garbage.

DeflectSpecialPower stores six vtables. The screen reported one, and it went
straight to the top of the queue as a clean candidate -- the exact failure the
screen was written to prevent, reintroduced by the screen itself.

This repository already learned this: the x87 detector in screen_blockers was
byte-matching and flagged 753 of 1041 naked thunks when only 150 really used x87,
and the fix was to decode with capstone. Screening on raw byte patterns for a
variable-length instruction set does not work, and knowing that in one file did
not stop me writing it in another.

Decoding dropped the queue from 240 to 143. Two other filters came out of the
same pass: calls through the import table, which an e8-only search cannot see and
which made a dynamic-import stub look call-free, and bodies with a frame pointer
and a stack frame, which were compiled without the project's -O2 and are a
different matching problem entirely.


## throw() is the lever that removes an EH frame from a new-expression

A factory that does `new T` gets an exception frame even under -EHsc-, because if
T's constructor throws the compiler must call operator delete. Retail's factory
at 0x0012B650 has no such frame, and the difference was worth 22 bytes of
prologue and a pile of state stores.

Declaring the constructors throw() removes it outright. The compile then matches
the allocation, the null check, the INI branch and the epilogue, and the target's
whole opening sequence appears where it should. Any constructor the factory can
reach has to be marked, including the one that is only declared -- an undefined
constructor is assumed to throw.

This generalises to every new-based factory in the tree, and friend_newModuleData
is a large family.

## What is left, and what did not move it

Retail inlines the module data constructor into the factory; MSVC emits a call to
it. __forceinline on the constructor changes nothing -- MSVC 7.1 will not inline
a constructor whose class has two bases, one of them with an out-of-line
constructor of its own.

The class identity came free from the call: the pushed pointer 0x004102C6 is an
ILT jump to ?buildFieldParse@StatusBitsUpgradeModuleData, so the object is that
module data whatever the row happens to be called. Layout follows from the
constructor -- a polymorphic 8-byte base at 0, StealthUpgradeModuleData as a
second base at +8 whose 0x68 bytes land the next store exactly on 0x70, then two
twelve-byte members, total 0x88. A base at +8 is ordinary multiple inheritance
and the existing row note calling it inexpressible is too pessimistic; the
inlining is the real obstacle.

## Read the build's own report before theorising

After editing the // cl: line the build printed "Compile: 0 of 1 TU(s)
(deps-cache: 1 current)" -- it had not recompiled, and I spent two exchanges
reasoning about bytes that came from the previous compile. Deleting the object
and forcing a rebuild produced identical bytes, so the flag was irrelevant
anyway, but that was luck rather than method. The line saying how many
translation units actually compiled is right there in the output.


## A raw address is honest where a name would be a guess

The FireWeaponCollide factory pushes a field-parse function pointer. It points at
an ILT jump whose target carries no name in the ledger, so declaring
`&FireWeaponCollideModuleData::buildFieldParse` would have meant inventing a
symbol and pinning it -- the thing declined on SupplyTruck.

Casting the address instead produces the identical instruction and asserts
nothing: `(void (*)(MultiIniFieldParse &))0x0043ABC0`. The byte `68 c0 ab 43 00`
matched first time. The tree already uses integer-literal casts for globals, and
it works the same way for code addresses.

Worth being clear about when this is right. It is right when the address is
evidence and the name is not. Where a name is already attested -- as
StatusBitsUpgradeModuleData was, by its own buildFieldParse symbol -- use the
name, because it carries information the literal throws away.

## throw() confirmed twice, inlining still open

Declaring the constructors throw() removed the exception frame again, on a second
factory in a different family. Everything outside the constructor now matches
byte for byte: the allocation, the null test, the branch, the pushed literal, the
call to initFromINIMultiProc, the epilogue.

What is left is that retail inlines the module data constructor and MSVC emits a
call to it. Defining the constructor inside the class body does not change that,
and __forceinline on a constructor is ignored outright by MSVC 7.1. Two different
classes now, one with two bases and one with a single base, so it is not about
the inheritance.

Stopping at three builds rather than taking a fourth on a stated hypothesis, as
happened last tick. The hypothesis is written down instead: an exception
specification may itself be what blocks the inliner, and __declspec(nothrow) is
the spelling that carries no specification. That is where the next attempt
starts.


## The constructor-into-new-expression inline is not reachable from source

Two ticks on it now. MSVC 7.1 emits a call to the constructor where retail has it
inlined, and none of these changes it: defining the constructor out of line,
defining it inside the class, __forceinline on it, throw(), __declspec(nothrow),
or giving the base a defined destructor rather than a declared one. Two different
classes, one with two bases and one with a single base.

The exception-specification hypothesis from last tick is refuted. Recording that
plainly because it was the reason for stopping at three builds then, and a
hypothesis worth deferring a tick for is worth reporting the answer to.

Factories of this shape are parked until someone finds the lever. What is not
parked is everything else about them -- throw() removing the exception frame, and
the address-literal for an unnamed field-parse pointer, both still hold.

## /O1 and /O2 each get half of removeAllShadows

Three lists walked identically: read the head, null it, follow the chain at
+0xd4 setting a byte at +4. The structure compiles exactly, alignment padding
included -- 8d a4 24 00 00 00 00 in the right places.

What differs is how the constants are held. Retail keeps 0 in edx and 1 in bl,
pushing ebx to afford the second register, and stores registers rather than
immediates. Under /O2 the compile uses immediates throughout. Under /O1 and /Os
it produces retail's register form exactly -- 33 d2, then 89 51 0c -- but
rotates the loops differently and drops the alignment padding.

So retail is neither: /O2's rotation with /O1's constants. That is worth knowing
because it means the flag sweep cannot settle this one, and the next thing to try
is a source change that raises the constant's value to the compiler -- a static
helper called three times, so the 1 is shared across three inlined copies and
earns a callee-saved register on merit.


## Factor the repetition and the constants find registers

removeAllShadows matched on the first build of this tick, from the hypothesis
written down at the end of the last one.

Three lists are walked identically. Written out as three loops, the compile is
structurally exact -- right rotation, right alignment padding -- but materialises
0 and 1 fresh in each loop as immediates. Written as one static helper called
three times, the same two values are live across all three inlined bodies, so
they earn registers on merit: edx for the zero, bl for the one, with ebx pushed
to afford the second. That is precisely what retail holds them in.

The general shape: when the residual is that retail keeps a constant in a
register and the compile uses immediates, the question is not which flag to pass.
It is whether the source gives that constant a longer life. Repetition written
out three times has three short lives; repetition factored into a callee has one
long one.

This also explains why the flag sweep could not settle it. /O1 and /Os produced
the register form but changed the rotation, /O2 kept the rotation but used
immediates, and retail wanted both -- because the difference was never about the
optimisation level, it was about how many times the source said the same thing.

## Deferring a hypothesis is not the same as abandoning it

Two ticks running I stopped at the build limit and wrote the next hypothesis into
the log instead of spending one more build on it. The first, that an exception
specification blocked the inliner, was wrong. The second was this one, and it
landed on the first attempt.

Both were worth deferring. Stopping preserved the rule, and writing the
hypothesis down meant the next tick opened with a specific test rather than a
fresh guess -- which is the whole value the rule was costing before.


## The vector constructor iterator names the element type for free

FastAllocatorGeneral's constructor starts with a call to ??_L, and its arguments
answer three questions at once. The count and size, 0x80 and 0x18, multiply to
0xC00, which is exactly where the next initialisation begins -- so the array
spans the whole front of the object and nothing has to be inferred about its
extent. The two function pointers it is handed are ??_F and ??1 of
FastFixedAllocator, so the element type is named outright rather than guessed.

??_F is the default constructor closure. It does not get written; declaring the
member array is enough for the compiler to emit it and reference it.

## Unsigned is visible in the branch

The clamp compiled to jl where retail has jb. Making the running size unsigned
fixed it in one build. That is the same signed-versus-unsigned tell already
recorded for loop indices, and it applies just as well to a clamp: jb and jbe
mean the source type was unsigned, jl and jle mean it was signed.

Worth noting the clamp is not dead code even though the running size starts at 16
and only grows. The compiler cannot prove that, so it emits the comparison, and a
source without the clamp would not match.

## rep stosd is an optimiser rewrite, not an intrinsic

The 128-dword zero loop compiles to rep stosd; retail runs an explicit pointer
and counter. /Oi-, which disables intrinsic expansion, changes nothing -- so the
rewrite happens in the optimiser rather than at the memset intrinsic, and no
flag reachable from here turns it off.

The sharing half of the problem did work. Declaring a local zero and assigning
every scalar from it puts the value in one register, and the compile uses al for
the byte at 0xe00 and eax for the three dwords above it, which is what retail
does with cl and ecx. Only the loop form is left.


## rep stosd survives every source shape tried

The do-while pointer walk was the recorded hypothesis and it is refuted: MSVC
still rewrites it. Across two ticks the rewrite has survived an indexed loop, a
pointer walk with a counted do-while, and /Oi-. Retail runs the explicit loop, so
its build did not do this, but nothing reachable from source or flags here
reproduces that.

Two of three hypotheses deferred this way have now landed and one has not. That
is a reasonable rate for something that costs nothing but a line in the log.

## A dead loop is a source construct, not dead code to delete

ProductionPrerequisite's constructor ends with a loop whose trip count is
computed as `mov ecx,eax` then `sub ecx,eax` -- zero, always, and the branch over
it is always taken. It is tempting to read that as garbage.

It is erase(begin(), end()) on a vector of a 4-byte POD, inlined. The copy that
would move the tail down has nothing to move, so the count folds to zero while
the loop survives; the `sar ecx,2` still names the element size, and the final
store of the begin pointer into the end slot is the clear itself. Writing a
source without that erase would lose the whole tail of the function.

The other vector in the same constructor is cleared by a real call, because its
element type is not POD. One class, two vectors, two entirely different shapes
for the same operation -- which is the tell for whether an element has a
destructor.

## Not every synthetic name looks like Gen_<hex>

The screen excluded callees named Gen_ followed by hex. MultiplayerSettings'
destructor calls Gen_setmd_0008eb60, which has a word in the middle and passed
straight through, so a candidate blocked on an unnamed member destructor reached
the top of the queue. Widened to any Gen_ prefix; the queue went from 136 to 134.


## memmove or a copy loop tells you whether the element is a POD

ProductionPrerequisite's second clear runs an element-wise dword loop -- mov edi,
[eax] then mov [edx],edi. STLport only does that when the element is not
trivially copyable; a plain enum or int gets memmove instead. So the science
entry is a four-byte class with its own assignment operator, not the bare enum
the Generals reference declares, and giving it one took the compile from a folded
`cmp eax,eax` with no loop at all to retail's exact sequence.

That is a second, independent reading of the same vector alongside the one
already recorded. The element's destructor decides whether erase is a call or is
inlined; the element's copy assignment decides whether the inlined form is
memmove or a loop. Both are visible without knowing the type's name.

## clear() folds harder than erase(begin(), end())

Written as clear(), the compile folded the whole tail away -- the trip count
became `cmp eax,eax`, the copy loop vanished, and forty bytes of retail had no
counterpart. Written as an explicit erase(begin(), end()) the arithmetic
survives: the subtraction, the sar that names the element size, and the guarded
loop.

They are the same call in STLport. The difference is only how much the optimiser
sees through, and the more explicit spelling is the one that reproduces retail
here.

## Three separate things, each necessary

Getting this to one register pair took stlport with a real std::vector, the
explicit erase spelling, and a non-trivially-copyable element. None of the three
would have shown up as an obvious next step from the others, and each was
readable from the bytes: the mangled erase name demanded the real container, the
surviving arithmetic demanded the explicit spelling, and the copy loop demanded
the non-POD element.


## A constructor's exception frame comes from members, not from the class

SegLineRendererClass's copy constructor has an SEH frame and one unwind state.
Declaring a destructor on the class itself does not produce one, which is right --
destroying a complete object is the caller's job. Declaring a destructor on a
member does, immediately, because now the constructor owns cleanup for what it
has already built if the body throws.

So the presence of a frame in a constructor is a statement about the members, and
the number of states counts the destructible ones. One state here means exactly
one member has a destructor.

## Where the frame-slot store sits says which member it is

With the destructor on the member at offset 4, everything matched except one
instruction's position: retail writes this into the frame slot immediately after
zeroing the register, before the first member store, while the compile writes it
two instructions later, after the member at offset 4 is loaded.

That store is the registration, and it is emitted before the first destructible
sub-object is constructed. Retail registers before the store to offset 0, which
puts the destructor on the member at offset 0 -- the texture pointer, held by
something with a destructor rather than being a raw pointer. The reference's
operator= uses REF_PTR_SET on it and the destructor uses REF_PTR_RELEASE, which
fits.

The general point is that the registration's position is evidence, not noise. It
localises which sub-object owns the cleanup, the same way the state count says
how many there are.


## The frame-slot store localises the unwind owner, confirmed

SegLineRendererClass matched on the first build of this tick, from the hypothesis
recorded at the end of the last one: move the declared destructor off the member
at offset 4 and onto the member at offset 0.

The reasoning was that the store of this into the frame slot is emitted before
the first destructible sub-object is constructed. Retail emits it before the
store to offset 0; with the destructor at offset 4 the compile emitted it two
instructions later, after offset 4 was loaded. Nothing else in 148 bytes
differed, so the position was the only evidence available -- and it was enough.

Three readings of a constructor's exception frame now stand together. Whether a
frame exists at all says some member has a destructor, since a destructor on the
class itself produces none. How many states there are counts the destructible
members. And where the frame slot is written says which member owns the state.

Three of four deferred hypotheses have now landed.


## A stack local's size is a fact about the class, and it shows in one instruction

CampaignManager::init is three lines and it failed on `sub esp`. Retail reserves
0x84C; the compile reserved 0x2438 and took a __chkstk probe, because every INI
header in this tree carries an 8K read buffer. BFME's INI does not have one: 0x848
is the two 1028-byte line buffers plus about sixty bytes.

Declaring INI in the function's own translation unit fixed it without disturbing
CampaignManager.cpp, which needs the real header for field-parse tables
referencing INI::parseAsciiString and INI::parseBool. Shadowing a header for a
whole TU to fix one function is the wrong shape when the rest of the TU depends
on it.


## The string-ref check catches what the byte gate cannot

CampaignManager::init passed the byte gate while its source literal read
DataINICampaign.ini. The backslashes had been lost, MSVC dropped them as unknown
escapes, and the bytes still matched because what the instruction encodes is the
literal's ADDRESS, not its text -- and the address is copied from the target.

The string-ref verifier compares the text and failed the commit. Without it the
row would have been recorded as clean C++ that produces a different string, which
is worse than a naked dump: it looks correct and is not.

Two things follow. A literal that only appears as a relocation is not verified by
byte equality, so the string check is doing real work and a failure there is not
a formality. And when a heredoc collapses backslashes -- as one did here, twice,
making a search string and its replacement identical so the fix silently no-opped
while reporting success -- build the strings from character codes and assert the
two differ before replacing.


## A magic divide names the element size

PropagandaTowerBehaviorModuleData's destructor tears down a vector inline and the
arithmetic says exactly what is in it. Multiply-high by 0x2AAAAAAB then sar 3 is
a divide by 48, and the lea eax,[eax+eax*2] with shl 4 that follows multiplies
the count straight back to bytes. Forty-eight byte elements, and no destroy loop
survives, so they are trivially destructible.

The other vector in the same class is destroyed by an out-of-line call, which
says its element has a destructor. One class, two vectors, and both element types
readable without a single name.

Landed on the first build by composing two existing conversions -- the POD-vector
base and novtable shape from HealContainModuleData, the vector<AsciiString>
member from AnimalAIUpdateModuleData. When the shape is already solved twice,
the work is picking the right two files.


## Assignment order in the body is not declaration order

WaterTransparencySetting assigns the river multiplier at 0x34 before the blend
flag at 0x2c, which is the reverse of how the members are declared. Member
construction follows declaration order and is not negotiable, but statements in
the body are emitted in the order written, so the two can disagree and the bytes
show which is which.

The same function also shows what a constructor does not do. The two words at
0x38 and 0x3c are members, and retail never writes them -- they take no INI field
and are runtime-only state. A source that helpfully zeroes them would be three
stores longer than retail and would not match. Absence of a store is evidence as
much as a store is.

## Three conversions off one triage pass

CampaignManager::init, PropagandaTowerBehaviorModuleData and
WaterTransparencySetting all landed on the first or second build, in one tick,
having been picked by a fan-out that classified twelve queue candidates against
the levers and blockers already on record.

The contrast with the preceding ticks is the point. Sampling the queue uniformly
kept landing on the FXParticleSystem ModuleInfo family, on mis-anchored rows and
on the by-value transposition -- all already known-blocked, none of which the
size-ordered screen could see. Screening on structure got the pool down to 133;
classifying against what is already known got three conversions out of the next
three attempts.


## Statement order in a constructor body is recoverable from the schedule

ToppleUpdateModuleData needed two builds and the second changed nothing but the
order of five assignments. MSVC groups stores that share a value -- the two 0.2f
fields go out together through eax, the four false flags through bl -- but it does
not reorder across those groups. So the emitted order is the source order with
same-valued stores coalesced, and reading it back gives the statement order
directly: the flag at 0x24 sits between the bl run and the two float immediates,
so it is written there.

That makes body order a recoverable fact rather than a guess, which is worth
knowing because it is otherwise the sort of residual that reads as scheduling
noise and gets abandoned.

## Four conversions from one triage pass

CampaignManager::init, PropagandaTowerBehaviorModuleData, WaterTransparencySetting
and ToppleUpdateModuleData, all in two ticks, all first or second build. The
preceding six ticks landed one conversion between them while sampling the queue
uniformly at random.

The difference is not effort, it is that candidates are now rejected on evidence
before a build is spent: the ModuleInfo family on vptr sinking, mis-anchored rows
on their own arity, unnamed callees on the naming rule. Screening on structure
got the pool to 133; classifying that pool against what is already known is what
turned it into conversions.


## A recipe is worth more than a conversion

CampaignManager::init took a tick to work out: TU-local INI at 0x848 so the frame
does not take a __chkstk probe, and the shim AsciiString so the by-value
temporary comes out in retail's order. ControlBarResizer::init is the same
function with a different literal and took one build and no thinking.

So after landing something, ask what else has that shape. Here the answer was
small -- three functions in the image build a stack-local INI and call load -- but
finding that out cost one query and closed the family for good. Two converted,
one blocked, nothing left to rediscover later.

## Dead code that survives in retail and not in the compile

ControlBarSchemeManager::init loads two INI files, which reproduces exactly, and
then walks its scheme list counting nodes into edx and never stores the count.
It is size() with the result discarded, and MSVC deletes it.

The knock-on is what makes it unfixable from source rather than merely different:
with the count gone, `this` is unused, so the push esi that saves it disappears
and every stack offset in the function shifts by four. One eliminated loop moves
the whole frame.

This is the same class as the duplicate zero store in
WeaponChangeSpecialPowerModuleModuleData -- retail's build kept dead code that
this toolchain removes. Two functions now, so it is worth naming as a family
rather than filing twice as a curiosity.


## Run the control before believing a negative

A triage pass argued that ??1Template@@MAE@XZ is a mis-named row, partly because
no vtable anywhere references its address. Checking the same property on
??1PlayerUpgradeSpecialPowerModuleData gave the same answer, which looked like
confirmation of a pattern.

It is not. The control settles it: ??1PropagandaTowerBehaviorModuleData, which is
genuinely a virtual destructor and was converted byte-exact this session, also has
zero references in every section of the image. Vtable slots hold the deleting
stub ??_G, and ??_G calls ??1 -- so a virtual destructor is never referenced from
a vtable, and finding no references says nothing at all.

The cost of the control was one line added to a query I was already running. The
cost of skipping it would have been retiring a correctly-named row on reasoning
that proves nothing, which is precisely the mistake the DebugIOOds correction was
about.

## A body that no class can produce

PlayerUpgradeSpecialPowerModuleData's destructor tears down a vector<AsciiString>
whose begin, end and capacity sit at 0, 4 and 8, and it stores no vptr anywhere.
A UAE destructor means the class is polymorphic, which puts the vptr at offset 0
and every member after it; __declspec(novtable) suppresses the store but not the
slot. So no faithful class definition produces these bytes.

That makes it an ICF-folded ~vector<AsciiString> wearing a retail name rather
than a conversion candidate, and the ledger holds only the one name because that
is all the harvest recovered. Landing it would mean the alias mechanism, not a
class -- worth recognising early, because the body reads as a perfectly ordinary
destructor right up until the offsets are checked against what the mangling
implies.

## The stash without the frame

Two facts about GameLODManager::findStaticLODLevel looked contradictory. Retail
emits `mov [esp+0xC],esp` before setting up the by-value AsciiString argument --
the /EHsc temporary stash, reusing the dead key slot -- and retail carries no SEH
prologue at all. /EHs-c- reproduces everything except the stash and lands four
bytes short; /EHsc reproduces the stash and adds a 78-byte frame.

They are only contradictory if the frame is unavoidable under /EHsc. It is not.
The frame exists to destroy the inner-scope key if the lookup throws, so the frame
is a property of what the lookup is allowed to do, not of the exception model.
Declaring the find shim `throw()` removes the reason for the frame and leaves the
stash, and the function matched at 106 bytes on that build.

This is the residue the sibling OptionPreferences::getIdealStaticGameDetail was
reverted over, logged in re_attempts as "not EH bookkeeping: /EHsc adds a full SEH
prologue retail does not have". The conclusion was half right -- it is EH
bookkeeping, and the prologue is separable from it. That accessor has the same
shape around the "IdealStaticGameLOD" key and should now go in the same way.

The general form: /EHsc versus /EHs-c- is not one lever but two, the temporary
bookkeeping and the unwind frame. When retail shows one without the other, the
throw-specifications on the callees are what tell them apart, and they are worth
reaching for before concluding the exception model is wrong.

## Three LOD rows look rotated

Converting 0x00090970 turned up an identity problem in its neighbours, and the
evidence is worth banking even though the fix is not yet determined.

0x0007E0F0, filed as OptionPreferences::getIdealStaticGameDetail, is Zero Hour's
GameLODManager::findStaticLODLevel almost line for line: `cmp [esi+0x1708],-1`
is `m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN`, the six pushes plus
`lea edi,[esi+0x1710]` and `add esp,0x1C` are the seven-argument
`testMinimumRequirements(&m_videoChipType,NULL,...)`, `mov [esi+0x1708],0` is the
assignment to STATIC_GAME_LOD_LOW, and `mov eax,[edi]; test eax,eax; jne;
mov [edi],1` is the DC_UNKNOWN-to-DC_TNT2 fixup. A 942-byte hardware benchmark is
also not a shape any preferences accessor takes.

That matters because 0x00090970 is filed as GameLODManager::findStaticLODLevel,
and one binary cannot hold that name twice. 0x00090970 keys a map at this+4 --
the OptionPreferences/CustomMatchPreferences skeleton, not GameLODManager -- so it
reads as a preferences accessor for "StaticGameLOD". Its neighbour 0x00090900 has
the identical shape over "IdealStaticGameLOD" and returns -1 on a miss, which is
an Int return, not the _N its useCameraInReplays row claims.

So the three rows appear rotated one step. What blocks fixing it is that only two
of the three destinations are known: 0x0007E0F0 is findStaticLODLevel and
0x00090900 is getIdealStaticGameDetail, but nothing in symbols.csv or exports.csv
names the "StaticGameLOD" accessor at 0x00090970, and repointing 0x0007E0F0 while
0x00090970 still carries the name would put findStaticLODLevel on two addresses.
Retiring 0x00090970's name without a replacement also drops a byte-verified claim.

0x00090970 is converted and byte-exact regardless -- the offsets it encodes are
literal, so only the row's name is in question, and that name predates the
conversion. The next step is xref work on 0x00090970's callers to name it, after
which all three can move together.

## novtable hides a base's unwind entry

BuildListInfo's destructor tracks unwind states 3/2/1/0 for three AsciiString
members. Three members should give 2/1/0/-1, so the extra state is the base
subobject, and getting the count wrong is what made a first attempt three bytes
short rather than merely mis-registered.

The cause was `__declspec(novtable)` on the stand-in base. It suppresses the
vptr store, and with it the base's entry in the unwind table, so every state
number shifts down by one. Dropping novtable restored 3/2/1/0 and the size.

Worth knowing as a diagnostic in both directions: if compiled EH states are
uniformly one below retail's, look for a base whose destructor the compiler
decided it need not unwind, and novtable is the usual reason. The state numbers
are a member count you can read straight off the disassembly before writing any
source -- retail's highest state plus one is how many destructible subobjects the
class has, bases included.

## novtable is the switch for interim vtable stores

A module constructor that delegates to a base and then carries interface bases
writes each interface vtable twice: once as the interface subobject is
constructed, once when the most-derived class installs its own. Retail's
ObjectWeaponStatusHelper writes each only once, and the compile was 14 bytes
long -- exactly the two extra 7-byte stores.

`__declspec(novtable)` on the interface bases removes them. It tells the compiler
the base is never instantiated on its own, so the interim initialisation is
dropped and only the most-derived stores remain. With it the ctor matched at
107/107.

Two of these now point the same way, in opposite directions. Here novtable was
needed to remove stores; on BuildListInfo's destructor novtable had to be removed
to restore a base's unwind entry. So read it as one knob with two visible
effects -- the interim vptr store and the unwind entry -- and set it by which of
those retail shows, not by habit.

This matters beyond one function: the (Thing *, const ModuleData *) module ctors
are a large family with the same skeleton, an SEH frame, a base call through an
ILT thunk, and three vtable stores at +0/+0xC/+0x10. The recipe is a
single-virtual anchor on the module base, two novtable interface bases, a
<Name>Base holding the ctor declaration pinned to the thunk in symbols.csv, and
the real body from the Zero Hour header.

## Where a store sits tells you which class owns the member

Module constructors write their interface vtables twice when the interface bases
are not novtable: once as each subobject is constructed, once for the
most-derived set. Any member store that lands *between* those two groups cannot
be in the constructor body, because the body runs after the most-derived vtables
are installed. It is a base subobject's member initialiser.

BridgeTowerBehavior matched at 96/96 on that reading alone: the two zeroed words
at +0x1C/+0x20 sit between the interim and most-derived groups, so they belong to
the fourth interface base and are initialised in its constructor, and the derived
body is empty.

The reading has a limit worth knowing. SiegeDeploySpecialPower has four zero
stores before the vtable group and eleven after; moving the first four onto the
last base is right, but the eleven in the body then hoist up to join them,
because they all share the one zeroed register and MSVC groups such stores freely
across the vtable writes. So the rule places members reliably only when nothing
remains on the other side to be hoisted. Where stores appear on both sides of the
vtable group, source ordering does not reach it.

## Which module ctors are reachable: look for a call after the vtables

Seven module constructors in, the failures separate from the successes on one
observable, and it can be read off the disassembly before writing any source.

MSVC will hoist the constructor body's member stores above the most-derived
vtable writes. Retail does not. So a conversion only lands when nothing needs to
sit after those writes, or when something anchors it there.

  matched   ObjectWeaponStatusHelper   no member stores, call after
  matched   GeometryUpgrade            string ctor + releaseBuffer call after
  matched   WeaponModeSpecialPowerUpdate  one byte store, call after
  matched   BridgeTowerBehavior        nothing after the vtables at all
  reverted  TensileFormationUpdate     three stores after, no call
  reverted  SiegeDeploySpecialPower     eleven stores after, no call

A call after the vtable group pins the stores before it; with no call they float
up and no source arrangement -- body assignment or member-init list -- brings
them back down.

So when picking from the family, disassemble first and take the ones whose member
stores are either absent after the vtable group or followed by a call. The ones
with bare trailing stores need a different lever than source ordering, and there
is no point spending builds on them until someone finds it.

## Split the vtable base from the field base

AnimalAIUpdate came down to one instruction out of place: retail stores the
+0x340 interface vtable and only then materialises the zero it uses for six
member writes, while the compile hoisted `xor eax,eax` above the vtable store.

No ordering inside a single class reaches that, because the vtable write and the
member initialisers both belong to the same subobject and MSVC schedules them
together. Splitting them into two bases does: a four-byte polymorphic base
carrying the vtable at +0x340, then a non-polymorphic base holding the fields and
zeroing them in its constructor. Base subobjects are constructed in declaration
order, so the vtable write is pinned ahead of the zero. 118/118 on that build.

Generalises the same way as the earlier reading: when two groups of stores must
stay in a fixed order and no source ordering inside one class produces it, ask
whether retail's layout is telling you they belong to different subobjects.

## Refining the tail-store rule: immediates do not hoist

The post-vtable-store rule said trailing member stores float above the vtable
group unless a call anchors them. HordeTransportContain has two trailing stores
and no call, and matched anyway.

The difference is what they store. TensileFormationUpdate and
SiegeDeploySpecialPower write a shared zeroed register, and MSVC groups every
such store together, which is what carries them over the vtable writes.
HordeTransportContain writes two immediates -- a byte 0 and -1000 -- so there is
no shared register and nothing to group with, and they stay where the source puts
them.

So the rule reads: trailing stores are safe when they are immediates or when a
call follows, and unreachable when they share a materialised constant with stores
on the other side of the vtable group.

## A node allocation size fixes the element type

HotKeyManager's constructor has an empty body; everything is member
construction. Each of its two maps allocates a single 0x1c node and wires it as
its own header -- colour byte zeroed, parent null, left and right pointing back
at the node.

Twenty-eight bytes is the arithmetic that names the element. Sixteen of those are
the red-black node header (colour plus three pointers), so the value type is
twelve, which beside a four-byte key fixes the mapped type at eight. No element is
ever inserted, so nothing else in the function constrains it -- the allocation
size is the only evidence, and it is enough.

That is the same move as reading a vector's element size off its magic divide,
applied to a tree instead.


## Two sessions, one ledger

Another session pushed seventy-seven commits while this one worked, and the
rebase surfaced exactly one conflict: docs/lessons.md. functions.csv and
re_attempts.log merged silently because .gitattributes gives them merge=union,
and lessons.md is append-only in the same way but was never listed. It is now.

The mistake worth recording is mine rather than the tooling's. My resolver's
pattern did not match CRLF line endings, so it asserted and changed nothing --
and I ran git add and rebase --continue anyway, committing three conflict
markers into the file. The assert did its job; I ignored it because it was two
commands earlier in the same block.

An assert that fires and a command that proceeds regardless is worse than no
assert, because the failure is now silent at the point it matters. When a guard
fires in a batch, the rest of the batch is void.


## A zero displacement means the symbol, not the code

friend_makeVeterancyUpgrade compiled to retail's exact instruction sequence with
one call left as e8 00 00 00 00. A zero REL32 is not a scheduling difference or a
wrong address -- it is the linker having nothing to resolve, because the symbol
the source declared is not the symbol that is pinned.

Here the culprit was a return type. nameToKey mangles as
?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z, where ?AW4NameKeyType@@
says the return is an enum. Declaring NameKeyType as a typedef to unsigned int
mangles the same function as ...QAEIPBD@Z and nothing matches. Making it an enum
fixed it in one build.

So when a call comes out zeroed, stop reading the disassembly and read the
mangled name of the callee instead. W4 is an enum, I is unsigned int, H is int,
and they are three different functions as far as the linker is concerned.


## Output parameters are not initialised, and that shows

calcDeltaScroll passes two Vector3 locals to CameraClass::Project as destinations.
Giving them a zero constructor added six stores retail does not have. They are
output parameters -- the callee fills them -- so the source declares them and
says nothing more, which needs a do-nothing default constructor rather than the
three-float one.

That is the same rule as the untouched words in WaterTransparencySetting, in a
different costume: what a function does not write is as much a constraint as what
it does. Here it also decides the shape of the class being modelled, because a
Vector3 with only a three-argument constructor cannot express an uninitialised
local at all.

## Symbol-not-found is an access-modifier message

The first build failed with "symbol not found in object" rather than a byte
mismatch, because the method was declared public. The row's name says AAE, which
is private; public mangles QAE and nothing in the object matches.

Worth separating the two failure modes when reading build output. A byte
mismatch means the code is wrong. Symbol-not-found means the declaration is
wrong -- access, return type, constness or parameter types -- and no amount of
staring at the disassembly will help until the mangled name is read back.


## The vptr-sinking blocker is narrower than recorded

ParticleSystemTemplate's constructor sits in the FXParticleSystem family that
vptr sinking was recorded as blocking wholesale, and it converted on the first
build with the vptr store exactly where retail has it, ahead of the member copy
constructor.

The difference from the family members that really are stuck is what the body
contains. LifeEventModuleInfo and DefaultPhysicsModuleInfo call setRange three
times and their vptr stores sink past those calls. This one's body is nothing but
stores, and the store stays put.

Working hypothesis from one positive case rather than a proof: the sink needs a
call in the body to move past, not merely statements. Worth acting on, because it
means the family should be re-screened on what its bodies call instead of skipped
by name. A blocker recorded at family granularity is cheap to write and expensive
to believe.

## open(path, "wb") truncates before the argument is evaluated

This emptied functions.csv -- all 94171 rows -- in a single statement:

    io.open(p, "wb").write(raw.replace(m.group(0), new, 1))

A regex had missed, so m was None and m.group(0) raised. But Python evaluates
io.open(p, "wb") first, and opening for write truncates immediately; the
exception then landed after the file was already zero bytes. The assert I would
normally have written was not there, and the guard that did exist -- the crash
itself -- arrived too late to protect anything.

Compute the new bytes into a variable, assert on them, and only then open the
file. The pattern that is safe reads:

    out = raw.replace(old, new, 1)
    assert len(out) > len(raw)
    io.open(p, "wb").write(out)

Recovery was one git checkout because the file is tracked, which is the only
reason this cost minutes rather than the session.


## The shim closes the by-value transposition for good

AITunnelNetworkGuardState sat parked for several ticks on the `mov [esp+8],esp` /
`mov ecx,esp` pair, and the note said the transposition survived every source
shape. It did not survive using the real shim AsciiString instead of a
hand-rolled four-byte stand-in. Five 46-byte State constructors -- AIBusyState,
FailureState, ContinueState, AIWaitState, AIDeadState -- then converted on the
first build each.

Two ticks ago I recorded this correction for CampaignManager and did not go back
and re-try the functions I had already parked on it. Parked rows should be
re-queued when the blocker that parked them is retired; that is a cheap sweep and
it was worth five conversions here.

## A shape screen hides exactly what it matches on

Seven candidates were selected because their bytes matched the family pattern
byte for byte. Three of them failed, and the difference was a single call
displacement -- the base constructor. They resolve to 0x0014F280 and 0x0018D890
where the others resolve to State's 0x000A19E0, so those classes derive from an
intermediate class rather than from State directly.

The relocated operand is excluded from a shape match by construction: that is what
makes the screen useful across a family, and it is also the one field that can
hide a structural difference. When a shape-selected batch fails, look at the
relocations first, because they are the part the screen was blind to by design.

My first reading of this was that retail used a different ILT thunk for the same
function. That was wrong -- only one thunk targets State's constructor -- and
resolving the jump chain took one query that I should have run before forming the
theory.


## Screen on behaviour, not on byte shape

The first pass at this family screened on the exact 46-byte pattern and found
seven, three of which had the wrong base class. Screening instead on what the
body does -- an AsciiString constructor call followed by exactly one more call,
with a literal pushed -- found thirty-one across every size from 46 to 124 bytes,
and grouped them by the address of that second call.

Grouping by the base's address is what makes the batch safe. Thirteen call
State's constructor, thirteen call 0x0014F280 and five call 0x0018D890, and those
last two groups are the ones that failed when a shape screen lumped them in with
the first. The property that decides whether a source compiles is the base class,
and it is directly observable; matching bytes around it is not a proxy for it.

## The vptr store scheduled itself

Retail puts the vptr store first in the 53-byte members of this family and last
in the 54-byte ones. Writing the added members as initialisers in both cases
produced retail's order each time without the source saying anything about it --
MSVC sinks the store past a run of same-valued member stores and leaves it in
front of a single immediate one.

Worth knowing because vptr placement has been treated here as a blocker to be
worked around. In this family it is simply a consequence of what the members are,
and the source that describes the members correctly gets the placement for free.


## Naming a base class from thirteen callers and a reference header

Thirteen retail State subclasses call 0x0014F280 as their base constructor, and
it has no ledger row. The reference declares AIInternalMoveToState with exactly
that set of children -- AIMoveToState, AIMoveOutOfTheWayState, AIEnterState and
the rest -- and its constructor takes StateMachine* and an AsciiString by value,
which is precisely why the body at that address copy-constructs the string a
second time before calling State.

That is enough to pin the name. It is not an invention: the caller set, the
signature and the by-value copy all agree, and any one of them alone would not
have been. Four conversions followed immediately.

## Correcting the vptr-sinking narrowing

Two ticks ago I proposed that the sink needs a call in the body to move past,
from one positive case. That is wrong. AIMoveAndEvacuateState has no call after
its base constructor and MSVC still sinks the vptr store past three member
stores, where retail keeps it in front.

What the evidence actually supports: with a single added member, compiler and
retail agree on placement. With several, MSVC always sinks and retail sometimes
does -- AIMoveAndTightenState sinks in retail too, AIMoveAndEvacuateState does
not, from sources that look the same shape. So the rule is not about calls and
is not yet known; the honest statement is that one member is safe and more than
one is a coin toss.

A hypothesis from one positive case earned a re-test, got one, and lost. That is
the cheap outcome -- the expensive one would have been screening the family on it.


## Two base classes named the same way, and one access modifier that mattered

TurretState was recovered exactly as AIInternalMoveToState was: five retail
subclasses call one unnamed address, the reference declares a class with exactly
that set of children, and its constructor signature matches what the body does.
All five converted on the first build.

The difference between the two was the access modifier. AIInternalMoveToState's
constructor is public and mangles QAE; TurretState's is protected and mangles
IAE. Pinning the public spelling would have produced a symbol nothing calls, and
the failure would have read as symbol-not-found rather than as a byte mismatch --
which is the tell for a declaration problem, already recorded. Reading the
reference's access specifier before writing the pin cost nothing and saved a
build.

## The class name is not the state name

TurretAIHoldTurretState passes "AIHoldTurretState" as its state name. The class
and the string disagree, and nothing but the pushed literal shows it -- every
other member of the family passes its own class name, so a generator that
assumes the two are equal produces five correct files and one that fails.

Worth checking per candidate rather than deriving, because it is exactly the kind
of detail a family template makes invisible.


## The vptr blocker is only the disagreement, not the sink

AIAttackSquadState has two zeroed members and retail sinks its vptr store past
them. MSVC sinks identically, and it matched on the first build.

That sharpens what was recorded last tick. The blocker is not "more than one
member" -- it is only the subset where retail keeps the store in front and MSVC
sinks it anyway. Where retail sinks, the compiler agrees for free and there is
nothing to work around. AIMoveAndEvacuateState is blocked because retail does not
sink; AIAttackSquadState is not blocked because retail does.

So the screen for this family is: read whether the vptr store precedes or follows
the member stores in retail, and only park the ones where it precedes them and
there is more than one member.

## A parameter that is never stored

AIAttackSquadState takes an AttackExitConditionsInterface* and does nothing with
it -- retail zeroes both members and ignores the argument. The signature is not
optional, because it is in the mangled name and the caller pushes it, but the
body must not use it.

Writing the obvious source, which assigns the parameter to the member at 0x24,
would have produced a store retail does not have. The argument being present in
the signature says nothing about whether the body touches it.


## Half the parked cases were not blocked at all

Last tick four constructors were parked as vptr-sinking failures. Applying the
sharpened screen -- park only where retail keeps the store in FRONT of several
member stores -- showed two of them have retail sinking as well, so the compiler
was never disagreeing about placement.

Their actual defect was store order. Retail writes the flag at 0x54 before the
word at 0x50, and an initialiser list emits members in declaration order, which
cannot express that. Moving the two assignments into the body, in retail's order,
matched both on the first build.

Two lessons already recorded separately turn out to compose: body statements are
emitted as written, and the vptr blocker is only the disagreement. Neither alone
would have unparked these; the combination did, and the cost was one build each.

Worth being blunt about the failure mode. Attributing a failure to a known
blocker is the cheapest possible explanation and it is wrong half the time here.
A blocker should be assigned only after the specific evidence for it -- in this
case which side of the member stores the vptr sits on -- has actually been
checked.


## The vptr disagreement has a third form: how far it sinks

AIIdleState writes five members and its body order already matches retail store
for store. The only difference is where the vptr lands: retail sinks it past all
four of the leading member stores, MSVC sinks it past the two that share the
zeroed byte register and emits it there.

So the disagreement is not simply in-front versus behind. It is how far the store
travels, and the compiler stops at the end of a same-valued run while retail
carries on past stores of different values. Two of this family are blocked
because retail keeps the store in front, and this one because retail moves it
further -- same underlying cause, three surface forms.

That also means the screen needs stating more carefully than last tick: compare
the vptr's position against the member stores exactly, not just which side it
falls on.


## What the vptr sink actually does

Enough cases have now been measured to state the compiler's half exactly. MSVC
sinks a constructor's vptr store to the end of the leading run of member stores
that share a value, and no further. AIWanderState zeroes ten members and then
writes a byte to 1; the store lands after the ten and before the one. AIIdleState
zeroes two bytes and then writes 1 and 0xffff; the store lands after the two.

Retail's half is not predictable from anything measured so far. It sometimes puts
the store ahead of every member store, sometimes after all of them including
differing values. A function matches when the two happen to coincide -- which is
why single-member cases and uniform-value tails nearly always work, and why a
tail with a differently-valued store at the end nearly always fails.

That turns the blocker into a screen rather than a mystery. Before writing a
constructor in this family, compare retail's vptr position with the end of the
leading same-valued run. If they agree the function is convertible; if not, it is
parked and no ordering of the source will change it, because the source cannot
address vptr placement at all.


## Turning the vptr rule into a screen

The characterisation from last tick is mechanical enough to run: predict MSVC's
vptr position as the end of the leading run of same-valued member stores, treat a
run shorter than two as no sink at all, and compare against where retail actually
put it. tools/screen_vptr.py does that and splits the naked constructor pool into
16 convertible and 35 parked.

It is calibrated against every case measured by hand -- the single-member ones
that agreed at position zero, the uniform-value tails that matched, and
AIWanderState, AIIdleState and AIMoveAndEvacuateState which did not. That is the
part worth insisting on: a screen built from the successes alone would have had
no way to be wrong.

The value is not the sixteen it found. It is that thirty-five constructors now
have a reason not to be attempted, and the reason is checkable rather than
remembered.

## An unwritten word is still a member

PhysicsBehaviorModuleData writes twenty-four members and every offset was four
too low. The vptr sits at 0 and the first written member at 8, so a word lies
between them that the constructor never touches -- and it still has to be
declared, because everything after it depends on where it ends.

The same reading as the untouched tail words in WaterTransparencySetting, from
the opposite direction: there, absence of a store meant do not initialise; here it
means do not forget to declare.


## The screen's two verdicts are not equally sound

GarrisonContainModuleData was the screen's pick and it failed. Base pinned,
all eighteen member offsets right, and the vptr still landed two stores late.

The cause is in the screen itself. It predicts where MSVC will sink the store by
reading retail's instruction stream, which means it inherits retail's register
allocation. Retail keeps 1.0f in ecx beside a zero run in eax, so its run of
register-sourced stores ends at eleven. The compile put both constants in eax,
making the run thirteen, and the store travelled two further.

That asymmetry is worth stating in the tool and not just here. A "parked" verdict
is sound: retail puts the store where no allocation of registers could place it,
so the function cannot match. A "convertible" verdict only means nothing in
retail's own bytes rules it out -- the compiler still gets a vote, and it votes
with its allocator.

Half a screen that is reliable is still worth having. The thirty-five parked
constructors are genuinely not worth a build; the sixteen are worth exactly one
each.


## Floats reach the FPU by being passed, not by being assigned

Get_Diffuse copies three floats and retail does it on the x87 stack: three loads,
an exchange to undo the stack's reversal, three stores. Writing three field
assignments gives integer moves instead, and so does a whole-struct copy -- MSVC
treats a float lvalue copy as a bit pattern.

What does put them on the FPU is passing them by value into an inlined setter.
That produced real fld and fstp instructions in the right places. It still was not
exact: MSVC folded one of the three back to an integer move where retail kept all
three on the stack, and that is instruction selection rather than anything the
source can express.

The transferable part is the mechanism. If retail uses x87 for something that
looks like a plain copy, the source is passing the values somewhere, not
assigning them.

## Calling convention is part of the name, and can be wrong in the ledger

getListboxBottomEntry reads its parameter from ecx in the first instruction and
returns with a bare ret. That is __fastcall. The row calls it
?getListboxBottomEntry@@YAHPAU_ListboxData@@@Z, where YA is cdecl and the
argument would live at [esp+4].

Both cannot be true, and the bytes win. The row needs repairing to YI before the
function can be attempted -- writing it as declared produces a source that reads
the wrong location, and writing it as __fastcall produces a symbol the row does
not name. This is the third mis-named row found by reading arity and convention
off the body rather than trusting the mangled name.


## Put last tick's failures into the screen, not just the log

Two builds were lost last tick to an x87 float copy and to a row whose calling
convention did not match its name. Both are cheap to test for, so both went into
the non-constructor screen: exclude bodies containing x87 instructions, and
exclude free functions whose name says cdecl while the body reads an argument out
of ecx. Thirteen and one candidate respectively, and getListboxBottomEntry -- the
one that cost the build -- is gone from the list.

The first pick after that filtering, HideDiplomacy, matched on the first build.
That is the argument for spending the failure: a build lost to a cause you then
encode is cheaper than the same build lost twice.

## The same name can be two functions

?HideDiplomacy@@YAXXZ takes no arguments. Diplomacy.cpp already contains a clean
HideDiplomacy(Bool), which is a different overload with a different mangled name,
and reading that file to understand the naked row was wasted effort -- the two
share a name and nothing else.

Check the mangled signature before going to look for the source. XZ means no
arguments and it is right there in the row.


## The by-value transposition is closed for UnicodeString too

ResetInGameChat passes a UnicodeString by value and matched on the first build
using the shim's class from reference/shims/languagefilter. The blocker that was
recorded as surviving every source shape, and later narrowed to "only the
UnicodeString flavour remains open", is now closed on both sides.

The rule was the same both times and it was already written down: use the real
StringBase-backed class, not a four-byte stand-in of your own. AsciiString is
StringBase<D> and UnicodeString is StringBase<G> -- the same template, so it was
never plausible that one would need a different fix than the other, and treating
them as separate problems cost several ticks.

Every row parked on this blocker is now worth re-queueing: resetIdleWorker,
GadgetComboBoxSetText, isUser@LANGameSlot, amIHost@GameSpyStagingRoom. Retiring
a blocker means sweeping what it parked, which is the same lesson the AsciiString
closure taught and which I again did not act on immediately.

## A reloaded global is a second read in the source

HideSaveLoadMenu writes three fields and retail reloads the menu pointer from its
global before the middle one, despite holding it in a register from the null
check two instructions earlier.

That is not a spill. It is the source naming the global again instead of the
local it already has, and writing it through the local produces one fewer load.
The register the compiler happens to have is not evidence about what the source
said.


## Sweeping a retired blocker pays immediately

Closing the by-value transposition parked four rows that were waiting on it.
Three of them converted this tick -- amIHost and resetIdleWorker on the first
build, GadgetComboBoxSetText on the third.

This is the second time the sweep has been worth running and the second time I
had to be reminded to run it. When a blocker retires, the rows it parked are the
best-understood candidates available: each already has a disassembly, a diagnosis
and a reason it failed. They should be the next thing attempted, not something
noticed later.

## Hoisting a call out of an argument list changes when it runs

GadgetComboBoxSetText builds a string copy for its second argument and calls
winGetUserData for its first. Retail evaluates right to left, so the copy is
built first and the accessor runs after it.

Writing the accessor as its own statement before the call inverts that, and the
two are not interchangeable: a call in an argument list is sequenced with the
other arguments, a call in a preceding statement is not. Putting it back inside
-- via a small inlined helper, since MSVC rejects assignment-in-condition as
C4706 here -- matched.

So when a temporary appears earlier in retail than the source suggests, look at
which expressions are arguments and which have been lifted into locals. Lifting
is not free.


## throw() also removes unwind states for temporaries, not just EH frames

The known form of this lever was: put `throw()` on a constructor a
`new`-expression reaches, and MSVC stops building the EH frame that exists only
to run `operator delete`. isUser generalises it.

isUser evaluates `!userName.compareNoCase(getName())`. The `getName()` temporary
is conditionally constructed -- `&&` short-circuits -- so it needs a
did-we-construct-it flag either way. Retail keeps that flag in ebx and never
touches the unwind state. My build kept the flag in a separate stack dword *and*
bumped the unwind state to 1, costing an extra local.

The unwind state exists to destroy the temporary if something throws while it is
alive. The only thing that runs while it is alive is compareNoCase. Declaring
that `throw()` makes the window provably exception-free, the state bump
disappears, and the flag collapses into ebx. Byte-exact.

So the rule is wider than constructors: `throw()` on **whatever executes between
a temporary's construction and its destruction** removes that temporary's unwind
state. When retail guards a temporary with a plain flag and no state transition,
look at what runs in that window and try marking it non-throwing.

The ledger corroborated this before the build did -- the function has exactly one
generated unwind funclet, and one funclet cannot cover both the by-value argument
and an EH-protected temporary. Counting funclets is a cheap check on how many
things retail unwinds.


## Touching a shim runs the full gate, which is where latent problems surface

Adding one declaration to the languagefilter shim tripped the pre-commit rule
that any header change runs the full gate instead of the delta verify. It found
six DIR32 inconsistencies that had nothing to do with the change -- none of the
files involved include that header.

They had been latent because the full gate almost never runs. Delta verify sees
only the sources you touched, so a cross-source inconsistency introduced by one
commit stays invisible until somebody edits a header months later.

The finding itself: constructors of behaviors implementing two module interfaces
disagree with single-interface classes about where an interface vtable lives.
The sources name the vptr after the base (??_7UpdateModuleInterface@@6B@) when
each derived class has its own vtable for that base sub-object, so N classes
claim one symbol at N addresses. Nine single-interface Die constructors agree
only because ICF folds identical vtables -- agreement by coincidence, not by
correctness.

Two things worth keeping. A gate that runs rarely accumulates debt silently, so
the rare run is worth reading carefully rather than clearing. And when a majority
of references agree on an address, check whether they agree for a reason or
because the linker folded them -- ICF makes wrong names look consistent.


## Do not derive from StringBase when retail inlines the default construction

isPlayer builds a local UnicodeString and translates into it. Deriving
UnicodeString from StringBase<G> is the obvious spelling and it costs a call:
the real StringBase default ctor is declared out of line, so construction emits
one, where retail inlines a single zero store and shares that zero with the EH
state register.

The campaignmanagerascii AsciiString shim already has the right shape -- a
standalone class with its own inline `m_text = 0` ctor, an undefined destructor
that is pinned to releaseBuffer's address, and every real operation reached by
casting to StringBase<T>*. Copying that shape matched. Reach for it whenever
retail inlines part of a string class and calls out for the rest.

Two smaller notes from the same file. wchar_t is not a keyword under
/Zc:wchar_t- and nothing in that include set declares it, so the template
argument has to be spelled `unsigned short` -- which is what G means in the
mangling anyway. And guessing a function's RVA to disassemble it produces a
plausible-looking listing with every call annotation silently wrong; the
instruction sequence still reads correctly, which is what makes it dangerous.
Look the address up.

## The throw() lever is blocked when the declaration is in real source

getSlotNum shows the same unwind-state bump isUser had, for the by-value copy
passed to the inlined isPlayer. The fix that worked for isUser -- declare the
only call in that window throw() -- is not available the same way here: isUser
went through the languagefilter shim, which is TU-scoped, while getSlotNum uses
the real Code/Libraries/.../string_base.h that hundreds of TUs include.

Editing it is a legitimate experiment and the full gate would arbitrate, but it
belongs in its own tick rather than inside a conversion. Worth doing: if retail's
compareNoCase really is non-throwing, the declaration is simply more accurate,
and every string-heavy function with this shape unblocks at once.

getSlotNum stays parked regardless, because it also has esi and edi swapped
against retail for this-versus-loop-counter, which is the register allocation
residual and not something the source can address.


## A virtual destructor always stores a vptr, so its absence disproves the name

The ledger had Template's destructor as ??1Template@@MAE@XZ, where M means
protected *virtual*. But retail calls releaseBuffer on this+0, which leaves no
room for a vptr, and the already-dumped constructor builds an AsciiString there
from a literal rather than storing a vtable.

Building it as declared settled it: MSVC emitted `c7 06 <vtable>` at the top and
shifted every subsequent member offset by four. So the class is not polymorphic
and the name could not be right. Renamed to IAE -- non-virtual from this
evidence, protected from the reference, where MEMORY_POOL_GLUE and EMPTY_DTOR
put Template's destructor there. Byte-exact immediately after.

Worth generalising: the access letter in a mangled name is invisible to the byte
gate, but the *virtual* bit is not. M/U/E versus I/Q/A is testable, because a
virtual destructor cannot avoid its vptr store. When a destructor row will not
convert and the first member looks like real data, check that bit before
anything else.

The reference also explained why the name was plausible. Generals' Template
derives from MemoryPoolObject and does have a virtual destructor; BFME's does
not. Inheriting a name from the reference is a good first guess and a bad last
word.

## Two candidates rejected by reading before building

AIAttackState::onExit ends in a bare `ret`. A one-argument thiscall must `ret 4`,
so the declared W4StateExitType parameter is wrong -- the body takes nothing.
Logged as suspect rather than attempted.

ProductionPrerequisite's constructor contains `mov ecx,eax` immediately followed
by `sub ecx,eax`, so the shift and compare that follow work on a provable zero
and the copy loop below can never execute. That is the dead-code-retail-keeps
family, which no source spelling reproduces.

Both cost one disassembly and no builds. The screen ranks candidates by shape;
it cannot see either of these, and a minute of reading is cheaper than three
builds discovering the same thing.


## Correction: a virtual destructor does NOT always store a vptr

Last tick I wrote that a virtual destructor always emits a vptr store, and used
that to prove Template's row was mis-named. The conclusion was right; the rule
as stated is wrong, and stated that way it would condemn a lot of correct rows.

Screening every naked single-row destructor with a virtual access letter turned
up 29 of 134 with no vptr store. Classes like MultiplayerSettings and
StealthUpdate are certainly polymorphic, so the rule cannot be that strong.

What MultiplayerSettings shows is the real shape: it ends by calling
??1SubsystemInterface@@UAE@XZ, its base destructor. When ~Derived runs, the
object's vptr already holds Derived's vtable -- the constructor put it there, or
a more-derived destructor reset it on the way down -- so storing it again is
redundant and MSVC elides it. The base destructor still stores the *base*
vtable, because after ~Derived's body the dynamic type really does change.

So the store survives only where it is not redundant: in a **root** polymorphic
class's destructor. That is exactly the case Template presented, which is why
building it as MAE emitted one.

The usable test is therefore a conjunction: no vptr store AND no base-destructor
call. Neither half alone means anything. Even that over-reports here, because
base destructor calls often go through synthetic j_ thunks whose targets the
name resolver does not follow, so 25 of the 29 survive a check that should
eliminate most of them.

The wider lesson is about how I generalised. One positive case -- Template
emitting the store -- became "always". The screen that should have tested the
rule was written after the rule was published, and it immediately refuted it.
Run the screen first when the claim is cheap to check across the whole ledger.

## TooltipUpgrade's row is not a destructor

??1TooltipUpgrade@@UAE@XZ ends in `ret 4`. A destructor takes no arguments, so
that alone settles it. The body builds an AsciiString from a literal, then
either releases a UnicodeString at this+0x2d4 or calls set@UnicodeString on it
with the argument -- a setter taking a const UnicodeString reference.

Logged rather than repaired: the address and size are probably fine, but the
true name is not derivable from the body, and inventing one is worse than
leaving the row visibly wrong.


## The new-expression blocker is two problems, and throw() solves one of them

"Constructor inlined into a new-expression" has been recorded as one blocker with
throw() among its refuted fixes. The Sabotage factory shows that is wrong: it is
two independent problems, and throw() solves the first cleanly.

Without it MSVC wraps the whole factory in an EH frame -- push -1, the handler,
the fs:[0] chain -- so operator delete can run if a constructor throws. Retail
has no frame at all. Putting throw() on every constructor the new-expression
reaches (the class, both bases, and the two member sub-objects) removed it, and
the prologue then matched retail instruction for instruction.

What remains is narrower: MSVC emits a call to the derived constructor where
retail inlines it. Three further shapes produced byte-identical output -- the
constructor defined in-class, both destructors defined rather than merely
declared, and no user-declared constructor at all so MSVC synthesises one. So
the refuted list for the *inlining* half now also covers defined-own-destructor
and implicit-constructor.

Recording the split matters because the EH frame was the visible symptom. Any
future row of this shape should get throw() first and be judged on what is left.

Two things read off retail on the way. Base constructors run before the
most-derived vptr store, so a constructor call at a non-zero offset appearing
*before* that store is a second base under multiple inheritance -- here
UpgradeModuleDataSub at +8, which the reference confirms does not inherit from
ModuleData. And a member zeroed via `lea reg,[obj+N]` then stores at [reg],
[reg+4], [reg+8] is a sub-object with its own inlined constructor, not a plain
array; an array member would be stored through the object register directly.

FireWeaponCollide's factory, the same shape, zeroes 0x0c through 0x24 twice
over. That is the duplicate-zero-store family, so it was not attempted.


## A naked source passes the byte gate, so OK N/N can be a false positive

Writing seven cloned files and building them reported `Functions: OK 7/7
matched`. No files had been written -- an assertion earlier in the same script
had fired and stopped it. The seven sources were still `__declspec(naked)`
dumps, and a naked dump reproduces its own bytes by construction.

The gate answers "do these bytes match", which is the right question only once
the source is real C++. It cannot tell a correct conversion from an unconverted
one. Every batch that writes sources should assert afterwards that none of the
targets still contains `__declspec(naked)`, and that is now in the clone script.

This is the second time in two ticks that an assertion fired mid-batch and the
rest of the batch ran anyway. The rule already existed. What was missing was a
post-condition that would have caught it regardless of why the write did not
happen.

## Matching normalised bodies finds work that needs no analysis

Two ticks of picking candidates by shape produced no conversions. Normalising
every naked single-row body instead -- zeroing rel32 operands and any four-byte
immediate that looks like an image address -- and hashing it against the bodies
of already-converted rows found 20 exact twins out of 982.

Twelve converted immediately, most by substituting one class name into an
existing model, because ICF folds identical bodies and the ledger carries a row
per name. Seven UpgradeModuleData constructors are literally one body at
0x129C10 with seven names.

Only the final class name reaches the mangled symbol, so helper classes in a
model can keep their original names; a token substitution on the one name that
matters is enough. One of the twenty did not clone -- DynamicPortalBehaviour's
constructor against QueueProductionExitUpdate's -- so an exact normalised match
is a strong lead rather than a guarantee.

Worth doing again whenever a batch of conversions lands: each newly converted
body becomes a model for whatever still matches it.

## Survey the flag sets already proven in the tree before inventing one

Two functions were written off this session as blocked on "constant materialisation",
with the reasoning that no source spelling moved them. That reasoning was sound and the
conclusion was still wrong, because the per-file `// cl:` directive is a second axis and
it had never been searched.

There is no need to search it blind. The tree already records every flag set that has
been proven to reproduce retail bytes, one per source file, and counting them takes a
second:

    1704  /DNDEBUG /MD /EHsc
     118  /DNDEBUG /MD /GX- /O2 /Ob2
      59  /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
       1  /DNDEBUG /MD /EHsc /Og-

That /GX- /O2 /Ob2 line is 118 files' worth of evidence that some of this binary was
built with exceptions off and aggressive inlining on. Applied to
SabotageMilitaryFactoryCrateCollide::friend_newModuleData it removed both of that
function's recorded blockers at once -- the SEH prologue that /EHsc wraps around a new
expression, and the out-of-line constructor call that no amount of defining the
constructor in the translation unit would inline.

What is left there is narrower and worth stating precisely, because it is the same shape
seen elsewhere: retail checks the allocation with test esi,esi and then builds each of
the two member runs independently, a fresh xor for its zero and its own lea'd this
pointer. The rebuild finds the common zero, hoists it into edi at the cost of saving the
register, and folds both lea's into [esi+disp] addressing. Splitting the two runs into
distinct struct types did not stop the merge, so that part genuinely is not source-
steerable -- but note that this is the mirror image of removeAllShadows, where the
rebuild refused to share a zero that retail did share. Same flags, opposite decisions,
which is what makes it a heuristic rather than a switch.

/Og- is not the answer either: it overshoots, stopping inlining altogether and producing
an ebp frame with stack locals.

The general point: when the source has been ruled out, the flags are the next axis, and
the cheapest move is to sort the existing directives by frequency and try the ones the
project has already proven rather than reasoning from first principles about /O1 versus
/O2.

## A call through an ILT thunk needs the name pinned at the thunk

Remove_Render_Object turned out to be blocked on a helper that is not what it looks like.
The body at 0x00943430 decodes its argument's +0x94 field as three signed ten-bit
quantities -- a packed grid cell address -- and unlinks the object from cell lists, which
reads exactly like GridCullSystemClass::unlink_object. It is not: that name is already
claimed at 0x008DDC60, and every other GridCullSystemClass method sits in the 0x8D
region while this one is at 0x94. The object at SimpleSceneClass+0x34 is a second spatial
grid this build added, with no counterpart in the reference. So the row stays blocked, but
on a definite answer rather than an open question.

Unregister, in the same neighbourhood and already understood, is blocked differently and
more interestingly. Three of its five switch arms call 0x00018EC6, an ILT jump thunk
whose target 0x00711B70 is claimed as
?Remove@?$RefMultiListClass@VRenderObjClass@@@@QAE_NPAVRenderObjClass@@@Z. Writing that
call in C++ emits a call to whatever address that name resolves to -- the body -- while
the retail bytes target the thunk five bytes of displacement away.

The project already handles this: eight real names are pinned at 0x00002874, itself a
thunk, and ??0DrawableModule@@ among them is how the W3DDebrisDraw conversion resolved
its base constructor. So the mechanism is to pin the real name at the thunk address. What
is not obvious, and not something to guess at, is what happens when that name is already
mapped to the body in functions.csv -- whether a second mapping in symbols.csv is
intended or would make resolution ambiguous.

Recorded rather than attempted. The remaining two arms of Unregister call Internal_Remove
directly and would reproduce; it is only the thunked three that need this settled.

## Where an unwind state sits tells you whether a subobject is a base or a base's member

CritterEmitterUpdateModuleData's destructor destroys five things: four at unwind states
3, 2, 1, 0 and the subobject at 0x08 last, at state 4. Reading that as "four members and
a base" and writing `class X : public RootBase, public Base08 { ...four members... }`
reproduces every instruction and gets the numbering exactly backwards -- MSVC emits it as
base 0, members 1..4, because bases are constructed before members and numbered in
construction order.

The shape that does reproduce it is an intermediate class with an inline destructor:

    class Mid : public RootBase { InnerAt08 m_at08; public: virtual ~Mid() {} };
    class X : public Mid { AsciiString a; vector b; UnknownB4 c; AsciiString d; };

~Mid is inlined into ~X, so its member's cleanup is emitted after X's own members and
numbered after them. State 4 running last is therefore not "a base numbered oddly", it is
positive evidence that 0x08 belongs to an intermediate class rather than to this one --
the numbering distinguishes two hierarchies that produce identical instructions.

The same function needed __declspec(novtable) on both the intermediate and the derived
class. Retail stores exactly one vptr, the root base's restore at the very end; without
novtable MSVC opens the destructor by storing the derived vptr and stores the
intermediate's again before its member. That is the same lever as the two vptr sections
above, applied to a class that is not the most-derived one at runtime.

## A byte-exact conversion can silently break rows in its own translation unit

Converting a body to real C++ changes the whole TU's codegen, and the rows most
exposed are the `gen-funclet` unwind stubs, because their `object-symbol=` is a
compiler-assigned `$L` label with no stable meaning. Landing one conversion
renumbers every label after it, and each orphaned row then fails the gate with
`symbol not found in object`, not with a byte mismatch.

The renumbering is a **constant shift per translation unit**, and that is what
makes the repair mechanical rather than a guess. Measured across seven files
whose gate had gone red: -124 in GameState.cpp, -223 in BattlePlanUpdate.cpp,
-374 in W3DVolumetricShadow.cpp, -710 in LANAPIhandlers.cpp, -1657 in
AIPathfind.cpp, +2457 in fx_particle_system_bulk.cpp, -24566 in W3DModelDraw.cpp.
Take the rows whose new label is unambiguous, read the shift off them, apply it
to the rest, and re-verify each one byte-for-byte; 43 of 67 broken rows came
back that way.

Two traps in the diagnosis:

* Comparing retail bytes against **raw** object bytes proves nothing, because a
  relocated field is zero in the object and resolved in retail. An 8-byte
  funclet is `mov ecx,[ebp-X]; jmp <rel32>`, so four of its eight bytes are the
  relocation. Resolve first, exactly as `compile_function` does, then compare —
  a raw comparison reports every row as unrepairable and sends you to retract
  rows that were only renumbered.
* Because the resolver *searches* symbols.csv for a displacement that
  reproduces retail, a tiny funclet can be "matched" by several different
  labels. Ambiguity there is not evidence of anything; use the TU's shift to
  choose, not the first hit.

What does not come back is a row whose function the source no longer emits at
all — an unreferenced template instantiation, a constructor that became trivial,
or an identity that was wrong to begin with. Retract those rather than adding a
reference or an explicit instantiation to force emission: fitting the source to
the ledger makes the gate green without proving anything about retail.

## The pre-push hook only verifies outgoing sources, so cross-TU rot lands unseen

`verify_pr.sh` byte-verifies the sources a push touches. That is sound for the
pusher's own rows and blind to everyone else's: a conversion that shifts codegen
breaks rows in the same TU that the pusher never re-verifies, and nothing looks
at them again until somebody runs a full gate. Sixty-seven rows across ten files
accumulated this way, and the count grew from 42 to 63 over about an hour of
fleet pushes while the breakage was being diagnosed.

The tell is that the full gate dies on the *first* broken row, so the visible
symptom is one `ValueError` naming one label, and the actual population is
whatever a full sweep finds. Before concluding a red gate is a single bad row,
sweep every row and count: `compile_function` over the whole ledger reports the
unresolvable and the mismatching separately, and they have different causes.


## Widening the clone screen's size window found three more clusters

The first run of the normalised-body screen capped candidates at 600 bytes and
found 20 twins. Raising the cap to 900 found 22 -- and the additions were not
stragglers, they were two whole clusters the window had cut in half: nine 283-byte
ModuleData constructors and six 169-byte preference setters.

An arbitrary bound chosen for speed hid more work than it saved. When a screen
is cheap, run it wide.

## A cloned body can still need per-instance data read from the binary

The six preference setters share one body: format an int into an AsciiString and
store it into the preferences map under a literal key. Only the key differs, and
because a string literal is a DIR32 whose address is copied from the target, the
byte gate passes whatever text you write. The string-ref verifier is what
catches a wrong key.

So the clone was not a pure substitution: each key had to be read out of the
binary first, by disassembling the target and following its pushed addresses
into the data section. All six came back cleanly -- CampaignDifficulty,
MaxDisconnects, MaxPoints, MinPoints, NumPlayers, WaitTime -- and all twenty
literals across the batch verify.

Worth remembering as the general shape: identical code plus differing data is
still clonable, but the data has to come from the target rather than the model.

## Worktree isolation needs the session cwd to be the repo

A thirteen-agent fan-out died instantly with "not in a git repository". The
session's working directory is D:\BFME1 while the repo is D:\Open-BFME-1, and
worktree isolation resolves against the former.

Without worktrees the agents share one checkout, which is safe only because each
one edits a distinct file and the one genuinely shared mutable artifact -- the
deps cache -- is untracked and self-healing. The protection that matters is
re-verifying every claimed match centrally before committing, since a stale
cache could in principle hand an agent a false OK.


## Parallel agents need a central re-verify, and it earned its keep immediately

Thirteen agents each converted one naked function in the shared checkout. Twelve
removed the naked dump from their file and reported a match. Re-running the gate
centrally over all twelve found that two of them did not match.

Both had been instructed to confirm the gate printed OK and that the naked
marker was gone, and both reported doing so. Whatever happened -- a stale deps
cache handing back another agent's object, or simply an over-eager report -- the
failure mode is the one already recorded from my own mistake: the gate answers
"do these bytes match" and cannot, on its own, tell you the answer came from the
source you think it did.

So the rule for any fan-out is that an agent's verdict is a claim, not a result.
Ten landed; the two false positives were reverted and cost nothing, because
nothing was committed on an agent's word alone.

The cheap structural protection is that each agent owns exactly one file. That
makes reverting a bad claim a one-line operation and keeps a wrong answer from
contaminating anything else.


## The byte gate does not catch a naked body wrapped as non-naked

A swarm agent found that removing only the `__declspec(naked)` keyword from a
function whose body is purely `__asm { __emit ... }` still passes the byte
gate: MSVC 7.1 does not force a stack frame around a plain function whose body
is an inline-asm block with no locals, so the emitted bytes are unchanged.
`grep -c "__declspec(naked)"` then reports 0 and `Functions: OK 1/1 matched`
still prints, even though nothing was actually converted -- the naked marker
check I added as a swarm safeguard is necessary but not sufficient on its own;
what actually matters is "no __asm/__emit anywhere in the file", and that is
what the check needs to be, not just the naked keyword.

Confirmed by sweeping the whole tree: this was the only non-naked file, out of
several thousand, still containing __emit. Rejected regardless of the byte
match and reverted.

The underlying disassembly finding is worth keeping even though the
conversion isn't: the retail bytes at this address are 18 back-to-back E9 jmp
instructions to unrelated targets, 17 of them unreachable dead code after the
first. That is not a shape any compiler emits for a real function body -- it
reads like an ILT thunk table or jump-table data captured as if it were code,
and whoever attempts this row next should start from that theory rather than
re-deriving it.

## A ledger's existing status/notes can predate real conversion and be stale

The rejected row's own functions.csv entry already said status=matched with
notes claiming "exact C++ __emit thunk converted from MASM dump" -- before the
swarm ever touched it. Git history showed why: the file was committed already
naked, by the same commit that added the row, with that boilerplate note. A
naked dump trivially matches the byte gate (documented earlier this session),
so "status=matched" on a ledger row is not itself proof a real conversion
happened -- it can be the leftover state from the initial dump commit. Check
what is actually on disk, not just what the ledger claims about it.

## Failed agents can be more valuable than agents that report a match

Five of eight agents in this swarm self-reported matched:false with precise,
independently-verified residuals rather than guessing a fourth build. Two of
those diagnoses are new, real findings, not restatements of known blockers:

- MeshMatDescClass's constructor implies Texture/TextureArray are a small
  ref-counting smart pointer type, not the plain TextureClass* the shared
  header currently declares, based on an eh_vector_constructor_iterator call
  and per-element Release_Ref that only exist for a non-trivial element type.
- DequePartitionCellInitializeMap's ledger pin forces an extern "C" free
  function (cdecl), but the target bytes are thiscall shape. No MSVC 7.1
  calling-convention keyword produces both the pinned plain symbol name and
  thiscall ABI at once -- __thiscall is illegal on free functions (C4234),
  __fastcall decorates the symbol with @N even under extern "C". This is a
  ledger-level conflict, not a source-level one.

Neither of these would have surfaced from a screen; both came from an agent
reading its own compiled .obj's actual symbol and relocation tables rather
than trusting build.py's summary line, after exhausting the build budget
honestly instead of padding a report.


## A recurring EH-bookkeeping scheduling artifact now has a name and four instances

ParticleSystemInfo's copy constructor failed on exactly one residual: retail
stores the this-pointer to its EH-frame stack slot as the very first
instruction after the prologue's initial push, before loading the source
object pointer or the vptr. Every source shape compiled instead defers that
store to immediately before the first call that could throw, a few bytes
later, shifting the whole function's length.

This is not a one-off. The same shape is already on record for addRadar@Player,
getIdealStaticGameDetail@OptionPreferences, and two destructors elsewhere in
this project. Four independent sightings across unrelated functions makes this
a real, recognized residual class -- MSVC 7.1 choosing to schedule the
EH-frame's this-store at the top of the function in some cases and just before
first use in others, for reasons not yet tied to anything expressible in
source. Worth a dedicated screen once enough instances accumulate to look for
what they have in common.

## Not every naked function has a discoverable fix, and that is a legitimate outcome

A 4-agent swarm this tick landed zero conversions -- all four candidates were
diagnosed precisely and reverted cleanly, no exceptions. Two hit the
calling-convention/ledger-ABI conflict already on record (this is now three
occurrences: DequePartitionCellInitializeMap, VectorICoord2D::_M_insert_overflow,
and by the same shape likely more waiting in the pool). One hit a
register-allocation residual. One found a genuinely new structural fact --
MapMetaDataReader has an 8-element array of an unidentified 20-byte "slot
record" type nobody has named in this codebase yet -- and reported that instead
of inventing a plausible-sounding class to paper over it.

The pool of readily-available naked functions at the size/call-count tier this
swarm searched is thinning out: what is left after three swarm runs skews
toward known-hard categories rather than easy wins. Future candidate selection
should either widen further (larger functions, more calls) or specifically hunt
for instances of the already-named blocker classes, since those are at least
diagnosable even when not fixable from a single file.


## Same target address means a clone is a pure rename; a different one means check the calls

Three clones this tick split cleanly along that line. GettingBuiltBehaviorModuleData
and HordeUpdateModuleData share W3DLaserDrawModuleData's exact target address --
ICF folded them onto one body -- so substituting the class name was the whole job
and both matched first build.

DelayedLuaEventUpdate matched the normalised body of PassiveAreaEffectBehavior's
destructor but sits at a different address, and there the clone was not free: the
sole differing byte region in the whole 116 bytes was one call's rel32. Its member
at 0x24 is not the model's list<int>; its destructor is a different instantiation
entirely.

So the address relationship tells you in advance which kind of clone you have.
Same address, rename and go. Different address, the structure is shared but every
call target is an independent question -- diff first and expect to retarget.

The fix also shows when a synthetic name is legitimate to use. The real destructor
here is only pinned under generated names (??1Gen_uw_00013156 and a Gen_dtor
sibling), and declaring a member typed to that existing pin is the same convention
the model file itself already uses for Gen_dtor_00113d40. That is reusing a pin,
not inventing a signature for an unnamed callee.


## When cloning, rename the target class and nothing else

DynamicPortalBehaviour was on record as a clone that did not reproduce from
QueueProductionExitUpdate despite matching its normalised body. That diagnosis
was wrong, and the real cause is worth more than the conversion.

They are ICF-folded onto one address, so the bytes are identical and a rename
should have been the whole job. The failure came from doing the rename with a
blind token substitution, which also renamed the helper class
QueueProductionExitUpdateBase -- whose construct() the constructor calls. That
changed the helper's mangled name, so it no longer resolved to the pinned
symbol, and the call's rel32 came out different.

Renaming only the target class, leaving every helper name untouched, matched on
the first build.

So the clone rule has two halves that pull in opposite directions. Same address
means every call target must stay exactly as it is -- rename the one class the
row names and nothing else. Different address means the shared structure is only
a starting point and call targets are independent questions to re-derive. Getting
these backwards produces exactly the failure logged here, and it looks like an
unfixable codegen difference rather than a self-inflicted one.


## A normalised-body match across different addresses can still be a false lead

The clone screen reported six FXParticleSystem ModuleTemplate constructors as
matching LightningDrawModuleTemplate's body. All six sit at unique addresses --
no ICF folding -- and the first one attempted turned out not to be a clone at
all.

CategoryModuleTemplate<7> writes vptrs at offsets 0, 4 and 8 and calls an
out-of-line constructor for the subobject at +8, so it has three polymorphic
subobjects. Its own 23-byte siblings <1> through <6> have none of that: writing
the obvious uniform template reproduces the 23-byte shape exactly, which is
strong evidence the template is not uniform across its instantiations and the
106-byte ones carry an extra base the others lack.

So normalised-body equality is a much weaker signal at the same size when the
addresses differ. Same address stays reliable -- the bytes are literally shared.
Different address means only that two functions have the same instruction
skeleton, which for constructors of similar-shaped class hierarchies is common
enough to mislead. Confirm the address relationship before treating a screen hit
as a clone.

Mangling note worth keeping, confirmed against an already-converted sibling:
MSVC encodes a non-negative integer template argument N as $0(N-1), so $06 is
<7> and $0A@ is <0>.


## Neighbouring addresses are strong evidence for a row's real identity

A row named ?setEaseTimes@ParabolicEase@@QAEXMM@Z turned out to be
FVFInfoClass's constructor. Four independent things agreed: the body calls
D3DXGetFVFVertexSize, it does FVF bit arithmetic on the exact constants
(0x002 XYZ, 0x00c XYZB4, 0x1000 LASTBETA_UBYTE4, 0x010 NORMAL, 0x040 DIFFUSE),
it is thiscall with two arguments, and its member stores land on FVFInfoClass's
layout.

The clincher was cheaper than any of those: it sits at 0x964150, and
FVFInfoClass::Get_FVF_Name -- an already-matched row -- starts at 0x964290,
274 bytes and a little padding later. Functions from one translation unit land
adjacently, so when a suspect row abuts a correctly-named row of some class,
that class is where to look first. Worth checking before disassembling anything.

Two further findings from the attempt, kept because they will save the next one:

- Retail reaches D3DXGetFVFVertexSize through a direct call, so the declaration
  must not be __declspec(dllimport) -- dllimport emits an indirect call through
  the IAT (ff 15) where retail has e8.
- BFME's FVFInfoClass is NOT the Generals one. dx8fvf.cpp's constructor written
  verbatim reproduces the first ~60% byte-for-byte, through texcoord_offset[0]
  at +0x14, and then diverges: retail writes a member at +0x3c, past
  specular_offset, chosen by comparing FVF against a lookup table at 0x0113E0BC.
  The reference header has no such member. Identifying it and the table is the
  whole remaining job.

The row is NOT renamed, and that is the gate working as intended. The
pre-commit conversion check rejects any edit that adds naked lines -- including
merely rewriting the declaration of a file that was already naked -- on the
grounds that a lift is not a conversion. So a rename cannot be landed ahead of
the conversion it belongs to, and forcing one would leave the ledger naming a
symbol the object does not emit. The identification is recorded here instead,
and the rename belongs in whatever commit finally converts it.


## Unwind-state indices off by a constant means one extra destructible sub-object

TerrainRoadType's constructor compiled with every offset, every call target and
every eh-vector-constructor-iterator argument already correct, and still failed:
each unwind-state store held a value exactly one higher than retail's
(0x0b where retail had 0x0a, and so on all the way down).

A uniform offset like that is not a scheduling artifact, it is a count. MSVC
numbers unwind states by how many destructible sub-objects are live, so being
consistently +1 means the class had one more of them than retail's does. The
culprit was the base: modelling MemoryPoolObject with a virtual DESTRUCTOR
makes the base sub-object destructible and consumes a state. Replacing it with a
plain virtual function keeps the vptr at offset 0 -- which the body needs -- and
removes the state. Byte-exact immediately.

So when a constructor is otherwise perfect and the EH state numbers are off by a
constant, count destructible members rather than looking for a codegen quirk.
A base only needs a destructor if retail actually destroys it, and giving one
where retail has none is invisible in the layout but not in the unwind states.

Worth pairing with the earlier destructor lesson: there, the presence or absence
of a vptr store distinguished virtual from non-virtual. Here it is the reverse
direction -- the class genuinely needs a vptr, but must not have a destructor to
go with it.

## Reading layout off the body beats deriving it from the reference header

The reference header for TerrainRoadType declares roughly seventy AsciiStrings
across several two-dimensional arrays, and working out each offset from
declaration order and enum sizes would have been slow and error-prone. The
retail body hands the same information over directly: the inline zero stores
land on exactly the scalar-string offsets, and each array shows up as an
eh-vector-constructor-iterator call whose element count and size are pushed as
immediates.

Deriving the layout from the header is the fallback. Reading it from the body is
the primary source, and it also cross-checks the header rather than trusting it.


## The AsciiString shims model getLength wrongly for BFME

Every AsciiString shim in reference/shims defines

    inline int AsciiString::getLength() const { return m_data ? strlen(peek()) : 0; }

but BFME's does not call strlen. obfuscate() at 0x7FBF0 inlines it as a null
guard followed by `movzx eax, word ptr [eax+4]` -- reading the stored 16-bit
length straight out of the string header.

The asciistring8 shim already knows this. Its isEmpty() reads m_data->m_len and
carries a comment citing two other retail bodies that prove the 8-byte header
and the 16-bit length field. getLength was simply never brought into line with
its own sibling.

Fixing it is `return m_data ? m_data->m_len : 0;` and is zero-risk right now:
only three sources include that shim and none of them call getLength. It was not
landed here because it is a header edit, which forces the full gate, and the
conversion it was meant to unlock did not finish anyway -- but it is the correct
change and should ride along with whichever conversion needs it first.

Also worth knowing: asciistring8 is not self-contained the way
campaignmanagerascii is. It includes Lib/BaseType.h, so it needs the GeneralsMD
reference include paths on the cl line; copy them from
Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp.

## Choosing between shims is part of the reconstruction, not setup

obfuscate's first build failed only because campaignmanagerascii forwards
getLength and str() to out-of-line StringBase calls, where retail inlines both.
Nothing about the body was wrong. The shim determines whether an accessor
inlines, and that is as much a codegen decision as any source-level choice.

So when a body matches structurally but has a call where retail has inline code
(or vice versa), suspect the shim before rewriting the logic. There are several
AsciiString shims precisely because different retail translation units inlined
different amounts, and picking the wrong one produces a plausible-looking near
miss.


## MSVC will not inline a recursive walk twice, so write the two steps out

SpecialPowerTemplate's two accessors both walk an override chain and then read a
member of whatever the walk lands on. Retail expands the walk exactly two levels
-- two null tests -- before falling back to an out-of-line call.

A recursive inline function does not reproduce that. Written the obvious way
(`if (m_nextOverride) return m_nextOverride->friend_getFinalOverride(); return
this;`) MSVC expands one level and calls. `__forceinline` changes nothing,
because it does not apply recursively. `#pragma inline_recursion(on)` makes it
worse: MSVC then declines to inline at all and emits a bare call.

Writing the first two steps explicitly, and leaving friend_getFinalOverride
merely declared so the tail resolves to its existing pin, produced the right
shape. One further fix was needed: retail places the "no override, use this"
exit LAST, so the source has to be `if (o) { ...; return o; } return this;`
rather than an early `if (!o) return this;`. With both, getViewObjectDuration
came out byte-exact.

getName, in the same file, still differs by one thing: retail carries the walk
result in eax (`mov ecx,eax` then `add ecx,0xc`) where the identical source
yields ecx (`mov eax,ecx` then `add eax,0xc`). That is the register-allocation
class, so the file is reverted -- build.py verifies a source as a whole, and a
file with two rows cannot land with one of them matching.

Two things worth carrying forward: the explicit-unroll technique for inline
depth, and the branch-ordering rule that an early-return guard and a trailing
fallback are not interchangeable even though they compute the same thing.

## Multi-row naked files are a large untouched pool, with a catch

Every screen so far skipped files carrying more than one ledger row, which is
where roughly four thousand of the five thousand remaining naked rows live.
Screening for small ones -- two to four rows, under about 320 bytes total --
turns up 22 files.

The catch is that build.py verifies a source file as a whole, so every row in
the file has to convert before any of it lands. SpecialPowerTemplate shows the
failure mode directly: one accessor byte-exact, the other blocked, and nothing
committable. Prefer files whose rows share a shape, so one insight closes all of
them, and expect all-or-nothing outcomes.

Also seen while screening: MeshGeometryMeshModelLeafThunks.cpp looks like a
candidate but is already finished. Its one real function is converted and the
other three rows are deliberate ICF aliases keeping the folded body, which is
correct -- a void function cannot compile to a value-returning body.


## Where the vptr stores land tells you which members are sub-objects

Two module constructors this tick shared a shape: an external base constructor
call, some zero stores, several vptr stores, and more stores. The first
(74 bytes, four vptrs) came out on the first build with plain int and bool
members. The second (77 bytes, five vptrs) did not, and the difference was
entirely about where the vptr stores sat.

Retail put one zero store at 0x38, then all five vptr stores, then four more
zero stores at 0x3c through 0x48. Writing five plain members put every zero
store first and all the vptrs after; chaining the assignments only reversed the
order of the group.

What reproduces it is modelling 0x3c..0x4c as a member sub-object with its own
inline constructor, and 0x38 as an init-list member. Member initialisers run
after the vptr stores, so the sub-object's four stores stay a group behind them,
while the single init-list store at 0x38 is the one thing the vptr stores sink
past.

So the position of the vptr stores is a layout signal, not just a scheduling
quirk. Stores that appear *after* the vptrs are member construction; a store
appearing *before* them is one the sink moved past, and there will be exactly
one leading group of those. When plain members give the wrong split, look for a
sub-object boundary at the point where the vptrs actually sit.

This also refines the earlier sinking note. The rule was recorded as needing a
run of two or more stores to move the vptr; here it moved past exactly one. The
run length is not the trigger -- what matters is that the leading group belongs
to the constructor's own initialisation while the trailing group belongs to a
sub-object's constructor.

## Same-address rows in one file convert together for free

Both files held two ledger rows at one address, ICF-folded. Writing the class
shape twice, once per name, converts both rows in a single build, which is what
makes multi-row files worth targeting despite build.py verifying a source as a
whole. Four rows landed here from two builds' worth of real work.
## Two drifts sit under every Overridable-derived destructor

CrateTemplate cost two separate BFME/ZH divergences, and both generalise.

The first is `KindOfMaskType`. Retail `CrateTemplate::CrateTemplate`
@0x00379DC0 zeroes six dwords at this+0x18 where Zero Hour's 121-bit mask needs
four, so BFME's `KINDOF_COUNT` is in (160,192] and every member past the mask
sits eight bytes higher. `std::bitset` rounds to whole 32-bit words, so any
count in that range gives the same layout: the width is provable, the extra
enumerator names are not. A `typedef BitFlags<192> KindOfMaskType` scoped to
the one translation unit -- guard-suppress `__KINDOF_H_` before `PreRTS.h`,
which reaches `Common/KindOf.h` at its line 61 -- turned a 187-byte body into
the exact 199. `reference/shims/bfmekindof` carries the two extra names
TunnelTracker proves but is still four dwords wide, so it does not fix layout.
Suspect this whenever a class holding a KindOf mask is off by eight per member.

The second stopped the destructor. BFME's `~Overridable` is
`if (m_nextOverride) delete m_nextOverride; m_nextOverride = NULL;` -- a
`vtbl[0]` call with the deleting flag, the same polymorphic delete the rest of
this file uses -- where Zero Hour calls `m_nextOverride->deleteInstance()` and
never clears the field. It is inlined into every derived destructor, so it
cannot be pinned as a call; a TU-local `Overridable` plus `__forceinline`
(plain `__inline` is not enough, MSVC leaves it out of line) reproduces every
instruction of retail's 147-byte `~CrateTemplate` @0x00379EC0 except six bytes:
our object emits two vptr stores, `Overridable`'s then `MemoryPoolObject`'s,
and unwind state 3 before the delete, while retail emits one store hoisted
between the `test` and the `je` and unwind state -1. Retail therefore gets
nothing at all out of `~MemoryPoolObject` -- no vptr reset, no cleanup state --
which is a `GameMemory.h`-level drift, not a CrateTemplate one, and it will
block the last few bytes of every other `MemoryPoolObject` destructor the same
way. Worth solving once, centrally, rather than per file.

Finding the body at all needed the vtable, not the drift report: slot 0 of
0x10EA378 is the deleting destructor behind ILT 0x2647C, which reaches
`??_GCrateTemplate` @0x37A2F0 and from there `~CrateTemplate` @0x379EC0. The
drift report had guessed 0x0081DC99, which is not a function start, and
`locate.py` reported the symbol unlocated because the compiled body was still
128 bytes with an out-of-line `~Overridable` call.


## The module-constructor family is 97 rows with one shared shape

Screening for naked rows named ??0X@@QAE@PAVThing@@PBVModuleData@@@Z turns up 97
of them. Four are converted. They share a shape worth writing down, because
getting it right is most of the work:

- an out-of-line base constructor call, which is the ObjectModule constructor.
  It is pinned at 0x000170E4 under about ten ICF-folded names; use
  ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z, which is the semantically
  correct one, rather than whichever alias a neighbouring row happened to pick.
- UpdateModule's own constructor inlined next: its two vtables at 0x0c and 0x10,
  then its three members as 0x18 = -1, 0x1c = -1, 0x14 = 0 in that order.
- then the derived class's own three vtables at 0x00, 0x0c and 0x10, and last
  its own members.

The sub-object trick from the previous tick is needed again here. A derived
member that is a plain int holding zero merges into UpdateModule's zero group
and the vptr stores sink past both; declaring it as a small struct with an
inline constructor keeps its store after the vptrs, where retail has it.

ProneUpdate and AutoFindHealingUpdate come out of that recipe byte-identical
except for one thing: retail materialises the zero into ecx up front (`or eax,-1`
then `xor ecx,ecx`) and uses ecx for both 0x14 and 0x20, while the same source
reuses eax once it is done with -1. Same instructions, same count, same length --
only the register differs, which is the allocation class. Both reverted.

That is worth knowing before spending builds on the rest of the family: this
particular sub-shape, where the same zero feeds a member on each side of the
vptr stores, currently ends in a register residual. Family members whose derived
part uses non-zero constants, or only one zero, do not have that problem -- the
four already converted are exactly those.
## The red DIR32 gate, and two of its eight cases cleared

Every header or shim edit runs the full gate, and the full gate has been
failing on `DIR32 consistency: FAIL 8 NEW inconsistent symbol(s)`, so no
header or shim change can be committed at all. That cost three conversions in
one session before it was worth stopping to look at. Two of the eight are now
gone; here is what the other six are, so nobody has to re-derive them.
`python3 tools/dir32.py <symbol>` prints the disagreeing rows.

Cleared: `?OpenBFME5_W3DShaders@@3PAPAVW3DShaderInterface@@A` and
`?OpenBFME5_W3DShadersPassCount@@3PAKA`. Two thunk TUs each declared
`extern ... OpenBFME5_W3DShaders[4]`, but they are windows onto *different*
slices of the same retail array - the bases sit 0x2C apart, eleven elements -
so one C++ name legitimately resolved to two addresses. Giving each window its
own name (`_terrainBase`, `_flatTerrainBase`) says what the code actually
models and leaves both bodies byte-identical. A full gate confirms 8 -> 6.

Cleared next, by retraction rather than renaming:
`??0FireWeaponNugget@@QAE@XZ` and `??0ObjectCreationNugget@@QAE@XZ`. Retail at
0x5C6C0 is `mov eax,ecx; [eax]=0; [eax+4]=0; ret` and at 0x61D90 is
`mov eax,ecx; [eax]=0; ret`. A constructor of a polymorphic class stores its
vftable at that site, not a literal zero, so neither body can be the
constructor claimed on it - the patcher masking the relocation site is the
only reason they "byte-matched". Both came from the same bulk ICF-alias commit
that produced the already-retracted `??0UpdateModuleInterface` row at that very
same 0x61D90, and no unique coverage is lost because both addresses stay
claimed by their alias groups. 6 -> 4.

Of the remaining six, four look like the ctor-vs-dtor vtable family this
whitelist already documents, where a destructor inlines the base-chain
destructor and its final vptr store names a different vtable than the class's
own:

- `??_7RenderObjectUpdateModuleInfo@FXParticleSystem@@6B@` is the clearest:
  the destructor in fx_particle_system.cpp resolves to 0x1073744, which the
  whitelist header already identifies as the real `??_7MemoryPoolObject@@6B@`,
  while a newly landed copy-ctor thunk resolves to the class's own 0x1110D78.
  Nine of its FXParticleSystem siblings are already whitelisted for exactly
  this.
- `??_7TeamFactory@@6BSnapshot@@@` and `??_7TeamFactory@@6BSubsystemInterface@@@`
  split the same way, TeamFactoryCtorThunk.cpp against
  TeamFactoryDestructorThunk.cpp.
- `??_7UpdateModule@@6B@` has one dissenter, `~TensileFormationUpdate` in
  TensileFormationUpdateDestructorThunk.cpp at 0x10B1DC4, against a long list
  of agreeing rows at 0x109CBAC.

The last two are a different shape and should not be whitelisted with the
rest. `??_7FireWeaponNugget@@6B@` and `??_7ObjectCreationNugget@@6B@` each
resolve to base **0x0** from their constructor in ObjectCreationList.cpp,
which means retail stores a zero dword where our reconstruction stores a
vtable pointer. The DIR32 patcher masks the site with the original bytes, so
the body still byte-verifies - this is precisely the latent error the check
exists to catch, and it wants a real fix in the constructor, not a whitelist
line.


## Screen the module-ctor family by where the last vptr store sits

The family splits cleanly on one cheap test: decode the body and compare the
address of the last vtable store against the address of the last member store.

Bodies where the vtable stores come last convert with plain members on the first
build -- the vptr stores simply sink past the whole run of member stores, which
is what MSVC does by default. DemoTrapUpdate and RadarUpdate both landed that
way, the second straight from the first as a template.

Bodies with a member store after the vtables need the sub-object treatment, and
if that trailing member holds the same zero as one before the vtables, they hit
the register residual recorded last tick. Of fifteen family members in the 60 to
200 byte range, only one was vtable-last, so the residual shape is the common
one -- which is worth knowing before picking a candidate.

Two details that generalise. Retail's member stores are grouped by value, not by
offset: RadarUpdate writes 0x14, 0x25, 0x20, 0x24 as one zero group and then
0x18, 0x1c as the -1 group, so the source order within a group has to be read off
the body rather than assumed from the declaration order. And the base call is
ObjectModule's constructor, pinned at 0x000170E4 under about ten ICF-folded
aliases; naming the class ObjectModule emits the right symbol without inventing
anything.

## What UpdateModule's three vtable stores look like, and where TensileFormationUpdate differs

Useful for reading any Update-module destructor. `~AutoAbilityBehavior`
@0x001ED6E0 is the canonical shape: three stores for the class's own tables
(`[+0]=0x10A1BC4`, `[+0xC]=0x10A1B00`, `[+0x10]=0x10A1AF4`), then the inlined
UpdateModule base teardown, which is always `[+0x10]=0x109CBAC`,
`[+0]=0x109CB5C`, `[+0xC]=0x109CA98` - three adjacent tables, in that order.
Dozens of rows agree on it, constructors included.

`~TensileFormationUpdate` @0x00253090 is the one dissenter and it is a strange
one: its base teardown writes `[+0]=0x109CB5C` and `[+0xC]=0x109CA98`, exactly
UpdateModule's, but `[+0x10]=0x10B1DC4` instead of 0x109CBAC. Two thirds of
one class's triple with the third slot from somewhere else, so it is not simply
another class's tables and it is not the ctor-vs-dtor family either. Either
BFME has an intermediate class between TensileFormationUpdate and UpdateModule
that overrides only the UpdateModuleInterface branch - and the local class
model in TensileFormationUpdateDestructorThunk.cpp is missing it, which would
make this a modelling artifact fixable in that one TU - or 0x10B1DC4 is a
second copy of the same table. Deciding which is what the last DIR32 failure
in this family needs.

## A member sourced from the module data avoids the register residual entirely

FloatUpdate converted on the first build where ProneUpdate could not, and the
difference is where the trailing member's value comes from. ProneUpdate stores a
zero at 0x20 after the vtables, and that zero is the same one already stored at
0x14 before them, so retail keeps it live in ecx while the same source reuses
eax -- the residual. FloatUpdate reads its trailing member out of the module
data at +8, so no constant has to survive the vtable stores at all, only one
zero is live, and 0x14 comes out as an immediate rather than a register.

That makes the useful screen for this family: not just whether a member store
follows the vtable stores, but whether its value is one that was already
materialised before them. Members fed from a parameter, from the module data, or
from a distinct constant are fine. Members repeating an earlier constant are the
blocked shape.

Two corrections to my own screening. The vptr-last sub-shape is exhausted --
after DemoTrapUpdate and RadarUpdate there are no candidates left up to 400
bytes, so that easy tier is done. And a screen comparing "the trailing value" to
earlier ones has to compare register *families*, not spellings: Oathbreakers
stores cl at 0x20 where ecx fed 0x14, which is the same value, and a naive
string comparison sorted it as tractable. It is not; it fails exactly like
ProneUpdate, and the trailing non-zero float at 0x24 does not change the
allocation.

## Write to the path the ledger names, not the one that looks right

Oathbreakers' row lives under GameLogic/AI, not GameLogic/Object/Update where
every other module constructor in this family sits. Assuming the directory from
the pattern created a new untracked file next to the real one and left the
original naked. The gate caught it immediately -- "ZERO matched rows, source
presence is not progress" -- which is a good check to have, but the cheaper habit
is to read the source column out of functions.csv rather than infer the path.
### and 0x009F2800 is one destructor wearing three names

Following the same vtable evidence out from TeamFactory: 0x009F2800 currently
carries **three** matched destructor rows - `??1FXListStore@@UAE@XZ`,
`??1PartitionManager@@UAE@XZ` and `??1TeamFactory@@UAE@XZ` - all 115 bytes.
Retail demonstrably does not fold identical COMDATs, so at most one can be
right, and the vtables say none of them are obviously it: the body writes
`[+0]=0x11457F8`, `[+8]=0x11457E8`, then `[+8]=0x1073744`, which is the exact
mirror of the constructor at **0x009F2730** (`[+8]=0x1073744`, `[+0]=0x11457F8`,
`[+8]=0x11457E8`) - and that constructor is claimed as `??0ControlBar@@QAE@XZ`.
A constructor and a destructor 0xD0 apart writing the same two tables in
opposite order are the same class, so 0x009F2730 and 0x009F2800 stand or fall
together, and `??1ControlBar@@UAE@XZ` is meanwhile claimed at 0x004A9980 on a
679-byte body.

Whoever untangles this should start from the constructor, since constructors
name their class unambiguously, and expect to retract two rows. TeamFactory's
is already known wrong from the other direction.

## Sweep in batch; the queue is the slow path

Three hours of drawing candidates from `next_work.py` one at a time produced
about 1,600 bytes. One hour of batch sweeping produced 5,400. The queue is
still right for hard, layout-bound work, but it should not be the first thing
you do in a session. Two sweeps, both safe to run in the background:

**Exact matches in `reverse/reloc_names.csv`.** The `identity=real` rows are
unclaimed functions whose name, RVA and size all came out of a byte-true call
site, and a fraction of them already compile byte-exact from source that is
already in the tree. Emit name/rva/size/source for them, sort by source so the
object cache is reused, run each through `tools/explain_mismatch.py`, and keep
whatever prints `classification: exact match`. Measured hit rate 10 in 741.
Skip `vendor/` sources and `?j_` names. One of the ten turned out to be a real
body sitting unclaimed while its symbol was pinned to a 5-byte ILT thunk, which
is +109 bytes and a deleted file for no work at all.

**`tools/locate.py` over every source.** It byte-scans .text with relocation
sites masked and accepts only unique placements, so unlike the structural tier
it needs no candidate address and never guesses. Measured, by how unmatched the
file already is:

    1-8 markers    178 files -> 23 placements
    9-40 markers   216 files -> 45 placements
    41+ markers    216 files -> 11 placements

The shape is the point. Small-drift files pay; the enormous ones do not, because
a file with two hundred unmatched bodies is unmatched *because* its class layout
drifts, and no byte-scan sees past that. InGameUI.cpp placed nothing at all out
of 196 candidates. Spend scan time on files that are mostly done and vtable
archaeology on the ones that are not.

And it is not a one-off. Other contributors' layout and shim fixes open placements
that were not there an hour ago, so re-scan the changed set after every pull:
`git diff --name-only <last-base>..HEAD -- 'Code/**/*.cpp'` fed into locate.py.
Fifty changed files gave five more placements in one pass.

Two mechanical notes. Prefer `locate.py <source> --emit` over `add_match.py` per
row: add_match writes only the ledger row, and a body whose callees are still
unpinned also needs the `reverse/symbols.csv` additions locate reads out of the
call displacements - PeerDefs.cpp refused eleven rows through add_match and took
all eleven through `--emit`. And `--emit` writes backslash source paths that
`check_csv` rejects, so normalise them before committing.


## Interleaved stores across two offset ranges are one loop, not separate members

ClickReactionBehaviorModuleData writes 0x08, then 0x14, then 0x0c, then 0x18,
then 0x10, then 0x1c. Read as six independent members that ordering looks
arbitrary. It is one unrolled loop over two parallel three-element arrays --
each iteration writes one element of each -- and writing it that way matched on
the first build.

Worth checking whenever a constructor's store offsets alternate between two
ranges with a constant stride: the alternation is the loop body, and the stride
is the element size.

## The base-register-versus-direct-offset choice is not source-expressible

DemoTrapUpdateModuleData came out byte-identical except for six dwords at 0x0c.
Retail leas their base into edx and stores through [edx], [edx+4] and so on;
MSVC instead folds them to [eax+0x0c], [eax+0x10] and so on, which is one byte
shorter per store. Both a sub-object with an inline constructor and a plain
array zeroed by a loop produced exactly the same folded output, so the two
obvious spellings are indistinguishable here.

This is worth separating from the sub-object lesson recorded earlier. There, the
sub-object boundary determined *where* stores landed relative to the vptr
stores, which source can control. Here it is only *how* the same stores are
addressed, which it cannot. When the residual is a lea plus short displacements
against direct displacements, and the instruction count matches, stop -- it is
the same class as a register-allocation difference.


## A base needs a declared destructor before an EH frame appears

Two ModuleData constructors came out with no EH frame at all where retail has
one. The bodies were otherwise right: vptr store, then a member constructed
through an out-of-line call.

The frame exists to unwind if that member's constructor throws -- but only if
there is something to unwind. With a base that has no destructor and no
previously-constructed members, MSVC correctly concludes there is nothing to
clean up and omits the frame entirely. Declaring `~ModuleData();` on the base,
without defining it, makes the base destructible, and the frame and its state
store appear exactly as retail has them.

This is the mirror of the TerrainRoadType lesson. There, giving a base a virtual
destructor added an unwind state that retail did not have and shifted every
index by one. Here, withholding a destructor removed the only state retail did
have. The destructibility of a base is a load-bearing modelling decision in both
directions, and the unwind states are how you read which way it should go.

## Constructors that differ only in vtable address convert as a batch

The three 82-byte ModuleData constructors -- HeroDie, UpgradeDie and
WeaponBonusUpdate -- are instruction-for-instruction identical apart from the
vtable addresses their classes store. One class shape written three times
converted all three in a single build.

That is a cheaper pattern than the ICF case, where several names share one
address. Here the addresses genuinely differ, so each needs its own file and its
own row, but the reconstruction work is done once. Worth scanning a family for
equal sizes and diffing two bodies before treating them as separate problems.


## Cluster naked bodies against each other, not just against converted ones

The clone screen has always compared naked rows to already-converted ones.
Clustering naked rows against *each other* by normalised body finds work the
clone screen cannot: 15 clusters covering 42 rows between 40 and 200 bytes,
where solving one member solves the rest.

The clusters are worth listing by kind, because they fail for different reasons:
four crate-collide ModuleData constructors share a single address, so a rename
would do -- except the body has the sub-object folding problem. Five
Register_*_Prototype functions share a shape but each calls a per-type prototype
constructor that has neither a ledger row nor a pin, so they cannot be written
without inventing names. Two AI State constructors differ only in vtable and get
within one instruction of matching.

## The vptr sink stops at the end of the leading same-valued run

AIPanicState reached one difference. Retail emits every member store and then the
vtable store last, including a trailing byte set to 1 after a long run of zeros.
MSVC sinks the vptr only to the end of the leading zero run, so the vptr lands
before that trailing byte.

That is a sharper statement of the sinking rule than the one recorded earlier.
The sink does not go "past the member stores" -- it goes to the end of the first
group of stores sharing one value, and a store with a different value ends the
run. Where retail's vptr sits after such a store, the source needs that store to
belong to the same group or to come from member construction rather than the
constructor body, and neither is expressible when the value genuinely differs.

Recording it as a distinct residual: same-value-run-ends-the-sink, separate from
the register-carrier and addressing-mode residuals already on file.


## Writing assignments in retail's emitted order is worth doing first

PhysicsBehaviorModuleData is all constants and no calls, and written in plain
offset order it came out badly scrambled. Rewriting the constructor body so the
assignments appear in the order the retail bytes show them -- the four 1.3f
stores, then the eight zeros, then the remaining groups -- made the entire
leading half byte-identical, including where the vtable store lands.

That is cheap and should be the first move on any all-constant constructor
rather than a later correction. MSVC preserves source order within a value group
and hoists whole groups, so source order in retail's own sequence is the closest
starting point available.

What it does not fix is which constants get a register. Retail keeps 0.33f as an
immediate at each of its three uses and holds 0.66f in edx interleaved with
them; MSVC registerises both and hoists the three 0.66f stores into a single
group ahead of the vptr. That is the constant-materialisation choice, and it
belongs with the register-carrier residual rather than with anything source can
express.

## The easily-reachable pool at 40-200 bytes is essentially exhausted

Screening every naked single-row body in that range against all recorded
residuals at once -- no rep or x87, no unnamed callees, no global references, no
sub-object lea bases, no duplicate stores to one offset -- leaves three
candidates, and two of those are already on file as blocked.

The lea-base exclusion is probably over-broad, so the true number is higher than
three. But the direction is real: what remains at this size is dominated by the
handful of residual classes now on record rather than by unexplored shapes.
Further progress here likely needs either larger functions, multi-row files, or
solving one of the residuals outright rather than screening around them.


## Disassembling at address zero silently breaks every call-target lookup

Last tick's conclusion that the clean pool was exhausted was wrong, and the
reason is a bug in the screen rather than anything about the binary.

The screen decoded each body with capstone starting at address 0 instead of at
target_rva + 0x400000. Relative call targets are computed from the instruction
address, so every call resolved to a meaningless address, every name lookup
failed, and the "all callees named" filter rejected every candidate. The screen
reported zero and looked like a finding.

The same screen also only consulted functions.csv for callee names. Many
legitimate callees are named only by a pin in symbols.csv -- ObjectModule,
RS_Member and AIInternalMoveToState were all found that way earlier this session
-- so that omission rejected more candidates on top.

Fixing both turned zero candidates into 49. This is the second time a wrong
disassembly base has produced a confident wrong answer; the first was reading a
function's body at a guessed RVA and getting plausible instructions with silently
wrong call annotations. Both failures look like results rather than errors, which
is what makes them expensive.

Worth a standing habit: when a screen returns zero or near-zero, instrument the
stages and check the counts before believing it.


## Count the vtable stores to count the polymorphic layers

Three ModuleData constructors this tick shared one base-constructor pin, and the
two 82-byte ones cloned straight from an already-converted sibling. The 69-byte
one did not, and the reason is visible without any building.

The 82-byte bodies store two vtables: the intermediate class's, then the derived
class's overwriting it. The 69-byte body stores exactly one. That means there is
no intermediate -- the class whose constructor this is owns that single vtable
directly. Keeping the intermediate layer from the sibling produced a second
store that retail does not have, and removing the derived override instead did
not help, because MSVC emits a vtable for every polymorphic class whether or not
it introduces new virtuals.

So the count of vtable stores in a constructor is the count of polymorphic
classes at or above it that get constructed, and it should be read off the body
before choosing a hierarchy. Two stores means an intermediate; one store means
the class sits directly on its base.


## Group a family by call count and vtable-store count before writing anything

Twenty-five naked ModuleData constructors call one of three now-proven base pins.
Grouping them by two numbers read straight off the body -- how many calls, and
how many vtable stores -- sorts them into shapes that each convert the same way,
and three from the single-vtable group landed on the first build.

The two counts answer the two structural questions. Vtable stores give the
number of polymorphic layers being constructed: one means the class sits
directly on its base, two means there is an intermediate. Call count separates
how many sub-objects have out-of-line constructors, which is what the EH frame
and the member ordering hang off.

The presence or absence of the EH frame then settles destructibility, in the
direction recorded earlier: ObjectCreationUpgradeModuleData has no frame at all,
so neither its base nor its member may carry a declared destructor, while the
two that do have frames need one on the base.

Reading all three signals before writing turns what used to be three or four
builds into one.

## Pair every asm dump with the real source; a lot of them already compile

`tools/list_naked_candidates.py` hands you one naked body at a time and leaves
you to write the C++. Often you do not have to: the real Zero Hour source is
already in the tree, and for a useful fraction of these rows it already emits
the retail bytes exactly. Find them mechanically rather than one at a time.

Take every `matched` row whose source file contains `__declspec(naked)` or
`__emit` - about 4,970 of them - demangle-lite the symbol to `Class::method(`
(or ` freefunc(` for `?name@@Y...`), grep Code/ for other sources containing
that text, and run `tools/explain_mismatch.py <symbol> --rva --size --source
<candidate>`. Requiring exactly one candidate gives 308 pairs; allowing several
and testing each gives 794. Sort the results by how many `!=` lines came back.

What that produced in one session, all of it assembly retired for C++ rather
than new coverage: `HLodDefClass::Initialize` (485B) and
`RenderObjClass::Validate_Transform` (80B) needed nothing at all - the rows just
moved onto hlod.cpp and rendobj.cpp and the thunk TUs were deleted. Four more
were one to three instructions away and each of those instructions turned out to
name a real BFME drift:

- `MultiIniFieldParse::add` - retail throws with `mov [esp+0xc],1` where Zero
  Hour's `ERROR_BUG` is 0xDEAD0001. **BFME rebases the whole ErrorCode enum at
  1.** The `_CxxThrowException` type descriptor is unchanged, so only the value
  moved. That constant is thrown all over the engine.
- `AdaptiveDeltaMotionChannelClass::decompress` - `fmul [eax+0x14]` where the
  source's `Scale` is at +0x10. motchan.h already carries a `_bfme_adm_scale2`
  hole at +0x14, so the two are simply the other way round.
- `AABTreeClass::Cast_Ray_To_Polys` - **MeshGeometryClass** has `Poly` at +0x2C
  and `Vertex` at +0x30, four lower than the header, and `PolySurfaceType` at
  +0x60, 0x1C higher: BFME drops one dword ahead of Poly and adds seven pointer
  members between Vertex and PolySurfaceType. `ShareBufferClass::Get_Array` is
  at +0xC in both.
- `VertexMaterialClass::Get_Diffuse` - the material pointer is at this+0x8, not
  +0xC. vertmaterial.h parks its BFME dword ahead of the pointer; putting it
  between `Flags` and `AmbientColorSource` instead satisfies that header's own
  +0x14/+0x18 constraint and puts the pointer back at +0x8.

Each of the last four is a header fix that is byte-neutral or better for its
whole library, and each is blocked only by the red full gate. Until that clears,
read the member at the retail offset in the body and write the evidence next to
it - `CrateSystem.cpp`'s `retailLoadType` is the precedent.

Two mechanical notes. `explain_mismatch` caches its own
`build/match/<name>.harvest.obj`, separate from the build's object, so delete
both when a source edit looks like it had no effect. And check the mangled name
against the right overload - `decompress` has a two-argument and a
four-argument form, and only one of them is the dump.

### correction: the TeamFactory destructor claim above is not settled

The section "TeamFactory's destructor is at 0x000F74C0, not 0x009F2800" is
overstated and should not be acted on as written. It reasoned from one side of
the contradiction only. The other side:
`??_GTeamFactory@@UAEPAXI@Z` is claimed at **0x009F2900**, and 0x009F2900 is
slot 0 of vtable **0x11457F8** - which is the table the 0x009F2800 body installs.
A class's deleting destructor sits in slot 0 of its own primary vtable, so if
that `??_G` row is right then 0x009F2800 *is* `~TeamFactory` and the existing
claim is correct.

So the two rows disagree about which class owns which table pair:

    ??0TeamFactory@@QAE@XZ  @0x000F2250  writes 0x1085F1C / 0x1085F08
    ??_GTeamFactory@@UAEPAXI@Z @0x009F2900  lives in 0x11457F8

and that disagreement is exactly what the DIR32 check is reporting. One of the
two is a bad claim; nothing found so far decides which. The
`??$initSubsystem@VTeamFactory@@` instantiation @0x00074F90 does not settle it
either - it makes only four calls, none of them a TeamFactory constructor, and
the one vtable it writes (0x1075E40) belongs to an eight-byte helper it
allocates.

What does still stand from that section: 0x000F74C0 is a real 118-byte
destructor-shaped body that installs 0x1085F1C and 0x1085F08 and is unclaimed,
and 0x009F2800 carries three names at once, so at least two of those three are
wrong regardless of how the TeamFactory question resolves. Start from whichever
of the two rows can be independently disproved, not from the vtables alone.

## One scheduling swap is holding back 3 KB of asm-to-C++, in eight bodies

Eight naked dumps whose real source is already in the tree compile to the right
size and differ from retail only - or almost only - by the same two adjacent
instructions, in that order:

    retail:  push ecx / mov [esp+N], esp / mov ecx, esp / push arg / call copyctor
    ours:    push ecx / mov ecx, esp / mov [esp+N], esp / push arg / call copyctor

`mov [esp+N], esp` is the unwinder's slot for a by-value `UnicodeString`
temporary and `mov ecx, esp` is its `this`; the two are independent and the
scheduler simply picks a different order. Same bytes, swapped.

The eight, with what each is worth once it is fixed:

    737B  PopupReplaySystem                  PopupReplay.cpp
    446B  GameInfoWindowInit                 GameInfoWindow.cpp
    435B  PopupJoinGameSystem                PopupJoinGame.cpp
    386B  PopupReplayInit                    PopupReplay.cpp
    363B  DownloadMenuUpdate                 DownloadMenu.cpp
    270B  GadgetRadioButtonSystem            GadgetRadioButton.cpp
    250B  PopulateRemoteIPComboBox           NetworkDirectConnect.cpp
    179B  getSlotNum@LANGameInfo             LANGameInfo.cpp
    171B  GadgetCheckBoxSystem               GadgetCheckBox.cpp

For `PopupReplayInit` and `GadgetRadioButtonSystem` this swap is the *only*
difference left; the others carry one or two member offsets alongside it. So a
single codegen answer is worth about 3,240 bytes of assembly
retired, and probably more once the pairing sweep is finished.

Source shaping does not move it. Tried on `PopupReplayInit`: wrapping the
argument in an explicit `UnicodeString(...)` temporary changes nothing, and on
`GadgetRadioButtonSystem` neither binding the argument to a local pointer first
nor qualifying the call helped. Every one of these is a by-value
`UnicodeString` argument copy-constructed from an lvalue, so if it is a source
difference it is one shared by all eight; more likely it is a compiler switch.
Worth someone comparing the flag set against a body that *does* emit the retail
order.

That search has now been done, and it rules the easy answers out: **504 matched
sources already emit the retail order**, `Code/GameEngine/Source/Common/GameLOD.cpp`
among them, and its flag set is the same `/MD /EHsc` stlport line PopupReplay.cpp
uses. So our toolchain can produce both orders and it is neither a flag nor a
compiler-version difference. It is context - which is the puzzling part, because
in PopupReplayInit every other byte of the 386 already matches, so whatever the
scheduler is reacting to is not visible in the emitted code around it.

## Arity-contradicted rows split into two kinds, and the strings tell you which

`tools/audit_ret_arity.py` reports 245 rows whose retail stack cleanup
contradicts their decorated name, and ten of them are large naked dumps
(10.4 KB). Those all byte-match by construction, so the gate cannot see them -
but pulling the string literals a body pushes separates the two failure modes in
about a minute each. Scan the claimed range for `68 <imm32>` and read whatever
each immediate points at in .rdata.

**Wrong identity** - the strings name a different class entirely:

- `?init@GameTextManager@@UAEXXZ` @0x0051F3A0, 3411B, `ret 4`. Pushes eighteen
  literals and every one is an AptMainMenu callback name. Retracted: while it
  stood, the real GameTextManager::init could never be claimed, because one name
  gets one address.
- `?updateBridgeRepair@AIPlayer@@IAEXXZ` @0x00167930, 1077B, `ret 0xC`. Every
  string is about team recruiting - "Unable to recruit singleton team ",
  " recruits ", " from team " - and nothing about bridges. Left in place with the
  evidence logged, since I could not name it; the real `recruitSpecificAITeam` is
  claimed elsewhere with two parameters, so this is a third recruiting function
  taking three.

**Right class and method, wrong signature** - the strings fit the name perfectly
and only the parameter list is off. I first assumed these were boundary errors;
they are not, but neither are they all one thing. Check two things at each
address before deciding: that the byte before it is 0xCC and the first bytes are
a prologue, and that the INT3 boundary returns the claimed size. Seven of the
ten pass both, so their ranges are right and the bodies genuinely take arguments
the mangled name does not declare. One does not:

- `?handleQMMatch@PeerThreadClass@@QAEXXZ` @0x00649180, 653B, `ret 0x24` -
  pushes "We're matched!".
- `?joinBestGroupRoom@GameSpyInfo@@UAEXXZ` @0x00634EF2, 433B, `ret 4` - pushes
  "GUI:GSGroupRoomJoinFail" and "GUI:Error". This one is a **bad start address**,
  not a signature error: 0x00634EF2 is not INT3-preceded, is not aligned, and
  begins `test eax,eax` - it is 0x634EF2 sitting inside a larger function whose
  real entry is earlier. Check the prologue before concluding anything about the
  parameter list.
- `?validate@ThingTemplate@@QAEXXZ` @0x00139B40, 350B, `ret 4` - pushes
  "DefaultThingTemplate".

Do not retract the second kind - the coverage is byte-true and the class and
method are right. What they need is the parameter list, and the body shows it:
read how the argument at [esp+4] is used before writing a type into the
mangling. `?setWrappedCommandID@NetWrapperCommandMsg@@QAEGXZ` was the same
species and was easy only because the correctly mangled name already existed at
the same address; these three have no such twin, so guessing the type would be
inventing identity. And note
that three of the ten push no literals at all - `BuddyThreadClass::Thread_Function`,
both `BFMEConnectionManager` updaters - so those need a different handle.

### resolved: the 0x009F2800 cluster is PartitionManager, and TeamFactory's destructor is at 0x000F74C0

The correction two sections up said the TeamFactory question was unsettled. It is
settled now, and the original reading was right. What decides it is the
constructors' **call sites**, which are independent of any vtable reasoning:

    ??0TeamFactory@@QAE@XZ  @0x000F2250  installs 0x1085F1C / 0x1085F08
                                         called from ?init@GameEngine@@
    (0x009F2730)            installs 0x11457F8 / 0x11457E8
                                         called from ?init@GameLogic@@

GameEngine::init is where TheTeamFactory is made, so the first is TeamFactory and
its tables are 0x1085F1C / 0x1085F08. The 0x009F27xx cluster is a GameLogic
subsystem instead - and `??1PartitionManager@@UAE@XZ`, one of the three names
claiming 0x009F2800, is exactly that. So 0x009F2730 is PartitionManager's
constructor (not ControlBar's, as claimed) and 0x009F2800 is ~PartitionManager.

That makes `??1TeamFactory@@UAE@XZ` and `??1FXListStore@@UAE@XZ` wrong on that
address, and `??_GTeamFactory@@UAEPAXI@Z` @0x009F2900 wrong too - it is slot 0 of
0x11457F8, which is PartitionManager's table. The TeamFactory destructor row is
retracted; the real body is the unclaimed 118 bytes at **0x000F74C0**, the only
other function in the image that writes 0x1085F1C.

The general lesson: when two vtables contradict each other, do not try to settle
it from the tables. Find who calls the constructor. A subsystem singleton is
constructed in exactly one place and that place names it.

### the Mouse layout correction does not survive W3DMouse's unwind funclets

With the gate green I tried the header fix the DirectInputMouse work had been
waiting for: move the 0x10 out of Win32Mouse into Mouse's tail (DirectInputMouse
derives from Mouse directly and reads m_pDirectInput at this+0x4E14, so
sizeof(Mouse) is 0x4E14 on its own) and put eight bytes ahead of m_mouseEvents,
taking them back out of _bfme_hole_beforeCurrentCursor so m_currentCursor stays
at +0x4DA8. Both are byte-neutral for sizeof and both are what the retail reads
say.

Win32DIMouse.cpp then verifies with its two TU-local hacks removed, which is the
result I wanted. But W3DMouse.cpp loses `uw_00c4c358`, one of two unwind funclets
belonging to `initW3DAssets`, and it is not a label-renumbering: `gen_uw.py land`
does not touch parent-owned rows, and trying $L57591 through $L57596 by hand all
fail. The funclet's *contents* change, so the eight bytes ahead of m_mouseEvents
move something `initW3DAssets` holds inside a try-scope.

Reverted. The DirectInputMouse reads stay TU-local. Whoever picks this up should
work out what initW3DAssets has in scope at that point first - the +8 is probably
right but in the wrong place among the members between m_isTooltipEmpty and
m_mouseEvents.

## TeamFactory takes two strings everywhere Zero Hour takes one

Converting `?initTeam@TeamFactory@@QAEXABVAsciiString@@0_NPAVDict@@@Z` (220B at
0x000F8170) produced a single finding that repeats across the whole class: where
Zero Hour identifies a team prototype by one `AsciiString`, BFME identifies it by
two. Three signatures fall out of one body:

- `findTeamPrototype(owner, name)`. At 0x000F8191 retail pushes both strings
  before the call. Two independent call sites now agree - `initTeam` and
  `createInactiveTeam` at 0x000F7AC1 - and both reach it through ILT 0x00040A39,
  which lands on the gen-dump at 0x000EFE10. That dump is `findTeamPrototype`.
- The `TeamPrototype` constructor at 0x000F3E40 takes seven parameters, passing
  owner and name as two separate strings, then the `Player*`, the singleton flag,
  the `Dict*` and the id.
- `createInactiveTeam(owner, name)`. Its body at 0x000F7AB0 ends `ret 8`, so the
  ledger name claiming one parameter is wrong-arity.

This is the same shape as the pair-keyed `m_prototypes` map derived earlier from
`addTeamPrototypeToList`, and it is confirmed from the other direction: at
0x000F822B `initTeam` re-reads the two strings off the prototype it has just
built, at `proto+0x10` and `proto+0x14`, rather than reusing its own parameters.
Those are exactly the `m_first`/`m_second` offsets the map key was built from.

Two smaller facts, both cheap to reuse:

- BFME's `initTeam` early-returns when the prototype already exists. Zero Hour
  only asserts, so the guard compiles out under NDEBUG and the retail branch at
  0x000F819C looks like an invention until you notice it.
- `createInactiveTeam` throws where Zero Hour returns NULL: `push 0x011E0004`
  (`__TI1?AW4ErrorCode@@`) with `0xDEAD0003` written into the exception object,
  which is `throw ERROR_BAD_ARG` under the ErrorCode rebase at 1.

`TeamPrototype` is 0x278 bytes - `initTeam` allocates exactly that, and
`createInactiveTeam` reads `[esi+0x274]` as its last dword. Confirmed members:
`m_first` +0x10, `m_second` +0x14, singleton flag bit 0 of the byte at +0x18,
`getFirstItemIn_TeamInstanceList()` +0x274, `m_executeActions` +0x1EC.

### The lead worth taking next

`Code/GameEngine/Source/Common/RTS/Team.cpp` **already contains the real C++ for
`createInactiveTeam`** - `throw ERROR_BAD_ARG`, `getIsSingleton()`,
`getFirstItemIn_TeamInstanceList()` and `m_executeActions` all sit where the bytes
want them. It compiles to 287 of 390 bytes and the very first difference is
`mov eax, [esp+0x14]` against our `[esp+0x10]`: the missing second parameter and
nothing else. So this is a pairing job, not a reconstruction.

What blocks it is not the gate, which is green - it is blast radius.
`findTeamPrototype` and `createInactiveTeam` are declared in `Team.h` and called
from many byte-verified translation units, so widening both signatures at once
re-codegens all of them. Do it as its own change with the full gate run before and
after, not as a rider on a conversion.

### initFromSides is not a pairing case: SidesList itself drifted

`Team.cpp` also already defines `initFromSides`, so it looks like the same easy
job as `createInactiveTeam`. It is not. Ours compiles to 344 bytes against a
260-byte target - *larger* - and the reason is that BFME's `SidesList` is a
different container, not that the loop body differs.

Our iteration reads an `Int` count at `sides+0x194` and a pointer array at
`sides+0x19C`, stepping with `lea esi, [eax + edi*4]`. Retail does not count at
all - it walks a chain threaded through 16-byte records by index. The loop bottom
at 0x000F8499 is what gives it away:

    mov   eax, [esp+0x2c]            ; sides
    mov   eax, [eax + 0x63c]         ; -> record block
    movsx ecx, word ptr [edi+eax]    ; short at the CURRENT record is the next index
    cmp   ecx, ebx                   ; zero terminates
    jne   0xf8400
    ...
    f8400: shl ecx, 4                ; index * 16 -> byte offset of the next record
           mov edi, ecx
           cmp word ptr [edi+eax+6], bx   ; skip this record unless the short at +6 is 0
           lea esi, [edi+eax+0xc]         ; the Dict lives at record+0xC

So: a block pointer at `SidesList+0x63C`; 16-byte records addressed by index, not
by pointer; the `short` at `record+0` is the *next* index with 0 as the terminator,
which makes record 0 the head sentinel; a `short` filter at `record+6` that must be
zero for the record to be processed; and a `Dict` embedded at `record+0xC` - one
pointer wide, which is why the record is only 16 bytes.

The entry read at 0x000F83EB is the same field with `edi` still zero, so the
function starts by following record 0's link rather than by loading a length.

The `Dict` reads themselves are unchanged. Three `NameKey` globals feed the getter
at 0x0002FF6D and the `Bool` getter at 0x00043A1D: 0x012A75B8, 0x012A75C0 and
0x012A75C8, which are `TheKey_teamName`, `TheKey_teamOwner` and
`TheKey_teamIsSingleton`. `initTeam` is then called through ILT 0x00039E0F with
those four arguments, exactly as Zero Hour has it.

Doing this one means modelling `SidesList` TU-locally first. Worth it, because
`SidesList+0x63C` will explain every other unmatched body that walks sides, but it
is a class model rather than a body conversion - budget it as such.

## Name dumps from the call graph, not from their bytes (tools/callers_of.py)

Byte-scanning is finished as a lane, and 5.0 MB of the binary is still sitting in
115,086 anonymous `?d_xxxxxxxx@@YAXXZ` dumps. Those two facts are the same fact:
`locate.py` can only place a function whose compiled bytes still agree with retail,
so everything that drifted is exactly what stays anonymous, and no amount of
re-scanning will move it.

The call graph is immune to that. A dump reached from one named function is pinned
by that function - open its Zero Hour source, read what it calls at that point, and
the dump has a name. Drift in the callee's body is irrelevant, because the evidence
is the caller's `E8` displacement.

`tools/callers_of.py` does this both ways:

    python3 tools/callers_of.py 0x000efe10     # who calls this address
    python3 tools/callers_of.py --report 40    # best naming candidates

It follows one level of link thunk and only counts a target that is a known
function start, which is what keeps stray `E8` bytes inside instruction operands
out of the results. Checked against the one answer already known independently:
0x000EFE10 comes back with `TeamFactory::initTeam` and
`TeamFactory::createInactiveTeam`, the two callers found by hand, and nothing else.

**There are 3,910 anonymous dumps with exactly one named caller.** Each is one
source read from a name. The largest:

    4572  0x004A4240  <- ControlBar::updateSpecialPowerShortcut
    3775  0x0072B580  <- W3DTerrainBackground::doTesselatedUpdate
    3124  0x007B14A0  <- W3DProjectedShadowManager::renderShadows
    3002  0x0042A270  <- ParticleSystemFXNugget::doFXObj
    2924  0x00997C80  <- _luaD_call
    2669  0x0027C250  <- AnimalAIUpdate::~AnimalAIUpdate
    2445  0x003006B0  <- ScriptActions::executeAction

Two cautions. A sole caller pins *an* address, not a *name* - the caller may reach
several helpers, so confirm with arity (`ret imm16`), the callee's own string
literals, or a second caller before writing the name down. And a name is not a
conversion: it makes the body attackable, which is the step that has been missing.

### ...and let the dump name its own file (`--files`)

Retail keeps the `__FILE__` strings its asserts push, so a body that asserts names
the translation unit it was compiled in - and that survives drift, which is exactly
the property needed here. `callers_of.py --files` crosses that with the sole-caller
edge. Thirteen dumps currently name their own source, and in nine of them the
caller lives in the same file, so they are same-TU helpers and the search for a
name is one file wide:

    3002  0x0042A270  FXList.cpp        <- ParticleSystemFXNugget::doFXObj
    2445  0x003006B0  ScriptActions.cpp <- ScriptActions::executeAction
    1071  0x00390A50  GameLogic.cpp     <- GameLogic::startNewGame
     825  0x001CDE30  Object.cpp        <- Object::attemptDamage
     587  0x0075A990  W3DRopeDraw.cpp   <- W3DRopeDraw::doDrawModule
     107  0x001E1680  Weapon.cpp        <- Weapon::reloadWithBonus

The four where the two files disagree are the more interesting ones, because the
disagreement is the finding: `0x00097020` asserts in `RandomValue.cpp` but is called
from `BoneFXUpdate::update`, which is what an inlined `GameLogicRandomValue` helper
looks like, and `0x00416820` asserts in `Drawable.cpp` under
`StealthUpdate::changeVisualDisguise`.

Only thirteen of 3,910 assert at all, so this is a narrow filter rather than a
general answer - but it is the cheapest thirteen in the queue.

## Converting a naked row is not coverage; claiming an unclaimed body is

Worth stating plainly because I spent a long stretch optimising the wrong
number. A `__declspec(naked)` row is already `matched`, so rewriting it as real
C++ moves progress.py's clean-C++/ASM split and leaves Total exact untouched.
An unclaimed retail body has no row at all, so claiming it is what grows
coverage.

Both are real work and the pre-commit gate exists precisely to stop lifts
travelling the other way, but they are different metrics and the repo tracks
them separately. `tools/next_work.py` selects for the second kind.

## Use the tools the repo ships before building screens

`tools/next_work.py` names a candidate, weights the draw by measured land rate,
and hides the candidates already recorded in re_attempts.log -- which is the
dedup I had been maintaining by hand as a SKIP set. `tools/decode_calls.py`
compiles a source the way build.py does, finds every unresolved REL32, decodes
the displacement out of the target bytes and prints a ready-to-paste
symbols.csv pin: exactly the grep-for-j_, follow target=FUN_, grep symbols.csv
loop I ran manually dozens of times. `tools/add_match.py` appends a claim and
reverts itself if verification fails.

One doc drift found while adopting them: next_work.py prints
`decode_calls.py --rva <a> --size <n>` as the start command, but decode_calls
takes no --size and is a post-build-failure tool, not a starting disassembler.

## An explicit template instantiation does not guarantee a claimable body

Code/gen_small/tgrid_107.cpp already contains
`template class _STL::vector<Gen_t_001fa830_p12cd >;`, so the vector's
_M_insert_overflow is emitted by that TU and the unclaimed retail body at
0x001FA5B0 looks like a free claim. It is not.

The emitted body carries a full EH frame where retail's has none, because the
generated file's own cl line adds /EHsc and retail built that instantiation
without unwind. Four callees also need pins. The pins are routine; the exception
model is not, because the file carries forty other verified rows and changing
its flags needs the full gate rather than a scoped build.

## One-line lessons kept from trimmed sections

- MSVC does not fold `a == K || a < K` into a single `jle`; it emits `cmp/je/jl` to the same target, exactly as written. A retail `cmp` followed by two conditional jumps to one label is therefore evidence of two source conditions, not one relational operator — and getting the split right can also settle register allocation that looked arbitrary.
- A divide-by-constant magic pins a structure size exactly: brute-forcing which divisor reproduces `imul <magic>` + add-back + `sar n` over a range of inputs gave a unique answer (292 for PlayerTemplate). A plain pointer subtraction then regenerates the whole sequence.
- MSVC returns a 4-byte struct in `eax`, so a one-pointer iterator will not reproduce a callee that takes a hidden return pointer. Declaring a copy constructor (never defined) makes the type non-trivial and forces the memory-return form — the same declaration trick that fixes by-value class arguments.
- A hand-rolled value type is not a substitute for the reference one. Replacing WWMath's `Vector3` with an equivalent-looking class (initialiser-list constructor, compiler-generated copy and assignment) made MSVC round-trip every temporary through memory with integer moves; copying the real header's form — user-defined copy constructor and `operator=`, constructor bodies that assign — kept each component in the FPU and the body collapsed onto retail.
- MSVC does not evaluate float operands in source order, and is not consistent between components of the same expression: `Max + Min` loaded `Min.X` first but `Max.Y` and `Max.Z` first. A reversed-looking operand pair in one component proves nothing on its own — flip the whole expression and re-compare.
- When a body is mostly a container's inline machinery, identify the exact container first — `SimpleDynVecClass` and `DynamicVectorClass` have different member order and different growth rules, so guessing costs a full reconstruction. Two divide-by-four sequences in one function were `Shrink` (`ActiveCount < VectorMax/4`, folding to `VectorMax/4 > 0` right after `Delete_All` zeroes the count) and `Grow` (`Length() + Length()/4`) — same idiom, unrelated meanings.
- Padding filler must account for the vtable pointer explicitly, and whether one exists depends on the *shim* class, not the real one. A filler of `[0xD8]` in a class that declares a virtual puts the next member at 0xDC; the same filler in a class that declares none puts it at 0xD8. Both mistakes shift every offset in the dump by four and read like a different layout rather than an off-by-one-slot — check the shim's own virtuals before re-deriving the layout.
- `mov reg,0` where `xor reg,reg` would do is not a different constant: `xor` clobbers flags, so MSVC picks the longer encoding when a comparison has already set flags that a later branch still needs.
- The decorated name distinguishes `class` from `struct`: `PBURGBColor@@` is a pointer-to-const *struct*, `PBVAsciiString@@` a pointer-to-const *class*. Declaring the wrong one produces a differently-mangled symbol and `build.py` fails with "symbol not found in object" rather than a byte mismatch — read the `U`/`V` before writing the shim.
- MSVC does not algebraically simplify integer division, so `LOGICFRAMES_PER_SECOND * t / DRAWABLE_FRAMES_PER_FLASH` stays a multiply followed by a divide instead of collapsing. Two constants in the source remain two operations in the bytes, which is what makes them individually recoverable.

--------------------------------------------------------------------------

# lessons.md as it stood on 2026-08-29, before the curation pass

Preserved verbatim. The curated file keeps one canonical entry per recipe;
this is where the war stories, the superseded derivations and the retracted
hypotheses went. Nothing below was deleted from the project -- it was moved
here so that lessons.md could be read end to end.

# Codegen recipes

Full history: docs/lessons-archive.md and git log.
This file is curated, not append-only: edit a recipe in place rather than
appending a new section; the commit message is the place for the war story.

## A naked body passing the byte gate proves nothing

Symptom: `Functions: OK N/N` on a file that is still `__declspec(naked)` /
`__asm { __emit ... }` — the dump reproduces its own bytes by construction.
Removing only the `naked` keyword around a pure `__emit` block also still
passes. Rule: a conversion means NO `__asm`/`__emit` anywhere in the file;
check what is on disk, not the ledger — `status=matched` can be leftover from
the original dump commit.

## A naked row's name is unverified by construction

The byte check is a tautology for a dump, so the attached name was never
tested. Read the body against the claimed signature BEFORE starting: `ret N`
vs the mangled argument list, `or eax,-1` vs a void return, eax loaded vs `_N`
return, this-relative offsets that make no sense for the claimed class.
Example: `??1TooltipUpgrade@@UAE@XZ` ends in `ret 4` — destructors take no
arguments, so the name is wrong whatever the bytes say.

## Row boundary rules

A MASM dump matches at any length (one 231-byte function claimed 1006 bytes
and swallowed three neighbours); a 5-byte row matches any E9 thunk; a 1-byte
row matches every bare `ret`. Before adding or trusting a row: deref the thunk
chain, measure the body by disassembly, and check the claimed address is an
instruction boundary — linear-decode from the containing function's start;
interior `int3` is decisive. Functions from different TUs do not interleave in
the image.

## vptr scheduling: screen before writing

MSVC sinks a constructor's vptr store exactly to the end of the leading run of
same-valued member stores, no further; retail's placement varies. Compare
retail's vptr position against that prediction: if they agree, convert; if
not, park — no source ordering reaches vptr placement.
Members initialised by a member constructor land after the vptr and before the
body; stores between the interim and most-derived vtable groups are base-
subobject member inits, not body statements.

## novtable is one knob with two effects

It removes the interim per-base vtable stores (module ctors writing each
interface vtable twice → once) AND removes that base's unwind entry (all EH
states shift down by one, body a few bytes short). Set it by what retail
shows, not habit. Destructor variant: retail restoring only the base vptr at
the end means the derived class is novtable; a derived vptr store at entry
means it is not.

## Read destructible subobjects off the unwind states

Retail's highest EH state + 1 = destructible subobjects, bases included. A
base gets an unwind entry only if it has a declared destructor — declaring
`~Base();` (undefined) adds the missing frame; a virtual destructor where
retail has none adds a state and shifts every index. A virtual destructor
stores a vptr only in a ROOT polymorphic class; in derived destructors it is
elided as redundant, so "no vptr store AND no base-destructor call" is the
test for non-polymorphic, and neither half alone means anything.

## throw() removes EH frames and temporary unwind states

`new T` carries an EH frame just to call `operator delete` if T's ctor throws;
declaring the reachable constructors `throw()` removes it (an undefined ctor
is assumed throwing). Wider: `throw()` on whatever executes between a
temporary's construction and destruction removes that temporary's unwind
state. Declaring `void __cdecl operator delete[](void *) throw();` (as real
<new> does) removes the state for `delete[]` in a destructor. Scope the
declaration to a TU shim; editing a real shared header is its own tick.
Counter-lesson: the constructor-inlined-into-new-expression shape is NOT
reachable from source (forceinline/throw()/nothrow all tried) — park those.

## SEH shape is a flag, not code

Base build is `/EHs-c-`. Right length but an extra `fs:[0]` prologue means the
per-file `// cl:` line re-enabled exceptions (`/GX-` restores). The
`mov [esp+N],esp` stash before a by-value class argument is the /EHs model;
/EHsc and /EHa add an SEH prologue retail may lack. Probe flags directly with
a throwaway TU and build.py's compile_source instead of round-tripping the
byte gate, and give the probe the same destructible locals as the target.

## x87 flags from byte tests are mostly false

`any byte in D8..DF` matches displacements and immediates: 603 of 753 flagged
functions had no x87 at all. Decode with capstone before believing an x87 (or
any opcode-shaped) label, and re-screen parked rows when a screen is fixed.

## Write the reference's loop; MSVC's rotation is the target

A counted `for`/`while` gets rotated (entry test peeled, value test on the
back edge) and small counted loops get unrolled — `for (i=0;i<4;i++)
size=(size<<8)|b[i]` unrolls two-at-a-time into paired dword/word loads that
no hand-unrolled spelling reproduces. Retail's bottom-tested scan with an
early exit past the loop is `do{}while` plus `goto`; reach for that only when
no plain loop form produces the flow.

## Byte loads widen within the array they belong to

Adjacent byte reads widen to the widest access that stays inside their own
array: `struct { u8 magic[2]; u8 size[4]; }` gets dword+word where a flat
`u8[6]` gets neither. Split buffers into the sub-arrays retail's accesses
imply.

## Register allocation is not source-controllable

Same instruction count, same length, but a different induction base, lea-base
vs direct displacements, esi/edi swapped, or a constant in a different
register: these are compiler tie-breaks with no source lever. Stop permuting
and record present-unmatched. (Distinguish from *placement* of stores, which
source does control.)

## Ordering levers that ARE source-controllable

- Initialiser list emits in declaration order; body assignments emit as
  written. Retail's store order tells you which to use — a flag at +0x54
  stored before the word at +0x50 means body statements, not init list.
- Independent locals initialise in declaration order.
- Switch arms lay out in source order; sort the jump table by target address
  to recover it.
- `x = y` (inline operator= forwarding to set) materialises the destination
  before the argument; `x.set(y)` pushes the argument first.
- A discarded return value becomes a tail jump: retail's real call where you
  emit `jmp` means the function returns something the reference discards.

## A this-adjustment hoists only if the source goes through the owning base

An override of a virtual declared in a *secondary* base is entered with that
subobject's `this`. Reading a member off it directly gives negative
displacements from the entry register:

    ours:   mov esi,ecx / mov eax,[esi-8] / mov ecx,[esi-0xc]
    target: mov eax,[ecx-8] / lea esi,[ecx-0x10] / mov ecx,[esi+4]

Retail materialises the *primary* base once (`lea esi,[ecx-0x10]`) and indexes
forward off it. That is not a scheduling tie-break: it happens because the
reference source calls a helper declared on the primary base, so the adjustment
is a real subexpression with two uses. Spelling the helper's body inline at the
call site removes it, and no permutation of the inlined form gets it back.
Write the wrapper as an inline member of the base that declares it
(`DieModule::isDieApplicable` calling `getDieModuleData()` and `getObject()`),
then call it unqualified. Same instruction count either way, so the size is no
clue -- look at whether displacements off the entry register are negative.

## `delete p` shape reads the type's completeness

Null check + `push 1` + call through vtable slot 0 = complete polymorphic
type (deleting destructor). Plain `operator delete` call = incomplete type.
Complete the class (with virtual dtor) or keep it forward-declared to match.

## A vtable slot belongs to the class that DECLARES the virtual

Reordering a derived header cannot move a base-declared slot. Reference base
classes often carry slots BFME lacks (SubsystemInterface adds six;
MemoryPoolObject's pure getObjectMemoryPool adds one) — one wrong base slot
count shifts every virtual in every derived class. Same-name virtual
overloads lay out in reverse declaration order.

## Temporaries schedule by how visible their type is

An extern, undefined constructor makes a temporary opaque and reorders the
unwind-slot store vs the receiver load; making construction visible (inline
delegation) restores retail's order. When retail inlines part of a string
class, do not derive from StringBase — use a standalone shim class with an
inline `m_text = 0` ctor, a destructor pinned to releaseBuffer, and real ops
via cast to `StringBase<T>*` (the campaignmanagerascii shim is the model).

## Shim headers do not invalidate the build cache

The deps cache keys on content of previously-seen paths; a brand-new shim
compiles nothing ("Compile: 0 of 1 TU(s)") and you diff stale bytes. Change
the source text (any character) to force the recompile, and always read the
build's own compile count before theorising.

## Header edits cost the host-wide full gate — batch them

Any staged header/shim change runs the full gate, serialised host-wide (one
commit queued 44 minutes). Per-file verifies (<8 TUs) take no lock: make every
header edit first, verify each dependent source with `./build.sh`, then pay
the gate once. Never run a per-file verify while a full gate is running.

## Union-merge duplicate row: delete the line by hand, not dedup_csv

The ledgers mix `\r\r\n`, `\r\n` and bare-LF terminators (~94k `\r\r\n` rows)
and `add_match` indexes them by physical line. `tools/dedup_csv.py` rewrites
both files normalised — a ~157,000-line diff that conflicts with every branch
in flight — so ignore the `Fix: dedup_csv` hint for a simple post-merge
duplicate. But do not assume it is ONE line: union merge duplicates CONTIGUOUS
BLOCKS -- six exact-duplicate Open2Handler pins arrived in one rebase. The
procedure that scales and stays inside the rules: drop records whose payload is
byte-identical to an earlier record, keep the first, and do it with
tools/ledger_io.py so terminators survive and nothing else in the file moves.
That is the sanctioned programmatic middle between "never hand-edit the ledger"
and "do not run dedup_csv here": one row per duplicate, no normalisation.
Verify with check_csv and pin_consistency before pushing. Union merge can also silently
drop pins during a rebase; check `git status` before pushing.

## Comment lines that start with a mangled name are parsed as claims

find_declared_unmatched.py reads any line starting `// ?` as the next
definition's declared symbol — a wrapped prose comment then fails the claims
gate on an unrelated function. Write names in prose form
(`ControlBar::findNonConstCommandSet`) or keep them off the line start.

## Convert families, not functions

Normalise bodies (zero rel32 operands and image-address immediates), hash
against converted rows AND against other naked rows: ICF-folded twins convert
by substituting the one class name that reaches the mangled symbol;
constructors differing only in vtable address are one reconstruction written
N times. Each landed conversion is a model for whatever still matches it.

## Count the blockers before starting, and stop at single digits

A big function's cost is its least-known callee: count unresolved call
targets against functions.csv/symbols.csv first (GameEngine::init: ~50
independent naming problems). Read the disassembly before building — a bare
`ret` against claimed arguments, or provably dead code retail kept, kills a
candidate in one read. When a body stalls within single digits of exact with
every instruction present, the residue is retail's TU structure (what the
inliner saw), not a spelling — record it and move on.
One exception, and screen for it before you give up: a callee DEFINED later in
the same TU can inline into an earlier caller where retail emits a call.
TeamPrototype::hasAnyBuildFacility failed while three structurally identical
sibling walks passed, because the inliner declined their callees and took that
one. Declare the callee on a view class -- declared, never defined -- so the
call survives, then alias that spelling at the ILT address. The screen costs one
build: list the callees defined in the same TU and rebuild -- and go one level
deeper than your own body: for each body RETAIL inlines into yours, screen ITS
callees for in-TU definitions too. Retail inlines the whole
TeamPrototype::teamAboutToBeDeleted walk into the TeamFactory one, and at that
depth MSVC also took Team::removeOverrideTeamRelationship, defined in the same
TU, where retail still calls it; one view fixed both sites. In
TeamPrototype::updateState both candidates were declined and the existing pins
resolved unchanged, so the screen is cheap even when it finds nothing.

## Layout facts you can read straight off the bytes

Element size from the `sar`/`shl` pair or a reciprocal-multiply magic
constant; POD-ness from memmove vs an element-wise loop; funclet count = EH-
protected temporaries; an untouched gap between stored offsets is still a
member (declare it, do not initialise it). A raw address literal is honest
where a name would be invented: `(void (*)(MultiIniFieldParse &))0x0043ABC0`
emits the same push as an unattested name without asserting one.

## W3DRopeDraw::buildSegments: two real drifts, then the shim's STL stops it

Worked as the first test of the `callers_of.py --files` queue: the 587-byte dump at
0x0075A990 asserts in `W3DRopeDraw.cpp` and its sole caller
`W3DRopeDraw::doDrawModule` lives there too, so the name had to be one of that
file's eight unmatched functions. `buildSegments` compiled to 602 bytes against the
587 wanted, which is close enough to work. Two drifts came out of it:

- **`NEW Line3DClass(...)` should be `::new Line3DClass(...)`.** Retail calls the
  global `??2@YAPAXI@Z` at both allocation sites. Our `NEW` routes through the W3D
  memory pool, which is what leaves `?allocateFromW3DMemPool@@YAPAXPAXH@Z` and
  `?getClassMemoryPool@Line3DClass@@CAPAXXZ` unresolved. Fixing it took the body
  from 602 bytes to exactly 587.
- **The leading `m_segments.clear()` is an `erase(begin(), end())`.** With `clear()`
  the helper call takes four pushed arguments; retail pushes five. Switching to
  `erase` matched the argument count and the `push edi`, and moved the first
  difference from +0x1A to +0x21.

It still does not land, and the reason is worth writing down because it is not this
function's fault. What is left is a single CSE decision:

    target: mov eax,[esi+0x14]                 push edx / push ecx / push eax / push eax
    ours:   mov edx,[esi+0x14] / mov eax,...   push edi / push ecx / push edx / push eax

Same five values in the same order. Retail reads `_M_finish` once and pushes the
register twice; we read it twice into two registers. That is `vector::erase` doing
`copy(last, _M_finish, first)` where `last` and `_M_finish` are the same read - and
whether they get folded is decided inside the STL header, not here. Hoisting `end()`
into a local changes nothing and `resize(0)` is worse (567 bytes).

So the finding is that **the shim's `vector` differs from BFME's**: our `clear()`
lowers to a four-argument helper where theirs takes five. The three-byte offset from
that one extra `mov` never re-syncs, so 172 of 184 instructions read as different
even though the total size is exactly right. Do not chase the tail of this diff -
size agreement plus a cascade from instruction one means look at the container.

Reverted rather than committed: both edits are almost certainly correct, but the
body does not byte-verify, and changing unverified C++ on inference alone puts a
wrong guess where the next agent will read it as fact.

## A shared shim header is not the place for a member declaration

`ArchiveFileSystem.cpp` did not compile for twelve hours, and the cause is worth
generalising because the change that broke it looked completely innocuous: two
copy constructors were converted to real C++, and their declarations were added
to `reference/shims/archivefilesystem_nosubsystem/Common/ArchiveFileSystem.h`.

Declaring a copy constructor suppresses the **implicit default constructor**, and
`ArchivedDirectoryInfoMap` default-constructs its values. So a TU that merely
*included* the header stopped compiling:

    ArchiveFileSystem.cpp(204) : error C2512: 'ArchivedDirectoryInfo' :
        no appropriate default constructor available

There is a second effect that is easy to miss and does not go away by adding a
default constructor back. With the copy constructor visible in the shared header,
MSVC stops inlining `pair`'s copy constructor in the including TU: retail's
`_Construct` copies the two members individually (`AsciiString` copy ctor, then
`ArchivedDirectoryInfo` copy ctor at `+4`), while ours emits one out-of-line
`pair` copy constructor call. Restoring the default constructor got the TU
compiling and still left that row failing.

**Both effects disappear if the declaration lives in the TU that needs it.**
Guard-suppress the shim and spell the class locally:

    #define __ARCHIVEFILESYSTEM_H_
    #include "Common/AsciiString.h"
    ...
    class ArchivedDirectoryInfo
    {
    public:
        ArchivedDirectoryInfo(const ArchivedDirectoryInfo &);
        ...
    };

The conversions are then kept exactly as they were and the including TU is
untouched. All three verify 18/18.

The general rule: a shim header is compiled into every TU that includes it, so any
change to a class in one is a change to all of them. Prefer TU-local modelling for
anything that only one translation unit actually needs - which is the same advice
that already applies to member offsets and enum widths.

### Two failure modes that hide everything else

A red gate is not always a DIR32 problem, and both of these silence it completely:

- **A TU that will not compile** stops the gate at the compile phase, so DIR32
  never runs. Twelve hours of commits landed behind that wall. When the compile is
  fixed, the DIR32 failures that appear are usually *not* new - check which objects
  emit the symbol (`grep -rl '_$E2' build/match/*.obj`) before assuming you caused
  it.
- **A Windows extended-length path.** `Path.resolve()` returns a `\?\` prefix for
  deep paths on Python 3.14 and `ROOT` never has one, so `relative_to` threw in
  `verify_string_refs` - *after* 157,929 functions had already verified. Fixed by
  `tools/build.py`'s `resolved()` helper.

And the payoff for having the gate back: it immediately caught
`RegistryGetUnicodeString.cpp` calling `RegOpenKeyExA` where retail calls
`RegOpenKeyExW`, seen as one symbol resolving to both the A slot (0x01359148) and
the W slot (0x0135914C). The body byte-matches either way because relocation sites
are masked, so no other check in the gate could ever have seen it. **When a symbol
reports two bases four bytes apart in the IAT, suspect A-versus-W before you
suspect a duplicate import.**

## The EH-temporary transposition: one phenomenon, many near-miss bodies

Several bodies in the pairing queue come back at **exactly the right size** with only
four to six differing instructions, and every one of them is the same two
instructions swapped:

    target: 89 64 24 08   mov [esp+8], esp      ours: 8b cc         mov ecx, esp
            8b cc         mov ecx, esp                89 64 24 08   mov [esp+8], esp

Confirmed instances so far, all `--source`-paired against real C++ that is
otherwise byte-identical:

    435B  0x004D7740  PopupJoinGameSystem     (2 sites, 4 diffs)
    446B  0x004C8910  GameInfoWindowInit      (2 sites, 4 diffs)
    737B  0x004DEB70  PopupReplaySystem       (3 sites, 6 diffs)

The construct is always a `UnicodeString` passed **by value** -
`GadgetStaticTextSetText(GameWindow *, UnicodeString)` - so MSVC copy-constructs the
argument on the stack, sets `ecx` to its address, and records that address in a
frame slot so the unwind funclet can destroy it if the call throws. Retail records
first and loads `ecx` second; we do it the other way round. Both orderings are
correct, the byte count is identical, and the rest of the body matches exactly.

Levers already tried, none of which move it:

- `UnicodeString.TheEmptyString` versus `UnicodeString::TheEmptyString`. Note that
  MSVC 7.1 accepts the dot form on a type name and generates identical code, so
  that spelling in the tree is not a drift even though it looks like one.
- The callee signature: ZH declares the parameter by value and so do we, so this is
  not a by-value-versus-const-reference mismatch.

Do not spend a session picking at one of these bodies. They are worth attacking as
a family, and the way in is a TU whose flags differ, not a source rewrite - a
matched body containing the *same* construct would prove which flag flips the
order. Until then, treat "right size, four diffs, `89 64 24` against `8b cc`" as a
known-unfixed classification and move to the next candidate.

**A 93-byte specimen of the same family**, found 2026-08-16 and worth starting
from because everything else about it is settled:
`?sendDisconnectChat@Network@@UAEXVUnicodeString@@@Z` at `0x006824C0`. The whole
body is `m_conMgr->sendDisconnectChat(text)` with `m_conMgr` at `[this+0x08]`,
and it reproduces byte for byte except the same two adjacent instructions:

    retail    89 64 24 08   mov [esp+8], esp
              8b cc         mov ecx, esp
    compiled  8b cc         mov ecx, esp
              89 64 24 08   mov [esp+8], esp

Same construct as the bigger ones — a class passed **by value** into a call
inside an unwind frame — but with nothing else in the function to look past. The
reconstruction is not in the tree, because a source with no matched row cannot
live under `Code/`; rebuild it from this paragraph and the packet at
`reverse/zh_sweep/packets/006824c0.md`.


## The baseline exe is not entirely compiler output

`CopyProtect::notifyLauncher` at `0x001020D0` will not match, and the reason is not
in our source. The target's branch shape is impossible for a compiler to emit:

    0x0010211F   eb ..      jmp    (where the port emits 75 .. jne)
    0x00102173   eb 00      jmp    to the very next instruction
    0x001021B2   eb 04      jmp    followed by 90 90 90 90

A `jmp` whose displacement is zero, and four `nop` bytes padding the middle of a
body, are what a **hand patch** looks like: someone disarmed the copy-protection
checks in place, keeping every instruction boundary so the file length did not
move. `baselines/bfme1/workshop-vanilla-1.03` is a redistributable, not a pressed
retail image, and this is where that shows.

The damage is narrow. The other three `CopyProtection.cpp` bodies --
`isLauncherRunning`, `checkForMessage` and `shutdown` -- byte-match from clean C++,
so only the checks that actually gate the launcher were touched. But the rule
generalises: when a diff is *only* conditional branches turning unconditional, or
shows `nop` runs inside a body, suspect the binary before rewriting the source. No
amount of C++ reproduces a patch.


## Triaging a red DIR32 gate: the count points, the structure proves

`DIR32 consistency: FAIL n NEW inconsistent symbol(s)` names the symbol and its
two bases and stops. `tools/dir32.py <symbol>` lists the rows resolving it to
each base, and one row against twenty says which row to doubt -- but that is a
pointer, not a proof: a majority can be an ICF artifact, and a 1-vs-1 split
says nothing at all. Structure proves it. The six symbols red on 2026-08-16
were **all six wrong rows**, none a second legitimate base, and each fell to
one of these reads.

**Offsets fix the class.** `??0BehaviorModule` at 0x005F84E0 stored its extra
vptrs at +0x14/+0x18 over a 0x14-byte base; BehaviorModule's are at
+0x00/+0x0C/+0x10, where twenty derived destructors restore
0x0109CB5C/0x0109CA98/0x0109CBAC on their way out. A base sub-object is not
0x0C bytes in one body and 0x14 in another, so the body is another class's.
That TU had already written the gap down as two pad dwords to make the offsets
fit -- padding invented to seat a body IS the finding. Which vtable is whose
comes free: MEMORY_POOL_GLUE puts the pool name straight after the table, and
"BehaviorModule" sits at 0x0109CB8C.

**GameEngine::init names a global.** It pushes the subsystem's string literal
and then the global's address, so 0x012F0888 is TheExperienceLevelSystem
(literal at 0x00479C3A, push at 0x00479C48) and 0x012F076C is TheScriptEngine.
Same walk as the whitelist's ThePlayerAITypeSet note; it settles "which
singleton is this" in a minute.

**`??_M` names a container's element.** The call carries element size and
destructor together: 0x74 with dtor ILT 0x0041AAD2 is ProxyClass, 0x10 with
0x00436AB1 is MixFileCreator::FileInfoStruct. Two ILT thunks are the same
function only if they jump to the same place -- these go to 0x003F6EA0 and
0x0005DBE0 -- so "both bases are odd, therefore both are thunks for one
destructor" was the wrong read of that pair. Check the target, not the parity.

**COMDAT adjacency breaks a 1-vs-1.** Constructor, deleting destructor, vtable
and the member that uses the buffer travel together. 0x006DB100 installs the
vtable three other TUs call `ShareBufferClass<I>`'s, its deleting destructor
(0x006DB1D0, slot 1 of that vtable) is 0xD0 bytes on and Get_Color_Array
0x270 further; a body in the wrong run is not the one you named.

Byte verification sees none of this: build.py copies DIR32 slots from retail,
so a body under the wrong name matches at every reference site. And because
`.githooks/pre-commit` forces the full gate on any staged `*.h` or
`reference/shims/*`, a red DIR32 blocks **every** header and shim change in the
tree, not just the guilty file -- fixing one of these rows unblocks a category.


## A `pinharvest` row in symbols.csv is a candidate, not an address

`reverse/symbols.csv` is additive by design: each pinned address becomes one more
candidate for the resolver, which tries them in order and keeps the first that
reproduces retail's bytes. That is what makes incremental-link thunks work, and
it is also why a pin cannot be read as *the* address of anything.

Measured on 2026-08-16: of the 1,361 pins whose notes say `pinharvest` and whose
name also has a matched body in `functions.csv`, **1,193 do not reach that body**
— they resolve through their thunk to some entirely different function. Most are
STL template instantiations, where one mangled name genuinely fits code at
dozens of addresses and the harvest picked all of them.

That is harmless for byte-matching, because a wrong candidate simply fails to
reproduce the target and the next one is tried. It is not harmless for
*reasoning*. `BoneFXDamage::friend_newModuleInstance` at `0x0011E800` is the
case that costs an afternoon:

- The ModuleFactory registration block pairs the literal `"BoneFXDamage"` with
  `0x0011E800`, which is byte-true evidence.
- The name currently sits on `0x0011E2D0` as one of three aliases, and the same
  block registers `0x0011E2D0` as `LockWeaponCreate`.
- The factory calls its constructor through ILT `0x00005B19`, which reaches
  `0x00250740`.
- `functions.csv` puts `??0BoneFXDamage@@…` at `0x0024FC20`.
- `symbols.csv` pins six more thunks for that same constructor, one of which
  reaches `0x0024F860`.

Three mutually inconsistent answers for one constructor, and the factory cannot
land until one of them is proven. **Before spending a name on the strength of a
callee, resolve the thunk and check it against the ledger's own body** — and if
they disagree, say so rather than picking the convenient one.

### The guard that checks this for you

`tools/pin_consistency.py` enforces one name, one function: every address pinned
to a name must follow its thunk chain to a body byte-equal to every other body
that name pins (templates handled by rebasing rel32 slots, not by excluding
them). Landing a pin:

    python3 tools/pin_consistency.py --symbol <mangled>   # chains, extents, owners
    python3 tools/pin_consistency.py --check              # what the hooks run, 1.6s

It runs in the commit hook whenever `symbols.csv` or `functions.csv` is staged,
in the push hook on every push, and in the full gate. Both hooks used to run
only *scoped* builds and the full gate exited before ever reaching it, so until
2026-08-18 a wrong pin could reach origin without any check looking at it.

`reverse/pin_consistency_baseline.csv` is the backlog of 410 known-bad pin sets,
each with its evidence, and **it is only allowed to shrink** — that is enforced
now, not merely requested. Its preamble explains what a line means and how to
resolve one; start there rather than here.

Two things it does *not* cover, both real: names that pin a single address
(70,144 of 70,633 — the 0x14867 "one address, four names" shape is invisible to
it), and the `functions.csv` half of the resolver's candidate list, which
`--candidates` reports and which currently holds **114 more violations**.

Finally, the trap: a session landed all 47 `--clear-cut` verdicts and the gate
turned 111 byte-matched rows red, 110 reaching a pin it had just deleted. **A
byte-verified caller outranks a byte-verified identity row.** `--clear-cut`
emits candidates, not verdicts; retract in small batches, full-gate each one.


## Retail's string payload is at m_data+8, and this tree inlines m_data+4

`AsciiString::str()` and `UnicodeString::str()` inline to a fixed idiom -- test
the data pointer, add the header size, or fall back to the shared empty string:

    85 c0        test eax, eax
    74 05        je   +5
    83 c0 08     add  eax, 8
    eb 05        jmp  +5
    b8 8b 38 07 01   mov eax, 0x0107388B

Counting that idiom across retail `.text` gives **808 sites, every one of them
`add eax,8`**, split by which empty string they fall back to: 734 use
`0x0107388B` (a `char`) and 74 use `0x0107388C` (a `WideChar`). So both string
classes agree, and **retail never emits `add eax,4`**.

Counting the same idiom across this repo's built objects gives 87 sites at `+4`.

The reason is visible in the vendored header. `AsciiStringData` is

```c
#if defined(_DEBUG) || defined(_INTERNAL)
        const char* m_debugptr;
#endif
        unsigned short  m_refCount;
        unsigned short  m_numCharsAllocated;
```

Four bytes with the pointer compiled out, eight with it in — and eight is what
retail uses. Either the shipped build defined `_INTERNAL`, or BFME widened the
two counters; the bytes cannot tell those apart, but they are emphatic that the
header is eight bytes wide.

**This is safe to fix.** A matched row cannot contain `add eax,4`, because retail
has no such site, so all 87 are in bodies nobody has landed yet. Correcting it
should unlock rather than break — the tree already carries BFME overrides in
`Code/GameEngine/Include/Common/` (CRC.h, Snapshot.h, Recorder.h, Module.h) and
an `AsciiString.h` / `UnicodeString.h` override is the same shape of change.
Budget a full gate per attempt, and expect the fallout to be in *unmatched*
bodies that suddenly compile differently rather than in matched ones.

### What it costs, measured

Restoring the eight bytes is a two-file shim in
`reference/shims/sweep/Common/` and it works: `ScriptActions.cpp`,
`GameInfo.cpp` and `MapUtil.cpp` all move from `+4` to `+8` with their 164
matched rows still verifying, and `LANAPI::RequestAccept` loses the string
offset from its diff list. Two things bite anyway, and the second is why it is
not landed yet.

**The define must not reach `Common/Debug.h`.** It reads `_INTERNAL` too, and
letting it see the define turns `DEBUG_ASSERTCRASH` back on — which grew
`LANAPI::removePlayer` past its matched extent. Hoist the vendored header's own
includes above the `#define` and it goes away.

**The dependency cache will tell you the tree is fine when it is not.** Adding a
header *earlier on the search path* does not change any recorded header list, so
`./build.sh` reuses objects built against the old one — 324 of them, still dated
13 August. The full gate passed on those. Delete the affected objects and rebuild
before believing any include-path change.

Once they really do rebuild, the bill arrives: **403 ledger rows in those 135
sources are `uw_*` funclets anchored on compiler-local `$L` labels**
(`object-symbol=$L78143` and friends). Recompiling renumbers those labels and
every one of them stops resolving with `symbol not found in object`. So this
change is not a header edit — it is a header edit plus a 403-row re-anchoring,
and it wants to be one piece of work rather than a surprise inside somebody
else's build.

## MSVC has a private calling convention, and it decides which functions share a file

`drawStaticTextText` at `0x00796BA0` is entered with its first argument in
**EAX**. The callee opens

```
sub esp,0x2c / push esi / push edi / mov edi,eax
```

and its caller at `0x00796FAF` sets up

```
push outline / push color / mov eax,esi / call ... / add esp,8
```

Two stack arguments, one register argument, and an `add esp,8` that does not
account for the third. This is not `__fastcall`, which would use ECX and EDX,
and it is not anything that can be written on a declaration. It is MSVC's own
convention for a `static` function whose every call site the compiler can see,
and **this toolchain reproduces it exactly** — `mov edi,eax` appeared in the
first compile, unprompted.

The consequence is a rule about file layout, not about bytes: **a file-static
that retail called this way and its callers must be converted in the same
translation unit.** Split them and the caller compiles to `push esi` with
`add esp,0xc`, and the caller is wrong in its last dozen bytes for a reason
nothing inside the caller's own file can fix. Before drawing a work packet for
a body whose calls do not account for all their arguments, find the callee and
check whether it takes one in a register.

### And the inverse, which is this lane's hazard

Merging a body INTO the TU that defines its callee turns the same mechanism
against you. `ScreenBWFilter::init` came out three bytes short of 91 with every
offset, constant and call already right: `getChipset` is defined in
W3DShaderManager.cpp, MSVC reached it with the private convention, concluded
ECX survives the call, and kept the shader-handle address there -- where retail
has to park it in ESI and pay the push/pop. Nothing in the body's own text says
so; the tell is a caller that is SHORTER than retail by exactly a
callee-saved-register save/restore, with a value live across a call to a static
defined in the same file.

Fix: declare the callee on a view class -- declared, never defined -- so the
call takes the ordinary convention, and pin that spelling at the ILT the real
name already uses. Same one-line screen either way: before merging, list the
callees your body makes that this destination also DEFINES.

### What that does not buy you

Both of these bodies then stalled on differences below the source level, and
they are worth recognising on sight because no amount of rewriting moves them.

**A SIB base/index inversion.** `W3DGadgetStaticTextImageDraw` came out 237 of
238 bytes. The one difference: retail computes `end.x` as `8d 1c 08`
(`lea ebx,[eax+ecx]`, base EAX, index ECX) and this toolchain emits `8d 1c 01`
(base ECX, index EAX). Identical operation, identical registers, inverted
encoding. It survived `start.x + size.x`, `size.x + start.x`, a compound `+=`,
inlining the expression into the call argument, swapping the `end.x`/`end.y`
statements, and reordering the `ICoord2D` declarations. `/G6` changed nothing;
`/G7` rewrote the body to 234 bytes.

That instance is still a wall, but the class is not: when one of the two
operands comes from a member of a padded VIEW STRUCT, re-spell that member as
a direct address dereference before parking it. `InGameUI::removeMilitarySubtitle`
came out 154 of 154 with one byte wrong -- retail `8b 04 07` (`mov eax,[edi+eax]`)
against `8b 04 38` -- and reaching the record pointer as
`*(Rec **)((UnsignedByte *)this + 0x818)` instead of `view->militarySubtitle`
encoded it retail's way. Same registers, same operation, same length either way,
and reversing the subscript does nothing (`i[p]` is `p[i]` to the front end).
Both spellings are ordinary tree idiom, so the choice looks free and is not.

**An allocator split.** `drawStaticTextText` came out 344 of 346. Retail spills
`tData` to `[esp+0xc]` and defers `push ebx / push ebp` past the early return,
which leaves a register free later; this toolchain keeps `tData` in EBX and
pays four bytes spilling a temp instead. Same immunity to declaration order.

When the last difference is which register got picked or how an equivalent
encoding was spelled, stop rewriting the source. Log it, and note that the
body, the layout and the convention were all correct — that is the part worth
keeping.

## A work packet's callee pins were matched by name, not followed

`reverse/zh_sweep/packets/0059eb90.md` proposes `AttackNugget::parse` at 98.6%
and lists, under "Callee pins (paste unresolved ones into
reverse/symbols.csv)":

```
??0AttackNugget@@QAE@XZ,0x000047A5 (already in the ledger)
```

`0x000047A5` is an incremental-link thunk. It jumps to `0x0059EB00`. The
ledger's `??0AttackNugget@@QAE@XZ` is at `0x001D6CD0`, reached through a
*different* thunk at `0x00022B42`. The sweep took the name from its Zero Hour
candidate, found that name already in the ledger, and marked the pin resolved
without ever following the thunk it had just printed.

`callee_pins` now asks that question of the decoded address instead, so the
same pin reads `(unpinned: this is the address retail calls; the ledger holds
this name at 0x001D6CD0; reverse/symbols.csv pins it at 0x00022B42)`. Over the
live queue that took 171 markings to 107. The lesson outlives the fix: a
marking says an address is pinned, never that the body is the function its name
promises.

Pasting that pin and building would have produced a byte-exact body under a
name whose constructor it does not call. **Disassemble the ILT target before
trusting a pin that arrives with a name attached**, especially for a body whose
whole shape is generic.

The second check is cheaper and would have caught it alone: look at what the
ledger already claims either side of the address. `0x0059EB90` is bracketed by
`MainMenuSmallScaleDownTransition::update`, `::skip` and `::init` — it is in
`GameWindowTransitionsStyles.cpp`, nowhere near `ObjectCreationList.cpp`.

### Read the data the body points at

The decisive evidence was the field-parse table. The body pushes one address
into `INI::initFromINI`, and at that address are **sixteen zero bytes** — an
empty table. Both reference candidates parse fields: `AttackNugget` has four,
`GameWindowTransitionsHandler::parseWindow` three. A candidate that parses
fields cannot be a body whose table is empty.

Two things make this readable. Absolute operands in the disassembly are **VAs**
while the ledger's `target_rva` is an **RVA**, so a data pointer needs
`- 0x400000` before it maps to a file offset; and the check that proves your
mapping is right is to resolve a string you already know, such as
`parseScreenRect`'s `" ,:=\n\r\t"` at VA `0x010F943C`.

## Two ways to finish a reference TU that locate.py gives up on

`reference/` sources that already own ledger rows are the cheapest lane in the
tree: the source is known-good, the compile flags are known-good, and anything
still unmatched in them is a body somebody has already proved this toolchain can
produce. `vertmaterial.cpp` went from 19 rows to 21 and `mapper.cpp` from 23 to
30 in one sitting, without a line of new C++.

### Find them by size, not by bytes

`locate.py` places a function by masked byte-scan, and it needs a
relocation-free run long enough to be unique. A body dense with pointer stores —
a constructor, a mapper `Apply` — has none, so it comes back **unlocated** even
though the function is right there in the image.

What it prints for those is the compiled **size**. Take the address span the TU
already owns from its landed rows, list every unclaimed dump in that span, and
match on size:

- `??0VertexMaterialClass@@QAE@XZ` compiled to 279 bytes; exactly one unclaimed
  279-byte dump in the span; exact on the first `explain_mismatch`.
- `??1VertexMaterialClass@@UAE@XZ`, 129 bytes, likewise.
- `?Apply@GridTextureMapperClass@@UAEXH@Z`, 863 bytes, likewise.

A size match is a *candidate*, not a result — the 274-byte candidate for
`Parse_W3dVertexMaterialStruct` disagreed at its first byte. It costs one
`explain_mismatch` call to find out.

### When several names match one address, ask the vtable

The same pass over `mapper.cpp` produced 32 more "exact" pairs that are worth
nothing on their own: **four** mapper classes compile `Apply` to the same 860
bytes, so four names matched each of eight addresses. Bytes cannot break that
tie — the bodies are identical, that is what folding means.

One slot away, the tie breaks completely:

1. Scan `.rdata` for the target address **as a VA** (`rva + 0x400000`). Each of
   the eight appeared in exactly **one** vtable slot.
2. Read the rest of that vtable and look every entry up in the ledger. Six of
   the eight held an already-named `Clone@X` — and `Clone` is class-specific
   because it constructs its own class, so the vtable holding `Clone@X` holds
   `Apply@X`.

That named six bodies, 5,160 bytes, on evidence that has nothing to do with the
matching bytes.

**Do not finish the job by elimination.** The last two were the last of four in
each group and elimination would have named them. It was not taken: elimination
is only as strong as the claim that the group is closed, and the slot that
looked like their `Clone` holds a 44-byte dump when every other `Grid*` `Clone`
in the family is 85 — so the window was misaligned and the "obvious" reading was
wrong. Anything whose only argument is *what else could it be* is a guess.

## The unwind-record transposition: a two-byte wall this toolchain cannot cross

Two unrelated functions, in unrelated subsystems, converted hours apart, came
out the correct size with every offset right and stopped on the identical
difference:

```
retail   lea eax,[esp+0x1c]   mov [esp+0x18],esp   mov ecx,esp
ours     lea eax,[esp+0x1c]   mov ecx,esp          mov [esp+0x18],esp
```

`mov [esp+N], esp` is MSVC recording the address of a **by-value class argument**
so the unwind funclet can destroy it. Retail writes that record *before* setting
up the constructor's `this`; this toolchain writes it *after*. Same two
instructions, same slots, opposite order.

- `?parseOCL@@YAXPAVINI@@PAX1PBX@Z` at `0x00201770` — 116 of 118 bytes.
- `?setPlayerName@EstablishConnectionsMenu@@QAEXHVUnicodeString@@@Z` at
  `0x004B2D10` — 135 of 137.

Between them it survived `/G5`, `/G6`, `/O1`, `/O2 /Oi`, `/Ox`, `-Os`, `-Ot`,
`-Oy-`, `-Gy`, `/EHa`, `/EHs`, `/EHac`, an inline versus declared-only
destructor, and replacing the implicit conversion with an explicit temporary.

**Recognise it and stop.** The signature is: correct compiled size, every
member offset and vtable slot already proven right, and the only diff a pair of
adjacent `esp` moves around a class argument passed by value. This is a compiler
*build* difference, not a port error — there is one cl.exe in
`build/toolchains/vs2003` and no second one to try. Any body that passes a class
by value to a function, where that class has a non-trivial destructor, is
currently two bytes out of reach.

Log it with everything the attempt did prove. `setPlayerName` established that
`m_playerNameControlNames` is a file-scope array and not a member — retail
indexes it as `mov ecx,[eax*4 + 0x012B66F8]` and never touches `this` — and that
`winGetWindowFromId` is `GameWindowManager` vtable slot `+0xDC`. Both of those
had to be right before the transposition was the only thing left standing, and
both are worth as much as the landing would have been.

- The `Snapshot::xfer` seeder family (`mov al,1` + a slot-ten call, 198 dumps)
  yields to a *parser*, not to eyeballing: decode each dump into (member call |
  sub-object hand-over | __cdecl helper | guard) and emit the TU from that IR.
  139 bodies landed byte-exact first try this way, in four passes, each pass
  adding one rule. The rule that paid most was treating a deferred `add esp,8`
  as scheduling noise rather than structure.

- A `// cl:` line REPLACES the flag list, it does not add to it. Two vector
  destructor TUs prove the cost: `-GX` gives retail's `cmp eax,0x80` dispatch
  between operator delete and the node allocator, while `/DNDEBUG /MD /EHsc`
  links the DLL CRT and routes the deallocation through an imported operator
  delete instead -- same C++, 40 bytes apart. If an STLport body is right
  except at its allocator call, suspect the flag line before the source.

- MSVC emits `??_G` (the scalar deleting destructor the vtable actually points
  at) ONLY alongside the vtable, and the vtable only where something
  instantiates the class. Declaring the virtual destructor does not emit it;
  neither does adding an inline virtual. A DEFINED CONSTRUCTOR does. Mark that
  constructor `// ??0X@@QAE@XZ present-unmatched` -- the commit hook only binds
  a marker that starts `// ?` and carries a real MANGLED name, so a readable
  `// X::X present-unmatched` is silently ignored and the commit is refused.

- When a data member is the RECEIVER of a call, bind it once as a local
  reference (`Thing &t = m_thing; t.f(x);`). Spelled `m_thing.f(x)` MSVC keeps
  `this` in the register and reads `this+K+field`; retail keeps the MEMBER's
  address and reads `+field`, while still folding the first read back onto ecx.
  It also orders `add ecx,K` before the argument push instead of after. Two
  unrelated families needed exactly this on the same day.

## Two STLport knobs a merged container body usually needs

Both are cl-line changes, so neither costs a full-tree gate, and both recompile
the TU so the byte gate re-verifies every row in it.

**The node allocator.** `PreRTS.h` and `Common/STLTypedefs.h` both force
`_STLP_USE_NEWALLOC`, which flattens a container node deallocation to a bare
`operator delete`; retail pushes the node SIZE alongside the pointer and calls
`__node_alloc::_M_deallocate` (0x0082E5F0). If a merged body's diff starts at a
container teardown -- `push eax / call / add esp,4` against retail's
`push 0xc / push eax / call / add esp,8` -- add
`/DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc` ahead of the reference
include path. On InGameUI.cpp it cost nothing: all 65 rows already landing there
still verified.

**Two node sizes in one TU.** `BFME_PARTICLE_LIST_NODE_TAIL` pads EVERY
`_List_node` in the TU by 0x20, and a destination can need it for one container
and not another: InGameUI.cpp's `list<SuperweaponInfo*>` copy constructor
allocates a 0x2C head node while its idle-worker lists are plain 12-byte nodes.
The two cannot share `list<>::clear()`. Give the 12-byte one a local node struct
and a local `clear()` spelled the way STLport spells it -- head re-read on every
iteration, `_STL::allocator<Node>().deallocate(p, 1)` for the free -- and it
reproduces retail's reload pattern exactly.

## A donor is unmergeable when its TU compiles the class under a different header

Two TUs can hold bodies for the same class under DIFFERENT layouts on purpose,
and the ledger can have both spellings matched at different addresses. When that
happens the donor cannot be folded, because one TU cannot emit both.

GameWindowFields.cpp is the worked case: 31 of its rows are marked for
GameWindow.cpp, but it compiles against `/Ireference/shims/gamewindow` (the true
BFME layout, m_instData@0x30) while GameWindow.cpp compiles the vendored header
(m_instData@0x2C). Putting the shim on the destination costs three compile
errors and, behind them, four matched rows: BFME changed `winSetNextInLayout`,
`winSetPrevInLayout` and `winSetLayout` from void to Int, and the ledger holds
BOTH `?…@GameWindow@@QAEXPAV1@@Z` (from GameWindow.cpp) and `…QAEHPAV1@@Z` (from
GameWindowFields.cpp) at different addresses. C++ cannot declare two members
differing only in return type, so adopting the shim deletes the void rows. The
merge also gains no file, since the donor keeps 14 rows either way.

Screen for it: compare the two files' `// cl:` include paths before planning a
partial donor, and grep the ledger for the donor's symbols under a second
spelling.

## Reaching a member as a MEMBER or through a local pointer picks the registers

Not a style choice. `view->field` off a hoisted local makes MSVC keep the
MEMBER's address in a register and read small offsets from it; `self->sub.field`
off a padded view struct makes it keep `this` and read `this+K+field`. Retail
picks one, and getting it wrong moves every offset in the body. The lesson
already recorded the receiver-of-a-call direction; this is the same lever for
plain reads, and it is worth one build before concluding anything about a body.
`GameWindow::winSetInstanceData` went from "every offset wrong" to "register
allocation only" on that change alone -- and then stopped there, which is the
honest end of it: retail spills `&m_instData` and holds both saved pointers in
callee-saved registers, this toolchain holds the address instead. Logged
`attempted`, not a dead end.

## A $L funclet row self-heals ONLY if it carries `parent=`

### And a funclet with NO candidate is a diagnostic, not a pin problem

`funclet_candidates` returning nothing for a row that HAS a `parent=` does not
mean the pin is stale -- it means no `$L` body in the parent's COMDAT matches
retail's bytes, so the merged body lays its TEMPORARIES out differently. That
fires before a single byte of the parent is compared, which makes it the
cheapest signal this lane has that a body carrying unwind states is wrong.
`LANAPI::addGame` is the worked case: every pin and offset was right and the
funclet row still refused, because the two `getName()` temporaries were not
being built the way retail builds them. Read it as evidence about the
temporaries and go back to the body.

A row whose `object-symbol=` names a compiler-local label (`$L51425`, `$T294`,
`$SG…`) is pinned to a per-compilation ordinal, and ANY edit to its TU can
renumber it. build.py already handles that -- `funclet_candidates` finds the
body again inside the parent's own COMDAT group (the section that also holds
`__ehhandler$<parent>`) and prints

    $L96540 was renumbered by an edit to this TU; the body is $L96533 in the
    object built now (stale ledger pin, not a byte mismatch)

-- but ONLY when the row's notes carry `parent=<mangled>`. Without it the
lookup returns nothing and the gate stops hard at `symbol not found in object`,
which is what makes such a destination look untouchable. THE FIX IS THE NOTE,
not a new pin: give the row a `parent=` and it never needs re-anchoring again.
`gen-alias` funclet rows are the ones that lack it; `gen-funclet` rows carry it
by construction. Screen a destination before choosing it:

    grep -F ",<destination>," reverse/functions.csv | grep 'object-symbol=[$]' \
      | grep -v 'parent='

Those are the only rows that will stop you. To work out the right `parent=`
(or when the parent's group holds look-alikes and the gate refuses to choose),
two filters, and neither is enough alone.

  BYTES NARROW IT. Compile, then for every `$…` label in the object compare its
  bytes against retail at the row's RVA with relocation sites masked on both
  sides (build.read_object_symbol_bytes returns the relocs). Funclets are 8-25
  bytes and generic, so expect several hits -- lanapi's three rows matched 2,
  10 and 2 candidates.

  THE COMDAT RECORD SETTLES IT. A funclet's section is
  IMAGE_COMDAT_SELECT_ASSOCIATIVE, and the section-definition symbol's aux
  record carries the associated section number at offset 12 with the selection
  byte at 14. Intersect the byte candidates with "associated with the section
  that defines the parent function" and exactly one survives:

      $L50814 -> $L50829   section 206, associated with 205 = RequestChat
      $L51425 -> $L51415   section 236, associated with 235 = addGame

  The parent comes from the row's own `parent=` note where it has one; a
  gen-alias row's prose note ("LANAPI::addGame second getName temporary") names
  it too, and when the association agrees with the prose that is two
  independent lines of evidence rather than adjacency. If neither filter leaves
  one candidate, STOP -- a wrong anchor seats a byte-matching row under an
  invented claim and no gate can see it.

Apply with `add_match.py --replace-existing --notes` (the sanctioned path for
rewriting a row), and write the `parent=` in while you are there so the next
edit heals itself. Where a TU has several such rows the gate cannot pass until
all of them are right, so the first N need `--no-verify` and one `./build.sh`
verifies the set.

## Half the cluster-marker files are naked dumps, and they are not merge work

Measured over all 887 files carrying a `readable body of` marker: **408 are
`__declspec(naked)` / `_emit` dumps and 479 are real C++.** A naked donor cannot
be folded -- the merge would add an `__emit` body to the destination and
`conversion_gate.py` refuses it -- so draining one means CONVERTING it first,
which is a different lane. `merge_cluster.py --list`'s per-destination count is
therefore an upper bound, sometimes a wild one: InGameUI.cpp listed 25 donors of
which 6 were mergeable. Screen a cluster before committing to it:

    grep -rlE "_emit|declspec\(naked\)" <the cluster's donors>

## reverse/symbols.csv duplicates itself on EVERY rebase over your own pins

Not once -- every time. `merge=union` re-applies your commit's appended pins on
top of a master that already has them, so a pin lands twice for each rebase that
crosses it. Check `tools/check_csv.py` after every `pull --rebase`, not just the
first, and repair with the ledger_io drop-exact-duplicate-payload pass described
above rather than `dedup_csv.py`.

## A mixed-ending file turns a one-line edit into a lift accusation

Symptom: you change a comment and `conversion_gate.py` rejects the commit with
"adds a naked/__emit body outside Code/gen_small/: __emit 0x81; (3967 such
lines)". Cause: 13 cluster destinations hold a CRLF `__emit` block inside an
otherwise-LF file — AIPathfind.cpp is 3967 CRLF against 11131 LF, and
OptionsMenu.cpp, GameText.cpp, InGameUI.cpp, ControlBarScheme.cpp,
ActionManager.cpp, Drawable.cpp and GameWindowManagerScript.cpp are the same
shape. Python's `read_text()`/`write_text()` translates on read and writes LF,
so a scripted edit silently rewrites every CRLF line and the diff really does
re-add them. The gate is right; the accusation is not. Rule: script every edit
with `read_bytes().decode("utf-8")` and `write_bytes(s.encode("utf-8"))`, and
check `git diff --stat` after — a whole-file rewrite means line endings, not a
bad edit. Same root cause as the ledger terminator hazard in tools/ledger_io.py.

## An access specifier can make a body unmergeable, and it fails like a compile error

Symptom: the gate says "symbol not found in object" rather than showing a byte
mismatch, so it reads like the callee is missing. Cause: MSVC encodes access in
the mangled name — Q public, I protected, A private — so a member the shim
declares `protected` emits `?name@Class@@IAE...` while the ledger row carries
the public `QAE` spelling. `AIUpdateInterface::setGoalPositionClipped` is
protected in reference/shims/aiupdatelayout/GameLogic/Module/AIUpdate.h and
public in the ledger. No view struct and no alias pin reaches an access
specifier; only a shim-header edit does, which is a wide change and a full-tree
build for one body. Rule: before starting a body, compare the row's access
letter against the shim's declaration. If they disagree, leave the donor and
annotate its marker.

## One agent per checkout, not one agent per cluster

Symptom: two agents merging disjoint clusters in the same working tree, and
whichever commits first silently takes the other's work. Not a conflict -- a
partial commit. Cause: there is one index and one reverse/functions.csv, and
`merge_cluster.py --apply` git-adds both the sources and the ledger. So the
committer's staged set contains the other agent's row repoints without their
sources, and the pre-commit gate only byte-verifies the sources THAT agent
staged, so it passes and leaves the ledger naming a file that does not hold
those bodies. Neither split is available either: commit your paths with the
shared ledger and you land their rows without their source; commit without it
and check_csv fails "source not in git" on your own donor deletions.
Partitioning by cluster is sound ACROSS clones or git worktrees, where each has
its own index and its own ledger; it buys nothing inside one checkout. Rule: one
agent per checkout. Give a second agent `git worktree add` (seed build/ by
hardlink and build/readability/counts.json by COPY -- two trees writing one
cache file is the hazard), or a different clone.
Corollary: authoring-without-applying is a safe way to keep working while
blocked on git ONLY if nobody else can commit your tree. `git commit` takes the
working tree for tracked files, so another agent's commit will sweep in edits
you deliberately left unstaged -- including markers removed in anticipation of
an apply, which leaves bodies that look claimed and are not.

## A fold can delete a compiler-generated symbol another matched row needs

Symptom: the merged body compiles clean and a DIFFERENT function, one you never
touched, fails the gate with "symbol not found in object". Cause: some matched
rows are not hand-written bodies at all -- they are symbols MSVC emits as a side
effect of an expression in the TU. Remove the last such expression and the
symbol stops being emitted and its row dies. Two proven shapes:

  memory-pool placement delete. `newInstance(Upgrade)` is the only pool-new for
  Upgrade in Player.cpp, and it is what makes MSVC emit
  ??3Upgrade@@SAXPAXW4UpgradeMagicEnum@0@@Z -- a matched 12-byte row at
  0x007EFFF0 claimed from Player.cpp. BFME allocates through the class's own
  operator new instead, so a faithful merge emits no newInstance and kills the
  row. Trading a 238-byte row for a 12-byte one is still going backwards.

  But CHECK THE GLUE'S EXPANSION before declining on this one: the rule is that
  the EXPRESSION disappears, not that retail reaches a different allocator.
  InGameUI::addNamedTimer holds its TU's only newInstance(NamedTimerInfo) and
  retail allocates with a plain `push 0x1c; call ::operator new` -- the shape
  that looks like the blocker. It is not: reference/shims/sweep's
  MEMORY_POOL_GLUE routes its placement operator new to ::operator new,
  MSVC inlines it to exactly that call, and still emits the COMDAT. newInstance
  stayed and all three rows held.

  inline COMDAT. becomingTeamMember's call to areModulesReady is the only one in
  the TU, and the COMDAT copy MSVC emits for that inline is the matched 7-byte
  row ?areModulesReady@Object@@QBE_NXZ at 0x002ED260, also claimed from
  Player.cpp.

Recoverable only if the reference expression can be kept beside the merged body.
It could not be here: the reference inline reads Object+0x295 and byte-matches
retail's standalone body at that address, while retail inlines a read of +0x341
in becomingTeamMember. Both are right -- they are different members, and the
donor's one name for both is doing double duty.

Pre-check before authoring a line, one command -- list the rows claimed from the
destination whose owning class is NOT the destination's, dropping STL noise:

    cls=Player   # destination basename
    grep -F ",Code/.../$cls.cpp," reverse/functions.csv | cut -d, -f1 \
      | grep -v "@${cls}@@" | grep -v "_STL@@" | grep -v '?\$'

The `??2X@@SAPAXI...MagicEnum` and `??3X@@SAXPAX...MagicEnum` hits are pool
new/delete pairs and are the ones that bite: Player.cpp carries five, Team.cpp
eight. Any body whose merge would stop emitting one of them is blocked before
you write anything.

## Two cl-line flags that look like a rewrite and are not

Both are one token on the file's own `// cl:` line -- not a header edit, so
neither costs a full-tree gate, and both recompile the whole TU so the byte gate
re-verifies every matched body in it and cannot hide a regression. That is what
makes them safe to reach for mid-merge.

`/D_STLP_USE_STATIC_LIB` missing makes every STLport call INDIRECT. Without it
STLport declares its exports dllimport, so a map's tree-increment compiles to a
six-byte `ff 15` through a pointer where retail has a five-byte direct `e8`. The
one-byte shift moves the whole tail and an otherwise byte-exact body reads as
unrelated. 565 cl lines in the tree carry the define, so its ABSENCE is the
anomaly -- suspect it whenever a merged body's diff starts at a container call.
A donor that has it merging into a destination that does not is the usual shape.

`/Ireference/shims/asciistringsetoutofline` is the fix when retail CALLS a
string destructor and the TU inlines it. The vendored header defines
releaseBuffer inline, so an AsciiString local's destruction compiles to a null
test, a refcount compare and an indirect dllimport free where retail emits a
plain out-of-line call. Three TUs already use this shim. Unrelated to the
m_data+4/+8 payload question, which stays parked.

## BFME's KindOfType is four entries longer than the reference's, past index 41

Two unrelated files agree, which is why this is worth propagating where the
individual readings were not:

    InGameUI::evaluateSoloNexus   MOB_NEXUS 46, IGNORED_IN_GUI 47   (ref 42, 43)
    PartitionFilterRepulsor::allow            INERT 0x58            (ref 0x54)

KINDOF_STRUCTURE is 7 in both, so the four extra entries are not at the front.

CORRECTION TO WHAT THIS ENTRY FIRST SAID. I wrote that a body passing a
reference constant "still byte-matches, because the number is an immediate".
That is backwards, and it is the error "The gate is blind to NAMES and
authoritative about IMMEDIATES" below was written to stop: `push 0x54` against
retail's `push 0x58` is a byte mismatch, so a MATCHED body proves its own
constants and the exposure is only unconverted bodies and new code. Read that
entry before sizing an alarm from this one.

What this entry is still for is the SHIFT itself: the value is proven, the
naming is not, so write the number and say where it came from rather than
inventing a name for the four entries BFME has and the reference does not.

## A member-order difference does not need the header changed

An initialiser list emits in the CLASS's declaration order, whatever order it is
written in -- so when BFME declares a class's members in a different order than
the reference, the reference constructor stores each argument into the wrong
slot and no list can fix it. Body assignments emit AS WRITTEN, and that is
enough: `PartitionFilterPossibleToAttack`'s constructor lands all 32 bytes from
the body form, vptr store included -- MSVC still sinks the vptr to the position
retail puts it, between the first and second member store. Works for POD
members; a member needing construction still wants the list, and then the order
really is the class's.

## The bytes prove values and offsets, never names

A donor's local enum, its member names and its comments are the ORIGINAL
author's reading. The byte gate validates none of them: a wrong name compiles to
the same instruction as a right one, so a body can be byte-exact and its
vocabulary still be invented. Three instances on one lane, each caught only when
a second body disagreed:

  a donor named the values it tests CMD_FROM_AI; a sibling donor in the same
  cluster named the same value CMD_FROM_SCRIPT, and the reference enum orders
  them PLAYER 0, SCRIPT 1, AI 2. Nothing settles it, so the merged code compares
  against the numbers and asserts no name.

  a donor called the pointer at Player+0x04 "the AI player". That file's own
  matched bodies already place the AI player at Player+0x220. Two fields cannot
  be one field, so the identification is unproven and was not propagated.

  a donor's enum gave LOCO_HOVER 2 and LOCO_WINGS 3. Drawable.cpp's
  calcPhysicsXform is a jump table over the whole range -- the only place the
  enum is visible at once -- and numbers them with the reference's own ordering,
  where 2 and 3 are TREADS and HOVER. Both donors byte-match; only the naming
  disagrees. The constants were renamed BFME_LOCO_APPEARANCE_2/_3 with the
  conflict written out, and the compiled bytes did not move.

Detection is cheap: when two clusters test the same numeric constant on the same
field, check whether their donors agree on the name BEFORE propagating either.
When they disagree, name the thing for what is proven -- the value -- and record
both readings. Renaming to an honest placeholder costs nothing at the gate,
which is the point: if it were expensive, guessing would be tempting.

## "symbol not found in object" has three causes and none is a byte mismatch

The message means the destination is not EMITTING the symbol the row wants. It
never means the bytes are wrong, so do not go reading the disassembly. Three
causes, each with a pre-check that costs one command:

  ACCESS SPECIFIER. MSVC encodes access in the mangled name -- Q public, I
  protected, A private. A member the shim declares protected emits
  ?name@Class@@IAE... where the ledger carries the public QAE spelling. Check
  the row's access letter against the shim's declaration.

  object-symbol NOTE. A row's notes column can pin it to a spelling that is not
  its name, and build.py reads THAT out of the object.
  ?WriteScriptsDataChunk@ScriptList@@...QAPAV1@H@Z carries
  object-symbol=...PBQAV1@H@Z -- PBQAV1@ is what `ScriptList *const []` mangles
  to, the donor's own declaration, where Scripts.h declares `ScriptList *[]` and
  emits QAPAV1@. Different parameter TYPES, not a top-level const the compiler
  would ignore, so the destination cannot produce it without a header change.
  1,662 of 4,402 cluster-donor rows carry one of these notes, so check it:
      grep -F "<symbol>," reverse/functions.csv | grep -o "object-symbol=[^;]*"

  A DELETED COMPILER-GENERATED SYMBOL -- the separate recipe above.

The object-symbol case has two shapes and only one is recoverable. A spelling
the destination COULD emit with the right declaration is a view problem. A
spelling that names a DONOR-PRIVATE symbol is not:
?preloadAssets@ControlBar@@QAEXW4TimeOfDay@@@Z carries
object-symbol=?bfme_preloadAssets_wrapper@ControlBar@@QAEXXZ -- a private
wrapper, and note the arity differs too (retail's body takes no argument). The
destination compiles the real ControlBar, which declares
preloadAssets(TimeOfDay), so it cannot emit a no-argument private wrapper
without a header change. The override is the correct mechanism, not a wart --
it is what lets the donor hold a body the real class cannot express.

## When a reference inline owns a row, and your body needs a different offset

Unmergeable, and it is worth recognising in one read rather than three builds.
The shape: the reference's inline expansion has its OWN matched row, byte-
matching retail's standalone body at some offset, while retail inlines a read of
a DIFFERENT offset into the body you are merging. Both offsets are right -- they
are not the same member, and the donor's single name for both is doing double
duty. Keeping the reference call to preserve the row therefore reads the wrong
field, and dropping it kills the row. You cannot satisfy both, and the standalone
row is the one already proven.
Seen twice: Object::areModulesReady (+0x295 standalone against +0x341 inlined in
becomingTeamMember) and Script::getAction/setAction (+0x28 standalone against
+0x20 inlined in ParseActionDataChunk, two rows at 0x00112980 and 0x00112970).

## Register allocation is sometimes source-controllable, so try once before parking

Two different phenomena get filed as "register allocation" and only one is a
wall. Telling them apart is worth doing because 123 entries in re_attempts.log
cite register allocation, and some of that pool is recoverable.

RECOVERABLE -- a chain that switches register one load too early. On
ControlBar::onPlayerRankChanged the walk switched from eax to ecx ahead of
retail's; routing the local-player fetch through an IN-CLASS accessor on the view
made it reuse eax down the chain exactly as retail does. Same lever as the
scheduling and jump-threading fixes, reaching further than expected.

A WALL -- two registers swapped wholesale. On Path::appendNode retail keeps the
parameter in esi and `this` in edi while the merged TU does the reverse, and the
swap also flips two adjacent stores. Three source shapes (a local view pointer, a
re-evaluated static helper, an inline setter) all produced byte-identical output.

FIRST, RULE OUT THE OTHER CAUSE -- an inlined same-TU callee and a register
tie-break look IDENTICAL in a byte diff: extra register traffic clustered around
a missing call. The tell is a call whose target is not one the body should make.
Screen it before reaching for the accessor: compare the definition line of every
named callee against your body's own line number, and treat anything defined
EARLIER in the TU as an inlining candidate. Getting this backwards costs a cycle
in each direction.

THE ACCESSOR NEEDS A GLOBAL AT THE HEAD OF THE CHAIN. It works by changing how
that global is fetched, which re-seats everything downstream --
ControlBar::onPlayerRankChanged starts at ThePlayerList. On a PURE MEMBER WALK
off `this` there is no global fetch for the extra inline layer to reorder, and
it cannot help: 0x002B6390 has the identical recorded signature and three shapes
(accessor on the middle hop, accessors on both, a reference instead of a
pointer) all produced byte-identical output.

AND CHECK IT IS NOT CSE FIRST. Five 83-byte twins logged as register allocation
were common-subexpression elimination of a member read: retail consumes m_begin
as a memory operand of the span subtraction so nothing holds it, then re-loads
it for the index, while MSVC materialises it into esi once and reuses it --
which then denies esi to `this` and cascades. The registers are the symptom. A
view class does NOT defeat this, even reading the index through a distinct view
type at the same offset, because MSVC folds on the address computation and does
not care that the struct type differs. Only volatile breaks it, at the cost the
existing note records.

So: try the accessor ONCE, and only on a global-headed chain. If the diff is a whole-body register swap rather than
a chain diverging at one load, park it. And a body already parked as
"register-allocation class" with an eax/ecx chain signature is worth one more
look, not a permanent skip.

## Retail rarely caches a global or a member across a call

Binding ThePlayerList to a local cost showSpecialPowerShortcut its match: MSVC
parked the local in ebp where retail loads the global three separate times.
Writing the global out at each use restored the match. The instinct to hoist a
repeated expression into a local is the wrong one here -- spell it out as often
as retail does, and let the compiler decide.

## An extent complaint on an already-matched row is about the body, not the row

Symptom: the build asks you to raise a row's target_size, and the row already
matched from its donor. Do not raise it. The row's extent was proven when the
donor landed; if the merged body now needs more bytes, the merged body is wrong
-- it is reaching past the function retail actually ends. Raising the extent
makes the complaint go away and buries the real cause under a row that now
claims bytes belonging to the next function.

Diagnostic, not a fix: raise the extent LOCALLY to see what the extra bytes are,
read them, then REVERT the extent before fixing the body. The bytes tell you
which construct over-ran -- usually an inlined tail retail calls out of line, or
a destructor the merged shape emits and retail does not.

## Sizing work off re_attempts.log overstates it, in three separate ways

The log is append-only and nobody prunes it, so a body that later lands leaves
its old "abandoned" note behind forever. A grep over it is not a work queue.
Measured on one slice -- entries citing register allocation with an eax/ecx
signature -- the count collapsed at every step:

    61  matching log LINES
    58  distinct symbols        (a symbol can be logged more than once)
    30  that are ledger rows    (the rest are narrative/capstone entries such as
                                 "pool-figures-and-two-more-refuted-pins", or
                                 symbols since renamed or retired)
    18  whose row is still on a dump -- the actionable pool

The other 12 had been converted since their note was written: a 21% false-parked
rate in one slice. Cross-reference before quoting a number off this file or it
overstates by about a fifth.

And do NOT filter on status=matched to find the unconverted ones. All 18 are
matched -- from Code/gen_asm/*.asm, because a dump matches by construction. The
discriminator is the SOURCE PATH, not the status column.

## A by-value string argument needs a VISIBLE copy, not an opaque one

The wall: retail passes AsciiString/UnicodeString by value, and the vendored
header's copy constructor is out of line, so the temporary is opaque and MSVC
schedules the unwind-slot store after the copy-constructor receiver load where
retail stores first. It gates roughly 114 of 511 clean cluster donors, so it is
worth getting right.

The fix is a per-file view, NOT a shim header and NOT a full-tree gate. But the
SHAPE decides it, and the obvious shape is the wrong one. A view with an opaque
copy -- declared, never defined -- removes the inlining and still leaves MSVC
hoisting the receiver's global and vtable across the call. Retail's compiler saw
a VISIBLE copy that delegates to a base constructor which is itself declared and
never defined:

    class BfmeStringArgBase { friend class BfmeAsciiStringArg;
    private: BfmeStringArgBase( const BfmeStringArgBase & ); ~BfmeStringArgBase(); };

    class BfmeAsciiStringArg { public:
        BfmeAsciiStringArg( const AsciiString &that )
        { ((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
              *(const BfmeStringArgBase *)&that); }
        ~BfmeAsciiStringArg();
    private: char *m_text; };

Opaque and visible-delegating are both different from the reference header and
only the second matches. This is "temporaries schedule by how visible their type
is" applied in the right direction -- and the shape is not invented, it is what
the sibling donors' own shims already spell, which is why they match and a
merged body does not.

Cost: a few additive aliases at addresses already pinned under the real string
spellings, each reached through a call so the rel32 proves it. And the cost is
ZERO for any further call site whose callee is virtual, because a view's virtual
signature can change types freely -- one body matched first try with no new pins
at all.

AND THE CONVERSION AT THE CALL SITE MUST BE IMPLICIT. `f(Arg(x))` makes MSVC
materialise the temporary in a NAMED LOCAL and pass its address; `f(x)` builds
it directly in the argument slot, which is what retail does. So the callee has
to be declared under a name of its own rather than as an overload of the real
one -- an overload taking the real string type is an exact match and wins,
leaving the view unused. `LANAPI::SetLocalIP` is the worked case: same bytes
either way up to that point, and the whole prologue and temporary land once the
call reads `bfmeResolveIP(localIP)`.

A WARNING ABOUT THE TU-WIDE STRING SHIMS in a file that carries funclet rows.
`/Ireference/shims/asciistringsetoutofline` fixes an inlined destructor, and in
lanapi.cpp it changes codegen enough that a funclet row on a body you are NOT
editing stops finding a byte-equal candidate in its parent's COMDAT. Check for
`object-symbol=$` rows in the destination before reaching for one.

## "It did not match" is a deferral, not a dead end

Read tools/re_log.py's status doctrine (lines ~40-70) BEFORE recording a
verdict. The distinction it draws is not bookkeeping:

  DEAD_END_STATUSES -- no-match, refuted, identity-suspect, mis-anchored -- are
  findings about the BOUNDARY. Re-serving cannot fix them.
  DEFERRED_STATUSES -- blocked, attempted, abandoned, partial -- are properties
  of the ATTEMPT. Every retail byte needs a C++ equivalent, so "I could not
  match it" can only ever mean "not this session".

Conflating them retired 535 symbols the project cannot finish without. An
SEH-frame, register-allocation, CSE or inlining-depth wall is a deferral: it was
usually measured by an agent working the body SOLO, and the land rate is 19.5%
solo against 46.5% with ten or more siblings landed, so the finding is stale by
construction the moment its file drains.

`partial` is the one to reach for when the attempt produced something -- it banks
the body under reverse/attempts/<rva>.cpp and serves it beside the candidate. The
tool REFUSES partial without --stash and --score, because a row describing a near
miss with no body measures worse than recording nothing.

Corollary for anyone sizing work off the log: `note`, `evidence`, `lever`,
`correction` and unrecognised words are ANNOTATIONS, not verdicts, and an
unrecognised status leaks a candidate rather than burying one. So a grep counts
things the tool does not. Use re_log.is_dead_end(), not text.

## The first build after --apply can look like a pass it never ran

`merge_cluster.py --apply` repoints the ledger rows; it does NOT clear the
donor's `present-unmatched` marker. verify_source_claims reads that stale
annotation and fails BEFORE the byte comparison runs, so the output you get is
about the marker, not the bytes -- and the line it prints,

    byte-verified matched from this file but still carries an unmatched marker
    (stale annotation)

reads like a pass. It is not evidence of a byte match; it only means the row now
names this file while the comment still says otherwise. Only the `Functions:`
line is evidence.

Clear the marker first, then build. Two agents hit this independently, one of
them on three separate folds before spotting it, and one body (Object::setLayer)
did turn out to match once the marker was dropped -- which is the trap: the
message is sometimes right by accident.

## Accessor disagrees with a body: is it a SECOND member or a shifted class?

Two classes now carry two links where the reference carries one -- LANGameInfo
with the accessors on +0x360 and the bodies walking +0x398, Script with the
accessors on +0x28 and the parser using +0x20. The tempting fix is a view that
moves the body onto the accessor's offset: it makes the row match and silently
merges two distinct members, which is a green build hiding a structural error.

There is a cheap mechanical test, and it does not need a view or a build.
Collect the offsets the class's MATCHED TINY ACCESSORS prove -- they are
authoritative about their own offset, being byte-verified -- and look at the
shape of the disagreement:

  * A SHIFTED CLASS shows a RUN of consecutive members displaced by the SAME
    delta. That is a reliable positive. GameWindow: m_status, m_size,
    m_userData and m_instData are every one of them exactly +4 from where the
    vendored class puts them, because BFME has a member at +0x04 the reference
    does not. Four coincidental second members all exactly four bytes apart is
    not credible; one inserted member is.

  * ANYTHING ELSE NEEDS THE LIVENESS TEST, and a gap in the accessor set is
    NOT enough on its own. The question is whether BOTH offsets are live IN
    RETAIL. Two members means retail uses both; one misplaced member means
    retail uses only its own and ours is simply wrong.
    LANGameInfo passes: +0x360 is proven by get/setNext and +0x398 by three
    matched bodies -- removeGame, LookupGameByListOffset and addGame.
    Drawable::getID FAILS it and is the counter-example that matters: retail
    reads +0x100, this tree reads +0x8C, the accessors either side agree
    (getInstanceMatrix +0xD4 and getFullyObscuredByShroud +0x148 are both
    matched from Drawable.cpp at retail's offsets), and +0x100 sits in a gap
    -- so the gap heuristic alone would have called it a second member. It is
    not: NO retail accessor reads +0x8C and nothing else claims it. One member
    declared in the wrong POSITION.

So: a RUN at a constant delta means the class is short and the header is wrong.
Everything else means go and check whether retail uses OUR offset anywhere --
an accessor reading it, or a matched body. If nothing does, our offset is the
error and there is only one member.

Script sits in the middle and should be treated as unresolved: its +0x20 has no
accessor and no matched body, only retail's own bytes in the one function that
cannot land. That is good evidence the offset is real and NOT evidence that
+0x28 and +0x20 are two members rather than one relocated one.

The remaining doubt on the second-member reading is worth stating: an offset is
strongest when a MATCHED row proves it. +0x398 has three (addGame's siblings
removeGame and LookupGameByListOffset among them). Script's +0x20 has none --
only retail's own bytes, read from the target -- because the body that uses it
is the one that cannot land.

## Before adding a shim for a header, check whether the tree OWNS that header

Four separate requests for a new shim in this lane dissolved on an artefact
the repo already had. The last one is the cleanest example, and it
generalises past strings.

CachedFileInputStream::open would not land because BFME's
CompressionManager::decompressData takes a `const void *` source and the
call site emitted the non-const mangling. The apparent fix was a shim
carrying a corrected Compression.h. But
Code/Libraries/Source/Compression/compression.h is OUR copy, byte-identical
to the reference bar one provenance comment, and DataChunk.cpp is the ONLY
file in the tree that includes "Compression.h" -- it was reaching the
reference copy because our directory was not on its include path. Correct
the header we own, put our directory first, done. A shim would have
duplicated a header already in the repo to fix a one-word error in it.

THE TELL, and it is the reusable part: a MATCHED TU carrying a local
workaround for a shared declaration is evidence about the declaration, not
a trick to copy. CompressionManager_decompressData.cpp reproduces retail
byte for byte and has to declare its own `class CompressionManager` with
the const signature to do it. That is retail telling you the shared header
is wrong. Before writing a shim, grep for who else includes the header --
if it is one file, or none, fix the header.

## Read the whole shims directory before asking for a new one

They are named for the TU that motivated them, not for what they do, so the
general one does not look general. I surveyed five AsciiString shims, concluded
none had both the 8-byte header and an out-of-line copy constructor, and asked
for a sixth. `campaignmanagerascii` has both and was already on 71 TUs: it is
StringBase-based, so its 8-byte `Header` comes from `string_base.h` rather than
from a field of its own -- which is why grepping the shims for the ZH
`m_debugptr` marker misses it -- and its copy constructor delegates to
`StringBase<char>::StringBase(const StringBase<char> &)`, declared private in
string_base.h and never defined, so the delegation compiles to a CALL. Same
declared-never-defined mechanism as the by-value view.

Two mechanics when you reach for it:

  `/ICode/Libraries/Source/WWVegas/WWLib` goes LAST on the cl line.
  string_base.h resolves from anywhere on the path, but WWLib ahead of the
  sweep shim shadows headers sweep needs and snmp.h stops compiling.

  Its `compare(const AsciiString &)` is the INLINE length-bounded memcmp retail
  spells; its `operator==` forwards to a StringBase one that is declared and
  never defined, so `a == b` compiles to a call retail does not make. Write
  `a.compare(b) == 0`.

And know the price before taking it: it makes AsciiString's copy constructor
THROWING (an undefined declaration is assumed so), which can put an EH frame on
anything that copy-constructs a class holding one. `SpecialPower.cpp` absorbed
that with all 13 rows intact; `W3DModelDraw.cpp` did not -- see the
`_Construct` / `push_back` pair in re_attempts.log for the two-sided wall.

## Four string levers, four symptoms: pick by which operation retail calls

"Retail calls it, we inline it" has four different string shapes and four
different fixes. They are not interchangeable and reaching for the wrong one
costs a build each time. All four are per-file cl-line or TU-local changes, so
none costs a full-tree gate:

  inlined DESTRUCTOR  -> /Ireference/shims/asciistringsetoutofline   (5 TUs use it)
  inlined COMPARE     -> a TU-local view of retail's eight-byte header; the
                         include-path shims do NOT substitute, because they give
                         the right header size and a strcmp-based compare where
                         retail does a length-bounded memcmp
  inlined CONSTRUCTOR -> /Ireference/shims/campaignmanagerascii      (71 TUs use it)
  inlined str() AT +4     -> /Ireference/shims/asciistring8                (5 TUs use it)
                             when the single wrong instruction is `add eax,4`
                             where retail has `add eax,8`
                         plus /ICode/Libraries/Source/WWVegas/WWLib for string_base.h
  inlined str() at +4 -> /Ireference/shims/asciistring8              (6 TUs use it)

The fourth is the `add eax,4` against retail's `add eax,8` that the m_data+8
section below parks as a tree-wide change. It IS a tree-wide change if you want
all 87 sites at once -- full gate, and 403 funclet rows to re-anchor. But a
SINGLE body stuck on that one instruction does not need any of that: putting
/Ireference/shims/asciistring8 on that file's own cl line gives the eight-byte
header for that TU only, and the file's existing rows re-verify in the same
build. UpgradeCenter::findUpgrade came home that way with sixteen prior rows
unchanged. Reach for it whenever a diff is `83 c0 04` against `83 c0 08` with the
empty-string fallback at 0x0107388B beside it; the parked section is about the
tree, not about your body.

Note asciistringsetoutofline does NOT fix an inlined constructor -- it leaves
that one inline. And campaignmanagerascii works for the same reason the by-value
view does: its constructor is a VISIBLE inline delegating to a StringBase
constructor declared and never defined. Two agents reached that shape from
opposite directions, which is the strongest evidence the tree offers about it.

The same shape rule governs a LOCAL string, not just a by-value argument. This
tree already spells retail's one-dword string as BFMERetailAsciiString in
ControlBar.cpp and elsewhere with a DECLARED-ONLY literal constructor, and that
schedules the unwind-slot store after the receiver load. Make it delegate
visibly to an undefined base and it matches. Those existing call sites are not
scheduling-sensitive, so nothing there is wrong today -- but copy the shape, not
the spelling.

And know this failure signature before it costs you a build: a body with a local
string has an unwind funclet of its own, and changing the local's type makes the
funclet reference the inline destructor MSVC emits. That fails as an UNRESOLVED
RELOCATION -- `e9 00 00 00 00` -- which reads like a broken build and is really a
missing alias for the destructor ILT the funclet jumps to. One additive pin fixes
it. It is not a byte mismatch and there is nothing wrong with the body.

A fourth symptom is NOT a string problem at all: if the residue after the string
construction matches is an extra vptr store (mov dword ptr [esi+4] right after
the vtable store), that is a second vptr the vendored hierarchy carries and BFME
does not. Base and vptr stores come from the CLASS, so no .cpp reaches them, and
initializer order is not the cause -- base-first and member-first are
byte-identical. Revert the shim with the body; a TU-wide compile change that
buys nothing is worse than no change.

## A shared header's vtable can be wrong, but a matched row proves its own slot

BFME's GameClient vtable is not the vendored one: findDrawableByID is slot 11
(+0x2C) where GameClient.h puts it at slot 8 (+0x20), and destroyDrawable is
slot 24 (+0x60) against slot 19 (+0x4C) -- three BFME virtuals ahead of the
first and two more between them. The header already carries three
bfmeVirtualStub slots for a different part of the same table, so the divergence
is known and this part is simply not covered.

Bound the alarm before acting on it. A body that BYTE-MATCHED cannot be
dispatching through the wrong slot: the call encodes the offset, so `ff 50 20`
against retail's `ff 50 2c` is a mismatch and the gate would have refused it.
Every matched row is therefore proof about its own dispatch. The exposure is
UNCONVERTED bodies -- which will hit it as a byte mismatch when someone attempts
them, exactly as intended -- and any new code written against the header.

So this is not a fire to put out; it is a header correction worth doing
deliberately, and a per-file view reaches it meanwhile.

## When a merged body's diff starts at a container teardown, try the node allocator

PreRTS.h and STLTypedefs.h force _STLP_USE_NEWALLOC, which flattens a node
deallocation to a bare `operator delete` where retail pushes the node size and
calls __node_alloc::_M_deallocate. The sanctioned opt-out is per-file and costs
nothing:

    /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc

on the file's own cl line. It recompiles the TU, so every matched row in it
re-verifies -- 65 of them on the first file to use it. Try this before anything
else when a diff opens at a container teardown.

Related trap in the same area: BFME_PARTICLE_LIST_NODE_TAIL pads EVERY
_List_node in a TU by 0x20. If one row in the file needs that padding and
another needs plain 12-byte nodes, they cannot share list<>::clear() -- give the
12-byte one a local node type and a local clear() spelled the way STLport spells
it.

## To correct an allocation size, use a standalone view -- not derive-and-pad

Deriving from the vendored class and padding it to retail's size gets
`push <size>` right and still does not reproduce `new T(...)`. The derived
constructor is inlined, so only the BASE constructor is called, and MSVC will
not reuse that return value as the derived pointer -- it parks the block in an
extra callee-saved register retail does not need.

A STANDALONE view at retail's size, with its constructor DECLARED AND NEVER
DEFINED, has a constructor of its own and matches exactly. Cost is one additive
alias per constructor, at the address already pinned under the real spelling and
reached through a direct call, so the rel32 proves it.

Note this is the same shape as the by-value string argument view and the
campaignmanagerascii constructor: declared-never-defined is what makes MSVC
emit the call retail emits instead of expanding something in its place. Three
different problems, one mechanism.

## symbols.csv is sorted, and its header sorts AFTER a mangled name

Inserting programmatically into reverse/symbols.csv: the header line
`name,address,notes` sorts after any `??0...` symbol, so a naive sorted insert
places the new row ABOVE the header and check_csv rejects the file with "bad
header". Start the scan at index 1 and keep the header pinned at the top.

## A paired #line lets a __LINE__ body move into a shared destination

Retail pushes its own __LINE__ into GameLogicRandomValue and friends, and the
reference file and this port have drifted apart, so a body carrying one appears
unmergeable: a `#line N` to satisfy it would renumber everything BELOW it in a
shared destination. That reasoning is why several donors kept their own TU.

It is wrong. Emit the `#line` for the statement, then a bare `#line N` AFTER it
restoring the physical numbering, and nothing below moves. The presumed FILE
stays as retail has it. TurretAIIdleState::resetIdleScan landed this way;
LifetimeUpdate.cpp and SlowDeathBehavior.cpp each still have one open, and
anything else parked on "a #line would renumber the file" is now foldable.

## Check a donor's remaining ROW COUNT after --apply, not the "kept" line

`--plan` reports a donor with a second destination as kept, which is right when
it has rows left over. It is misleading when the donor's ONLY row is the one you
just moved: the file survives owning ZERO rows and the gate refuses that
outright -- "source presence is not progress".

INI_parseObjectCreationList.cpp is the shape to recognise: it carried TWO
markers for ONE body -- the full mangled spelling naming ini.cpp and a truncated
`?parseObjectCreationList@INI@@` naming INI_stl.cpp -- and both destinations
hold a copy of the function. So the donor looked multi-destination and was not.
After --apply, count the donor's rows:

    grep -c ",<donor>," reverse/functions.csv

Zero means delete the donor rather than leave it.

## A bare `// ??0Class@@` marker binds by PREFIX, so landing one ctor staleens the other

The claims hook matches a marker comment by prefix. Write both a default and a
copy constructor as the bare `// ??0Class@@` and they are the same marker to it,
so landing one leaves the other's marker pointing at a body that is no longer
there. Give the survivor its FULL mangled name.

Related, when a batch refuses: merge_cluster compares declarations only across
the `--only` set, so two donors that declare one member differently will block
an --apply that names both and go through cleanly in two batches -- provided the
destination has already reconciled them.

## The gate is blind to NAMES and authoritative about IMMEDIATES

These are opposite properties of the same check and this lane has confused them
three times, in both directions. Get it right before you size an alarm:

  A NAME is unvalidated. A row's symbol, a member name, an enum spelling, a
  function identity -- all compile to the same instruction whether right or
  wrong. `identity-suspect` findings, mis-anchored rows and reversed enum names
  all live here, and only a second body disagreeing exposes them.

  AN IMMEDIATE IS PROVEN. `isKindOf(KINDOF_INERT)` compiles to `push 0x54`. If
  retail pushes 0x58, the bytes differ and the row does not match. The same goes
  for a vtable slot (`ff 50 20` against `ff 50 2c`), a chipset tier compare, a
  structure offset, a frame size.

So when you find a renumbered enum, a shifted vtable or a changed constant, the
exposure is NEVER the matched bodies -- those are self-proving. It is
    - bodies not yet converted, which will fail as a byte mismatch when someone
      attempts them, exactly as intended, and
    - new code written against the vendored header.
That is a header correction to schedule, not a fire to fight. Say which of the
two you mean when you report one, because "N call sites are testing the wrong
bit" reads as the first and is usually the second.

Worked examples on this lane: BFME's KindOfType has four entries the reference
lacks (MOB_NEXUS 46 against 42, IGNORED_IN_GUI 47 against 43, INERT 0x58 against
0x54, PROJECTILE bit 25 against 22), GameClient's vtable is off by three and five
slots, and DC_GENERIC_PIXEL_SHADER_1_1 is 3 where the header numbers it 9. All
three were reported as tree-wide hazards; all three are bounded the same way.

## BFME ships BOTH module layouts -- a family lever is not a family fact

48 donors carry a module-constructor marker (the first screen said 23 -- it
grepped the full signature and a third of markers name no signature at all, so
it could not see them). Every one
holding a constructor byte-identical to what its destination already spells.
What keeps them apart is the module hierarchy: retail's Module has no
MemoryPoolObject base, so BehaviorModule spans 0x0C and the second vtable store
lands there, while the wide layout puts a fourth vptr at +0x04 and shifts
everything. reference/shims/sweep/Common/Module.h carries the switch as
BFME_MODULE_NO_MPO and thirty-odd files already set it.

Screened one file at a time -- add the define, require the destination's OWN
rows to stay green, then diff with explain_mismatch:
    6 land    (CashHackSpecialPower, GrantUpgradeCreate, OCLSpecialPower,
               BoneFXDamage, SupplyWarehouseCreate, W3DTreeDraw)
   10 turn their destination RED, so their module layout genuinely is the wide
      one (SlowDeathBehavior, WorkerAIUpdate, BoneFXUpdate, BattlePlanUpdate,
      StructureCollapseUpdate, ToppleUpdate, SupplyWarehouseDockUpdate,
      OCLUpdate, GarrisonContain, BridgeBehavior)
    6 miss for unrelated reasons, 3 are genuinely different bodies, 1 has no
      marker pair to consume.

SETTING THIS DEFINE TREE-WIDE WOULD BREAK TEN FILES. The screen is per-file and
cheap; the generalisation is false. Apply the same caution to any switch that
looks like it characterises a family.

CORRECTED: an earlier reading of three misses as "retail stores a FOURTH vtable
the vendored hierarchy has nowhere to put" was wrong, and wrong in an
instructive way. Retail stores four vptrs, at +0x00/+0x0C/+0x10/+0x18; this tree
stores four, at +0x00/+0x04/+0x10/+0x14. Nothing is missing and nothing is
reordered -- the sub-object at +0x00 spans 0x0C in BFME against 0x04 here, eight
bytes of data the vendored BehaviorModule does not declare, and bases two and
four both slide by that eight.

The error came from screening those three WITH the define on. The define lands
base two correctly AND DELETES base four, so three stores showed against
retail's four and read as a missing base -- an artifact of the experiment read
as a fact about retail. DO NOT READ A COUNT DIFFERENCE OFF A RUN WHOSE FLAGS
CHANGE THE COUNT. It surfaced because a fourth family member, invisible until
the marker fix, screens at 2 diffs WITHOUT the define with all four stores
present: one body disagreeing with a three-body conclusion.

The actionable statement is "BehaviorModule is eight bytes bigger", not "find a
missing interface base".

## The `// cl:` line must be the FIRST line of the file

Put an explanatory comment above it and every flag on it is silently dropped --
no error, no warning, and the body then fails for reasons that have nothing to
do with the edit you made. Explanations go BELOW.

## An ordered call sequence names its unnamed members, like a vtable does

W3DRoadBuffer::loadRoads's donor called its seven callees loadRoadsHelper0
through loadRoadsHelper6 -- honest and worth nothing. The DESTINATION's source
calls seven named methods in a fixed order, and four of the seven already
resolved to ledger-named W3DRoadBuffer members at exactly the positions the
source puts them (insertTeeIntersections fourth, insertCurveSegments fifth,
insertCrossTypeJoins sixth, preloadRoadsInVertexAndIndexBuffers seventh). Four
independent agreements in a row fix the other three BY POSITION, and all three
bodies sit inside the class's own address span:

    ?clearAllRoads@W3DRoadBuffer@@QAEXXZ        ILT 0x000336F9 -> 0x00706E60
    ?addMapObjects@W3DRoadBuffer@@IAEXXZ        ILT 0x0002001D -> 0x007100C0
    ?updateCountsAndFlags@W3DRoadBuffer@@IAEXXZ ILT 0x00010B5E -> 0x00705260

Two of the three had been carrying nothing but a d_00xxxxxx dump name. This is
the "ask the vtable" argument pointed at a CALL SEQUENCE: when a body's callee
list is ordered and most of it is already named, the remainder falls out. The
agreements have to be independent and in order to count -- one or two matches
is coincidence.

## Triage a donor WITHOUT applying it

Cheapest screen there is, two compiles: clear the marker in the destination,
require the destination's own rows to stay green, then run
`explain_mismatch --rva/--size/--source`. You get the exact distance without
touching the ledger, so near-misses sort themselves and a body that needs
AUTHORING rather than repointing (its destination has no definition at all)
shows up before you spend anything.

CAUTION: a match prints "OK: bytes match" and NO Disassembly section. Do not
detect a match by counting diff lines -- an ERRORED run also has zero. Match on
the success string.

This screen found the module-constructor 6/10/6/3 split, two bodies sitting one
instruction from home, and a marker asking for authoring rather than a fold.

## The m_data+8 header is cheap PER FILE, even though the tree-wide change is not

The tree-wide correction really does cost a full gate plus a 403-row funclet
re-anchoring, and this file parks it on that basis. But that is the TREE-WIDE
question. A single body stuck on one instruction -- `add eax,4` where retail
inlines str() as `add eax,8` -- can be unstuck today: put
/Ireference/shims/asciistring8 on THAT FILE's own cl line. Five files already
carry it. UpgradeCenter::findUpgrade landed that way with no full gate, no
re-anchoring, and all 16 pre-existing rows in the destination re-verified.

So: park the tree-wide change, but do not read that as parking the bodies. Check
whether your residue is exactly the +4/+8 difference before deferring one.

## A view's constructor may need throw()

Without it MSVC wraps the allocation in an SEH prologue purely to free the block
if the constructor throws, and retail -- which has no unwind funclet there --
does not. Usually this is a couple of bytes. On LocomotorStore::newOverride it
was the difference between an entire prologue and none. Add `throw()` to a view
constructor whose retail caller has no unwind state.

## A vtable slot read off ONE call site is a guess

Three AIUpdateInterface/DozerAIInterface slots move together: getDozerAIInterface
+0x13C against the vendored +0xFC, isIdle +0x180 against +0x13C -- isIdle landing
exactly where the header put getDozerAIInterface, which is what an interface that
GAINED sixteen entries ahead of them looks like, not one that was reordered.
getMostRecentCommand goes the other way, +0x14 against +0x180, and is a different
interface saying the same thing about DozerAIInterface.

Two of the three were assigned backwards on the first attempt and the gate caught
it. The rule is the same one that names members from an ordered call sequence:
one agreement is a guess, and the whole sequence has to line up before you can
claim any of it.

## $L-anchored rows break on ANY codegen change ABOVE them in source order

The 403-row re-anchoring cost is usually quoted against the tree-wide string
header, which makes it read as a cost of BIG changes. It is not. The labels are
assigned across the whole TU during codegen, so a forty-slot view class is
enough to renumber them.

This entry used to say "any added DECLARATION", which named the wrong variable
and was falsified: a plain function-pointer typedef -- no class, no members, no
emitted code -- renumbers them too. The rule is POSITION, not construct. $L
numbering runs across the whole TU in source order, so any codegen change ABOVE
a pinned funclet renumbers it, and that is why a `#line` directive stays free:
it is a contrast, not a coincidence. The useful corollary is the one the old
wording hid -- a view added BELOW every pinned row does not renumber it, so
check where the pins sit before concluding a TU is frozen.

(Aside for anyone reaching a vtable slot through a function pointer: MSVC 7.1
rejects `__thiscall` on a function-pointer type with C4234, so the call has to
be `__fastcall`. That is call-compatible for a no-argument method and has
nothing to do with the renumbering.)

GameSpyInfo::updateStagingRoom is one instruction from home (addStagingRoom is
vtable +0xA0 in BFME against the vendored +0x84, and the by-value copy and its
unwind slot already match). The view that reaches +0xA0 renumbers PeerDefs.cpp's
labels, and uw_00c40e10 / uw_00c40e8a are anchored on them: one fails its byte
compare and the other can no longer be told from two siblings, so the gate
refuses to guess.

COMMENTS ARE FREE; CODE IS NOT. Before adding a view to a TU, check:
    grep -F ",<destination>," reverse/functions.csv | grep -c 'object-symbol=[$]'
and if it is non-zero, re-anchor those rows FIRST.

Re-anchoring is usually just a NOTES fix, and `parent=` alone is not it.
build.py re-finds a renumbered funclet from its parent's __ehhandler group --
that is the "Funclet pins: N row(s) verified past a renumbered $L label" line --
but is_funclet_row() (tools/build.py:920) gates on the notes containing
**gen-funclet**, AND on a parent=. A row with parent= but no gen-funclet never
reaches the healer: it dies with "symbol not found in object: $L<n>", which
reads exactly like a hard wall and is why lanapi.cpp was called frozen for
weeks. It was one word. `gen-alias` and `gen-funclet` are not exclusive -- an
ICF-twin alias claim can also be a $L-pinned funclet, and then the notes must
say both (keep `gen-alias;` leading, check_csv enforces that prefix).

Exactly three rows tree-wide are gen-alias + $L + parent=. lanapi's is fixed;
?a_00bfd4b8@@YAXXZ (UpgradeNamesPlacementCleanup_00BFD4B8.cpp) and
?a_00c52ae0@@YAXXZ (VectorClassArrayPlacementCleanup_00C52AE0.cpp) are latent
the same way. If either destination looks frozen, this is why.

## A vendored class that is too SMALL needs bytes, not a new class

"Retail's frame is 0x70 where this tree's is 0x64, and that is a
class-shape difference, not a field view" is a verdict Player.cpp carried
against disableRadar and enableRadar. The diagnosis was right and the
conclusion was wrong: both land byte-exact, and so does removeRadar.

A local whose class is twelve bytes too small does not need the class
changed. It needs twelve bytes:

    struct BfmeAudioEventStorage
    {
        BfmeAudioEventStorage( const AudioEventRTS &src ) : e(src) { }
        AudioEventRTS e;
        UnsignedByte _bfme_tail[12];
    };

The member sits at offset 0, so its address, constructor and destructor are
unchanged and every call in the body stays what it was; only the frame
grows. THE CONSTRUCTOR IS LOAD-BEARING. Declaring the storage and then
assigning (`BfmeAudioEventStorage x; x.e = src;`) default-constructs and
then assigns, where retail COPY-CONSTRUCTS in one call. Taking the source
by const reference and initialising the member in the initialiser list is
what reproduces retail's single call.

This reaches any body blocked only by a vendored class smaller than BFME's.
It does NOT generalise to the class: retail's addRadar reserves 0x60 where
the other three reserve 0x70, sets its EH frame up in the other order, and
sits at 0x000FB3F0 well away from them at 0x000CC0B0-0x000CC2C0. The twelve
bytes belong to the frame those three share, not to AudioEventRTS
everywhere -- so measure the frame per body rather than padding on faith.

## Screen a whole cluster with ONE build, before applying anything

Repointing a row to find out how close it is costs an apply, a build and a
revert, and leaves the ledger dirty if you die between them. It is
unnecessary. After ONE build of the destination, read each candidate's
symbol straight out of the .obj, mask the relocation sites, and compare
against retail:

    build.read_object_symbol_bytes(obj, symbol, size)  vs
    build.read_target_bytes(rva, size)

Twenty InGameUI candidates ranked in a single build, no applies. It put
addMessageText (64.9%) at the top -- it landed 388/388 -- and correctly
warned off update, which agrees on 19.3% and fails at offset ZERO on an
`and esp,-8` aligned frame nothing in the body explains.

A 100% SCREEN IS NECESSARY, NOT SUFFICIENT. The screen masks relocation
sites, so it cannot see a call that resolves to the WRONG FUNCTION -- the
gate resolves those and will reject what the screen passed.
DataChunkInput::openDataChunk screens at 100% and fails: retail's
`AsciiString("")` calls RVA 0x00102D90, an unidentified gen-dump that reads
[ecx] and compares [m_data+0xC] against its argument -- a `set`, not the
constructor at 0x00888BC0 the tree resolves to. When a 100% screen fails
the build, read the relocation SYMBOLS out of the object and check each
against what retail's call target actually is.

Read the COMPILED SIZE beside the percentage. Once the two sizes differ the
percentage stops moving even as you fix real things, because every byte
after the first divergence is compared against the wrong position. On
addSuperweapon three separate offset fixes each left it at exactly 60.4%
while the loads visibly stopped diverging. Size converging on retail's is
the signal; the percentage is only useful while the sizes match.

## throw() can be made TU-local with an explicit specialisation

A nothrow declaration is often the whole difference between a merged body and
retail -- it is what lets MSVC drop the unwind-state bump around a temporary and
guard it with a liveness flag instead. addGame was 77 diverging instructions
with the throwing declaration and 6 without it.

The declaration usually lives in a SHARED header you must not change:
Code/Libraries/Source/WWVegas/WWLib/string_base.h declares
`int compareNoCase(const StringBase<T> &) const;` and every TU that includes it
would move. Copying the header into a new shim dir works -- that is what
reference/shims/asciistring_downloadmanager/string_base.h is, one word different
from WWLib's -- but you do not need a new file for it:

    template <>
    class StringBase<UnsignedShort>
    {
    public:
        Int compareNoCase( const StringBase<UnsignedShort> &that ) const throw();
    };

An explicit specialisation REPLACES the primary for that one argument, so the
shared declaration every other TU sees is untouched and no shim dir is created.
It is legal after the primary is defined, as long as nothing has yet forced an
implicit instantiation for that argument -- check that first, and declare only
the members this TU actually calls. wchar_t and unsigned short are the same
mangled type (G) under MSVC 7.1's default, so one specialisation covers both.

## Run the object-symbol check BEFORE authoring, not after

A row can carry an object-symbol naming a spelling the destination will NEVER
define, and no amount of correct bytes fixes it.
GameSpyBuddyMessageQueueInterface::createNewMessageQueue looked like a one-diff
allocation-size fix -- 0x74 against the vendored 0x68, which is real -- but its
row carries
object-symbol=?createNewGameResultsInterface@GameResultsInterface@@SAPAV1@XZ.
The two are ICF-folded onto one body at 0x0063E240, build.py reads THAT spelling
out of the object, and the destination does not define it and never will. The
repoint fails "symbol not found in object" the moment it lands.

It is free and it is one grep. Put it first in your screen, ahead of any compile.

## Some rows only need repointing: the destination already compiles them

DX8Wrapper::Set_Shader needed no source change at all -- dx8renderer.cpp already
produced it byte for byte, and the row pointed at boxrobj.cpp only because that
is where it was originally lifted from. INI::parseObjectCreationList was the
same. The marker-clear screen finds these for free: clear the marker, build the
destination, and if it is already green the work is a repoint, not a fold.

## The "$L freeze" was a notes misclassification, not a constraint

build.py has always re-found renumbered funclets from the parent's
`__ehhandler$` group -- that is the "Funclet pins: N row(s) verified past a
renumbered $L label" line, 339 rows on a full gate. It never fired for
lanapi.cpp because is_funclet_row() (tools/build.py:920) gates on the notes
containing **gen-funclet**, and `?a_00c464f8@@YAXXZ`'s notes said **gen-alias**.
Both are true of that row: it is an ICF-twin alias claim AND a $L-pinned funclet
with a parent=. Saying both in the notes lets the pin self-heal like the 20,051
others, and lanapi stopped being frozen.

So a TU is only "frozen" if its $L-pinned row cannot be classified as a funclet.
EXACTLY THREE ROWS TREE-WIDE are gen-alias + $L + parent=:

    ?a_00c464f8@@YAXXZ   lanapi.cpp                                (fixed)
    ?a_00bfd4b8@@YAXXZ   Common/System/UpgradeNamesPlacementCleanup_00BFD4B8.cpp
    ?a_00c52ae0@@YAXXZ   WWVegas/WW3D2/VectorClassArrayPlacementCleanup_00C52AE0.cpp

The other two are latent the same way. If either file is a destination someone
is holding off, that is why -- and the fix is one add_match.py
--replace-existing on the notes, not a re-anchor.

What it bought immediately: lanapi.cpp had no AsciiString shim at all, adding
campaignmanagerascii (with /ICode/Libraries/Source/WWVegas/WWLib LAST for
string_base.h) left all 18 pre-existing rows green and collapsed one body's
residue from ~55 diverging instructions to 2. A re_attempts.log entry recording
"the shim is not free in this TU" had been measuring the misclassification, not
the shim.

## A stripped marker over an unmoved row hides a non-matching body

The worst state a half-finished fold can leave, because the gate reports success
BECAUSE of it. Recovering an agent that died mid-cycle, e92e20fdf carried a
rewritten BFME body into AIStates.cpp, deleted its `present-unmatched` marker,
and repointed only ONE of the two rows. The other body was then: rewritten, no
marker, row still naming the donor. verify_source_claims has nothing to
complain about -- the marker is gone -- and the byte comparison never looks at
it, because the row points elsewhere. `Functions: OK 158/158` and `PRE-COMMIT
OK` both passed, and neither was evidence about that body.

An unclaimed REFERENCE body in a destination is the baseline: 254 of them in
that one file. An unclaimed REWRITTEN body with its marker removed is not, and
the two are indistinguishable from the row side.

DIAGNOSING IT: `git show <sha> -- <dest> | grep "^+.*ClassName"` does NOT work.
A function's class name appears only in its signature, which stays as unchanged
context, so the grep returns 0 whether or not the body was replaced. Compare the
bodies directly:

    git show <sha>^:<dest> | awk '/^Ret Class::method/,/^}/'
    git show <sha>:<dest>  | awk '/^Ret Class::method/,/^}/'

and check what markers the commit removed:

    git show <sha> -- <dest> | grep -E "^-.*present-unmatched"

After ANY mid-cycle recovery, count the markers the commit deleted against the
rows it repointed. They must match.

## Half the markers are truncated, so a name-shaped grep undercounts by half

Measured: 4,545 `present-unmatched` markers carry a TRUNCATED mangled name
(`??0AudioEventRTS@@`, no parameter encoding) against 4,640 carrying a full one.
Any screen that greps a complete signature therefore misses about half its
population. A family screen on `PAVThing@@PBVModuleData` returned 23 module
constructors; at least one more (StealthDetectorUpdate) was missed purely
because its marker is the truncated `??0StealthDetectorUpdate@@`. Treat any such
count as a LOWER BOUND and say so when you quote it.

The same truncation causes two other failures already recorded here -- a bare
`??0Class@@` binds by PREFIX so landing one constructor staleens the other, and
a donor carrying a full spelling for one destination and a truncated one for
another LOOKS multi-destination and is not. One cause, three symptoms.

When you need a real count, match on the class-and-name prefix rather than the
signature, and expect to disambiguate by hand.

## A destination can be uncommittable at HEAD, and you find out by touching it

DeletionUpdate.cpp defines setLifetimeRange and calcSleepDelay; the ledger names
only calcSleepDelay and a d_ row. Staging the file fails the claims gate with
"staged sources define functions the ledger does not declare:
DeletionUpdate::setLifetimeRange". That condition sits at HEAD and is invisible
until somebody edits the file for an unrelated reason -- then the gate names a
function they never went near.

It is not something to work around: the file wants a declaration or a marker,
and that is a ledger decision. Revert your edit, record the file, and pick
another. Worth screening a destination for it before authoring if the fold is
large.

## "Naked donor" is not a reason to skip -- 75% of them are the BEST folds

Two opposite operations get confused under the anti-lift policy:

  FOLDING A DUMP INTO A DESTINATION puts `__emit` into readable code. Forbidden,
  and conversion_gate.py rejects it.
  DELETING A DUMP whose destination ALREADY has a readable body, and repointing
  the row at it, retires the dump and lands the row on real C++. That is the
  best fold available and it is the anti-lift policy working, not breaking.

Measured across the cluster set: 415 marked donors are naked, and 310 of them --
75% -- have a destination that already defines a body for that symbol.
LANAPIUpdateThunk.cpp is 2,035 lines of `__asm __emit` for `?update@LANAPI@@`
while lanapi.cpp carries the readable LANAPI::update(). Nearly the whole
AIStates cluster is this shape.

So a naked-donor count is not a count of unmergeable work. Screen the pair
first: does the destination define that symbol? If yes it is a candidate, and
tools/marker_screen.py measures the distance in two compiles. If no, it is
genuinely conversion work for another lane.

## Buy throw() with an explicit specialisation, not a shim directory

A nothrow declaration usually lives in a shared header you must not edit
(WWLib/string_base.h). Copying the header into a shim dir works and creates a
file; an explicit specialisation does not:

    template <>
    class StringBase<UnsignedShort>
    {
    public:
        Int compareNoCase( const StringBase<UnsignedShort> &that ) const throw();
    };

It REPLACES the primary for that one argument, so every other TU sees the shared
declaration untouched. Legal while nothing has forced an implicit instantiation
for that argument, and declare only the members the TU calls. wchar_t and
unsigned short share a mangled type (G) under MSVC 7.1, so one specialisation
covers both. On one body this was worth 71 of 77 diverging instructions --
compareNoCase sat between a temporary's construction and its destruction, and
nothrow let MSVC drop the unwind-state bumps either side.

## "Same body, different template instantiation" is only cheap if something else keeps the old one alive

A call site resolving to the wrong template instantiation looks like a free fix:
point it at the right one and the bytes match. But the OLD instantiation's
COMDATs are matched rows too, and if your call site was their only emitter in
that TU, the fix trades one matched row for another.

GameSpyInfo::removeFromSavedIgnoreList is the worked example. Retail's
m_savedIgnoreMap has a twelve-byte value type where the vendored header says
AsciiString, so its erase belongs to the generic 12-byte _Rb_tree instantiation
that gen_small/tgrid_119.cpp already owns rather than the AsciiString one -- the
same 91-byte body under a different template, and a local map view compiles the
call correctly. But that erase is the ONLY expression in the TU instantiating
the AsciiString tree's `_M_upper_bound`, a MATCHED 38-byte row claimed from that
same file. operator[] and find() elsewhere in the file do not instantiate it;
only erase does. So the body cannot land until that row is retired or rehomed --
a ledger decision, not a fold.

Check before costing one of these: does any OTHER expression in the TU keep the
old instantiation's COMDATs alive? Same screen as the pool-glue and inline-COMDAT
cases, pointed at templates.

And when you find the real reason, REPLACE the note that named the wrong one. A
note naming the wrong blocker is worse than no note: it bills the next agent for
the wrong fix.

## An orphan accessor: retail has NO caller, and your correct fold kills the row

`callers_of` on `?setNext@LANGameInfo@@QAEXPAV1@@Z` and
`?setName@LANPlayer@@QAEXVUnicodeString@@@Z` returns no named caller anywhere in
retail. They are orphan COMDATs the linker kept. Our tree held those rows green
only because converted bodies called accessors that RETAIL INLINES AWAY -- so
writing the body correctly stops emitting the accessor and the row goes red.

That is why a correct fold can turn a row you never touched red, and it is
distinct from the pool-glue and template cases: there the emitter was incidental,
here the emitter exists only because the port is wrong.

Two outcomes, and check which before declining:
  the row has another real home -- setName is called three times from
  LANAPIhandlers.cpp and byte-verifies there (7/7), so add_match repointed it and
  the fold landed;
  the row has none -- setNext's only call in the tree is on a different class's
  member, so the fold stays declined until someone rehomes or retires the row.

## Some donors are in the WRONG DESTINATION, not merely hard

/EH mode is per-TU, so a donor needing a different one can never fold into a
destination that cannot move. Retail's LANAPI::RequestAccept has NO SEH frame at
all -- `sub esp,0x1e0 / push esi / mov esi,ecx` -- while constructing and
destroying a temporary, which only happens under /EHs-c-. lanapi.cpp is /EHsc
and cannot change, because RequestGameJoin, LookupGame and RequestGameOptions
are matched there WITH frames.

So RequestAccept and RequestGameAnnounce should KEEP their own TU or find a
different destination. Folding them into lanapi.cpp is wrong in principle, not
merely blocked -- record it that way, because "blocked" invites a retry and
"wrong destination" does not.

## check_csv's own fix hint contradicts the duplicate-row rule

check_csv reports a union-merge duplicate with `Fix: python3 tools/dedup_csv.py`.
Following that rewrites both ledgers normalised -- a ~157,000-line diff that
conflicts with every branch in flight -- when the correct repair is to drop the
duplicate ROWS with ledger_io.py keeping the first. The message is wrong for
this case and agents have followed it. Ignore the hint; the rule is above.
## Any two 5-byte jmp thunks byte-match, so count the callers

A `jmp rel32` is five bytes of which four are a masked relocation. One byte is
compared. So EVERY 5-byte tail-call thunk in the tree byte-matches every other,
and a row parked on the wrong one still says `matched`. It is the same trap as
the wrong `$L93744` pin that rode along on the PeerDefs funclets, one level up:
masking is what makes the reconstruction possible and what makes these
indistinguishable.

The discriminator is the call profile, and it is one pass over `.text`:

    hist = Counter()
    for i in range(len(text) - 5):
        if text[i] in (0xE8, 0xE9):
            hist[tva + i + 5 + int32_at(text, i+1)] += 1

Then read the count against what the claimed function is FOR.
`?addTeam@TeamsInfoRec@@QAEXPBVDict@@@Z` claimed a stub with 6,947 callers;
retail calls addTeam from a handful of places, and 6,947 is what a string
destructor's import thunk looks like. Sure enough the stub was
`jmp 0x0005EE90`, which functions.csv already recorded as
`??1AsciiString@@QAE@XZ`'s body.

To find the candidates, sweep for rows whose `target_rva` equals a DIFFERENT
symbol's `export_rva` and whose first retail byte is 0xE9. That is 1,078 rows,
and almost all of them are fine: 1,048 are `?j_XXXXXXXX@@YAXXZ` placeholders in
`Code/gen_small/thunks_*.cpp`, which claim ILT slots by address on purpose. Of
the 30 with real mangled names, 27 are the FX `getClass<T> -> jmp getInstance<T>`
pairs -- semantically coherent, ~5 callers each, a real tail call. Three were
the outlier. So the sweep alone proves nothing; the sweep plus the caller count
does.

Consequence for triage: `marker_screen` reports a small `miss(N)` when a
destination holds a real body and the donor row owns a jmp stub -- it is
comparing the body's first five bytes against a jump. A low miss(N) is only
meaningful when donor and destination model the same SHAPE of function. Check
the donor row's size before believing one.

## A push loop that trusts an empty commit range cannot see its own failure

`git log origin/master..HEAD` is empty when you are pushed AND when a conflicted
rebase has left HEAD detached on origin's tip with your commit only in the
reflog. Checking HEAD's POSITION instead does not help -- in that failure HEAD
really is an ancestor of origin/master, so the position check passes too. And a
push guard grepping for "rejected" misses the actual error text, which can be
"a pushed branch tip is behind its remote counterpart" or, mid-rebase, "fatal:
Exiting because of an unresolved conflict."

Both failures start with a silenced `git pull --rebase` swallowing the conflict.
Observed twice in one day: once reporting a false PUSHED, once exhausting its
retries in total silence while the commit was lost.

Use `tools/push_retry.sh`, which never silences the pull, refuses to start
mid-rebase, exits non-zero with the conflicted paths when the rebase needs
hands, and confirms the commit SUBJECT is in origin/master before printing OK.
Verify a push by what reached the remote, never by a range that is empty in the
failure case as well.

## An investigation command can be destructive: never reset a checkout you share

Chasing whether some orphaned reflog commits had really landed, I ran
`git reset --hard origin/master` in the shared Open-BFME1 checkout to get a
clean base to grep. Another lane was mid-fold in that tree, and the reset threw
away its index and working copy without a prompt.

Nothing was actually lost -- every InGameUI.cpp and functions.csv blob from that
window turned out to be BEHIND master, a superseded mid-rebase snapshot -- but
that was luck, not care. The reason to write it down is that `reset --hard` did
not feel like a mutation at the time; it felt like setup for a read-only
investigation, which is exactly how the dangerous ones look.

Two rules. Investigate from a worktree you own, or from `git cat-file`/`git show`
against a ref, which touch nothing. And if you must know what a shared tree
holds, `git status --porcelain` first and stop if it is non-empty.

Recovering a clobbered index is possible but only briefly: staged blobs survive
as loose objects until gc, and `find .git/objects -type f -printf '%T@ %p\n'`
sorted by time finds them far faster than `git fsck`, which times out on this
repo. Note `find -newermt` silently returned nothing here; compare the numeric
`%T@` against a cutoff instead.

## A GREEN build under a layout define is not evidence the define is right

`/DBFME_MODULE_NO_MPO` drops MemoryPoolObject from Module's base list, removing a
vptr and shifting every member below by four. Three destinations, same family,
three different answers:

  W3DPropDraw and CreateObjectDie: the define IS the whole fix, no view, no shim.
  InstantDeathBehavior and BridgeTowerBehavior: RED under it. Each has an
    already-matched this-adjusting interface getter in the same TU, and a
    this-adjustment encodes base offsets directly -- so those matched rows are
    positive proof these objects DO carry the vptr the define removes.
  AssaultTransportAIUpdate: stays GREEN under the define and gets WORSE --
    ctor miss(7) without it, miss(11) with it.

That last one is the trap. Nothing in that TU contradicted the define, so the
build had nothing to say; only the screen did. Take the miss count, not the exit
code, as the evidence that a layout define belongs. And note the shape of the
proof in the RED pair: a matched this-adjusting thunk in the same TU is a
layout witness you already own.

## When a diff lands on a masked DIR32, read the relocations, not the disassembly

explain_mismatch rendered two vptr stores as `mov DWORD PTR [esi+0x4],0x5ec68b00`
followed by stray `.byte`s, because relocation targets are zero-filled in the
object and the disassembler ran off the end of the immediate. Read as a mystery
member, it sent an agent looking for a field that does not exist.
`build.read_object_symbol_bytes` returns `(body, relocs)`; the relocation list
named `??_7W3DPropDraw@@6BMemoryPoolObject@@@` and `??_7W3DPropDraw@@6BSnapshot@@@`
outright and the diagnosis was immediate.

## Rank a cluster with ONE compile before applying anything

Build the destination once, then for each donor read its symbol out of the
already-built .obj, mask relocations, and compare against retail. Twenty
candidates ranked in a single build with no applies and no ledger churn. It put
addMessageText at 64.9% agreement (landed 388/388 first try) and correctly warned
that `update` at 19.3%, failing at offset 0 on an `and esp,-8` aligned frame, was
a research task rather than a fold.

## Fresh views need tuning ONE AT A TIME against the residue

objectChangedTeam: repointing its row onto the existing body agreed on 62.4% of
masked bytes; correcting all six known offset facts at once dropped it to 29.7%.
The offsets were right and the spellings were wrong -- each fresh view moved
MSVC's register allocation more than the corrected offset was worth. In the same
file addMessageText landed first try, because its views already existed as proven
spellings. Correct facts applied together can still go backwards; add one view,
measure, keep or revert.
## The second thunk test: is this stub the body's ONLY thunk?

Caller counts settle a jmp stub's identity only when the two candidates have
wildly different call profiles. They are useless when both are called once, and
plenty of constructors are. The test that works there is topological: build the
map of every 5-byte `E9` in `.text` to its target, and ask how many stubs reach
the body in question. Incremental linking emits ONE thunk per function, so if a
body already has a matched claim under name B and exactly one stub jumps to it,
that stub is B's thunk -- whatever name a row has parked on it.

`??0AutoHealBehavior@@` claimed a stub whose only target is a 276-byte matched
`??0SpyVisionUpdate@@`. Both are called once. ICF is not the alternative
explanation: folding needs identical bodies WITH identical relocations, and two
module constructors store different vftables.

Sweeping for it: 5-byte rows whose jump target is claimed by a differently-named
symbol give 272 hits, and most are the project's own conventions -- a real name
thunking to a `?d_`/`?j_`/`tg_`/`Gen_` placeholder body, or to a deliberate
`..._Body`/`...Shim` split, or the same template function under two manglings.
Excluding those leaves 81; requiring the stub to be the body's unique thunk and
the body to be a matched claim of 32 bytes or more leaves 67. Confidence is not
uniform inside that 67: a 276- or 652-byte body cannot be an ICF twin of another
class's constructor, but a 69-byte trivial ModuleData constructor plausibly can,
and for those the ledger may be modelling a genuine fold. Sort by body size and
believe the large ones.

Eleven of the 67 are donors in the marker queue, so screening them returns a
small `miss(N)` that means nothing at all.

## $L numbering is file-sequential, so a typedef freezes a TU as hard as a class

"$L-anchored rows are broken by ANY added declaration" is true but understates
it. The counter runs across the whole translation unit in source order, so any
change that alters codegen ABOVE a pinned funclet renumbers it -- not only new
declarations, and not only new types.

Measured on StagingRoomGameInfo.cpp, which owns `$L70459` and `$L64396`. A
class-template slot view renumbers them, as expected. So does this, which
declares no class and emits no code of its own:

    typedef Bool (__fastcall *BfmeAmIHostFn)( const GameSpyStagingRoom * );
    if ((*(BfmeAmIHostFn **)this)[4]( this ))

Both die with `symbol not found in object: $L70459`. Contrast a `#line`
directive, which is genuinely free and renumbers nothing. So when a destination
carries `object-symbol=$` rows, the question is not "can I avoid declaring a
class" -- it is whether the funclet pins get re-anchored first.

Two smaller notes from the same attempt. MSVC 7.1 rejects `__thiscall` on a
function-pointer type outright (`error C4234: nonstandard extension used`), so a
hand-rolled vtable call has to be `__fastcall`, which is call-compatible for a
method taking no arguments. And the cost of re-anchoring is worth weighing
against the whole destination, not one body: StagingRoomGameInfo.cpp is one byte
from closing `?resetAccepted@GameSpyStagingRoom@@` -- retail tail-calls slot
+0x10 where the shared header computes +0x08 -- and carries eleven queue entries
behind the same freeze.

## A class that is too SMALL needs BYTES, not a new class -- and measure per body

Player.cpp carried a written verdict against disableRadar and enableRadar:
"Cannot come home: retail's AudioEventRTS is 0x70 bytes where this tree's is
0x64 ... a class-shape difference, not a field view." The diagnosis was right
and the conclusion was wrong. All three radar bodies now match byte for byte
(193/193, 186/186, 215/215) on a padded local:

    struct BfmeAudioEventStorage
    {
        BfmeAudioEventStorage( const AudioEventRTS &src ) : e(src) { }
        AudioEventRTS e;
        UnsignedByte _bfme_tail[12];
    };

The member sits at offset 0, so its address, constructor and destructor are
unchanged and every call in the body stays what it was; only the frame grows.
**The constructor is load-bearing**: declaring the storage and then assigning
default-constructs and then assigns, where retail copy-constructs in one call.
Take the source by const reference and initialise in the member list.

The counter-example matters as much. addRadar reserves 0x60 where the other
three reserve 0x70, orders its EH frame differently, and lives at 0x000FB3F0
well away from them. The twelve bytes belong to the FRAME those three share,
not to AudioEventRTS everywhere. Measure the frame per body; do not pad on
faith. And treat a "cannot come home" verdict as a measurement someone took
once, not as a closed door.

## A bespoke local replica proves the byte SHAPE, never the IDENTITY

A `*_Thunk.cpp` donor that declares its own little struct to reach an offset has
chosen those offsets as free parameters to fit the bytes it wanted. It will
agree with retail and still be about a different function. Squad_isOnSquad.cpp
declares the membership pair at +0x04 and matches; three siblings compiled from
the REAL class in Squad.cpp say the pair is at +0x08/+0x0C. Against siblings
built from the shared class, a local replica is the weaker witness.

This is why a large number of our `*_Thunk.cpp` donors cannot be trusted to name
the function they claim, and it is the same failure as the 5-byte jmp rows: a
match against a shape you chose is not evidence of identity.

## Screening one symbol does not license applying the DONOR

`?parseArmorTemplateSet@ArmorTemplateSet@@` screened MATCH into ThingTemplate.cpp,
but the apply moved a SECOND row in the same donor that was never screened and
does not match from there. merge_cluster was correct -- selection is by row, and
a marker named that destination. The screen simply did not cover it. **Compare a
donor's row count against its marker count before --apply.**

It then failed dishonestly, which is the part to remember: `verify_source_claims`
read the repointed row as "byte-verified matched from this file" out of the
LEDGER rather than out of the bytes, and complained that the other symbol's
marker was a stale annotation. Clearing that marker is what let the real byte
failure surface on the next build. **A stale-annotation complaint about a row
that just moved is a question, not an instruction.**

## miss(1) and miss(2) are where a wrong offset lives, not "nearly done"

Forty donors screened in one pass: four landed, six were free, and every
remaining small miss was a layout fact costing a compile each to learn.
DecalMeshClass at one byte is a refcount initialiser that fourteen sibling
classes set the other way. Squad::isOnSquad at two bytes is a class-shape
contradiction inside one class. The Upgrade family's four bodies at miss(2) are
one base-ORDER difference: read as spans, eight bytes move out of the second
base into the first, which is why no define closes it.

Budget a near-miss as a research task, not as a fold that is almost finished.

## Read the compiled SIZE beside the agreement percentage

Once the compiled size differs from retail's, the percentage stops moving even
as you fix real things, because every byte after the first divergence is being
compared against the wrong position. Three separate correct offset fixes left
addSuperweapon at exactly 60.4% while its loads visibly stopped diverging.
Size converging on retail's is the signal; the percentage alone will tell you
your correct fixes did nothing.

## Read which REGISTER a call goes through, not which line it sits next to

`FileSystem::openFile` was assumed virtual because the vtable call NEXT TO IT
had shifted. Adding the view emitted an extra `mov edx,[ecx]`, which misaligned
everything after it and took agreement from 98.4% down to 95.7%. It is a DIRECT
call in both trees.

Proximity to a call you have just corrected is not evidence about a call. The
indirection is visible in the instruction -- read it. Same family as
objectChangedTeam: a plausible view that is wrong does not merely fail to help,
it actively destroys agreement you already had.

## OBJECT_STATUS_UNDER_CONSTRUCTION is bit 2: BFME drops one enum entry

Two independent retail bodies do `test BYTE PTR [eax+0x90],0x4` where this tree
reads a dword pair at +0x90/+0x94 and tests 0x8. ZH's ObjectStatusTypes runs
NONE, DESTROYED, CAN_ATTACK, UNDER_CONSTRUCTION -- index 3, so `test()` compiles
to bit 3. BFME has ONE FEWER entry ahead of it.

240 use sites, so this is a shared-header change behind a lot of rows and not a
readability-lane fix. But it is solvable rather than guessable, and that is the
point worth recording: `getStatusBits().test(X)` compiles the enum INDEX into
the instruction, so every matched body testing ANY status bit is a constraint on
the ordering. Collect the constraints, solve for which entry BFME drops, and let
the already-matched rows prove it -- do not edit the enum and see what survives.

## A 100% masked screen is necessary, not sufficient

DataChunkInput::openDataChunk reaches 100% of masked bytes and still fails,
because the masked comparison cannot see a call that resolves to the WRONG
FUNCTION. Retail's `AsciiString("")` there calls RVA 0x00102D90 --
`?d_00102d90@@YAXXZ`, an unidentified 77-byte gen-dump whose body reads `[ecx]`
and compares `[m_data+0xC]` against its argument, which is a `set` and not the
constructor at 0x00888BC0 this tree resolves to.

This is the same blindness as the 5-byte jmp thunks arriving from another
direction: masking hides IDENTITY. A perfect score means every byte you can see
agrees, and the bytes you cannot see are exactly the ones that name the callee.

## Before renaming to fix a DIR32 red, check the TARGET symbol's existing bases

Renaming misnamed references onto the correct global is the honest fix, but it
only clears the red if the name you are moving TO is already consistent. If that
symbol is itself referenced somewhere at a different address, the rename hands
it a second base and the gate stays red under a new name -- with the work spent.

One pass of dir32_sites.py over the candidates answers it before any edit. For
the ThePartitionManager red: `?TheShroudManager@@3PAVShroudManager@@A` already
had two references and both were at 0x012ED5BC, the same base the misnamed sites
resolved to; `?TheRadar@@3PAVRadar@@A` had nine, all at 0x012EF0E4. So every
reference being moved landed on a symbol that already agreed with it.

Two useful corollaries. A second NAME at the same address is not a problem --
the check is per symbol, so `?TheRadarClientUpdate@@...` sharing 0x012EF0E4 is an
ordinary alias. And the completion test needs no gate run: when the rename is
done the misnamed symbol should have ZERO DIR32 references, not one base. A
remaining base means a site was missed.

## Markers are COMMENTS, so one compile answers a whole destination

marker_screen.py pays two compiles per (donor, symbol) question. But a marker
cannot change what the compiler emits, so a destination carrying 65 markers does
not need 65 builds: compile it ONCE, then ask build.compile_function the same
question of every marker against that single object. 24 destinations and ~1,300
markers screened in one pass, against roughly 2,600 compiles the old way.

The general form is worth keeping in mind elsewhere: when the thing you are
varying is a comment, an annotation or a ledger note, the expensive artifact is
invariant and belongs outside the loop.

## find_declared_unmatched cannot see a stale marker that has an overloaded sibling

It resolves an abbreviated label by prefix, but only when the file carries
exactly ONE marker with that label. Overloads share a label, and claiming one
says nothing about the others -- so a stale marker with an overloaded sibling is
invisible to it permanently, not merely missed once. Two such markers had made
their files uncommittable at HEAD and had never been looked at.

Treat this as a known blind spot rather than trusting the check's silence. A
tool that is confidently wrong costs more than one that stops.

## Prefix resolution binds a truncated marker to the WRONG overload

Fixing stale markers by script would have destroyed true statements.
render2d.cpp carries three `// ?Add_Quad@Render2DClass@@` markers while the
matched row is `?Add_Quad@Render2DClass@@QAEXABVRectClass@@0K@Z` -- a fourth
overload that correctly carries no marker. Seven candidates were rejected on
reading for this reason.

Same shape as the 5-byte jmp thunks and the 100%-masked screen: a prefix hides
identity exactly as a mask does, and identity is what the question is about.
When a fix needs a mangled name spelled out, read it from the compiled object;
a marker naming a symbol that does not exist is a worse lie than the stale one
being replaced.

Also: replace such a line in place rather than deleting it. Files that compile
macros expanding `__LINE__` change bytes below any removed line.

## When a matched TU works around the shared header, the HEADER is what is wrong

Four separate requests for a new `reference/shims/` directory have now dissolved
on an artefact the tree already owned. The clearest:
`CachedFileInputStream::open` appeared to need a Compression.h shim because
BFME's `decompressData` takes a `const void *src`. But
`Code/Libraries/Source/Compression/compression.h` is OUR copy, byte-identical to
the reference bar a provenance comment, and DataChunk.cpp was the ONLY file
including it -- reaching the reference copy merely because our directory was not
on its include path. Correcting the header we own was narrower than duplicating
it into a shim.

The tell was in the tree the whole time: `CompressionManager_decompressData.cpp`
reproduces that body byte for byte and has to declare its own local class to say
`const`. A matched TU carrying a local workaround for a shared declaration is
evidence about the DECLARATION, not a trick to copy.

Before adding a shim, check whether the repo already owns the header, whether
the destination is even reaching our copy, and which matched TUs already work
around it.

## `and esp,-8` with no floating point anywhere: rule it out before theorising

`LANAPI::update` opens `push ebp / mov ebp,esp / and esp,0xfffffff8`. MSVC 7.1
emits that for a local needing eight-byte alignment, which normally means a
double or an `__int64` -- so that is the first thing to test, and it is FALSE
here. Scanning all 2030 retail bytes for `fld`, `fstp`, `fild`, `fadd`, `fmul`,
`fdiv`, `movq` and any qword operand returns nothing at all.

That leaves `__declspec(align)`, `_alloca`, or inline asm, and the question has
to be settled before anything downstream in the body can be judged -- it fails
at offset zero, so every later measurement is against a shifted frame.

The wider point: re-measuring after the LANAPI layout correction landed produced
NO movement at all (393/2030 before and after). A body that does not move when
you fix a real thing is telling you the real thing was not what held it.

## The marker queue is NOT a fold backlog: two thirds of it has no ledger row

158 destinations screened in one pass, roughly 3,000 markers:

    ~2,000  no ledger row AT ALL -- a body present in the tree with no matched
            retail address behind it. Screening can never turn these into folds;
            they are AUTHORING work, not repointing work.
      ~300  measured misses, nearly all layout facts
       ~30  MATCH, collapsing to 9 distinct symbols, of which 6 landed

That is roughly one fold per 26 destinations screened. Anyone budgeting a lane
against the marker count is budgeting against a number that is two-thirds
something else. Measure the composition of a queue before planning against its
size -- this cost one pass and should have been done first.

## A marker can sit above a CALL, not a definition, and folding invalidates the rest

Markers are not always above the body they name. W3DVolumetricShadow.cpp carries
four `// ?Fabs@WWMath@@SAMM@Z present-unmatched` lines INSIDE a function body,
one above each CALL of it; W3DWater.cpp has four the same way for
Set_DX8_Render_State. `--apply` consumes the pair it matched and leaves the
others, so landing one inline-emitted COMDAT turns every remaining annotation of
that symbol in that file into a stale marker. The gate catches it, but the
cleanup belongs in the same commit.

Two consequences. Folding an inline-emitted symbol always means sweeping its
other annotations in the destination. And in-place replacement stops being a
preference and becomes mandatory: these lines sit inside function bodies, so
deleting one moves every line below it and changes any `__LINE__` the TU expands.

## Some MATCHes are not expressible as a merge, and --symbols does not help

`?Set_Transform@DX8Wrapper@@` matches from BOTH W3DWater.cpp and
W3DWaterTracks.cpp. One row cannot land in two files. Worse, boxrobj.cpp -- which
owns it -- carries no readable-body marker naming either, so there is no cluster
to select within at all. The constraint is UPSTREAM of selection, so per-symbol
selection cannot reach it.

Log these and leave them. Do not add a marker to create the cluster: the marker
is the evidence the tool reads, and writing one to make an apply possible is
manufacturing the input rather than recording a finding.

## A cluster member is a MARKERED ROW, not every row its donor owns

screen_cluster.py collected donor FILES by marker and then screened every row
those files own. ini.cpp owns 256 rows and carries 32 markers for INI_stl.cpp,
so 224 non-members were measured and reported as candidates -- an "eleven ready
rows" verdict that was really two.

The invariant: only a markered row is a cluster member, and only a markered row
is something merge_cluster can move. Filter a donor's rows against its own
marker list, matching by prefix since a marker may name a truncated symbol.

The instructive part is WHERE the bug was. merge_cluster -- the tool that ACTS
-- had it right all along, intersecting owned rows against `claims(...)`.
screen_cluster -- the tool that MEASURES -- did not. So the measurement was
promising folds the apply step would have refused, and the two disagreed
silently until --symbols made the apply reject nine names at once. When a
measuring tool and an acting tool encode the same rule separately, the measuring
one is where the drift hides, because nothing fails when it is wrong.

Corrected counts come in LOWER, never higher, so nothing landed on the old
numbers is at risk -- but any shortlist built with it is inflated wherever a
donor owns more rows than it has markers for. That shape is common:
lanapi, InGameUI, Player and DataChunk were unaffected precisely because each
donor there owned only the rows it had markers for.

## HYPOTHESIS: BFME classes carry TWO links where the reference carries one
(Superseded in part: the discriminator below now separates this from a
shifted class before any code is written. GameWindow was the third witness
and it was NEGATIVE, which is what bounded the habit.)

Two independent classes now show the same shape, and it is worth testing on a
third before treating it as a fact.

**Script** carries two action pointers. `ParseActionDataChunk` reads and writes
`Script+0x20`, while `getAction` and `setAction` both work on `+0x28` -- and
retail's own accessors settle it: `mov eax,[ecx+0x28]; ret` at 0x00112980 and
`mov [ecx+0x28],eax` at 0x00112970. So the accessor pair maintains one action
list and the parser appends to a different one.

**LANGameInfo** is the same: +0x360 maintained by the accessors, +0x398 walked
by the bodies.

If this is a habit rather than a coincidence, it predicts a family of blockers
that read as "the accessor and the body disagree about an offset" and are
actually two real members. The diagnostic that distinguishes them: a matched
ACCESSOR is authoritative about its own offset, so when a body disagrees with a
matched accessor, suspect a second member before suspecting a layout error --
and check whether both offsets are live rather than assuming one is wrong.

Do not fold this into a layout correction. Adding a view that moves the parser
onto the accessor's offset would make one row match and silently merge two
distinct members.

## find_emitter: which TU could an orphaned row live in, without a build

Seventh instance of the orphan-accessor pattern, so `tools/find_emitter.py`
answers it directly:

    python3 tools/find_emitter.py '?getAction@Script@@QBEPAVScriptAction@@XZ'

Every object under `build/match` is already compiled, so the answer is in the
symbol tables. It reads them, names the sources, compiles nothing, writes
nothing.

**The distinction it enforces is the one grep cannot make: EMITTING is what the
ledger needs, and calling is not enough.** `Script::setAction` is called in
GameLogic.cpp and not emitted there -- a guess that looked right and cost a full
TU build to disprove. It agrees with all four cases previously resolved by hand,
including the two with no home at all, which is why addGame and
ParseActionDataChunk are declined rather than pending.

Build the object map forward from the tree, never by decoding object names:
`obj_path()` joins path parts with `_` and filenames contain underscores too, so
decoding produced a path to "scripts.cpp" that was nothing of the sort.

## The rows ALREADY matched tell you which regions are safe to change

Correcting a shared class reads as dangerous because N rows depend on it. Those
rows are also the constraint that tells you whether it is safe, and they can be
read before touching anything. The question is never "how many rows depend on
this class" but **"which of them read the region I am moving, and HOW".**

**The "how" is the part that was originally got wrong here, and it is the whole
rule.** This entry first claimed that none of GameWindow.cpp's matched rows read
the shifted region. The enumeration says TWENTY of 34 do. They did not break,
and the reason is not that they avoid the region:

  * **A row reaching an offset through a TU-LOCAL VIEW is immune to a header
    change.** It compiled an absolute number -- `struct BFMEGameWindowOrigin
    { char pad[0x14]; Int x; Int y; }` and the `BFME_WIN_` macro rows -- and
    editing the class cannot reach it. Seventeen of the twenty are this.
  * **A row that reads a member BY NAME is the one at risk.** Three do:
    winSetNextInLayout writes `this+0x1F8`, winSetPrevInLayout `+0x1FC`,
    winSetLayout `+0x200`, as plain `m_nextLayout = next;` bodies. Under the
    gamewindow shim's tail those become 0x208/0x20C/0x210 and stop matching.

So enumerate by MECHANISM, not by offset range. And enumerate properly: the
first pass here grepped for one macro name (`BFME_WIN`) and so counted five
view-based rows as symbolic because their views were spelled differently. One
naming convention is not a census.

## Displacement is CUMULATIVE: map the whole class with its getters

GameWindow was read twice and reported wrongly both times -- first as uniformly
+4, then as "short at the front, already correct at the tail". Both were
artefacts of measuring one end. The truth is a staircase, one step per
insertion:

    +0x2C m_userData  +4     +0x34 m_id      +4     +0x3C m_style    +4
    +0x1EC m_tooltip  +8
    +0x1F8 m_next    +16     +0x200 m_parent +16    +0x210 m_layout +16

which is exactly the four BFME-only insertions in `reference/shims/gamewindow`
(+0x04, +0x1DC, +0x1F0, +0x1F4) accumulating.

**A sizeof tells you the TOTAL, never the distribution.** 112 against 108 is
consistent with one insertion anywhere, or four. Do not size a header pass from
one measured delta or from a sizeof.

**The cheap instrument is the getters.** Each getter is a single load, so each
PROVES one retail offset outright -- no build, no view, no inference. Read a
class's getters together and the whole displacement falls out in one pass.
Thirteen of them mapped GameWindow after two wrong readings from partial data.

## A getter and a setter for one member cannot disagree about its offset

The cheapest identity evidence in the tree, and it settled a question that had
already been escalated as unanswerable.

Three matched GameWindow setters write `this+0x1F8`, `+0x1FC` and `+0x200` as
plain `m_nextLayout = next;` bodies. The getters prove those offsets are
**m_next, m_prev and m_parent** -- m_nextLayout sits at +0x208. So
`?winSetNextInLayout@…@Z` at 0x001BD6A0, `?winSetPrevInLayout@…@Z` at
0x00478DD0 and `?winSetLayout@…QAEX…@Z` at 0x0026ED70 are misnamed: they are
winSetNext, winSetPrev and winSetParent, matching only because our header puts
m_nextLayout exactly where retail puts m_next.

Third instance of a row green because a layout error cancels a naming error,
after the VertexMaterialClass colour-source pair. Reach for the getter/setter
pair BEFORE escalating an identity question -- it is one disassembly per member
and it answers outright.

## Check a candidate shim against the BODIES, not against the destination

`reference/shims/gamewindow/GameClient/GameWindow.h` already carried the exact
layout that nine GameWindow rows needed, four-byte anchor included. It had been
opened, read as disagreeing, and dismissed -- because it was compared against
the DESTINATION's current class rather than against the retail bodies. It was
agreeing with the bodies and disagreeing with the destination, which is precisely
what a correct shim for a wrong destination looks like.

Fifth new-shim need to dissolve on an artefact the repo already owned, and the
first where the artefact had been looked at and rejected. When a shim seems
wrong, check which side it disagrees with before discarding it.

## One source name, two real functions, two addresses

That shim still could not be used, for a reason worth knowing: it declares
`winSetLayout`, `winSetNextInLayout` and `winSetPrevInLayout` returning `Int`
where GameWindow.cpp defines them returning `void` -- and BOTH ARE REAL.
`?winSetLayout@GameWindow@@QAEHPAVWindowLayout@@@Z` is at 0x00478E10 and
`?winSetLayout@GameWindow@@QAEXPAVWindowLayout@@@Z` is at 0x0026ED70. MSVC
encodes the return type, so they are distinct symbols that share a source name.

A shim can therefore carry a correct layout AND a set of signatures that belong
to one TU only, and a destination gets one or the other. A TU-local view takes
the layout without the signatures, which is why views keep working where the
shim cannot be adopted.

## THE DISCRIMINATOR: second member, or short class? -- HALF OF THIS WAS WRONG
**The GAP RULE below is FALSIFIED. Read the correction that follows it before
using anything in this entry.**

A matched tiny accessor is authoritative about its own offset -- it is
byte-verified and does nothing else. So collect a class's accessor-proven
offsets and look at how the disputed offset sits among them. This costs four
disassemblies and no build, and it settles a question that otherwise costs a
speculative view.

**One disputed offset in a GAP the accessors do not cover, accessors consistent
among themselves -> a SECOND MEMBER. The body is right.**

    LANGameInfo   getNext/setNext prove +0x360, get/setLastHeard prove +0x364 --
                  adjacent, consistent, no shift. The link the bodies walk is
                  +0x398, 0x38 further on, covered by nothing.
    Script        setActive +0x1C, get/setAction +0x28, setFalseAction +0x2C,
                  setNextScript +0x30, setFrameToEvaluate +0x34 -- a dense
                  consistent run. The parser's +0x20 sits in the gap between
                  +0x1C and +0x28 with no accessor over it.

**A RUN of consecutive members at the SAME delta -> the CLASS IS SHORT. The
header is wrong.**

    GameWindow    m_status, m_size, m_userData, m_instData are every one exactly
                  +4 out. Four coincidental second members all four bytes apart
                  is not credible; one inserted member is -- and the gamewindow
                  shim's independent reconstruction names it,
                  `GameWindowAnchor *m_bfmeAnchor // @0x04 (BFME-only)`.

This is the guard the two-links hypothesis needed, because the tempting move --
a view sliding the body onto the accessor's offset -- makes the row match while
silently merging two distinct members.

Evidence strength differs and should be carried with the claim: LANGameInfo's
+0x398 is proven by three matched rows (removeGame, LookupGameByListOffset, and
a reverted addGame); Script's +0x20 rests on retail's bytes alone, because the
only body that uses it is the one that cannot land. Script is a strong reading,
not a proven one -- if a later case contradicts the gap rule, re-examine Script
first.

## retail LANPlayer::setName never touches `this`

0x00624C10, 72 bytes: it constructs something from its by-value argument and
destroys it again, and never writes through the instance pointer. Same shape as
the three InGameUI varargs message stubs -- a name that survives a layer BFME
removed. Not chased; flagged because anyone treating that symbol as an accessor
is reading a name rather than a body.

## A row can be GREEN because a layout error cancels a naming error

The worst case yet, because nothing complains. In VertexMaterialClass three
bodies -- Get_Ambient, Get_Specular, Get_Emissive -- each stop on ONE byte and
all on the same one: retail loads the material pointer with `mov eax,[ecx+0x08]`
where this tree emits `[ecx+0x0C]`. So MaterialDyn is at +0x08 in retail and
+0x0C here, and the class measures 112 against retail's 108.

Given that shift, two MATCHED rows in the same file read one field past their
names. `?Get_Ambient_Color_Source@` at 0x00921210 is `mov eax,[ecx+0x14]` and
`?Get_Emissive_Color_Source@` at 0x00921230 is `mov eax,[ecx+0x18]` -- our
offsets for those fields, while in retail's layout +0x14 is EmissiveColorSource
and +0x18 is DiffuseColorSource. They match ONLY because the +4 shift slides our
field under retail's load. The trio and the pair imply mutually exclusive
layouts for one class, so both cannot be right.

Two consequences worth internalising:

A matched row is evidence about BYTES, never about NAMES -- same conclusion the
5-byte jmp thunks, the 100%-masked screen and the local replicas all reached,
arriving here from a fourth direction. Compounding errors that cancel is the
only one of the four that a correct fix will appear to BREAK.

So expect it: fixing the layout will turn those two red, and that is the fix
working. Before a class correction, identify which matched rows are green by
cancellation, and predict them as expected casualties in the commit message --
otherwise the next agent reverts a correct change to get the count back.

## Ask the compiler for a sizeof, and validate the instrument before believing it

MSVC will state a size in a diagnostic if you make it print a type:

    static char (*p)[sizeof(X)] = 1;   // cannot convert from 'int' to 'char (*)[112]'

That gave sizeof(RefCountClass)=8, sizeof(W3DMPO)=1 (empty-base optimised), and
sizeof(VertexMaterialClass)=112 against retail's 108.

**Validate the probe first with an unconditional `#error` in the same header**,
to prove the file actually recompiles. Only then does a conditional probe that
does NOT fire mean anything -- a probe silently reusing a cached object reads as
a clean negative result, which is the same swallowed-failure shape as a sweep
reporting "0 refs" for 314 objects that failed to load.

**RETRACTED, and the retraction is the more important lesson.** The sizeof
figures above and a companion result -- that dropping the empty W3DMPO base did
not move the offsets, so W3DMPO was "ruled out" -- were all measured against
`reference/CnC_Generals_Zero_Hour/.../vertmaterial.h`, which this build does not
use. WW3D2 has its own copy and a relative include finds it first. Every one of
those experiments was a no-op, and two of them were reported as findings.

So `#error` proves the file RECOMPILES. It does not prove you are editing the
file the build READS. Those are different questions and only the second one
matters. **Check the deps sidecar for the header the compile actually opened
before editing any header**, especially where a vendored copy and a local copy
share a name.

## Three screen MATCHes that are not folds

They look identical in a report and each needs a different answer:

  * **A symbol matching from a SECOND destination.** `?Fabs@WWMath@@SAMM@Z`
    matched from coltest.cpp after its row had already moved into
    W3DVolumetricShadow.cpp. That is not a second fold -- it means the body
    compiles identically in several TUs, and chasing it is ping-pong.
  * **Donor equals destination.** `?Add_Quad@Render2DClass@@QAEXABVRectClass@@0K@Z`
    "matches" from render2d.cpp, which is already its own source. A no-op.
  * **Donor under `reference/`, not `Code/`.** `?Configure_Material@MeshMatDescClass@@`
    matches with its donor in the vendored tree. Repointing a row onto a
    reference-tree source is a different decision from folding two of our own
    files, and should not be taken as ordinary cluster work.
## A small miss(N) is a classification, not a distance

Screening a whole destination per compile makes miss counts cheap enough to
gather in bulk -- 493 of them here, after dropping the 5-byte jmp stubs whose
count is meaningless. Sorted smallest-first they look like a work queue. They are
not. Every miss(1) and miss(2) read in detail turned out to be one of four
things, and only the last is work:

  A CONSTANT BFME CHANGED.  WeaponSet's three miss(1)s are all `loop to 4` where
  ZH's WEAPONSLOT_COUNT is 3: BFME's weapon set has a fourth slot. Fixing the
  constant widens m_weapons[] by four bytes and moves everything nine matched
  rows in that file read, so the donors stay split on purpose.

  A FIELD OFFSET.  VertexMaterialClass's three getters are all `[ecx+0x08]`
  against our `[ecx+0x0C]`; User::setName is `add ecx,0x4C` against `add ecx,4`.
  One byte on the wire, 4 or 72 bytes of layout behind it.

  A TRUNCATION.  W3DSnowManager::update's three bytes are where OUR body ends
  and retail keeps going -- one more call and a tail call. When the differing
  offsets are the LAST bytes of the row, the bodies are different lengths and
  the number is missing behaviour, not drift.

  TWO FACTS AT ONCE.  WorkerAIUpdate::isCurrentlyFerryingSupplies has three
  offset bytes with deltas +0x14, -4, -4 across two different classes. A single
  lever cannot close a miss whose deltas disagree.

So read the DIFFERING BYTES before costing a miss, and check three things in
order: is the row a 5-byte jmp stub (then the number is noise), do the diffs sit
at the end (then it is a length difference), do the deltas agree (then one lever
might close it). A miss(1) is not nearer to landing than a miss(9); it is just
smaller evidence of whatever it is.

## CORRECTION: the gap rule is dead; use the LIVENESS test

`Drawable::getID` falsified it within the hour. Retail reads +0x100, this tree
reads +0x8C, the accessors either side both AGREE at retail's offsets
(getInstanceMatrix +0xD4, getFullyObscuredByShroud +0x148), and +0x100 sits in
the gap between them. The gap rule calls that a second member. It is not -- it
is ONE member declared in the wrong position, and the row lands 7/7 by pointing
at +0x100.

**What survives:**

  * A RUN of consecutive members at a CONSTANT delta is still a reliable
    shifted-class positive. GameWindow's four members, all exactly +4.
  * **The liveness test, which replaces the gap rule entirely: does retail use
    OUR offset anywhere -- an accessor, or a matched body? If nothing does, our
    offset is the error and there is one member.** A question about evidence,
    not about shape.

**Reclassified:** LANGameInfo PASSES -- +0x360 by get/setNext, +0x398 by three
matched bodies. Drawable FAILS -- one misplaced member. Script is UNRESOLVED:
its +0x20 has no accessor and no matched body, only retail's bytes in the one
function that cannot land, which is good evidence the OFFSET is real and no
evidence that +0x20 and +0x28 are two members rather than one relocated one.

**So "BFME classes carry two links" rests on ONE solid case, not two.** Treat it
as a single-witness observation and do not let it steer a diagnosis.

The mechanism of the error is the part to keep: two positives, a rule built to
explain both, shipped without a case that could have falsified it. The liveness
test was the falsifiable version and something cheaper was substituted for it.
A rule that explains every case you have is not evidence -- it is a description
of the cases you have. Find the case that would break it BEFORE writing it down,
and if you cannot construct one, say the rule is untested.

## BFME overloads on integer signedness where the reference has one function

Two sightings, and -- given the entry immediately above -- recorded as an
observation rather than a rule, with no case yet sought that would break it.

    ?setFlashColor@Drawable@@QAEXH@Z   at 0xD0    Int
    ?setFlashColor@Drawable@@QAEXI@Z   at 0x164   UnsignedInt
    ?winSetLayout@GameWindow@@QAEH...  at 0x00478E10
    ?winSetLayout@GameWindow@@QAEX...  at 0x0026ED70   (return type, not a parameter)

MSVC encodes both the parameter types and the return type, so these are distinct
symbols sharing a source name. The practical consequence is the one already
recorded for winSetLayout: a header declaring one spelling cannot serve the TU
that defines the other, and a matched row for one says nothing about the other.

## THE MARKER QUEUE, MEASURED END TO END

273 destinations, one compile each. This supersedes every estimate:

    5,182  markers with NO ledger row -- a body present in the tree with no
           matched retail address behind it. Not foldable by anything. This is
           AUTHORING work, and it is the overwhelming majority of the queue.
      792  miss verdicts; dropping 5-byte jmp stubs, whose miss counts are
           meaningless, leaves ~493 real ones
      217  errors -- the symbol is not in the destination's object at all
           (donor-private spellings, ICF twins)
       46  MATCH, collapsing to 16 distinct symbols, of which 10 landed

The six MATCHes that did not land each failed differently, and the distinctions
matter: two needed per-symbol `--apply`; two have no cluster at all so the fold
is not expressible as a merge; one was already home (donor equals destination);
one has its donor under `reference/`, which is a different decision entirely.

The ten destinations judged "at floor" were screened too: ZERO MATCHes. That
call is now measured rather than assumed.

**Do not budget a lane against the marker count.** The queue is ~5% foldable and
~85% unclaimed bodies.

## A small miss(N) is a CLASSIFICATION, not a distance

Every miss(1) and miss(2) opened fell into one of four buckets, and the number
does not tell you which:

  * **A constant BFME changed.** WeaponSet's three miss(1)s are all "loop to 4"
    where ZH's WEAPONSLOT_COUNT is 3 -- BFME's weapon set has a fourth slot.
  * **A field offset.** `User::setName` is `add ecx,0x4C` against our `add ecx,4`:
    one byte, seventy-two bytes of layout behind it.
  * **A TRUNCATION -- the one most easily misread as drift.**
    `W3DSnowManager::update`'s three bytes are where OUR body ENDS and retail
    keeps going: `mov ecx,esi / call / mov ecx,esi / pop esi / add esp,4 / jmp`.
    BFME's snow update does two more things per frame than the ZH body. A miss(3)
    at the end of a row is a MISSING FEATURE, not an offset.
  * **Two facts at once.** `WorkerAIUpdate::isCurrentlyFerryingSupplies` has
    deltas +0x14, -4, -4 across two classes. No single lever closes a miss whose
    deltas disagree.

Three checks before costing a miss: is the row a 5-byte jmp stub (its miss count
is meaningless); do the diffs sit at the END of the row (truncation, not drift);
do the deltas agree (one lever, or several).

## A register-allocation wall moves on a TU FLAG, never on a source rewrite

The zero-register hoist is a class now, not a one-off -- it has blocked three
bodies. The instructive part is what beat it the one time it was beaten: a TU
FLAG (a string shim on the cl line), not a source shape. Seven separate source
rewrites of `RequestSetName` produced nothing at all.

That is the cost rule. When a body is exact in size and structure and differs
only in which registers hold which values, rewriting the source is close to
free of information: MSVC's allocator is responding to what the TU declares and
includes, not to how you spell the statement. Reach for the cl line -- a shim,
an inliner flag, an STLport knob -- or record the wall and move on.

Two corollaries already in this file, now with a shared cause: a fresh view can
make a body WORSE by moving allocation more than the corrected offset was worth
(objectChangedTeam, 62.4% to 29.7%), and six correct offsets applied at once did
exactly that. Same mechanism, opposite direction -- allocation is a TU-level
response, so TU-level inputs are the only reliable lever on it.

## TWO defects can MULTIPLY to a pass: six green GameWindow rows are false

The worst case in the tree, and the one that most needs stating plainly. Six
currently-MATCHED rows are green because a wrong row->address BINDING and a
wrong LAYOUT cancel each other. Fix either alone and all six go red.

Retail emits NINE draw-data setters, three groups of three, with array bases
0x48 / 0xB4 / 0x120, element stride 0x0C and fields at +0x00 Image, +0x04
Color, +0x08 BorderColor:

    0x00478FE0 byte 0x48    0x00479010 byte 0x4C    0x00479040 byte 0x50
    0x00479070 byte 0xB4    0x004790A0 byte 0xB8    0x004790E0 byte 0xBC
    0x00479120 byte 0x120   0x00479150 byte 0x124   0x00479190 byte 0x128

This paragraph first said SIX, and that the three `winSet*BorderColor` bodies
were never emitted. **That was wrong** -- they exist, parked under placeholder
`?dup_004790XX@@YAXXZ` names. See "CORRECTION: the GameWindow BorderColor
bodies DO exist" below for how they were found and for what the mistake
teaches. The cancellation described here is unaffected: it is a uniform
one-field rotation across all nine rows rather than six bodies with three
missing, which if anything makes it tidier -- there is no retirement to decide,
only a rebinding.

Every row in the family is bound ONE FIELD TOO HIGH. Our GameWindow is 4 bytes
short at the front, so our `.color` write lands on retail's `.image` byte and
our `.borderColor` lands on retail's `.color` byte. Verified against our own
object rather than inferred: our compiled `winSetEnabledColor` is
`lea [eax+eax*2+0x12]; mov [ecx+eax*4]` -- instruction for instruction retail's
`winSetEnabledImage`.

**So the qualifier this file has needed all along:** a matched row proves the
offsets it COMPILES, never that the RIGHT FUNCTION compiled them. Where a class
is uniformly shifted and the fields are a contiguous same-size run, an
off-by-one-slot name binding is invisible to the gate, because the shift
supplies exactly the error that cancels it. "The already-matched rows are the
proof" holds only for offsets, not for identity.

The repair is in the LEDGER, not the header:

    winSetEnabledColor   0x478FE0 -> 0x479010
    winSetDisabledImage  0x479120 -> 0x479070
    winSetDisabledColor  0x479070 -> 0x4790A0
    winSetHiliteColor    0x479120 -> 0x479150
    the three BorderColor rows have NO retail body at all
    winSetEnabledImage and winSetHiliteImage were already correct

## A detector for mis-bound rows that offsets alone cannot find

An address claimed by **2+ distinct row names**, where **at least one is matched
and at least one is not**, AND the names are **same-family functions that cannot
possibly compile identically** -- so ICF cannot explain the sharing.

In the GameWindow cluster that flags exactly the three real defects and nothing
else. The fourth multi-named address there,
GameWinDefaultInput/GameWinDefaultSystem at 0x006CF680, is a genuine ICF fold of
two identical default handlers, and the family test is what separates it.

Ledger-wide there are **1032 addresses carrying 2+ names**. Most will be honest
ICF. The family test is the only cheap thing that distinguishes them, and this
class of defect cannot be found by reading offsets, because the offsets agree --
that is the whole problem.

The same defect nearly produced a second false green deliberately:
0x00478EB0 is claimed by both winSetPrev and winSetTooltipFunc; the body writes
0x1EC, retail's m_tooltip is at 0x1EC and m_prev at 0x1FC, and our class is 16
short there. winSetTooltipFunc is the true owner. Landing winSetPrev would have
authored a false green on purpose.

## A pad that must be UNDONE at every call site is a wrong layout

`vertmaterial.h` carried a deliberate `unsigned int _bfme_vmat_v0` pad ahead of
MaterialOld. `MeshMatDescClass_Do_Mappers_Need_Normals_Thunk.cpp` then carried
two `reinterpret_cast<unsigned char *>(mtl) - 4` adjustments, subtracting that
pad back off every VertexMaterialClass pointer before calling through it.
Deleting the pad makes those casts unnecessary and the body matches.

Treat a correction that has to be reversed at each use as evidence against
itself. It is the same tell as a matched TU declaring a local class to work
around a shared header: the workaround marks where the shared artefact is wrong.
`meshmatdesc.cpp` had independently reached the same conclusion from different
evidence and worked around it by including the reference header through angle
brackets -- two separate per-file workarounds for one wrong dword.

## Enumerate a header's includers with a SOURCE GREP, not the deps sidecars

The sidecars record what THIS worktree has compiled, not what includes what. A
per-file enumeration built from them missed
`MeshMatDescClass_Do_Mappers_Need_Normals_Thunk.cpp` entirely, and only the full
gate caught it. Use the sidecars to learn which header a TU actually opened;
use a grep over sources to learn who includes a header at all.

## `g_bfme5ParseVtable` names three different globals

`?g_bfme5ParseVtable@@3PAXA` resolves to three addresses -- 0x0108B1B8,
0x0108D638 and 0x0108D748 -- one for each of `bfme5MakeParseNodeA`, `B` and `C`
in `Code/GameEngine/Source/Common/Bfme5NodeMakers.cpp`, each at +0x11.

One placeholder name standing for three distinct vtables is exactly what the
DIR32 check exists to catch, and it fails the gate for the whole tree: a header
or shim change makes the pre-commit hook run the FULL gate, so this blocks every
lane, not only the one that introduced it. Three distinct globals need three
distinct names; a shared placeholder asserts they are one object.

## The DIR32 check only fires once a SECOND base exists

`Bfme5ReadyQueue.cpp` declared `extern PartitionManager *ThePartitionManager;`
locally in the TU and used it twice in `bfmeIsShrouded` -- a shroud predicate
reaching the shroud manager through the wrong name. The check caught it within
hours, which is the argument against ever whitelisting it.

But note the limit honestly: **it catches a misnamed global only once a second
base exists.** A new file that declares the extern itself and is the ONLY
reference to that name passes silently while being just as wrong. The
declaration being TU-local is what makes this recurrable -- nothing in the tree
prevents the next new file from doing the same, and the ledger's own pin for the
correct name does not help, because the wrong name never has to resolve against
it.

If this recurs a third time, the fix is a positive check -- every global a TU
declares `extern` must have a symbols.csv pin agreeing with the address its
references resolve to -- not another rename.

## `this` is not always the entry pointer: measure the base, and use a control

`GarrisonContain::getApparentControllingPlayer` is 88B/88B with nine differing
bytes, all member offsets. The first views moved every offset by a constant
-0x20 rather than fixing anything, which is what proved the mechanism: MSVC
treats `this` in that method as **the entry pointer minus 0x20**, so a
`this`-relative view needs +0x20 on the number you want to see in the
instruction.

Two things made that a measurement rather than a guess. The file's own
`findConditionIndex` already documented the same base ("m_object at module+0x08")
-- independent corroboration already sitting in the file. And the fourth view,
on the `observingPlayer` PARAMETER, needed no adjustment and landed first time,
which isolates the effect to `this` specifically. **Keep a view that should not
need the correction as a control**; without it, a uniform shift looks like a bad
view rather than a different base.

Corrected targets: m_object at this+0x08, hide flag at this+0x9b5, m_originalTeam
at this+0xd4, Player's default team at observingPlayer+0x230.

## SYMBOLIC vs VIEW-BASED: the sharpest form of "a matched row proves bytes"

The rule that made Squad decidable, in the form it was actually used:

**A symbolic matched row is evidence about the header, because the COMPILER
chose the number. A view-based matched row is not, because the AUTHOR did.**

Squad.cpp has two matched rows naming the member symbolically -- `m_objectIDs.size()`
and `m_objectIDs.push_back(objectID)`, no view anywhere near them:

    getSizeOfGroup  0x000ED420  mov eax,[ecx+0x0C]; sub eax,[ecx+0x08]; sar eax,2
    addObjectID     0x0036B770  mov eax,[ecx+0x0C]; mov edx,[ecx+0x10]; add ecx,8

start +0x08, finish +0x0C, end_of_storage +0x10 -- this tree's two-vptr layout
exactly. So retail's Squad IS our Squad and the +0x04 claims are the error, which
is the liveness test answering positively: retail does use our offset.

That indicted a row nobody was looking at. `?removeObject@Squad@@` at 0x0018B620
is matched only through an inline `struct BFMESquad { char pad[0x04];
VecObjectID m_objectIDs; }`, and its retail bytes `lea edi,[ecx+0x04]; mov
esi,[ecx+0x08]` agree with that view while contradicting both symbolic siblings.
It sits one body after 0x0018B520 and both read a container at +0x04 -- siblings
of each other, not of Squad.

## CORRECTION: the GameWindow BorderColor bodies DO exist

An earlier reading concluded that nothing writes +8, so the three
`winSet*BorderColor` functions were never emitted and their rows had no retail
body. **That was wrong**, and acting on it would have thrown away three genuine
claims. They are emitted, and already parked under placeholder names as
`?dup_004790XX@@YAXXZ` in GameWindowBorderColorSetters.cpp.

Nine prologues in 0x478F80..0x4791E0, three groups of three, element stride 0x0C:

    0x478FE0 base 0x48    0x479010 +0x4C   0x479040 +0x50
    0x479070 base 0xB4    0x4790A0 +0xB8   0x4790E0 +0xBC
    0x479120 base 0x120   0x479150 +0x124  0x479190 +0x128

Fields are +0x00 Image, +0x04 Color, +0x08 BorderColor, so the true mapping is
Image/Color/BorderColor in address order within each group. Every Color and
BorderColor row is one field low; only winSetEnabledImage and winSetHiliteImage
are correct. A uniform one-field rotation -- the VertexMaterialClass shape again,
and byte-verifying for the same reason.

The lesson beyond the correction: **"no body writes that offset" is a claim about
what you enumerated, not about what exists.** Nine bodies were in one address
range and only six had been listed. Count the prologues in the range before
concluding a function was never emitted.

## Two placeholder conventions, for two different things

  * `?j_XXXXXXXX@@YAXXZ` -- an ILT thunk claimed by ADDRESS, 5 bytes, no identity
    claim. 1,048 of these in gen_small.
  * `?dup_XXXXXXXX@@YAXXZ` -- a REAL BODY whose identity is unknown or disputed,
    parked under its address.

So a mis-anchored row is re-homed to whichever fits its SIZE: a 5-byte jmp stub
becomes `?j_`, and a 38- or 62-byte real body becomes `?dup_`. Neither throws
away the byte coverage, and neither asserts an identity the evidence does not
support.

## Re-homing a mis-anchored row: the recipe, and why `object-symbol=` is the trick

Retiring a false row throws away real byte coverage. Re-homing keeps it:

  1. retire the false-named row and tombstone it in `reverse/deleted_rows.csv`
     with the evidence, so a union merge from an older branch cannot restore it;
  2. `add_match '?j_00048b9e@@YAXXZ' 0x00048B9E 5 <donor> \
         --notes 'object-symbol=<the symbol the donor actually emits>;...'`

**`object-symbol=` is what makes it work.** The row's NAME becomes
address-derived and claims nothing, while the byte comparison still knows which
emitted symbol supplies the bytes. Coverage unchanged, identity claim gone, no
file deleted. AutoHealBehavior verified as it stood: `Functions: OK 1/1 matched`.

Deletion is the fallback for the case re-homing cannot reach -- the three
AsciiString rows went that way because their donor held nothing else, and
`verify_source_claims` forbids a row-less .cpp. That took the matched total
161787 -> 161784, stated in the commit message. **An honest decrease beats a
total you cannot trust**, and the tombstone reason carries what the false rows
were hiding: retail's TeamsInfoRec::addTeam and ::removeTeam are UNLOCATED.

## The FILE name describes the C++; the ROW name describes the bytes

They are allowed to differ, and after a re-homing they must.

`AutoHealBehaviorCtorThunk.cpp` keeps its name even though its row is now
`?j_00048b9e@@YAXXZ`, because the file genuinely does declare AutoHealBehavior's
constructor -- that declaration is precisely what makes the compiler emit a
tail-call thunk of the right shape. The name is accurate about the SOURCE. What
was false was the ROW's claim that those five bytes ARE that constructor, and
that claim is what got removed.

So do not rename these donors. Renaming rewrites every row's `source` in a
union-merged ledger for a benefit one comment already delivers -- and the
comment is mandatory: without a line saying the class name is there to shape the
emitted thunk and is not an identity claim, the file is a trap for the next
reader.

## Worktrees do NOT isolate the stash stack

The one-lane-per-worktree rule protects the working tree and the index. It does
not protect `refs/stash`, the reflog, or the object store -- those are one per
REPOSITORY, shared by every worktree of it.

A lane stashed WIP by explicit path, and while it worked, another lane pushed a
stash labelled "HOLD until dir32 green". That put the HOLD stash at `stash@{0}`,
so the first lane's subsequent bare `git stash pop` applied SOMEONE ELSE'S held
work into its tree and dropped their stash ref.

Recoverable, and worth knowing how: back up the working state, re-create the
dropped ref from its commit with `git stash store -m '<original message>'
<sha>`, return the affected files to HEAD, then pop your own by explicit ref.

The rule is in AGENTS.md now: never `git stash pop` bare, and prefer a patch
file or a temp branch, which no other lane can consume.

**Corollary for push_retry.sh:** it refuses a dirty tree and says so, which is
correct -- another lane's uncommitted edit is not yours to rebase over. Do NOT
add `rebase.autoStash`; autostash pushes and pops through the same shared stack,
so it reintroduces exactly this race. Use
`git -c rebase.autoStash=true pull --rebase` deliberately and only when you have
read the stash list, or better, wait for the tree to be yours.

## ICF needs identical RELOCATIONS, so relocations decide it -- not size
**FALSIFIED AS A RULE ABOUT IDENTITY. Retail folds constructors that store
DIFFERENT vftables. This test says whether two bodies are byte-identical; it
does NOT say whether a shared address is a mis-anchoring. See "a call site beats
stub topology" below. It cost five wrong retirements.**

The ambiguous middle of the mis-anchored list was framed as a size question:
bodies between 32 and 130 bytes where an ICF fold is a live alternative to a
mis-anchoring. Size is the wrong axis. **ICF folds bodies that are identical
INCLUDING their relocations**, so two constructors that store different vftables
cannot fold however small and however similar their code.

That makes it decidable rather than a judgement call:

  * read both candidate bodies' relocation lists (`read_object_symbol_bytes`
    returns `(body, relocs)`);
  * if the targets differ -- different vftables, different string literals,
    different callees -- ICF is IMPOSSIBLE and a shared address is a
    mis-anchoring, whatever the size;
  * if the targets are identical, an ICF fold is genuinely possible and the row
    may be correct bookkeeping that merely looks odd. Log it, do not convert it.

This is the same instrument that named the two vftables behind the
`/DBFME_MODULE_NO_MPO` diagnosis. When a diff or an identity question lands on a
masked DIR32, read the relocations rather than the disassembly.

## Caller counts go silent exactly where the topology test earns its keep

All four constructor thunks re-homed in one pass had caller counts of **1
against 1**. The histogram that cracked the AsciiString case -- 6,947 sites
against one -- says nothing at all here.

That is the argument for keeping both discriminators rather than the one that
fired first. Caller counts settle a case where an import thunk serves the whole
binary; the topology test (incremental linking emits ONE thunk per function, so
a body already matched under name B with exactly one stub reaching it owns that
stub) settles the case where both counts are one, which is most of them.

## Re-homing is duplicate-prone in a way ordinary folds are not

A retire-plus-add-match writes the SAME ADDRESS twice in one commit, so any
concurrent rebase has two rows to union. A duplicate `?j_00048b9e@@YAXXZ`
appeared exactly this way and pre-push caught it -- the documented case, fixed
with ledger_io keeping the first, never dedup_csv.

Expect it on every re-homing commit and check `check_csv` before pushing rather
than after the rebase surprises you.

## Quote the heredoc when a commit message contains backticks

`git commit -F -` with an unquoted `<<EOF` lets the shell execute backticks and
`$` inside the message; two phrases vanished from one message this way and a
word from another. Use `<<'EOF'`. Amend before pushing if you catch it; do not
force-push over shared history to fix prose if you do not.

## A detector that goes quiet has finished; bucket the leftovers, do not list them

The ILT identity sweep ran to exhaustion: five rows re-homed, three retired, and
the 62 survivors of the unique-stub test bucketed by the RELATIONSHIP between the
claiming name and the body's name:

    25  FX getClass<T> -> getInstance<T>                       real tail call
    13  ~ConcreteModuleTemplate<Tag> -> ~<Name>ModuleTemplate  one dtor, two spellings
     4  same-class pairs reading as genuine tail calls
     5  cross-class constructors -- the shape that was real
    15  cross-name oddities needing individual reading

**47 of the 62 need nobody.** That count is the artefact worth having: a bucket
tells the next agent which rows to stop re-deriving, where a raw list of 62
invites the whole investigation again.

And the honest limit of the instrument, from running it to the end: **the
topology test is decisive when the two names are UNRELATED and the body is
large, and it stops separating cases as soon as the names are related** -- a
template spelling against a typedef spelling, a method against its own class's
operator=, a getter against its own instance accessor. It found the real defects
and then went quiet. That is correct behaviour for a detector, but it means the
remainder is judgement rather than screening, and should be labelled as such
instead of left looking like a backlog.

Every survivor that shared the acted-on shape had its own reason to stop:
`??0SupplyWarehouseCripplingBehavior@@` points at a 154-byte body claimed by SIX
names, which is either a large ICF group or a defect bigger than one row;
`??0SimpleParameterClass<int,0>` points at a body claimed by two ClientBehavior
constructors from one file, an ICF twin pair.

The sharpest thing left is a multi-name case rather than a topology one:
**0x0000B9CE**, where `?getClassMemoryPool@ObjectDefectionHelper@@` and
`?Clear@VectorClass<TangentsClass>@@` -- two entirely unrelated names -- both
claim a stub jumping to a 74-byte `?reset@NetCommandList@@`.

## A finding is only as durable as the instrument that produced it

Two of the most productive scripts in this effort -- a batch screener that made
a 273-destination sweep affordable, and a multi-name-per-address detector that
rediscovered a known defect unaided from 1,041 addresses -- were reported as
"built and validated" while living in a session scratchpad. The commit named as
building the detector changed one line of `re_attempts.log`.

The findings landed. The instruments did not. That leaves numbers in a log that
nobody can reproduce, extend, or check -- and the scratchpad directories on this
machine hold a dozen dead one-off scripts from earlier sessions (`vtab.py`,
`vt2.py`, `vt3.py`, `vorder.py`) that were each presumably worth something once.

Two rules. **Land the instrument in the same stretch as the finding it
produced**, with tests, or the finding degrades to an anecdote the moment the
session ends. And when reporting, **say "built, not yet committed" when that is
what happened** -- a table of commits is the thing a reader is least likely to
re-derive, and the difference between planning around a tool and planning around
an idea is total.

Ephemeral scratch is correct for a one-off probe answering a question you will
never ask again. It is wrong for anything that produced a number you reported.

## A marker must be ADJACENT to its definition: explanation goes ABOVE it

`find_declared_unmatched` reads a marker as declaring the body that FOLLOWS it.
Twenty lines of explanation inserted between the marker and the code made the
hook read the body as undeclared, and the pre-commit failed.

    // why this row is re-homed, at whatever length              <- explanation
    // ?dup_0018b520@@YAXXZ present-unmatched                    <- marker
    void Squad::isOnSquad(...) { ... }                           <- the body

Never between the marker and the code. This bites precisely when documenting a
re-homing in place, which is exactly when the explanation is longest.

## batch_screen's safety contract is the INVERSE of marker_screen's

marker_screen clears a marker to ask its question, so it MUST restore it, even
on BaseException. batch_screen must never have cleared one, because a marker is
a comment and cannot change what the compiler emits -- which is the whole reason
one compile answers a destination's entire marker list.

So its first test is that contract: **it never writes** -- not the source, not
the ledger. If it ever starts editing to get a better answer, it needs the
restore machinery, and that test should fail loudly rather than be relaxed. Two
tools, opposite invariants, each pinned by the test that would catch the other's
bug.

Its other tests encode things this effort learned expensively: a truncated label
resolves only when unambiguous (two overloads sharing a prefix return
`ambiguous`, never a guess); an unknown label is REPORTED, not skipped, since
~2,000 of ~3,000 markers name no row and that is the largest bucket; a miss
reports its byte count; and `moves` counts only rows a marker HERE names -- the
miscount that turned one lane's eleven ready rows into two.

## CORRECTION: compare relocation STRUCTURE, not relocation NAMES

"Compare the claimants' relocation targets" was the instruction given, and the
obvious reading of it is actively misleading. Measured against 1,041 multi-name
addresses:

  * **Target NAMES flags 367 and is useless.** Two classes' constructors name
    different vftables -- but that is a masked DIR32 the byte comparison never
    sees, so this flags every template and module family in the tree.
  * **REL32 call targets only gives 225 and still over-flags.** One function
    under a C and a C++ decoration (`?png_handle_IHDR@D3DX@@` against
    `_png_handle_IHDR@12`) and per-instantiation template symbols resolve to
    different names for the same call.
  * **Structure is decisive: 11.** Mask every relocation site to zero in BOTH
    bodies, then compare the remaining bytes AND the `(offset, type)` list.

The reasoning is the important part: two ICF-folded bodies **are the same
bytes**, so their relocation SITES must coincide however differently our objects
happen to name the targets. Names are a property of our compile; sites are a
property of the code.

Final classification of 1,041 multi-name addresses: **965 real folds, 65
all-placeholder, 11 that cannot be one body.** 976 of 1,041 need nobody.

## Five of the eleven are GameWindow, and four were new

    0x00478EB0  winSetPrev           | winSetTooltipFunc
    0x00478E40  getEnergyBonus       | winGetPrevInLayout
    0x00478E30  getEnergyProduction  | winGetNextInLayout
    0x00478710  getContain           | winGetEnabledTextBorderColor
    0x00478490  getFrame@GameLogic   | winGetStyle

Each pairs a GameWindow accessor with an unrelated accessor of a DIFFERENT
CLASS at one address, matched claimants on both sides. The detector was told
nothing about GameWindow and rediscovered 0x00478EB0 unaided, which is the
reason to trust the other four.

**The six of the eleven deliberately NOT called** are large trivial-constructor
groups -- 24 names at 18 bytes, 40 at 9, 17 at 16 -- where at least one member
compiles differently here. The likelier fault is our compile of one member than
a 40-name group being wrong. A detector saying "these cannot be one body" is
evidence about the group, and when the group is that large the evidence points
at the odd member first.

## The funclet self-heal searched the wrong section, and 18,690 rows cannot heal at all

`funclet_candidates` re-identified a renumbered `$L` pin by searching the section
holding `__ehhandler$<parent>`. But MSVC 7.1 gives that handler a COMDAT OF ITS
OWN, while the `$L` funclet bodies stay in the PARENT function's section. In
StagingRoomGameInfo.obj the parent is section 342 and its handler 343, and all
eighteen ehhandlers in that object split the same way -- so the search returned
no candidate and the row died on its stale pin.

The symptom is opaque: a one-line view shifts two pins by two and the build stops
on `ValueError: symbol not found in object: $L70459`, naming a compiler-local
label and nothing else, while the body sits in the object as `$L70461`. Fixed by
searching the parent's own section as well as the handler's; both paths still go
through `holds_funclet` and a group of look-alikes still fails loudly, so this
widens where evidence is sought without picking anything on faith.

**RETRACTED: there is no tree-wide tripwire.** This entry claimed 18,690
parent-less `gen-funclet` rows were a hazard under every header change. Scoping
the back-fill answered the question instead of starting it. Of 20,052
`gen-funclet` rows:

    hand-edited sources    1,361 rows -- ALL carry parent=, zero without
    generated sources      18,689 without, 2 with   (gen_small/, gen_asm/)

Every parent-less row is in a GENERATED TU. Checked against git rather than
inferred: before the StagingRoomGameInfo fix there was exactly ONE parent-less
funclet row in a hand-edited TU in the whole tree, and that was the one that
froze the build. Someone had already done the annotation everywhere else; the
last gap is now closed.

The error is worth keeping: a tree-wide hazard was inferred from one instance
without checking how the instances were DISTRIBUTED. Alarm is as much a failure
of measurement as complacency, and it is the easier one to feel virtuous about.

What survives is a REGENERATION risk, not an edit risk: if whatever produces
`gen_small` re-emits those TUs with different label numbering, 18,689 rows go
stale at once and none can self-heal. Not urgent, not blocking, worth someone's
judgement before a regeneration.

The back-fill method, if it is ever needed: build the TU, find the `$L` symbol
the pin names, record the non-`$L` symbol sharing its section, refuse any section
with more than one candidate owner.

## Two cheap screens that save a build

**A donor declaring a class with a method it never defines: the mangled name IS
the pin.** `ThingTemplate::parsePrerequisites` reaches retail only because its
donor declares a fake `PrereqVector` with an `erase` it never defines -- retail's
`clear()` calls a range-destroy helper where our readable `m_prereqInfo.clear()`
calls STLport's `vector::erase`, a different function. Folding it would mean
importing that fiction into a readable TU to gain one file. Grep the donor for a
declared-never-defined method before spending a build.

**A masked compare can say MATCH while build.sh says FAIL**, because masking
hides relocation TARGETS as well as addresses. A screen is a filter; a fold is
only verified by build.sh.

## Withdrawing a wrong rule about a shared tool

A lesson was logged saying `merge_cluster --apply` discards uncommitted edits to
the destination. It is wrong and was withdrawn: a later `--apply` ran over an
unstaged view in StagingRoomGameInfo.cpp and the view survived. Something else
reverted the earlier edit and the cause was never established.

The rule kept is the defensive one -- apply the view after the merge and grep
that it is still there. Worth the retraction: a wrong rule about a SHARED tool
has every other lane working around behaviour the tool does not have, which is
more expensive than the original confusion.

## The two identity detectors are COMPLEMENTARY: neither subsumes the other

The natural assumption is that the newer structural detector replaces the older
thunk-topology one. It does not, and `0x0000B9CE` is the proof.

That address carries four names -- three `?Clear@VectorClass<...>` instantiations
and `?getClassMemoryPool@ObjectDefectionHelper@@` -- and `multi_name` classifies
it as a genuine FOLD. Correctly: all four are 5-byte jmp thunks whose only
differing content is the masked rel32, so **structurally they really are
identical bytes**. It was predicted to be the detector's first confirmed hit, by
two people, and it was not.

    a STRUCTURAL comparison cannot separate thunks
        -- every 5-byte jmp is structurally identical to every other
    a THUNK-TOPOLOGY test cannot see a wrong field offset
        -- it only asks which stub reaches which body

So run both. `multi_name.py` finds defects where the offsets agree;
the unique-stub topology test finds mis-anchored ILT stubs. Each is blind
exactly where the other sees.

## A detector that CLOSES a question is worth as much as one that opens one

The 69-byte body shared by `??0DestroyDieModuleData@@` and
`??0KeepObjectDieModuleData@@` -- the ambiguous middle that was deliberately left
alone for hours because ICF was a live alternative -- classifies as a **real
fold**: identical masked bytes, identical relocation sites. Logged `refuted`.

That pile is correct bookkeeping rather than odd-looking bookkeeping, and it
comes OFF the suspect list instead of staying uncertain forever. "Twelve rows we
chose not to touch" was the right call at the time and is now a closed question
rather than a standing doubt. Prefer the instrument that can return a negative.

## Byte-verification is evidence about bytes, in both directions

Address 0x0018B520 was UPGRADED from the placeholder `?d_0018b520@@YAXXZ` to
`?isOnSquad@Squad@@…` as a "byte-verified" identity, and has now been DOWNGRADED
to `?dup_0018b520@@YAXXZ` on the evidence of two symbolic siblings. **The same 38
bytes verified both times.**

The tombstone chain records the mistake being made and unmade, which is what that
file is for. A byte-verified upgrade is not proof of identity either.

## An ICF POOL address is never identity evidence

A matched row whose address carries many names tells you only that your body
compiled to a shape many classes share. It says nothing about whose body it is.

`??0StringInfo@@QAE@XZ` at 0x0005C5D0 shares that address with **eighteen** other
constructors -- ArmorTemplateSet, ModuleInfo, Smudge, four DLNodeClass<>
instantiations, TeamsInfoRec. It is the generic "zero three pointers"
constructor, and our StringInfo lands in that pool precisely BECAUSE we made it
twelve bytes. The row is a binding to a pool the wrong layout fell into, and it
would read as proof that the layout is right.

`??_EStringInfo@@QAEPAXI@Z` at 0x0005E420 is the same, shared with five
HashTemplateClass<StringClass,...>::Entry vector-deleting destructors.

**The converse is the useful half: a UNIQUELY named row IS identity evidence.**
Retail's `~StringInfo` at 0x004368F0 is the only claimant of that address, and it
destroys exactly two members -- `lea ecx,[esi+4]` into one destructor, then
`mov ecx,esi` into a DIFFERENT one. Two members at +0 and +4, reverse order,
two different destructors: an AsciiString and a UnicodeString. That settled the
layout where the pool rows could not.

So before treating a matched row as evidence about a class, run one awk pass over
functions.csv for other names at its address. `tools/multi_name.py` answers it
directly. This has now cost two hypotheses -- check it before spending a build.

## BFME's StringInfo is 8 bytes, and a 12-byte one manufactures its own proof

`{ AsciiString label; UnicodeString text; }` -- no `speech` field, where ZH has
three members and this tree copies it. Three independent strands:

  * the uniquely-named `~StringInfo` destroys exactly two members (above);
  * `GameTextManager::reset` and `::deinit` both pass **8** as the element size
    to the vector destructor iterator `??_M@YGXPAXIHP6EX0@Z@Z` where our twelve
    bytes make us pass 0xc -- the ONLY differing byte in either body, 85/85 and
    137/137 at ndiff 1, with the destructor argument relocating to
    `??1StringInfo@@QAE@XZ` on both sides;
  * dropping `speech` reddens exactly two rows, and both are ICF pool members
    that prove nothing.

The circularity is the thing to notice: the twelve-byte struct is what puts our
constructor in a nineteen-name pool, and the pool membership then reads as
confirmation. A wrong layout can manufacture the evidence that appears to support
it.

## A this-ADJUSTMENT residue cannot be viewed, even in principle

The strongest form of "a view is only honest when the number it encodes is the
member's real offset from the pointer the compiler actually holds".

`WorkerAIUpdate::isCurrentlyFerryingSupplies` is entered with the
`SupplyTruckAIInterface` sub-object at +0x204, so retail's `mov eax,[ecx+0xe0]`
and our `[ecx-0x124]` differ by exactly that adjustment. A view written to force
retail's encoding would read `object+0x204+0xe0` instead of `object+0xe0` -- it
would **byte-match while reading the wrong member**, and the gate cannot tell the
difference. `RTS2DScene::draw` is the same in one instruction.

So where the residue is a this-adjustment from base-class ordering, the recorded
refusal is CORRECT and permanent, not a stale measurement waiting to be
overturned. Three written "cannot come home" verdicts were re-tested and all
three held; two held for this reason.

That is the sharpest statement of the trap this file keeps circling: **the gate
is blind to names AND to which object a displacement lands in.**

## `verify_source_claims` reports the LEDGER's status, not a byte comparison

Its stale-annotation complaint used to read "X is byte-verified matched from
this file", which sounds like proof. It is not: `matched_sources` is the ledger's
status column, and `merge_cluster --apply` sets that status without building. So
immediately after an apply the message asserts a verification nobody performed.

It cost a near-miss. A repointed row was believed proven, an overturned verdict
was almost written into a source comment, and the build disagreed. The message is
reworded now and pinned by tests -- it names the ledger as the source of the
claim and points at `./build.sh` as the thing that would settle it.

General form, and it has bitten twice today: **when a check's message and a
check's implementation disagree, agents follow the message.** check_csv's
duplicate hint was the other one. Fix the wording where it is emitted; docs do
not reach the moment of decision.

## BFME's LANMessage enum carries two extra types, and the enum is POSITIONAL

`LANAPI::setIsActive` stores the type constant directly and reproduces retail
byte for byte: the wire byte is 0x10 where a build from the reference enum
computes 0xe. Two additional message types sit ahead of `MSG_INACTIVE`.

Because the enum is positional, **every type after the two additions is
renumbered by two**. Two clients built from the two enums would not merely
disagree about inactive announcements -- each would misread every later type as
its neighbour two places down. The two extra types are not identified yet; only
that there are exactly two. Recorded in docs/measuring.md as behaviour.

## Validate a proposal by running the REAL consumer, not a reimplementation

The funclet back-fill tool does not merely resolve a parent and write it. For
each proposal it runs the actual `funclet_candidates` and requires it to recover
the funclet before the annotation is offered at all.

That is the right shape for any tool that writes ledger annotations another tool
consumes. A reimplementation of the consumer's logic can agree with the proposal
and disagree with the consumer -- which is exactly the drift that put a
measuring tool and an acting tool out of step earlier today, where merge_cluster
had the rule right and screen_cluster did not. Call the real thing.

## A THIRD kind of false green: the five-byte virtual-dispatch thunk

`0x00495580` is `8b 01 ff 60 0c` -- `mov eax,[ecx]; jmp [eax+0x0C]`. **No E9, no
jump target.** It was handed between lanes as an ILT stub and a ready-made
re-homing; it is neither.

**Neither detector can see this class.** The unique-stub topology test needs an
E9 to follow. The structural comparison cannot separate two forwarders to the
same vtable slot, because they genuinely are the same five bytes. So this joins
the E9 ILT jump and the local-replica body as a third way a row goes green while
naming the wrong function -- and it is the first one no instrument catches.

**What caught it was SIZE AGAINST SIBLINGS.** The three other
`reverseAnimateWindow` implementations in retail are 260 to 263 bytes --
SlideFromBottom 0x004966E0, SlideFromTop 0x00496260, SlideFromRightFast
0x00497760. A real one is not five bytes of forwarding. The row verified only
because its `object-symbol` pinned it to the first five bytes of an unrelated
function, and ANY method forwarding to vtable slot +0x0C compiles to exactly
those bytes.

That heuristic -- compare a row's size against its named family's siblings -- is
cheap, is in neither tool, and is the obvious fourth pass.

Re-homed to `?dup_00495580@@YAXXZ` rather than `?j_`: a real body of unknown
owner, not an ILT entry. `?j_` is for a 5-byte E9 claimed by address; this is
five bytes of something else.

## Re-derive a row handed over pre-diagnosed, from the bytes

The premise travelled between two lanes and a team lead and was wrong at every
hop: "a 5-byte ILT row whose destination already compiles it byte-exact." It was
not an ILT row, and `batch_screen` on the destination returns
`error symbol not found in object: ?init@ScriptActions@@UAEXXZ` -- the row's
`object-symbol` exists only in the donor, so a repoint could never have verified.

Ten minutes of reading bytes stopped a repoint that could not have worked. **A
diagnosis arriving from another lane is a hypothesis with a good prior, not a
finding**, and the cost of re-deriving it is far below the cost of acting on it.
This applies with most force to the relay in the middle: a lead passing a lane's
diagnosis onward launders it into fact.

## When two measurements of the same thing DISAGREE, the finding is the disagreement

The single most expensive one-line decision of this effort, and it is worth
stating as a rule because the reasoning felt entirely normal at the time.

An enumeration of the GameWindow draw-data bodies was run twice. A loose grep
returned 0x479040, 0x4790E0, 0x479190. An exact mangled-name grep returned
0x479010, 0x4790A0, 0x479150. Two answers to one question. The exact one looked
more trustworthy, the loose one was written off as an artifact in a single line,
and the report that followed claimed three retail bodies had never been emitted
at all.

**The exact grep reads the LEDGER's bindings -- which were the thing under
suspicion.** So a contradiction was resolved by trusting the very source being
audited, and the loose grep, which had stumbled onto the real bodies, was
discarded. All nine bodies exist; they were parked under `?dup_004790XX@@YAXXZ`
placeholder names, which is precisely why a search for the real names found
nothing.

Neither measurement is "the corrected one" until you know WHY they differ. A
discrepancy is data. Write off a discrepancy and you have chosen an answer
without reading the evidence that would have chosen it for you -- and if one of
the two methods reads the artefact you are auditing, it is the one to distrust.

## Log both hypotheses when one call site cannot choose between them

`DX8Wrapper::Set_Gamma` agrees on 482 of 568 bytes. Retail's gamma call pushes an
extra leading zero and uses vtable slot 0x54 where the d3d8 shim gives
`SetGammaRamp` two arguments at 0x48 -- which is the D3D9 signature shape.

The tempting conclusion is that BFME is a D3D9 title. It was NOT drawn, and the
reason is the right one: all 101 rows in `dx8wrapper.cpp` are matched and their
retail bytes call slots up to 0x178, several above 0x54, so the shim's ordering
is correct everywhere those rows touch. One call site cannot distinguish "the
shim mis-places this one method" from "this method goes through another
interface", so the log records both and picks neither.

A single observation that would rewrite a large shared assumption is exactly the
one to hold rather than bank -- especially when a hundred matched rows already
constrain the same artefact.

## A FOURTH false green: the adjustor thunk, and it has MORE real bytes than the others

    0x00C2787D   add ecx,0x194 ; jmp 0x0000D828
    0x0000D828   jmp 0x0005EE90   =   ??1AsciiString@@QAE@XZ

Eleven bytes that adjust `this` by 0x194 to reach an AsciiString member and
destroy it. Two rows claimed it -- `?addTeam@SidesList@@` and
`?removeTeam@SidesList@@`, neither of which is a string destructor; both forward
to `m_teamrec`. They matched because the jump is masked, so the only compared
content is the add-ecx immediate, and our `m_teamrec` offset happens to equal
retail's AsciiString member offset.

**Name it separately because it has MORE compared bytes than the other three** --
six bytes of real immediate, against a 5-byte jmp's one. That is exactly why two
rows could share it and look solid. **A comparison being partly real is not the
same as it being enough.** The question is never how many bytes agreed, but
whether the bytes that agreed could distinguish this function from another.

The four classes now: the E9 ILT jump, the local-replica body, the
virtual-dispatch thunk, and the adjustor thunk. Retail's
`SidesList::addTeam`/`::removeTeam` are UNLOCATED, exactly as TeamsInfoRec's pair
turned out to be -- the same family, found four hours later, in the finder's own
file, by its own detector's FAMILY refinement.

## Redo a stale ledger patch with the TOOLS; never replay it

A held patch stopped applying once `functions.csv`, `re_attempts.log` and
`reloc_names.csv` moved under it. The source half still applied cleanly and was
kept. The ledger half was **redone with `add_match` and `merge_cluster` against
the current ledger** rather than replayed.

That is the right split and the reason is specific: replaying a stale ledger
patch is how a union merge resurrects a retired row -- the patch reintroduces
lines the tombstone was written to keep out. The tools re-verify as they go and
operate on the ledger that exists, not the one that existed when the patch was
cut.

Hold source in a patch; hold ledger work as a list of tool invocations.

**Sharpened by using it: split by REPRODUCIBILITY, not by file type.** A held
shim change spanned `functions.csv`, which an unrelated commit also needed. The
right split was not source-versus-ledger but reproducible-versus-not: the merge
was one `merge_cluster` command, so it was RESTORED and re-run rather than held,
while only the hand-written source edits stayed parked. A new shim DIRECTORY is
untracked, so it survives a rebase untouched and needs no holding at all.

Ask of each piece: can I regenerate this with one command? If yes, let it go and
re-run it. Only what you cannot reproduce needs a patch.

## A call through an ILT thunk is PERMANENTLY unreachable from source

`GameSpyInfo::removeFromSavedIgnoreList` reads 118 of 118 bytes exact and the
gate still refuses it. Retail's call at +35 lands on `?j_000052bd`, an
incremental-link thunk in gen_small, where this tree calls the map's `erase`
directly. Every other call in the body matches.

**Nothing in the source chooses whether a call goes through an ILT stub.** That
is a property of how retail's binary was linked, so no view, no spelling, no
shim and no cl-line flag reaches it. Record it as permanent, not deferred --
this is the same category as the this-adjustment residue, not the same category
as a missing header fact.

**The consequence that changes how donors are read: an `__emit` body can be
LOAD-BEARING.** It encodes the rel32 that points at the thunk, which readable
C++ cannot express. So a naked dump is not always scaffolding waiting to be
drained, and "the destination already compiles this exactly" is not sufficient
grounds to fold.

The screen is cheap and belongs in front of every fold: for each direct call in
the retail body, decode the rel32, resolve the destination in functions.csv, and
look for a `?j_` name. Running it on `Set_Transform` cleared that fold before a
build was spent; running it after would have cost one.

## A near-miss filter hides the already-perfect

A scan built to surface rows within N bytes of retail filtered out `nd == 0`
along with the rows too far away to reach. Those are the CHEAPEST wins in the
tree -- rows whose destination already compiles them exactly and whose donor is
pointed at for no reason -- and the instrument was structurally blind to them
because it was built to find near-misses.

Two folds came out of noticing it: `UnicodeString`'s default constructor (9
bytes, no relocations at all, uniquely named) and
`DX8Wrapper::Set_Transform(Matrix3D)` (682 bytes, forty relocations, every one a
data reference to a named global -- so no direct call could resolve wrongly).

Check what your filter excludes at BOTH ends. A tool built to measure distance
will quietly drop the zero.

## A CALL SITE beats stub topology, and beats the relocation argument

Five rows were re-homed on this reasoning: ICF needs identical bodies WITH
identical relocations, so two module constructors storing different vftables can
never fold, so each stub must belong to whichever class owns the body it jumps
to. **Retail folds them anyway.** All five re-homings were wrong and are
retracted.

The evidence that settles it is the caller, not the stub:

    0x00048B9E  called by friend_newModuleInstance of AutoHealBehavior,
                SpyVisionUpdate, EMPUpdate and FireOCLAfterWeaponCooldownUpdate
    0x0002A379  called by FireWeaponWhenDamagedBehavior and MobMemberSlavedUpdate
    0x0001002D  called by BridgeScaffoldBehavior and ParkingPlaceBehavior

Several classes' factories calling ONE constructor stub is direct evidence of a
real fold. Each row was a legitimate member of an ICF group.

**The rule: the unique-stub test says which body a stub REACHES. It cannot say
whose that body IS when the body is shared.** A matched caller that names the
symbol outranks any inference from topology or from relocation structure. Check
callers before re-homing anything.

Note what still stands, because it was re-verified the same way rather than
assumed: the TeamsInfoRec trio at 0x0000D828 keeps its retirement -- its 31
matched callers are all destructor paths (`_Destroy`, `__destroy_aux`,
`_M_clear`, scalar-deleting destructors), which is what a string destructor's
thunk looks like and not what `addTeam` looks like. SidesList 0x00C2787D and
0x00495580 have no matched callers at all, so they rest on their own evidence.

## Retiring a row can break a matched row in ANOTHER file, and delta verify misses it

Retiring the AutoHealBehavior row broke `?friend_newModuleInstance@AutoHealBehavior@@`
at 0x00114200 -- a 96-byte matched body in a different file -- with
`unresolved call(s)`. **The delta verify that passed when the retirement landed
only built the donor.**

So: a retirement removes a symbol from the map, and any matched row that CALLS
that symbol loses its address. Before retiring, scan matched rows for calls to
the address. The full gate is the only thing that catches this after the fact,
which is an argument for running one after a batch of retirements even when each
one verified individually.

## Keep the cautious framing when a sharper rule arrives; run BOTH

Two lanes arrived at one rule today from opposite directions, which is why it is
worth stating twice.

One had the enumeration answer in hand from a loose grep, got a second answer
from an exact grep, wrote the first off in a line, and lost the central claim of
a report. The other had a cautious size-based framing for the mis-anchored rows,
dropped it when a sharper relocation-based rule arrived from the lead, and
retracted five commits.

**Both errors are the same shape: a disagreement between two methods was
resolved by picking one, rather than treated as the finding.** The correct move
in both cases was to run both and notice they disagreed -- which costs one extra
run and would have caught both.

A sharper rule does not supersede a cautious one until they have been run
against the same case and agreed. Where they disagree, the disagreement is data
about the rules, not noise to be resolved by preference.

## None of the four detectors establishes IDENTITY

Written into `size_outlier.py`'s own docstring rather than left as folklore,
because the natural assumption is that the newest tool replaces the rest:

    the ILT unique-stub test   needs an E9, and cannot say whose a SHARED body is
    multi_name's structural test  cannot separate two forwarders to one vtable slot
    multi_name's FAMILY rule   needs two names; most stubs carry one
    size_outlier               needs siblings implementing the same method

`0x0000B9CE` falls out of `size_outlier` and multi_name correctly does NOT flag
it -- four 5-byte jmp thunks are structurally identical bytes. Each instrument
is blind exactly where another sees, so **a clean run from one is not a clean
bill of health**, and a hit from one is a candidate rather than a verdict.

**A matched caller naming the symbol outranks every inference any of them
makes.** Check call sites before touching a row.

## size_outlier: both halves of the rule are load-bearing

A row is suspect when its body is SMALL AGAINST ITS FAMILY -- at most a quarter
of the median size of the same method name across three or more classes, median
itself at least 48 bytes -- AND the body TAIL-JUMPS. A forwarder delegates; an
implementation returns.

Size alone flags 104: a virtual method may legitimately have a tiny override,
and `?onEnter@AIBusyState@@` really is three bytes. Tail-jump alone flags every
honest thunk in the tree. Together: 14, with the tests pinning both boundaries.

Sharpest of them: `?duplicate@Condition@@` at 5B against a 167B family,
`?onEnter@AIInternalMoveToState@@` 5B against 122B, `?setPingString@GameSpyInfo@@`
8B against 102B, `?Free@DistLODClass@@` 5B against 50B.

## Never validate a layout fix against the CURRENT byte output

GameWindow.cpp's `winSetPrev` body is `m_prev = prev`. Under our short header
that writes +0x1EC, and retail's byte at that site agrees -- so the body **looks
correct and is not**. `m_prev` is at +0x1FC; +0x1EC is `m_tooltip`, which a
separate matched row already claims.

So when correcting a layout, write the definitions in terms of the MEMBERS and
let the corrected header supply the offsets. Checking the result against the
bytes the current header produces confirms the bug: the agreement you are
testing against is the thing you are fixing.

Same shape as the six draw-data false greens one level up -- a body right about
its member name and wrong about where that member lives, agreeing with retail
because two errors cancel.

## Two independent derivations meeting is the standard to reach BEFORE acting

The GameWindow renames had a byte proof from one lane -- thirteen getters, each
a single load, plus the setters read against them. They also had, from the other
lane and derived independently, three ALREADY-MATCHED rows landing on the same
offsets from the opposite side of the getter/setter pair:

    matched winGetPrev reads +0x1FC   <->  the void winSetPrevInLayout writes +0x1FC
    two matched rows read +0x200 as parent <-> the void winSetLayout writes +0x200
    matched winSetTooltipFunc holds +0x1EC, so +0x1EC cannot also be m_prev

**A matched getter and a matched setter agreeing on one offset settles a
member.** Neither derivation used the other's evidence.

Worth naming because today's retractions all share the opposite shape: a single
derivation, acted on, then falsified. The five re-homings had one argument; the
six-versus-nine setter claim had one grep whose disagreement with another was
written off. Where a structural change is about to be made on inference, the
question to ask first is not "how strong is my evidence" but "is there a second,
independent route to it".

## Two fixes paid off within the hour, on TUs nobody had flagged

Worth recording because both were made on one instance and doubted as
over-fitting at the time.

`verify_source_claims`' reworded complaint -- "the LEDGER records X as matched
from this file (status only -- not a byte comparison) ... either the marker is
stale, or the row was repointed here and has not been byte-verified yet;
./build.sh settles which" -- reached the same agent who had misread the old
wording, within the hour, and it went straight to clearing the markers instead
of inferring a match. Fixing the message where it is EMITTED rather than in a
doc is the whole difference.

The `funclet_candidates` section fix caught its first unknown case the same way:
GameText.cpp's `uw_00c222b6` renumbered from `$L37642` to `$L36977` under an
unrelated struct edit and HEALED rather than freezing the build. That is a TU
nobody had identified as affected -- the fix was made against one known case and
immediately earned its keep on another.

## The gate swallowed its own error text, and we diagnosed the silence twice

`build.py`'s `run(label, check)` catches `SystemExit` so every check reports
before the gate exits once -- a good design. But it discarded `exc.code`, and
`exc.code` is where a check raising `SystemExit("<explanation>")` puts its whole
diagnosis. So this:

    uw_00c054b0 (AIPlayer.cpp): $L85894 does not hold this funclet and 2 bodies
    in the parent's group match it equally ($L85915, $L86009). Byte evidence
    cannot tell them apart, so the gate will not pick one.

was reduced to "verify_functions did not produce a patch set" -- which reads as
a crash rather than a finding. **Two people independently concluded "race" from
the absence of output**, across three full-gate runs, before anyone called
`verify_functions()` directly to recover the text.

Fixed where it is emitted: the handler prints `exc.code` unless it is an int (a
bare exit status carries no diagnosis). Third time today a tool's MESSAGE, not
its logic, was the defect -- after check_csv's duplicate hint and
verify_source_claims' false "byte-verified" claim.

**The organisational half is worth as much:** the "everyone diagnosing everyone
else's file" problem is partly a reporting problem. Four consecutive reds
belonged to a lane other than the one that hit them, and this one took three
runs to attribute only because the tool ate the evidence. A check that names its
TU and its candidates hands the right lane the right file immediately.

## An ambiguous funclet heal is a REFUSAL, not a crash

Distinct from the withdrawn tripwire, which was `symbol not found in object`.
Here the pin renumbered, the self-heal searched the parent's group, and **two
bodies matched equally** -- so it declined to pick one. That is correct: byte
evidence genuinely cannot separate them, and guessing would anchor a row on a
coin flip.

RESOLVED, and not by re-anchoring: **the two candidates were never equal.**
`$L85915` is `lea ecx,[ebp-0x1c]; jmp <AsciiString dtor>` -- retail's own
instructions with only the jump target relocated. `$L86009` is a DATA table of
four label pointers, `$L78697` through `$L78700`, whose relocations cover ALL
EIGHT of its bytes.

`holds_funclet` masks every relocation site on both sides, so **a body with no
unmasked byte left compares equal to ANY target of its length.** The table was
not matching the funclet; there was nothing left of it to compare. The tie was
between one candidate carrying byte evidence and one carrying none.

Requiring at least one surviving byte separates them without choosing between
them, and the refusal on a genuine tie still fires. Three rows healed on it --
uw_00c054b0, uw_00c054b8 and uw_00c056a0 -- and AIPlayer.cpp went 42/42.

**This is the file's own "100 percent masked is not a pass" rule, which we apply
to folds, missing from the healer that does the same masking.** Before treating
an ambiguous heal as a re-anchoring job, check whether a candidate is fully
relocated: it is not a rival body, it is an absence of evidence.

## A CONSTANT delta is a shifted member list; a SCATTERED one is a different list

The cheapest first read on any near-miss, and it tells you which kind of work it
is before you spend anything:

  * **constant delta across every differing operand** -> the members are the
    same and sit at a uniform offset. View-or-shim work.
  * **scattered divergence** -> the member LIST differs. You need the class;
    no view reaches it.

`GameInfo::clearSlotList`, `W3DTreeDrawModuleData`'s constructor and
`evaluateAsVisibleCliff` are all scattered -- header items. `Image`'s
constructor confirms it from a third direction: it initialises two members BFME
does not have, and retail's EH state byte is **1** where ours is **2**, so BFME's
Image tracks one unwindable member where ours tracks two. An EH state count is
another readout of the member list.

## A frame-size difference is SHIM work by nature, not by preference

`ControlBarSchemeManager::init` is 177 bytes with every operand identical except
three, and those differ by a uniform **0x1BF0**. Our prologue reserves 0x243c
through `__chkstk` where retail reserves 0x84c, and the body constructs a local
`INI`. So **BFME's INI is 7152 bytes smaller than this tree's** -- almost
certainly a shorter line buffer.

The reason it cannot be a view: **a frame size is computed by the compiler from
`sizeof`**, so no cast, no local replica and no reinterpretation reaches it. That
is a different category from "a view would be ugly here" -- it is unreachable in
principle, like the this-adjustment residue and the ILT-routed call.

It is still TU-scoped, so it is a small contained shim rather than a shared
header change.

## Sweeping a suspected blind spot and finding it nearly empty IS the result

The `nd > 40` band was taken by hand precisely because the automated scan could
not see it -- the scan only ever surfaced rows whose difference was small enough
to be constants. The band contained one shim item and four header items, and no
views at all.

That closes the question rather than leaving it as a standing "we never looked
there". A negative sweep of a region you had reason to suspect is worth its cost;
what is not worth it is carrying the suspicion indefinitely.

## Every base class in a virtual family is a size outlier BY CONSTRUCTION

The dominant false positive in size-against-siblings, and it is structural
rather than incidental. `?Flush@Pipe@@` is 17 bytes **precisely because**
`?Flush@Base64Pipe@@` is 299 and does the work. The family median is computed
over the derived implementations, so a thin base-class body is not an anomaly --
it is what a base class in a virtual family looks like.

Five of six clearances in the call-site sweep were exactly that shape.

The clearing test, now in the tool: build the caller index once, then clear any
candidate whose callers include **the same method name in a different class**
(delegation) **or any method of its own class**.

That second clause has a mangling trap in it: **a constructor or destructor
names its class without a leading `@`** -- `??1DistLODClass@@`, not
`@DistLODClass@@` -- so a naive same-class check misses its own destructor. A
first pass did exactly that and reported `?Free@DistLODClass@@` as suspicious
when its only caller was `??1DistLODClass@@`.

## Silence is UNDECIDED, never confirmed

Of 14 candidates: 6 cleared, **7 with no matched caller at all**, 1 other, and
**0 confirmed defects**. The seven are undecided, not guilty. No caller is not
evidence of a defect -- it is the absence of the evidence that would decide, and
this tree has plenty of matched bodies nothing else matched calls.

There is a test pinning that specifically, because a verdict tally is exactly
where "no evidence" quietly becomes "evidence of".

## A detector that returns nothing across a full sweep has reported a result

`size_outlier` found zero defects in its own 14 candidates. That is not a
failure to report: it means the sweep is clean, and it says something honest
about the instrument -- **size-against-siblings is much weaker than the other
three**, because a small base-class body is normal where a 5-byte jmp thunk or a
one-name-three-addresses collision is not.

It earned its place on exactly one find, the virtual-dispatch thunk at
0x00495580, where the class has no siblings implementing that method so no
delegation explanation exists. One real find and a clean sweep is a fair account
of a weak-but-real instrument, and it is worth writing down rather than quietly
retiring the tool or quietly trusting it.

## THE MASKING RULE, generalised: ask what a fully-masked input compares equal to

Three places in this tree mask bytes before comparing, and the same failure hides
in each. Stated once, because it has now been discovered three times separately:

**Wherever you mask before comparing, an input with nothing left unmasked
compares equal to EVERYTHING of its length. That is an absence of evidence, and
counting it as a match is how the comparison certifies whatever you hand it.**

(This is the QUANTITY failure -- filter 1 above. It is distinct from the
LOCATION failure, where the bytes that survive masking are identical and the
discriminator sits in the masked region. Different diagnoses, different fixes.)

    the FOLD comparison    -- "a 100% masked screen is necessary, not sufficient".
                              openDataChunk scores 100% and still fails, because
                              masking hides the callee.
    holds_funclet          -- a DATA table of four label pointers, relocations
                              covering all eight bytes, tied with a real funclet.
                              Now requires one surviving byte.
    multi_name's STRUCTURAL test -- ** worth re-examining. ** It classifies
                              0x0000B9CE as a real fold because four 5-byte jmp
                              thunks are "structurally identical". They are --
                              but a 5-byte jmp has ONE unmasked byte, the E9
                              opcode. Every 5-byte jmp in the tree is
                              structurally identical to every other by that
                              measure.

The third is not necessarily wrong -- the ILT topology test covers that case, and
the two instruments were designed to be complementary -- but the verdict
"identical masked bytes and reloc sites, therefore a real fold" is carrying much
less evidence for a 5-byte thunk than for a 154-byte constructor, and the output
does not distinguish them.

**The cheap guard, wherever this pattern appears: report the number of surviving
unmasked bytes alongside the verdict.** A match on 1 byte and a match on 600 are
not the same claim, and today they printed the same way in three different tools.

## THE AMBIGUOUS-HEAL PROCEDURE (there was no "three-filter recipe"; here is the real one)

A phrase -- "re-anchor with the three-filter recipe" -- circulated between two
lanes and a lead as though it named a documented procedure. It did not exist
anywhere. What follows was derived from the data instead, and both filters are
demonstrated on real cases.

On an ambiguous heal, BEFORE reaching for a re-anchor:

**(1) Drop any candidate with no unmasked byte.** `holds_funclet` masks every
relocation site on both sides, so a body that is entirely relocations compares
equal to any target of its length. AIPlayer.cpp's `$L86009` is a data table of
four label pointers covering all eight bytes; it tied with `$L85915`, which is
retail's own `lea ecx,[ebp-0x14]; jmp <dtor>`. Requiring one surviving byte
separates them without choosing between them. **Implemented and tested.**

**(2) When the survivors differ only INSIDE the masked region, resolve the
relocation.** `uw_00c46f00` in LANGameInfo.cpp has three candidates that really
are byte-identical in everything `holds_funclet` compares -- `$L49714`,
`$L49524`, `$L49691`, each four unmasked bytes of `lea ecx,[ebp-0x14]; jmp`.
Their relocation TARGETS differ:

    $L49714 -> ??1UnicodeString@@QAE@XZ
    $L49524 -> ??1?$pair@$$CBVUnicodeString@@V1@@_STL@@QAE@XZ
    $L49691 -> ??1UnicodeString@@QAE@XZ

and retail settles it: decoding the jump in the target bytes gives 0x00047EFB,
the ILT `?j_00047efb@@YAXXZ`, which forwards to 0x0068E6D0 -- the **pair**
destructor. Only `$L49524` relocates where retail jumps. `load_symbol_map`
already builds the body-plus-thunks list this needs. **Demonstrated by hand, not
yet implemented.**

**(3) Only if more than one survives both filters is it a genuine tie** -- and
then it is a boundary finding, not a task.

**The two filters are DIFFERENT failure modes and must not be collapsed.**

  * **Filter 1 is about the QUANTITY of evidence.** `$L86009` did not hide a
    discriminator -- it had no unmasked region at all, so nothing about it was
    ever compared in either direction. This is the repo's own "a 100% masked
    screen is necessary, not sufficient", applied to a tie-break instead of a
    fold. Someone handed the filter-2 rule and AIPlayer's tie would go hunting
    for a discriminator inside a data table's relocations, and there is nothing
    there to find.
  * **Filter 2 is about the LOCATION of evidence.** The LANGameInfo candidates
    had IDENTICAL unmasked bytes; the only thing separating them was the
    relocation target, which is exactly what the comparison masks. Once two
    bodies have compared equal, the discriminator can only be in what was
    masked.

**And filter 2 does NOT mean "unmask it".** A pre-link addend genuinely is not
an address, so comparing those bytes raw compares nothing meaningful. Filter 2 is
a DIFFERENT OPERATION: resolve the relocation's SYMBOL to its ledger address,
thunks included, and compare that against the destination decoded from retail's
own bytes. A symbolic comparison where the byte comparison has nothing to say --
not the same comparison with masking switched off. That distinction is the whole
implementation.

## A second "permanently blocked" verdict overturned by measurement

`isUser@LANGameSlot` -- 132 bytes with "zero differences outside two REL32s" --
is logged as blocked, with the only escapes recorded as a new anchor or a
separate thunk TU. Its sole blocker was the `uw_00c46f00` tie above, and that tie
is resolvable. The verdict was a correct measurement of what was then visible and
is now simply out of date.

That is the second today, after the "cannot come home" AudioEventRTS verdict that
a padded local closed. **A logged verdict is a measurement, not a door.** Both
were overturned by looking at evidence the original measurement had no reason to
consult -- and in both cases the person who overturned it went and re-derived
rather than trusting the note.

## For a family of forwarders, THE CALLEE NAMES THE CALLER

No heuristic, no stub topology, no name comparison: decode the rel32, follow the
ILT, read the name. W3DTerrainVisual's water accessors are thin forwarders into
WaterRenderObjClass, so each is named by what it calls:

    0x00730A20 -> setGridChangeAttenuationFactors  = setWaterAttenuationFactors
    0x00730A50 -> setGridTransform                 = setWaterTransform
    0x00730AC0 -> setGridResolution                = setWaterGridResolution
    0x00730AF0 -> getGridResolution                = getWaterGridResolution

The ledger had `setWaterTransform` and `getWaterGridResolution` each one body
early. Both retired, tombstoned and re-anchored; W3DTerrainVisual.cpp 27/27.

This is the same evidence class that refuted five wrong re-homings earlier the
same day -- a call site naming the symbol -- used constructively rather than
defensively.

## A one-slot rotation MUST leave a hole: the spare placeholder is the proof

The strongest form an identity argument has taken here. A rotation cannot
consume its own displaced body, so it necessarily leaves one body spare -- and
in both confirmed cases the spare was sitting in the ledger under a generated
`?dup_` name.

    VertexMaterialClass   the colour-source rotation left Get_Diffuse_Color_Source
                          unclaimed, with a marker and no row
    W3DTerrainVisual      two one-slot rotations left ?dup_00730a50@@ and
                          ?dup_00730af0@@ holding the two real bodies

That converts "these two rows look wrong" into a positive prediction the evidence
either satisfies or refutes. **If you suspect a rotation and there is no spare
body, that absence is evidence AGAINST it** -- which is what makes this stronger
than any of the four detectors.

## Two pending pieces that both touch the ledger cannot be stashed independently

Sharper form of "hold source as a patch, ledger as tool calls". If two held
changes both write `functions.csv`, the second to land cannot be restored -- its
rows would point at bodies whose source changes are still parked. It has to be
REDONE with the tools against the ledger that exists.

So when work is queued behind a blocker, expect the ledger half of every held
piece but the first to be re-run once per landing ahead of it. Keeping that half
as a short list of tool invocations rather than a patch is what makes re-running
it cheap; one held piece had its four tool calls re-run three times.

## Making a broken thing HEAL is not the same as making it right

`uw_0045bea0` was the single parent-less `gen-funclet` row in a hand-edited TU in
the whole tree. It was annotated with a `parent=` so the healer could find it --
a reasonable-looking tooling fix, and the row then healed onto `$L70461`: twenty
bytes, all twenty relocated, matching on nothing. It stayed green for another
half day.

The row was already bogus before the annotation -- twelve `int3` through the
middle of a claimed funclet, two ILT slots, two `?b_` pins -- so the annotation
did not create the false green. **It extended its life by one heal.**

The failure is treating an unhealable row as a TOOLING gap without asking whether
the row deserved to heal. A row that cannot find its body is telling you
something; the first question is whether it should have one, not how to help it
find one.

## A fix that resolves cases DESTROYS the test cases for its own diagnostics

Sequencing insight, and it decided an ordering:

The refusal diagnostic (print each candidate with its surviving unmasked byte
count) and filter 2 (resolve ties by relocation symbol) were queued in that
order by default. But **filter 2 resolves ties, so after it lands there are
strictly fewer refusals left to exercise the diagnostic against.** Right now two
live refusals exist -- a no-candidate case and a genuine three-way tie -- and
building the reporting first means checking its output against real refusals
rather than synthetic ones.

So: **when one change removes instances of the condition another change reports
on, build the reporting first.** The general form is that diagnostics are
cheapest to validate while the thing they diagnose still happens.

## A refusal that prints nicely and PASSES is worse than a crash

The guard to write into any change that turns a crash into a report. A bare
`ValueError` killing the gate is unreadable but honest -- it stops. A refusal
that reports beautifully and lets the row through is the fallback path this
project forbids, wearing the costume of an improvement.

So when replacing a crash with a diagnostic, check the exit path explicitly:
does the gate still go red? That is the question, not whether the message reads
well.

## A HIGH surviving-byte count is not a pass either

The surviving-unmasked-byte column was added on the suspicion that some verdicts
rested on almost nothing. That suspicion was half right, and the half that was
wrong is the more useful half.

**Right:** 44 of 958 folds rest on three bytes or fewer, and printed identically
to the 694 that rest on sixteen or more. The column earns its place.

**Wrong:** no group rests on ZERO bytes, so the logic needed no change -- the ILT
topology test does cover the thunks, exactly as the complementarity argument
said.

**And the sharpest case is the inversion: both GameWindow draw-data families rest
on ALL 37 of their bytes and are still wrong.** Full byte evidence, nothing
masked, and the error is visible only in the NAMES.

So the column is a caveat and never a verdict. A low count says "this verdict is
thin"; a high count says nothing at all about identity. **Byte evidence, however
complete, cannot see a naming error** -- which is the day's central lesson in its
shortest form, and it took a tool printing 37/37 next to a wrong answer to state
it that plainly.

## Fourteen predicted addresses, fourteen hits, on full evidence

The GameWindow layout correction was verified the honest way: the shim added to
the cl line, the three definitions changed to return `Int`, the TU compiled, and
each emitted body compared against the RETAIL bytes at its PREDICTED address --
never against our own current output, which is where the false green lives.

    winSetEnabledImage    0x00478FE0  37B  rests on 37/37
    winSetDisabledBorderColor 0x004790E0 40B rests on 40/40
    winSetPrev            0x00478DD0  13B  rests on 13/13
    ... fourteen in all, every one MATCH

The 37/40 size split came out right although nothing in the derivation forced it
-- the kind of prediction that is hard to satisfy by accident.

**And the predicted trap sprang exactly as forecast.** `winSetPrev` does not
belong at 0x00478EB0; written in member names against the corrected header it
walked off the tooltip body onto 0x00478DD0 by itself. One lane predicted that
behaviour from its own matched rows; the other observed it. Two witnesses, and
the second was an experiment the first could not run.

Consequence for the commit: the three `?dup_004790XX` rows are NOT renames.
GameWindow.cpp now emits those bodies byte-exact, so the 101-line replica file
folds home -- same nine addresses, one fewer file.

## A name held HOSTAGE on the wrong address forces someone to invent a name

Third instance of one shape today, and it is now predictive rather than
anecdotal.

`winSetStatus`'s row sat on a body that ORs into +0x04 -- the anchor pointer.
`m_status` is +0x08, and TWO matched rows in the same accessor run already said
so (`winClearStatus`@0x00478440 and `winGetStatus`@0x00478480, both noted
"BFME m_status@0x08"). The correctly-written body compiles to a 19-byte sequence
occurring **exactly once** in retail, at 0x00478420 -- immediately before those
two.

And that address was already claimed, by `?_bfme_winSetStatus@GameWindow@@QAEII@Z`.
**Someone had converted the right body and had to invent a name for it, because
the real name was hostage on the wrong address.** `GameWindowStatusThunk.cpp`
existed only to house that invention.

The three instances:

    VertexMaterialClass   Get_Diffuse_Color_Source unclaimed while its two
                          neighbours sat one field high
    W3DTerrainVisual      two ?dup_ placeholders holding the real bodies of two
                          rotated accessors
    GameWindow            ?_bfme_winSetStatus invented for a body whose true
                          name was pinned elsewhere

**So an invented `?_bfme_`, `?dup_` or thunk-file name adjacent to a real one is
a SYMPTOM.** Someone met a correct body that could not take its correct name and
worked around it. Read those as evidence of a displaced row nearby, not as
scaffolding.

## A fabricated MECHANISM in a comment is worse than a wrong offset

`GameWindowFields.cpp` had `winSetDisabledImage` writing `m_hiliteDrawData`,
under a comment asserting: *"BFME never wrote a distinct disabled-image path
here; write the same field so our object code folds the same way."*

That is an invented mechanism, constructed to justify a body that made a wrong
row verify. Retail has nine separate setters at 0x478FE0 + 0x30, and 0x479070 is
exactly the disabled-image one.

A wrong offset is a mistake and the next reader can measure it. **A wrong
offset with a mechanism attached is an argument, and the next reader has to
refute it** -- the reasoning reads as evidence while being the opposite of it.
It also survives review better than a bare wrong number, which is what makes it
more expensive.

When correcting one, name the old claim in the comment so nobody re-derives it.
And when writing one: a comment may state what was MEASURED and what remains
UNKNOWN. It may not supply a reason the measurement did not establish.

## Byte-exactness proves OUR SOURCE COMPILES TO THOSE BYTES -- never that the name is right

The day's central lesson in its final and sharpest form, and it cost a fully
built, fourteen-address, full-unmasked-evidence GameWindow mapping that was
wrong.

Fourteen bodies each matched retail exactly at a predicted address, on 37/37 and
40/40 and 13/13 surviving bytes. The mapping was still wrong, and retail's own
callers say so -- decoded through the ILT with no names involved:

    GadgetSliderSetEnabledThumbBorderColor  -> ILT 0x000262B0 -> 0x00479010
    GadgetSliderSetDisabledThumbBorderColor -> ILT 0x0001EAEC -> 0x004790A0
    GadgetProgressBarSetHiliteBarBorderColor-> ILT 0x000248B1 -> 0x00479150
    GadgetSliderSetEnabledThumbImage        -> ILT 0x00035E09 -> 0x00478FE0
    GadgetSliderSetHiliteThumbImage         -> ILT 0x0000B406 -> 0x00479120

Five of the nine addresses, naming **the binding that was already in the
ledger**. The mapping was derived entirely from body bytes; no call site was ever
opened.

**The self-check, and it is one grep: before moving a row, ask who calls the
address it is LEAVING.** A caller that names the old binding is the evidence that
outranks any amount of byte agreement -- the same rule that refuted five
re-homings earlier the same day, unused by the same lane a few hours later while
it was writing the commit message about the vertmaterial pad.

**Only the full gate could see it.** All twelve reds were CALLERS in a third file
-- `GameWindowManager.cpp` -- green before the change and invisible to a scoped
run over the two files being edited.

## multi_name's own docstring, falsified by its own tool

The docstring claimed two accessors one family member apart "cannot be one body
whatever our compile says". **AABTree disproves it.**
`Cast_AABox_Recursive`, `Cast_OBBox_Recursive` and `Intersect_OBBox_Recursive`
share 0x0096B100 legitimately: every method they call on their differing type had
already folded, so the callers became genuinely identical.

The rule that separates the two live cases:

  * **FAMILY is REAL when the difference would have to appear in the COMPARED
    bytes.** GameWindow -- a field offset is a literal, and the claimants rest on
    all 37 of their bytes.
  * **FAMILY is UNDECIDABLE when the difference lives inside the MASKED
    relocations.** AABTree -- 211/219 surviving, and the difference is in the two
    calls.

Each FAMILY line now reports which case it is, and **it does not auto-clear**:
clearing a candidate automatically is how a real defect gets filed as noise --
the forbidden fallback in this tool's shape.

## Stop at "not self-consistent" rather than guessing twice

The caller evidence does not yet close: 0x00479120 is reached both as
`GadgetSliderSetHiliteThumbImage`'s image call and as
`GadgetProgressBarSetHiliteBarColor`'s colour call. Either one of those Gadget
rows is itself misnamed, or the parameter convention differs.

That is the correct place to stop -- no replacement mapping proposed, and the
rejected diff banked outside the repo because its four forced discoveries are a
map of where the pressure is even though the binding is wrong. **A wrong answer
kept for its by-products, with the answer itself withdrawn.**

## THE ASYMMETRY FAILURE: a relocation WE have and retail does not

Third distinct way masking hides a difference, and the largest so far: **67
matched rows across 20 bodies.**

Masking blanks every DIR32 site, and it chooses WHICH bytes to blank from the
COMPILED side's relocation list. So a site that is a relocation for us and a
plain literal for retail gets blanked on both sides -- and the one field that
separates the two bodies is the one field nobody compares:

    ours    8b c1  c7 00 <DIR32 ??_7X@@6B@>  c3     mov [eax], vftable
    retail  8b c1  c7 00  00 00 00 00        c3     mov [eax], 0

**A linked absolute address is never zero. All-zero retail bytes under one of our
DIR32 sites prove retail stored NO POINTER there.**

The three masking failures, now distinct:

    QUANTITY   no surviving byte at all (AIPlayer's data table)
    LOCATION   identical surviving bytes, discriminator inside the mask
    ASYMMETRY  we have a relocation site retail does not -- and these rows have
               PLENTY of surviving bytes, all of which agree

15 of the 67 carry an explicit `icf-owner=`, which made the alias look
sanctioned. 23 sit on 0x00087A50 and 21 on 0x00061D90, both storing literal
zero: abstract-base and interface constructors -- MemoryPoolObject, InputStream,
DockUpdateInterface, ObjectDrawInterface, the eight Blit*Xlat instantiations,
PostLoadableClass.

**The real constructors exist and are distinguishable.** Retail holds 215
pointer-storing bodies of the 9-byte shape against 203 zero-storing, and 66 of
the 18-byte shape against 3, each storing a different vftable. So these rows are
on the wrong side of a fork the comparison cannot see, and each is in principle
re-homeable by its own `??_7X@@6B@` address.

**One legitimate zero, excluded BY NAME with a test rather than by a threshold:**
`mov eax, fs:[__except_list]` really does relocate against absolute 0 -- a TIB
offset, not a linked address -- and it opens every try-block in the tree. A
threshold would have buried the result or admitted noise; naming the one real
case does neither.

## A green row over an `__emit` dump is evidence about the DUMP, never its name

`?Recolor_Texture@W3DAssetManager@@QAEHHHHHHHHHH@Z` was a fabricated nine-int
thiscall signature resting on a 658-line `__emit` dump. **Re-emitting retail's
bytes cannot fail to match**, so the green said nothing whatever about whether
the name was right.

Settled by call sites, as it should have been originally: the only two callers of
0x00A5828A in the whole image are `D3DXSaveMeshToXofEx` and
`D3DXPatchSaveMeshToXofEx`, both from `d3dx9.lib`. Retired; the d3dx9 row still
covers the address so no bytes are lost, and both real `Recolor_Texture`
overloads return to `present-unmatched`, which is what they are.

The conversion-direction gate stops new ones. This was an old one verifying
itself.

## COUNT BODIES, NOT ROWS -- where duplicate names are the audit, rows let the defect vote

Second counting defect to change a conclusion today, and the sharper one.

A caller sweep over the GameWindow draw-data run counted ledger ROWS, so a
single body carrying four claimant names contributed four "caller sites". The
apparent six-to-three Colour majority at 0x00479010 was **two bodies**:

    0x0047B650   SetEnabledThumbColor | SetDisabledThumbColor |
                 SetHiliteThumbColor  | SetEnabledThumbBorderColor
    0x0047B700   the same four names, Selected variants

One 28-byte body wearing four names, counted four times, in a sweep whose whole
purpose was to detect bodies wearing several names. **Where duplicate names are
the thing under audit, counting rows lets the defect vote on its own case.**

Recounted by unique body the signal reversed: six unambiguous single-name
BorderColor bodies across two groups, from two independent wrapper families,
and not one Color.

## A displacement is a NUMBER; it names nothing

A proposed shortcut for settling `WinDrawData`'s field order -- "check whether
position 2's displacement is the one our header calls Color" -- is circular, and
it fails in the direction that looks like confirmation.

Position 2 writes base+8, and our header calls +8 `borderColor`. So the test
appears to REFUTE the (correct) hypothesis -- but only by assuming our header's
field order, which is exactly the thing in question. **There is no caller-free
version of this test.**

What retail alone does give is the geometry, which needs no names: bases
0x48 / 0xB4 / 0x120, fields at +0 / +4 / +8, stride 0x6C = 9 x 12. So
MAX_DRAW_DATA is 9 and WinDrawData is three 4-byte fields. Geometry from bytes,
identity from callers -- and never identity from a byte offset interpreted
through the header you are auditing.

## WITHDRAWN: BFME's WinDrawData is ZH's {image, color, borderColor}
**This entry claimed a swapped field order. It is wrong -- the order is
UNCHANGED from ZH. See "an offset is only as absolute as its TU's layout" below;
the apparent swap was a uniform 4-byte base bias read as a field rotation.**

Position 1 is BorderColor on six single-name bodies across two groups and two
independent wrapper families; position 2 has no named callers **because the
Colour wrappers' rows are piled onto the enabled group's position-1 body
instead**. Our header has the last two fields swapped.

So the GameWindow fix is a `WinDrawData` field-order correction in the shim --
not the ledger rebinding that was attempted and reverted. The six
Colour/BorderColor rows and the three `?dup_` position-2 bodies should fall out
once it lands, with the Image third already proven independently.

One residue that does NOT resolve this way and was correctly left alone:
`?GadgetProgressBarSetEnabledBarColor@@` at 0x0047A8C0 is a single-name body
still calling position 0 with idx=4. Under the settled order that looks
misnamed, but it has no companion name to convict it and no inference was made.

## Validate a NULL against a control before trusting it

"Zero callers" and "my query is broken" produce identical output. Before
concluding that 0x00061D90 and 0x00087A50 have no call sites, the same code path
was run against 0x00478FE0 and returned **70 caller bodies**, ILT hops included.
Only then was the null evidence.

This costs one extra query and it is the difference between a finding and a
silent failure -- the same shape as the sweep that once reported "0 refs" for 314
objects it had failed to load, and the regression test that passed with and
without its fix.

**Any time an absence is the result, produce the control that proves the
instrument can see a presence.**

## POOL CAPACITY is evidence, and it can point opposite ways for one defect

The 67-row `null_reloc` family looked like one problem with a leverage point --
44 of the rows on two addresses. The two addresses turned out structurally
opposite:

     9-byte shape   215 pointer-storing bodies   190 free   for 21 rows
    18-byte shape    66 pointer-storing bodies     4 free   for 23 rows

The 9-byte pool has room to spare. **The 18-byte pool has none**: 62 of its 66
bodies are held by a legitimate, coherent template family --
`??0?$SubsystemSlot@V<T>@@@@QAE@PAX@Z`, one instantiation per subsystem, each
with its own vftable -- and those names look right. So its 23 claimants have
nowhere in that pool to go, while the other 21 have 190 candidate homes.

Counting the free bodies in the destination pool tells you whether a re-homing is
even arithmetically possible, before any per-row work.

## Four closed routes are a result; the hypothesis they suggest is still not one

For those 44 rows the negative is solid -- all store a vftable through a DIR32
where retail stores a literal zero, and a linked absolute address is never zero.
The positive half is unavailable, and every route was checked rather than
assumed:

    call sites          zero caller bodies for either (control-validated);
                        expected -- a 9-byte base ctor is inlined into every
                        derived ctor at /O2
    vftable pins        73 ??_7 symbols pinned; none of the 44 classes
    object-symbol=      zero of 146 placeholder-named bodies carries one
    vftable by contents  no matched virtuals exist -- they are abstract interfaces

The hypothesis this suggests -- that retail emits **no standalone constructor at
all** for these classes -- fits every observation and matches the `StringInfo`
disposition already in `deleted_rows.csv`. **It was recorded and not acted on.**
Retiring 44 rows on an inference with no positive evidence would be the reverted
GameWindow mapping at twenty-three times the scale.

Leave them flagged. Either of two events cracks the 9-byte group at once, since
it has 190 free bodies waiting: a vftable pin for one of these classes, or a
single matched virtual method, which locates the vftable by contents and then the
constructor by the address it stores.

**And the framing correction worth keeping: "two questions, not sixty-seven" was
the right instinct, and both answers came back UNAVAILABLE rather than SETTLED.
The leverage was real; the evidence was not there to spend it on.**

## A cache keyed on what was OPENED cannot see a file that changes what WILL be opened

The most dangerous no-op yet, because it wears the appearance of a passed
prediction.

Adding a new header to a shim directory does **not** invalidate the deps cache.
The sidecar records the files the compiler actually opened last time, and a new
higher-priority header is not among them -- so nothing looks stale. The run
reported `Compile: 0 of 3 TU(s)` and a green 209/209, which read exactly like the
prediction being confirmed. Nothing had been compiled at all.

Caught only by asking the sidecar which `WinInstanceData.h` it had read, rather
than trusting the green.

**So whenever a change ADDS a file to an include path rather than editing one
already on it, the deps cache cannot know. Force the rebuild, or verify from the
sidecar that the new file was opened, before believing any result.** This is the
same family as editing `reference/.../vertmaterial.h` when a local copy wins:
both are the build reading something other than what you edited.

## A shim-path grep matched a DIFFERENT shim by prefix

`grep -rl '/Ireference/shims/gamewindow'` also matches
`/Ireference/shims/gamewindowlist`. A substring false positive hid an entire
third shim, and with it the fact that two shims disagree about GameWindow's
layout.

Third matching-or-counting defect of the day, after counting rows instead of
bodies and the double-counted caller table. **When a name is a prefix of another
name, an unanchored grep is a guess.** Anchor the path or read the deps sidecar
-- which is what eventually caught this one, and is the rule this file already
carried for a different reason.

## PREDICT THE CASUALTIES: first use, and it stopped a wrong change

The discipline is: write down which rows will go red BEFORE compiling, name the
ones expected to stay green, then compare.

Predicted three -- `winGet{Enabled,Disabled,Hilite}Color` moving position 0 to
position 2 -- with the three BorderColor getters explicitly called out as
staying green. **Measured ten.** All six getters plus four `GadgetSlider Get*`
wrappers; the headline "stays green" prediction was wrong.

The cause was the hidden third shim: `GameWindowManager.cpp` builds against a
GameWindow.h with no `m_bfmeAnchor`, so its draw-data base sits four low, and
under that base the ZH field order coincidentally puts `color` and `borderColor`
where the correct order puts `image` and `borderColor`. Swapping two fields
slides both by four instead of moving one to position 2.

**Without the written prediction, ten red rows would have read as "the change is
bigger than expected" rather than "the model is wrong."** A count that misses is
a falsification; a count you never wrote down is a surprise you rationalise.

## The rotation-hole proof held, independently of the failed change

Untouched by the revert, and it is the strongest evidence in the round: the three
position-2 getter bodies exist -- 0x0047A280, 0x0047A2C0, 0x0047A300 --
interleaved with the correctly-named BorderColor getters at 0x0047A260,
0x0047A2A0, 0x0047A2E0, and **all three are held by `?dup_` placeholders**.

A rotation must leave a hole. There are three holes, one per group, exactly
where the field order predicts. That is the third confirmed instance of the
rotation-hole structure, and the first where the prediction was made before the
holes were looked for.

## Measure on a PARAMETER to break the circularity

Every GameWindow derivation until now went through `GameWindow`'s own layout --
which was the thing under question -- so each answer depended on the assumption
it was testing. `?parseTooltipDelay@@` breaks it: `add ecx, 0x198` on a
**`WinInstanceData*` PARAMETER**, so the offset is measured INSIDE
`WinInstanceData` with no GameWindow layout anywhere in the path.

Combined with two `this`-relative measurements the system becomes
**over-determined** -- three measurements, two unknowns, no free parameters:

**The first solution of it was WRONG, and the way it was wrong is the lesson.**
It counted `m_id, m_state, m_style, m_status, m_owner` as 0x14 and concluded
`m_instData = 0x2C`, "8 extra bytes in WinInstanceData", and "neither shim's
insertion is real". `WinInstanceData` declares `virtual ~WinInstanceData()`, so
it carries a **vptr at +0** that was not counted. Corrected:

    offsetof(m_enabledDrawData) = 0x18            (vptr + five dwords)
    m_instData                  = 0x48 - 0x18 = 0x30
    m_tooltipDelay              = 0x1C4 - 0x30 = 0x194
    parseTooltipDelay measures                  0x198
    residual                                      4 bytes, AFTER the arrays

**0x30 is exactly what `reference/shims/gamewindow` already asserts**, so that
shim was right all along and only `gamewindowlist` is wrong. The residual 4 bytes
sit after the draw arrays and do not touch the draw-data question.

**Reading five members and stopping is how you get an offset exactly one pointer
wrong** -- and four or eight bytes is precisely the size of error that still
produces plausible, self-consistent arithmetic. Count the vptr. A class with any
virtual function has one, and it is not in the member list you are reading.

This is the same move as the GarrisonContain control view -- the fourth view, on
the `observingPlayer` PARAMETER, needed no adjustment and isolated the effect to
`this`. **A parameter-relative measurement carries no assumption about the class
you are auditing.** Look for one before deriving a layout from `this` alone.

## A shim comment named its own resolution condition, and evidence arrived later

`reference/shims/gamewindowlist` documented the conflict it could not settle: the
`gamewindow` spread "breaks all seven" accessors, and the +0x04 field "can only
coexist with them if something before +0x48 is 4 bytes SMALLER in BFME, which
nothing here proves."

Caller evidence supplied exactly that, from the other side: **three of those
seven pins are on the wrong bodies.** `winGet{Enabled,Disabled,Hilite}Color` sit
at position 0 -- the Image bodies -- so the +0x48 pin they appeared to provide
was never real, and the constraint the author could not discharge was never
binding.

Worth the pattern: **a comment that states its unproven condition precisely is
worth writing even when you cannot discharge it.** It let a later measurement
close a question its author had correctly refused to guess at. Contrast the
fabricated `winSetDisabledImage` mechanism, which asserted a reason and cost a
reader the work of refuting it.

## Predict the OFFSET, not just which rows go red

The prediction discipline sharpened by one turn. First use predicted a set of
rows and got ten where three were named -- a falsification, correctly reverted.
Second use predicted **each row's resulting offset**:

    winGetEnabledColor        -> +0x4C   measured +0x4C
    winGetDisabledBorderColor -> +0xBC   measured +0xBC
    winGetHiliteColor         -> +0x124  measured +0x124
    setTooltipDelay           -> 0x1C8 against retail 0x1C4, red with no home
    ... 11 predicted, 11 measured, zero unpredicted

**A set of row names can be satisfied by a wrong model that happens to break the
same rows. A set of offsets cannot.** Predicting where each row LANDS turns the
check from "did I anticipate the damage" into "is my model of the layout right",
and it costs nothing extra to write down.

Note the fix that came out of it was not the one authorised: not an invented
`m_bfmeAnchor`, but **restoring `m_userData` to its ZH position in front of
`m_instData`**, which `gamewindowlist` had moved to the tail. Restoring a
vendored position beats adding a BFME-only member whenever the arithmetic allows
both -- one asserts less.

## Two independent routes meeting on the same three bodies

The Colour field order was derived from **callers** (six single-name BorderColor
bodies across two groups, counted by body). The probe then derived it from
**layout**: with the field order corrected, Color lands at elem+8 -> +0x50 /
+0xBC / +0x128, which are 0x0047A280 / 0x0047A2C0 / 0x0047A300 -- the three
`?dup_` placeholder bodies.

Neither route used the other's evidence, and the rotation-hole argument predicted
the holes before either had been checked. **Three independent derivations meeting
on the same three addresses** is the strongest standard reached on this class,
and it is the standard the two reverted attempts did not have.

## Investigation sequencing is not COMMIT sequencing

A standing instruction -- "one change, one prediction, its own commit" -- does
not survive when the first change has no green state of its own.

Probe 1 (restore `m_userData`, shrink the pad) leaves 11 rows red; that is what
the probe MEASURED. Those casualties are repaired only by the field order plus
the ledger moves. So splitting it into two commits means landing the first one
red, which is worse than any benefit the split offers.

**The split was right as INVESTIGATION and it worked** -- probing the anchor
alone is what proved the model and localised the residue. It simply is not
separable as commits. When a staged investigation converges, ask whether each
stage has a green state before insisting on one commit per stage; if it does
not, the whole convergence is one commit with one prediction covering all of it.

## The residual dissolved by asking the call-site question first

`setTooltipDelay` compiled to 0x1C8 where retail wrote 0x1C4 -- a 4-byte residue
that would otherwise have gone in as unnamed padding. Asking who calls it
instead:

    0x0098D2B0  writes +0x1C4, claimed by TWO names --
                ?Set_Frame_Mode@ParticleEmitterDefClass@@UAEXH@Z
                ?setTooltipDelay@GameWindow@@QAEXH@Z   <- ZERO callers
    0x0047A330  writes +0x1C8, held by ?set@Rva0047A330DwordSlot@@, whose own
                note reads "disp32 accessor at this+0x1C8; address-derived
                placeholder"

`setTooltipDelay` was on an ICF body shared with an unrelated class's virtual
setter, with no callers -- while a body writing exactly the predicted offset sat
under a placeholder **in the middle of the GameWindow accessor run**. No padding
was needed; the row was simply in the wrong place.

**Five placeholders in one accessor run is itself a signal.** 0x0047A280,
0x0047A2C0, 0x0047A300 and 0x0047A330 all sit interleaved with correctly-named
getters. A dense band of address-derived names inside an otherwise-named run
marks displaced rows, not scaffolding.

And the arithmetic now closes with **zero free parameters** on four independent
measurements:

    m_instData 0x30 + offsetof(m_enabledDrawData) 0x18  = 0x48   caller-confirmed
    m_instData 0x30 + offsetof(m_tooltipDelay)   0x198  = 0x1C8  body at 0x0047A330

The parameter-relative 0x198 is the only number in the system that never passes
through `GameWindow`, and it is the only one that survived both failed
derivations unchanged.

## Check both the READERS and the WRITERS before naming a field

The field order was derived from setter call sites -- 81 of them, six wrapper
families, counted by body -- and the getters were never asked. They disagree.

    setters (call graph)     group+0 is IMAGE
    inline getters (names)   group+0 is COLOR, and the third field is image

Both families are internally consistent. `GadgetButtonGetDisabledColor` and
`GadgetCheckBoxGetDisabledColor` both read +0xB4; the BorderColor pair both read
+0xB8; the SelectedImage pair both read +0xBC -- and the same pattern repeats
exactly at +0x120 / +0x124 / +0x128 in the hilite group. That is structural
agreement across two groups, not one row's opinion.

**One grep would have caught it.** A field has readers and writers, and deriving
its identity from only one side is the same single-derivation failure that
produced two reverted mappings earlier the same day, in a narrower form.

## When two witnesses contradict, rank them by HOW THEY COULD BE WRONG

Not by count, and not by which was found first.

    setter evidence   retail's own CALL GRAPH. No ledger binding can distort it;
                      a wrong row name cannot move where retail jumps.
    getter evidence   ledger row NAMES -- the exact class of thing this lane
                      exists because it is unreliable. Several of those
                      addresses carry two names, with `?dup_` siblings at each
                      offset.

So the setters are the stronger witness *by kind*. But that is a lean, not a
settlement, and a lean is not what should move nine rows. The getter family is
not weak either -- `...GetHiliteSelectedImage` reading the same field offset in
two different groups is a structural claim.

**The resolution of two internally-consistent contradictory witnesses is not a
third derivation. It is finding the question whose answer both must satisfy.**
Here: the "Selected" variants should differ from their plain siblings by INDEX
-- twelve bytes, one `WinDrawData` -- and not by four. If they differ by four,
that is an index-versus-field confusion large enough to explain the whole
contradiction, and it is read-only to check.

## A getter and a setter for one property cannot disagree about which SLOT it lives in

The invariant that resolved the WinDrawData contradiction, and it settles a
two-witness deadlock without counting either side.

The inline getter names, taken at face value, do not fit EITHER candidate order.
They fit a third:

                              +0xB4     +0xB8         +0xBC
    getter names say          Color     BorderColor   SelectedImage
    {image, color, border}    image X   color X       borderColor X
    {image, border, color}    image X   borderColor X color X
    {color, border, image}    color OK  borderColor OK image OK

**A witness that fits neither candidate is not evidence between them** -- it is a
claim about a third possibility, and that possibility has its own consequences to
test. Here: `{color, borderColor, image}` requires "Selected" to mean a different
FIELD of one element.

It does not. Retail's call graph shows every `Selected` wrapper calling the SAME
setter as its plain sibling with a different INDEX:

    GadgetButtonSetEnabledImage          -> 0x00478FE0   idx 0, 5, 6
    GadgetButtonSetEnabledSelectedImage  -> 0x00478FE0   idx 1, 2, 3

Same body, same field, different slot in the nine-element array. So under the
getter-name reading, `GetDisabledSelectedImage` would read index 0's THIRD FIELD
while `SetDisabledSelectedImage` writes index 1's FIRST FIELD -- a getter and a
setter for one property disagreeing about which slot it occupies. That cannot be.

The invariant is sound and it does rule out `{color, borderColor, image}`. But
the conclusion drawn from it -- that `{image, borderColor, color}` therefore
stands -- **was wrong**: the third candidate was an artefact of a 4-byte base
bias, and removing it restores ZH's `{image, color, borderColor}` rather than the
swap. The getters' zero-caller status is still true and still makes them weak as
NAMES; what was misread was their OFFSETS. See the entry below.

## Refuse a stale go-ahead

An approval to run probe 2 crossed the stop report that made probe 2 wrong.
Acting on it would have been "absorbing a known problem" with a lead's
authorisation attached.

**An instruction issued before your latest evidence is not an instruction about
it.** When a go-ahead crosses a finding that changes the question, the finding
wins and the approval needs re-asking. This is the second time today a lane has
been right to decline an instruction of mine -- the other being the
one-commit-per-change rule that would have required landing red.

## An offset read out of a TU is only as ABSOLUTE as that TU's layout

The whole GameWindow field-order detour, in one rule.

`Selected` is exactly `+0x0C` from its plain sibling -- one whole `WinDrawData`
-- across six independent pairs in two groups, eighteen names fitting one model
with no exceptions:

    +0x0B0 GetDisabledImage        +0x0BC GetDisabledSelectedImage
    +0x0B4 GetDisabledColor        +0x0C0 GetDisabledSelectedColor
    +0x0B8 GetDisabledBorderColor  +0x0C4 GetDisabledSelectedBorderColor

So the order is **image +0, color +4, borderColor +8 -- ZH's, unchanged.**

The apparent conflict with the setter callers was never about field order. It is
a uniform **4-byte base offset**:

    enabled   getters say 0x44   setters say 0x48
    disabled  getters say 0xB0   setters say 0xB4
    hilite    getters say 0x11C  setters say 0x120

The inline getters live in a TU whose `GameWindow` is four bytes short -- the
same unshimmed defect already proved for `GameWindow.cpp` and `gamewindowlist`.
**A global -4 makes `{image, color, borderColor}` read as
`{color, borderColor, image}` shifted into the neighbouring slots**, which is
exactly the phantom third order that looked like a decisive third witness.

**Compare DIFFERENCES before comparing OFFSETS.** The getters' spacing was
trustworthy from the first look; their absolute values carried a bias already
measured in two other files. Two errors, and the second was hidden by the first:
absolute offsets read out of a biased TU, and a field-order swap inferred from
setter-caller names when no swap existed.

The `Selected` labels are ledger names and carry no weight. **The load-bearing
evidence is the 0x0C spacing** -- six pairs at one constant is a structural fact;
the words attached to them are not.

## What GameWindow actually established, after three withdrawn derivations

Parked. Solid:

  * geometry -- bases 0x48 / 0xB4 / 0x120, stride 0x6C, nine elements of twelve
  * `m_instData` at 0x30 and `setTooltipDelay` at 0x1C8, closing with no free
    parameter on a parameter-relative measurement
  * `setTooltipDelay` mis-anchored on an ICF body with zero callers; real home
    0x0047A330
  * `gamewindowlist` is four bytes short because `m_userData` was moved to the
    tail -- and the inline getters are a SECOND, independent witness to that
    same shift
  * five placeholders interleaved through one named accessor run

Not established: which of `color`/`borderColor` sits at element+4 under the
setter-wrapper names. Six single-name setter bodies say BorderColor at position
1; eighteen internally cross-checked getter names say Color. **That residue is
left open deliberately** -- it is a fourth derivation on a class that has already
produced three withdrawals, and nothing depends on it.

## When BOTH witnesses are names, the question may be undecidable -- say so

The `color`-versus-`borderColor` question at `WinDrawData` element+4 resisted
three derivations, and the reason is structural rather than a failure of effort:

  * the call GRAPH is retail's -- which body a wrapper calls is a fact;
  * but "bodies named `*BorderColor*` call element+4" leans on the WRAPPER's
    name, which is a ledger binding;
  * and the inline getters lean on the GETTER's name, also a ledger binding.

Two name-based witnesses pointing opposite ways, with **no structural
tiebreak** -- because swapping two same-width fields changes no structure. The
+0x0C Selected spacing, the 0x6C stride, the nine elements and the array bases
all agree with BOTH readings.

**The question is invisible to every byte measurement available.** Naming that
is a result. Three internally-consistent answers that each rested on unaudited
names is what an undecidable question looks like from the inside, and the
correct output is a park with the unblock conditions written down -- not a
fourth attempt.

## Retail's own STRINGS are non-circular naming evidence

The one route out that is not circular: **a parse table.** The `.wnd` script
parser reads these fields by keyword, so `parseDrawData`-style code maps a
literal string -- `"ENABLEDBORDERCOLOR"` -- to an offset. That is a name
supplied by RETAIL rather than by our ledger, which is exactly what every other
witness lacked.

**The machinery already exists.** `tools/fieldnames.py` extracts precisely this
and has produced `reverse/field_names.csv`: 4,416 rows of
`table_rva, ini_key, bfme_offset`, e.g.

    0x00cfc430,CommandBarBorderColor,0x30,ControlBarScheme,m_commandBarBorderColor,65,64

So the unblock is not a research project -- it is pointing an existing extractor
at a specific table, if that table exists. The current file has no `.wnd`
draw-data entries, so the table has not been located; that is a search, and a
search has a clean negative.

**General form: when a naming question deadlocks between two ledger-derived
witnesses, look for a place where retail names the thing itself** -- a parse
table, a keyword string, a debug format. Those are the only names in the binary
that are not ours.

## A THROWAWAY script gets the same audit as a committed tool

The sharpest self-catch of the day. A small follow-up script, written four hours
after the tool that detects exactly this, did:

    len({addrs_a, addrs_b}) == 1

Two **empty** tuples compare equal, so an unpinned symbol on both sides printed
`same-address=True` and was declared a real fold. **Absence of evidence counted
as agreement** -- the masking failure the entire day has been about, reproduced
in a fresh script because the script was small and felt obviously right.

It is the throwaway ones nobody reviews. **Ask a scratch script the same
question you ask a committed one: what does an empty result compare equal to?**

## `symbols.csv` is ADDITIVE, so intersect the candidate sets -- never compare them

Second defect in the same script, and it inverted two verdicts. The resolver
keeps the first pinned address that reproduces retail, so a symbol legitimately
carries several candidates. Comparing SETS for equality calls two claimants
different when they merely have different candidate lists; what matters is
whether the **intersection is non-empty**.

    0x006F7C80  Cull_Box / Cull_Sphere       {0x008DB060, 0x008DB380} vs {0x008DB060}
    0x00979D20  Set_Position / Set_Transform  all three sets contain 0x00982110

Both had been called "cannot be one body". Neither is refuted at all. A corrected
test intersects the sets AND treats an unpinned symbol as *no information*
rather than as agreement.

## The careful tool was right; the quick script was not

`multi_name` reported all five FAMILY candidates as *"the claimants name
different relocation targets, so what separates them was masked"* -- it declined
to guess, and it was right about every one. The follow-up script written to
"settle" them produced two wrong refutations and two false folds.

Honest tally: **1 resolved, 4 undecided**, not the 1-plus-4-defects the first
read suggested. 0x00924840 is real ICF -- all three claimants' single relocation
resolves to exactly 0x0096B100, consistent with the other two AABTree families.

Worth remembering when a tool's cautious verdict feels unsatisfying: the
caution was the tool being correct about the limits of its evidence, and the
instinct to go past it needs an instrument at least as careful as the one that
stopped.

## CLOSED: retail contains no `BORDERCOLOR` string, so the parse-table route does not exist

The `.wnd` route was the one non-circular way to name `WinDrawData` element+4.
It is closed on the strongest evidence available -- **the name is not in the
binary**:

    ENABLEDDRAWDATA    5 hits
    DISABLEDDRAWDATA   5 hits
    HILITEDRAWDATA     5 hits
    ENABLEDCOLOR       1 hit   (a TEXT colour, alongside SELECTED/HILITE/DISABLED)
    BORDERCOLOR        0 hits
    IMAGE:             0 hits
    COLOR:             0 hits

The `...DRAWDATA` keywords exist; their sub-fields do not. The parser reads the
three fields **positionally** inside the value, so retail never spells `color`
or `borderColor` as a string, and there is no `{token, proc, offset}` table for
`fieldnames.py` to read.

**Record it as CLOSED rather than open.** "We could not find the table" invites
another search; "there is nothing to find" does not. A negative established this
firmly is a permanent saving.

So element+4 has **no retail-side name evidence of any kind**. Three sources
could in principle have named it -- the setter wrappers, the inline getters, and
the parser -- and the first two are ledger bindings pointing opposite ways while
the third does not name it at all. With the structural point that swapping two
same-width fields changes no structure, the question is **undecidable from the
tree as it stands**, not merely unsolved.

What could still unblock it, from elsewhere: a caller passing a **literal colour
value** to a position-1 setter, or independent identity for any one of the
`Gadget*Get*Color` / `Set*BorderColor` wrappers from its own callers.

## A discipline survives only if it is cheap enough to use every time

The prediction files, the deps-sidecar check and the stop rule caught five wrong
bindings in one day and let none of them reach the tree. The reason they worked
is not that they were rigorous -- it is that **each one costs almost nothing**.

Banking a prediction to a file before compiling is seconds. Asking the sidecar
which header was opened is one command. Stopping when an unpredicted row goes
red requires no analysis at all. The expensive version of that discipline --
review boards, second opinions, formal write-ups before each attempt -- would
have been skipped by the third attempt and absent for the two that mattered
most.

**Design the check so that using it is cheaper than justifying skipping it.**

## A full gate's GREEN is a statement about the base it ran on

On a tree this busy, that base can be gone before the gate returns. **Eighteen
commits landed during one full-gate run**, so its green described a tree that no
longer existed by the time it finished.

The correct handling, and it was not obvious: rebase and **re-verify on the new
base before pushing**, rather than trusting a result that predates eighteen other
commits. A green is evidence about a specific tree, not a property the commit
carries with it.

**And the subtler half: a regenerated artefact from a stale run is worse than no
regeneration.** That gate refreshed `reloc_names.csv` -- a *valid* refresh of an
18-commit-stale tree, which is precisely what makes it dangerous: it looks
current, it is internally consistent, and it silently reverts eighteen commits
worth of other lanes' updates. It was discarded rather than pushed.

So on a shared tree: check how far the base moved while a long verification ran,
and treat any file the run REGENERATED as stale output rather than as a result.

**And there is a cheap third option, which is the one to take.** A background
gate can outlive its own premise -- both long runs in one evening finished
against a moved base, one by eighteen commits. The choices look like *trust it*
(wrong) or *re-run it* (ten minutes, and the base may move again). The one that
works is neither: **treat the green as provisional and re-verify cheaply on the
new base** -- one scoped `./build.sh <file>`, seconds -- since the expensive
part of the gate was establishing that everything else is green, and only your
own change needs re-checking against the new base.

Two full gates were killed this evening for want of that option. Killing them
was right; a scoped re-verify would have been better still.

## The same defect in a different costume, twice in one evening

`len({a, b}) == 1` with two empty sets comparing equal is filter 1's exact
failure -- **an absence of evidence counted as a match** -- and it recurred in a
scratch script written by someone who had just read filter 1.

That is the strongest argument for building the check into the tool rather than
carrying it as a rule. A rule you have just read does not survive a small script
that feels obviously right. So an implementation of filter 2 must make the
unresolvable case **explicit and separate**: a candidate whose relocation symbol
resolves to nothing is UNDECIDED, and undecided must never narrow the field. The
refusal table has to distinguish "this candidate disagrees" from "this candidate
could not be resolved", or it misleads in exactly the way the two defects did.

## A REGRESSION test and a BOUNDARY GUARD are different things -- label which you wrote

Today produced at least three tests that passed with and without the fix they
claimed to cover. The distinction that prevents it:

  * **regression test** -- verified FAILING without the change and passing with
    it. It proves the change did something.
  * **boundary guard** -- passes either way today, and only fails against a
    WRONG future implementation. It proves nothing now and protects later.

Both are worth writing. Neither substitutes for the other, and **claiming a
boundary guard as a regression test is how a suite grows tests that certify
nothing.** `test_a_tie_is_broken_by_where_the_relocation_points` was verified
failing first; `test_an_unpinned_symbol_does_not_break_a_tie` was not, and was
labelled a guard rather than promoted.

## Design a defect out rather than avoiding it

Filter 2 had to avoid two known traps -- set-equality over additive symbol
addresses, and treating an unpinned symbol as agreement. Neither was avoided by
remembering to; both were made unreachable:

  * **No new comparison was written.** The gate already resolves a relocation by
    trying each candidate address until one reproduces retail's bytes, so the
    verdict asks *"is retail's value among this symbol's addresses"*. Set
    equality is not expressible on that path. Reusing it is also what the other
    lane's test would have CALLED rather than reimplemented -- which is the
    argument for building the shared machinery once.
  * **The verdict is three-valued** -- `True` / `False` / `None` -- and only
    `False` eliminates. A candidate whose symbol is absent from the map neither
    wins nor loses, so an unresolvable tie stays a REPORTED tie rather than
    collapsing to a false answer.

A rule you must remember fails the moment someone writes a small script that
feels obviously right. **A shape that cannot express the mistake does not.**
