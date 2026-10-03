# RVA 006A1C60: opaque audio-region scan

The retail body spans 752 bytes, from the stack allocation at RVA 006A1C60
through `ret 8` at +0x2ED. ILT 000445D0 reaches this body. The matched
006B1CE0 initFilters3D caller and retail 006B2FC0 pass the manager in ECX,
a pointer to a playing-audio wrapper, and a byte output pointer. Those
callers prove the calling convention, not a semantic method spelling.
The recovered owner and method therefore remain Rva006A1C60::body.

The wrapper dereference supplies the event at +14, cached XYZ at +1C,
float at +2C, region index at +30, and validity byte at +3E. The manager
uses a settings pointer at +0C, a refresh flag at +636, and an 8-byte-entry
vector at +ADC. All layout views keep the address token; no engine header
is redefined and no additional named class identity is asserted.

## Independent callee and relocation audit

The five named ILT entries printed by callees.py are retained literally
through typed member-call adapters. These preserve ECX and the observed
stack contracts without introducing another pin for a body:

- 00001ECE -> 00695F80: three stack words, `ret 0C` on both exits; writes
  three floats and a validity byte and returns the output address in EAX.
  Incoming manager ECX is unused by this helper, but the parent explicitly
  sets ECX to the manager. The adapter preserves that observed call setup.
- 00010343 -> 000B2280: no stack words; tests event+30 against 2 and returns
  event+2C or zero in EAX. The conflicting BattlePlan label is not used as
  identity evidence. This consumer keeps the ILT identity.
- 0001F253 -> 0009A510: one stack word, `ret 4`; reads the hash buckets
  through manager+ B4/B8 and returns the node payload pointer or null.
- 0000D6ED -> 001BEA90: one region-pointer stack argument, `ret 4`, byte
  result in AL; scans Object records at +2D8, stride 8, bounded by +346.
- 0000A7DB -> 0018FA20: one XYZ-reference stack argument, `ret 4`, byte
  result in AL. Full 367-byte retail decoding confirms the floating-point
  polygon predicate and both return paths.

TheGameLogic remains the existing GameLogic-typed global; the local layout
view is used only at its call site. The strict build verifies the two float
constants (zero and one), all five REL32 destinations, and three DIR32
references, including both loads of TheGameLogic at VA 012F0898.
No jump table, owned vtable, string, or initialized table is emitted.

## Source shape and verification

A reference bound to `regions[i]` generated 778 bytes and 590 differing
non-relocation bytes. Directly indexing the vector for each condition,
region load and successful value reload removes the cached scaled index
and the early zero-register lifetime. It reproduces all 752 retail bytes.
The float comparisons and ternary integer results retain retail's duplicated
early return tails, including the optimized integer comparison against 1.0.

`add_match.py --replace-rva 0x006A1C60` passed the scoped strict build:
Functions OK 1/1, two float constants verified, three DIR32 references
verified. No new pins or shared headers were needed.
