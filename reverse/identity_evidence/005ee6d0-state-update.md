# RVA 0x005EE6D0: float state update

The complete 170-byte no-argument thiscall ends at 0x005EE77A with RET. It twice loads a pointer through data+0x4C, using the existing fallback accessor when null. States one and two return immediately without modifying or clamping the float. Otherwise it updates value+0x50 by delta+0x54, tests the signed index+0x58 against eight, and uses eight-byte table entries starting at +0x10. The unsigned elapsed value comes from data+0x34 minus data+0x68, not fields on this receiver. The source preserves these distinctions.

The full existing fallback accessor at 0x005CFF50 (190 bytes, ILT1B18) returns the lazily constructed static object at VA0x12F6510 with no parameters. The source preserves its existing class-spelled return ABI `ParticleSystemZA*`; no extra alias pin is needed. The full existing update helper 0x005EE410 (57 bytes, ILT2666B) computes the next table delta and stores it at +0x54, with a plain RET and no stack arguments. No stronger class identity is claimed for the new owner.

Once elapsed reaches the table threshold, the body copies the table float into +0x50, advances the index and invokes that helper. Exhausted entries set delta to zero. The final ordered float clamps preserve the retail unordered behavior. A TU-local volatile read of the current value fixes the two remaining x87 operand-order bytes without adding instructions; merely commuting the addition did not. The same explicit pointer-slot loads preserve retail's repeated fallback checks.

The scoped byte gate verifies 1/1 including both fallback calls, the update helper, and the float constants. No pins or headers change, the ASM remains untouched, and the 170 rebuilt bytes do not change total exact coverage.
