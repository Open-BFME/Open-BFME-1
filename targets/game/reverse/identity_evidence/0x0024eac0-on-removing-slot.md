# 0x0024EAC0: secondary interface onRemoving slot

The retail row is a complete 48-byte body ending in `ret 4`. The
constructor at 0x0024E7A0 installs secondary vtable 0x010B0F40 at
complete-object offset +0x20. Its slot 18 (+0x48) contains ILT
0x000282D1, which jumps to 0x0024EAC0. The independently matched
GarrisonContain secondary vtable 0x010AB598 has the corresponding slot 18
pointing to ILT 0x00005C22 and matched
`GarrisonContain::onRemoving(Object *)` at 0x0021F0A0. The 0x0024EAC0 body
passes its one stack argument unchanged to that same ILT and ends `ret 4`.
This identifies the override's `onRemoving(Object *)` method without
inferring its name from code shape alone.

The exact declaring class is not settled. Existing ledger rows call the
0x0024E7A0 constructor `SlaughterHordeContain` and the 0x0024E8E0
destructor `SlaughterHordeContainBase`, yet both retail bodies install this
same secondary vtable. A derived table can contain an inherited base method;
the vtable cannot decide which class declares the override. The new source
therefore uses address-derived owner `Rva0024EAC0` rather than adding a
possibly wrong Base or derived method name.

The earlier bank used invented stand-in class `BfmeOwnAZ` and explicitly
marked its identity unknown. Its `bfmeMarkAZ` routine did not express a
retail identity; the vtable slot and base call now establish `onRemoving`.
Replacing that stand-in owner with an address-derived class is an intentional
correction of the bank's temporary name, not a retreat from a proven class.

After the base call, retail loads the Object pointer from secondary `this-0x18`
(complete module +0x08), tests dword `Object+0x110` against 0x400, sets the
bit only when clear, and calls ILT 0x0002191D. That ILT resolves to the
matched `Object::notifyModelConditionChanged` at 0x001BE1C0. The flag dword
is the first word of the 320-bit Object model-condition field in matched
Object sources; bit 10 corresponds to GARRISONED in the aligned
GarrisonContain source. The native `_STL::bitset<320>` test/set accessors
produce the retail register-held mask shape; the prior raw-int bank at
`targets/game/reverse/attempts/0x0024eac0.cpp` reached 47/48 but folded the mask into
immediates.

The source models only the secondary interface and its owner link, rather
than claiming a complete multiple-inheritance class layout. Strict byte and
relocation verification must confirm both ILT call targets before landing.
