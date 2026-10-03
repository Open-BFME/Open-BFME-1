# RVA 001B4A50: native vector cross products

The retail body is exactly 224 bytes at RVA `001B4A50..001B4B30`.
The preceding bytes are INT3 padding. Its final `ret 4` starts at
`001B4B2D`, followed by INT3 at `001B4B30`. Ghidra's complete function
at VA `005B4A50` agrees with this extent; the retail PE was checked separately.

The receiver holds a three-row matrix at `+0x64`. The body retains the
translation column at `+0x70/+0x80/+0x90`, calls the existing `Cos(float)`
and `Sin(float)` bodies at RVAs `00873920` and `00873910`, constructs two
cross products, and stores the resulting basis while preserving translation.
The repeated real constant at VA `01075350` contains four zero bytes.

The old bank's `BfmeXformXC::bfmeSetXC` is not an independently established
identity. This recovery uses `Rva001B4A50::method(float)` and makes no semantic
owner claim. Locomotor callers and their saved-transform layout are useful
context but do not independently name this method.

Starting from the bank reproduced 224 bytes with a six-byte positional
mismatch: the FMUL at `+0x6E` and integer stack reload were reversed.
A split arithmetic temporary did not change it. Replacing the local vector
facade with the existing WWMath `Vector3` and `Vector3::Cross_Product`
reproduced every instruction. Adopting the existing `Matrix3D` retained the
exact result. No volatility, assembly, dummy padding, new callee pin, or
shared-header change is needed. The ordinary strict source gate, rather than
the relocation-masked probe alone, determines whether this may be claimed.

## Historical bank versus new production source

The name check pairs the historical partial bank with this new production
file. The original bank is archived byte-for-byte as
`001b4a50-original-bank.cpp.txt`, including `BfmeXformXC`,
`bfmeSetXC`, and `pad`. The active stash must be removed once the body lands.
No established production class/member is removed or renamed: the prior
production row is the generated `?d_001b4a50` placeholder. The bank contains
only a padded local view and has no authoritative identity citation; its
attempt history explicitly rejects its invented owner identity. The new source
therefore uses an address-qualified owner and layout field, as required for
unproven names. Snapshot-bound correction entries document this historical-bank
comparison; they do not authorize renaming a real production identity.
