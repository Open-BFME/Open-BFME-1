# Rva00566EC0Profile: separate embedded-object lifecycle

The former BfmeAptScreenSkirmish no-argument constructor at 00566EC0 (506 B),
nonvirtual-spelled destructor at 005668C0 (300 B), and deleting destructor at
00566AE0 (30 B) do not belong to the main screen constructed at 0057DA50.
They are renamed together to the address-derived Rva00566EC0Profile identity;
no semantic name is inferred for this smaller object.

Independent identity and layout evidence:

* Retail main-screen constructor 0057DA50 calls ILT00049BC0 -> 00566EC0 on
  this+390, then constructs SkirmishPreferences at +3AC. The embedded extent
  is therefore 0x1C. Its EH state 3 unwinds through ILT0004AC4B -> 005668C0.
* Constructor00566EC0 installs vtable VA0110A314, constructs preferences at
  +4, tests/sets singleton VA012F4B3C, and binds four faction tooltip names.
  Destructor005668C0 installs the same table, removes those four bindings,
  clears that singleton, and destroys preferences at +4.
* The complete 30-byte deleting destructor00566AE0 calls that destructor,
  conditionally deallocates the same pointer according to bit0, returns the
  pointer, and RET4. Vtable0110A314's deleting slot routes to this body.
* The full screen uses singleton012F4B54 and three different vtable views,
  including generic view0110AFE0. Sharing the legacy generic
  ??_7BfmeAptScreenSkirmish@@6B@ symbol made the two constructors' DIR32
  identities collide even though masked instruction bytes matched.

The repair preserves all three extents. The constructor remains in its own
TU. The 300-byte native destructor now declares its genuine virtual ABI and
lets the compiler install the vptr; it naturally emits the exact 30-byte
virtual scalar-deleting destructor in that same TU. The obsolete force-delete
probe is removed. Canonical AsciiString replaces the old local covered-type
copies. Both lifecycle TUs model the actual 24-byte preferences member.

Only one data pin changes spelling: the singleton at VA012F4B3C becomes
?Rva012F4B3CProfile@@3PAVRva00566EC0Profile@@A. Its address is independently
witnessed by both lifecycle bodies; this is a correction of the existing pin,
not a speculative new target. The existing opaque _bfmeSkirmishOptionsVft
address remains0110A314, with its obsolete owner comment corrected.
No function pin or route is added.

Official callers_of closure: the 506-byte constructor is called only by
0057DA50; the 300-byte destructor is called by00566AE0, the main destructor
00579480, and unwind funclets00C35D4F/00C36574. The latter bodies already use
address-derived ILT0004AC4B views and need no semantic rename. There are no
named direct callers of the deleting destructor. Existing thunk and unwind
aliases remain untouched; the full screen's virtual destructor at00579480
retains its independently proven BfmeAptScreenSkirmish identity.

Validation: 506/300/30-byte native probes exact; scoped strict builds include
those lifecycle bodies, the complete3013-byte main constructor and caller
closure. Pin-consistency before/after and normal repository hooks apply.
This repairs already-authored identities and contributes zero native bytes.
Model GPT-6; independent review and repair2026-09-27.
