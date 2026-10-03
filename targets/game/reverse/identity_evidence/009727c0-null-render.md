# Null3DObjClass::Render

Native Zero Hour nullrobj.h declares virtual void Render(RenderInfoClass&),
and nullrobj.cpp supplies its empty definition. Both native files already
exist in the game tree; this change only claims the existing clean body
and removes its stale present-unmatched comment.

Retail table VA0113E878 is independently installed by the two matched
Null3DObjClass constructors at009726A0 and009726E0. Named Clone at slot2
and Class_ID at slot3 corroborate its family and slot alignment. The
BFME-adapted game rendobj.h retains the two additional retail slots
between Class_ID and Get_Name and another after Get_Num_Polys, which the
ZH header lacks. With those insertions and the inherited base slots,
Render is slot12; retail's
operand there is VA00D727C0. This establishes the entry and
one-reference-argument void thiscall ABI independently of the bytes.
The compiled native `??_7Null3DObjClass@@6BRefCountClass@@@` COFF table
independently names Render at offset30, with Clone/Class_ID at08/0C and
the three BFME additions at10/14/2C. Its secondary MultiListObjectClass
table is distinct and is not used for this alignment.

RVA009727C0 is exactly RET4 (three bytes), followed by thirteen INT3
before the next aligned entry. Ghidra read_memory at00D727C0 independently
matches all16 baseline bytes. No identity is inferred from byte equality
with another empty function; this native owner has its own table slot.
The scoped add_match gate passes all13 existing/new TU claims.
