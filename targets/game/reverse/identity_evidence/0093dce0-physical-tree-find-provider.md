# RVA 0093DCE0: one physical tree-search provider

GPT-6, 2026-10-06. This corrects the provider and callable ABI of an already
covered 60-byte body and two already covered 21-byte callers. It does not
establish an original C++ declaring class, a mapped-value specialization, new
conversion coverage or a measured LINKED-byte increase.

## Retail contract

RVA 0093DCE0 starts by loading the header pointer through ECX, then the root
through header+4. Nodes supply left/right links at +8/+12 and an unsigned-short
key at +16. The search keeps the first node whose key is not less than the
requested key, then checks equality before returning that node or the header.
It reads the key through one stack argument, returns a node pointer in EAX,
and ends with RET4 at +57; the complete extent is 60 bytes. No mapped payload,
global, callee, relocation, exception metadata or virtual dispatch is involved.

The new `Rva0093DCE0Tree` is an address-qualified structural view. Its name
does not claim the original nominal class. The node view models only the
accessed prefix; it neither defines a payload nor asserts a complete allocation
size. The first word is deliberately uninterpreted.

A raw executable-section call scan finds exactly three direct references:
0093E825, 0093FA75 and 009412AD. No E9 route or absolute pointer occurrence to
VA 00D3DCE0 was found in the image. These observations do not rule out arbitrary
computed runtime targets.

The first two belong to the 21-byte wrappers at 0093E820 and 0093FA70. Each
forwards the unchanged ECX and key-reference argument, then stores the returned
node pointer in the caller's result buffer, returns that buffer, and executes
RET8. Their existing opaque names and result structs are retained. Direct
member calls replace the union-based calls to the zero-argument
`Rva0093DCE0Target` declaration.
That obsolete pin is retired after both references disappear; the new
provider's matched row supplies its callable address directly.

## Why the borrowed specialization does not establish ownership

The old `dup_93dce0` row selected the `_M_find` member emitted by the explicit
`map<unsigned short, unsigned char>` instantiation in ConnectionManager.cpp.
This body reads only keys and links, so identical bytes cannot identify its
mapped type. The font caller reads a four-byte payload at node+20. Retail
0093DD20 copies a two-byte key and a four-byte value at value+4; 0093FD80
allocates 24-byte nodes; 00940B40 returns node+20. The uchar specialization
instead places its one-byte payload at node+18. These are different layouts.

The evidence supports a four-byte font payload, but does not prove whether its
original type was a pointer, integer or another four-byte type. The repair
therefore gives this physical address one honest opaque provider rather than
inventing a template specialization or accessing STLport private members.

Only the 0093DCE0 row/provider association changes. ConnectionManager.cpp and
its explicit instantiation remain unchanged: the same emitted `_M_find`
continues to support the existing 0037B060 and 006651C0 rows and other template
members. No alternate name, forwarding thunk or second owner is introduced.

## Parked font caller

The third direct caller is the 81-byte body at 00941290 in
FontCharsClass_Get_Char_Data_BFME.cpp. It calls the existing pin-only
`FontCharDataMap::find` spelling, which has no physical same-name definition.
It did not reference the borrowed ConnectionManager template symbol. Its
source, row and pin are unchanged, so this patch neither repairs nor worsens
that pre-existing unresolved binding. Its FontCharsClass header/name/layout
conflict is outside this unit. The separately landed 260-byte 009412F0 body
receives no new credit here.

## Acceptance

The provider's first normal compiler probe produces all 60 retail bytes with
zero relocations. Both direct-call wrappers produce their full 21-byte bodies.
The unchanged integration gate passes all 42 rows across the four translation
units, including both strictly resolved calls and all retained ConnectionManager
rows. It also passes string/constant, DIR32 and body checks. Normal dependency
validation accepted two cached objects and compiled two; this is not a claim
that every object was freshly compiled in that command.

The staged header-impact tool reaches exactly the new provider and two
wrappers. Pin consistency passes with no new or stale baseline finding.
Independent review checks every emitted nondebug section and relocation,
the three complete retail bodies, retained owners and the parked font binding.

There is no current accepted linking index in this recovered checkout. Source
and COFF proof cannot establish final linker selection or LINKED-byte gains.
Receipts and before/after artifacts are preserved under
`build/font-map-provider-repair-20261006/` in the working checkout.
