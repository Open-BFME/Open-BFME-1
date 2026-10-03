# Drawable ambient startup and its result holder

The 681-byte body at RVA 00417710 ends with RET8 at +2A6, then INT3.
Ghidra function creation independently reports 681 bytes. The GeneralsMD
Drawable.cpp damage-state startAmbientSound overload supplies the source twin;
BFME splits custom and template selection into two owning-result getters and
keeps ambient pointers at Drawable+144/+148. The 417CB0 -> 417A70 -> 417710
caller chain independently agrees with the damage-state/permanent-only contract.

## Result-holder name correction

The bank invented the convenience name AudioEventInfoRef. It has no name
witness in the Zero Hour twin: that source uses AudioEventInfo pointers and
AudioEventRTS references. Its bare class name must not be promoted into a
recovered BFME identity simply because its layout byte-matches. The landed
holder therefore keeps the call-site address as Rva00417710InfoRef. This is a
correction of the bank's unsupported identity claim, not discovery of an
alternative original name.

Independent retail evidence is narrower than the old name:

* Getter 004175F0 takes a hidden output pointer and the damage selector. At
  +64 it loads the output pointer, stores the selected pointer at +68, and
  increments pointee+4 through InterlockedIncrement at +70. The +76 path
  returns the output pointer in EAX and RET8 at +7C. The other paths return
  it at +CE/+D6 and end RET8 at +D3/+E4. Extent: 231 bytes.
* Parent 00417710 keeps each returned word live independently, decrements
  pointee+4 during cleanup and dispatches deleting-destructor slot zero if
  its count reaches zero. This proves ownership and lifetime, not a class
  spelling or template specialization.
* Matched 000B3FA0 accepts a pointer to that pointer and updates receiver+8
  after comparing names at pointee+8 and receiver+14. The existing opaque
  Rva000B3FA0Owner::bfmeSet identity is retained. Its prefix base in the new
  caller is explicitly a zero-offset ABI view, not a source-inheritance claim.

The new pin names only the address-qualified getter, with the opaque holder
return type. The custom getter keeps the existing BfmeHostQR callable name;
an inline holder constructor preserves the post-call cleanup-state boundary.
The audio constructor uses the existing int-timeOfDay overload at 000B2CC0,
not the bank's ObjectID overload. No semantic setter alias is added.

Validation: probe exact 681 bytes; strict scoped build verifies all 29
relocation sites and nine DIR32 references; pin_consistency --check passes.
