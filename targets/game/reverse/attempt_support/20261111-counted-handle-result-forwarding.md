# Counted-handle wrappers: preserve direct hidden-result forwarding

## Native facts

The existing 43B wrappers at 0x0092CA60 and 0x0092CA90 pass their caller's
result address directly to the 41B providers at 0x009292E0 and 0x0092C9D0.
Both native calls use ECX=table and stack arguments output, row, column.
The providers copy one pointer from +0x74+(column+row*2)*4 and increment its
16-bit reference count at +4 when nonnull. Bfme5FiftyFive.cpp supplies the
matched provider symbols and the four-byte BfmeHandleCX representation.
The wrappers do not destroy or decrement the forwarded result.

The old unprovided BfmeSubAUZA/BfmeSubBUZA getter declarations had the right
ABI but different symbols. Existing caller/result identities stay opaque;
this repair does not assert an original EA class name or retag a ledger row.

## Compiler evidence and repair

Prior one-word copy and return-type member-pointer conversions introduced a
stack temporary and copy-back (attempts57245/57246). A force-inline
BfmeHandleUZA constructor instead views the provider member as a void-return
fill operation with an explicit result argument. Returning this directly
constructed result lets VC7.1 pass the original caller storage, with no
intermediate result, extra copy, destructor or reference-count operation.
The union preserves the provider's exact decorated symbol. No pin or alias
is added. The source no longer declares the two unprovided getter names.

Both wrappers retain all43 bytes and all relocations. Normal build of
BfmeConv1347.cpp and Bfme5FiftyFive.cpp passes7/7 rows; all five provider rows
are checked with the consumers. find_declared_unmatched passes. The existing
MSVC7.1 default /O2 /GR- /EHsc- build context is retained (no per-TU override).
This technique was tested only for the two witnessed four-byte result ABIs;
it is not a general license to reinterpret unrelated C++ return types.

BFME2 reference76f0baefa6f285d54bc1ca922397674312a5913f,
Code/GameEngine/Source/Common/BfmeConv1347.cpp, still uses an alternative-name
binding to MeshMatDescClass's getter. It does not supply this constructor
technique or establish the BFME1 provider's class identity; no donor source,
addresses, aliases or headers are imported.

Before: near queue census90c15cdeca lists the two unprovided getter names.
After: the caller COFF references the two matched provider names; current
link selection may remain UNKNOWN because this worktree lacks most census
objects. No linked-byte gain is claimed. No ledger identity or baseline changes.
