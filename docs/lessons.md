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
