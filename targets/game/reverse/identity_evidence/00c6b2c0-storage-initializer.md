# One storage initializer at 00C6B2C0

The full 30-byte routine passes an unused local tag reference to the thiscall
body0039D5B0 through ILT00048667, with ECX=VA012F1000. That complete15-byte
callee clears the three words at +0/+4/+8, returns its receiver and uses ret4.
The routine then registers callback00C6FEF0 using the independently pinned
CRT atexit at009F6E26. It cleans eight stack bytes and returns normally.

The complete ten-byte callback00C6FEF0 independently reloads the SAME global
address VA012F1000 and tail-jumps through ILT000422B7 to its cleanup. Its
existing native emitter bfmeForward_00C6FEF0 is reused. Thus both lifetime
ends witness the global address without inferring it from a source's name.

Three old static-initializer claims share this one extent: _$E117 from
ObjectCreationList.cpp, _$E25 from WOLLobbyMenu.cpp, and _$E30 from MapUtil.cpp.
They are emitter-local labels, not three retail bodies. The lobby emitter
specifically calls a list constructor instead of the witnessed zero-three-word
constructor. Source placement and a matched instruction shape cannot establish
which unrelated source initializer owns this address.

Replace all three claims with one address-derived native initializer. The
storage layout and unused tag keep address-qualified names; no game-level
identity is asserted. Existing attribute-pool users corroborate this global,
but their semantic names are unnecessary to this repair. Reuse the actual
registered cleanup rather than synthesize a destructor. Coverage stays30B;
only the failing lobby claim is repaired, with no net byte gain.
