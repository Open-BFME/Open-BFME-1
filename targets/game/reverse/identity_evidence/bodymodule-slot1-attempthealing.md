# BodyModuleInterface slot 1: InactiveBody::attemptHealing

## Retail ownership and unique slot

Facts below are from pefile/Capstone reads of
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs unless marked VA.

The InactiveBody module_registry.tsv row records factory 0011F320 and
constructor 00213BF0. Independently decoding the factory shows its call at
0011F35B to ILT 00011FB8 -> 00213BF0. The constructor's final vptr stores are:

| Store RVA | Object offset | Table VA |
|---|---|---|
| 00213C3E | 0 | 010A8B74 |
| 00213C44 | 0x0C | 010A8AB0 |
| 00213C4B | 0x10 | 010A89E0 |

The primary table's slot 2 is ILT 0004B637 -> getter 00213C90, which returns
literal VA 0108FBA8, `InactiveBody`. This proves the table's owner separately
from any destructor name or from this candidate's behavior.

The body-interface table begins:

| Slot | ILT RVA | Body RVA | Identity |
|---|---|---|---|
| 0 | 00039AEA | 00213E40 | matched InactiveBody::attemptDamage |
| 1 | 00017166 | 00213BB0 | this method |
| 2 | 0000A2AE | 00213B90 | matched InactiveBody::estimateDamage |

ILT 00017166 is a five-byte E9 to 00213BB0. A complete mapped-image search
for its little-endian VA yields exactly VA 010A89E4, this slot. The owner
therefore defines this callback, rather than inheriting a shared implementation.
The catalog of registered Body-module constructors also places matched
ActiveBody::attemptHealing (0020FBC0, ILT 00027962) in slot 1 of ActiveBody's
body table and its inheriting HighlanderBody/ImmortalBody tables. Later BFME
slots differ from ZH; this proof makes no mapping claim about them.

## Exact-name and behavior witness

GeneralsMD `Code/GameEngine/Include/GameLogic/Module/BodyModule.h:119` starts
its interface with attemptDamage, attemptHealing, estimateDamage.
`InactiveBody.h:53-55` declares those same public virtual overrides, and
`Code/GameEngine/Source/GameLogic/Object/Body/InactiveBody.cpp:114` supplies
the exact method twin: null is ignored; non-healing input is forwarded to
attemptDamage; healing zeros both damage-result floats and sets noEffect.
The independently matched BFME attemptDamage and estimateDamage bracket slot 1.
The matched attemptDamage also calls slot 1 when its damage type equals 7,
just as the ZH twin does. This is name evidence, not a behavioral guess.

Retail 00213BB0 decodes completely as follows (VA form):

```
00613BB0 mov eax,[esp+4]
00613BB4 xor edx,edx
00613BB6 cmp eax,edx
00613BB8 je 00613BD2
00613BBA cmp dword ptr [eax+10h],7
00613BBE je 00613BC8
00613BC0 mov edx,[ecx]
00613BC2 mov [esp+4],eax
00613BC6 jmp dword ptr [edx]
00613BC8 mov [eax+50h],edx
00613BCB mov [eax+54h],edx
00613BCE mov byte ptr [eax+58h],1
00613BD2 ret 4
```

INT3 starts at 00213BD5, so the proven extent is exactly 37 bytes. The
secondary-interface ECX and tail dispatch to slot 0 agree with the existing
InactiveBody.cpp hierarchy. The source's existing DamageInfo view already
uses the same witnessed offsets in its matched attemptDamage method; no new
member names or layout declarations are introduced. The ZH method is public,
virtual, non-const, void-returning with one DamageInfo* argument, yielding
`?attemptHealing@InactiveBody@@UAEXPAVDamageInfo@@@Z`.

Replace `?bfmeGoCD@BfmeThingCD@@QAEXPAUBfmeItemCD@@@Z` at the same extent and
remove its retired body and now-unused placeholder classes from
BfmeOneHundredSeventyNine.cpp. Verify the new method and the two existing
InactiveBody.cpp methods together.
