# RVA 001BBC50: control flow and native lifetime

2026-10-03 b1, gpt-6-astra. Analysis only; no byte-match or lexical identity claim.
Retail baseline: bfme1/retail-1.03-unpacked.

Capstone verifies the complete 1791-byte interval 001BBC50..001BC34F, ending
with RET10 at 001BC34C. Matched GiantBird caller 002C12E0 establishes byte-return
thiscall(Object*, float, float*, path*). Receiver template is +4 and matrix +64.
Object+204 is AI; virtual +150 yields a pointer, incorrectly inferred as float
by Ghidra. Bird fields used are +3F0/+470/+474/+47C. Null object/AI/bird returns
false. Ghidra VA005BBC50 was created and decompiled; retail remains authoritative.

## Whole control-flow inventory

1. Radius = object+0C0 * 0.5, multiplied by final template+14 if that exceeds 1.
   The override query is repeated. Copy object matrix+8 into receiver+64.
2. Increment caller distance by bird+470 and sample path through 148800.
   Failure clears object bits at +114 mask10000000, +11C mask40, +118 mask80,
   notifying individually when changed, then returns true.
3. Success sets receiver position through 1B49E0. Bird+3F0 bit7 or squared
   distance from OBJECT to bird+47C exceeding 4900 controls bit60 and notification.
4. Template byte+18 enables object Thing::setTransformMatrix(receiver matrix).
   Sample path at distance-radius and distance+radius. Each success contributes
   normalized delta-Z through 1B46B0 and OBJECT-relative angle through 150510.
   Rear angle adds pi and normalizes. Count is FLOAT. Average slope and angle.
5. Query 1B5860 turn rate, save abs(angle)>3*rate, clamp to +/-rate, smooth
   bird+474 = old*0.8 + clamp*0.2. Normalize object+44 + clamp and call receiver
   1B4A50 with that float.
6. Object 148990 returns vector relative to path+54 through hidden output arg.
   Length uses x*x + z*z + y*y. If current bird speed*4 exceeds length and slope
   is negative, negate slope; else saved excessive-turn flag adds 1.5 to slope.
7. Accelerate/decelerate old speed toward float argument using 1B8010/1B8070,
   multiply by (1-slope*0.4), clamp using 1B7E90/1B5910. Selected clamp getter
   is called twice. Store bird+470.
8. Terrain virtual+18 takes matrix x,y,zero. Copy GeometryInfo from object+AC.
   Add copied FIELD+14 TIMES 0.25 to terrain height, then maximize matrix z
   against that height. Preserve x/y. VA01083B6C is float0.25, not 1.
9. Slope>0.3 clears bit71/sets102; slope<-0.6 clears102/sets71, with combined
   notification only if needed. Otherwise clear both independently/notify.
10. Object Thing::rva00132200 receives receiver matrix. Initialize vector from
    object+38/+3C/+40, sample path at distance+bird speed, and if successful call
    1B3F60 on the OBJECT receiver. Destroy geometry and return false.

## Specific blocker: owning GeometryInfo temporary

001BC155 takes object+AC; 001BC160 calls FFD10 with local destination ESP+68.
The local has size5C; field+14 is read at 001BC165 and multiplied by 0.25.
State0 is installed at 001BC16F. Normal cleanup001BC2C9 calls FFCA0. EH FuncInfo
DF7500 has state0 -> -1 and cleanupC08C90, adjusting ECX by EBP-68 then jumping
through ILT309F4 to FFCA0. It cannot be replaced by memcpy or empty destruction.

Matched Common/System/GeometryInfoCopyConstructor.cpp independently proves
vectors at +2C/+38, owning string members, and cached fields through +58.
Canonical Common/System/geometry.h and donor Common/Geometry.h retain smaller
ZH layout without those vectors. FFCA0 currently has opaque destructor name
Rva000FFCA0. A layout repair must preserve actual normal/EH vector cleanup and
resolve this identity without creating a duplicate claim.

No reconstruction compiled or banked. Lead decision requested before adding
another local declaration of the already-covered GeometryInfo. This is a
specific native-layout/lifetime dependency, replacing the old vague missing-CFG
diagnosis. Do not reuse the old 681-byte incomplete-path trial.
