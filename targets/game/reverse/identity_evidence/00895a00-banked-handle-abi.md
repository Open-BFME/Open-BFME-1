# 00895A00 bank identity and return ABI

This changes an unverified attempt, not a matched production identity.
The old bank calls the method `bfmeBuildEVB` and returns its locally invented
`BfmeResultEVB` struct. Its inline `lookupEVB(void **, BfmeStrVKI *)` treats
the lookup as a void output-parameter helper. No EA label, name table,
vtable, Zero Hour twin, or matched caller supplies `bfmeBuildEVB`. The
2026-09-10 bank header and attempt log describe it as a recipe candidate.

Independent retail evidence refutes that ABI model: 00895A00+2E calls
008958D0 with key then hidden result storage. The now-matched
Rva00893030ManagerFind.cpp proves that callee returns
RefHandle008958D0 by value, leaves the hidden result pointer in EAX,
and retains its BfmeDropObjectA payload. The receiver/head/node evidence
is documented in that native provider using independently matched
00895200 removal and 00895260 destruction.

The 274-byte caller ends RET8 at 00895B0F, followed by INT3. Its prologue
references handler C57109, FuncInfo E46584, unwind map E4656C:
state0 owns result guard C570E8; state1 owns incoming-slot cleanup
C570E0; state2 owns local cleanup C57101. Both normal exits copy and
retain a handle before releasing a local. Ghidra and retail bytes agree.

The replacement bank therefore calls the real hidden-return lookup and
keeps the independently supported receiver. `rva00895A00` explicitly
retains the address because no evidence supplies a semantic method name.
It is still nonmatching (294/274 bytes, measured score 0.2044), and no
new production identity or destructor pin is claimed. `bfmeBuildEVB`
was a bank-only invented recipe label, not an established retail name.
