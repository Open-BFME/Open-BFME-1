# Display-string member cleanup

The complete114-byte W3DDisplayString destructor at006F4C50 calls the complete
334-byte renderer cleanup at009409F0 for its members at offsets14 andE0.
That callee installs vptrVA0113CEAC, accesses member+4C, calls the independently
matched renderer Reset body0093EA60, and releases renderer-owned storage.
The old ledger name UnicodeString::releaseBuffer cannot describe this layout.
No new semantic identity is inferred from the other generated names there.

The existing address-witnessed W3DDisplayStringMemberB destructor pin already
points to009409F0. The new focused TU uses that contract with the existing
W3DDisplayString layout header. Its empty native destructor lets the compiler
emit the normal members and base cleanup; it does not write unwind assembly.
Only this TU's renderer member spelling is substituted, retaining its layout.

Retail FuncInfo atRVA00E3B3FC reached by handler00C4BA31 independently identifies
three unwind states. State0 cleans the DisplayString base through ILT0000D823
to004100B0 atC4BA10/8B. State1 cleans member+14 atC4BA18/11B, and state2 cleans
member+E0 atC4BA23/14B; both tail-jump to009409F0. The compiler's corresponding
local labels are used only after checking these parent-associated actions.

All existing extents are preserved. The147-byte parent/action family includes
8B of already-correct base cleanup and139B of previously failing parent/member
cleanup claims. There is zero new byte coverage and no boundary adjustment.
