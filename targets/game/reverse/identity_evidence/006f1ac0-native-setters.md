# Radial image caller and private texture helper

The caller at RVA 0x006F1AC0 is 1416 bytes: the final RET 0x1C is at +0x585,
followed by INT3 at +0x588. Ghidra's independently created function has that
same extent. Its owner/method identity remains unproved, so the reconstruction
retains `RadialImage006F1AC0::draw`. The five calls through ILT 0x00024BCC
reach the already matched Render2DClass::Add_Tri at 0x006EB070. They pass
six two-float references and a color, consistent with its verified source.
The adapter reuses that existing symbol, rather than pinning a second name.

The score-0.99858757 stash was the starting point. After removing a stale
StringBase::str specialization (the canonical header now provides it), it
again differed only at +0xC5/+0xCB: EDX instead of EAX for the first renderer
store. In-class inline setters for **both** fields (+0 and +0x54) make the
complete 1416-byte caller exact modulo its 43 relocation sites. Only the first
setter fixes that first store but perturbs later allocations (272 differences).
The setters keep their address-qualified names and perform just the original
stores. Enum storage and a nested clamp scope leave the original two bytes.

## Private helper, RVA 0x006F18F0

The complete helper is 371 bytes: RET at +0x172, INT3 at +0x173. The caller
loads ECX with Image and pushes a hidden result address; its call at +0xDF
reaches the helper directly, then ADD ESP,4 performs caller cleanup. The helper
returns that result address in EAX. Both Ghidra and retail decoding confirm
this compiler-private convention. A static C++ function compiled with its
actual caller reproduces it without an assembly adapter.

Its native handle, texture, image and asset declarations come from the banked
paired reconstruction documented in 006f21b0-private-helper-and-frame.md.
The helper independently probes exact over all 371 bytes and 21 relocations.
It checks Image status+0x30, copies the one-word raw handle through Image+0x2C,
and increments the underlying texture's 16-bit reference count at +4. Both
paths call the established ShroudTexture::getFilter and set filter+0x10/+0x0C
to one. The loaded-texture path also calls Gen_0090E810::bfmeSetFlag(1).

The native asset-local storage uses the **existing** BfmeList950B constructor
provider at 0x00143B20 through ILT 0x0002FB80, avoiding a second ctor identity.
Its native pointer set reproduces the actual cleanup at 0x00140950 through
ILT 0x00015D7A. A local address-qualified insertion adapter calls the existing
AssetList::operator<<(AsciiString const&) at 0x00141D00 through 0x0001A44C.
This is the same layout view used by existing W3DAptComponentView3D.cpp:
20-byte storage, tree at +0, trailing word at +0x0C and flag at +0x10.
No new inheritance or constructor alias is asserted.

Image::getFilename uses existing ILT 0x000336AE -> 0x00520640 and its canonical
AsciiString return. The native BFMEGetWaterTrackTexture at 0x0090E910 returns
the retained one-word handle. Release uses the existing TextureClass::Release_Ref
binding to 0x009EB7A0. Asset tracking uses Rva0134FAA0 and the established
cdecl one-word Rva009EBAC0, keeping its address-based identity.

## Renderer texture setter, RVA 0x006EB000

The 54-byte body receives the renderer in ECX and a reference to a one-word
retained texture handle on the stack. It compares the input word to renderer
+0x4C, increments input->refs+4, releases the old texture through 0x009EB7A0,
and stores the new texture and a zero/nonzero-derived flag at +0x4C/+0x50.
Its final RET 4 is at +0x33; INT3 starts at +0x36. This independently supports
the address-qualified `Render006F1AC0::setTexture006EB000` declaration, without
asserting a new semantic identity. A body pin, rather than an ILT route alias,
can resolve the caller's observed 0x00032F51 call.

## Review correction

The helper promotion in 5a4d32b098 was reverted after review 7171721b31: its actual caller context still fails five strict PI DIR32 checks. Both bodies remain banked; none of this document claims current production acceptance.

## 2026-10-04 bounded storage-view test

Fresh origin `13bd7532` retains the paired caller bank SHA-256
`eac538ac2fbc285b1187206c09dd6c162fcfd385159ef1a3cf7b5854be1928b9`.
The caller freshly reproduces 1416 bytes and 43 relocation sites, and the
same-TU helper reproduces 371 bytes and 21 sites. These are masked instruction
results, not strict acceptance. A fresh `verify_dir32_addresses` over both
candidate rows reports the same five caller failures and no other address
conflicts. String verification passes with zero literals; constant verification
passes ten float operands. With current production symbols the caller's helper
and setter REL32 names remain unresolved; neither was promoted or pinned.

An actual Ghidra MCP stdio initialize/list-tools/call-tools batch independently
read VA `0x0111F874`, its references, and the caller. The five reported READ
xrefs are instruction VAs `0x00AF1CFB`, `0x00AF1DE3`, `0x00AF1E22`,
`0x00AF1E33`, and `0x00AF1E59`. They consume four-byte x87 float operands:
FLD, FADD, FCOMP, FSUB, and FLD respectively. The PE places the datum at
RVA `0x00D1F874` in `.rdata`, section RVA `0x00C73000`, virtual size
`0x00232000`, characteristics `0x40000040` (readable initialized data,
not writable). Its bytes are `DB 0F 49 40`, IEEE binary32
`3.1415927410125732`. At this revision no `data_rows.csv` interval spans the
address and no source or symbol pin names it. This proves a readable four-byte
partial view, not the full original type, name, enclosing object, or extent.
The next bytes start a separate UTF-16 string; no larger object was inferred.

Only a bounded, causal storage-view family was tested after the existing
scalar experiments:

- `struct Rva00D1F874View { float value00; }; extern const
  Rva00D1F874View Rva00D1F874;`, used as `Rva00D1F874.value00` at all five
  sites, preserves 1416 bytes/43 relocations but retains the five-byte x87
  load/add reversal. The data relocation is address-qualified rather than
  the canonical literal, but the instruction stream is still wrong.
- Defining that const aggregate with the literal initializer makes all five
  references fold to `__real@40490fdb`. Masked instructions become exact,
  while strict identity still demands the canonical VA `0x01087B14` and
  fails against the caller's actual VA `0x0111F874`.
- An extern one-element const-float array has the same reversal as the
  extern aggregate.
- Giving only `corner` or only the aggregate member a volatile read in the
  boundary3 expression grows the caller to 1420 bytes, with 471 or 477
  non-relocation differences. Neither is an improvement.

The key source expression is:

```cpp
float boundary3 = corner + Rva00D1F874.value00;
```

The immediate disassembly window, offsets from caller RVA `0x006F1AC0`:

```text
              retail                          extern aggregate candidate
+031B         MOV EAX,[ESP+30]                 MOV EAX,[ESP+30]
+031F         D9 44 24 20  FLD [ESP+20]        D9 05 <DIR32>  FLD [Rva00D1F874]
+0323         D8 05 74 F8 11 01 FADD [0111F874]
+0325                                         D8 44 24 20  FADD [ESP+20]
+0329         MOV ECX,[ESP+38]                 MOV ECX,[ESP+38]
```

Thus the aggregate candidate moves the datum relocation from `+0x325` to
`+0x321`. The compiler flags are unchanged from the bank, including the
load-bearing `/EHsc` override and `// stlport` marker:

```text
/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
/Igame/Libraries/Source/WWVegas/WW3D2
/Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
/Igame/Libraries/Source/WWVegas/WWMath
/Igame/Libraries/Source/WWVegas/WWLib
/Igame/Libraries/Source/WWVegas/WWDebug
```

No data provider, global-literal pin edit, whitelist edit, production function,
or header change was made. The original best paired bank remains unchanged.

The separately claimed 54-byte renderer setter was also decoded through real
Ghidra MCP. Its own input is a one-word handle passed by reference, not a raw
texture pointer; its last two stores are texture pointer at renderer+0x4C and
zero/nonzero mask at +0x50. A standalone address-qualified view using canonical
`texture.h` reaches 54 bytes/one relocation/four differing bytes (the final
stores are exchanged). It is only a bank, and establishes no newly recovered
native class name or shared dependency benefit. It must not be promoted merely
because a shape score is 1.000.
