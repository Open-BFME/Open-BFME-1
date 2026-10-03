# C55C00 intermediate-base cleanup

Parent0084B410 -> handlerC55C0E -> FuncInfoE44E08 state0/-1 selects
C55C00. Its14 bytes load savedECX fromEBP-10, subtractB4 and tail-jump
atC55C09 throughILT0002E40B to005BFA20. The next byte is the EH handler.
Native$L716 selects the same one-state map and calls
??1Mid0112F304@@UAE@XZ. The parent is an existing /vd0 reconstruction
whose normal destructor independently performs the intermediate-vfptr
store after the member destruction.

Before adding its missing pin, compile the native intermediate destructor
itself:15/15 bytes match, with just its DIR32 at+10 masked. Retail005BFA20
loads vbptr fromECX-4, loads vbtable slot1, stores0112F304 atECX+offset-4,
then RET at5BFA2E followed byCC. Native DIR32 targets
??_7Mid0112F304@@6B@, independently recorded atVA0112F304 and also
checked in the matched parent. This proves the virtual-base calling view,
complete body and actual vftable reference, not just equal wildcard bytes.

The new pin is this address-based C++ destructor ABI view of the existing
opaque005BFA20 provider. It asserts no original class name and adds no
second function row or progress claim for that already-matched body.
Existing R2IndirectSlotWrites.cpp provider remains unchanged. Pin
consistency and the full scoped parent/cleanup gate must pass together.
