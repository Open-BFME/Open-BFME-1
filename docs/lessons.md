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

## Win32BIGFileSystem::openArchiveFile, decoded but not yet landed

0x009CC710, 900 bytes. Everything below is read off the instruction stream and
verified as far as it goes -- a written version matched the whole prologue on
the first attempt, through the file open, the lowercased name, the archive
allocation and the null-file return. It is recorded here so the next attempt
starts from the structure rather than the disassembly.

What BFME does differently from Zero Hour:

- one sixteen byte header read, not three four-byte reads;
- the whole directory table read in a single call into `operator new[]` storage
  and then walked in memory, rather than each entry read a byte at a time;
- `"BIG4"` accepted alongside `"BIGF"`, both loaded through pointer variables at
  0x012D9030 and 0x012D9034 rather than pushed as literals;
- the archive is told its own name through vtable slot 9 before anything else;
- a bad magic is **not** fatal: the parse is skipped but the archive is still
  attached to the file and returned, so the caller gets an empty archive. Only a
  null file pointer returns NULL.

Header, sixteen bytes: magic at +0x00, archive size at +0x04, entry count at
+0x08 big endian, and at +0x0c, big endian, where the entry data starts. That
last one is the allocation size; the read length is it minus sixteen. Entries
are packed back to back: offset and length, both big endian, then a
NUL-terminated name, and the next entry begins at name + strlen(name) + 1.

Callee pins are already in `reverse/symbols.csv`: ArchivedFileInfo's constructor
and destructor at 0x009CC650 and 0x009CC600, `addFile` at 0x009D1110 and
`attachFile` at 0x009CE560.

Two deltas remain, and they are the same delta twice over. The frame comes out
at 0x38 where retail has 0x3c, because retail spills the entry counter to memory
(`dec dword ptr [esp+0x1c]` closes the loop) and the written version keeps it in
a register. Every register choice downstream follows from that, including the
four big-endian decodes, which come out three to six bytes short apiece because
they have a spare register retail does not. Total 61 to 81 bytes short depending
on how the decode is spelled -- and spelling the decode differently does not
help, because the difference is not in the decode. Find the frame slot first.

## The RenderObjClass vtable is still five slots long above slot 96

The slot-40 fix corrected slots 40 through 47. There is a second divergence
further down, and it is now measured rather than suspected:

- slot 96 is right. `Animatable3DObjClass::Render` matches, and it reaches
  `Is_Not_Hidden_At_All` as `call [eax+0x180]`.
- slot 133 is five too high. Writing the two-argument
  `Simple_Evaluate_Bone` produced a body identical to retail except for one
  displacement: it forwards to the three-argument overload as
  `call [edx+0x228]` where retail has `call [edx+0x214]` -- 138 against 133.

So the headers carry five virtuals that retail does not, somewhere between slots
97 and 132. Retail's own layout in that range, read off the
`Animatable3DObjClass` vtable at 0x0113F148, is: 97 unnamed, 98 `Set_Visible`,
99..110 the Is_/Set_ flag pairs through `Set_Additive`, 111..118 the eight
`_bfme_ro_flag*` placeholders, 119 `Get_Collision_Type`, 120
`Set_Collision_Type`, 121 `Is_Complete`, 122 `Is_In_Scene`, 123
`Get_Native_Screen_Size`, 124 `Set_Native_Screen_Size`, 125 `Create_Decal`, 126
and 127 unnamed, 128 `Update_Cached_Bounding_Volumes`, 129
`Update_Sub_Object_Bits`, then Animatable3DObjClass's own five: 130
`Set_Animation_Frame_Rate_Multiplier`, 131 `Peek_Animation_And_Info`, 132
`Is_Animation_Complete`, 133 and 134 the two `Simple_Evaluate_Bone` overloads.
The vtable is 136 slots.

Anything that calls a slot above 96 through a render object is blocked on this.
The cheapest way to find the five is a probe translation unit that includes the
real headers and calls a handful of virtuals, then reading the displacements out
of the object file -- one compile answers it, where guessing costs a build each.

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

## BFME's pivot fade, and what still blocks the two blend evaluators

`HTreeClass::Anim_Update` (0x00953AD0, 987 bytes) is matched, and getting there
turned up a whole subsystem Zero Hour does not have. The fade lives in four
places:

- `PivotClass::PivotFade` at +0xac, written by `Base_Update`, `Anim_Update`,
  `Blend_Update` and `Slave_Update` alike;
- `HAnimClass` virtual slot 13, a per-pivot fade getter taking the same
  `(pividx, frame)` the visibility getter does;
- `NodeMotionStruct`'s ninth channel at +0x20 -- Zero Hour's struct is eight
  pointers and BFME's stride is 0x24 -- which is where a raw animation's fade
  curve lives;
- and `Blend_Update` lerps the two animations' fades by the same percentage it
  lerps the pose: `fade0 + (fade1 - fade0) * percentage`.

The other BFME change in the same family: `Get_Orientation` returns bool rather
than void. It reports whether the animation has any rotation for that pivot.
`Anim_Update` skips the matrix build and post-multiply when it is false;
`Blend_Update` skips the blend when *neither* animation has one and substitutes
identity for whichever does not.

### What still blocks Blend_Update and Combo_Update

With the fade, the orientation guard and the identity substitution written in,
`Blend_Update` compiles to 1473 of retail's 1746 bytes. The remaining 273 are
one thing: retail **inlines `Matrix3D::Multiply`** there, where our build emits
a call. Retail calls it in `Anim_Update` and inlines it in `Blend_Update`, which
is just MSVC's cost model differing between the two functions -- but our
`matrix3d.h` declares `Multiply` non-inline, so we always call it.

That guess was wrong, and the right answer is simpler. Making `Multiply`
`WWINLINE` breaks five other functions in htree.cpp, because MSVC then inlines
it everywhere. `Matrix3D::mul` is **already** `WWINLINE` and does the same job:
`pivot->Transform.mul(a, b)` inlines where `Matrix3D::Multiply(a, b, &dest)`
calls, and that one substitution takes Blend_Update from 1473 to **1744 of
retail's 1746 bytes**. Two different spellings of the same multiply, chosen per
call site -- that is how retail gets the split.

`Matrix3D::Multiply` did turn out to be worth converting on its own account: its
403 bytes match the reference's ALLOW_TEMPORARIES arm exactly, first try,
despite matrix3d.cpp's own note claiming its codegen had drifted.

The last two bytes were the fade, not the multiply: retail reads **motion1's
fade before motion0's** and keeps both results on the x87 stack, where reading
them in the written order makes MSVC spill one and add it back from memory --
`fadd st,st(1)` against `fadd DWORD PTR [esp+0x18]`, two bytes. Declaring the
second animation's fade first closes it, and Blend_Update now compiles to
**exactly 1746 bytes**.

What survives is one operand ordering. Retail's inlined `submul` runs its three
products X, Z, Y -- (0x38 x [esi+0x44]), (0x58 x [esi+0x4c]), (0x48 x
[esi+0x48]) -- and ours runs them Z, Y, X. Things that do **not** move it:
splitting `postMul(Build_Matrix3D(q,mtx))` into two statements, moving `mtx`
inside the rotation block, or using the temp-taking spelling
(`Matrix3D pre = t; t.mul(pre,mtx)`, which costs 124 bytes instead). `submul` is
a shared WWINLINE that `Anim_Update` already matches through, so the ordering is
a scheduling artifact of the larger function rather than a spelling of the
source. That is the whole remaining distance.
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

## Combo_Update's fade is accumulated, and it calls Multiply where Blend_Update inlines it

Two things fall out of retail's `HTreeClass::Combo_Update` (0x00954D90, 1753
bytes) that do not carry over from its sibling.

**The multiply spelling does not generalise.** Retail calls `Matrix3D::Multiply`
here -- `call 0x008D80C0` at 0x00954E99 -- where `Blend_Update` inlines the same
operation through `Matrix3D::mul`. So the two spellings really are chosen per
call site in the original source, and substituting one for the other everywhere
is wrong in both directions.

**The fade is summed, not lerped.** Inside the same loop that ors the
visibilities together:

```
009553C5  call dword ptr [eax + 0x34]      ; the slot-13 fade getter
009553C8  fadd dword ptr [edi + 0xac]      ; += PivotFade
009553CE  fstp dword ptr [edi + 0xac]
009553D7  fld  dword ptr [esp + 0x48]      ; a running count
009553DC  fadd dword ptr [0x01075334]      ; += 1.0f
009553E5  fstp dword ptr [esp + 0x48]
```

and the count is reloaded once the loop ends, so the accumulated fade is
averaged over the animations that contributed. That is a third fade rule, after
`Anim_Update`'s straight read and `Blend_Update`'s lerp.

The C++ body also compiles 96 bytes **longer** than retail's, which points at
the pivot-weight-map handling in the reference having no counterpart in BFME --
retail's HAnimComboClass calls in this function are `Get_Motion`, `Get_Frame`
and three others, with nothing that looks like `Get_Pivot_Weight_Map`.

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

## Texture pipeline: what is actually known, and the three sibling vtables

`locate.py` places nothing from any of the six texture sources -- 0 of 152
functions across `texture.cpp`, `textureloader.cpp`, `surfaceclass.cpp`,
`ddsfile.cpp`, `bitmaphandler.cpp` and `texproject.cpp`. The nine "ambiguous"
hits it does report are all 30-byte `??_G` scalar deleting destructors resolving
to the same six addresses -- folded bodies, worth nothing (see the folded-body
entry above).

`bitmaphandler.cpp` is the useful datapoint: its twelve functions are static and
take no object, so no class layout can be blamed, and they still do not place.
That points at rewritten bodies rather than one shared structural fault.

Three sibling vtables in the family, all reached from constructors around
0x0090E3D0:

```
VA 0x0113A668   stored at 0x0090E4A1
VA 0x0113A6B0   stored at 0x0090E5A1
VA 0x0113A6F8   stored at 0x0090E8AD and 0x0090E9AB
```

All three are 12 slots and share slots 0, 4, 5, 6, 7, 8, 10 and 11; only 1, 3
and 9 are overridden (plus slot 2 in the third). Slot 0 is
`mov eax,[ecx+0x18]; ret`, a plain getter -- **not** a destructor, so whatever
owns this vtable has no polymorphic base, which rules out the `TextureBaseClass`
chain (it derives from `RefCountClass`) and does not fit
`TextureLoadTaskClass` either, whose subclasses override far more than three
slots. Identify the owner before writing anything against these.

Note on addresses: values encoded in instruction operands are **VAs**, and
`IMAGE_BASE` is 0x400000, while the ledger is in RVAs. `read()`/`u32()` in the
probe helper take RVAs, so a vtable printed as `0x0113A668` must be read at
`0x00D3A668`. Getting this wrong returns empty bytes, not an error.
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

## The texture pipeline's real blocker: BFME split the texture classes handle/impl

Earlier entries blamed the format enum for `locate.py` placing nothing from the
texture sources. That was retracted above; this is the actual reason.

BFME's texture objects hold a **pointer at +0 to a separate implementation
object**, where Zero Hour's classes hold their state inline. Seven of thirteen
sampled bodies in the 0x0090D000-0x0090E900 cluster open by dereferencing and
null-testing `[ecx]`, then calling virtuals on what it points at:

```
0090DC60  ?Peek_D3D_Base_Texture@TextureBaseClass@@QBEPAUIDirect3DBaseTexture8@@XZ
0090DC61  mov esi, [ecx]        ; the impl, not a vptr
0090DC63  test esi, esi ; je -> return 0
0090DC6B  mov eax, [esi]        ; the impl's vtable
0090DC6F  call [eax + 0x28]     ; ...and its virtuals
0090DC7A  call [eax + 0x2c]
0090DC7D  mov eax, [esi + 0x14]
0090DC80  mov eax, [eax + 8]
```

The impl is **0x48 bytes** and is allocated at 0x0090D211 (`push 0x48`, then
zeroing +4, +8 through +0x20, +0x34 and +0x38). `+0x38` holds the D3D texture --
`Poke_Texture` writes it and 0x0090E810 writes it through the handle.

This is why no amount of faithful porting makes those bodies match: every Zero
Hour texture method reaches its members directly, and every BFME one reaches
them one indirection away. It is a redesign, not an offset fix, and it explains
all six sources at once (0 of 152 placed).

Do not try to salvage this with small corrections. The way in is the same one
that produced 62 animation functions today: establish the two class shapes from
allocation sites, destructors and vtables first, then let locate.py place the
family. The three sibling vtables noted above (VA 0x0113A668/0x0113A6B0/
0x0113A6F8, 12 slots, slot 0 a plain getter rather than a destructor) are
consistent with being the *impl* side of this split, which is why slot 0 did not
look like a destructor.

Beware the small matched rows here when reconstructing: `?As_TextureClass@TextureBaseClass`
and `?Get_Asset_Type@ZTextureClass` are both 3 bytes at the same address
(0x006CF680), and `?Poke_Texture@TextureBaseClass` is 10 bytes at 0x001BD780
that writes `[ecx+0x38]` -- an impl offset. Folded and near-folded rows like
these will not constrain the layout, and may mislead.
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

2026-08-03: When lifting an existing MASM dump, compare its emitted bytes to the retail target; this tab-control dump carried an extra 0F 8B pair at +0x43 despite a stale exact-match note.
2026-08-03: C-linkage runtime helpers can gain a leading underscore in MSVC COFF; use a functions.csv object-symbol alias when the retail ledger name strips it.
