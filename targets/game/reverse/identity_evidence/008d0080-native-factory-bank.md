# 008D0080 native factory draft

Extent is2566B. The main return is RET14 at+9E0, but the complete body
includes the invalid-callable cleanup tail ending RET14 at+A03..A05,
then INT3. Ghidra-created body size2563 is an instruction-address census,
not an extent; the raw PE establishes the final three-byte RET.
Existing Rva8D0D80BuildObject.cpp supplies the five-argument thiscall
view and stack offsets0/8. This draft retains that address-derived
create symbol; name_oracle has no aligned layout witness for the class.
No semantic original class name is inferred from string comparisons.

Retail compares exactly Sound, Array, String, Date, TextFormat, Color,
MovieClip, XML, LoadVars and Error (raw strings at VA10A4FAC,1136FE0,
107FC8C,1136FBC,1136E54,107C750,1137300,1136E28,1136F7C,1136FB4).
The body includes array sizing/element append, pooled-string wrapping,
argument-dependent constructors, tagged prototype reference replacement,
optional word-vector copy and optional invocation with both stack pops.

The real lifetime chain is parent+3 -> C5A611 -> FuncInfo E49638:
all17 retail/native predecessor states agree. States3/9/15 select the
three shard actions C5A546/C5A5A0/C5A5F3. Ghidra/raw bytes establish
15B through each RET, respectively sizes16/40/32 with saved EBP+0C/+08/+08
and calls891A80/8C47A0/8A3160. They are still blocked on the parent.
The state map supplies15 allocation-cleanup states for13 allocation
shapes, plus two scoped string lifetimes, including the two distinct XML new expressions and the
by-value Error-string constructor. No standalone fake cleanup is used.

A first complete draft compiles2540B/2056 positional byte differences.
Float fmod with float zero agrees with the retail FST and float-zero
comparison shape, giving2544B/2054 differences, quality0.1824 and
normalized instruction shape0.933 (diagnostic only). A common return
form gives2524B/1982 differences, quality0.1949, shape0.925; both forms
are banked, with the numerical score selecting the latter. There are
still register/prologue differences from+1E, shorter epilogues and
reference-layout drift. These are not byte-exact or production claims.

Class allocation cleanup bodies can be expressed with native new and
TU-local inline sized delete forwarding to existing opaque free helpers.
Raw8C4620/8C4680/8C47A0 bodies take two cdecl stack operands, unlink
storage through897330 then dispatch(storage-8,size+8) via writable
VA1337830. This draft adds no operator pins. Despite __forceinline, the native
cleanup actions still call the class-specific forwarding methods out of
line (state9 calls ??3Rva008B38D0, state15 calls ??3Rva00899F00Base),
introducing an extra wrapper hop relative to retail. That remains a real
operator-identity/link blocker: these wrappers cannot simply be pinned
to the longer retail free bodies. Promotion must independently prove
and reconcile the class operator identities/declarations and canonical
free-body rows; the agreeing state map alone proves neither binding.

Other bindings remain experimental. Legacy8B9C60/8CBA80/8CBB30 ledger
entries are pointer-return member views of constructor calls; this draft
uses unpinned address-derived constructor views and must reconcile them
before promotion. The existing8CB820Derived thirteen-int constructor view
receives pointer bits in arguments1/9 and float bits in argument2; the
draft explicitly preserves those bits, but the original parameter types
still need independent correction. Pool/global aliases, virtual slot
contracts and string destructor identity need a full reference audit.
No pins, production source, baseline changes or cleanup conversions land.
