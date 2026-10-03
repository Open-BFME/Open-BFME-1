# RVA 00249F50: list drain and coordinate call

The complete retail body is 178 bytes: `sub esp,1C` at 00249F50 through
`ret 4` at 00249FFF. Ghidra created the same 178-byte function. The one
incoming stack argument is unused. The owner and method stay address-qualified;
the filename passed to the random helper is evidence for source placement,
not a claim of the original method spelling.

The receiver's list sentinel is at +CC, with next at node+0 and payload at
node+8. Each non-null entry goes to virtual slot +90 with a second argument
zero. Table VA 010B0028 slot 36 contains VA 0043AF1C; that ILT reaches
0024BBD0. Its already matched 83-byte body consumes two stack words and
returns with `ret 8` at 0024BC11/0024BC20. We emit no table of our own.
After that call, retail reloads the containing Object pointer at receiver-18
and its physics pointer at Object+208. Local types are layout/ABI views and
do not redeclare Object or PhysicsBehavior.

The owner floats at +8 and +18 are copied before the random call. The native
string at VA 010AFF30 is exactly:

    F:\bfme\Code\gameengine\Source\GameLogic\Object\Contain\HordeContain\HordeSiegeEngineContain.cpp

GetGameLogicRandomValue(3,8,path,782) reaches 00096CF0 through ILT 00001BAE.
Its four cdecl arguments and EAX integer result are witnessed independently
in that 93-byte body and the caller's `add esp,10`. The scale is converted
with FILD, applied to the two loaded components, and itself becomes Z.

The second coordinate is a memberwise nontrivial copy of that scaled triple.
Retail keeps its final XYZ at caller frame +18/+1C/+20 and passes its address
in EDX. Writing only one triple had hidden this lifetime from earlier drafts.
The new C++ copy constructor emits the exact x87/word-copy schedule and all
178 bytes, including the long loop branches, without assembly or volatile.

ILT 0002A284 reaches 0029AC40, which saves incoming ECX as EBP and uses a
single pointer argument. Full 990-byte decoding ends at 0029B01B with
`ret 4`; the parent passes the physics pointer in ECX. Its name and original
coordinate type are not asserted; the adapter calls the recorded ILT name.
There are no new pins, vtables, internal jump tables, or initialized arrays.

Validation: probe matches 178/178 modulo three relocations; add_match runs the
strict source, call, string and constant checks before installing the row.
